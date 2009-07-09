/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef WIN32
#include "player_ffmpeg.h"
#define localAV_NOPTS_VALUE int64_t(0x8000000000000000LL)
#else
#define __STDC_CONSTANT_MACROS 1
#include "player_ffmpeg.h"
#undef __STDC_CONSTANT_MACROS
#define localAV_NOPTS_VALUE AV_NOPTS_VALUE
#endif

#include <SDL.h>
#include <SDL_audio.h>
#define SDL_AUDIO_BUFFER_SIZE 1024

Q_EXPORT_PLUGIN2(player_ffmpeg, PlayerFfmpeg) 

uint8_t PlayerFfmpeg::audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 5)];

PlayerFfmpeg *instance = 0;

void audio_callback(void *userdata, Uint8 *stream, int len)
{
	if(instance) {
		instance->fetchData(stream, len);
	}
}
	
PlayerFfmpeg::PlayerFfmpeg() : inited(false), opened(false), pFormatCtx(0), pCodecCtx(0), pFrame(0), audioStream(-1), needToStop(false), curvolume(1.f), byteSeek(false)
{
	av_register_all();
	instance = this;
	inited = !SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeSlot()));
	timer->start(100);
}

PlayerFfmpeg::~PlayerFfmpeg()
{
	close();
	SDL_Quit();
	delete timer;
}

bool PlayerFfmpeg::prepare()
{
	return inited;
}

bool PlayerFfmpeg::ready()
{
	return inited;
}

bool PlayerFfmpeg::open(QUrl fname, long start, long length)
{
	close();
	SDL_LockAudio();
	QString filename = ToLocalFile(fname);
	if(!filename.size()) {
		filename = fname.toString();
	}

	if(fname.toString().right(4).toLower() == "flac") byteSeek = true;
	else byteSeek = false;

	if(av_open_input_file(&pFormatCtx, filename.toLocal8Bit(), NULL, 0, NULL)!=0) {
		processErrorMessage("FFmpeg: Couldn't open file "+ filename);
		return false;
	}
	// Retrieve stream information
	if(av_find_stream_info(pFormatCtx)<0) {
		processErrorMessage("FFmpeg: Couldn't find stream information in "+filename);
		return false;
	}

	// Find the first audio stream
	audioStream=-1;
	for(int i=0; i<pFormatCtx->nb_streams; i++)
		if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
			{
				audioStream=i;
				break;
			}

	if(audioStream==-1) {
		processErrorMessage("FFmpeg: Didn't find audio stream in "+filename);
		return false;
	}

	// Get a pointer to the codec context for the video stream
	pCodecCtx=pFormatCtx->streams[audioStream]->codec;

	AVCodec *pCodec;

	// Find the decoder for the audio stream
	pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec==NULL) {
		processErrorMessage("FFmpeg: Codec not found for "+filename);
		return false;
	}

	// Inform the codec that we can handle truncated bitstreams -- i.e.,
	// bitstreams where frame boundaries can fall in the middle of packets
	if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
		pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

	// Open codec
	if(avcodec_open(pCodecCtx, pCodec)<0) {
		processErrorMessage("FFmpeg: Could not open codec for "+filename);
		return false;
	}

	pFrame=avcodec_alloc_frame();

	SDL_AudioSpec wanted_spec, spec;
	// set up SDL_audio
	wanted_spec.freq = pCodecCtx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = pCodecCtx->channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
	wanted_spec.callback = audio_callback;
	wanted_spec.userdata = pCodecCtx;

	if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
		processErrorMessage(QString("SDL_OpenAudio: ")+ SDL_GetError());
		return false;
	}

	opened = true;
	audio_buf_ptr = 0;
	curts = 0;
	startts = start * pFormatCtx->streams[audioStream]->time_base.den / pFormatCtx->streams[audioStream]->time_base.num / 75;
	stopts = double(length + start) * pFormatCtx->streams[audioStream]->time_base.den / pFormatCtx->streams[audioStream]->time_base.num / 75;
	if(stopts > pFormatCtx->streams[audioStream]->duration && pFormatCtx->streams[audioStream]->duration > 0) 
		stopts = pFormatCtx->streams[audioStream]->duration;
	int64_t ts = startts;
	int flags = AVSEEK_FLAG_ANY;
	if(byteSeek) {
		flags |= AVSEEK_FLAG_BYTE;
		//ts *= 3;
		if(pFormatCtx->bit_rate)
			ts = ts * pFormatCtx->streams[audioStream]->time_base.den * 60 / pFormatCtx->bit_rate / pFormatCtx->streams[audioStream]->time_base.num;
		else {
			qDebug("pFormatCtx->bit_rate is null, multiply by %f", (float)pFormatCtx->streams[audioStream]->time_base.den / 180000 / pFormatCtx->streams[audioStream]->time_base.num);
			ts = ts * pFormatCtx->streams[audioStream]->time_base.den / 180000 / pFormatCtx->streams[audioStream]->time_base.num;
		}
	}
	bool result = !startts || av_seek_frame(pFormatCtx, audioStream, ts, flags) >= 0;
	curts = startts;
	SDL_UnlockAudio();

	getNextFrame(true);
	
	return true;
}

bool PlayerFfmpeg::play()
{
	SDL_PauseAudio(0);
    return true;
}

bool PlayerFfmpeg::stop()
{
	//SDL_PauseAudio(1);
	close();
    return true;
}

bool PlayerFfmpeg::setPause(bool p)
{
	SDL_PauseAudio(p);
	if(pFormatCtx) {
		if(p) av_read_pause(pFormatCtx);
		else av_read_play(pFormatCtx);
	}
    return true;
}

bool PlayerFfmpeg::close()
{
	SDL_LockAudio();
	// Free the frame
	if(pFrame) {
		av_free(pFrame);
		pFrame = 0;
	}
	// Close the codec
	if(pCodecCtx) {
		avcodec_close(pCodecCtx);
		pCodecCtx = 0;
	}
	// Close the video file
	if(pFormatCtx) {
		av_close_input_file(pFormatCtx);
		pFormatCtx = 0;
	}
	if(opened) {
		SDL_PauseAudio(1);
		while(SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {}
		//SDL_Delay(1000);
		SDL_CloseAudio();
		SDL_UnlockAudio();
	} else
		SDL_UnlockAudio();
	opened = false;
    return true;
}

bool PlayerFfmpeg::setPosition(double pos)
{
	SDL_LockAudio();
	bool result = false;
	try {
		int64_t ts;
		if(stopts) {
			ts = pos * (stopts - startts) + startts;
		} else {
			ts = pos / pFormatCtx->streams[audioStream]->time_base.num * pFormatCtx->streams[audioStream]->time_base.den * pFormatCtx->duration / AV_TIME_BASE;
		}
		int flags = AVSEEK_FLAG_ANY;
		curts = ts;
		if(curts >= ts) flags |= AVSEEK_FLAG_BACKWARD;
		if(byteSeek) {
			flags |= AVSEEK_FLAG_BYTE;
			if(pFormatCtx->bit_rate)
				ts = ts * pFormatCtx->streams[audioStream]->time_base.den * 60 / pFormatCtx->bit_rate / pFormatCtx->streams[audioStream]->time_base.num;
			else {
				qDebug("pFormatCtx->bit_rate is null, multiply by %f", (float)pFormatCtx->streams[audioStream]->time_base.den / 180000 / pFormatCtx->streams[audioStream]->time_base.num);
				ts = ts * pFormatCtx->streams[audioStream]->time_base.den / 180000 / pFormatCtx->streams[audioStream]->time_base.num;
			//ts *= 3;
			}
		}
		if(curts >= ts) flags |= AVSEEK_FLAG_BACKWARD;
		result = av_seek_frame(pFormatCtx, audioStream, ts, flags) >= 0;
	} catch(...) {
	}
	SDL_UnlockAudio();
	return result;
}

double PlayerFfmpeg::getPosition()
{
	if(stopts) {
		return (double)(curts - startts) / (stopts - startts);
	}
	return (double)pFormatCtx->streams[audioStream]->time_base.num*curts / pFormatCtx->streams[audioStream]->time_base.den / pFormatCtx->duration * AV_TIME_BASE;
}

int  PlayerFfmpeg::volume()
{
	return curvolume * 100.f;
}

void PlayerFfmpeg::setVolume(int v)
{
	curvolume = (float)v * 0.01f;
}

bool PlayerFfmpeg::playing()
{
    return SDL_GetAudioStatus() == SDL_AUDIO_PLAYING;
}

int PlayerFfmpeg::weight()
{
	return 15;
}

QString PlayerFfmpeg::name()
{
	return "FFmpeg";
}

bool PlayerFfmpeg::getNextFrame(bool fFirstTime)
{
    static AVPacket packet;
    static int      bytesRemaining=0;
    static uint8_t  *rawData;
    //static bool     fFirstTime=true;
    int             bytesDecoded;
    int             frameFinished;
	int             audio_buf_size = sizeof(audio_buf) - audio_buf_ptr;

    // First time we're called, set packet.data to NULL to indicate it
    // doesn't have to be freed
    if(fFirstTime)
    {
        //fFirstTime=false;
        //packet.data=NULL;
		av_init_packet(&packet);
		bytesRemaining = 0;
		rawData = 0;
    }

    // Decode packets until we have decoded a complete frame
    while(true)
    {
		audio_buf_size = sizeof(audio_buf) - audio_buf_ptr;
		if(bytesRemaining > audio_buf_size) bytesRemaining = audio_buf_size;
		
        // Work on the current packet until we have decoded all of it
        while(bytesRemaining > 0)
        {
			audio_buf_size = sizeof(audio_buf) - audio_buf_ptr;
			if(audio_buf_size < AVCODEC_MAX_AUDIO_FRAME_SIZE && audio_buf_ptr > 0) 
				goto frame_unpacked;
				//return true;
            // Decode the next chunk of data
//#ifdef WIN32
//			bytesDecoded=avcodec_decode_audio3(pCodecCtx, (int16_t *)audio_buf + audio_buf_ptr, &audio_buf_size, &packet);
//#else
			bytesDecoded=avcodec_decode_audio2(pCodecCtx, (int16_t *)audio_buf + audio_buf_ptr, &audio_buf_size, rawData, bytesRemaining);
//#endif

            // Was there an error?
            if(bytesDecoded < 0)
            {
                //fprintf(stderr, "Error while decoding frame. Got %d bytes\n", (int)audio_buf_ptr);
                //return false;
				bytesDecoded = 0;
				audio_buf_size = 0;
				bytesRemaining = 0;
				//return true;
				goto frame_unpacked;
            }
			audio_buf_ptr += audio_buf_size;
			//audio_buf_size -= bytesDecoded;

            bytesRemaining-=bytesDecoded;
            rawData+=bytesDecoded;

            // Did we finish the current frame? Then we can return
			if(bytesRemaining <= 0 && audio_buf_ptr > 0) {
				av_free_packet(&packet);
                //return true;
				goto frame_unpacked;
			}
        }

        // Read the next packet, skipping all packets that aren't for this
        // stream
        do
        {
            // Free old packet
            if(packet.data!=NULL)
                av_free_packet(&packet);

            // Read new packet
            if(av_read_frame(pFormatCtx, &packet)<0) {
				if(packet.data!=NULL)
					av_free_packet(&packet);
				SDL_PauseAudio(1);
				needToStop = true;
				processErrorMessage("FFmpeg: End of stream");
				return false;
			}
        } while(packet.stream_index!=audioStream);

		if(packet.pts != (int64_t)localAV_NOPTS_VALUE)
			curts = packet.pts;
		if(stopts > 0 && curts >= stopts) {
			if(packet.data!=NULL)
				av_free_packet(&packet);
			SDL_PauseAudio(1);
			needToStop = true;
			processErrorMessage(QString("FFmpeg: End of song. Current TS %1, stop TS %2").arg(QString::number(curts)).arg(QString::number(stopts)));
			return false;
		}
        bytesRemaining=packet.size;
        rawData=packet.data;
    }
frame_unpacked:
	if(packet.pts == (int64_t)localAV_NOPTS_VALUE) {
		curts += audio_buf_ptr / 2 / pCodecCtx->channels;
	}
	//int64_t nopts = localAV_NOPTS_VALUE;
	//processErrorMessage(QString("curpts %1, stopts %2").arg(QString(QByteArray((const char*)&curts, sizeof(int64_t)).toHex())).arg(QString(QByteArray((const char*)&stopts, sizeof(int64_t)).toHex())));
	return audio_buf_ptr > 0;
}

void PlayerFfmpeg::fetchData(unsigned char *stream, int len)
{
	int len1, audio_size;
	SDL_LockAudio();
	//static uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	static unsigned int audio_buf_size = audio_buf_ptr;
	static unsigned int audio_buf_index = 0;

	//processErrorMessage("fetchData");
	//getNextFrame();
	//memcpy(stream, audio_buf, len);
	while(len > 0) {
		if(audio_buf_index >= audio_buf_size) {
			// We have already sent all our data; get more 
			audio_buf_ptr = 0;
			try {
				if(!getNextFrame()) {
					SDL_UnlockAudio();
					return;
				}
			} catch (...) {
				SDL_UnlockAudio();
				processErrorMessage("FFmpeg: Exception while reading next frame");
				return;
			}
			//audio_size = audio_decode_frame(aCodecCtx, audio_buf,	sizeof(audio_buf));
			if(audio_buf_ptr < 0) {
				// If error, output silence 
				audio_buf_size = 1024;
				memset(audio_buf, 0, audio_buf_size);
			} else {
				audio_buf_size = audio_buf_ptr;
			}
			audio_buf_index = 0;
			correctVolume(audio_buf + audio_buf_index, audio_buf + audio_buf_size, curvolume);
		}
		len1 = audio_buf_size - audio_buf_index;
		if(len1 > len)
			len1 = len;
		memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);
		len -= len1;
		stream += len1;
		audio_buf_index += len1;
	}
	SDL_UnlockAudio();
}

void PlayerFfmpeg::timeSlot()
{
	SDL_LockAudio();
	if(needToStop) {
		stop();
		emit finish();
		needToStop = false;
	}
	if(opened) {
		if(SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {
			if(stopts > 0) {
				emit position( (double)(curts - startts) / (stopts - startts) );
			} else {
				emit position((double)pFormatCtx->streams[audioStream]->time_base.num*curts / pFormatCtx->streams[audioStream]->time_base.den / pFormatCtx->duration * AV_TIME_BASE);
			}
		}
	}
	SDL_UnlockAudio();
}

void PlayerFfmpeg::correctVolume(uint8_t* start, uint8_t *end, float volume)
{
	if(volume <= .0f) {
		memset(start, 0, end - start);
	} else if(volume == 1.f) return;
	int16_t *i = (int16_t*)start, *e = (int16_t*)end;
	int32_t l;
	while(i <= e) {
		l = *i * volume;
		if(l > SHRT_MAX) l = SHRT_MAX;
		if(l < SHRT_MIN) l = SHRT_MIN;
		*i = l;
		i ++;
	}
}

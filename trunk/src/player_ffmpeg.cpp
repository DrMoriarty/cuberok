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
#define QUEUESIZE 16

Q_EXPORT_PLUGIN2(player_ffmpeg, PlayerFfmpeg) 

//uint8_t PlayerFfmpeg::ffmpeg.audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 5)];

PlayerFfmpeg *instance = 0;

///////////////////
//
// static functions
//
///////////////////

bool getNextFrame(bool fFirstFrame = false);
void correctVolume(uint8_t* start, uint8_t* end, float volume);
void fetchData(unsigned char *stream, int len);

void audio_callback(void *userdata, Uint8 *stream, int len)
{
	//if(instance) {
		fetchData(stream, len);
	//}
}

struct _ffmpeg{
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVFrame *pFrame;
	int audioStream;
	uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 4)];
	int audio_buf_ptr;
	bool needToStop;
	int64_t curts, startts, stopts;
	float curvolume;
	bool byteSeek;
	SDL_AudioSpec sdl_spec;
	QString error;
	bool pause;
	float seekTo;
	SampleFormat audio_src_format;
	ReSampleContext* resampleCtx;
	QQueue<AVPacket> packetQueue;
} ffmpeg;


void correctVolume(uint8_t* start, uint8_t *end, float volume)
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

void freePacket(AVPacket &packet)
{
	if(packet.data) free(packet.data);
	packet.data = 0;
	packet.size = 0;
	packet.pts = (int64_t)localAV_NOPTS_VALUE;
}

bool getNextFrame(bool fFirstTime)
{
    static AVPacket packet;
    static int      bytesRemaining=0;
    static uint8_t  *rawData;
    int             bytesDecoded;
	int             audio_buf_size = sizeof(ffmpeg.audio_buf) - ffmpeg.audio_buf_ptr;

    if(fFirstTime) {
		//av_init_packet(&packet);
		freePacket(packet);
		bytesRemaining = 0;
		rawData = 0;
    }

    // Decode packets until we have decoded a complete frame
    while(1)
    {
		audio_buf_size = sizeof(ffmpeg.audio_buf) - ffmpeg.audio_buf_ptr;
		if(bytesRemaining > audio_buf_size) bytesRemaining = audio_buf_size;
		
        // Work on the current packet until we have decoded all of it
        while(bytesRemaining > 0)
        {
			audio_buf_size = sizeof(ffmpeg.audio_buf) - ffmpeg.audio_buf_ptr;
			if(audio_buf_size < AVCODEC_MAX_AUDIO_FRAME_SIZE && ffmpeg.audio_buf_ptr > 0) 
				goto frame_unpacked;
//#ifdef WIN32
//			bytesDecoded=avcodec_decode_audio3(ffmpeg.pCodecCtx, (int16_t *)ffmpeg.audio_buf + ffmpeg.audio_buf_ptr, &audio_buf_size, &packet);
//#else
			bytesDecoded=avcodec_decode_audio2(ffmpeg.pCodecCtx, (int16_t *)ffmpeg.audio_buf + ffmpeg.audio_buf_ptr, &audio_buf_size, rawData, bytesRemaining);
//#endif
            if(bytesDecoded < 0)
            {
				bytesDecoded = 0;
				audio_buf_size = 0;
				bytesRemaining = 0;
				goto frame_unpacked;
            }
			ffmpeg.audio_buf_ptr += audio_buf_size;
			//audio_buf_size -= bytesDecoded;

            bytesRemaining-=bytesDecoded;
            rawData+=bytesDecoded;

			if(ffmpeg.audio_src_format != ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_fmt) {
				// need to convert
				if(ffmpeg.resampleCtx)
					audio_resample_close(ffmpeg.resampleCtx);
				ffmpeg.resampleCtx = av_audio_resample_init( ffmpeg.pCodecCtx->channels,
															 ffmpeg.pCodecCtx->channels,
															 ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_rate,
															 ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_rate, 
															 SAMPLE_FMT_S16,
															 ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_fmt,
															 0, 0, 0, .0f);
				if(!ffmpeg.resampleCtx) {
					ffmpeg.error = QString("Can't convert from %1 to %2").arg(QString::number(ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_fmt)).arg(QString::number(SAMPLE_FMT_S16));
				} else {
					ffmpeg.error = QString("Enable convert from %1 to %2").arg(QString::number(ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_fmt)).arg(QString::number(SAMPLE_FMT_S16));
				}
				ffmpeg.audio_src_format = ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec->sample_fmt;
			}
            // Did we finish the current frame? Then we can return
			if(bytesRemaining <= 0 && ffmpeg.audio_buf_ptr > 0) {
				//av_free_packet(&packet);
				freePacket(packet);
				goto frame_unpacked;
			}
        }

		// Free old packet
		if(packet.data!=NULL) {
			//av_free_packet(&packet);
			freePacket(packet);
		}

		// Read new packet
		if(ffmpeg.packetQueue.size()) {
			packet = ffmpeg.packetQueue.dequeue();
		} else {
			//SDL_PauseAudio(1);
			//ffmpeg.needToStop = true;
			return false;
		}
		if(packet.pts != (int64_t)localAV_NOPTS_VALUE)
			ffmpeg.curts = packet.pts;
		if(ffmpeg.stopts > 0 && ffmpeg.curts >= ffmpeg.stopts) {
			//if(packet.data!=NULL)
			//	av_free_packet(&packet);
			freePacket(packet);
			SDL_PauseAudio(1);
			ffmpeg.needToStop = true;
			return false;
		}
        bytesRemaining=packet.size;
        rawData=packet.data;
    }
frame_unpacked:
	if(packet.pts == (int64_t)localAV_NOPTS_VALUE) {
		ffmpeg.curts += ffmpeg.audio_buf_ptr / 2 / ffmpeg.pCodecCtx->channels;
	}
	return ffmpeg.audio_buf_ptr > 0;
}

void fetchData(unsigned char *stream, int len)
{
	int len1;
	static unsigned int audio_buf_size = ffmpeg.audio_buf_ptr;
	static unsigned int audio_buf_index = 0;

	while(len > 0) {
		if(audio_buf_index >= audio_buf_size) {
			// We have already sent all our data; get more 
			ffmpeg.audio_buf_ptr = 0;
			try {
				if(!getNextFrame()) {
					memset(stream, 0, len);
					return;
				}
			} catch (...) {
				return;
			}
			if(ffmpeg.audio_buf_ptr < 0) {
				// If error, output silence 
				memset(stream, 0, len);
				return;
			} else {
				audio_buf_size = ffmpeg.audio_buf_ptr;
			}
			audio_buf_index = 0;
			correctVolume(ffmpeg.audio_buf + audio_buf_index, ffmpeg.audio_buf + audio_buf_size, ffmpeg.curvolume);
		}
		len1 = audio_buf_size - audio_buf_index;
		if(len1 > len)
			len1 = len;
		if(ffmpeg.resampleCtx) {
			audio_resample(ffmpeg.resampleCtx, (short*)stream, (short*)((uint8_t *)ffmpeg.audio_buf + audio_buf_index), len1 / 2 / ffmpeg.pCodecCtx->channels);
		} else {
			memcpy(stream, (uint8_t *)ffmpeg.audio_buf + audio_buf_index, len1);
		}
		len -= len1;
		stream += len1;
		audio_buf_index += len1;
	}
}

//////////////
//
//  Thread
//
//////////////

void PlayThread::run()
{
	SDL_AudioSpec spec;
	ffmpeg.audio_src_format = SAMPLE_FMT_S16;
	if(SDL_OpenAudio(&ffmpeg.sdl_spec, &spec) < 0) {
		ffmpeg.error = QString("SDL_OpenAudio: ")+ SDL_GetError();
		return;
	}
	while(!ffmpeg.needToStop) {
		if(ffmpeg.pause && SDL_GetAudioStatus() != SDL_AUDIO_PAUSED) {
			SDL_PauseAudio(1);
		}
		if(!ffmpeg.pause && SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
			SDL_PauseAudio(0);
		}
		if(ffmpeg.seekTo != .0f) {
			int64_t ts;
			if(ffmpeg.stopts) {
				ts = ffmpeg.seekTo * (ffmpeg.stopts - ffmpeg.startts) + ffmpeg.startts;
			} else {
				ts = ffmpeg.seekTo / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den * ffmpeg.pFormatCtx->duration / AV_TIME_BASE;
			}
			int flags = AVSEEK_FLAG_ANY;
			ffmpeg.curts = ts;
			if(ffmpeg.curts >= ts) flags |= AVSEEK_FLAG_BACKWARD;
			if(ffmpeg.byteSeek) {
				flags |= AVSEEK_FLAG_BYTE;
				if(ffmpeg.pFormatCtx->bit_rate)
					ts = ts * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den * 60 / ffmpeg.pFormatCtx->bit_rate / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num;
				else {
					qDebug("ffmpeg.pFormatCtx->bit_rate is null, multiply by %f", (float)ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / 180000 / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num);
					ts = ts * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / 180000 / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num;
					//ts *= 3;
				}
			}
			if(ffmpeg.curts >= ts) flags |= AVSEEK_FLAG_BACKWARD;
			bool result = av_seek_frame(ffmpeg.pFormatCtx, ffmpeg.audioStream, ts, flags) >= 0;
			ffmpeg.seekTo = .0f;
			ffmpeg.packetQueue.clear();
		}
        // Read the next packet, skipping all packets that aren't for this
        // stream
		bool eofstream = false;
		while (ffmpeg.packetQueue.size() < QUEUESIZE && !eofstream) {
			AVPacket packet;
			av_init_packet(&packet);
			do {
				// Free old packet
				if(packet.data!=NULL)
					av_free_packet(&packet);
				// Read new packet
				if(av_read_frame(ffmpeg.pFormatCtx, &packet)<0) {
					if(packet.data!=NULL)
						av_free_packet(&packet);
					eofstream = true;
				}
			} while(packet.stream_index!= ffmpeg.audioStream && !eofstream);
			if(!eofstream) {
				AVPacket p2;
				av_init_packet(&p2);
				p2.size = packet.size;
				p2.pts = packet.pts;
				p2.data = (uint8_t*)malloc(p2.size);
				memcpy(p2.data, packet.data, p2.size);
				ffmpeg.packetQueue.enqueue(p2);
			}
			av_free_packet(&packet);
		}
		if(eofstream) ffmpeg.needToStop = true;
		SDL_Delay(100);
	}
	SDL_LockAudio();
	SDL_PauseAudio(1);
	while(SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {}
	//SDL_Delay(1000);
	SDL_CloseAudio();
	SDL_UnlockAudio();
}

//////////////////
//
//  PlayerFfmpeg
//
//////////////////

PlayerFfmpeg::PlayerFfmpeg() : inited(false), opened(false), threadId(0)
{
	ffmpeg.pFormatCtx = 0;
	ffmpeg.pCodecCtx = 0;
	ffmpeg.pFrame = 0;
	ffmpeg.audioStream = -1;
	ffmpeg.needToStop = false;
	ffmpeg.curvolume = 1.f;
	ffmpeg.byteSeek = false;

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
	QString filename = ToLocalFile(fname);
	if(!filename.size()) {
		filename = fname.toString();
	}

	if(fname.toString().right(4).toLower() == "flac") ffmpeg.byteSeek = true;
	else ffmpeg.byteSeek = false;

	if(av_open_input_file(&ffmpeg.pFormatCtx, filename.toLocal8Bit(), NULL, 0, NULL)!=0) {
		processErrorMessage("FFmpeg: Couldn't open file "+ filename);
		return false;
	}
	// Retrieve stream information
	if(av_find_stream_info(ffmpeg.pFormatCtx)<0) {
		processErrorMessage("FFmpeg: Couldn't find stream information in "+filename);
		return false;
	}

	// Find the first audio stream
	ffmpeg.audioStream=-1;
	for(int i=0; i<ffmpeg.pFormatCtx->nb_streams; i++)
		if(ffmpeg.pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
			{
				ffmpeg.audioStream=i;
				break;
			}

	if(ffmpeg.audioStream==-1) {
		processErrorMessage("FFmpeg: Didn't find audio stream in "+filename);
		return false;
	}

	// Get a pointer to the codec context for the video stream
	ffmpeg.pCodecCtx=ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->codec;

	AVCodec *pCodec;

	// Find the decoder for the audio stream
	pCodec=avcodec_find_decoder(ffmpeg.pCodecCtx->codec_id);
	if(pCodec==NULL) {
		processErrorMessage("FFmpeg: Codec not found for "+filename);
		return false;
	}

	// Inform the codec that we can handle truncated bitstreams -- i.e.,
	// bitstreams where frame boundaries can fall in the middle of packets
	if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
		ffmpeg.pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

	// Open codec
	if(avcodec_open(ffmpeg.pCodecCtx, pCodec)<0) {
		processErrorMessage("FFmpeg: Could not open codec for "+filename);
		return false;
	}

	ffmpeg.pFrame=avcodec_alloc_frame();

	SDL_AudioSpec wanted_spec;
	// set up SDL_audio
	wanted_spec.freq = ffmpeg.pCodecCtx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = ffmpeg.pCodecCtx->channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
	wanted_spec.callback = audio_callback;
	wanted_spec.userdata = ffmpeg.pCodecCtx;
	ffmpeg.sdl_spec = wanted_spec;

	opened = true;
	ffmpeg.audio_buf_ptr = 0;
	ffmpeg.curts = 0;
	ffmpeg.startts = start * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num / 75;
	ffmpeg.stopts = double(length + start) * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num / 75;
	if(ffmpeg.stopts > ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->duration && ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->duration > 0) 
		ffmpeg.stopts = ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->duration;
	int64_t ts = ffmpeg.startts;
	int flags = AVSEEK_FLAG_ANY;
	if(ffmpeg.byteSeek) {
		flags |= AVSEEK_FLAG_BYTE;
		//ts *= 3;
		if(ffmpeg.pFormatCtx->bit_rate)
			ts = ts * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den * 60 / ffmpeg.pFormatCtx->bit_rate / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num;
		else {
			qDebug("ffmpeg.pFormatCtx->bit_rate is null, multiply by %f", (float)ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / 180000 / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num);
			ts = ts * ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / 180000 / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num;
		}
	}
	bool result = !ffmpeg.startts || av_seek_frame(ffmpeg.pFormatCtx, ffmpeg.audioStream, ts, flags) >= 0;
	ffmpeg.curts = ffmpeg.startts;

	ffmpeg.pause = true;
    threadId = new PlayThread();
	threadId->start();

	getNextFrame(true);
	
	return true;
}

bool PlayerFfmpeg::play()
{
	ffmpeg.pause = false;
    return true;
}

bool PlayerFfmpeg::stop()
{
	close();
    return true;
}

bool PlayerFfmpeg::setPause(bool p)
{
	ffmpeg.pause = p;
	if(ffmpeg.pFormatCtx) {
		if(p) av_read_pause(ffmpeg.pFormatCtx);
		else av_read_play(ffmpeg.pFormatCtx);
	}
    return true;
}

bool PlayerFfmpeg::close()
{
	if(opened) {
		ffmpeg.needToStop = true;
		threadId->wait();
		ffmpeg.needToStop = false;
	} 
	// Free the frame
	if(ffmpeg.pFrame) {
		av_free(ffmpeg.pFrame);
		ffmpeg.pFrame = 0;
	}
	// Close the codec
	if(ffmpeg.pCodecCtx) {
		avcodec_close(ffmpeg.pCodecCtx);
		ffmpeg.pCodecCtx = 0;
	}
	// Close the video file
	if(ffmpeg.pFormatCtx) {
		av_close_input_file(ffmpeg.pFormatCtx);
		ffmpeg.pFormatCtx = 0;
	}
	if(ffmpeg.resampleCtx) {
		audio_resample_close(ffmpeg.resampleCtx);
		ffmpeg.resampleCtx = 0;
	}
	opened = false;
	ffmpeg.audio_buf_ptr = 0;
    return true;
}

bool PlayerFfmpeg::setPosition(double pos)
{
	ffmpeg.seekTo = pos;
	return true;
}

double PlayerFfmpeg::getPosition()
{
	if(ffmpeg.stopts) {
		return (double)(ffmpeg.curts - ffmpeg.startts) / (ffmpeg.stopts - ffmpeg.startts);
	}
	return (double)ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num*ffmpeg.curts / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / ffmpeg.pFormatCtx->duration * AV_TIME_BASE;
}

int  PlayerFfmpeg::volume()
{
	return ffmpeg.curvolume * 100.f;
}

void PlayerFfmpeg::setVolume(int v)
{
	ffmpeg.curvolume = (float)v * 0.01f;
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

void PlayerFfmpeg::timeSlot()
{
	if(ffmpeg.error.size()) {
		processErrorMessage(QString("FFmpeg: ")+ffmpeg.error);
		ffmpeg.error.clear();
	}
	
	if(ffmpeg.needToStop && threadId && threadId->isFinished()) {
		//stop();
		emit finish();
		ffmpeg.needToStop = false;
	}
	if(opened) {
		if(SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {
			if(ffmpeg.stopts > 0) {
				emit position( (double)(ffmpeg.curts - ffmpeg.startts) / (ffmpeg.stopts - ffmpeg.startts) );
			} else {
				emit position((double)ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.num*ffmpeg.curts / ffmpeg.pFormatCtx->streams[ffmpeg.audioStream]->time_base.den / ffmpeg.pFormatCtx->duration * AV_TIME_BASE);
			}
		}
	}
}

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

#ifndef PLAYER_FFMPEG_H
#define PLAYER_FFMPEG_H

#include <QtCore>
#include "player.h"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

class PlayerFfmpeg : public Player
{
    Q_OBJECT
	Q_INTERFACES(Player) 
 public:
    PlayerFfmpeg();
    ~PlayerFfmpeg();

	virtual bool prepare();
	virtual bool ready();

    virtual bool open(QUrl fname, long start = 0, long length = 0);
    virtual bool play();
    virtual bool stop();
    virtual bool setPause(bool p);
    virtual bool close();
    virtual bool setPosition(double pos);
    virtual double getPosition();
    virtual int  volume();
    virtual void setVolume(int v);
    virtual bool playing();
	virtual int  weight();	
	virtual QString name();

	void fetchData(unsigned char *stream, int len);

 protected:
	bool inited, opened;
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVFrame *pFrame;
	int audioStream;
	static uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	int audio_buf_ptr;

	bool getNextFrame();
};


#endif // PLAYER_VOID_H

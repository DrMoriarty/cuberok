/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef PLAYER_GST_H
#define PLAYER_GST_H

#include <QtCore>
#include "player.h"
#define GST_DISABLE_LOADSAVE 1
#define GST_DISABLE_REGISTRY 1
#include <gst/gst.h>

class PlayerGst : public Player
{
    Q_OBJECT
	Q_INTERFACES(Player) 
 public:
    PlayerGst();
    ~PlayerGst();

	virtual bool prepare();
	virtual bool ready();

	virtual bool canOpen(QString mime);
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

	void need_finish();
	void newpad (GstElement *decodebin, GstPad *pad, gboolean last, gpointer data);

 private slots:
    void timerUpdate();

 private:
	GstElement *pipeline;
	GstBus *bus;
	bool paused;
    QTimer *timer;
	gint64 Gstart, Glength;
	int link;
	bool usePlaybin;

	void setLink(int, QUrl&);
	void cleanup();
};


#endif // PLAYER_GST_H

/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "player_gst.h"
#define TIME 200

PlayerGst * gstplayer = 0;

static void gst_finish(GstElement* object, gpointer userdata)
{
	if(gstplayer) gstplayer->need_finish();
}

PlayerGst::PlayerGst() : player(0), paused(false), playflag(false)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	gstplayer = this;
}

PlayerGst::~PlayerGst()
{
    delete timer;
	gst_object_unref(G_OBJECT(player));
}

bool PlayerGst::prepare()
{
	//int argc = 0;
	//char *arg1 = "";
	//char **argv = &arg1;
	//gst_init (&argc, &argv);
	gst_init (0, 0);
// 	GstElementFactory *	fact = gst_element_factory_find("playbin");
// 	if(fact)
// 		player = gst_element_factory_create (fact, "player");
	player = gst_element_factory_make ("playbin2", "player");
	if(player)
		g_signal_connect(player, "about-to-finish", G_CALLBACK(gst_finish), NULL);
	else
		player = gst_element_factory_make ("playbin", "player");

	return player;
}

bool PlayerGst::ready()
{
	return player;
}

bool PlayerGst::open(QUrl fname)
{
	g_object_set (player, "uri", (const char*)fname.toString().toLocal8Bit(), NULL);
    return true;
}

bool PlayerGst::play()
{
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_PLAYING);
	timer->start(TIME);
	playflag = true;
    return true;
}

bool PlayerGst::stop()
{
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	timer->stop();
	playflag = false;
    return true;
}

bool PlayerGst::setPause(bool p)
{
    if(p && playing()) {
		timer->stop();
		gst_element_set_state (GST_ELEMENT (player), GST_STATE_PAUSED);
		paused = true;
		return true;
    }
    if(!p && paused) {
		timer->start(TIME);
		gst_element_set_state (GST_ELEMENT (player), GST_STATE_PLAYING);
		paused = false;
		return true;
    }
    return false;
}

bool PlayerGst::close()
{
	timer->stop();
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_NULL);
	playflag = false;
    return true;
}

bool PlayerGst::setPosition(double pos)
{
	gint64 time;
	GstFormat fmt = GST_FORMAT_TIME;
	gst_element_query_duration(player, &fmt, &time);
	time = pos * time;
    return gst_element_seek(player, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, time, GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
}

double PlayerGst::getPosition()
{
    if(playing()) {
		gint64 p, l;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(player, &fmt, &p);
		gst_element_query_duration(player, &fmt, &l);
		return (double)p/l;
	}
	return 0.0;
}

int  PlayerGst::volume()
{
	gdouble vol;
	g_object_get (G_OBJECT(player), "volume", &vol, NULL);
	return vol * 10;
}

void PlayerGst::setVolume(int v)
{
	gdouble vol = 0.01 * v;
	g_object_set (G_OBJECT(player), "volume", vol, NULL);
}

bool PlayerGst::playing()
{
	GstState st;
    gst_element_get_state (GST_ELEMENT (player), &st, 0, 0);
	return st == GST_STATE_PLAYING;
}

int PlayerGst::weight()
{
	return 30;
}

QString PlayerGst::name()
{
	return "GStreamer";
}

void PlayerGst::timerUpdate()
{
    if(playing()) {
		gint64 p, l;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(player, &fmt, &p);
		gst_element_query_duration(player, &fmt, &l);
		emit position((double)p/l);
    } else if(playflag) {
// 		timer->stop();
// 		playflag = false;
// 		emit finish();
    }
}

void PlayerGst::need_finish()
{
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	emit finish();
}

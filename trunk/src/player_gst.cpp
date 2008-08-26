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

#include <QtGui>

PlayerGst * gstplayer = 0;

#define sync_set_state(element, state) 	{ GstStateChangeReturn res; \
	res = gst_element_set_state (GST_ELEMENT (element), state); \
	if(res == GST_STATE_CHANGE_FAILURE) return false; \
	if(res == GST_STATE_CHANGE_ASYNC) { \
		GstState state; \
		do { \
			res = gst_element_get_state(GST_ELEMENT (element), &state, NULL, 1000000000/*GST_CLOCK_TIME_NONE*/); \
			if(res == GST_STATE_CHANGE_FAILURE) return false;			\
		} while(res == GST_STATE_CHANGE_ASYNC); \
	} }

#define sync_set_state2(element, state) 	{ GstStateChangeReturn res; \
	res = gst_element_set_state (GST_ELEMENT (element), state); \
	if(res == GST_STATE_CHANGE_FAILURE) return; \
	if(res == GST_STATE_CHANGE_ASYNC) { \
		GstState state; \
		do { \
			res = gst_element_get_state(GST_ELEMENT (element), &state, NULL, 1000000000/*GST_CLOCK_TIME_NONE*/); \
			if(res == GST_STATE_CHANGE_FAILURE) return; \
		} while(res == GST_STATE_CHANGE_ASYNC); \
	} }


static void gst_finish(GstElement* object, gpointer userdata)
{
	if(gstplayer) gstplayer->need_finish();
}

PlayerGst::PlayerGst() : player(0), paused(false), playflag(false), needseektoavoidgstbug(false)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	gstplayer = this;
}

PlayerGst::~PlayerGst()
{
    delete timer;
	if(player) gst_object_unref(G_OBJECT(player));
	gst_deinit();
}

bool PlayerGst::prepare()
{
	gst_init (0, 0);
// 	GstElementFactory *	fact = gst_element_factory_find("playbin");
// 	if(fact)
// 		player = gst_element_factory_create (fact, "player");
	player = gst_element_factory_make ("playbin2", "player");
	if(player) g_signal_connect(player, "about-to-finish", G_CALLBACK(gst_finish), NULL);
	else player = gst_element_factory_make ("playbin", "player");
	//sync_set_state(player, GST_STATE_NULL);
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_NULL);

	return player;
}

bool PlayerGst::ready()
{
	return player;
}

bool PlayerGst::open(QUrl fname, long start, long length)
{
	g_object_set (player, "uri", (const char*)fname.toString().toLocal8Bit(), NULL);
	gst_element_set_state (GST_ELEMENT (player), GST_STATE_PAUSED);
	//sync_set_state(player, GST_STATE_PAUSED);
// 	GstStateChangeReturn res;
// 	res = gst_element_set_state (GST_ELEMENT (player), GST_STATE_PAUSED);
// 	if(res == GST_STATE_CHANGE_FAILURE) return false;
// 	if(res == GST_STATE_CHANGE_ASYNC) {
// 		GstState state;
// 		do {
// 			res = gst_element_get_state(GST_ELEMENT (player), &state, NULL, GST_CLOCK_TIME_NONE);
// 			if(res == GST_STATE_CHANGE_FAILURE) return false;
// 		} while(res == GST_STATE_CHANGE_ASYNC);
// 	}
	Gstart = start;
	Gstart *= 1000000000 / 75;
	Glength = length;
	Glength *= 1000000000 / 75;
	gint64 all=0;
	GstFormat fmt = GST_FORMAT_TIME;
	while(!gst_element_query_duration(player, &fmt, &all)) {}  // don't do that again, bad boy
	if(!Glength) {
		Glength = all - Gstart;
	}
	//QMessageBox::information(0, "", QString("start = %1, length = %2, stream = %3").arg(QString::number((qlonglong)Gstart), QString::number((qlonglong)Glength), QString::number((qlonglong)all)));
    return true;
}

bool PlayerGst::play()
{
	gst_element_seek(player, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, Gstart, GST_SEEK_TYPE_SET, Gstart + Glength);
	sync_set_state(player, GST_STATE_PLAYING);
// 	if(gst_element_set_state (GST_ELEMENT (player), GST_STATE_PLAYING) == GST_STATE_CHANGE_ASYNC) {
// 		GstState state;
// 		while(gst_element_get_state(GST_ELEMENT (player), &state, NULL, GST_CLOCK_TIME_NONE) == GST_STATE_CHANGE_ASYNC) {}
// 	}
	timer->start(TIME);
	playflag = true;
	//needseektoavoidgstbug = true;
    return true;
}

bool PlayerGst::stop()
{
	sync_set_state(player, GST_STATE_READY);
	//gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	timer->stop();
	playflag = false;
    return true;
}

bool PlayerGst::setPause(bool p)
{
    if(p && playing()) {
		timer->stop();
		sync_set_state(player, GST_STATE_PAUSED);
		//gst_element_set_state (GST_ELEMENT (player), GST_STATE_PAUSED);
		paused = true;
		return true;
    }
    if(!p && paused) {
		timer->start(TIME);
		sync_set_state(player, GST_STATE_PLAYING);
		//gst_element_set_state (GST_ELEMENT (player), GST_STATE_PLAYING);
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
	time = Glength;
	time *= pos;
	time += Gstart;
    return gst_element_seek(player, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, time, GST_SEEK_TYPE_SET, Gstart + Glength);
}

double PlayerGst::getPosition()
{
    if(playing()) {
		gint64 p;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(player, &fmt, &p);
		p -= Gstart;
		p *= 100;
		p /= Glength;
		return (double)p/100;
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
		gint64 p;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(player, &fmt, &p);
		emit position((double)(p - Gstart) / Glength);
		if(needseektoavoidgstbug) {
			setPosition(0.0f);
			needseektoavoidgstbug = false;
		}
    } else if(playflag) {
// 		timer->stop();
// 		playflag = false;
// 		emit finish();
    }
}

void PlayerGst::need_finish()
{
	timer->stop();
	sync_set_state2(player, GST_STATE_NULL);
	//gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	emit finish();
}

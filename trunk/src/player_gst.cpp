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
			res = gst_element_get_state(GST_ELEMENT (element), &state, NULL, 1000000000/*GST_CLOCK_TIME_NONE*/); \
			if(res == GST_STATE_CHANGE_FAILURE || res == GST_STATE_CHANGE_ASYNC) return false;			\
	} }

#define sync_set_state2(element, state) 	{ GstStateChangeReturn res; \
	res = gst_element_set_state (GST_ELEMENT (element), state); \
	if(res == GST_STATE_CHANGE_FAILURE) return; \
	if(res == GST_STATE_CHANGE_ASYNC) { \
		GstState state; \
			res = gst_element_get_state(GST_ELEMENT (element), &state, NULL, 1000000000/*GST_CLOCK_TIME_NONE*/); \
			if(res == GST_STATE_CHANGE_FAILURE || res == GST_STATE_CHANGE_ASYNC) return; \
	} }


// static void gst_finish(GstElement* object, gpointer userdata)
// {
// 	if(gstplayer) gstplayer->need_finish();
// }

static void 
cb_newpad (GstElement *decodebin,
		   GstPad     *pad,
		   gboolean    last,
		   gpointer    data)
{
	if(gstplayer) gstplayer->newpad(decodebin, pad, last, data);
}

void PlayerGst::newpad (GstElement *decodebin,
		   GstPad     *pad,
		   gboolean    last,
		   gpointer    data)
{
	GstCaps *caps;
	GstStructure *str;
	GstPad *audiopad;
	
	/* only link once */
	GstElement *audio = gst_bin_get_by_name(GST_BIN(pipeline), "audiobin");
	audiopad = gst_element_get_static_pad (audio, "sink");
	gst_object_unref(audio);
	if (GST_PAD_IS_LINKED (audiopad)) {
		g_object_unref (audiopad);
		return;
	}
	
	/* check media type */
	caps = gst_pad_get_caps (pad);
	str = gst_caps_get_structure (caps, 0);
	if (!g_strrstr (gst_structure_get_name (str), "audio")) {
		gst_caps_unref (caps);
		gst_object_unref (audiopad);
		return;
	}
	gst_caps_unref (caps);
	
	/* link'n'play */
	gst_pad_link (pad, audiopad);
}

PlayerGst::PlayerGst() : pipeline(0), bus(0), paused(false), Gstart(0), Glength(0), link(0)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	gstplayer = this;
}

PlayerGst::~PlayerGst()
{
    delete timer;
	if(pipeline) sync_set_state2 (GST_ELEMENT (pipeline), GST_STATE_NULL);
	if(bus) gst_object_unref (bus);
	if(pipeline) gst_object_unref(G_OBJECT(pipeline));
	gst_deinit();
}

bool PlayerGst::prepare()
{
	GstElement *dec, *conv, *sink, *audio;
	GstPad *audiopad;
	gst_init (0, 0);
	pipeline = gst_pipeline_new ("pipeline");
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

	dec = gst_element_factory_make ("decodebin", "decoder");
	g_signal_connect (dec, "new-decoded-pad", G_CALLBACK (cb_newpad), NULL);
	gst_bin_add (GST_BIN (pipeline), dec);

	audio = gst_bin_new ("audiobin");
	conv = gst_element_factory_make ("audioconvert", "aconv");
	audiopad = gst_element_get_static_pad (conv, "sink");
	sink = gst_element_factory_make ("autoaudiosink", "sink");
	gst_bin_add_many (GST_BIN (audio), conv, sink, NULL);
	gst_element_link (conv, sink);
	gst_element_add_pad (audio, gst_ghost_pad_new ("sink", audiopad));
	gst_object_unref (audiopad);
	gst_bin_add (GST_BIN (pipeline), audio);

	GstElement *l_src, *http_src;
	l_src = gst_element_factory_make ("filesrc", "localsrc");
	http_src = gst_element_factory_make("neonhttpsrc", "httpsrc");
	gst_bin_add_many (GST_BIN (pipeline), l_src, http_src, NULL);
	gst_element_set_state (l_src, GST_STATE_NULL);
	gst_element_set_locked_state (l_src, TRUE);
	gst_element_set_state (http_src, GST_STATE_NULL);
	gst_element_set_locked_state (http_src, TRUE);
	//gst_element_link (src, dec);

// 	player = gst_element_factory_make ("playbin2", "player");
// 	if(player) g_signal_connect(player, "about-to-finish", G_CALLBACK(gst_finish), NULL);
// 	else player = gst_element_factory_make ("playbin", "player");
 	//sync_set_state(player, GST_STATE_NULL);
// 	gst_element_set_state (GST_ELEMENT (player), GST_STATE_NULL);

	return pipeline;
}

bool PlayerGst::ready()
{
	return pipeline;
}

void PlayerGst::setLink(int l, QUrl &url)
{
	GstElement *dec = gst_bin_get_by_name(GST_BIN(pipeline), "decoder");
	GstElement *l_src = gst_bin_get_by_name(GST_BIN(pipeline), "localsrc");
	GstElement *http_src = gst_bin_get_by_name(GST_BIN(pipeline), "httpsrc");
	if(l != link) {
		switch(link) {
		case 2: // http
			gst_element_unlink (http_src, dec);
			gst_element_set_state (http_src, GST_STATE_NULL);
			gst_element_set_locked_state (http_src, TRUE);
			break;
		case 1: // file
			gst_element_unlink (l_src, dec);
			gst_element_set_state (l_src, GST_STATE_NULL);
			gst_element_set_locked_state (l_src, TRUE);
			break;
		case 0:
		default:
			{}
		}
		switch(l) {
		case 2: // http
			//g_object_set (G_OBJECT (http_src), "location", (const char*)url.toString().toLocal8Bit(), NULL);
			gst_element_link (http_src, dec);
			gst_element_set_locked_state (http_src, FALSE);
			break;
		case 1: // file
			//g_object_set (G_OBJECT (l_src), "location", (const char*)url.toLocalFile().toLocal8Bit(), NULL);
			gst_element_link (l_src, dec);
			gst_element_set_locked_state (l_src, FALSE);
			break;
		case 0:
		default:
			{}
		}
		link = l;
	}
	switch(link) {
	case 2: // http
		g_object_set (G_OBJECT (http_src), "location", (const char*)url.toString().toLocal8Bit(), NULL);
		break;
	case 1: // file
		g_object_set (G_OBJECT (l_src), "location", (const char*)url.toLocalFile().toLocal8Bit(), NULL);
		break;
	case 0:
	default:
		{}
	}
	gst_object_unref(l_src);
	gst_object_unref(http_src);
	gst_object_unref(dec);
}

bool PlayerGst::open(QUrl fname, long start, long length)
{
	sync_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
	if(fname.toString().toLower().startsWith("file://")/*fname.toLocalFile().size()*/) {
		//g_object_set (G_OBJECT (l_src), "location", (const char*)fname.toLocalFile().toLocal8Bit(), NULL);
		setLink(1, fname);
	} else if(fname.toString().toLower().startsWith("http://")) {
		//g_object_set (G_OBJECT (http_src), "location", (const char*)fname.toString().toLocal8Bit(), NULL);
		setLink(2, fname);
	} else if(fname.toString().toLower().startsWith("mms://")) {
		QMessageBox::warning(0, "Error", "The mms protocol not supported now");
		return false;
	}

	//g_object_set (player, "uri", (const char*)fname.toString().toLocal8Bit(), NULL);
	sync_set_state (GST_ELEMENT (pipeline), GST_STATE_PAUSED);
	Gstart = start;
	Gstart *= 1000000000 / 75;
	Glength = length;
	Glength *= 1000000000 / 75;
	gint64 all=0;
	GstFormat fmt = GST_FORMAT_TIME;
	//while(!gst_element_query_duration(pipeline, &fmt, &all)) {}  // don't do that again, bad boy
	if(gst_element_query_duration(pipeline, &fmt, &all)) { 
		if(!Glength)
			Glength = all - Gstart;
	} else {
		Gstart = Glength = 0;
	}
	//QMessageBox::information(0, "", QString("start = %1, length = %2, stream = %3").arg(QString::number((qlonglong)Gstart), QString::number((qlonglong)Glength), QString::number((qlonglong)all)));
    return true;
}

bool PlayerGst::play()
{
	if(Glength) gst_element_seek(pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, Gstart, GST_SEEK_TYPE_SET, Gstart + Glength);
	//sync_set_state(player, GST_STATE_PLAYING);
	gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);
	timer->start(TIME);
    return true;
}

bool PlayerGst::stop()
{
	//sync_set_state(player, GST_STATE_READY);
	gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_READY);
	timer->stop();
    return true;
}

bool PlayerGst::setPause(bool p)
{
    if(p && playing()) {
		timer->stop();
		//sync_set_state(player, GST_STATE_PAUSED);
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PAUSED);
		paused = true;
		return true;
    }
    if(!p && paused) {
		timer->start(TIME);
		//sync_set_state(player, GST_STATE_PLAYING);
		gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);
		paused = false;
		return true;
    }
    return false;
}

bool PlayerGst::close()
{
	timer->stop();
	gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
    return true;
}

bool PlayerGst::setPosition(double pos)
{
	gint64 time;
	if(Glength) {
		time = Glength;
		time *= pos;
		time += Gstart;
		return gst_element_seek(pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, time, GST_SEEK_TYPE_SET, Gstart + Glength);
	}
	return false;
}

double PlayerGst::getPosition()
{
    if(/*playing() &&*/ Glength) {
		gint64 p;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(pipeline, &fmt, &p);
		p -= Gstart;
		p *= 100;
		p /= Glength;
		return (double)p/100;
	}
	return 0.0;
}

int  PlayerGst::volume()
{
	gdouble vol = 0;
	//g_object_get (G_OBJECT(p), "volume", &vol, NULL);
	return vol * 10;
}

void PlayerGst::setVolume(int v)
{
	gdouble vol = 0.01 * v;
	//g_object_set (G_OBJECT(player), "volume", vol, NULL);
}

bool PlayerGst::playing()
{
	GstState st;
    gst_element_get_state (GST_ELEMENT (pipeline), &st, 0, 0);
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
	GstMessage* message;
	while(message = gst_bus_pop(bus), message) {
		switch (GST_MESSAGE_TYPE (message)) {
		case GST_MESSAGE_ERROR: {
			GError *err;
			gchar *debug;
			gst_message_parse_error (message, &err, &debug);
			QMessageBox::warning(0, "Gstreamer error", "Error #"+QString::number(err->code)+" in module "+QString::number(err->domain)+"\n"+err->message);
			g_error_free (err);
			g_free (debug);
			break;
		}
		case GST_MESSAGE_EOS:
			need_finish();
			return;
		default:
			break;
		}
	}
    if(playing()) {
		gint64 p;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(pipeline, &fmt, &p);
		emit position((double)(p - Gstart) / Glength);
    }
}

void PlayerGst::need_finish()
{
	timer->stop();
	sync_set_state2(pipeline, GST_STATE_NULL);
	//gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	emit finish();
}

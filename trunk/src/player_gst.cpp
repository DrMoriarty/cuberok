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

#include "player_gst.h"
#include "playlistsettings.h"
//#define ToLocalFile(url) url.toString().toLocal8Bit().mid(8)

#define TIME 200

#define canUsePlaybin false

#include <QtGui>

Q_EXPORT_PLUGIN2(player_gst, PlayerGst) 

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


static void gst_finish(GstElement* object, gpointer userdata)
{
	if(gstplayer) gstplayer->need_finish();
}

static void cb_newpad (GstElement *decodebin,
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

PlayerGst::PlayerGst() : pipeline(0), bus(0), paused(false), Gstart(0), Glength(0), link(0), usePlaybin(false)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	gstplayer = this;
	gst_init (0, 0);
}

PlayerGst::~PlayerGst()
{
    delete timer;
	cleanup();
	gst_deinit();
}

void PlayerGst::cleanup()
{
	if(pipeline) sync_set_state2 (GST_ELEMENT (pipeline), GST_STATE_NULL);
	if(bus) gst_object_unref (bus);
	if(pipeline) gst_object_unref(G_OBJECT(pipeline));
}

bool PlayerGst::prepare()
{
	GstElement *dec, *conv, *sink, *audio, *vol, *playbin;
	GstPad *audiopad;
	pipeline = gst_pipeline_new ("pipeline");
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

	dec = gst_element_factory_make ("decodebin", "decoder");
	g_signal_connect (dec, "new-decoded-pad", G_CALLBACK (cb_newpad), NULL);
	gst_bin_add (GST_BIN (pipeline), dec);

	audio = gst_bin_new ("audiobin");
	conv = gst_element_factory_make ("audioconvert", "aconv");
	audiopad = gst_element_get_static_pad (conv, "sink");
	vol = gst_element_factory_make ("volume", "volume");
	sink = gst_element_factory_make ("autoaudiosink", "sink");
	gst_bin_add_many (GST_BIN (audio), conv, vol, sink, NULL);
	gst_element_link (conv, vol);
	gst_element_link (vol, sink);
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

	if(canUsePlaybin) {
		playbin = gst_element_factory_make ("playbin2", "player");
		if(playbin) g_signal_connect(playbin, "about-to-finish", G_CALLBACK(gst_finish), NULL);
		else playbin = gst_element_factory_make ("playbin", "player");
		gst_bin_add (GST_BIN (pipeline), playbin);
		//g_object_set (G_OBJECT(playbin), "audio-sink", audio, NULL);
		gst_element_set_state (playbin, GST_STATE_NULL);
		gst_element_set_locked_state (playbin, TRUE);
 	//sync_set_state(player, GST_STATE_NULL);
// 	gst_element_set_state (GST_ELEMENT (player), GST_STATE_NULL);
	}

	return pipeline;
}

bool PlayerGst::ready()
{
	return pipeline;
}

void PlayerGst::setLink(int l, QUrl &url)
{
	GstElement *audio = gst_bin_get_by_name(GST_BIN(pipeline), "audiobin");
	GstElement *dec = gst_bin_get_by_name(GST_BIN(pipeline), "decoder");
	GstElement *l_src = gst_bin_get_by_name(GST_BIN(pipeline), "localsrc");
	GstElement *http_src = gst_bin_get_by_name(GST_BIN(pipeline), "httpsrc");
	GstElement *playbin;
	if(canUsePlaybin) playbin = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");

	if(l != link) {
		switch(link) {
		case 2: // http
			gst_element_unlink (http_src, dec);
			gst_element_set_state (http_src, GST_STATE_NULL);
			gst_element_set_locked_state (http_src, TRUE);
			break;
		case 1: // file
			if(canUsePlaybin) {
				gst_element_set_state(playbin, GST_STATE_NULL);
				gst_element_set_locked_state(playbin, TRUE);
				usePlaybin = false;
				gst_element_set_locked_state(audio, FALSE);
				gst_element_set_locked_state(dec, FALSE);
			} else {
				gst_element_unlink (l_src, dec);
				gst_element_set_state (l_src, GST_STATE_NULL);
				gst_element_set_locked_state (l_src, TRUE);
			}
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
			if(canUsePlaybin) {
				gst_element_set_locked_state(playbin, FALSE);
				usePlaybin = true;
				gst_element_set_state(audio, GST_STATE_NULL);
				gst_element_set_locked_state(audio, TRUE);
				gst_element_set_state(dec, GST_STATE_NULL);
				gst_element_set_locked_state(dec, TRUE);
			} else {
				//g_object_set (G_OBJECT (l_src), "location", (const char*)url.toLocalFile().toLocal8Bit(), NULL);
				gst_element_link (l_src, dec);
				gst_element_set_locked_state (l_src, FALSE);
			}
			break;
		case 0:
		default:
			{}
		}
		link = l;
	}
	switch(link) {
	case 2: {// http
		g_object_set (G_OBJECT (http_src), "location", (const char*)url.toEncoded(), NULL);
		QString proxy;
// 		if(PLSet.proxyEnabled) 
// 			proxy = PLSet.proxyHost + ":" + QString::number(PLSet.proxyPort);
		//g_object_set (G_OBJECT (http_src), "proxy", (const char*)proxy.toLocal8Bit(), NULL);
		break;
	}
	case 1: // file
		if(canUsePlaybin) {
			g_object_set (playbin, "uri", (const char*)ToLocalFile(url).toLocal8Bit(), NULL);
		} else {
			g_object_set (G_OBJECT (l_src), "location", (const char*)ToLocalFile(url).toLocal8Bit(), NULL);
		}
		break;
	case 0:
	default:
		{}
	}
	if(canUsePlaybin) gst_object_unref(playbin);
	gst_object_unref(l_src);
	gst_object_unref(http_src);
	gst_object_unref(dec);
	gst_object_unref(audio);
}

bool PlayerGst::canOpen(QString mime)
{
	return true;
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
	//gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PAUSED);
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
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
	if(Glength) gst_element_seek(p, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, Gstart, GST_SEEK_TYPE_SET, Gstart + Glength);
	//sync_set_state(player, GST_STATE_PLAYING);
	gst_element_set_state (GST_ELEMENT (p), GST_STATE_PLAYING);
	timer->start(TIME);
	if(usePlaybin) gst_object_unref(p);
    return true;
}

bool PlayerGst::stop()
{
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
	//sync_set_state(player, GST_STATE_READY);
	gst_element_set_state (GST_ELEMENT (p), GST_STATE_READY);
	timer->stop();
	if(usePlaybin) gst_object_unref(p);
    return true;
}

bool PlayerGst::setPause(bool pause)
{
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
    if(pause && playing()) {
		timer->stop();
		//sync_set_state(player, GST_STATE_PAUSED);
		gst_element_set_state (GST_ELEMENT (p), GST_STATE_PAUSED);
		paused = true;
		if(usePlaybin) gst_object_unref(p);
		return true;
    }
    if(!pause && paused) {
		timer->start(TIME);
		//sync_set_state(player, GST_STATE_PLAYING);
		gst_element_set_state (GST_ELEMENT (p), GST_STATE_PLAYING);
		paused = false;
		if(usePlaybin) gst_object_unref(p);
		return true;
    }
	if(usePlaybin) gst_object_unref(p);
    return false;
}

bool PlayerGst::close()
{
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
	timer->stop();
	gst_element_set_state (GST_ELEMENT (p), GST_STATE_NULL);
	if(usePlaybin) gst_object_unref(p);
    return true;
}

bool PlayerGst::setPosition(double pos)
{
	gint64 time;
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
	if(Glength) {
		time = Glength;
		time *= pos;
		time += Gstart;
		bool b = gst_element_seek(p, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, time, GST_SEEK_TYPE_SET, Gstart + Glength);
		if(usePlaybin) gst_object_unref(p);
		return b;
	}
	if(usePlaybin) gst_object_unref(p);
	return false;
}

double PlayerGst::getPosition()
{
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
    if(/*playing() &&*/ Glength) {
		gint64 pos;
		GstFormat fmt = GST_FORMAT_TIME;
		gst_element_query_position(p, &fmt, &pos);
		if(usePlaybin) gst_object_unref(p);
		pos -= Gstart;
		pos *= 100;
		pos /= Glength;
		return (double)pos/100;
	}
	if(usePlaybin) gst_object_unref(p);
	return 0.0;
}

int  PlayerGst::volume()
{
	gdouble vol = 0;
	if(usePlaybin) {
		GstElement *playbin = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
		g_object_get (G_OBJECT(playbin), "volume", &vol, NULL);
		gst_object_unref(playbin);
	} else {
		GstElement *volume = gst_bin_get_by_name(GST_BIN(pipeline), "volume");
		g_object_get (G_OBJECT(volume), "volume", &vol, NULL);
		gst_object_unref(volume);
	}
	return vol * 100;
}

void PlayerGst::setVolume(int v)
{
	gdouble vol = 0.01 * v;
	if(usePlaybin) {
		GstElement *playbin = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
		g_object_set (G_OBJECT(playbin), "volume", vol, NULL);
		gst_object_unref(playbin);
	} else {
		GstElement *volume = gst_bin_get_by_name(GST_BIN(pipeline), "volume");
		g_object_set (G_OBJECT(volume), "volume", vol, NULL);
		gst_object_unref(volume);
	}
	//g_object_set (G_OBJECT(player), "volume", vol, NULL);
}

bool PlayerGst::playing()
{
	GstState st;
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
    gst_element_get_state (GST_ELEMENT (p), &st, 0, 0);
	if(usePlaybin) gst_object_unref(p);
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
	while(!usePlaybin && (message = gst_bus_pop(bus), message)) {
		switch (GST_MESSAGE_TYPE (message)) {
		case GST_MESSAGE_ERROR: {
			GError *err;
			gchar *debug;
			gst_message_parse_error (message, &err, &debug);
			QString str;
			str = "Error #"+QString::number(err->code)+" in module "+QString::number(err->domain)+"\n"+QString::fromUtf8(err->message);
			if(err->code == 6 && err->domain == 851) {
				str += "\nMay be you should to install gstreamer0.10-plugins-ugly or gstreamer0.10-plugins-bad";
			}
			QMessageBox::warning(0, "Gstreamer error", str);
			g_error_free (err);
			g_free (debug);
			break;
		}
		case GST_MESSAGE_EOS:
			need_finish();
			//QMessageBox::information(0, "", "EOS");
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
	GstElement *p = pipeline;
	if(usePlaybin) p = gst_bin_get_by_name(GST_BIN(pipeline), "playbin");
	sync_set_state2(p, GST_STATE_NULL);
	if(usePlaybin) gst_object_unref(p);
	//gst_element_set_state (GST_ELEMENT (player), GST_STATE_READY);
	emit finish();
}

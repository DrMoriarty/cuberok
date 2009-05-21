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

#include "player_phonon.h"
//#define ToLocalFile(url) url.toString().toLocal8Bit().mid(8)

#define TIME 200

#include <QtGui>

Q_EXPORT_PLUGIN2(player_phonon, PlayerPhonon) 

PlayerPhonon::PlayerPhonon() : repeat_mode(0), shuffle_mode(0), needPos(false)
{
	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	mediaObject = new Phonon::MediaObject(this);
	metaInformationResolver = new Phonon::MediaObject(this);
	
	mediaObject->setTickInterval(1000);
	connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
	connect(mediaObject, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(stateChanged(Phonon::State, Phonon::State)));
	connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(metaStateChanged(Phonon::State, Phonon::State)));
	connect(mediaObject, SIGNAL(currentSourceChanged(const Phonon::MediaSource &)), this, SLOT(sourceChanged(const Phonon::MediaSource &)));
	connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
	connect(mediaObject, SIGNAL(finished()), this, SLOT(sourceFinished()));
	
	Phonon::createPath(mediaObject, audioOutput);

	mimeTypes["ogg"] = "application/ogg";
	mimeTypes["oga"] = "application/ogg";
	mimeTypes["tsi"] = "audio/TSP-audio";
	mimeTypes["au"] = "audio/basic";
	mimeTypes["snd"] = "audio/basic";
	mimeTypes["kar"] = "audio/midi";
	mimeTypes["mid"] = "audio/midi";
	mimeTypes["midi"] = "audio/midi";
	mimeTypes["mp2"] = "audio/mpeg";
	mimeTypes["mp3"] = "audio/mpeg";
	mimeTypes["mpga"] = "audio/mpeg";
	mimeTypes["au"] = "audio/ulaw";
	mimeTypes["aif"] = "audio/x-aiff";
	mimeTypes["aifc"] = "audio/x-aiff";
	mimeTypes["aiff"] = "audio/x-aiff";
	mimeTypes["m3u"] = "audio/x-mpegurl";
	mimeTypes["wax"] = "audio/x-ms-wax";
	mimeTypes["wma"] = "audio/x-ms-wma";
	mimeTypes["rpm"] = "audio/x-pn-realaudio-plugin";
	mimeTypes["ram"] = "audio/x-pn-realaudio";
	mimeTypes["rm"] = "audio/x-pn-realaudio";
	mimeTypes["ra"] = "audio/x-realaudio";
	mimeTypes["wav"] = "audio/x-wav";
}

PlayerPhonon::~PlayerPhonon()
{
	delete audioOutput;
	delete mediaObject;
	delete metaInformationResolver;
}

bool PlayerPhonon::prepare()
{
    return true;
}

bool PlayerPhonon::ready()
{
    return audioOutput && mediaObject && metaInformationResolver;
}

bool PlayerPhonon::open(QUrl fname, long start, long length)
{
    //QString file = ToLocalFile(fname);
	mediaObject->stop();
	mediaObject->clearQueue();

	source = Phonon::MediaSource(fname);
	metaInformationResolver->setCurrentSource(source);
	mediaObject->setCurrentSource(source);

	if(fname.toLocalFile().size()) {
		QString suffix = QFileInfo(fname.toLocalFile()).suffix().toLower();
		if(mimeTypes.find(suffix) != mimeTypes.end()) {
			QString mimetype = mimeTypes[suffix];
			if(!Phonon::BackendCapabilities::isMimeTypeAvailable(mimetype)) {
				QString message = tr("This mime type is not supported by phonon: ") + mimetype;
#ifndef WIN32
				if(mimetype == "audio/mpeg") {
					message += tr("\nDo you forget to install phonon-backend-xine or libxine1-ffmpeg?");
				} else {
					message += tr("\nDo you forget to install proper phonon backend?");
				}
#else
				message += tr("\nDo you forget to install proper phonon backend?");
#endif
				//QMessageBox::information(0, tr("Error"), message);
				processErrorMessage(message);
			}
		}
	}
		
	Pstart = start;
	Pstart *= 1000;
	Pstart /= 75;
	Plength = length;
	Plength *= 1000;
	Plength /= 75;
	if(!Plength) Plength = mediaObject->totalTime();
	
	//mediaObject->seek(Pstart);
	
    return true;
}

bool PlayerPhonon::play()
{
	mediaObject->play();
	//bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
	
	return true;
}

bool PlayerPhonon::stop()
{
	mediaObject->stop();
    return true;
}

bool PlayerPhonon::setPause(bool p)
{
	if(p) mediaObject->pause();
	else mediaObject->play();
    return true;
}

bool PlayerPhonon::close()
{
	mediaObject->stop();
	mediaObject->clearQueue();
    return true;
}

bool PlayerPhonon::setPosition(double pos)
{
	qint64 time = Plength;
	time *= pos;
	time += Pstart;
	if(mediaObject->state() == Phonon::PlayingState) {
		mediaObject->seek(time);
	} else {
		needPos = true;
		_pos = time;
	}
    return true;
}

double PlayerPhonon::getPosition()
{
	qint64 time = mediaObject->currentTime() - Pstart;
    return (double)time / Plength;
}

int  PlayerPhonon::volume()
{
    return audioOutput->volume() * 100;
}

void PlayerPhonon::setVolume(int v)
{
	audioOutput->setVolume((qreal)v / 100);
}

bool PlayerPhonon::playing()
{
    return mediaObject->state() == Phonon::PlayingState;;
}

int PlayerPhonon::weight()
{
	return 20;
}

QString PlayerPhonon::name()
{
	return "Phonon";
}

void PlayerPhonon::stateChanged(Phonon::State newState, Phonon::State oldState )
{
    switch (oldState) {
	case Phonon::LoadingState:
	    /*if(newState == Phonon::StoppedState)*/ {
		play();
	    }
	    break;
	default:
	    break;
    }
	switch (newState) {
	case Phonon::ErrorState:
		if (mediaObject->errorType() == Phonon::FatalError) {
			//QMessageBox::warning(0, tr("Fatal Error"), mediaObject->errorString());
			processErrorMessage(mediaObject->errorString());
		} else {
			//QMessageBox::warning(0, tr("Error"), mediaObject->errorString());
			processErrorMessage(mediaObject->errorString());
		}
		mediaObject->stop();
		break;
	case Phonon::PlayingState:
 		if(oldState != Phonon::PausedState)
 			mediaObject->seek(Pstart);
		if(needPos) {
			needPos = false;
			mediaObject->seek(_pos);
		}
		break;
	case Phonon::StoppedState:
		break;
	case Phonon::PausedState:
		break;
	case Phonon::BufferingState:
		break;
	default:
		;
	}
}

void PlayerPhonon::tick(qint64 time)
{
	//QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
	double pos = double(time - Pstart) / Plength;
	emit position(pos);
	if(pos >= 1.0) {
		mediaObject->stop();
		emit finish();
	}
}

void PlayerPhonon::sourceChanged(const Phonon::MediaSource &source)
{
}

void PlayerPhonon::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
	if (newState == Phonon::ErrorState) {
		//QMessageBox::warning(0, tr("Error opening files"), metaInformationResolver->errorString());
		processErrorMessage(metaInformationResolver->errorString());
		mediaObject->stop();
		return;
	}
	
	if (newState != Phonon::StoppedState && newState != Phonon::PausedState)
		return;
	
	if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
		return;
	
	QMap<QString, QString> metaData = metaInformationResolver->metaData();
	
	QString title = metaData.value("TITLE");
	if (title == "")
		title = metaInformationResolver->currentSource().fileName();
	
	QTableWidgetItem *titleItem = new QTableWidgetItem(title);
	titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
	QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
	artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
	QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
	albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
	QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));
	yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);
	
}

void PlayerPhonon::aboutToFinish()
{
	//mediaObject->stop();
    //emit finish();
}

void PlayerPhonon::sourceFinished()
{
	mediaObject->stop();
	emit finish();
}

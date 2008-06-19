#include "playerthread.h"
#include "main.h"

using namespace audiere;

PlayerThread::PlayerThread(int *fd, QString fname, QMutex &mp, QObject *parent)
    : QThread(parent), fdescr(fd), tags(true)
{
	file = fname;
	mutexPause = &mp;
}

PlayerThread::~PlayerThread()
{
	*fdescr = 0;
}

void PlayerThread::run()
{
	//if(mpg) run_mpg123();
	//else run_audiere();
}

void PlayerThread::seek(double pos)
{
	
}

void PlayerThread::prepareTags()
{
	emit tagready(
			prepareTag("FIXME"/*mpg::id3.title.p*/)/*,
			prepareTag(mpg::id3.artist.p),
			prepareTag(mpg::id3.album.p),
			prepareTag(mpg::id3.year.p),
			prepareTag(mpg::id3.genre.p),
			prepareTag(mpg::id3.comment.p)*/);
}

QString PlayerThread::prepareTag(char *tag)
{
	switch(tag[0]) {
	case 0: return QString(tag+1);
	case 1: return QString::fromUtf16((ushort *)(tag+1));
	case 2: return QString::fromUtf16((ushort *)(tag+1));
	case 3: return QString::fromUtf8(tag+1);
	}
	return QString();
}

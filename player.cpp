#include "player.h"

Player::Player() : QObject(0), _play(false),  svolume(100), file(""), sync(false)
{
    device = OpenDevice();
    device->registerCallback(this);
    stream = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

Player::~Player()
{
    delete timer;
}

Player &Player::Self()
{
    static Player* player = new Player();
    return *player;
}

void Player::ref() {}

void Player::unref() {}

void Player::streamStopped(StopEvent* event)
{
    if(sync) {
	sync = false;
	sem.release();
    } else emit finish();
}

bool Player::open(QString fname)
{
    file = fname;
    stream = OpenSound(device, file.toLocal8Bit(), true);
    if(stream) stream->setVolume(float(svolume)/100);
    _play = false;
    return stream;
}

bool Player::play()
{
    if(stream) {
	stream->play();
	timer->start(500);
	_play = true;
	return true;
    }
    return false;
}

bool Player::stop()
{
    if(stream && _play) {
	stream->reset();
	return true;
    }
    return false;
}

bool Player::setPause(bool p)
{
    if(p && stream && _play) {
	timer->stop();
	_play = false;
	sync_stop();
	return true;
    }
    if(!p && stream && !_play) {
	stream->play();
	_play = true;
	timer->start(500);
	return true;
    }
    return false;
}

bool Player::close()
{
    if(stream) {
	timer->stop();
	_play = false;
	sync_stop();
	stream = 0;
	return true;
    }
    return false;
}

bool Player::setPosition(double pos)
{
    if(stream && stream->isSeekable()) {
	stream->setPosition(stream->getLength()*pos);
	return true;
    }
    return false;
}

int  Player::volume()
{
    return svolume;
}

void Player::setVolume(int v)
{
    svolume = v;
    if(stream) stream->setVolume(float(svolume)/100);
}

bool Player::playing()
{
    return _play;
}

void Player::timerUpdate()
{
    if(stream && stream->isPlaying()) {
	long p = stream->getPosition();
	long l = stream->getLength();
	if(l > 0) emit position((double)p/l);
    } else {
	timer->stop();
    }
}

void Player::sync_stop()
{
    if(stream) {
	sync = true;
	stream->stop();
	sem.acquire();
    }
}

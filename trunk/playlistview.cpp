#include "playlistview.h"
#include "tageditor.h"
#include "tagger.h"

/***********************
 * 
 *    PlaylistView
 * 
 ***********************/ 

PlaylistView::PlaylistView(AudioDevicePtr *dev, QWidget *parent)
    : QTreeView(parent)/*, filler(0)*/, plthread(0), repeat_mode(false), 
    shuffle_mode(false), disable_signal(false), filedescr(0), 
    correct(false), svolume(99), playing(false), dragStarted(false)
{
	setModel(&model);
	setEditTriggers(QAbstractItemView::NoEditTriggers); 
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	hideColumn(PlaylistModel::Empty);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	
	// init audiere
	device = dev;
	//device->registerCallback(this);
	
}

PlaylistView::~PlaylistView()
{
	if(plthread) {
		if(filedescr > 0) ::close(filedescr);
		plthread->disconnect();
		plthread->terminate();
		plthread = 0;
	}
	
	// clear audiere
	device = 0;
	
}

bool PlaylistView::isPlaying()
{
	return playing;
}

// start drag&drop block
void PlaylistView::dropEvent(QDropEvent *event)
{
	if(dragStarted) {
	    QModelIndex index = indexAt(event->pos());
        if (model.dropMimeData(event->mimeData(),
            Qt::MoveAction, index.row(), index.column(), index)) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
	    stopAutoScroll();
	    setState(NoState);
	} else QTreeView::dropEvent(event);
}

void PlaylistView::startDrag(Qt::DropActions supportedActions)
{
	dragStarted = true;
	QTreeView::startDrag(supportedActions);
	dragStarted = false;
}


// end drag&drop block

void PlaylistView::addItem(QString item, int id, QModelIndex* ind)
{
	//QMessageBox::information(0, tr(""), item);
	//item.insert(0, QString::number(item.at(0).unicode()));
	if(!ind) ind = &insindex;
	if(id == PlaylistModel::File)
		model.insertRows(ind->row()<0 ? model.rowCount() : ind->row(), 1);
	model.setData(ind->row()<0 ? model.index(model.rowCount()-1, id) : model.index(ind->row(), id), item, Qt::EditRole);
}

void PlaylistView::fillFinished()
{
//	if(filler) {
//		delete filler;
//		filler = 0;
//	}
}

void PlaylistView::fillCancel()
{
//	if(filler) {
//		filler->terminate();
//		delete filler;
//		filler = 0;
//	}
}

void PlaylistView::prev()
{
	clearSelection();
	QModelIndex prev = prevItem(); 
	setCurrentIndex(prev);
	curindex = prev;
	play();
}

void PlaylistView::next()
{
	if(disable_signal) {
		disable_signal = false;
		return;
	}
	//clearSelection();
	if(plindex.row() >= 0) prev_queue.push_back(plindex);
	QModelIndex next = nextItem();
	curindex = next;
	setCurrentIndex(curindex);
	if(curindex.row() >= 0) play();
}

void PlaylistView::pause(bool pause)
{
	if(stream) {
		if(pause) {
			disable_signal = true;
			stream->stop();
		}
		else {
			stream->play();
			timer->start();
		}
	} else {
		if(pause) {
			mutexPause.lock();
		} else {
			mutexPause.unlock();
		}
	}
}

void PlaylistView::play()
{
	if(curindex.row() < 0) return;
	plindex = model.index(curindex.row(), PlaylistModel::File);
	model.setCurrent(plindex.row());
	if(plthread) {
		disable_signal = true;
		if(filedescr > 0) ::close(filedescr);
		plthread->disconnect();
		plthread->terminate();
		plthread = 0;
	}
	if(stream && stream->isPlaying()) {
		disable_signal = true;
		stream->stop();
		stream = 0;
		timer->stop();
	}
	stream = OpenSound(*device, model.data(plindex, Qt::UserRole).toString().toLocal8Bit().constData(), true);
	if(stream) {
		stream->setVolume(float(svolume)/100);
		stream->play();
		timer->start(500);
		playing = true;
		emit started(this);
	} else {
		plthread = new PlayerThread(&filedescr, model.data(plindex, Qt::UserRole).toString()/*.insert(0, QChar('"')).append(QChar('"'))*/, mutexPause);
		connect(plthread, SIGNAL(finished()), this, SLOT(playFinished()));
		connect(plthread, SIGNAL(position(double, double)), this, SLOT(position(double, double)));
		plthread->start();
		playing = true;
		emit started(this);
	}
	//disable_signal = false;
	//QMessageBox::information(this, tr(""), "message");
	info = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString m = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString() + " - " + model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	emit status(info/*, &m*/);
}

void PlaylistView::stop()
{
	if(plthread) {
		if(filedescr > 0) ::close(filedescr);
		plthread->disconnect();
		delete plthread;
		plthread = 0;
		playing = false;
	}
	if(stream) {
		stream->stop();
		stream = 0;
		timer->stop();
		playing = false;
	}
}

void PlaylistView::playFinished()
{
	if(disable_signal) {
		disable_signal = false;
		return;
	}
	if(plthread) {
		if(filedescr > 0) ::close(filedescr);
		plthread->disconnect();
		delete plthread;
		plthread = 0;
		playing = false;
	}
	next();
}

QModelIndex PlaylistView::nextItem()
{
	if(model.rowCount() < 1) return model.index(-1, 0); 
	QModelIndex next;
	if(queue.count()) {
		next = queue.first();
		queue.pop_front();
		model.setData(model.index(next.row(), PlaylistModel::Stat), "", Qt::EditRole);
		for(int i=0; i<queue.count(); i++)
			model.setData(model.index(queue[i].row(), PlaylistModel::Stat), QVariant(i+1), Qt::EditRole);
	} else if(shuffle_mode) {
		bool duplicate;
		do {
			if(plindex.row() >= 0) next = model.index((plindex.row()+rand())%model.rowCount(), 0);
			else if(curindex.row() >= 0) next = model.index((curindex.row()+rand())%model.rowCount(), 0);
			else next = model.index(rand()%model.rowCount(), 0);
			duplicate = false;
			// FIXME more smart shuffle
			if(model.rowCount() > prev_queue.count()) 
				foreach(QModelIndex ind, prev_queue) {
					if(ind.row() == next.row()) {
						duplicate = true;
						break;
					}
				}
		} while(duplicate);
	} else {
		if(curindex.row() >= 0) 
			next = model.index(curindex.row()+1, 0);
		if(next.row() < 0) {
			if(repeat_mode) next = model.index(0, 0);
			else next = model.index(-1, 0);
		}
	}
	return next;
}

QModelIndex PlaylistView::prevItem()
{
	QModelIndex prev;
	if(prev_queue.count()) {
		prev = prev_queue.last();
		prev_queue.pop_back();
		return prev;
	}
	if(curindex.row() >= 0) {
		prev = model.index(curindex.row()-1, 0); 
		if(prev.row() >= 0) return prev;
		return model.index(0,0);
	} else
		return model.index(-1,0);
}

void PlaylistView::repeat(bool mode)
{
	repeat_mode = mode;
}

void PlaylistView::shuffle(bool mode)
{
	shuffle_mode = mode;
}

void PlaylistView::onClick(const QModelIndex &index)
{
	if(curindex.row() >= 0) prev_queue.push_back(curindex);
	curindex = index;
}

void PlaylistView::onDoubleClick(const QModelIndex &index)
{
	if(curindex.row() >= 0) prev_queue.push_back(curindex);
	curindex = index;
	play();
}

void PlaylistView::position(double pos1, double pos2)
{
	//char buf[1000];
	//sprintf(buf, " (playing) %02lu:%02u.%02u [%02lu:%02u.%02u]",
			//(unsigned long) pos1/60, (unsigned int)pos1%60, (unsigned int)(pos1*100)%100,
			//(unsigned long) pos2/60, (unsigned int)pos2%60, (unsigned int)(pos2*100)%100
			//);
	//emit status(QString(info).append(QString(buf)));
	if(pos2 > 0) {
		emit songPosition((int)(1000*pos1/pos2));
	} else emit songPosition(0); 
}

void PlaylistView::timerUpdate()
{
	if(stream && stream->isPlaying()) {
		long p = stream->getPosition();
		long l = stream->getLength();
		//char buf[1000];
		//sprintf(buf, " (playing) %ld [%ld]", p, l);
		//emit status(QString(info).append(QString(buf)));
		if(l > 0) {
			emit songPosition((int)(1000.0F*p/l));
		} else emit songPosition(0); 
	} else {
		timer->stop();
	}
}

void PlaylistView::setVolume(int volume)
{
	svolume = volume;
	if(stream) stream->setVolume(float(volume)/100);
}

#define eqalizer(n) void PlaylistView::eq##n(int value) {}

eqalizer(1);
eqalizer(2);
eqalizer(3);
eqalizer(4);
eqalizer(5);
eqalizer(6);
eqalizer(7);
eqalizer(8);
eqalizer(9);
eqalizer(10);
eqalizer(11);
eqalizer(12);
eqalizer(13);
eqalizer(14);
eqalizer(15);
eqalizer(16);

#undef eqalizer

void PlaylistView::eqalizer(bool enable)
{
//	mpg::have_eq_settings = (int)enable;
}

void PlaylistView::clear()
{
	plindex = curindex = insindex = model.index(-1, 0);
	queue.clear();
	prev_queue.clear();
	model.removeRows(0, model.rowCount());
}

void PlaylistView::queueNext()
{
	queue.append(curindex);
	model.setData(model.index(curindex.row(), PlaylistModel::Stat), QVariant(queue.count()), Qt::EditRole);
}

void PlaylistView::tagready(QString t1/*, QString t2, QString t3, QString t4, QString t5, QString t6*/)
{
	info = t1;
}

void PlaylistView::viewAlbum(bool h)
{
	setColumnHidden(PlaylistModel::Album, !h);
}

void PlaylistView::viewArtist(bool h)
{
	setColumnHidden(PlaylistModel::Artist, !h);
}

void PlaylistView::viewComment(bool h)
{
	setColumnHidden(PlaylistModel::Comment, !h);
}

void PlaylistView::viewTrack(bool h)
{
	setColumnHidden(PlaylistModel::Track, !h);
}

void PlaylistView::viewTitle(bool h)
{
	setColumnHidden(PlaylistModel::Title, !h);
}

void PlaylistView::viewYear(bool h)
{
	setColumnHidden(PlaylistModel::Year, !h);
}

void PlaylistView::viewGenre(bool h)
{
	setColumnHidden(PlaylistModel::Genre, !h);
}

void PlaylistView::viewFile(bool h)
{
	setColumnHidden(PlaylistModel::File, !h);
}

void PlaylistView::viewLength(bool h)
{
	setColumnHidden(PlaylistModel::Length, !h);
}

void PlaylistView::editTag()
{
	if(curindex.row() >= 0) {
		TagEditor *te = new TagEditor(model.data(model.index(curindex.row(), PlaylistModel::File), Qt::UserRole).toString(), this);
		te->index = curindex.row();
		connect(te, SIGNAL(editComplete(int)), this, SLOT(updateTag(int)));
		//resetTags(curindex);
		te->show();
	}
}

void PlaylistView::updateTag(int i)
{
	QModelIndex ind = model.index(i, 0); 
	resetTags(ind);
}

void PlaylistView::resetTags(QModelIndex& ind)
{
	QString path = model.data(model.index(ind.row(), PlaylistModel::File), Qt::UserRole).toString();
	QString title, artist, album, comment, genre, length;
	int track, year;
	
	Tagger::readTags(path, title, artist, album, comment, genre, track, year, length);
	
	addItem(title, PlaylistModel::Title, &ind);
	addItem(artist, PlaylistModel::Artist, &ind);
	addItem(album, PlaylistModel::Album, &ind);
	addItem(QString::number(year), PlaylistModel::Year, &ind);
	addItem(comment, PlaylistModel::Comment, &ind);
	addItem(QString::number(track), PlaylistModel::Track, &ind);
	addItem(genre, PlaylistModel::Genre, &ind);
}

void PlaylistView::removeSong()
{
	while(this->selectedIndexes().count() > 0) {
		model.removeRows(this->selectedIndexes().at(0).row(), 1);
	}
}


#include "playlistview.h"
#include "tageditor.h"
#include "tagger.h"

/***********************
 * 
 *    PlaylistView
 * 
 ***********************/ 

PlaylistView::PlaylistView(QString &str, QWidget *parent)
    : QTreeView(parent), correct(false), playing(false), dragStarted(false)
{
	plistname = str;
    model.setDynamicSortFilter(true);
    model.setSourceModel(&plmodel);
	setModel(&model);
	setEditTriggers(QAbstractItemView::NoEditTriggers); 
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	//setSortingEnabled(true);
	connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onClick(const QModelIndex &)));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onDoubleClick(const QModelIndex &)));
	hideColumn(PlaylistModel::Empty);
	if(plistname.size()) {  // read stored playlist
		QString fname = QDir::homePath() + "/.cuberok/" + plistname + ".plist";
		if(QFile::exists(fname)) {
			QFile file(fname);
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				QTextStream in(&file);
				QMimeData data;
				QList<QUrl> urls;
				while (!in.atEnd()) {
					QUrl url = QUrl::fromLocalFile(in.readLine());
					urls << url;
				} 
				data.setUrls(urls);
				plmodel.dropMimeData(&data, Qt::CopyAction, -1, -1, plmodel.index(plmodel.rowCount(), 0));
				file.close();
			}
		}
	}
}

PlaylistView::~PlaylistView()
{
	storeList();
}

void PlaylistView::storeList(QString fname)
{
	if(!fname.size())
		fname = QDir::homePath() + "/.cuberok/" + plistname + ".plist";
	QFile file(fname);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		for(int i=0; i<model.rowCount(); i++) {
			out << model.data(model.index(i, PlaylistModel::File), Qt::UserRole).toString() << endl;
		}
		file.close();
	}
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
	if(plindex.row() >= 0) prev_queue.push_back(plindex);
	QModelIndex next = nextItem();
	curindex = next;
	setCurrentIndex(curindex);
	if(curindex.row() >= 0) play();
}

void PlaylistView::play()
{
	if(curindex.row() < 0) return;
	plindex = model.index(curindex.row(), PlaylistModel::File);
	//model.setCurrent(plindex.row());
	if(Player::Self().playing()) Player::Self().close();
	Player::Self().open(model.data(model.index(plindex.row(), PlaylistModel::File), Qt::UserRole).toString());
	disconnect(&Player::Self(), SIGNAL(finish()), 0, 0);
	disconnect(&Player::Self(), SIGNAL(position(double)), 0, 0);
	connect(&Player::Self(), SIGNAL(finish()), this, SLOT(playFinished()));
	connect(&Player::Self(), SIGNAL(position(double)), this, SLOT(position(double)));
	Player::Self().play();
	playing = true;
	emit started(this);
	//QMessageBox::information(this, tr(""), "message");
	info = model.data(model.index(plindex.row(), PlaylistModel::Title), Qt::DisplayRole).toString();
	QString m = model.data(model.index(plindex.row(), PlaylistModel::Artist), Qt::DisplayRole).toString() + " - " + model.data(model.index(plindex.row(), PlaylistModel::Album), Qt::DisplayRole).toString();
	emit status(info/*, &m*/);
}

void PlaylistView::stop()
{
    Player::Self().stop();
    playing = false;
}

void PlaylistView::playFinished()
{
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
	} else if(Player::Self().shuffle_mode) {
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
			if(Player::Self().repeat_mode) next = model.index(0, 0);
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

void PlaylistView::position(double pos)
{
	emit songPosition((int)(1000*pos));
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


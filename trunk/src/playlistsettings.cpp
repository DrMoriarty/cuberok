#include "playlistsettings.h"
#include <QtGui>

PlaylistSettings::PlaylistSettings() : QObject(0)
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		_data[i].v = (bool)set.value("colvisible"+QString::number(i), 1).toInt(0);
		_data[i].w = set.value("colwidth"+QString::number(i), 30).toInt(0);
	}
}

PlaylistSettings::~PlaylistSettings()
{
	QSettings set;
	for(int i=0; i<PlaylistModel::ColumnCount; i++) {
		set.setValue("colvisible"+QString::number(i), (int)_data[i].v);
		set.setValue("colwidth"+QString::number(i), _data[i].w);
	}
}

PlaylistSettings& PlaylistSettings::Self()
{
	static PlaylistSettings self;
	return self;
}

bool PlaylistSettings::columnVisible(int col)
{
	return (col < PlaylistModel::ColumnCount ? _data[col].v : false);
}

bool PlaylistSettings::setColumnVisible(int col, bool vis)
{
	if(col >= PlaylistModel::ColumnCount) return false;
	if(_data[col].v != vis) {
		_data[col].v = vis;
		emit visibleChanged(col, vis);
		if(vis && !_data[col].w) setColumnWidth(col, 30);
		return !vis;
	} else return vis;
}

int  PlaylistSettings::columnWidth(int col)
{
	return col < PlaylistModel::ColumnCount ? _data[col].w : 0;
}

int  PlaylistSettings::setColumnWidth(int col, int wid)
{
	if(col >= PlaylistModel::ColumnCount) return 0;
	if(_data[col].w != wid) {
		int ow = _data[col].w;
		_data[col].w = wid;
		emit widthChanged(col, wid);
		return ow;
	} else return wid;
}


#ifndef PLAYLISTSETTINGS_H
#define PLAYLISTSETTINGS_H

#include <QtCore>
#include "playlistmodel.h"

class PlaylistSettings: public QObject
{
Q_OBJECT
 public:
	~PlaylistSettings();
	static PlaylistSettings& Self();
	bool columnVisible(int col);
	bool setColumnVisible(int col, bool vis);
	int  columnWidth(int col);
	int  setColumnWidth(int col, int wid);

 signals:
	void visibleChanged(int, bool);
	void widthChanged(int, int);

 private:
	PlaylistSettings();
	
	struct _Data {
		bool v;
		int w;
	};
	struct _Data _data[PlaylistModel::ColumnCount];
};

#define PLSet PlaylistSettings::Self() 

#endif // PLAYLISTSETTINGS_H

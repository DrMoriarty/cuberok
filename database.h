#ifndef DATABASE_H_
#define DATABASE_H_

#include <QtSql>

static const QString nArtist = "Artist",
	nAlbum = "Album",
	nGenre = "Genre",
	nMark = "Mark";


class Database
{
public:
	static Database& Self();
	virtual ~Database();
	int AddFile(QString file);
	int AddArtist(QString artist);
	int AddAlbum(QString album);
	int AddGenre(QString genre);
	int AddMark(QString mark);
	void Increment(int ar, int al, int ge);
	void Decrement(int ar, int al, int ge);
	void RemoveFile(QString file);
	void RemoveArtist(QString artist);
	void RemoveAlbum(QString album);
	void RemoveGenre(QString genre);
	void RemoveMark(QString mark);
	void RenameArtist(QString oldval, QString newval);
	void RenameAlbum(QString oldval, QString newval);
	void RenameGenre(QString oldval, QString newval);
	void RenameMark(QString oldval, QString newval);
	QMap<QString, int> Artists(QString *patt = 0);
	QMap<QString, int> Albums(QString *patt = 0);
	QMap<QString, int> Genres(QString *patt = 0);
	QMap<QString, int> Marks(QString *patt = 0);
	QList<QString> Songs(QString *ar = 0, QString *al = 0, QString *ge = 0, QString *ma = 0);
	QString GetArtist(int);
	QString GetAlbum(int);
	QString GetGenre(int);
	QString GetMark(int);
	bool GetTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, QString &length);
	bool SetTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year);
	bool SetMark(QString file, QString mark);
	
	void clearSubset();
	void subsetAlbum(QString);
	void subsetArtist(QString);
	void subsetGenre(QString);
	void subsetMark(QString);
private:
	Database();
	QSqlDatabase db;
	bool open;
	bool subset;
	QString ssAlbum;
	QString ssArtist;
	QString ssGenre;
	QString ssMark;
	QString ssFilter;
	void RefAttribute(const QString attr, int id, int v);
	int AddAttribute(const QString attr, QString val);
	void RemoveAttribute(const QString attr, QString val);
	void RenameAttribute(const QString attr, QString oldval, QString newval);
	QMap<QString, int> Attributes(const QString attr, QString *patt = 0);
	QString subsetFilter();
};

#endif /*DATABASE_H_*/

#ifndef TAGGER_H_
#define TAGGER_H_

#include <QtCore>

static bool _autoCorrect = false;
static bool _saveCorrected = true;

class Tagger
{
public:
	virtual ~Tagger();
	
	//static Tagger& self();
	static bool readTags(QString file, QString &title, QString &artist, QString &album, QString &comment, QString &genre, int &track, int &year, QString &length);
	static bool writeTags(QString file, QString title, QString artist, QString album, QString comment, QString genre, int track, int year);
	static bool updateArtist(QString file, QString artist);
	static bool updateAlbum(QString file, QString album);
	static bool updateGenre(QString file, QString genre);
	static QString correct8bit(QString str, bool *corrected = 0);
	static QString correctBrokenUnicode(QString str, bool *corrected = 0);
	
	static bool autoCorrect();
	static void setAutoCorrect(bool);
	static bool saveCorrected();
	static void setSaveCorrected(bool);
	
private:
	Tagger();
	
	//static bool corrected = false;
	
};

#endif /*TAGGER_H_*/

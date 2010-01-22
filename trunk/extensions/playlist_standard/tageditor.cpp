/* Cuberok
 * Copyright (C) 2008 Vasiliy Makarov <drmoriarty.0@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "tageditor.h"
#include "global.h"
#include "tagger.h"
//#include "database.h"

static const int genresSize = 148;
static const QString genres[] = {
      "Blues",
      "Classic Rock",
      "Country",
      "Dance",
      "Disco",
      "Funk",
      "Grunge",
      "Hip-Hop",
      "Jazz",
      "Metal",
      "New Age",
      "Oldies",
      "Other",
      "Pop",
      "R&B",
      "Rap",
      "Reggae",
      "Rock",
      "Techno",
      "Industrial",
      "Alternative",
      "Ska",
      "Death Metal",
      "Pranks",
      "Soundtrack",
      "Euro-Techno",
      "Ambient",
      "Trip-Hop",
      "Vocal",
      "Jazz+Funk",
      "Fusion",
      "Trance",
      "Classical",
      "Instrumental",
      "Acid",
      "House",
      "Game",
      "Sound Clip",
      "Gospel",
      "Noise",
      "Alternative Rock",
      "Bass",
      "Soul",
      "Punk",
      "Space",
      "Meditative",
      "Instrumental Pop",
      "Instrumental Rock",
      "Ethnic",
      "Gothic",
      "Darkwave",
      "Techno-Industrial",
      "Electronic",
      "Pop-Folk",
      "Eurodance",
      "Dream",
      "Southern Rock",
      "Comedy",
      "Cult",
      "Gangsta",
      "Top 40",
      "Christian Rap",
      "Pop/Funk",
      "Jungle",
      "Native American",
      "Cabaret",
      "New Wave",
      "Psychedelic",
      "Rave",
      "Showtunes",
      "Trailer",
      "Lo-Fi",
      "Tribal",
      "Acid Punk",
      "Acid Jazz",
      "Polka",
      "Retro",
      "Musical",
      "Rock & Roll",
      "Hard Rock",
      "Folk",
      "Folk/Rock",
      "National Folk",
      "Swing",
      "Fusion",
      "Bebob",
      "Latin",
      "Revival",
      "Celtic",
      "Bluegrass",
      "Avantgarde",
      "Gothic Rock",
      "Progressive Rock",
      "Psychedelic Rock",
      "Symphonic Rock",
      "Slow Rock",
      "Big Band",
      "Chorus",
      "Easy Listening",
      "Acoustic",
      "Humour",
      "Speech",
      "Chanson",
      "Opera",
      "Chamber Music",
      "Sonata",
      "Symphony",
      "Booty Bass",
      "Primus",
      "Porn Groove",
      "Satire",
      "Slow Jam",
      "Club",
      "Tango",
      "Samba",
      "Folklore",
      "Ballad",
      "Power Ballad",
      "Rhythmic Soul",
      "Freestyle",
      "Duet",
      "Punk Rock",
      "Drum Solo",
      "A Capella",
      "Euro-House",
      "Dance Hall",
      "Goa",
      "Drum & Bass",
      "Club-House",
      "Hardcore",
      "Terror",
      "Indie",
      "BritPop",
      "Negerpunk",
      "Polsk Punk",
      "Beat",
      "Christian Gangsta Rap",
      "Heavy Metal",
      "Black Metal",
      "Crossover",
      "Contemporary Christian",
      "Christian Rock",
      "Merengue",
      "Salsa",
      "Thrash Metal",
      "Anime",
      "Jpop",
      "Synthpop"
};

TagEditor::TagEditor(STags t, QWidget *parent)
    : QDialog(parent), index(0)
{
	ui.setupUi(this);
	tag = t;
	file = t.tag0.url.toString();
	
	QStringList sl;
	for(int i=0; i<genresSize; i++) sl.append(genres[i]);
	sl.sort();
	ui.comboBox_Genre->addItems(sl);
	//ui.comboBox_Genre->setEditText(QS(fr.tag()->genre()));
	//QString title, artist, album, comment, genre, length, type;
	//int track, year, rating=0;
	//Tagger::readTags(fname, title, artist, album, comment, genre, track, year, length);
	QString f = ToLocalFile(t.tag0.url);
	ui.label->setText(f.size() ? f : file);
	ui.lineTitle->setText(t.tag0.title);
	ui.lineArtist->setText(t.tag0.artist);
	ui.lineAlbum->setText(t.tag0.album);
	ui.lineComment->setText(t.tag0.comment);
	ui.spinBox_Track->setValue(t.tag0.track);
	ui.spinBox_Year->setValue(t.tag0.year);
	ui.comboBox_Genre->setEditText(t.tag0.genre);
	ui.spinBox_Rating->setValue(t.tag0.rating);
}

TagEditor::~TagEditor()
{

}

void TagEditor::correct1()
{
	ui.lineTitle->setText(Tagger::correct8bit(ui.lineTitle->text()));
	ui.lineArtist->setText(Tagger::correct8bit(ui.lineArtist->text()));
	ui.lineAlbum->setText(Tagger::correct8bit(ui.lineAlbum->text()));
	ui.lineComment->setText(Tagger::correct8bit(ui.lineComment->text()));
	ui.comboBox_Genre->setEditText(Tagger::correct8bit(ui.comboBox_Genre->currentText()));
}

void TagEditor::correct2()
{
	ui.lineTitle->setText(Tagger::correctBrokenUnicode(ui.lineTitle->text()));
	ui.lineArtist->setText(Tagger::correctBrokenUnicode(ui.lineArtist->text()));
	ui.lineAlbum->setText(Tagger::correctBrokenUnicode(ui.lineAlbum->text()));
	ui.lineComment->setText(Tagger::correctBrokenUnicode(ui.lineComment->text()));
	ui.comboBox_Genre->setEditText(Tagger::correctBrokenUnicode(ui.comboBox_Genre->currentText()));
}

void TagEditor::save()
{
	tag.tag0.title = ui.lineTitle->text();
	tag.tag0.artist = ui.lineArtist->text();
	tag.tag0.album = ui.lineAlbum->text();
	tag.tag0.comment = ui.lineComment->text();
	tag.tag0.genre = ui.comboBox_Genre->currentText();
	tag.tag0.track = ui.spinBox_Track->value();
	tag.tag0.year = ui.spinBox_Year->value();
	tag.tag0.rating = ui.spinBox_Rating->value();
	QString f = ToLocalFile(QUrl(file));
	if(f.size()) {
		Tagger::writeTags(f, ui.lineTitle->text(), ui.lineArtist->text(), ui.lineAlbum->text(), ui.lineComment->text(), ui.comboBox_Genre->currentText(), ui.spinBox_Track->value(), ui.spinBox_Year->value());
	}
	//Database::Self().SetTags(file, ui.lineTitle->text(), ui.lineArtist->text(), ui.lineAlbum->text(), ui.lineComment->text(), ui.comboBox_Genre->currentText(), ui.spinBox_Track->value(), ui.spinBox_Year->value(), ui.spinBox_Rating->value());
	emit editComplete(this);
	this->close();
}


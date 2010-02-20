/* Cuberok
 * Copyright (C) 2009 Vasiliy Makarov <drmoriarty.0@gmail.com>
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

#include "lyricwidget.h"

LyricWidget::LyricWidget(Proxy *pr, QWidget *parent) : ExtensionSetupWidget(parent), proxy(pr)
{
	setAttribute(Qt::WA_DeleteOnClose);

	vLayout = new QVBoxLayout(this);
	vLayout->setSpacing(4);
	vLayout->setMargin(4);
	vLayout->setObjectName(QString::fromUtf8("vLayout"));
	
    label_1 = new QLabel(this);
    label_1->setObjectName(QString::fromUtf8("label_1"));
	label_1->setText(QApplication::translate("Lyric", "Select preffered lyric source", 0, QApplication::UnicodeUTF8));

    vLayout->addWidget(label_1);

	comboBox = new QComboBox(this);
	comboBox->addItem("Lucky Google");
	comboBox->addItem("Lyrics.Wikia.Com");
	comboBox->addItem("NoMoreLyrics.Net");
	int cur = 0;
	if(proxy->hasVariable("lyricSearchType")) cur = proxy->getVariable("lyricSearchType").toInt();
	comboBox->setCurrentIndex(cur);

	vLayout->addWidget(comboBox);
	vLayout->addStretch();

    // QIcon icon4;
    // icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/lastfm.png")), QIcon::Normal, QIcon::Off);
	// setWindowIcon(icon4);

}

LyricWidget::~LyricWidget()
{
}

void LyricWidget::storeState()
{
	proxy->setVariable("lyricSearchType", QString::number(comboBox->currentIndex()));
}

/* This file is part of the KDE libraries
   Copyright (C) 2000 Ronny Standtke <Ronny.Standtke@gmx.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KSQUEEZEDTEXTLABEL_H
#define KSQUEEZEDTEXTLABEL_H

//#include <kdeui_export.h>
#include <QtGui/QLabel>

class KSqueezedTextLabelPrivate;
//class KDEUI_EXPORT KSqueezedTextLabel : public QLabel {
class KSqueezedTextLabel : public QLabel {
  Q_OBJECT
  Q_PROPERTY( Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode )

public:
  explicit KSqueezedTextLabel( QWidget *parent = 0 );
  explicit KSqueezedTextLabel( const QString &text, QWidget *parent = 0 );
  virtual ~KSqueezedTextLabel();

  virtual QSize minimumSizeHint() const;
  virtual QSize sizeHint() const;
  /*
   * Overridden for internal reasons; the API remains unaffected.
   */
  virtual void setAlignment( Qt::Alignment );

  Qt::TextElideMode textElideMode() const;
  void setTextElideMode( Qt::TextElideMode mode );

public Q_SLOTS:
  void setText( const QString &text );
  void clear();

protected:
  void resizeEvent( QResizeEvent * );
  /*
   * does the dirty work
   */
  void squeezeTextToLabel();

private:
  KSqueezedTextLabelPrivate * const d;
};

#endif // KSQUEEZEDTEXTLABEL_H

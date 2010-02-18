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

#include "global.h"
#include "psi.h"
#include "psi_settings.h"
#include <QtGui>
#ifdef Q_OS_LINUX
#include <QtDBus>
#endif

Q_EXPORT_PLUGIN2(scrobbler_psi, PsiTune) 

PsiTune::PsiTune() : Extension(), enabled(false)
{
}

PsiTune::~PsiTune()
{
}

bool PsiTune::prepare()
{
	QSettings set;
	set.beginGroup("im_tune");
	psiTuneFile = set.value("PsiTuneFile", DEFAULT_PSI_TUNE).toString();
	enabled = set.value("PsiTune", false).toBool();
	kopeteEnabled = set.value("KopeteTune", false).toBool();
	kopeteStatus = set.value("KopeteStatus", DEFAULT_KOPETE_STATUS).toString();
	kdeNotify = set.value("KdeNotify", true).toBool();
	set.endGroup();
	return true;
}

bool PsiTune::ready()
{
	return enabled || kopeteEnabled || kdeNotify;
}

void PsiTune::update(int)
{
	bool listening = false;
	bool changed = false;
	if(/*listening && */proxy->getStatus().playing == SStatus::Stopped) {
		// track finished
		listening = false;
		changed = true;
	}
	if(proxy->getStatus().playing == SStatus::Playing && proxy->getStatus().pos == .0f) {
		// track started
		listening = true;
		changed = true;
	}
	if ( changed ) {
		STags t = proxy->getTags();
		if(enabled) {
			QFile psiTuneFile(QSettings().value("PsiTuneFile", DEFAULT_PSI_TUNE).toString());
			psiTuneFile.open(QIODevice::WriteOnly | QIODevice::Text);
			QTextStream out(&psiTuneFile);
			if ( listening ) {
				out << t.tag0.title << '\n';
				out << t.tag0.artist << '\n';
				out << t.tag0.album << '\n';
				out << t.tag0.track << '\n';
				out << QString::number(t.tag0.length) << '\n';
			} else {
				out << '\n';
			}
			psiTuneFile.close();
		}
#ifdef Q_OS_LINUX
		if(listening) {
			if(kopeteEnabled) {
				QDBusMessage msg = QDBusMessage::createMethodCall("org.kde.kopete", "/Kopete", "org.kde.Kopete", "setOnlineStatus");
				QList<QVariant> args;
				args.append(QVariant(QString("online")));
				args.append(QVariant(kopeteStatus.replace("%song%", t.tag0.title).replace("%artist%", t.tag0.artist).replace("%album%", t.tag0.album)));
				msg.setArguments(args);
				//if(!QDBusConnection::sessionBus().send(msg)) qDebug("D-Bus error");
				QDBusMessage replyMsg = QDBusConnection::sessionBus().call(msg);
				if(replyMsg.type() == QDBusMessage::ErrorMessage) {
					qDebug("error: failed to send dbus message");
					qDebug("error text is:%s", (const char*)replyMsg.errorMessage().toUtf8());
				} else if(replyMsg.type() == QDBusMessage::ReplyMessage) {
				} else {
					qDebug("unexpected reply type");
				}
			}
			if(kdeNotify) {
				QDBusMessage m = QDBusMessage::createMethodCall( "org.kde.VisualNotifications", "/VisualNotifications", "org.kde.VisualNotifications", "Notify" );
				QList<QVariant> args;
				args.append(QString("Cuberok") ); // app_name
				args.append((uint)0 ); // replaces_id
				args.append(QString("")); // event_id
				args.append(QString("")); // app_icon
				args.append(tr("Play '%1'").arg(t.tag0.title)); // summary
				args.append(tr("by %1 - album '%2'").arg(t.tag0.artist).arg(t.tag0.album)); // body
				QStringList actionList;
				args.append( actionList ); // actions
				args.append( QVariantMap() ); // hints - unused atm
				args.append( 5000 ); // expire timout
				m.setArguments( args );
				QDBusMessage replyMsg = QDBusConnection::sessionBus().call(m);
				if(replyMsg.type() == QDBusMessage::ReplyMessage) {
					if (!replyMsg.arguments().isEmpty()) {
						uint dbus_id = replyMsg.arguments().at(0).toUInt();
					} else {
						qDebug("error: received reply with no arguments");
					}
				} else if (replyMsg.type() == QDBusMessage::ErrorMessage) {
					qDebug("error: failed to send dbus message");
					qDebug("error text is:%s", (const char*)replyMsg.errorMessage().toUtf8());
				} else {
					qDebug("unexpected reply type");
				}
			}
		}
#endif
	}
}

QString PsiTune::getName()
{
	return tr("PsiTune Scrobbler");
}

QWidget* PsiTune::getWidget()
{
	return 0;
}

QWidget* PsiTune::getSetupWidget()
{
	PsiTuneSettings *set = new PsiTuneSettings();
	connect(set, SIGNAL(destroyed(QObject*)), this, SLOT(settingsUpdate(QObject*)));
	return set;
//	return 0;
}

int PsiTune::getDisturbs()
{
	return DisturbOnStatus;// | DisturbOnTags;
}

void PsiTune::settingsUpdate(QObject* o)
{
	o->disconnect();
	QSettings set;
	set.beginGroup("im_tune");
	bool newEnabled = set.value("PsiTune", false).toBool();
	QString newPsiTuneFile = set.value("PsiTuneFile", DEFAULT_PSI_TUNE).toString();
	kopeteEnabled = set.value("KopeteTune", false).toBool();
	kopeteStatus = set.value("KopeteStatus", DEFAULT_KOPETE_STATUS).toString();
	kdeNotify = set.value("KdeNotify", true).toBool();
	set.endGroup();
	if(newEnabled != enabled || newPsiTuneFile != psiTuneFile) {
		enabled = newEnabled;
		psiTuneFile = newPsiTuneFile;
	}
}

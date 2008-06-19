#include "cuberok.h"
#include "aboutdialog.h"
#include "lookandfeel.h"
#include "tagger.h"

Cuberok::Cuberok(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.subsetLabel->setVisible(false);
	ui.subsetDisableButton->setVisible(false);
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(ui.actionPlay);
	trayIconMenu->addAction(ui.actionNext);
	trayIconMenu->addAction(ui.actionPrev);
	trayIconMenu->addAction(ui.actionPause);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(ui.actionExit);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(this->windowIcon());
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayevent(QSystemTrayIcon::ActivationReason)));
	
	QSettings set;
	//ui.line->restoreState(set.value("splitter").toByteArray());
	dirmodel.setFilter(QDir::AllDirs);
	this->findChild<QTreeView*> ("treeView_2")->setModel(&dirmodel);
	ui.treeView_2->hideColumn(1);
	ui.treeView_2->hideColumn(2);
	ui.treeView_2->hideColumn(3);
	ui.treeView_2->setAllColumnsShowFocus(true);
	ui.treeView_2->sortByColumn(0, Qt::AscendingOrder);
	
	connect(ui.volumeSlider, SIGNAL(valueChanged(int)), ui.listView, SLOT(setVolume(int)));
	ui.volumeSlider->setValue(set.value("volume", 99).toInt(0));
	
	if(set.value("shuffle", false).toBool())
		ui.actionShuffle->trigger();
	if(set.value("repeat", false).toBool())
		ui.actionRepeat->trigger();
	if(set.value("eqalizer", false).toBool())
		ui.actionEnableEqalizer->trigger();
	if(set.value("correctTag", false).toBool())
		ui.actionCorrectTag->trigger();
	
	ui.statusbar->addPermanentWidget(ui.listStatus);
	ui.statusbar->addPermanentWidget(ui.collectionStatus);
}

Cuberok::~Cuberok()
{
	QSettings set;
	//set.setValue("splitter", ui.line->saveState());
	set.setValue("volume", ui.volumeSlider->value());
	set.setValue("correctTag", ui.actionCorrectTag->isChecked());
	set.setValue("repeat", ui.actionRepeat->isChecked());
	set.setValue("shuffle", ui.actionShuffle->isChecked());
}

void Cuberok::on_AboutMenu()
{
	AboutDialog ad(this);
	ad.exec();
}

void Cuberok::lookAndFeel()
{
	LookAndFeel lnf;
	lnf.exec();
}

void Cuberok::message(QString title/*, QString* message*/)
{
	trayIcon->showMessage(title, /**message*/QString(""), QSystemTrayIcon::NoIcon, 10);
	setWindowTitle(QString(titlepref).append(title));
	trayIcon->setToolTip(title);
}

void Cuberok::trayevent(QSystemTrayIcon::ActivationReason r)
{
	if(r == QSystemTrayIcon::Trigger) setVisible(!isVisible());
}

void Cuberok::correctTag(bool b)
{
	Tagger::setAutoCorrect(b);
}

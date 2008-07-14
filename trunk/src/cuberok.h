#ifndef CUBEROK_H
#define CUBEROK_H

#include <QtGui>
//#include <QtGui/QMainWindow>
#include "ui_cuberok.h"
//#include "playlistmodel.h"

const char titlepref[] = "Cuberok - ";

class Cuberok : public QMainWindow
{
    Q_OBJECT

public:
    Cuberok(QWidget *parent = 0);
    ~Cuberok();
    
private:
    Ui::CuberokClass ui;
    QDirModel dirmodel;
    QSpinBox volumeBox;
    //PlaylistModel playlist;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

private slots:
	void on_AboutMenu();
	void on_AboutQtMenu();
	void trayevent(QSystemTrayIcon::ActivationReason);
	void progressEvent(double);

public slots:
	void lookAndFeel();
	void message(QString/*, QString**/);
	void correctTag(bool);
};

#endif // CUBEROK_H

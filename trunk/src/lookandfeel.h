#ifndef LOOKANDFEEL_H
#define LOOKANDFEEL_H

#include <QtGui>
#include "ui_lookandfeel.h"

class LookAndFeel : public QDialog
{
    Q_OBJECT

public:
    LookAndFeel(QWidget *parent = 0);
    ~LookAndFeel();
    void previewStyle(QStyle * style);
    void previewPalette(QPalette &palette);

private:
	void setStyleRecursive(QStyle *style, QWidget *wid);
	void setPaletteRecursive(QPalette &palette, QWidget *wid);
	
    Ui::LookAndFeelClass ui;
    QStyle *_style;
    QPalette _palette;
    int _role, _group;

public slots:
	void applyAll();
	void set_style(QString);
	void set_brush(int);
	void set_group(int);
	void set_role(int);
	void set_color();
	void acceptWithApply();
	void quick();
};

#endif // LOOKANDFEEL_H

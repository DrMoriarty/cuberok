#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QtCore>
#include <QtGui>

class ProgressBar : public QProgressBar
{
 Q_OBJECT
     
 public:
    ProgressBar ( QWidget * parent = 0 );

 protected:
    virtual void mousePressEvent ( QMouseEvent * event );
 signals:
    void userevent(double);
};


#endif //PROGRESSBAR_H

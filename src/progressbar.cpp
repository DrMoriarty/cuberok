#include "progressbar.h"

ProgressBar::ProgressBar ( QWidget * parent ) : QProgressBar(parent) 
{
}

void ProgressBar::mousePressEvent ( QMouseEvent * event ) 
{
    emit userevent((double)event->x()/width());
}


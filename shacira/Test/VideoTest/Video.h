
#ifndef _VIDEO_H
#define _VIDEO_H

#include <qapplication.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qcanvas.h>
#include <qframe.h>
#include <qtimer.h>
#include "base/eb_sema.hpp"
#include "Grabber.h"

class Video : public QWidget
{
   Q_OBJECT
public:
    Video(QWidget * parent, Grabber * grabber, cMutexSem * sync, int device_index);
   ~Video();
   void ShowImage();
   void Show(int i, int n);
protected:
   void paintEvent( QPaintEvent * );
   void keyPressEvent( QKeyEvent * );
   void update();
private:
   Grabber * _Grabber;
   QPixmap * _Pixmap;
   QTimer * _Timer;
   int _Sequence;
   bool _Recording;
   cMutexSem * _Sync;
   int _DeviceIndex;
};

#endif


#ifndef _clickfilter_h_
#define _clickfilter_h_

#include <qobject.h>

class ClickFilter : public QObject
{
protected:
   bool eventFilter(QObject * o, QEvent * e);
};

#endif

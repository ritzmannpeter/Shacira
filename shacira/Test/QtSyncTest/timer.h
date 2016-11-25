
#ifndef _time_h_
#define _time_h_

#include <qwidget.h>
#include <qtimer.h>
class Label;
void showText(Label * label);

class Timer : public QTimer
{
   Q_OBJECT
public:
   Timer(Label * label, QWidget * parent = 0)
      : QTimer(parent), _label(label)
   {
   };
#ifdef lassma
   virtual void timerEvent(QTimerEvent * e)
   {
      showText(_label);
   };
#endif
   public slots:
   void expired()
   {
      showText(_label);
   };
private:
   Label * _label;
};

#endif

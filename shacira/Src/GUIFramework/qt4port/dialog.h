
#ifndef _dialog_h_
#define _dialog_h_

#include <qwidget.h>
#include <qdialog.h>

#ifdef QT4
#include "qt4port.h"
#else
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#define NOT_PORTED(msg)
#define _CWIDGET_EXPORT_
#endif


class DialogBase : public QDialog
{
    Q_OBJECT

public:
    DialogBase(QWidget * parent, Qt::WindowFlags flags) : QDialog(parent, flags) {};
    virtual ~DialogBase() {};

    void move(int x, int y) { _positionExclusive = true; QDialog::move(x, y); };
    void move(const QPoint &point) { _positionExclusive = true; QDialog::move(point); };

    bool getPositionExclusive() const { return _positionExclusive; };
    void setPositionExclusive(bool posExclusive) { _positionExclusive = posExclusive; };

private:
    bool _positionExclusive;
};

#include "CWidgetBase.h"
template <class TClass> class Dialog : public DialogBase
{
public:
   inline Dialog(QWidget * parent = NULL, const char * name = NULL, bool modal = true, Qt::WindowFlags flags = 0)
       : DialogBase(parent, flags)
   {
      if (name != NULL) {
         setObjectName(name);
      }
      setModal(modal);
      _ui.setupUi(this);
   };
   virtual ~Dialog()
   {
   };
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   inline virtual void changeEvent(QEvent * event )
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      DialogBase::changeEvent(event);
   };
#endif

   inline virtual void languageChange()
   {
      _ui.retranslateUi(this);
   };
protected:
   TClass _ui;
public:
   inline TClass & ui()
   {
      CWidgetBase::CheckThread();
      return _ui;
   };
};

#endif // _dialog_h_



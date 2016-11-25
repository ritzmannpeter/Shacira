
#ifndef _cpublicdialog_h_
#define _cpublicdialog_h_

#ifndef QT4

#include <qdialog.h>
#include "cwidgetbase.h"

class cPublicDialog : public QDialog
{
   Q_OBJECT

public:
   cPublicDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, WIDGET_FLAGS_TYPE f = 0)
#ifdef QT4
      : QDialog(parent, f)
#else
      : QDialog(parent, name, modal, f)
#endif
   {
#ifdef QT4
      if (name != NULL) {
         setObjectName(name);
      }
      setModal(modal);
      setWindowFlags(f);
#endif
      _Result = actionProceed;
   };
   virtual ~cPublicDialog()
   {
   };
   void SetWFlags(WIDGET_FLAGS_TYPE f)
   {
#ifdef QT4
      setWindowFlags(f);
#else
      setWFlags(f);
#endif
   };
   ULONG_T Result()
   {
      return _Result;
   };
   void SetResult(ULONG_T result)
   {
      _Result = result;
   };

public slots:
   void Accept()
   {
      accept();
   };
   void Reject()
   {
      reject();
   };
   void Done(QDialog::DialogCode result)
   {
      done(result);
   };
private:
   ULONG_T _Result;
};

#endif

#endif



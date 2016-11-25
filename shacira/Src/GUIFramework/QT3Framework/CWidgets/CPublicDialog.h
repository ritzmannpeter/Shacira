
#ifndef _cpublicdialog_h_
#define _cpublicdialog_h_

#include <qdialog.h>
#include "cwidgetbase.h"

class cPublicDialog : public QDialog
{
   Q_OBJECT

public:
   cPublicDialog(QWidget * parent = 0, const char * name = 0, bool modal = FALSE, WFlags f = 0)
      : QDialog(parent, name, modal, f)
   {
      _Result = actionProceed;
   };
   virtual ~cPublicDialog()
   {
   };
   void SetWFlags(WFlags f)
   {
      setWFlags(f);
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



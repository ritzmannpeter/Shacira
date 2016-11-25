
#ifndef MEMVIEWIMPL_H
#define MEMVIEWIMPL_H

#include "Generated/memview.h"
#include "memory.h"
#include "qtimer.h"

class MemViewImpl : public MemView
{
    Q_OBJECT

public:
   MemViewImpl( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
   ~MemViewImpl();
public slots:
   virtual void dataChange();
   virtual void ShowMem();
   virtual void ChangeValue();
private:
   Memory _Memory;
   QTimer * _RefreshTimer;
};

#endif // MEMVIEWIMPL_H

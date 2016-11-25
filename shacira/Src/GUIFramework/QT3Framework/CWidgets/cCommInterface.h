
#ifndef _ccomminterface_h
#define _ccomminterface_h

#include "cWidgetComm.h"

class cCommInterface : public cWidgetComm
{
public:
   cCommInterface();
   virtual ~cCommInterface();
   virtual void GUIEvent(QEvent * e);
};

#endif


#ifndef _cviewinterface_h_
#define _cviewinterface_h_

#include "CWidgetBase.h"
#include "Client/Adapters/cDataControl.h"
#include "Client/Adapters/cEventControl.h"

class cDataView: public cDataControl
{
private:
   CWidgetBase * _View;
   VAR_REF_PTR _VarRef;
   ULONG_T _Id;
public:
   cDataView(CWidgetBase * view, VAR_REF_PTR var_ref, ULONG_T id);
   virtual ~cDataView();
   VAR_REF_PTR VarRef() const {return _VarRef;};
   virtual void NewValue(CONST_STRING_T value, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size, ULONG_T data_set); 
   virtual void NewValue(BUF_T buf, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size, ULONG_T data_set);
   virtual void * Widget() const;
   virtual STRING_T Name() const;
};

class cEventView: public cEventControl
{
private:
   CWidgetBase * _View;
public:
   cEventView(CWidgetBase * view);
   virtual ~cEventView();
   virtual void Object(TRANSIENT_OBJECT_PTR); 
};

#endif



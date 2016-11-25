

/// PR 28.01.05 - replaced SetControl(..) by AddControl(...)
/// PR 07.02.06 - extended new value interfaces with data_set
/// PR 30.09.14 - dangling link problem resolved in cVarRef.cpp

#include "cViewInterface.h"

#ifndef QT_PLUGIN

// Data Views

cDataView::cDataView(CWidgetBase * view, VAR_REF_PTR var_ref, ULONG_T id) :
   cDataControl(var_ref), _View(view), _VarRef(var_ref)
{
   _Id = id;
   _VarRef->AddControl(this);
}

cDataView::~cDataView()
{
}

void cDataView::NewValue(CONST_STRING_T value, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
   if (_View != NULL) {
      try {
         _View->PostNewValue(value, _Id, time_offset, data_type, size, data_set);
      } catch(cError & e) {
         CWidgetBase::WidgetError("%s\n", e.ErrMsg().c_str());
      } catch(...) {
         CWidgetBase::WidgetError("unhandled exception while setting new value\n");
      }
   }
}

void cDataView::NewValue(BUF_T buf, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
   if (_View != NULL) {
      try {
         _View->PostNewBuf(buf, _Id, time_offset, data_type, size, data_set);
      } catch(cError & e) {
         CWidgetBase::WidgetError("%s\n", e.ErrMsg().c_str());
      } catch(...) {
         CWidgetBase::WidgetError("unhandled exception while setting new value\n");
      }
   }
}

void * cDataView::Widget() const
{
   return _View;
}

STRING_T cDataView::Name() const
{
   return CONST_STRING(_View->Name());
}

// Event Views

cEventView::cEventView(CWidgetBase * view) :
   _View(view)
{
}

cEventView::~cEventView()
{
}

void cEventView::Object(TRANSIENT_OBJECT_PTR object)
{
   if (_View != NULL) {
      try {
         _View->PostNewObject(object);
      } catch(cError & e) {
         CWidgetBase::WidgetError("%s\n", e.ErrMsg().c_str());
      } catch(...) {
         CWidgetBase::WidgetError("unhandled exception while setting new value\n");
      }
   }
}

#endif

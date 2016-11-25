
/// PR 03.02.06 - now retrieving and setting new value also after reference initialisation
///               because its no more done ther

#include "CIndReqValue.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CIndReqValue, \
                   ICON_SET("label"), \
                   "input widget that maps integral numeric data to texts")
#endif


CIndReqValue::CIndReqValue(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f) :
                           CReqValue(parent, name, f) 
{
   _IdentValue = 0;
   _IndexBase = NULL;
   _Index1 = -1;
   _Index2 = -1;
   _Index3 = -1;
   _Index4 = -1;
}

CIndReqValue::~CIndReqValue() 
{
}

void CIndReqValue::mouseReleaseEvent(QMouseEvent * e)
{
   CReqValue::mouseReleaseEvent(e);
}

void CIndReqValue::mousePressEvent(QMouseEvent * e)
{
   CReqValue::mousePressEvent(e);
}

void CIndReqValue::focusInEvent ( QFocusEvent * e)
{
   CReqValue::focusInEvent (e);
}

void CIndReqValue::focusOutEvent ( QFocusEvent * e)
{
   CReqValue::focusOutEvent (e);
}

void CIndReqValue::keyReleaseEvent ( QKeyEvent * e )
{
   CReqValue::keyReleaseEvent(e);
}

void CIndReqValue::NewIndex(int i1, int i2, int i3, int i4)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Index1 = i1;
   _Index2 = i2;
   _Index3 = i3;
   _Index4 = i4;
   if (_IndexBase != NULL) {
      _IndexBase->Configure(_BaseNameValue,
                            _VarSpec,
                            _VarRef,
                            _VarView,
                            0,
                            _Index1, _Index2, _Index3, _Index4);
      _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CIndReqValue::NewVarName(const QString VarName, int i1, int i2, int i3, int i4)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Index1 = i1;
   _Index2 = i2;
   _Index3 = i3;
   _Index4 = i4;
   if ((_IndexBase != NULL) && !VarName.isEmpty()) {
      _IndexBase->Configure(VarName,
                            _VarSpec,
                            _VarRef,
                            _VarView,
                            0,
                            _Index1, _Index2, _Index3, _Index4);
      _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
   }
WMETHOD_VOID_EPILOG
#endif
}


// GUI related virtual methods

void CIndReqValue::View()
{
   CReqValue::View();
}

// CCS related virtual methods

void CIndReqValue::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);

   _IndexBase = new cIndexBase(this);
WMETHOD_VOID_EPILOG
#endif
}

void CIndReqValue::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (id == 0) {
      CReqValue::CCSNewValue(value, id, time_offset, data_type, size);
      emit ValueChanged(value, _IdentValue, _Index1, _Index2, _Index3, _Index4);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CIndReqValue::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
   CReqValue::CCSNewValue(buf, id, time_offset, data_type, size);
}

void CIndReqValue::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
   CReqValue::CCSEvent(object);
}

// cIndexBase Implementation

REF_MAP_T cIndexBase::_Refs;
ACTREF_MAP_T cIndexBase::_ActRefs;

cIndexBase::cIndexBase(CWidgetBase * base)
{
   _BaseWidget = base;
}

cIndexBase::~cIndexBase()
{
}

#ifdef QT4
void cIndexBase::Configure(const QString & base_name,
                           QByteArray & varSpec,
                           VAR_REF_PTR & var_ref,
                           DATA_VIEW_PTR & view,
                           ULONG_T id,
                           ULONG_T i1,
                           ULONG_T i2,
                           ULONG_T i3,
                           ULONG_T i4)
#else
void cIndexBase::Configure(const QString & base_name,
                           QCString & varSpec,
                           VAR_REF_PTR & var_ref,
                           DATA_VIEW_PTR & view,
                           ULONG_T id,
                           ULONG_T i1,
                           ULONG_T i2,
                           ULONG_T i3,
                           ULONG_T i4)
#endif
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString qvar_ref_spec;
   if (i4 != -1) {
      qvar_ref_spec = QString("%1[%2][%3][%4][%5]").arg(base_name).arg(i1).arg(i2).arg(i3).arg(i4);
   } else if (i3 != -1) {
      qvar_ref_spec = QString("%1[%2][%3][%4]").arg(base_name).arg(i1).arg(i2).arg(i3);
   } else if (i2 != -1) {
      qvar_ref_spec = QString("%1[%2][%3]").arg(base_name).arg(i1).arg(i2);
   } else if (i1 != -1) {
      qvar_ref_spec = QString("%1[%2]").arg(base_name).arg(i1);
   } else {
      qvar_ref_spec = base_name;
   }
   REF_T * act_ref = ActRef(view);
   if (act_ref != NULL) {
      act_ref->var_ref->RemoveControl(view);
   }

   REF_T * ref = Ref(qvar_ref_spec);
   if (ref != NULL) {
      var_ref = ref->var_ref;
      view = ref->view;
      var_ref->AddControl(view);
   } else {
      _BaseWidget->CCSInitializeVarRef(CONST_STRING(qvar_ref_spec), var_ref, view, id, false);
      ref = AllocRef(var_ref, view, id);
      AddRef(qvar_ref_spec, ref);
   }

   if (var_ref != NULL) {
      STRING_T value;
      var_ref->GetValue(value);
      varSpec = CONST_STRING(qvar_ref_spec);
      _BaseWidget->CCSNewValue(value.c_str(), ref->id, 0,
                               var_ref->DataType(),
                               var_ref->ValueSize());
   }

   AddActRef(view, ref);
WMETHOD_VOID_EPILOG
#endif
}

REF_T * cIndexBase::AllocRef(VAR_REF_PTR var_ref, DATA_VIEW_PTR view, ULONG_T id)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   REF_T * ref = (REF_T*)cSystemUtils::Alloc(sizeof(*ref));
   ref->var_ref = var_ref;
   ref->view = view;
   ref->id = id;
   return ref;
WMETHOD_RC_EPILOG(NULL)
#else
   return NULL;
#endif
}

REF_T * cIndexBase::Ref(const QString & ref_spec)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   REF_MAP_T::const_iterator i = _Refs.find(ref_spec);
   if (i == _Refs.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
WMETHOD_RC_EPILOG(NULL)
#else
   return NULL;
#endif
}

void cIndexBase::AddRef(const QString & ref_spec, REF_T * ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (ref->var_ref == NULL) {
      return;
   }
   _Refs[ref_spec] = ref;
WMETHOD_VOID_EPILOG
#endif
}

REF_T * cIndexBase::ActRef(void * view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (view == NULL) return NULL;

   ACTREF_MAP_T::const_iterator i = _ActRefs.find(view);
   if (i == _ActRefs.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
WMETHOD_RC_EPILOG(NULL)
#else
   return NULL;
#endif
}

void cIndexBase::AddActRef(void * view, REF_T * ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (ref->var_ref == NULL) {
      return;
   }
   _ActRefs[view] = ref;
WMETHOD_VOID_EPILOG
#endif
}


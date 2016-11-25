
#include "dframe.h"

DFrame::DFrame(QWidget* parent, const char* name, WFlags f)
   : CFrame(parent, name)
{
}

DFrame::~DFrame()
{
}


void DFrame::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QFrame::mousePressEvent(e);
   }
}


void DFrame::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QFrame::mouseReleaseEvent(e);
   }
}


void DFrame::paintEvent(QPaintEvent * e)
{
   CFrame::paintEvent(e);
}


// GUI related virtual methods
void DFrame::View()
{
}

#ifdef actually_not_reimplemented

void DFrame::Notification(ULONG_T event_code)
{
}

void DFrame::RefreshData()
{
}

void DFrame::GUIEvent(ULONG_T signal, QWidget * sender)
{
}

#endif


// CCS related virtual methods
void DFrame::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}


void DFrame::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void DFrame::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
}

void DFrame::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}






#include "CProtocolWindow.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CProtocolWindow, \
                   ICON_SET("designer_label"), \
                   "protocol output widget")
#endif

#ifndef QT_PLUGIN
#include "System/Objects/cProtocol.h"
#endif

CProtocolWindow::CProtocolWindow(QWidget * parent, const char * name, WFlags f)
   : QTextEdit(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
   setReadOnly(true);
   setTextFormat(Qt::PlainText);
}

CProtocolWindow::~CProtocolWindow() 
{
}

void CProtocolWindow::Clear()
{
   clear();
}

void CProtocolWindow::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QTextEdit::mousePressEvent(e);
   }
}

void CProtocolWindow::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QTextEdit::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CProtocolWindow::View()
{
}

// CCS related virtual methods

void CProtocolWindow::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CProtocolWindow::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CProtocolWindow::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CProtocolWindow::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   UCHAR_T object_type = object->get_Type();
   if (object_type == OT_PROTOCOL) {
      cProtocol * protocol = (cProtocol*)object;
      QString object_name = protocol->Source()->get_Name().c_str();
      if (!_ObjectNameValue.isNull() &&
          (_ObjectNameValue.length() > 0) &&
          (strcmp(CONST_STRING_T(object_name), (const char *)_ObjectNameValue) != 0)) {
         return;
      }
      QString msg = protocol->Msg().c_str();
      int size = text().length();
      if (size > 0x2000) {
         clear();
      }
//      append(msg);
      QString content = (const char*)text();
      content += msg;
      setText(content);
      moveCursor(MoveEnd, false);
   }
WMETHOD_VOID_EPILOG
#endif
}


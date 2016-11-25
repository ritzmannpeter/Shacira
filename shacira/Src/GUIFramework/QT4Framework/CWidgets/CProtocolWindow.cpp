
#include "CProtocolWindow.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CProtocolWindow, \
                   ICON_SET("listview"), \
                   "protocol output widget")
#endif

#ifndef QT_PLUGIN
#include "System/Objects/cProtocol.h"
#endif

CProtocolWindow::CProtocolWindow(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QTextEdit(parent),
#else
   : QTextEdit(parent, name),
#endif
     CWidgetBase(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   setReadOnly(true);
#ifdef QT4
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
#else
   setTextFormat(Qt::PlainText);
#endif
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
          (object_name != _ObjectNameValue)) {
         return;
      }
      QString msg = protocol->Msg().c_str();
#ifdef QT4
      int size = toPlainText().length();
#else
      int size = text().length();
#endif
      if (size > 0x2000) {
         clear();
      }
#ifdef QT4
      QString content = toPlainText();
#else
      QString content = (const char*)text();
#endif
      content += msg;
      setText(content);
#ifdef QT4
      textCursor().movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
#else
      moveCursor(MoveEnd, false);
#endif
   }
WMETHOD_VOID_EPILOG
#endif
}


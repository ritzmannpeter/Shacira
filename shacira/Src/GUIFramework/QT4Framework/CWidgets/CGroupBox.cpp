
#include "CGroupBox.h"

#ifdef QT4
#include <QLayout>
#endif

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CGroupBox, \
                   ICON_SET("groupbox"), \
                   "group box widget")
#endif

CGroupBox::CGroupBox(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QGroupBox(parent),
#else
   : QGroupBox(parent, name),
#endif
     CWidgetBase(this) 
{
#ifdef QT4
   setObjectName(name);
   setProperty("titleActive", false);
#endif
   CONSTRUCT_WIDGET
#ifdef QT4
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
#else
   setFrameStyle(QGroupBox::Panel | QGroupBox::Raised);
   setLineWidth(1);
#endif
}


CGroupBox::~CGroupBox() 
{
}

void CGroupBox::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QGroupBox::mousePressEvent(e);
   }
}

void CGroupBox::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QGroupBox::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CGroupBox::View()
{
}

// CCS related virtual methods

void CGroupBox::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CGroupBox::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CGroupBox::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CGroupBox::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

#ifdef QT4

int CGroupBox::insideMargin() const
{
   QLayout * layout = this->layout();
   int left = 0;
   
   if (layout) {
      int top;
      int right; 
      int bottom;
      layout->getContentsMargins(&left, &top, &right, &bottom);
   }

   return left;
}

int CGroupBox::insideSpacing() const
{
   QLayout * layout = this->layout();

   return layout ? layout->spacing() : 0;
}

void CGroupBox::setTitle(const QString & title)
{
    setProperty("titleActive", title.isEmpty() ? false : true);
    QGroupBox::setTitle(title);
}

#endif

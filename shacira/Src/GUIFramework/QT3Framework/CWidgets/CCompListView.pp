
#ifndef _ccomplistview_h_
#define _ccomplistview_h_

#include "CListView.h"

#ifndef QT_PLUGIN
class cVarGroups;
#endif

/**!
  * @brief A widget to display the state of different datasets.
  * <p>
  */
class SH_QT_WIDGET_PLUGIN_EXPORT CCompListView : public CListView
{
// start 2i generic widget definition

   Q_OBJECT

   // common property definitions of C widgets
public:
   /// end of common property definitions of C widgets

   // further widget specific properties
   PROPERTY_2i(QCString,GroupName0)
   PROPERTY_2i(QCString,GroupName1)
   PROPERTY_2i(QCString,GroupName2)
   PROPERTY_2i(QCString,GroupName3)
   PROPERTY_2i(QCString,GroupName4)
   PROPERTY_2i(QCString,GroupName5)
   PROPERTY_2i(QCString,GroupName6)
   PROPERTY_2i(QCString,GroupName7)
   PROPERTY_2i(QCString,GroupName8)
   PROPERTY_2i(QCString,GroupName9)
   PROPERTY_2i(QCString,GroupName10)
   PROPERTY_2i(QCString,GroupName11)
   PROPERTY_2i(QCString,GroupName12)
   PROPERTY_2i(QCString,GroupName13)
   PROPERTY_2i(QCString,GroupName14)
   PROPERTY_2i(QPixmap,DefaultIcon)
   PROPERTY_2i(QPixmap,Icon0)
   PROPERTY_2i(QPixmap,Icon1)
   PROPERTY_2i(QPixmap,Icon2)
   PROPERTY_2i(QPixmap,Icon3)
   PROPERTY_2i(QPixmap,Icon4)
   PROPERTY_2i(QPixmap,Icon5)
   PROPERTY_2i(QPixmap,Icon6)
   PROPERTY_2i(QPixmap,Icon7)
   PROPERTY_2i(QPixmap,Icon8)
   PROPERTY_2i(QPixmap,Icon9)
   PROPERTY_2i(QPixmap,Icon10)
   PROPERTY_2i(QPixmap,Icon11)
   PROPERTY_2i(QPixmap,Icon12)
   PROPERTY_2i(QPixmap,Icon13)
   PROPERTY_2i(QPixmap,Icon14)
   // end of widget specific properties

public:

   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

   virtual void Print(STREAM_T stream)
   {
   }
   virtual void Print(PAINTER_T painter)
   {
   }

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   void RefreshComparison();
   void RefreshShadowComparison();
   virtual void Print()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CListView::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CListView::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CListView::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CListView::keyReleaseEvent(e);
   };

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange();

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

protected slots:
    virtual void languageChange();

public:
   CCompListView(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~CCompListView();
private:
   QPixmap GroupPixmap(const QString & group_name);
   QString VarRefText(const QString & varRefSpec);
   void FillListView();

#ifndef QT_PLUGIN
   cVarGroups * _varGroups;
#endif
};

#endif




#ifndef _cdirectory_h_
#define _cdirectory_h_

#include "CListView.h"

/**!
  * @brief A widget to display the contents of a directory.
  * <p>
  */

class FileItem;

class _CWIDGET_EXPORT_ CDirectory : public CListView
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QByteArray,Pattern)
   VAR_REF_2i(SearchPath)
   VAR_REF_2i(NumberOfPatternFiles)
   VAR_REF_2i(SelectedFile)
   VAR_REF_2i(MaxNoOfPatternFiles)

   PROPERTY_2i(bool,Col0WithFileName)

   PROPERTY_2i(QByteArray,Col0Ref)
   PROPERTY_2i(QByteArray,Col1Ref)
   PROPERTY_2i(QByteArray,Col2Ref)
   PROPERTY_2i(QByteArray,Col3Ref)
   PROPERTY_2i(QByteArray,Col4Ref)
   PROPERTY_2i(QByteArray,Col5Ref)

   PROPERTY_2i(QString,Col0Text)
   PROPERTY_2i(QString,Col1Text)
   PROPERTY_2i(QString,Col2Text)
   PROPERTY_2i(QString,Col3Text)
   PROPERTY_2i(QString,Col4Text)
   PROPERTY_2i(QString,Col5Text)

   PROPERTY_2i(int,Col0Width)
   PROPERTY_2i(int,Col1Width)
   PROPERTY_2i(int,Col2Width)
   PROPERTY_2i(int,Col3Width)
   PROPERTY_2i(int,Col4Width)
   PROPERTY_2i(int,Col5Width)

   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

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
   virtual void Setup();
   virtual void ActivateRefresh(bool refresh) { _RefreshActivated = refresh; };

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   void SearchPathChange(QString search_path);
   void RefreshDirectory(QString full_file_name = "");
   void RefreshDirectory(ULONG_T button_result);
   void SelectionChanged();
   void SlotClearSelection();

signals:
   void FileSelected(QString path);

public:
   CDirectory(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CDirectory();
   BOOL_T getSelectedFile(QString & sValue);

private:
   void InitWidget();
   FileItem * AddFile(const QString & path, const QString & file_name, ULONG_T index);
   void GetVarRef(CONTEXT_PTR context, const QString & var_spec, QString & value);
   void AdjustColWidth();

   QString _SearchPath;           // path to search for files
   int m_iMaxNoOfPatternFiles;
   ListViewItem * _qlvWrittenFileItem;
   BOOL_T _Refresh;
   BOOL_T _RefreshActivated;
};

#endif



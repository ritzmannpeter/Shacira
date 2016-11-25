
/// PR 02.11.05 - edded variable reference NumberOfPatternFiles

#include "CDirectory.h"
#include <qheader.h>
#include <qvaluevector.h>

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ViewWidget, \
                   CDirectory, \
                   ICON_SET("designer_listview"), \
                   "list box widget to display contents of directories")
#endif

#include <qdatetime.h>
#include <qstring.h>
#include <qdir.h>

class FileItem : public QListViewItem
{
public:
   FileItem(QListView * parent, ULONG_T index, const QString & file) :
      QListViewItem(parent), _Index(index), _File(file), 
      m_iYear(0), m_iMonth(0), m_iDay(0), m_iHour(0), m_iMinute(0)
   {
      memset(&_isQtCompare, true, sizeof(_isQtCompare));
   };
   virtual ~FileItem()
   {
   };
   int Index()
   {
      return _Index;
   };
   QString File()
   {
      return _File;
   };

   //// provide Date to sort colmn 0 and to avoid parsing from text that is shown in the column
   void setDate(int iYear, int iMonth, int iDay, int iHour, int iMinute)
   {
        m_iYear = iYear;
        m_iMonth = iMonth;
        m_iDay = iDay;
        m_iHour = iHour; 
        m_iMinute = iMinute;
   }

   void setQtCompare(int column, bool isQtCompare) { _isQtCompare[column] = isQtCompare; };

   // for every column
   bool isColored(int column) {
      return column >= 0 && column < (int)_colors.count() && _colors[column].isValid() == true;
   }
   void clearColor(int column) {
      if (column >= 0 && column < (int)_colors.count())
         _colors[column] = QColor();
   }
   QColor getColor(int column) {
      return (column >= 0 && column < (int)_colors.count()) ? _colors[column] : QColor();
   }
   void setColor( int column, const QColor &color ) { 
      if (column >= 0 && color.isValid()) {
         if (column >= (int)_colors.count())
            _colors.resize(column+1);
         _colors[column] = color;
      }
   }

   // compare dates not strings at sorting with col 0
   virtual int compare(QListViewItem *i, int col, bool ascending) const
   {
      int iRet = 0;  
      if (_isQtCompare[col])
      {
          iRet = QListViewItem::compare(i, col, ascending);
          //iRet = key(col, ascending).compare(i->key(col, ascending));          
      }
      else
      { 
          if (i != NULL)
          {
              FileItem* pFileItem = reinterpret_cast<FileItem*>(i);
              QString qsTxt1 = text(col);
              QDate qD1(m_iYear, m_iMonth, m_iDay);
              QTime qT1(m_iHour, m_iMinute);

              QString qsTxt2 = i->text(col);          
              QDate qD2(pFileItem->m_iYear, pFileItem->m_iMonth, pFileItem->m_iDay);
              QTime qT2(pFileItem->m_iHour, pFileItem->m_iMinute);
    
              int iDays = qD1.daysTo(qD2);
              int iSecs = qT1.secsTo(qT2);
              if (iDays > 0) 
              {
                  iRet = -1; 
              }
              else if (iDays < 0)
              {
                  iRet = +1;
              }
              else if (iSecs > 0)
              {
                   iRet = -1;  
              }
              else if (iSecs < 0)
              {
                  iRet = +1;
              }
              else if (iSecs == 0 && iDays == 0)
              {
                  iRet = 0;
              }
          }
      }
      return iRet;
   }

protected:
   virtual void paintCell ( QPainter * p, const QColorGroup & cg, int column, int width, int align )
   {
      if (isColored(column)) {
         QColorGroup mycg = cg;
         mycg.setColor(QColorGroup::Text, getColor(column));
         QListViewItem::paintCell(p, mycg, column, width, align);
      } else {
         QListViewItem::paintCell(p, cg, column, width, align);
      }
   }
private:
   QString _File;
   int _Index;
   QValueVector<QColor> _colors;
   int m_iYear; 
   int m_iMonth; 
   int m_iDay;
   int m_iHour; 
   int m_iMinute;
   bool _isQtCompare[8];
};

CDirectory::CDirectory (QWidget * parent, const char * name, WFlags f)
   : CListView(parent, name, f),
     _Refresh(false),
     _RefreshActivated(true)
{
   CONSTRUCT_WIDGET

   _SearchPathRef = NULL;
   _SearchPathView = NULL;

   _NumberOfPatternFilesRef = NULL;
   _NumberOfPatternFilesView = NULL;

   _SelectedFileRef = NULL;
   _SelectedFileView = NULL;

   _Col0WidthValue = 0;
   _Col1WidthValue = 0;
   _Col2WidthValue = 0;
   _Col3WidthValue = 0;
   _Col4WidthValue = 0;
   _Col5WidthValue = 0;

   _MaxNoOfPatternFilesRef = NULL;
   _MaxNoOfPatternFilesView = NULL;
   m_iMaxNoOfPatternFiles = -1;
   _Col0WithFileNameValue = false;
   _qlvWrittenFileItem = NULL;
   header()->setMovingEnabled(false);
   setSorting(0, false);
#ifndef QT_PLUGIN
   connect(this, SIGNAL(selectionChanged()), this, SLOT(SelectionChanged()));
#endif

   header()->setMovingEnabled(false);
}

CDirectory::~CDirectory ( ) 
{
}

void CDirectory::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CListView::mousePressEvent(e);
   }
}

void CDirectory::mouseReleaseEvent(QMouseEvent * e)
{
   CListView::mouseReleaseEvent(e);
}

void CDirectory::SearchPathChange(QCString search_path)
{
   _SearchPath = search_path;
   RefreshDirectory();
}

void CDirectory::RefreshDirectory(QCString full_file_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_SelectedFileRef != NULL) {
      _SelectedFileRef->SetValue("");
   }

   QString WrittenFileName = "";
   QString WrittenPath = "";
   if (!full_file_name.isEmpty() && !full_file_name.isNull()) {
      WrittenFileName = cFileSystemUtils::FileName(CONST_STRING(full_file_name)).c_str();
      WrittenPath = cFileSystemUtils::DirName(CONST_STRING(full_file_name)).c_str();
   }

   LONG_T index = 1;
   QString path;
   QString pattern;
   if (!_SearchPath.isEmpty()) {
      path = cFileSystemUtils::FullPath(CONST_STRING(_SearchPath)).c_str();
      QString qsLastChar = path.right(1);
      if ((qsLastChar.find('/') != -1) || (qsLastChar.find('\\') != -1)) {
         path.remove(path.length()-1, 1); // remove last characeter
      }
   } else {
      path = cFileSystemUtils::FullPath("").c_str();
   }
   if (!_PatternValue.isEmpty()) {
      pattern = (const char*)_PatternValue;
   }

   _qlvWrittenFileItem = NULL;

   clear();

   QDir qMDatDir(path, pattern, QDir::Time, QDir::Files|QDir::Readable);  
   if (qMDatDir.exists()) {
      int iCount = qMDatDir.count();
      if (iCount > 0 && m_iMaxNoOfPatternFiles != 0) {
         QStringList qslFileNames = qMDatDir.entryList();
         for (QStringList::Iterator iter = qslFileNames.begin(); iter != qslFileNames.end(); ++iter) {
            FileItem * file_item = AddFile(path, *iter, index);
            QString FileName(*iter);
            if ((FileName == WrittenFileName) && (path == WrittenPath)) {
               _qlvWrittenFileItem = file_item;
            }
            if (index == m_iMaxNoOfPatternFiles) {
               break;
               index++;
            }
         }
      }
   }
   AdjustColWidth();
   sort();
   int numberOfChild = childCount();

   if (_NumberOfPatternFilesRef != NULL) {
      _NumberOfPatternFilesRef->SetValue((SHORT_T)numberOfChild);
   }

   if (numberOfChild > 0) {
      QListViewItem * qlvItem = NULL;

      if (!full_file_name.isEmpty() && !full_file_name.isNull()) {
         if (_qlvWrittenFileItem == NULL)
            return; // filename parameter not found therefor no item selected
         else
            qlvItem = _qlvWrittenFileItem;
      }
      else {
         qlvItem = firstChild();
      }

      if (selectionMode() == QListView::Single) {
         setSelected(qlvItem, true);
         setContentsPos(0, qlvItem->itemPos());
      }
      else {
         setCurrentItem(qlvItem);
         setSelectionAnchor(qlvItem);
         setSelected(qlvItem, true);
         setContentsPos(0, qlvItem->itemPos());
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CDirectory::RefreshDirectory(ULONG_T button_result)
{
//WMETHOD_PROLOG
   if (button_result == actionProceed) {
      RefreshDirectory();
   }
//WMETHOD_VOID_EPILOG
}

void CDirectory::SelectionChanged()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   FileItem * file_item = (FileItem*)currentItem();
   if ((file_item != NULL) && file_item->isSelected()) {
      QString sValue = file_item->File();
      emit FileSelected(CONST_STRING(sValue));
      if (_SelectedFileRef != NULL) {
         _SelectedFileRef->SetValue(CONST_STRING(sValue));
      }
      EmitGUISignal(SIG_LIST_SELECTED);
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CDirectory::View()
{
   if (_Refresh && _RefreshActivated) {
      _Refresh = false;
      RefreshDirectory();
   }
}

void CDirectory::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   setColumnText(0, _Col0TextValue);
   if (!_Col1RefValue.isEmpty() || _Col0WithFileNameValue) {
      setColumnText(1, _Col1TextValue);
   }
   if (!_Col2RefValue.isEmpty()) {
      setColumnText(2, _Col2TextValue);
   }
   if (!_Col3RefValue.isEmpty()) {
      setColumnText(3, _Col3TextValue);
   }
   if (!_Col4RefValue.isEmpty()) {
      setColumnText(4, _Col4TextValue);
   }
   if (!_Col5RefValue.isEmpty()) {
      setColumnText(5, _Col5TextValue);
   }
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CDirectory::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CListView::CCSSetContext(node, context); // id 0
   CCSInitializeVarRef(_SearchPathSpec, _SearchPathRef, _SearchPathView, 1);
   CCSInitializeVarRef(_NumberOfPatternFilesSpec, _NumberOfPatternFilesRef, _NumberOfPatternFilesView, 2);
   CCSInitializeVarRef(_SelectedFileSpec, _SelectedFileRef, _SelectedFileView, 3);
   CCSInitializeVarRef(_MaxNoOfPatternFilesSpec, _MaxNoOfPatternFilesRef, _MaxNoOfPatternFilesView, 4);

   InitWidget();
WMETHOD_VOID_EPILOG
#endif
}

void CDirectory::Setup()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Refresh && _RefreshActivated) {
      _Refresh = false;
      RefreshDirectory();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CDirectory::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
      CListView::CCSNewValue(value, id, time_offset, data_type, size);
      break;
   case 1:
   {
       // toggle faster from foreground to background 
       QString qcsNewSearchPath(value);
       if (!qcsNewSearchPath.isEmpty() && (qcsNewSearchPath != (CONST_STRING_T)_SearchPath))
       {
          _SearchPath = value;
          _Refresh = true;
          Notify(VIEW_DATA);
       }
       break;
   }
   case 4:
   {
       int iValue = atoi(value);
       if (iValue != m_iMaxNoOfPatternFiles)
       {
           m_iMaxNoOfPatternFiles = iValue; 
           _Refresh = true;
           Notify(VIEW_DATA);
       }
   }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CDirectory::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size)
{
}

void CDirectory::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CDirectory::InitWidget()
{
//WMETHOD_PROLOG
   addColumn(_Col0TextValue);
   if (!_Col1RefValue.isEmpty() || _Col0WithFileNameValue) {
      addColumn(_Col1TextValue);
   }
   if (!_Col2RefValue.isEmpty()) {
      addColumn(_Col2TextValue);
   }
   if (!_Col3RefValue.isEmpty()) {
      addColumn(_Col3TextValue);
   }
   if (!_Col4RefValue.isEmpty()) {
      addColumn(_Col4TextValue);
   }
   if (!_Col5RefValue.isEmpty()) {
      addColumn(_Col5TextValue);
   }
//   WMETHOD_VOID_EPILOG
}

FileItem * CDirectory::AddFile(const QString & path, const QString & file_name, ULONG_T index)
{
   FileItem * item = NULL;
   QString file_path = path + QDir::separator() + file_name;
   QFileInfo file_info(file_path);
   if (!file_info.exists()) {
      return NULL;
   }
   QDateTime file_date = file_info.lastModified();
   QString file_time = file_date.toString("dd.MM.yyyy hh:mm  ");
   QString day = file_date.toString("dd");
   QString month = file_date.toString("MM");
   QString year = file_date.toString("yyyy");
   QString hour = file_date.toString("hh");
   QString minute = file_date.toString("mm");
   item = new FileItem(this, index, file_path);
   if (item != NULL) {
      UCHAR_T ColOffset = 0;
      QString qsFileName(file_name);
      QString qsFileNameWithoutExt(qsFileName);
      SHORT_T ExtPos = qsFileName.findRev('.', -1);
      if (ExtPos != -1) {
         qsFileNameWithoutExt = qsFileName.left(ExtPos);
      }
      if (_Col0WithFileNameValue == true) {
         item->setText(0, qsFileNameWithoutExt);
         ColOffset = 1;
      }
      item->setDate(year.toInt(), month.toInt(), day.toInt(), 
                    hour.toInt(), minute.toInt());
      item->setText(0 + ColOffset, file_time);
      item->setQtCompare(0 + ColOffset, false);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      if (!_Col1RefValue.isEmpty() || !_Col2RefValue.isEmpty() ||
          !_Col3RefValue.isEmpty() || !_Col4RefValue.isEmpty() ||
          !_Col5RefValue.isEmpty()) {
         cContext * file_context = _Context->GetFileContext(CONST_STRING(file_path), true);
         QString value;
         if (file_context != NULL) {
             if (!_Col1RefValue.isEmpty()) {
                GetVarRef(file_context, _Col1RefValue, value);
                item->setText(1 + ColOffset, value);
             }
             if (!_Col2RefValue.isEmpty()) {
                GetVarRef(file_context, _Col2RefValue, value);
                item->setText(2 + ColOffset, value);
             }
             if (!_Col3RefValue.isEmpty()) {
                GetVarRef(file_context, _Col3RefValue, value);
                item->setText(3 + ColOffset, value);
             }
             if (!_Col4RefValue.isEmpty()) {
                GetVarRef(file_context, _Col4RefValue, value);
                item->setText(4 + ColOffset, value);
             }
             if (!_Col5RefValue.isEmpty()) {
                GetVarRef(file_context, _Col5RefValue, value);
                item->setText(5 + ColOffset, value);
             }
             delete file_context;
         }
      }
WMETHOD_RC_EPILOG(item)
#endif
      AdjustItemHeight(item);
   }
   return item;
}

void CDirectory::GetVarRef(CONTEXT_PTR context, const QString & var_spec, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   value = "??";
   try {
      VAR_REF_PTR var_ref = context->VarRef(CONST_STRING(var_spec));
      if (var_ref != NULL) {
         STRING_T v;
         var_ref->GetValue(v);
         value = v.c_str();
      }
   } catch (cError & e) {
      ErrorPrintf("%s getting value of %s\n", (const char *)e, CONST_STRING(var_spec));
   } catch (...) {
      ErrorPrintf("unhandled exception getting value of %s\n", CONST_STRING(var_spec));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CDirectory::AdjustColWidth()
{
   ULONG_T cols = columns();
   if (_Col0WidthValue != 0 && cols > 0) {
      setColumnWidth(0, _Col0WidthValue);
   }
   if (_Col1WidthValue != 0 && cols > 1) {
      setColumnWidth(1, _Col1WidthValue);
   }
   if (_Col2WidthValue != 0 && cols > 2) {
      setColumnWidth(2, _Col2WidthValue);
   }
   if (_Col3WidthValue != 0 && cols > 3) {
      setColumnWidth(3, _Col3WidthValue);
   }
   if (_Col4WidthValue != 0 && cols > 4) {
      setColumnWidth(4, _Col4WidthValue);
   }
   if (_Col5WidthValue != 0 && cols > 5) {
      setColumnWidth(5, _Col5WidthValue);
   }
}

BOOL_T CDirectory::getSelectedFile(QString & sValue)
{
   BOOL_T bRet = false;
#ifndef QT_PLUGIN
   if (!_SelectedFileSpec.isNull() && !_SelectedFileSpec.isEmpty()) {
      if (_SelectedFileRef != NULL) {
         STRING_T v;
         _SelectedFileRef->GetValue(v);
         sValue = v.c_str();
         bRet = true;
      }
   }
#endif
   return bRet;
}

void CDirectory::SlotClearSelection()
{
   clearSelection();
   triggerUpdate();
}

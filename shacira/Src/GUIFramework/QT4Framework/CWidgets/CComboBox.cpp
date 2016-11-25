
/// PR 24.01.08 - second workaround for blocking Qt combo box
/// PR 09.07.07 - added localiazation concept for box items
///               when item texts are set using the new method SetItemText(index,text)
///               these values are stored and act as base for subsequent translations
///               executed in DelayedLanguageChange that calls the virtual method
///               TranslateItems.
///               TranslateItems tries to translate the stored item texts and updates
///               those texts in the widget.
///               Both new methods SetItemText(..) and TranslateItems(..) are virtual
///               and can be reimplemented.
/// PR 29.10.09 - moved _ItemStrings to heap

#include "CComboBox.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#ifdef QT4
SH_PLUGIN_REGISTER(InputWidget,
                   CComboBox, \
                   ICON_SET("combobox"), \
                   "combo box widget")
#else
SH2_PLUGIN_REGISTER(InputWidget,
                    CComboBox, \
                    ICON_SET("designer_combobox"), \
                    "combo box widget")
#endif
#endif

#include <qimage.h>
#include <qpixmap.h>
#include <qapplication.h>

#define MOUSEBUTTONPRESS    1
#define MOUSEBUTTONDBLCLICK 2
#define MOUSEBUTTONRELEASE  3
#define POPUP_OPEN          4

static char _State = 0;

#ifdef QT4

#include "qstandarditemmodel.h"

#else

static const unsigned char height24_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x3b, 0xcc, 0x97, 0xda, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x78, 0x00, 0x01, 0x0b, 0xce, 0xbd, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height32_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xd3, 0xe5, 0x12, 0x1a, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0xdc, 0x00,
    0x00, 0x00, 0xa0, 0x00, 0x01, 0xb0, 0x06, 0x62, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height40_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x28,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x3f, 0xb6, 0x90, 0x77, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x1e, 0x00,
    0x00, 0x00, 0xc8, 0x00, 0x01, 0xad, 0x40, 0x76, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char height48_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xd0, 0x33, 0x10, 0x81, 0x00, 0x00, 0x00,
    0x0c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0x60, 0x18, 0x59, 0x00,
    0x00, 0x00, 0xf0, 0x00, 0x01, 0x06, 0x94, 0x89, 0xfd, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

#endif

#ifdef QT4
CComboBox::CComboBox(QWidget * parent, const char * name)
   : QComboBox(parent),
#else
CComboBox::CComboBox(bool editable, QWidget * parent, const char * name)
   : QComboBox(editable, parent, name),
#endif
     CWidgetBase(this),
     _Input(this)
{
#ifdef QT4
   setObjectName(name);
#pragma message(__LOC__ "todo: combo box must be set non editable")
NOT_PORTED("not ported yet")
// like   setReadOnly(editable);
#endif
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _ButtonFuncRef = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _ValueFuncRef = NULL;
   _IncrementValue = 0;
   _ModeValue = SetIndex;
   _DisableParentValue = false;
   _PrevValue = QString();

   if (TOUCH_SCREEN_ACTIVE()) {
      _ItemHeightValue = Height38;
   } else {
      _ItemHeightValue = NormalHeight;
   }

   setMinimumHeight(getScaledHeight(this, 24));
#ifndef QT_PLUGIN
   connect(this, SIGNAL(activated(int)), this, SLOT(SelectionChanged()));
#endif
}

CComboBox::~CComboBox() 
{
}

void CComboBox::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QComboBox::mousePressEvent(e);
   }
}

void CComboBox::mouseReleaseEvent(QMouseEvent * e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QComboBox::mouseReleaseEvent(e);
   }
WMETHOD_VOID_EPILOG
#endif
}

/// reimplemented to clear events without doing any processing
bool CComboBox::event(QEvent * e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QEvent::Type event_type = e->type();

   if (event_type == QEvent::MouseButtonPress) {
      _State = MOUSEBUTTONPRESS;
   }
   else if (event_type == QEvent::MouseButtonDblClick) {
      return true; // MouseButtonDblClick not allowed
      //_State = MOUSEBUTTONDBLCLICK;
   }
   else if (event_type == QEvent::MouseButtonRelease) {
      if (_State == POPUP_OPEN) { // when popup open and MouseButtonRelease it's no correct state
         setEnabled(false);
         InfoPrintf("Combobox-Error found, CComboBox %s", this->Name());
         setEnabled(true);
         setFocus();
      }
      _State = MOUSEBUTTONRELEASE;
   }
WMETHOD_RC_EPILOG(TRUE)
#endif
   return QComboBox::event(e);
}

void CComboBox::popup()
{
   _State = POPUP_OPEN;
#ifdef QT4
   QComboBox::showPopup();
#else
   QComboBox::popup();
#endif
}

void CComboBox::clear()
{
   _ItemStrings.clear();
   QComboBox::clear();
}

void CComboBox::SelectionChanged()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QWidget * parent = NULL;
   if (_DisableParentValue) {
      parent = parentWidget();
      parent->setEnabled(false);
      qApp->processEvents();
   }
   if (ExecuteButtonFunc(_ButtonFuncRef) == actionProceed) {
      QString new_value = NewValue();
      if (_VarRef == NULL) {
         ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_LIST_SELECTED);
         EmitGUISignal(new_signal);
      } else {
         if (_Input.Update(new_value) == actionProceed) {
            ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_LIST_SELECTED);
            EmitGUISignal(new_signal);
         } else {
            ResetValue();
         }
      }
   } else {
      ResetValue();
   }
   if (_DisableParentValue) {
      qApp->processEvents();
      if (parent == NULL)
         parent = parentWidget();
      parent->setEnabled(true);
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CComboBox::View()
{
#ifndef QT_PLUGIN
#endif
}

void CComboBox::DelayedLanguageChange()
{
   TranslateItems();
   AdjustItemHeight();
   ResetValue();
}

// CCS related virtual methods

void CComboBox::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   AdjustItemHeight();
   CCSCreateFuncRef(_ButtonFuncSpec, _ButtonFuncRef);
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSCreateFuncRef(_ValueFuncSpec, _ValueFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CComboBox::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SetValue(value);

#ifdef QT4
   if (_PrevValue.isNull()) {
      // emit currentIndexChanged signal for first new value
      int current_item = currentItem();
      emit currentIndexChanged(current_item);
   }
#endif

   _PrevValue = value;
WMETHOD_VOID_EPILOG
#endif
}

void CComboBox::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CComboBox::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CComboBox::SetItemText(int index, const QString & new_text)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (index >= (int)_ItemStrings.size()) {
      _ItemStrings.resize(index+1);
   }
   _ItemStrings[index] = new_text;
   int item_count = count();
   if (item_count <= index) {
      int fill = index - item_count;
      if (fill > 0) {
         int j = 0;
         for (j=0; j<fill; j++) {
            QString filler = "filler";
#ifdef QT4
            insertItem(-1, filler);
#else
            insertItem(filler, -1);
#endif
         }
      }
#ifdef QT4
      insertItem(-1, new_text);
#else
      insertItem(new_text, -1);
#endif
   } else {
#ifdef QT4
      setItemText(index, new_text);
#else
      changeItem(new_text, index);
#endif
   }
WMETHOD_VOID_EPILOG
#endif
}

QString CComboBox::FirstItemText()
{
   QString first_item_text = "";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_ItemStrings.size() > 0) {
      first_item_text = _ItemStrings[0];
   }
WMETHOD_RC_EPILOG(first_item_text)
#endif

   return first_item_text;
}

BOOL_T CComboBox::FoundItemText(QString text)
{
    BOOL_T ret_value = false;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   int size = _ItemStrings.size();
   if (size > 0) {
      int i = 0;
      for (i=0; i<size; i++) {
         if (_ItemStrings[i] == text) {
            ret_value = true;
            break;
         }
      }
   }
WMETHOD_RC_EPILOG(TRUE)
#endif
    return ret_value;
}

void CComboBox::ResetValue()
{
   SetValue(_PrevValue);
}

QString CComboBox::NewValue()
{
   QString new_value = "";

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T index = currentItem();
   LONG_T lval = index + _IncrementValue;

   if (_ModeValue == SetIndex) {
      new_value.setNum(lval);
   } else if (_ModeValue == SetText) {
      new_value = text(lval);
   } else if (_ModeValue == SetNumericText) {
      QString item_text = text(lval);
      new_value.setNum(item_text.toLong());
   }
WMETHOD_RC_EPILOG(new_value)
#endif
   return new_value;
}

void CComboBox::SetValue(const QString & value)
{
   LONG_T lval = value.toInt();
   if (_ModeValue == SetIndex) {
      lval -= _IncrementValue;
      setCurrentItem(lval);
   } else if (_ModeValue == SetText) {
      lval = ItemIndex(value);
      setCurrentItem(lval);
   } else if (_ModeValue == SetNumericText) {
      lval = ItemIndex(value);
      setCurrentItem(lval);
   }
}

long CComboBox::ItemIndex(const QString & search_text)
{
   int items = count();
   QString item_text;
   for (int i=0; i<items; i++) {
      item_text = text(i);
      if (!item_text.isNull() && search_text == item_text) {
         return i;
      }
   }
   return currentItem();
}

void CComboBox::AdjustItemHeight()
{
   if (_ItemHeightValue == NormalHeight) {
      return;
   }
#ifdef QT4
   int itemHeight = 20;
   if (_ItemHeightValue == Height24) {
      itemHeight = 24;
   } else if (_ItemHeightValue == Height32) {
      itemHeight = 32;
   } else if (_ItemHeightValue == Height38) {
      itemHeight = 38;
   } else if (_ItemHeightValue == Height40) {
      itemHeight = 40;
   } else if (_ItemHeightValue == Height48) {
      itemHeight = 48;
   } else {
      return;
   }
   QStandardItemModel * model = static_cast<QStandardItemModel*>(this->model());
   int items = count();
   for (int i=0; i<items; i++) {
      QStandardItem * item = model->item(i);
      if (item != NULL) {
         QSize sizeHint = item->sizeHint();
         sizeHint.setHeight(itemHeight);
         item->setSizeHint(sizeHint);
      }
   }
#else
   QPixmap pixmap;
   if (_ItemHeightValue == Height24) {
      pixmap.loadFromData(height24_data, sizeof(height24_data), "PNG" );
   } else if (_ItemHeightValue == Height32) {
      pixmap.loadFromData(height32_data, sizeof(height32_data), "PNG" );
   } else if (_ItemHeightValue == Height40) {
      pixmap.loadFromData(height40_data, sizeof(height40_data), "PNG" );
   } else if (_ItemHeightValue == Height48) {
      pixmap.loadFromData(height48_data, sizeof(height48_data), "PNG" );
   } else {
      return;
   }
   int items = count();
   for (int i=0; i<items; i++) {
      QString item_text = text(i);
      changeItem(pixmap, item_text, i);
   }
#endif
}

void CComboBox::TranslateItems()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   int current_item = currentItem();
   int size = _ItemStrings.size();
   if (size > 0) {
      QComboBox::clear();
      int i = 0;
      for (i=0; i<size; i++) {
         QString item_text = _ItemStrings[i];
         item_text =QApplication::translate("custom", CONST_STRING(item_text));
#ifdef QT4
         insertItem(i, item_text);
#else
         insertItem(item_text, i);
#endif
      }
   }
   setCurrentItem(current_item);
WMETHOD_VOID_EPILOG
#endif
}

#ifdef QT4

int CComboBox::currentItem() const
{
   return currentIndex();
}

void CComboBox::setCurrentItem(int index)
{
   setCurrentIndex(index);
}

QString CComboBox::text(int index) const
{
   return itemText(index);
}

void CComboBox::changeItem(const QPixmap & pixmap, const QString & item_text, int index)
{
   setItemIcon(index, QIcon(pixmap));
   setItemText(index, item_text);
}

#endif

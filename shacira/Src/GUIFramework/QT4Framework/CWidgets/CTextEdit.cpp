

/// PR 06.04.05 Added virtual focus to input fields 
/// PR 08.06.06 introduced termination modes to control behaviour
///             of enter key 

#include "CTextEdit.h"
#include "CAppFrame.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CTextEdit, \
                   ICON_SET("textedit"), \
                   "multiline text input widget")
#endif

#ifndef QT_PLUGIN
#include "cQtKeyboard.h"
#include "cQtKeyboardAlpha.h"
#include "cInput.h"
#endif

cQtKeyboardAlpha * CTextEdit::_EnglishKeyboard = NULL;
cQtKeyboardAlpha * CTextEdit::_GermanKeyboard = NULL;

CTextEdit::CTextEdit(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QTextEdit(parent),
#else
   : QTextEdit(parent, name),
#endif
     CWidgetBase(this),
     _Input(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _TermModeValue = TerminateOnEnter;
#ifdef QT4
#pragma message(__LOC__ "not ported yet: use qt 4 resource system / implement edit start ..")
NOT_PORTED("not ported yet")
   // edit start and edit end must be done
   // by overloading mouse or focus events the clicked signal
   // is not emitted for QTextEdit under QT 4
   connect(this, SIGNAL(clicked(int,int)), this, SLOT(Edit()));
#else
   mimeSourceFactory()->setFilePath("."); // set mime source factory to actual path
   connect(this, SIGNAL(clicked(int,int)), this, SLOT(Edit()));
#endif
}

CTextEdit::~CTextEdit() 
{
}

void CTextEdit::Edit()
{
#ifndef QT_PLUGIN
   QPalette prevPalette = palette();
WMETHOD_PROLOG
   try {
      if (isReadOnly() == true) {
         return;
      } 
      if (!HelpActive()) {
         if (_Input.VarRef() != NULL) {
            CAppFrame * app_frame = CWidgetBase::_AppFrame;
            if (app_frame != NULL) 
               app_frame->AlphaNumericStateChanged(_Input.VarRef()->_Name.c_str(), true);

            if (TOUCH_SCREEN_ACTIVE()) {
               setPaletteBackgroundColor(VirtualFocusColor());
               cQtKeyboardAlpha * board = NULL;

               if (useEnglishKeyboard()) {
                  if (_EnglishKeyboard == NULL) {
                     _EnglishKeyboard = new cQtKeyboardAlpha;
                     _EnglishKeyboard->setLayout(cQtKeyboard::layoutStandard);
                  }
                  board = _EnglishKeyboard;
               } else {
                  if (_GermanKeyboard == NULL) {
                     _GermanKeyboard = new cQtKeyboardAlpha;
                     _GermanKeyboard->setLayout(cQtKeyboard::layoutGerman);
                  }
                  board = _GermanKeyboard;
               }
               iFinalValidator * final_validator = _Input.FinalValidator();
               board->setFinalValidator(final_validator);
#ifdef QT4
               board->setCurrentValue(toPlainText());
#else
               board->setCurrentValue(text());
#endif
               // Center the keyboard in the page area
               if (app_frame != NULL)
               {
                   QPoint pt1App = app_frame->mapToGlobal(QPoint(0, 0));
                   QPoint pt1Board = board->mapToGlobal(QPoint(0, 0));
                   SHORT_T X = (app_frame->getPageAreaSize().width() - board->width()) / 2 + pt1App.x();
                   SHORT_T Y = (app_frame->getPageAreaSize().height() - board->height()) / 2 + pt1App.y();
                   QPoint ptBoard(X, Y);
                   board->move(ptBoard);
               }

               if (board->exec() == QDialog::Accepted) {
                  QString new_text = board->getNewValue();
                  setText(new_text);
                  _PrevValue = new_text;
                  emit ValueAccepted(_VarSpec, new_text);
               } else {
                  CancelInput();
               }
            }

            if (app_frame != NULL) 
               app_frame->AlphaNumericStateChanged(_Input.VarRef()->_Name.c_str(), false);
         }
      }
   } catch (cError & e) {
      ErrorPrintf("%s in text edit\n", (CONST_STRING_T)e);
   } catch (...) {
      Beep(50,50);
      InfoPrintf("unhandled execption in text edit %d\n", cSystemUtils::ProcessId());
   }
WMETHOD_VOID_EPILOG
   setPalette(prevPalette);
   if (Flag(CURSOR_DISABLED)) {
      clearFocus();
   }
#endif
}

void CTextEdit::Apply()
{
   if (_TermModeValue == TerminateOnSignal) {
      if (isReadOnly() == false) {
         ApplyInput();
      }
   }
}

void CTextEdit::Cancel()
{
   if (_TermModeValue == TerminateOnSignal) {
      if (isReadOnly() == false) {
         CancelInput();
      }
   }
}

void CTextEdit::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QTextEdit::mousePressEvent(e);
   }
}

void CTextEdit::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QTextEdit::mouseReleaseEvent(e);
#ifdef QT4
      emit clicked(0, 0);
#endif
   }
}

void CTextEdit::focusInEvent ( QFocusEvent * e)
{
   QTextEdit::focusInEvent (e);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (isReadOnly() == false) {
      StartInput();
   } else {
      QTextEdit::focusInEvent(e);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTextEdit::focusOutEvent ( QFocusEvent * e)
{
   if (_TermModeValue == TerminateOnEnter) {
      QTextEdit::focusOutEvent(e);
      if (isReadOnly() == false) {
         CancelInput();
      }
   } else if (_TermModeValue == TerminateOnFocusOut) {
      QTextEdit::focusOutEvent(e);
      if (isReadOnly() == false) {
         ApplyInput();
      }
   } else {
      QTextEdit::focusOutEvent(e);
   }
}

void CTextEdit::keyReleaseEvent ( QKeyEvent * e )
{
   if (_TermModeValue == TerminateOnEnter) {
      if (isReadOnly() == false) {
         int key = e->key();
         e->ignore();
         QTextEdit::keyReleaseEvent (e);
         if (key == Qt::Key_Return ||
             key == Qt::Key_Enter) {
            ApplyInput();
         }
      } else {
         QTextEdit::keyReleaseEvent(e); 
      }
   } else if (_TermModeValue == TerminateOnFocusOut) {
      QTextEdit::keyReleaseEvent(e); 
   } else {
      QTextEdit::keyReleaseEvent(e); 
   }
}


// GUI related virtual methods

void CTextEdit::View()
{
}

// CCS related virtual methods

void CTextEdit::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CTextEdit::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
   QString set_value = value;
   QString prev_value = value;

   if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
      if (!_Input.IsNumeric()) {
         set_value = FromUtf8(set_value);
         //set_value = QString::fromUtf8(CONST_STRING(set_value));
         prev_value = set_value;
      }
   }

   setText(set_value);
   _PrevValue = prev_value;
}

void CTextEdit::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CTextEdit::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CTextEdit::StartInput()
{
#ifndef QT_PLUGIN
#endif
}

void CTextEdit::CancelInput()
{
#ifndef QT_PLUGIN
#endif
}

void CTextEdit::ApplyInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef QT4
   QString new_value = toPlainText();
#else
   QString new_value = text();
#endif
   if (_Input.Update(new_value) == actionProceed) {
      setText(new_value);
      _PrevValue = new_value;
   } else {
      setText(_PrevValue);
   }
WMETHOD_VOID_EPILOG
#endif
}



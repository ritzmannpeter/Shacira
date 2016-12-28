
#include "CReqValue.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CReqValue, \
                   ICON_SET("creqvalue"), \
                   "data input widget for numeric and text data")
#endif

#include <qcursor.h>

/// PR 07.03.05 Changed format of value in ValueAccepted signal to original, not input format
/// PR 06.04.05 Added virtual focus to input fields 

#ifndef QT_PLUGIN
#include "cQtKeypadNumeric.h"
#include "cQtKeyboard.h"
#include "cQtKeyboardAlpha.h"
#include "cQtPathValidator.h"
#include "CInput.h"
#include "CAppFrame.h"
#endif

#define OFFSET_XPOS_NUM_INP    8
#define OFFSET_YPOS_INPDIALOG 60

cQtKeyboardAlpha * CReqValue::_EnglishKeyboard = NULL;
cQtKeyboardAlpha * CReqValue::_GermanKeyboard = NULL;
cQtKeypadNumeric * CReqValue::_NumericKeypad = NULL;

CReqValue::CReqValue(QWidget * parent, const char * name, WFlags f)
   : QLineEdit(parent, name) ,
     CWidgetBase(this),
     _Input(this)
{
   CONSTRUCT_WIDGET
   _InputModeValue = SingleLine;
   _ValidationValue = DataTypeSpecific;
   _UserValidator = NULL;
   _PathValidator = NULL;

   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   setMinimumHeight (25);
   setAlignment(Qt::AlignRight|Qt::AlignVCenter);
}

CReqValue::~CReqValue() 
{
   if (_PathValidator != NULL) {
      delete _PathValidator;
   }
}

void CReqValue::SetValidator(QValidator * validator)
{
   _UserValidator = validator;
}

ULONG_T CReqValue::DataType()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_VarRef != NULL) {
      return _VarRef->DataType();
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

ULONG_T CReqValue::ValueSize()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_VarRef != NULL) {
      return _VarRef->ValueSize();
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

void CReqValue::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QLineEdit::mousePressEvent(e);
   }
}

void CReqValue::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLineEdit::mouseReleaseEvent (e);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      if (_Input.VarRef() != NULL) {
         QValidator * validator = NULL;
         if (_ValidationValue == DataTypeSpecific) {
            validator = _Input.SyntaxValidator();
         } else if (_ValidationValue == PathValidation) {
            if (_PathValidator == NULL) {
               _PathValidator = new cQtPathValidator(_VarRef->ValueSize(), NULL);
            }
            validator = _PathValidator;
         } else if (_ValidationValue == UserDefined) {
            validator = _UserValidator;
         }
         if (validator != NULL) {
            setValidator(validator);
         }
         if (TOUCH_SCREEN_ACTIVE()) {
            CAppFrame * app_frame = CWidgetBase::_AppFrame;
            UCHAR_T data_type = _VarRef->DataType();
            if (data_type == SH_STRING ||
                data_type == SH_WSTRING) {
               if (app_frame != NULL) 
                   app_frame->AlphaNumericStateChanged(_VarRef->_Name.c_str(), true);

               AlphaNumericInput(validator);

               if (app_frame != NULL) 
                   app_frame->AlphaNumericStateChanged(_VarRef->_Name.c_str(), false);
            } else {
               if (app_frame != NULL) 
                   app_frame->NumericStateChanged(_VarRef->_Name.c_str(), true);

               NumericInput(validator);

               if (app_frame != NULL) 
                   app_frame->NumericStateChanged(_VarRef->_Name.c_str(), false);
            }
         }
      } else {
//      cSystemUtils::Beep(200, 200);
         Beep(200, 200);
      }
WMETHOD_VOID_EPILOG
#endif
   }
}

void CReqValue::focusInEvent ( QFocusEvent * e)
{
   QLineEdit::focusInEvent (e);
}

void CReqValue::focusOutEvent ( QFocusEvent * e)
{
   QLineEdit::focusOutEvent (e);
   CancelInput();
}

void CReqValue::keyReleaseEvent ( QKeyEvent * e )
{
   int key = e->key();
   e->ignore();
   QLineEdit::keyReleaseEvent (e);
   if (key == Qt::Key_Return ||
       key == Qt::Key_Enter ||
       key == Qt::Key_Tab ||
       key == Qt::Key_BackTab) {
      ApplyInput();
   }
}

// GUI related virtual methods

void CReqValue::View()
{
}

// CCS related virtual methods

void CReqValue::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
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

void CReqValue::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
   QString set_value = value;
   QString prev_value = value;
#ifndef QT_PLUGIN
   if (_AppFrame->getWidgetInputUTF8Encoded()) {
      if (!_Input.IsNumeric()) {
         set_value = FromUtf8(set_value);
         //set_value = QString::fromUtf8(CONST_STRING(set_value));
         prev_value = set_value;
      }
   }
#endif
   setText(set_value);
   _PrevValue = prev_value;
}

void CReqValue::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CReqValue::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CReqValue::StartInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _PrevValue = text();
WMETHOD_VOID_EPILOG
#endif
}

void CReqValue::CancelInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   setText(_PrevValue);
WMETHOD_VOID_EPILOG
#endif
}

void CReqValue::ApplyInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString new_value = text();
   if (new_value != _PrevValue) {
      if (_Input.Update(new_value) == actionProceed) {
      } else {
         CancelInput();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CReqValue::NumericInput(QValidator * syntax_validator)
{
#ifndef QT_PLUGIN
   QColor prev_color = paletteBackgroundColor();
   setPaletteBackgroundColor(VirtualFocusColor()); //creates special palette and set bkcolor there
WMETHOD_PROLOG
#ifdef STATIC_INPUT
   if (_NumericKeypad == NULL) {
      _NumericKeypad = new cQtKeypadNumeric;
   }
#else
   cQtKeypadNumeric pad;
   _NumericKeypad = &pad;
#endif
   QString default_language = cResources::get_DefaultLanguage().c_str();
   _NumericKeypad->setWidgetStacks(default_language);
   QString minimum = _Input.Minimum();
   QString maximum = _Input.Maximum();
   _NumericKeypad->setLowerLimit(minimum);
   _NumericKeypad->setUpperLimit(maximum);

   if (syntax_validator != NULL) {
      _NumericKeypad->setSyntaxValidator(syntax_validator);
   }

   iFinalValidator * final_validator = _Input.FinalValidator();
   _NumericKeypad->setFinalValidator(final_validator);
   _NumericKeypad->setCurrentValue(text());
   CAppFrame * app_frame = CWidgetBase::_AppFrame;
   if (app_frame != NULL)
   {
      QPoint pt1App = app_frame->mapToGlobal(QPoint(0,0));
      QPoint pt2App = QPoint(pt1App.x() + app_frame->width(),pt1App.y() + app_frame->height()); 
      QPoint p = mapToGlobal(QPoint(0,0));
      QRect r = geometry();
      SHORT_T heightPad = _NumericKeypad->height() + OFFSET_YPOS_INPDIALOG;
      QPoint ptPad(p.x() + r.width(),p.y());
      if((ptPad.x() + _NumericKeypad->width()) > pt2App.x()) {
         ptPad.setX(p.x() - _NumericKeypad->width() - OFFSET_XPOS_NUM_INP);     
	  }
	  if((ptPad.y() + heightPad) > pt2App.y()) {
         ptPad.setY(pt2App.y() - heightPad);     
      }
      _NumericKeypad->move(ptPad);
   }

   if (Flag(CURSOR_DISABLED)) {
      _NumericKeypad->setCursor(Qt::BlankCursor);
   }
   if (_NumericKeypad->exec() == QDialog::Accepted) {
      QString value = _NumericKeypad->getNewValue();
      STRING_T new_value;
      _VarRef->GetValue(new_value);
      value = new_value.c_str();
      if (_AppFrame->getWidgetInputUTF8Encoded()) {
         if (!_Input.IsNumeric()) {
            value = FromUtf8(new_value.c_str());
            //value = QString::fromUtf8(new_value.c_str());
         }
      }
      setText(value);
      emit ValueAccepted(_VarSpec, value);
   } else {
      CancelInput();
   }
WMETHOD_VOID_EPILOG
   setPaletteBackgroundColor(prev_color);
   //unsetPalette();  // revert special palette for widget 
   if (Flag(CURSOR_DISABLED)) {
      clearFocus();
   }
#endif
}

void CReqValue::AlphaNumericInput(QValidator * syntax_validator)
{
#ifndef QT_PLUGIN
   QColor prev_color = paletteBackgroundColor();
   setPaletteBackgroundColor(VirtualFocusColor());
WMETHOD_PROLOG
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

   if (_InputModeValue == MultiLine) {
      board->setMultiline(true);
   } else if (_InputModeValue == SingleLine) {
      board->setMultiline(false);
      board->setEchoMode(echoMode());
   }
   if (syntax_validator != NULL) {
      board->setSyntaxValidator(syntax_validator);
   }
   iFinalValidator * final_validator = _Input.FinalValidator();
   board->setFinalValidator(final_validator);
   board->setCurrentValue(text());

   CAppFrame * app_frame = CWidgetBase::_AppFrame;
   if (app_frame != NULL) {
      QPoint pt1App = app_frame->mapToGlobal(QPoint(0,0));
      QPoint pt2App = QPoint(pt1App.x() + app_frame->width(),pt1App.y() + app_frame->height()); 
      QPoint pt1Req = mapToGlobal(QPoint(0,0));
      QRect rectReq = geometry();
      QPoint pt1Board = board->mapToGlobal(QPoint(0,0));
      SHORT_T defaultPos = (_AppFrame->getPageAreaSize().width() - board->width()) / 2 + pt1App.x();
      SHORT_T heightBoard = board->height() + OFFSET_YPOS_INPDIALOG;
      QPoint ptBoard(defaultPos, pt1Req.y() + rectReq.height());

      if((pt1Req.y() - heightBoard) < pt1App.y()) {
         ptBoard.setY(ptBoard.y());     
      }
      if((pt1Req.y() + rectReq.height() + heightBoard) > pt2App.y()) {
         ptBoard.setY(pt1Req.y() - heightBoard);     
      }
      board->move(ptBoard);
   }

   if (Flag(CURSOR_DISABLED)) {
      board->setCursor(Qt::BlankCursor);
   }
   if (board->exec() == QDialog::Accepted) {
      QString value = board->getNewValue();
      STRING_T new_value;
      _VarRef->GetValue(new_value);
      value = new_value.c_str();
      if (_AppFrame->getWidgetInputUTF8Encoded()) {
         if (!_Input.IsNumeric()) {
            value = FromUtf8(new_value.c_str());
            //value = QString::fromUtf8(new_value.c_str());
         }
      }
      setText(value);
      emit ValueAccepted(_VarSpec, value);
   } else {
      CancelInput();
   }
WMETHOD_VOID_EPILOG
   setPaletteBackgroundColor(prev_color);
   if (Flag(CURSOR_DISABLED)) {
      clearFocus();
   }
#endif
}

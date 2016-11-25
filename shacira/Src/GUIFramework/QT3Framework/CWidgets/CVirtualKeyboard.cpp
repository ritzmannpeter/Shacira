
#include "CVirtualKeyboard.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CVirtualKeyboard, \
                   ICON_SET("designer_textedit"), \
                   "keyboard widget taht can be placed elsewhere on a page to enable data entry without physical keyboard (touch screen f. e.)")
#endif

#include "cPaintUtils.h"
#include "cQtKeyboard.h"
#include "cQtKeyboardInput.h"
#ifndef QT_PLUGIN
#include "cQtPropertyWidget.h"
#include "cinput.h"
#endif


#define FONT_POINT_SIZE 0
#define FONT_PIXEL_SIZE 1


CVirtualKeyboard::CVirtualKeyboard(QWidget * parent, const char * name, WFlags f)
   : QFrame(parent, name, f),
     CWidgetBase(this),
     _Input(this)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   
   _Layout = NULL;
   _InputFrame = NULL;
   _KeyboardFrame = NULL;
   _Layout1 = NULL;
   _Layout2 = NULL;
   _TextEdit = NULL;
   _GermanKeyboard = NULL;
   _GermanKeyboardInput = NULL;
   _EnglishKeyboard = NULL;
   _EnglishKeyboardInput = NULL;

   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   _Layout = new QVBoxLayout(this, 10, 10);
   _InputFrame = new QFrame(this);
   _InputFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   _InputFrame->setMinimumSize(QSize(300, 100));
   _KeyboardFrame = new QFrame(this);
   _KeyboardFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   _KeyboardFrame->setMinimumSize(QSize(300, 250));
   _KeyboardFrame->setMaximumSize(QSize(30000, 250));
   _Layout->addWidget(_InputFrame);
   _Layout->addWidget(_KeyboardFrame);
   _TextEdit = new QTextEdit(_InputFrame);
   _TextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   _Layout1 = new QVBoxLayout(_InputFrame);
   _Layout2 = new QVBoxLayout(_KeyboardFrame);
   _Layout1->addWidget(_TextEdit);
   _KeyboardType = UNDEFINED_KEYBOARD;
   _KeyboardChanged = true;
}

CVirtualKeyboard::~CVirtualKeyboard ( ) 
{
}

void CVirtualKeyboard::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QFrame::mousePressEvent(e);
   }
}

void CVirtualKeyboard::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QFrame::mouseReleaseEvent(e);
   }
}

void CVirtualKeyboard::resizeEvent(QResizeEvent * e)
{
   QFrame::resizeEvent(e);
#ifdef QT_PLUGIN
   QPainter painter(this);
   QRect input_rectangle = _InputFrame->geometry();
   QRect keyboard_rectangle = _KeyboardFrame->geometry();
   cPaintUtils::SetBox(painter, &input_rectangle, Qt::red);
   cPaintUtils::SetBox(painter, &keyboard_rectangle, Qt::green);
   setPaletteBackgroundColor(Qt::yellow);
   _InputFrame->setPaletteBackgroundColor(Qt::green);
   _KeyboardFrame->setPaletteBackgroundColor(Qt::red);
#endif
}

void CVirtualKeyboard::hideEvent ( QHideEvent* e)
{
   EmitGUISignal(SIG_LEAVE_KEYBOARD);
}

void CVirtualKeyboard::slotSave()
{
   slotClearValidationError();
   ApplyInput();
   emit Accept();
}

void CVirtualKeyboard::slotReject()
{
   slotClearValidationError();
   CancelInput();
   emit Cancel();
}

// GUI related virtual methods

void CVirtualKeyboard::View()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ChangeKeyboard();
   if (_GermanKeyboardInput != NULL) {
      _GermanKeyboardInput->setInput(_Text);
   }
   if (_EnglishKeyboardInput != NULL) {
      _EnglishKeyboardInput->setInput(_Text);
   }
   _PrevValue = _Text;
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::DelayedLanguageChange()
{
   _Text = _TextEdit->text();
   _KeyboardChanged = true;
   Notify(VIEW_DATA);
}

// CCS related virtual methods

void CVirtualKeyboard::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
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

void CVirtualKeyboard::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                                   UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString set_value = value;
   if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
      if (!_Input.IsNumeric()) {
         set_value = FromUtf8(value);
         //set_value = QString::fromUtf8(value);
      }
   }
   SetText(set_value);
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                                   UCHAR_T data_type, ULONG_T size)
{
}

void CVirtualKeyboard::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CVirtualKeyboard::Setup()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SetKeyboard();
WMETHOD_VOID_EPILOG
#endif
}

bool CVirtualKeyboard::ContentsChanged()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return (_PrevValue != _TextEdit->text());
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

void CVirtualKeyboard::ChangeKeyboard()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_KeyboardChanged) {
      if (useEnglishKeyboard()) {
         _GermanKeyboard->hide();
         _EnglishKeyboard->show();
         _KeyboardType = ENGLISH_KEYBOARD;
      } else {
         _EnglishKeyboard->hide();
         _GermanKeyboard->show();
         _KeyboardType = GERMAN_KEYBOARD;
      }
      _KeyboardChanged = false;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::SetKeyboard()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _FontSizeType = (font().pixelSize() == -1) ? FONT_POINT_SIZE : FONT_PIXEL_SIZE;

   CreateKeyboard(_GermanKeyboard, _GermanKeyboardInput, cQtKeyboard::layoutGerman);
   CreateKeyboard(_EnglishKeyboard, _EnglishKeyboardInput, cQtKeyboard::layoutStandard);
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::CreateKeyboard(cQtKeyboard * & keyboard,
                                      cQtKeyboardInput * & input,
                                      int keyboard_type)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cQtKeyboard::LAYOUT_TYPE layout_type = cQtKeyboard::layoutStandard;
   switch (keyboard_type) {
   case ENGLISH_KEYBOARD:
      layout_type = cQtKeyboard::layoutStandard;
      break;
   case GERMAN_KEYBOARD:
      layout_type = cQtKeyboard::layoutGerman;
      break;
   }
   keyboard = new cQtKeyboard(_KeyboardFrame);
   adjustSize();
   keyboard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   _Layout2->addWidget(keyboard);
   keyboard->setLayout(layout_type);
   input = new cQtKeyboardInput(keyboard);
   input->setEchoWidget(_TextEdit);
   QFont f = font();
   input->setSmallFont(f);
   if (_FontSizeType == FONT_POINT_SIZE) {
      f.setPointSize(f.pointSize()*13 / 10);
   }
   else {
      f.setPixelSize(f.pixelSize()*13 / 10);
   }
   input->setBigFont(f);
   cQtPropertyWidget qp(keyboard);
   qp.SetProperty("_error.shown", false);
   connect(keyboard, SIGNAL(acceptInput()), this, SLOT(slotSave()));
   connect(keyboard, SIGNAL(rejectInput()), this, SLOT(slotReject()));
   
   if (_Input.VarRef() != NULL) {
      QValidator * syntax_validator = _Input.SyntaxValidator();
      if (input != NULL) {
         if (syntax_validator != NULL) {
            input->setSyntaxValidator(syntax_validator);
         }
         iFinalValidator * final_validator = _Input.FinalValidator();
         input->setFinalValidator(final_validator);
      }
   }

   // Signale im Fehlerfall verbinden
   connect( input, SIGNAL( finalValidationFailed(const QString &) ),
            this, SLOT( slotValidationFailed(const QString &) ) );
   connect( input, SIGNAL( clearValidationError() ),
            this, SLOT( slotClearValidationError() ) );
   adjustSize();
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::SetText(QString text)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Text = text;
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::StartInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _PrevValue = _TextEdit->text();
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::CancelInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_GermanKeyboardInput != NULL) {
      _GermanKeyboardInput->setInput(_PrevValue);
   }
   if (_EnglishKeyboardInput != NULL) {
      _EnglishKeyboardInput->setInput(_PrevValue);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::ApplyInput()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_KeyboardType == GERMAN_KEYBOARD) {
      if (_GermanKeyboardInput != NULL) {
         QString new_value = _GermanKeyboardInput->getInput();
         if (_Input.Update(new_value) == actionProceed) {
            _GermanKeyboardInput->setInput(new_value);
            _PrevValue = new_value;
         } else {
            _GermanKeyboardInput->setInput(_PrevValue);
         }
      }
   } else if (_KeyboardType == ENGLISH_KEYBOARD) {
      if (_EnglishKeyboardInput != NULL) {
         QString new_value = _EnglishKeyboardInput->getInput();
         if (_Input.Update(new_value) == actionProceed) {
            _EnglishKeyboardInput->setInput(new_value);
            _PrevValue = new_value;
         } else {
            _EnglishKeyboardInput->setInput(_PrevValue);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::slotValidationFailed(const QString &error)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QWidget * parent = parentWidget();

   if (_KeyboardType == GERMAN_KEYBOARD) {
      if (_GermanKeyboard != NULL) {
         cQtPropertyWidget qp(_GermanKeyboard);
         qp.SetProperty("_error.shown", true);
         qp.SetProperty("_error.text", error);
         //_GermanKeyboard->adjustSize();
         parent->adjustSize();
      }
   } else if (_KeyboardType == ENGLISH_KEYBOARD) {
      if (_EnglishKeyboard != NULL) {
         cQtPropertyWidget qp(_EnglishKeyboard);
         qp.SetProperty("_error.shown", true);
         qp.SetProperty("_error.text", error);
         //_EnglishKeyboard->adjustSize();
         parent->adjustSize();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVirtualKeyboard::slotClearValidationError()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QWidget * parent = parentWidget();
   
   if (_KeyboardType == GERMAN_KEYBOARD) {
      if (_GermanKeyboard != NULL) {
         cQtPropertyWidget qp(_GermanKeyboard);
         qp.SetProperty("_error.shown", false);
         //_GermanKeyboard->adjustSize();
         parent->adjustSize();
      }
   } else if (_KeyboardType == ENGLISH_KEYBOARD) {
      if (_EnglishKeyboard != NULL) {
         cQtPropertyWidget qp(_EnglishKeyboard);
         qp.SetProperty("_error.shown", false);
         //_EnglishKeyboard->adjustSize();
         parent->adjustSize();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

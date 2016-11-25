
#include "cQtKeyboard.h"
#include "cQtKeyboardLayout.h"

// ---------------------------------------------------------------------------
// cQtKeyboardButton in Qt Designer Plugin einbinden
// QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)
// ---------------------------------------------------------------------------

#ifdef _KBDLAYOUT_PLUGIN_
QT_PLUGIN_REGISTER(cQtKeyboard, "cQtKeyboard.h", "form", "Keypads", 0, 0, false)
#endif

#ifdef QT4
#include "ui_KeyboardLayoutStandard.h"
#include "ui_KeyboardLayoutGerman.h"
#else
#include "KeyboardLayoutStandard.h"
#include "KeyboardLayoutGerman.h"
#endif

#include <qlayout.h>

cQtKeyboard::cQtKeyboard(QWidget* parent, const char* name)
#ifdef QT4
   : QFrame(parent)
#else
   : QFrame(parent, name)
#endif
{
#ifdef QT4
   if (!name) {
	   setObjectName("cQtKeyboard");
   } else {
	   setObjectName(name);
   }
#else
   if (!name) {
	   setName("cQtKeyboard");
   }
#endif   
   setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); 
   _keyboard_layout = 0;
   _keyboard_form_layout = 0;
#ifdef QT4
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
#else
   clearWState( WState_Polished );
#endif
}


void cQtKeyboard::setLayout(LAYOUT_TYPE lt)
{
   _layout_type = lt;

   if (_keyboard_layout == 0 && _keyboard_form_layout == 0) {
      _keyboard_layout = layoutFactory( this, getLayout());
      if (_keyboard_layout != 0) {
#ifdef QT4
         _keyboard_form_layout = new QVBoxLayout(this);
         _keyboard_form_layout->setObjectName("cQtKeyboardFormLayout");
         _keyboard_form_layout->setContentsMargins(0, 0, 0, 0);
         _keyboard_form_layout->setSpacing(0);
#else
         _keyboard_form_layout = new QVBoxLayout(this, 0, 0, "cQtKeyboardFormLayout"); 
#endif
         _keyboard_form_layout->addWidget( _keyboard_layout );

         connect( _keyboard_layout, SIGNAL( clicked(cQtKeyboardButton*) ),      
                  this, SLOT( slotClicked(cQtKeyboardButton*) ) );
         connect( _keyboard_layout, SIGNAL( toggled(cQtKeyboardButton*,bool) ), 
                  this, SLOT( slotToggled(cQtKeyboardButton*,bool) ) );
         connect( _keyboard_layout, SIGNAL( acceptInput() ),      
                  this, SLOT( slotAcceptInput() ) );
         connect( _keyboard_layout, SIGNAL( rejectInput() ), 
                  this, SLOT( slotRejectInput() ) );
         connect( _keyboard_layout, SIGNAL( inputChanged(const QString &) ), 
                  this, SLOT( slotInputChanged(const QString &) ) );
      }
      adjustSize();
   }
}

cQtKeyboardLayout *cQtKeyboard::layoutFactory( QWidget *parent, LAYOUT_TYPE lt )
{
   switch (lt) {
   case layoutGerman:
#ifdef QT4
      {
         cQtKeyboardLayout * keyboardLayout = new cQtKeyboardLayout;
         Ui::cQtKeyboardLayoutGerman ui;
         ui.setupUi(keyboardLayout);
         return keyboardLayout;
      }
#else
   return new Ui_cQtKeyboardLayoutGerman( parent );
#endif
   case layoutStandard:
#ifdef QT4
      {
         cQtKeyboardLayout * keyboardLayout = new cQtKeyboardLayout;
         Ui::cQtKeyboardLayoutStandard ui;
         ui.setupUi(keyboardLayout);
         return keyboardLayout;
      }
#else
   return new cQtKeyboardLayoutStandard( parent );
#endif
   default:
      return NULL;
   return NULL;
   }
}

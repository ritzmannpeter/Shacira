
#include "cQtKeyboard.h"
#include "cQtKeyboardLayout.h"

// ---------------------------------------------------------------------------
// cQtKeyboardButton in Qt Designer Plugin einbinden
// QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)
// ---------------------------------------------------------------------------

#ifdef _KBDLAYOUT_PLUGIN_
QT_PLUGIN_REGISTER(cQtKeyboard, "cQtKeyboard.h", DEFAULT_ICON, "Keypads", 0, 0, false)
#endif

#include "KeyboardLayoutStandard.h"
#include "KeyboardLayoutGerman.h"

#include <qlayout.h>

cQtKeyboard::cQtKeyboard( QWidget* parent,  const char* name )
    : QFrame( parent, name )
{
   if ( !name )
	   setName( "cQtKeyboard" );
   
   //setFrameShape( QFrame::Panel );
   //setFrameShadow( QFrame::Raised );
   setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); 
   
   _keyboard_layout = 0;
   _keyboard_form_layout = 0;

   clearWState( WState_Polished );
}


void cQtKeyboard::setLayout(LAYOUT_TYPE lt)
{
   _layout_type = lt;

   if (_keyboard_layout == 0 && _keyboard_form_layout == 0) {
      _keyboard_layout = layoutFactory( this, getLayout() );
      if (_keyboard_layout != 0) {
         _keyboard_form_layout = new QVBoxLayout( this, 0, 0, "cQtKeyboardFormLayout"); 
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
      return new cQtKeyboardLayoutGerman( parent );
   case layoutStandard:
      return new cQtKeyboardLayoutStandard( parent );
   default:
      return NULL;
   }
}

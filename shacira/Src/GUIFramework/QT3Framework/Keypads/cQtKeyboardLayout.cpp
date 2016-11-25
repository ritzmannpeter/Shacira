// ==========================================================================
// qt_keyboard_layout.cpp
//
// Implementierung fuer cQtKeyboardLayout
// ==========================================================================

#include "cQtKeyboardLayout.h"
#include "cQtKeyboardButton.h"

#include <qobjectlist.h>

// ---------------------------------------------------------------------------
// cQtKeyboardLayout in Qt Designer Plugin einbinden
// QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)
// ---------------------------------------------------------------------------

#ifdef _KEYPAD_PLUGIN_
#include "cQtPluginRegistry.h"
QT_PLUGIN_REGISTER(cQtKeyboardLayout, "cQtKeyboardLayout.h", DEFAULT_ICON, "Keypads", 0, 0, true )
#endif

// ---------------------------------------------------------------------------
// Implementierung fuer cQtKeyboardLayout
// ---------------------------------------------------------------------------

cQtKeyboardLayout::cQtKeyboardLayout( QWidget *parent, const char *name) : 
   QFrame(parent, name),
   _key_height(40),
   _key_width(40),
   _quick_overwrite(false)
{
   // Properties von QFrame anpassen
   // setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); 
}


void cQtKeyboardLayout::initialize()
{
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      button->setOn(false);
   }
   delete buttons;
}


// wenn im Layout einer der Tastenfonts geandert wird, diese Aenderung an
// alle Tasten weitergeben, die diesen Font benutzen

void cQtKeyboardLayout::setBigFont(const QFont &bf) 
{ 
   _big_font = bf;
   
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      if (button->getKeyFont() == cQtKeyboardButton::fontBigFont) {
         button->setFont(_big_font);
      }
   }
   delete buttons;
}

void cQtKeyboardLayout::setSmallFont(const QFont &sf) 
{ 
   _small_font = sf; 
   
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      if (button->getKeyFont() == cQtKeyboardButton::fontSmallFont) {
         button->setFont(_small_font);
      }
   }
   delete buttons;
}

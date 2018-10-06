// ==========================================================================
// qt_keyboard_layout.cpp
//
// Implementierung fuer cQtKeyboardLayout
// ==========================================================================

#include "cQtKeyboardLayout.h"
#include "cQtKeyboardButton.h"

#ifndef QT4
#include <qobjectlist.h>
#endif

// ---------------------------------------------------------------------------
// cQtKeyboardLayout in Qt Designer Plugin einbinden
// QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)
// ---------------------------------------------------------------------------

#ifdef _KEYPAD_PLUGIN_
#include "pluginfactory.h"
QT_PLUGIN_REGISTER(cQtKeyboardLayout, "cQtKeyboardLayout.h", "widget", "Keypads", 0, 0, true )
#endif

// ---------------------------------------------------------------------------
// Implementierung fuer cQtKeyboardLayout
// ---------------------------------------------------------------------------

cQtKeyboardLayout::cQtKeyboardLayout( QWidget *parent, const char *name)
#ifdef QT4
   : QFrame(parent),
#else
   : QFrame(parent, name),
#endif
     _key_height(40),
     _key_width(40),
     _quick_overwrite(false)
{
   // Properties von QFrame anpassen
   // setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); 
}


void cQtKeyboardLayout::initialize()
{
#ifdef QT4
   QObjectList buttons = children();
   QObjectList::const_iterator i = buttons.constBegin();
   while (i != buttons.constEnd()) {
      if ((*i)->inherits("cQtKeyboardButton")) {
         cQtKeyboardButton *button = static_cast<cQtKeyboardButton*>((*i));
         // autoDefault must be set to false otherwise
         // a clicked button or a button getting the focus
         // will be switched to default button
         button->setAutoDefault(false);
         button->setChecked(false);
#ifdef documentation
         QString buttonName = button->objectName();
         cQtKeyboardButton::KEY_TYPE t = button->getKeyType();
         if (t == cQtKeyboardButton::KEY_TYPE::typeNewLine) {
            button->setDefault(true);
         }
         bool def = button->isDefault();
         if (def) {
            int dummy = 0;
         } else {
            int dummy = 0;
         }
         bool autoDef = button->autoDefault();
         if (autoDef) {
            int dummy = 0;
         } else {
            int dummy = 0;
         }
#endif
      }
      i++;
   }
#else
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      button->setOn(false);
   }
   delete buttons;
#endif
}


// wenn im Layout einer der Tastenfonts geandert wird, diese Aenderung an
// alle Tasten weitergeben, die diesen Font benutzen

void cQtKeyboardLayout::setBigFont(const QFont &bf) 
{ 
   _big_font = bf;
#ifdef QT4
   QObjectList buttons = children();
   QObjectList::const_iterator i = buttons.constBegin();
   while (i != buttons.constEnd()) {
      if ((*i)->inherits("cQtKeyboardButton")) {
         cQtKeyboardButton *button = static_cast<cQtKeyboardButton*>((*i));
         if (button->getKeyFont() == cQtKeyboardButton::fontBigFont) {
            button->setFont(_big_font);
         }
      }
      i++;
   }
#else
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      if (button->getKeyFont() == cQtKeyboardButton::fontBigFont) {
         button->setFont(_big_font);
      }
   }
   delete buttons;
#endif
}

void cQtKeyboardLayout::setSmallFont(const QFont &sf) 
{ 
   _small_font = sf; 
#ifdef QT4
   QObjectList buttons = children();
   QObjectList::const_iterator i = buttons.constBegin();
   while (i != buttons.constEnd()) {
      if ((*i)->inherits("cQtKeyboardButton")) {
         cQtKeyboardButton *button = static_cast<cQtKeyboardButton*>((*i));
         if (button->getKeyFont() == cQtKeyboardButton::fontSmallFont) {
            button->setFont(_small_font);
         }
      }
      i++;
   }
#else
   QObjectList *buttons = queryList("cQtKeyboardButton");
   for (unsigned int i=0; i<buttons->count(); i++) {
      cQtKeyboardButton *button = (cQtKeyboardButton*)(buttons->at(i));
      if (button->getKeyFont() == cQtKeyboardButton::fontSmallFont) {
         button->setFont(_small_font);
      }
   }
   delete buttons;
#endif
}

#ifdef QT4

#include "comp_def.h"

void cQtKeyboardLayout::setCaption(const QString & text)
{
   setWindowTitle(text);
}

#endif

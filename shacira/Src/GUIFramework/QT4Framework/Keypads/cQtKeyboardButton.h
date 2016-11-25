/** 
 * @file  qt_keyboard_button.h
 *
 * @brief Button widget for on-screen keyboard
 */

#ifndef _cqtkeyboardbutton_h_
#define _cqtkeyboardbutton_h_

#include <qpushbutton.h>
#include "pluginfactory.h"

/**
 * @class cQtKeyboardButton qt_keyboard_button.h "path/qt_keyboard_button.h"
 *
 * @brief Special button widget for use inside a cQtKeyboardLayout
 * 
 * If a cQtKeyboardButton is placed inside a cQtKeyboardLayout, the button
 * will be automatically connected with the layout.
 * - keyboard fonts defined in the layout can be refereced from the button
 * - button size is adapted to the keyboard raster defined in the layout
 * - signals clicked() and toggled() of the buttons are connected to the layout
 *
 * This class inherits @b QPushButton.
 */
class _KEYPAD_EXPORT_ cQtKeyboardButton : public QPushButton
{
   Q_OBJECT

   Q_ENUMS( KEY_FONT )
   Q_PROPERTY( KEY_FONT keyFont READ getKeyFont WRITE setKeyFont )

   Q_ENUMS( KEY_TYPE )
   Q_PROPERTY( KEY_TYPE keyType READ getKeyType WRITE setKeyType )

   Q_PROPERTY( QString keyValue READ getKeyValue WRITE setKeyValue )
   Q_PROPERTY( QString keyValueShift READ getKeyValueShift WRITE setKeyValueShift )
   Q_PROPERTY( QString keyValueAlt READ getKeyValueAlt WRITE setKeyValueAlt )

   Q_PROPERTY( uint keyWidthX10 READ getKeyWidthX10 WRITE setKeyWidthX10 )
   Q_PROPERTY( uint keyHeightX10 READ getKeyHeightX10 WRITE setKeyHeightX10 )
   
public:
   cQtKeyboardButton( QWidget *parent = 0, const char *name = 0);

   /// Font for button text
   enum KEY_FONT { 
      fontManual = 0,   ///< use font property of QPushButton
      fontSmallFont,    ///< use smallFont from keyboard layout class
      fontBigFont       ///< use bigFont from keyboard layout class
   };

   /// Select button function
   enum KEY_TYPE {
      typeNormal = 0,   ///< normal key with values on the levels normal, shift and alt.
      typeOk,           ///< accept input.
      typeCancel,       ///< cancel input.
      typeAction,       ///< generic action.
      typeSign,         ///< special function: change sign of number.
      typeNewLine,      ///< special function: insert line break.
      typeShift,        ///< select shift level for the next key. In Qt Designer you must set property toggleButton = true!
      typeShiftLock,    ///< select shift level permanently. In Qt Designer you must set property toggleButton = true!
      typeCapsLock,     ///< select upper case letters permanently. In Qt Designer you must set property toggleButton = true!
      typeAlt,          ///< select alt level for the next key. In Qt Designer you must set property toggleButton = true!
      typeBackspace,    ///< delete character left to the cursor.
      typeDelete,       ///< delete character right to the cursor.
      typeClear,        ///< clear input.
      typeLeft,         ///< move cursor to left.
      typeRight,        ///< Cursor: Zeichen nach rechts
      typeUp,           ///< Cursor: Zeile nach oben
      typeDown,         ///< Cursor: Zeile nach unten
      typeLineStart,    ///< Cursor: Zeilenanfang
      typeLineEnd,      ///< Cursor: Zeilenende
      typePgUp,         ///< Cursor: Seite nach oben
      typePgDown,       ///< Cursor: Seite nach unten
   };

   /// Font für die Buttonbeschriftung festlegen.
   void setKeyFont(KEY_FONT kf);
   /// Fontreferenz erfragen.
   KEY_FONT getKeyFont() const { return _key_font; }
   
   /// Art des Buttons festlegen, entweder ist es eine normale Taste mit auf
   /// verschiedenen Ebenen hinterlegten Texten oder eine Taste mit einer
   /// speziellen Funktion.
   /// Steht im Designer als Property zur Verfügung.
   void setKeyType(KEY_TYPE kt) { _key_type = kt; }
   /// Buttontyp erfragen.
   KEY_TYPE getKeyType() const { return _key_type; }

   /// Tastenwert auf der normalen Eingabeebene festlegen.
   /// Steht im Designer als Property zur Verfügung.
   void setKeyValue(const QString &kv) { _key_value = kv; }
   /// Normaler Tastenwert erfragen.
   QString getKeyValue() const { return _key_value; }
   
   /// Tastenwert auf der Eingabeebene für Großbuchstaben festlegen (SHIFT).
   /// Steht im Designer als Property zur Verfügung.
   void setKeyValueShift(const QString &kv) { _key_value_shift = kv; }
   /// Shift-Tastenwert erfragen
   QString getKeyValueShift() const { return _key_value_shift; }
   
   /// Tastenwert auf der alternativen Eingabeebene festlegen (ALT).
   /// Steht im Designer als Property zur Verfügung.
   void setKeyValueAlt(const QString &kv) { _key_value_alt = kv; }
   /// Alt-Tastenwert erfragen.
   QString getKeyValueAlt() const { return _key_value_alt; }
   
   /// Multiplikator für die Buttonbreite festlegen. Aus der in cQtKeyboardLayout
   /// hinterlegten Rasterbreite wird zusammen mit diesem Faktor die Breite
   /// berechnet. Der Faktor ist mit 10 multipliziert, d.h. 10 entspricht 1.0,
   /// 15 entspricht 1.5 usw.)
   /// Steht im Designer als Property zur Verfügung.
   void setKeyWidthX10(uint kw) { _key_width_x10 = kw; }
   /// Multiplikator für Breite erfragen.
   uint getKeyWidthX10() const { return _key_width_x10; }
   
   /// Multiplikator für die Buttonhöhe festlegen. Aus der in cQtKeyboardLayout
   /// hinterlegten Rasterhöhe wird zusammen mit diesem Faktor die Höhe
   /// berechnet. Der Faktor ist mit 10 multipliziert, d.h. 10 entspricht 1.0,
   /// 15 entspricht 1.5 usw.)
   /// Steht im Designer als Property zur Verfügung.
   void setKeyHeightX10(uint kh) { _key_height_x10 = kh; }
   /// Multiplikator für Höhe erfragen.
   uint getKeyHeightX10() const { return _key_height_x10; }

   /// Intern: Buttongröße berechnen.
   QSize sizeHint() const;

   /// Intern: Unterstützung von Zeilenumbrüchen im Qt Designer.
   virtual void setText(const QString &t);

private slots:
   /// Intern: Das signal clicked() vom zugrundeliegenden QPushButton wird
   /// um cQtKeboardButton* ergenzt zum cQtKeyboardLayout weitergeschickt.
   void slotClicked() { emit clicked(this); }
   /// Intern: Das signal toggled() vom zugrundeliegenden QPushButton wird
   /// um cQtKeboardButton* ergenzt zum cQtKeyboardLayout weitergeschickt.
   void slotToggled(bool on) { emit toggled(this, on); }

signals:
   void clicked(cQtKeyboardButton *button);
   void toggled(cQtKeyboardButton *button, bool on);

private:
   // Properties
   KEY_FONT _key_font;
   KEY_TYPE _key_type;
   QString _key_value;
   QString _key_value_shift;
   QString _key_value_alt;
   unsigned int _key_height_x10;
   unsigned int _key_width_x10;
#ifdef QT4
public:
   void setPixmap(const QPixmap & pixmap);
   void setToggleButton(bool state);
#endif
};


#endif // QT_KEYBOARD_BUTTON_H

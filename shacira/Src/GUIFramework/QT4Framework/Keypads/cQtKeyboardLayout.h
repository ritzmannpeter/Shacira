// ==========================================================================
// qt_keyboard_layout.h
//
// Deklaration cQtKeyboardLayout. Das ist eine Container-Klasse die dazu
// bestimmt ist, cQtKeyboardButtons aufzunehmen und zu verwalten:
//
// - Das Grundraster der Tastengroesse wird festgelegt
// - Zwei Standardfonts (gross und klein) werden fuer die Tasten definiert
// - Signale von den Tasten und zum Dialog der das Layout enthaelt
//
// cQtKeyboardLayout
//    |
//    +- QFrame
//
// ==========================================================================

#ifndef _cqtkeyboardlayout_h_
#define _cqtkeyboardlayout_h_

#include <qframe.h>
#include <qfont.h>
#include "pluginfactory.h"

class cQtKeyboardButton;

class _KEYPAD_EXPORT_ cQtKeyboardLayout : public QFrame
{
   Q_OBJECT

   // keyHeight und keyWidth definieren das Grundraster, das dem
   // Tastenlayout zugrundeliegt. Zusammen mit den beim Button
   // hinterlegten Faktoren ergibt sich daraus der sizeHint() der
   // der Buttons.
   Q_PROPERTY( int keyHeight READ getKeyHeight WRITE setKeyHeight )
   Q_PROPERTY( int keyWidth READ getKeyWidth WRITE setKeyWidth )
   
   // bigFont und smallFont sind zwei Fonts, die bei den Buttons
   // referenziert werden koennen und dann von den Buttons ueber-
   // nommen werden. Vereinfacht Fontaenderungen ...
   //
   // DA DER QT DESIGNER 3.1.2 PROPERTIES VOM TYP QFont FEHLERHAFT
   // BEARBEITET (alle QFonts werden mit identischen Bezeichnern
   // implementiert) WERDEN AUS KOMPATIBILITAETSGRUNDEN (VORERST)
   // KEINE Q_PROPERTIES DAFUER ANGELEGT. MIT DEM DESIGNER 3.3.2
   // GIBT ES DIESE PROBLEME NICHT MEHR!!!
   // 
   // Q_PROPERTY( QFont bigFont READ getBigFont WRITE setBigFont )
   // Q_PROPERTY( QFont smallFont READ getSmallFont WRITE setSmallFont )

   // Mit quickOverwrite == true wird festgelegt, dass eine Vorbelegung
   // des Eingabeergebnisses geloescht wird, wenn als erstes eine normale
   // Taste betaetigt wird.
   Q_PROPERTY( bool quickOverwrite READ getQuickOverwrite WRITE setQuickOverwrite )

public:
   cQtKeyboardLayout( QWidget *parent = 0, const char *name = 0);

   /// Reinitialize layout
   void initialize();

   // READ Properties
   int getKeyHeight() const { return _key_height; }
   int getKeyWidth() const { return _key_width; }
   const QFont &getBigFont() const { return _big_font; }
   const QFont &getSmallFont() const { return _small_font; }

   // WRITE Properties
   void setKeyWidth(int kw) { _key_width = kw; }
   void setKeyHeight(int kh) { _key_height = kh; }
   void setBigFont(const QFont &bf);
   void setSmallFont(const QFont &sf);

   /// set quick overwrite flag
   void setQuickOverwrite(bool qo) { _quick_overwrite = qo; }
   /// get quick overwrite flag
   bool getQuickOverwrite() const { return _quick_overwrite; }

public slots:
   // Signale von den cQtKeyboardButton Objekten laufen in diesen Slots
   // zusammen und werden als Signale von cQtKeyboardLayout weitergesendet.
   void slotClicked(cQtKeyboardButton *button) { emit clicked(button); }
   void slotToggled(cQtKeyboardButton *button, bool on) { emit toggled(button, on); }
   // Ok und Cancel an den QDialog werden hier durchgeschleust (sind dort
   // protected und koennen nicht direkt bedient werden).
   void slotAcceptInput() { emit acceptInput(); }
   void slotRejectInput() { emit rejectInput(); }
   // Aktualisieren der aktuellen Anzeige der Eingabe
   void setInput(const QString &input) { emit inputChanged(input); }

signals:
   void clicked(cQtKeyboardButton *button);
   void toggled(cQtKeyboardButton *button, bool on);
   void acceptInput();
   void rejectInput();
   void inputChanged(const QString &input);

private:
   // Properties
   int _key_width;
   int _key_height;
   bool _quick_overwrite;
   QFont _big_font;
   QFont _small_font;
#ifdef QT4
public:
   void setCaption(const QString & text);
#endif
};


#endif // QT_KEYBOARD_LAYOUT_H

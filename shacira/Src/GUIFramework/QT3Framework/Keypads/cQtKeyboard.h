
#ifndef _cqtkeyboard_h_
#define _cqtkeyboard_h_

#include <qframe.h>
#include "cQtPluginRegistry.h"

class QVBoxLayout;
class cQtKeyboardLayout;
class cQtKeyboardButton;

class SH_QT_WIDGET_PLUGIN_EXPORT cQtKeyboard : public QFrame
{
   Q_OBJECT

   Q_ENUMS( LAYOUT_TYPE )
   Q_PROPERTY( LAYOUT_TYPE layout READ getLayout WRITE setLayout )
      
public:
   cQtKeyboard( QWidget *parent = 0, const char *name = 0);

   enum LAYOUT_TYPE {
      layoutUndefined = 0,
      layoutStandard,
      layoutGerman
   };

   void setLayout(LAYOUT_TYPE lt);
   LAYOUT_TYPE getLayout() const { return _layout_type; }

   cQtKeyboardLayout *layoutFactory( QWidget *parent, LAYOUT_TYPE lt);

   cQtKeyboardLayout *_keyboard_layout;

public slots:
   void slotClicked(cQtKeyboardButton *button) { emit clicked(button); }
   void slotToggled(cQtKeyboardButton *button, bool on) { emit toggled(button, on); }
   void slotAcceptInput() { emit acceptInput(); }
   void slotRejectInput() { emit rejectInput(); }
   void slotInputChanged(const QString &input) { emit inputChanged(input); }

signals:
   void clicked(cQtKeyboardButton *button);
   void toggled(cQtKeyboardButton *button, bool on);
   void acceptInput();
   void rejectInput();
   void inputChanged(const QString &input);

private:
   LAYOUT_TYPE _layout_type;

protected:
   QVBoxLayout *_keyboard_form_layout;
};

#endif // QT_KEYBOARD_H

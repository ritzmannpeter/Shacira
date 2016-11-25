

#include "generated/uic_keyboardmodal.h"
#include "keypads/qt_keyboard_input.h"


class cQtKeyboardModal : public cQtKeyboardModalBase
{
   Q_OBJECT

public:
   cQtKeyboardModal( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );

   void setText(const QString &line);

public slots:
   void slotAcceptInput();
   void slotRejectInput();

private:
   void showStatus(const QString &line);

   cQtKeyboardInput _keyboard_input;
   QString _text_saved;
};



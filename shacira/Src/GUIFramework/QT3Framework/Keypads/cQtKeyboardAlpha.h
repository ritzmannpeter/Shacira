
/// PR 06.10.04 added methods setEchoMode and setLayout

#include "cQtNumberValidator.h"
#include "cQtKeyboardInput.h"
#include "cQtKeyboard.h"
#include <qlineedit.h>
#include <qtextedit.h>
#include "KeyboardAlpha.h"

class cQtKeyboardAlpha : public cQtKeyboardAlphaBase
{
   Q_OBJECT

public:
   cQtKeyboardAlpha( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );

   void setMultiline(bool multi);
   void setEchoMode(QLineEdit::EchoMode mode);
   void setLayout(cQtKeyboard::LAYOUT_TYPE);

   void setBigFont(const QFont &font);
   QFont getBigFont() const;
   void setSmallFont(const QFont &font);
   QFont getSmallFont() const;

   void setSyntaxValidator(QValidator *v);
   void setFinalValidator(iFinalValidator *v);

   void setCurrentValue(const QString &cv);
   QString getNewValue() const;

   int exec();

   cQtKeyboardInput _keyboard_input;
   
private slots:
   void slotValidationFailed(const QString &error);
public slots:
   void slotClearValidationError();
};



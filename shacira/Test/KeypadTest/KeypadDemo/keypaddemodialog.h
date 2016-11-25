// keypaddemodialog.h
#ifndef qt_inputdemodialog_h
#define qt_inputdemodialog_h


#include "generated/uic_keypaddemodialog.h"

#include "keypads/qt_keyboard_input.h"


class iFinalValidator;
class QValidator;

class cQtKeypadDemoDialog : public cQtKeypadDemoDialogBase
{
	Q_OBJECT
public:
	cQtKeypadDemoDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags f = 0 );

   // Auswahl mit Combo-Box fuer QDialog
   virtual void slotSetDialog(const QString &dialog);
   // Auswahl mit Combo-Box fuer Syntax Validator
   virtual void slotSetValidator(const QString &validator);
   // Parameter des numerischen Validators geaendert (min, max, decimals)
   virtual void slotUpdateValidator();
   // Auswahl mit Combo-Box fuer Final Validator
   virtual void slotSetFinalValidator(const QString &validator);
   
   virtual void slotSetLayout(const QString &layout);
   virtual void slotShowModal();
   virtual void slotShowStatic();

   // Fontauswahl
   virtual void slotSetBigFont();
   virtual void slotSetSmallFont();

   // Eine Eingabe wird angefordert!
   virtual void slotGetInput();

private:
   // Der Dialog in dem die Eingabe stattfindet
   QDialog *_keyboard_dialog;

   // Flag ob der numerische Validator benutzt wird
   bool _is_num_validator;
   
   iFinalValidator *_final_validator;
   QValidator *_syntax_validator;

};


#endif // keypaddemodialog.h


#include "cQTNumberValidator.h"
#include "cQtKeyboardInput.h"
#include "KeypadNumeric.h"

class cQtKeypadNumeric : public cQtKeypadNumericBase
{
   Q_OBJECT

public:
   cQtKeypadNumeric( QWidget* parent = 0, const char* name = 0, bool modal = false, WIDGET_FLAGS_TYPE fl = 0 );

   void setBigFont(const QFont &font);
   QFont getBigFont() const;
   void setSmallFont(const QFont &font);
   QFont getSmallFont() const;

   void setSyntaxValidator(QValidator *v);
   void setSyntaxValidator(double min_val, double max_val, int prec);

   void setFinalValidator(iFinalValidator *v);

   //void setInfo(const QString &i);
   void setLowerLimit(const QString &text);
   void setUpperLimit(const QString &text);
   void setCurrentValue(const QString &cv);
   QString getNewValue() const;
   void setWidgetStacks(QString DefaultLanguage);
   int exec();

private slots:
   void slotValidationFailed(const QString &error);
   void slotClearValidationError();
private:
   cQtKeyboardInput _keyboard_input;
   cQtNumberValidator _number_validator;
};



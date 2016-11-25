
#include <qtimer.h>
#include <qdatetime.h>

class cStyleControl : public QTimer
{
   Q_OBJECT
public:
   cStyleControl(const QString & styleSheetPath, QObject * parent = NULL);
   virtual ~cStyleControl();
public slots:
   void slotControlStyleSheet();
protected:
   void updateStyle();
   QString loadStyleSheet(const QString & styleSheetPath);
protected:
   QString _styleSheetPath;
   QDateTime _lastModification;
};



#ifndef _applicationfilter_h_
#define _applicationfilter_h_

#include <qobject.h>

class ApplicationFilter : public QObject
{
public:
    void setUseApplicationStyleSheet(bool useApplicationStyleSheet) { _useApplicationStyleSheet = useApplicationStyleSheet; };
    bool getUseApplicationStyleSheet() { return _useApplicationStyleSheet; };

protected:
   bool eventFilter(QObject * o, QEvent * e);

private:
   bool _useApplicationStyleSheet;
};

#endif

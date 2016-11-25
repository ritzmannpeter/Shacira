#include "NewProjectMainWindow.h"


class NewProjectMainWindowImpl : public NewProjectMainWindow
{
	Q_OBJECT
public:
	NewProjectMainWindowImpl( QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );

public slots:
   void SelectionChanged(int pos);
};


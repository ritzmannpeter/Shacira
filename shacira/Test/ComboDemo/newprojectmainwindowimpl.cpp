#include "newprojectmainwindowimpl.h"
#include <qcombobox.h>
#include <windows.h>
#include <qapplication.h>


NewProjectMainWindowImpl::NewProjectMainWindowImpl( QWidget* parent, const char* name, WFlags f )
	: NewProjectMainWindow( parent, name, f )
{
	setCaption("NewProject");

	// Add your code

   connect(comboBox1, SIGNAL(activated(int)), this, SLOT(SelectionChanged(int)));
}

void NewProjectMainWindowImpl::SelectionChanged(int pos)
{
    ((QWidget*)comboBox1->parent())->setDisabled(true);
    qApp->processEvents();
    for (int i=1; i<5; i++) {
        Beep(50,50);
        Sleep(1000);
    }
    qApp->processEvents();
    ((QWidget*)comboBox1->parent())->setDisabled(false);

}

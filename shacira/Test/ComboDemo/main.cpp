#include <qapplication.h>
#include "newprojectmainwindowimpl.h"


int main( int argc, char** argv )
{
	QApplication app( argc, argv );

	NewProjectMainWindowImpl mainwindow;
	app.setMainWidget(&mainwindow);

	mainwindow.show();

	return app.exec();
}


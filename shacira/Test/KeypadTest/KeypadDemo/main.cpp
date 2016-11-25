// main.cpp
#include <qapplication.h>
#include "keypaddemodialog.h"


int main( int argc, char** argv )
{
	QApplication app( argc, argv );

	cQtKeypadDemoDialog dialog( 0, 0, TRUE );
	app.setMainWidget(&dialog);

	dialog.exec();

	return 0;
}


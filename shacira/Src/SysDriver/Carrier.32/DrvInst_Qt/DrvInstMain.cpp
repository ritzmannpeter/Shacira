
#include "drvinstform.h"
#include "qapplication.h"
#include "qtranslator.h"
#include "caritf.h"

QApplication * App = NULL;

int main(int argc, char **argv)
{
	if (argc > 1) {
      if (stricmp(argv[1], "-t") == 0) {
			HANDLE hnd = CARITF_Open();
			if (hnd != INVALID_HANDLE_VALUE) {
			   CARITF_Close(hnd);
				_exit(0);
			}
		}
	}
   App = new QApplication(argc, argv);
   QTranslator translator( 0 );
   translator.load( "D.qm", "." );
   App->installTranslator( &translator );
   DrvInstForm * form = new DrvInstForm;
   App->setMainWidget(form);
   form->show();
   return App->exec();
}


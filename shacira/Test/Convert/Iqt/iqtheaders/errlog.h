
#ifndef __errlog__
#define __errlog__

/* Codes fuer die Herkunft der Fehler. Hier kann jederzeit erweitert       */
/* werden. Es sollten nur die hier definierten Codes verwendet werden, um  */
/* die Codes einheitlich und uebersichtlich zu halten                      */
#define ERRLOG_CODE_MUTEX   1     /* Mutexfehler                            */
#define ERRLOG_CODE_SIGNAL  2     /* Programmabbruch                        */
#define ERRLOG_CODE_IQTTXT  3     /* Fehler beim Einlesen der Texte         */
#define ERRLOG_CODE_KBD     4     /* Fehler beim Tastaturhandling           */
#define ERRLOG_CODE_TASK    5     /* Fehler in Task-Funktion                */
#define ERRLOG_CODE_REG     6     /* Fehler in Register-Funktion            */


/* Severity-Codes                                                          */
#define ERRLOG_DEBUG   0  /* Debugausgabe, sparsam verwenden                */
#define ERRLOG_INFO    1  /* Informationsmeldung, kein Fehler               */
#define ERRLOG_WARNING 2  /* Warnung, kann zu Fehler fuehren                */
#define ERRLOG_ERROR   3  /* Ernster Fehler, Programm wird fortgesetzt      */
#define ERRLOG_FATAL   4  /* Fehler fuehrt zum Programmabbruch              */


GLOBAL void ErrLogPrintf (int code, int severity, char *format, ...);
GLOBAL void ErrLogPrintf_NoHdr (char *format, ...);

#endif /* __Errlog__ */

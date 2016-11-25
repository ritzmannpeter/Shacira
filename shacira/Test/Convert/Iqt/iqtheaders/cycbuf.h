// cycbuf.h  -  Deklarationen fuer den Zykluspuffer fuer OPC und Corba

#ifndef _cycbuf_
#define _cycbuf_

extern "C" {
#include <time.h>
#include <string.h>
#include <syntax.h>
#include <tasks.h>
#include <events.h>
}

//
// Konstanten
//

#define CYCBUF_NR_VAR         30 // Max. Anzahl ueberwachter (Register-)Variablen
#define CYCBUF_NR_CYC         50 // Max. Anzahl ueberwachter Zyklen
#define CYCBUF_NAMELEN        30 // Nax. Laenge des Item-Namensstrings incl. 0

#define CYCBUF_ERR_CONNECT    -1 // Keine Verbindung zum BBRAM moeglich
#define CYCBUF_ERR_BUFEMPTY   -2 // Zykluspuffer ist leer
#define CYCBUF_ERR_NOTFOUND   -3 // Variable nicht gefunden
#define CYCBUF_ERR_INVVAR     -4 // Variable ist falsch (Registernr. o.ae.)
#define CYCBUF_ERR_TOOMUCH    -5 // Variablenlist ist voll
#define CYCBUF_ERR_TOOLESS    -6 // Variablenlist ist leer
#define CYCBUF_ERR_TSKWAITING -7 // Eine andere Task wartet auf den naechsten Z.


//
// Typdefinitionen
//

// Die folgende Struktur enthaelt den Zykluspuffer und alle Daten zu seiner
// Verwaltung. Sie wird im batteriegepufferten RAM gespeichert.
//
typedef struct {
   // Verwaltung der ueberwachten Variablen
   int act_nr_var;               // Anzahl tatsaechlich ueberwachter Variablen
   UWORD reg_nr[CYCBUF_NR_VAR];  // Registernummern der ueberwachten Variablen
   UWORD ind_info[CYCBUF_NR_VAR];// samt Indexinfo und Indizes
   UWORD ind1[CYCBUF_NR_VAR];
   UWORD ind2[CYCBUF_NR_VAR];
   UWORD ind3[CYCBUF_NR_VAR];
   char  item_id[CYCBUF_NR_VAR][CYCBUF_NAMELEN];   // Item-Id (0-term. )

   // Verwaltung der gespeicherten Werte
   int act_cycles;               // Anzahl Zyklen, die aktuell im Puffer sind
   int write_ind;                // Pufferindex fuer den naechsten Schreibvorgang
   int read_ind;                 // Pufferindex fuer den naechsten Lesevorgang
   long  value[CYCBUF_NR_CYC][CYCBUF_NR_VAR];      // Gespeicherte Werte
   time_t timestamp[CYCBUF_NR_CYC];                // Zeitstempel   
} CYCBUF_T;


//
// Klasse CCycBuf
//

class CCycBuf {
   CYCBUF_T cycbuf;              // Cache des Zykluspuffers. Diese Daten
                                 // befinden sich nochmals im BBRAM und werden
                                 // wenn noetig upgedatet.
   TASKMUTEX m_mutex;            // Zugriff auf Puffer muss geschuetzt werden.
   BOOL m_connect;               // TRUE: Verbindung zum BBRAM ist hergestellt
   char m_bufname[50];           // Name des Puffers im BBRAM
   int  m_enum;                  // Enumerationsindex fuer die Variablenliste.
   EVENT_T m_event;              // Fuer Task die auf Daten wartet.
   BOOL m_task_waiting;          // TRUE wenn eine Task auf m_event wartet.
   BOOL m_lastcyc_locked;        // TRUE wenn der letzte Zyklus gesperrt ist.

public:
   CCycBuf (char *name)     {TaskMutexCreate (&m_mutex,TASK_RECURSIVE_MUTEX);
                              m_connect = FALSE;
                              strcpy (m_bufname, name);
                              memset (&cycbuf, 0, sizeof(CYCBUF_T));
                              TskEventInit (&m_event);
                              m_task_waiting = FALSE;
                              m_lastcyc_locked = FALSE;
                             }
   
   ~CCycBuf ()               {TaskMutexDestroy (&m_mutex);}

   // Fuellzustand des Zykluspuffers erfragen
   int GetActCycles ()       {return cycbuf.act_cycles;}

   // Die Namen aller zu ueberwachenden Variablen erfragen. CreateVarEnum
   // erzeugt einen Enumerator (setzt den Zaehlerindex zurueck), mit 
   // GetNextVarName bekommt man jeweils den naechsten Variablennamen, bis
   // die Variablenliste fertig bearbeitet ist. Es gibt nur einen Enumerator,
   // darum mit Lock/Unlock schuetzen.
   int CreateVarEnum ();
   char *GetNextVarName ();
   
   // Zugriff auf Zykluspuffer reservieren und wieder freigeben. Auf ein Lock
   // muss zwingend und in jedem Fall ein Unlock folgen.
   void Lock()               {TaskMutexLock (&m_mutex);}
   void Unlock()             {TaskMutexUnlock (&m_mutex);}

   void LockLastCycle()      {Lock();
                              m_lastcyc_locked = TRUE;
                              Unlock();}

   // BBRAM-Initialisierung, Anlegen des Puffers
   int BBRamInit (BYTE segment);

   // Zyklustrigger, wird bei jedem Spritzzyklus aufgerufen und fuegt dann
   // die neuen Werte in den Zykluspuffer ein.
   int TriggerCycle ();
   
   // Durch Aufruf dieser Funktion kann eine Task (nur eine) bei leerem 
   // Zykluspuffer darauf warten, dass neue Daten ankommen.
   int WaitForCycle ();
   
   // Lesen eines Wertes vom aeltesten gespeicherten Zyklus
   int ReadVal (char *id, long *val, time_t *timestamp);
   
   // Loeschen des aeltesten Spritzzyklus, Update des Puffers im BBRAM.
   int DeleteCycle ();
   
   // Neuinitialieren des gesamten Zykluspuffers. Alle Variablendefinitionen
   // und alle gespeicherten Werte gehen verloren. Dies wird durchgefuehrt,
   // bevor die Variablenliste neu definiert wird.
   int ClearAll ();
   
   // Einfuegen einer neuen zu ueberwachenden Variablen
   int InsertVar (char *id, UWORD regnr, UWORD indinfo, 
                  UWORD i1, UWORD i2, UWORD i3);
                  
protected:
   // Wird intern aufgerufen, wenn neue Daten ankommen, um auf diese Daten
   // wartende Tasks aufzuwecken.
   void WakeWaitingTask ();
};


//
// Beschreibung aller existierenden Zykluspuffer (z.Z. genau einer)
//
typedef struct {
   char *name;          // Name des Zykluspuffers (fuer Gruppe und BBRAM)
   CCycBuf *cb;         // Zeiger auf Zykluspufferobjekt
   BYTE segment;        // Segment im BBRAM
} CYCBUF_DESC;

//
// Globale Beschreibung aller Zykluspuffer. Endemarke der Tabelle ist eine
// Struktur mit NULL-Zeigern.
//
extern CYCBUF_DESC CycBufDesc [];

#endif  // _cycbuf_


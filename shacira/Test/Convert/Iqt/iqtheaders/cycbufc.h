// cycbufc.h  -  Deklarationen des C-Interfaces fuer den Zykluspuffer 
//               fuer OPC und Corba. Diese Funktion werden aus dem
//               Kernprogramm heraus aufgerufen.

#ifndef _cycbufc_
#define _cycbufc_

#include <hostenum.h>


   // BBRAM-Initialisierung, Anlegen des Puffers
   int CycBufBBRamInit (int dummy);

   // Zyklustrigger, wird bei jedem Spritzzyklus aufgerufen und fuegt dann
   // die neuen Werte in den Zykluspuffer ein.
   void CycBufTriggerCycle ();

   // Spezielle Zugriffsfunktionen
   int ReadCycBufCount (REG_ACCESS_T *acc,  long *val);
   int DeleteLastCycle (REG_ACCESS_T *acc,  long val);
   

#endif  // _cycbufc_


// ===========================================================================
// base/osbase.cpp                                              ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/osbase.h"

// Platform dependant headers
#if defined __ECL_LINUX__
   #include <fstream>
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/shm.h>
#endif




namespace ecl {


#if defined __ECL_LINUX__

// Randprobleme:
// - Erzeugung von key-Dateien in einer noch nicht vorhandenen Verzeichnis-Struktur
//   -> Vorlaeufig alles in /tmp/ecl/ anlegen um Problem zu umgehen.
//   -> Verzeichnisse automatisch erstellen?
//   -> leere Verzeichnisse auch wieder loeschen? (opendir, dirent, closedir)
// - Dateileichen von Programmabstuerzen
//   -> Idee: wenn bei Create zwar die Datei existiert, aber kein shmem unter key_t
//      dann kann die shmem-erzeugende Instanz danach die Datei loeschen.

cOsBase::cOsKey::cOsKey(const cString &name, int mode)
{
   _name = buildKeyFileSpec(name);
   _flags = 0;
   
printf("ifstream(%s)\n", (const char *)_name.ccp());
   bool exist = std::ifstream(_name.ccp(), std::ios::in);
printf("exist = %s\n", exist == true ? "true" : "false");
   if (exist == true && (mode == keyOpen || mode == keyOpenOrCreate)) {
printf("%d\n", __LINE__);
      // Open auf existierender Datei
      _key = ftok(_name.ccp(), PROJ_ID);
printf("%d\n", __LINE__);
      _created = false;
printf("%d\n", __LINE__);
   } else if (exist == false && (mode == keyCreate || mode == keyOpenOrCreate)) {
      // Create auf nicht existierender Datei
      // Wenn die Rechte nicht recht sein sollten, kann auch 
      // int open(char*, int, int) benutzt werden ???
//fopen(_name.ccp(), "w");
printf("%d\n", __LINE__);
      std::ofstream(_name.ccp(), std::ios::out);
printf("%d\n", __LINE__);
      _key = ftok(_name.ccp(), PROJ_ID);
printf("_key = %d in %d\n", (int)_key, __LINE__);
      _created = true;
   } else {
      // Fehler!
printf("%d\n", __LINE__);
      _key = -1;
      _created = false;
      errno = EINVAL;
printf("%d\n", __LINE__);
   }

   if (_key != -1) {
      switch (mode) {
      case keyCreate:       _flags = IPC_CREAT | IPC_EXCL | 0666; break;
      case keyOpenOrCreate: _flags = IPC_CREAT | 0666; break;
      case keyOpen:         _flags = 0; break;
      }
   }
}

cOsBase::cOsKey::~cOsKey()
{
   if (_created == true) {
      remove(_name.ccp());
   }
}

#endif // __ECL_LINUX__



}; // namespace ecl

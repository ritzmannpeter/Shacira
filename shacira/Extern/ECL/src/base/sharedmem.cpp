// ===========================================================================
// base/sharedmem.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/sharedmem.h"

// Other ECL headers
#include "base/osbase.h"

// Platform dependant headers
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#elif defined __ECL_LINUX__
   //#include <iostream>
   #include <fstream>
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/shm.h>
#endif




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ (identifizieren cSharedMem-Modul)
// TBD: anderes Modulbit statt dbgIpc / dbgAssert raus (wenn cBase bessere Filter hat)
const unsigned long SHMEM_ERROR = cBase::dbgError | cBase::dbgIpc | cBase::dbgAssert;
const unsigned long SHMEM_WARN  = cBase::dbgWarn  | cBase::dbgIpc;
const unsigned long SHMEM_INFO  = cBase::dbgInfo  | cBase::dbgIpc;


// ===========================================================================
// Private Data & Access methods
// ===========================================================================

struct cSharedMem::cPrivate {
   void *mem;           // Zugewiesene Startadresse nach Einblendung
   CREATION_MODE cm;    // Beim Konstruktor angewandete Methode
   int refc;            // Reference-Counter

   #if defined __ECL_LINUX__
      cPrivate() : key(0) {}
      ~cPrivate() { delete key; }
      cOsBase::cOsKey *key;
      int shmid;
   #elif defined __ECL_W32__ || defined __ECL_OS2__
      // cPrivate() { constructor not needed } 
      cOsBase::cOsHandle handle;
   #endif
};

void *cSharedMem::getAdr()
{ 
   return (void *)((char *)(_data->mem) + sizeof(int)); 
}

int cSharedMem::getSize() const
{ 
   return *((int *)(_data->mem)); 
}

cSharedMem::CREATION_MODE cSharedMem::getCreationMode() const
{ 
   return _data->cm; 
}




// ===========================================================================
// Implementierung cSharedMem
// ===========================================================================

cSharedMem::cSharedMem(const cString &name, OPEN_MODE mode, int size) :
   _data(new0 cPrivate)
{
   __ECL_STATISTIC__(name.isEmpty() ? "cSharedMem(local)": "cSharedMem(named)")

   int wanted_size = size;
   _data->mem = 0;
   _data->cm = cmLocalCreated;
   _data->refc = 0;

   if ( wanted_size < 1 && mode != memOpen ) {
      delete _data;
      throw cErrBase(cErrBase::errInvParam, "cSharedMem", name);
   }

   // Mehrbedarf fuer Groesseninformation
   size += sizeof(int);

   if ( name.isEmpty() ) {
      // Lokal Memory anfordern

      if ( mode == memOpen ) {
         delete _data;
         throw cErrBase(cErrBase::errInvParam, name);
      }
      _data->mem = malloc(size);

   } else {
      // Shared Memory anfordern
      openNamed(name, mode, size);
   }

   if ( _data->mem == 0 ) {
      delete _data;
      throw cErrBase(cErrBase::errInit, "cSharedMem", name);
   }

   // Groesseninformation belegen
   if ( _data->cm == cmLocalCreated || _data->cm == cmSharedCreated ) {
      *((int *)_data->mem) = wanted_size;
   } else if ( _data->cm == cmSharedOpened && (wanted_size > 0 && wanted_size > *((int *)_data->mem)) ) {
      close();
      delete _data;
      throw cErrBase(cErrBase::errInvParam, "cSharedMem", name);
   }
}


cSharedMem::cSharedMem(OPEN_MODE mode, void *ptr, int size) : 
   _data(new0 cPrivate)
{
   __ECL_STATISTIC__("cSharedMem(static)")

   if ( mode == memOpenOrCreate || ptr == 0 || size < sizeof(int)+1 ) {
      delete _data;
      throw cErrBase(cErrBase::errInvParam, "cSharedMem");
   }
   
   _data->mem = ptr;
   if ( mode == memCreate ) {
      _data->cm = cmStaticCreated;
      *((int *)_data->mem) = size - sizeof(int);
   } else {
      if ( (size - (int)sizeof(int)) > *((int *)_data->mem) ) {
         delete _data;
         throw cErrBase(cErrBase::errInvParam, "cSharedMem");
      }
      _data->cm = cmStaticOpened;
   }
   _data->refc = 0;
}

cSharedMem::cSharedMem(const cSharedMem &other)
{
   _data = other._data;
   _data->refc++;
}

cSharedMem &cSharedMem::operator=(const cSharedMem &other)
{
   if (&other != this) {
      uncount();
      _data = other._data;
      _data->refc++;
   }
   return *this;
}

cSharedMem::~cSharedMem()
{
   uncount();
}

void cSharedMem::uncount()
{
   if (_data->refc-- == 0) {
      if ( getCreationMode() == cmLocalCreated ) {
         if ( _data->mem ) free(_data->mem);
      } else if ( _data->cm == cmSharedOpened || _data->cm == cmSharedCreated ) {
         close();
      }
      delete _data;
   }
}

void cSharedMem::openNamed(const cString &name, OPEN_MODE mode, int size)
{
   #if defined __ECL_OS2__

      #error redesign of OS/2 parts not done
      APIRET rc;
      cString shname = "\\sharemem\\ecl\\" + name;
      _data->cm = cmSharedOpened;
      if ( mode == memOpen || mode == memOpenOrCreate )
         rc = DosGetNamedSharedMem(&_data->mem, shname, PAG_READ|PAG_WRITE);
      if ( rc != NO_ERROR && mode != memOpen ) {
         _data->cm = cmSharedCreated;
         if ( (rc = DosAllocSharedMem(&_data->mem, shname, size, PAG_COMMIT|PAG_WRITE|PAG_READ)) == NO_ERROR )
            memset(_data->mem, 0, size);
      }
      __ECL_ASSERT2__(!rc, ("OS/2: Creation of shared mem %s failed, rc = %d", (const char *)shname, rc));

   #elif defined __ECL_W32__

      cString shname = "/sharemem/ecl/" + name;
      _data->cm = cmSharedOpened;
      if ( mode == memOpen || mode == memOpenOrCreate )
         _data->handle = OpenFileMapping(FILE_MAP_WRITE, FALSE, shname);
      if ( !_data->handle.isValid() && mode != memOpen ) {
         if (mode != memCreate || isAllocated(name) == false) {
            _data->cm = cmSharedCreated;
            _data->handle = CreateFileMapping((HANDLE)0xffffffff, 0, PAGE_READWRITE, 0, size, shname);
         }
      }
      __ECL_ASSERT_PRINTF__(_data->handle.isValid(), SHMEM_ERROR, ("Win32: Creation of shared mem %s failed, err = %d", (const char *)shname, GetLastError()));
      if ( _data->handle.isValid() ) {
         _data->mem = MapViewOfFile(_data->handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
         __ECL_ASSERT_PRINTF__(_data->handle.isValid(), SHMEM_ERROR, ("Win32: Mapping of shared mem %s failed, err = %d", (const char *)shname, GetLastError()));
      }

   #elif defined __ECL_LINUX__

      cString shname = "sharedmem_" + name;
      _data->key = new0 cOsBase::cOsKey(shname, mode);
      // Der CreationMode haengt vom create/open des key-file ab, nicht von dem vom Shared Memory.
      // Kann verbessert werden, aber beide zustaende sollten sich entsprechen. Wenn z.B. das
      // Randproblem der Dateileichen bearbeitet wird, muss hier noch Grips investiert werden.
      _data->cm = _data->key->hasCreated() ? cmSharedCreated : cmSharedOpened;
      if (__ECL_ASSERT_PRINTF__(_data->key->isValid(), SHMEM_ERROR, ("Linux: No key for shared mem %s with mode %d: %s", _data->key->getName().ccp(), mode, strerror(errno)))) {
         _data->shmid = shmget(_data->key->getKey(), size, _data->key->getFlags());
         if (__ECL_ASSERT_PRINTF__(_data->shmid != -1, SHMEM_ERROR, ("Linux: Can't get id for shared mem %s with mode %d: %s", _data->key->getName().ccp(), mode, strerror(errno)))) {
            _data->mem = shmat(_data->shmid, 0, 0);
            if (!__ECL_ASSERT_PRINTF__(_data->mem != (void*)-1, SHMEM_ERROR, ("Linux: Can't attach address for shared mem %s with mode %d: %s", _data->key->getName().ccp(), mode, strerror(errno)) )) {
               _data->mem = 0; // bewirkt throw
            }
// PR linux port test
*(int*)_data->mem = size;
         }
      }
      //__ECL_DEBUG_TEXT__(SHMEM_WARN,"shared memory under construction");

   #else

      __ECL_DEBUG_TEXT__(SHMEM_ERROR,"shared memory not supported");

   #endif
}

void cSharedMem::close()
{
   #if defined __ECL_OS2__
      DosSubUnsetMem(_data->mem);
      DosFreeMem(_data->mem);
   #elif defined __ECL_W32__
      UnmapViewOfFile(_data->mem);
      CloseHandle(_data->handle);
   #elif defined __ECL_LINUX__
   
      __ECL_ASSERT_PRINTF__(shmdt(_data->mem) != -1, SHMEM_ERROR, ("Linux: Detach for shared mem %s failed", _data->key->getName().ccp()));
      if (_data->cm == cmSharedCreated) {
         __ECL_ASSERT_PRINTF__(shmctl(_data->shmid, IPC_RMID, 0) != -1, SHMEM_ERROR, ("Linux: Destroying shared mem %s failed: %s", _data->key->getName().ccp(), strerror(errno)));
      }

   #endif
}

bool cSharedMem::isAllocated(const cString &name)
{
   if ( name.isEmpty() )
      return false;

   #if defined __ECL_OS2__

      cString shname = "\\sharemem\\ecl\\" + name;
      void *temp_mem;

      if ( DosGetNamedSharedMem(&temp_mem, shname, PAG_READ|PAG_WRITE) == NO_ERROR ) {
         DosFreeMem(temp_mem);
         return true;
      }

   #elif defined __ECL_W32__

      cString shname = "/sharemem/ecl/" + name;
      HANDLE temp_handle;

      if ( (temp_handle = OpenFileMapping(FILE_MAP_READ, FALSE, shname)) != 0 ) {
         CloseHandle(temp_handle);
         return true;
      }

   #elif defined __ECL_LINUX__
      
      // Im Augenblick haengt die Existenz eines shared memory nur an der
      // Existenz der key-Datei. Koennte verbessert werden ...
      bool exist = std::ifstream(cOsBase::cOsKey::buildKeyFileSpec("sharedmem_" + name).ccp(), std::ios::in);
      __ECL_DEBUG_PRINTF__(SHMEM_INFO, ("Keyfile exist(%s)=%d", cOsBase::cOsKey::buildKeyFileSpec("sharedmem_" + name).ccp(), exist));
      return exist;

   #endif

   return false;
}




/*
#if defined __Test_eb_shmem__

   #include <conio.h>
   #include <iostream.h>
   #include "base/eb_sema.hpp"
   #include "base/eb_thread.hpp"

   class cWaitThread : public cThread {
   public:
      cWaitThread()
      {
         abort = false;
         start(teStart);
      }

      int onMain(void *extra)
      {
         while ( _getch() != 27 );
            // wait for ESC 
         abort = true;
         esc_pressed.set();
         return 0;
      }

      cEventSem esc_pressed;
      bool abort;
   };

   int main (int argc, char *argv[])
   {
      cWaitThread wait_thread;

      #define MAX_MEM 100
      cSharedMem shared_mem("test", cSharedMem::memOpenOrCreate, sizeof(int) * MAX_MEM);
      int *mem = (int *)shared_mem.getAdr();

      cMutexSem prot_sema("protection", cSema::semOpenOrCreate);
      cEventSem alive_sema("new_process_alive", cSema::semOpenOrCreate);
      int my_id = 0;

      prot_sema.request();
      for ( int i = 0 ; i < MAX_MEM ; i++ ) {
         if ( mem[i] == 0 ) {
            mem[my_id = i] = 1; break;
         }
      }
      prot_sema.release();

      cerr << "I'm number " << my_id << " - and I'm alive!" << endl;
      cerr << "Please, start more of me (or press ESC to quit)..." << endl << endl;
      alive_sema.pulse();

      do {
         cerr << "NOW ALIVE: ";
         prot_sema.request();
         for ( int i = 0 ; i < MAX_MEM ; i++ )
            if ( mem[i] )
               cerr << " " << i;
         prot_sema.release();
         cerr << endl;
         (alive_sema + wait_thread.esc_pressed).waitForOne();
      } while ( !wait_thread.abort );

      cerr << "Argh! I'm dead..." << endl;
      mem[my_id] = 0;
      alive_sema.pulse();

      return 0;
   }

#endif
*/




}; // __ecl_sharedmem__



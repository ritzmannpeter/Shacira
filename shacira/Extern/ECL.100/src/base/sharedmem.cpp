// ===========================================================================
// base/sharedmem.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================

#include "base/sharedmem.h"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




namespace ecl {




// Implementierung cSharedMem
// ===========================================================================

cSharedMem::cSharedMem(const cString &name, OPEN_MODE mode, int size)
{
   int wanted_size = size;
   cString shname;
   cSharedMem::mem = NULL;
   cSharedMem::cm = cmLocalCreated;

   if ( wanted_size < 1 && mode != memOpen )
      throw cErrBase(cErrBase::errInvParam, "cSharedMem", name);

   // Mehrbedarf fuer Groesseninformation
   size += sizeof(int);

   if ( name.isEmpty() ) {
      // Lokal Memory anfordern

      if ( mode == memOpen )
         throw cErrBase(cErrBase::errInvParam, name);
      mem = malloc(size);

   } else {
      // Shared Memory anfordern

      #if defined __ECL_OS2__

         APIRET rc;
         shname = "\\sharemem\\ecl\\" + name;
         cm = cmSharedOpened;
         if ( mode == memOpen || mode == memOpenOrCreate )
            rc = DosGetNamedSharedMem(&mem, shname, PAG_READ|PAG_WRITE);
         if ( rc != NO_ERROR && mode != memOpen ) {
            cm = cmSharedCreated;
            if ( (rc = DosAllocSharedMem(&mem, shname, size, PAG_COMMIT|PAG_WRITE|PAG_READ)) == NO_ERROR )
               memset(mem, 0, size);
         }
         __ECL_ASSERT2__(!rc, ("OS/2: Creation of shared mem %s failed, rc = %d", (const char *)shname, rc));

      #elif defined __ECL_W32__

         shname = "/sharemem/ecl/" + name;
         cm = cmSharedOpened;
         if ( mode == memOpen || mode == memOpenOrCreate )
            handle = OpenFileMapping(FILE_MAP_WRITE, FALSE, shname);
         if ( !handle.isValid() && mode != memOpen ) {
            if (mode != memCreate || isAllocated(name) == false) {
               cm = cmSharedCreated;
               handle = CreateFileMapping((HANDLE)0xffffffff, NULL, PAGE_READWRITE, 0, size, shname);
            }
         }
         __ECL_ASSERT2__(handle.isValid(), ("Win32: Creation of shared mem %s failed, err = %d", (const char *)shname, GetLastError()));
         if ( handle.isValid() ) {
            mem = MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
            __ECL_ASSERT2__(handle.isValid(), ("Win32: Mapping of shared mem %s failed, err = %d", (const char *)shname, GetLastError()));
         }

      #endif

   }

   if ( mem == 0 )
      throw cErrBase(cErrBase::errInit, "cSharedMem", shname);

   // Groesseninformation belegen
   if ( cm == cmLocalCreated || cm == cmSharedCreated ) {
      *((int *)mem) = wanted_size;
   } else if ( cm == cmSharedOpened && (wanted_size > 0 && wanted_size > *((int *)mem)) ) {
      throw cErrBase(cErrBase::errInvParam, "cSharedMem", shname);
   }
}


cSharedMem::cSharedMem(OPEN_MODE mode, void *ptr, int size)
{
   if ( mode == memOpenOrCreate || ptr == 0 || size < sizeof(int)+1 )
      throw cErrBase(cErrBase::errInvParam, "cSharedMem");
   
   mem = ptr;
   if ( mode == memCreate ) {
      cm = cmStaticCreated;
      *((int *)mem) = size - sizeof(int);
   } else {
      if ( (size - (int)sizeof(int)) > *((int *)mem) )
         throw cErrBase(cErrBase::errInvParam, "cSharedMem");
      cm = cmStaticOpened;
   }
}


cSharedMem::~cSharedMem()
{
   if ( getCreationMode() == cmLocalCreated ) {
      if ( mem ) free(mem);
   } else if ( cm == cmSharedOpened || cm == cmSharedCreated ) {
      #if defined __ECL_OS2__
         DosSubUnsetMem(mem);
         DosFreeMem(mem);
      #elif defined __ECL_W32__
         UnmapViewOfFile(mem);
         CloseHandle(handle);
      #endif
   }
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

      if ( (temp_handle = OpenFileMapping(FILE_MAP_READ, FALSE, shname)) != NULL ) {
         CloseHandle(temp_handle);
         return true;
      }

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



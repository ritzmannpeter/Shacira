//## begin module%3B8A23E00182.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A23E00182.cm

//## begin module%3B8A23E00182.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A23E00182.cp

//## Module: cSystemUtils%3B8A23E00182; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSystemUtils.h

#ifndef cSystemUtils_h
#define cSystemUtils_h 1

//## begin module%3B8A23E00182.includes preserve=yes
//## end module%3B8A23E00182.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"

class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3B8A23E00182.additionalDeclarations preserve=yes

typedef struct {
   ULONG_T size;
   BUF_T buffer;
}  BLOCK_DEF_T;
typedef std::map<STRING_T,BLOCK_DEF_T*>  CACHE_BLOCK_MAP_T;

typedef struct {
   void * memory;
   ULONG_T size;
   ULONG_T thread_id;
}  MEMORY_BLOCK_T;
typedef std::map<void*,MEMORY_BLOCK_T*>  MEMORY_BLOCK_MAP_T;

typedef std::map<ULONG_T,PTR_T> THREAD_DATA_MAP_T;

#define RESTRICT_TO_SINGLE_CPU      0x00000001

//## end module%3B8A23E00182.additionalDeclarations


//## begin cSystemUtils%3B8A23E00182.preface preserve=yes
//## end cSystemUtils%3B8A23E00182.preface

//## Class: cSystemUtils%3B8A23E00182
//	This class offers some utility functions wrapped around
//	system functionality.
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40D328E9038A;cTokenizer { -> F}
//## Uses: <unnamed>%40D32A4901C5;cFileSystemUtils { -> F}
//## Uses: <unnamed>%41F256C1035B;cObjectLock { -> }

class __DLL_EXPORT__ cSystemUtils 
{
  //## begin cSystemUtils%3B8A23E00182.initialDeclarations preserve=yes
   friend class cResources;
public:
  //## end cSystemUtils%3B8A23E00182.initialDeclarations

    //## Constructors (generated)
      cSystemUtils();

      cSystemUtils(const cSystemUtils &right);

    //## Destructor (generated)
      virtual ~cSystemUtils();


    //## Other Operations (specified)
      //## Operation: UserName%1133801931
      //	Denotes the name of the user that is running the process.
      static STRING_T UserName ();

      //## Operation: ComputerName%998912342
      //	Denotes the name of the computer the process is running
      //	on.
      static STRING_T ComputerName ();

      //## Operation: HostName%1124450017
      //	Denotes the name of the computer the process is running
      //	on.
      static STRING_T HostName ();

      //## Operation: IPAddress%1041592744
      //	Denotes the ip address of the computer the process is
      //	running on.
      static STRING_T IPAddress ();

      //## Operation: EnvironmentString%998912343
      //	Delivers the substitution of an environment variable. If
      //	this variable is not defined the return value is an
      //	empty string;
      static STRING_T EnvironmentString (CONST_STRING_T variable);

      //## Operation: ProcessId%1036748524
      //	Denotes the Id of the current process.
      static ULONG_T ProcessId ();

      //## Operation: ThreadId%1036748525
      //	Denotes the Id of the current thread.
      static ULONG_T ThreadId ();

      //## Operation: Suspend%1036748526
      //	Suspends thread execution for msecs milliseconds;
      static void Suspend (ULONG_T msecs);

      //## Operation: AcousticSignal%1153754506
      static void AcousticSignal (ULONG_T frequency, ULONG_T duration);

      //## Operation: Alloc%1050584916
      static void * Alloc (ULONG_T size);

      //## Operation: Free%1050584917
      static void Free (void *memory);

      //## Operation: RealtimeOffset%1054305357
      static ULONG_T RealtimeOffset ();

      //## Operation: DebugConsolePrintf%1076931337
      static void DebugConsolePrintf (CONST_STRING_T fmt_str, ... );

      //## Operation: CheckBinaryFile%1087580201
      //	Checks for the existence of a shared object and returns
      //	the path where the object is first found.
      static STRING_T CheckBinaryFile (CONST_STRING_T file_name, CONST_STRING_T rel_path = NULL);

      //## Operation: CachedAlloc%1097166811
      static BUF_T CachedAlloc (CONST_STRING_T name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T size);

      //## Operation: SetThreadData%1100592011
      static void SetThreadData (PTR_T data);

      //## Operation: GetThreadData%1100592012
      static PTR_T GetThreadData ();

      //## Operation: Allocated%1106400837
      static ULONG_T Allocated ();

      //## Operation: AllocatedBlocks%1116507649
      static ULONG_T AllocatedBlocks ();

      //## Operation: MsgBox%1116323884
      static void MsgBox (CONST_STRING_T title, CONST_STRING_T message);

      //## Operation: SetArchitectureFlags%1130348758
      static void SetArchitectureFlags (ULONG_T flags);

    // Data Members for Class Attributes

      //## Attribute: BlockMapMutex%41F256900157
      //## begin cSystemUtils::BlockMapMutex%41F256900157.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _BlockMapMutex;
      //## end cSystemUtils::BlockMapMutex%41F256900157.attr

  public:
    // Additional Public Declarations
      //## begin cSystemUtils%3B8A23E00182.public preserve=yes
      static BOOL_T IsMainThread();
      static ULONG_T MainThreadId();
      //## end cSystemUtils%3B8A23E00182.public

  protected:
    // Additional Protected Declarations
      //## begin cSystemUtils%3B8A23E00182.protected preserve=yes
      //## end cSystemUtils%3B8A23E00182.protected

  private:
    // Additional Private Declarations
      //## begin cSystemUtils%3B8A23E00182.private preserve=yes
      static void SetMainThread();
      //## end cSystemUtils%3B8A23E00182.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: MemoryBlock%1106400838
      static MEMORY_BLOCK_T * MemoryBlock (void *memory);

    // Data Members for Class Attributes

      //## Attribute: UserName%4394717E00DE
      //## begin cSystemUtils::UserName%4394717E00DE.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _UserName;
      //## end cSystemUtils::UserName%4394717E00DE.attr

      //## Attribute: ComputerName%3B8A3EB802BA
      //## begin cSystemUtils::ComputerName%3B8A3EB802BA.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _ComputerName;
      //## end cSystemUtils::ComputerName%3B8A3EB802BA.attr

      //## Attribute: HostName%4305BEBC00CB
      //## begin cSystemUtils::HostName%4305BEBC00CB.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _HostName;
      //## end cSystemUtils::HostName%4305BEBC00CB.attr

      //## Attribute: IPAddress%4305BD00008C
      //## begin cSystemUtils::IPAddress%4305BD00008C.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _IPAddress;
      //## end cSystemUtils::IPAddress%4305BD00008C.attr

      //## Attribute: CachedBlocks%41691FE4007D
      //## begin cSystemUtils::CachedBlocks%41691FE4007D.attr preserve=no  implementation: static CACHE_BLOCK_MAP_T {U} 
      static CACHE_BLOCK_MAP_T _CachedBlocks;
      //## end cSystemUtils::CachedBlocks%41691FE4007D.attr

      //## Attribute: MemoryBlocks%41F2558C006D
      //## begin cSystemUtils::MemoryBlocks%41F2558C006D.attr preserve=no  implementation: static MEMORY_BLOCK_MAP_T {U} 
      static MEMORY_BLOCK_MAP_T _MemoryBlocks;
      //## end cSystemUtils::MemoryBlocks%41F2558C006D.attr

      //## Attribute: Allocated%41F255AF009C
      //## begin cSystemUtils::Allocated%41F255AF009C.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _Allocated;
      //## end cSystemUtils::Allocated%41F255AF009C.attr

      //## Attribute: ThreadData%4199B5450000
      //## begin cSystemUtils::ThreadData%4199B5450000.attr preserve=no  implementation: static THREAD_DATA_MAP_T {U} 
      static THREAD_DATA_MAP_T _ThreadData;
      //## end cSystemUtils::ThreadData%4199B5450000.attr

      //## Attribute: AllocatedBlocks%428C943503D8
      //## begin cSystemUtils::AllocatedBlocks%428C943503D8.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _AllocatedBlocks;
      //## end cSystemUtils::AllocatedBlocks%428C943503D8.attr

    // Additional Implementation Declarations
      //## begin cSystemUtils%3B8A23E00182.implementation preserve=yes
      static ULONG_T _MainThreadId;
      //## end cSystemUtils%3B8A23E00182.implementation

};

//## begin cSystemUtils%3B8A23E00182.postscript preserve=yes
//## end cSystemUtils%3B8A23E00182.postscript

// Class cSystemUtils 

//## begin module%3B8A23E00182.epilog preserve=yes
//## end module%3B8A23E00182.epilog


#endif

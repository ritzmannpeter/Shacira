//## begin module%3B8A23E00182.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A23E00182.cm

//## begin module%3B8A23E00182.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A23E00182.cp

//## Module: cSystemUtils%3B8A23E00182; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSystemUtils.cpp

//## begin module%3B8A23E00182.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B8A23E00182.additionalIncludes

//## begin module%3B8A23E00182.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3B8A23E00182.includes

// cTokenizer
#include "System/cTokenizer.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cSystemUtils
#include "System/Sys/cSystemUtils.h"
//## begin module%3B8A23E00182.additionalDeclarations preserve=yes

/// PR 07.04.09 - added printf statements that are more safe with respect to buffer overflows

#undef CONTROL_MEMORY
#include "base/eb_thread.hpp"

//## end module%3B8A23E00182.additionalDeclarations


// Class cSystemUtils 

//## begin cSystemUtils::UserName%4394717E00DE.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cSystemUtils::_UserName;
//## end cSystemUtils::UserName%4394717E00DE.attr

//## begin cSystemUtils::ComputerName%3B8A3EB802BA.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cSystemUtils::_ComputerName;
//## end cSystemUtils::ComputerName%3B8A3EB802BA.attr

//## begin cSystemUtils::HostName%4305BEBC00CB.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cSystemUtils::_HostName;
//## end cSystemUtils::HostName%4305BEBC00CB.attr

//## begin cSystemUtils::IPAddress%4305BD00008C.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cSystemUtils::_IPAddress;
//## end cSystemUtils::IPAddress%4305BD00008C.attr

//## begin cSystemUtils::CachedBlocks%41691FE4007D.attr preserve=no  implementation: static CACHE_BLOCK_MAP_T {U} 
CACHE_BLOCK_MAP_T cSystemUtils::_CachedBlocks;
//## end cSystemUtils::CachedBlocks%41691FE4007D.attr

//## begin cSystemUtils::BlockMapMutex%41F256900157.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cSystemUtils::_BlockMapMutex;
//## end cSystemUtils::BlockMapMutex%41F256900157.attr

//## begin cSystemUtils::MemoryBlocks%41F2558C006D.attr preserve=no  implementation: static MEMORY_BLOCK_MAP_T {U} 
MEMORY_BLOCK_MAP_T cSystemUtils::_MemoryBlocks;
//## end cSystemUtils::MemoryBlocks%41F2558C006D.attr

//## begin cSystemUtils::Allocated%41F255AF009C.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cSystemUtils::_Allocated = 0;
//## end cSystemUtils::Allocated%41F255AF009C.attr

//## begin cSystemUtils::ThreadData%4199B5450000.attr preserve=no  implementation: static THREAD_DATA_MAP_T {U} 
THREAD_DATA_MAP_T cSystemUtils::_ThreadData;
//## end cSystemUtils::ThreadData%4199B5450000.attr

//## begin cSystemUtils::AllocatedBlocks%428C943503D8.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cSystemUtils::_AllocatedBlocks = 0;
//## end cSystemUtils::AllocatedBlocks%428C943503D8.attr

ULONG_T cSystemUtils::_MainThreadId = 0;

cSystemUtils::cSystemUtils()
  //## begin cSystemUtils::cSystemUtils%.hasinit preserve=no
  //## end cSystemUtils::cSystemUtils%.hasinit
  //## begin cSystemUtils::cSystemUtils%.initialization preserve=yes
  //## end cSystemUtils::cSystemUtils%.initialization
{
  //## begin cSystemUtils::cSystemUtils%.body preserve=yes
_ASSERT_UNCOND
  //## end cSystemUtils::cSystemUtils%.body
}

cSystemUtils::cSystemUtils(const cSystemUtils &right)
  //## begin cSystemUtils::cSystemUtils%copy.hasinit preserve=no
  //## end cSystemUtils::cSystemUtils%copy.hasinit
  //## begin cSystemUtils::cSystemUtils%copy.initialization preserve=yes
  //## end cSystemUtils::cSystemUtils%copy.initialization
{
  //## begin cSystemUtils::cSystemUtils%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSystemUtils::cSystemUtils%copy.body
}


cSystemUtils::~cSystemUtils()
{
  //## begin cSystemUtils::~cSystemUtils%.body preserve=yes
_ASSERT_UNCOND
  //## end cSystemUtils::~cSystemUtils%.body
}



//## Other Operations (implementation)
STRING_T cSystemUtils::UserName ()
{
  //## begin cSystemUtils::UserName%1133801931.body preserve=yes
   if (_UserName.size() == 0) {
      _UserName = EnvironmentString("USERNAME");
   }
   return _UserName;
  //## end cSystemUtils::UserName%1133801931.body
}

STRING_T cSystemUtils::ComputerName ()
{
  //## begin cSystemUtils::ComputerName%998912342.body preserve=yes
   if (_ComputerName.size() == 0) {
      _ComputerName = EnvironmentString("COMPUTERNAME");
   }
   return _ComputerName;
  //## end cSystemUtils::ComputerName%998912342.body
}

STRING_T cSystemUtils::HostName ()
{
  //## begin cSystemUtils::HostName%1124450017.body preserve=yes
   if (_HostName.size() == 0) {
      struct sockaddr_in tmp_addr;
      char host_name[0x200] = {0};
      char ip_addr[0x200] = {0};
      struct hostent * host_entry = gethostbyname(ComputerName().c_str());
      if (host_entry != NULL) {
         SafeStrCpy(host_name, host_entry->h_name, sizeof(host_name));
         _HostName = host_name;
         memcpy(&tmp_addr.sin_addr, host_entry->h_addr, host_entry->h_length);
         SafeStrCpy(ip_addr, inet_ntoa(tmp_addr.sin_addr), sizeof(ip_addr));
         _IPAddress = ip_addr;
      } else {
         _HostName = _ComputerName;
      }
   }
   return _HostName;
  //## end cSystemUtils::HostName%1124450017.body
}

STRING_T cSystemUtils::IPAddress ()
{
  //## begin cSystemUtils::IPAddress%1041592744.body preserve=yes
   if (_IPAddress.size() == 0) {
      char host_name[0x200] = {0};
      char ip_addr[0x200] = {0};
      struct hostent * host_entry = gethostbyname(ComputerName().c_str());
      if (host_entry != NULL) {
         SafeStrCpy(host_name, host_entry->h_name, sizeof(host_name));
         _HostName = host_name;
         SafeStrCpy(ip_addr, host_entry->h_addr, sizeof(ip_addr));
         _IPAddress = ip_addr;
      } else {
         _HostName = _ComputerName;
      }
   }
   return _IPAddress;
  //## end cSystemUtils::IPAddress%1041592744.body
}

STRING_T cSystemUtils::EnvironmentString (CONST_STRING_T variable)
{
  //## begin cSystemUtils::EnvironmentString%998912343.body preserve=yes
   const char * environment_string = NULL;
   environment_string = getenv(variable);
   return environment_string == NULL ? "" : environment_string;
  //## end cSystemUtils::EnvironmentString%998912343.body
}

ULONG_T cSystemUtils::ProcessId ()
{
  //## begin cSystemUtils::ProcessId%1036748524.body preserve=yes
   return cThread::getCurrentProcessId();
  //## end cSystemUtils::ProcessId%1036748524.body
}

ULONG_T cSystemUtils::ThreadId ()
{
  //## begin cSystemUtils::ThreadId%1036748525.body preserve=yes
   return cThread::getCurrentThreadId();
  //## end cSystemUtils::ThreadId%1036748525.body
}

void cSystemUtils::Suspend (ULONG_T msecs)
{
  //## begin cSystemUtils::Suspend%1036748526.body preserve=yes
   cThread::sleep(msecs);
  //## end cSystemUtils::Suspend%1036748526.body
}

void cSystemUtils::AcousticSignal (ULONG_T frequency, ULONG_T duration)
{
  //## begin cSystemUtils::AcousticSignal%1153754506.body preserve=yes
#if defined(_WIN32)
   Beep(frequency, duration);
#elif defined(__linux__)
PORT_LEVEL_2
#else
NO_PLATFORM
#endif
  //## end cSystemUtils::AcousticSignal%1153754506.body
}

void * cSystemUtils::Alloc (ULONG_T size)
{
  //## begin cSystemUtils::Alloc%1050584916.body preserve=yes
#ifdef CONTROL_MEMORY
   cObjectLock __lock__(&_BlockMapMutex);
   void * memory = calloc(1, size);
   MEMORY_BLOCK_T * mem_block = (MEMORY_BLOCK_T*)calloc(1, sizeof(*mem_block));
   mem_block->thread_id = ThreadId();
   mem_block->size = size;
   mem_block->memory = memory;
   _MemoryBlocks[memory] = mem_block;
   _Allocated += size;
   _AllocatedBlocks++;
   return memory;
#else
   void * memory = calloc(1, size);
   if (memory == NULL) {
      throw cError(BAD_ALLOC, 0);
   } else {
      _AllocatedBlocks++;
      return memory;
   }
#endif
  //## end cSystemUtils::Alloc%1050584916.body
}

void cSystemUtils::Free (void *memory)
{
  //## begin cSystemUtils::Free%1050584917.body preserve=yes
#ifdef CONTROL_MEMORY
   cObjectLock __lock__(&_BlockMapMutex);
   MEMORY_BLOCK_T * mem_block = MemoryBlock(memory);
   if (mem_block != NULL) {
      if (mem_block->memory == memory) {
         _Allocated -= mem_block->size;
         _MemoryBlocks.erase(memory);
      } else {
         ErrorPrintf("memory mismatch in Free (%p != %p)\n", memory, mem_block->memory);
      }
      free(mem_block);
   } else {
      ErrorPrintf("unregistered memory block %p in Free\n", memory);
   }
#endif
   _AllocatedBlocks--;
	free(memory);
  //## end cSystemUtils::Free%1050584917.body
}

ULONG_T cSystemUtils::RealtimeOffset ()
{
  //## begin cSystemUtils::RealtimeOffset%1054305357.body preserve=yes
#if defined(_WIN32)
   ULONG_T ticks = GetTickCount();
   return ticks;
#elif defined(__linux__)
PORT_LEVEL_2
#else
NO_PLATFORM
#endif
  //## end cSystemUtils::RealtimeOffset%1054305357.body
}

void cSystemUtils::DebugConsolePrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cSystemUtils::DebugConsolePrintf%1076931337.body preserve=yes
#if defined(_WIN32)
   static char _Text[0x8000] = {0};
   try {
      va_list args;
      va_start(args, fmt_str);
      int nprint = _vsnprintf(_Text, sizeof(_Text) - 1, fmt_str, args);
      va_end(args);
      OutputDebugString(_Text);
   } catch (...) {
   }
#endif
  //## end cSystemUtils::DebugConsolePrintf%1076931337.body
}

STRING_T cSystemUtils::CheckBinaryFile (CONST_STRING_T file_name, CONST_STRING_T rel_path)
{
  //## begin cSystemUtils::CheckBinaryFile%1087580201.body preserve=yes
   STRING_T working_dir = cFileSystemUtils::FullPath("");
   if (rel_path != NULL) {
      working_dir = cFileSystemUtils::AppendPath(working_dir.c_str(), rel_path);
   }
   STRING_T file = cFileSystemUtils::AppendPath(working_dir.c_str(), file_name);
   if (cFileSystemUtils::FileExists(file.c_str())) {
      return working_dir.c_str();
   }
   STRING_T path = getenv("path");
   cTokenizer tokenizer(path.c_str(), path.size());
   CONST_STRING_T token = tokenizer.GetToken(";");
   while (token != NULL) {
      if (cFileSystemUtils::IsRelativePath(token)) {
         if (rel_path == NULL ||
             strcmp(rel_path, token) != 0) {
            STRING_T found_path = CheckBinaryFile(file_name, token);
            if (found_path.size() > 0) {
               return found_path;
            }
         }
      } else {
         STRING_T search_path = token;
         if (rel_path != NULL) {
            search_path = cFileSystemUtils::AppendPath(token, rel_path);
         }
         STRING_T file = cFileSystemUtils::AppendPath(search_path.c_str(), file_name);
         if (cFileSystemUtils::FileExists(file.c_str())) {
            return search_path.c_str();
         }
      }
      token = tokenizer.GetToken(";");
   }
   return "";
  //## end cSystemUtils::CheckBinaryFile%1087580201.body
}

BUF_T cSystemUtils::CachedAlloc (CONST_STRING_T name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T size)
{
  //## begin cSystemUtils::CachedAlloc%1097166811.body preserve=yes
   char key[0x2000] = {0};
   SafePrintf(key, sizeof(key), "%s[%d][%d][%d][%d]", name, i2, i2, i3, i4);
   BLOCK_DEF_T * block_def = NULL;
   CACHE_BLOCK_MAP_T::const_iterator i = _CachedBlocks.find(key);
   if (i == _CachedBlocks.cend()) {
      block_def = (BLOCK_DEF_T*)Alloc(sizeof(BLOCK_DEF_T));
      block_def->buffer = (BUF_T)Alloc(size);
      block_def->size = size;
      _CachedBlocks[key] = block_def;
   } else {
      block_def = (*i).second;
      if (block_def->size < size) {
         block_def->buffer = (BUF_T)Alloc(size);
         block_def->size = size;
      }
   }
   memset(block_def->buffer, 0, block_def->size);
   return block_def->buffer;
  //## end cSystemUtils::CachedAlloc%1097166811.body
}

void cSystemUtils::SetThreadData (PTR_T data)
{
  //## begin cSystemUtils::SetThreadData%1100592011.body preserve=yes
   ULONG_T id = ThreadId();
   PTR_T old_data = NULL;
   THREAD_DATA_MAP_T::const_iterator i = _ThreadData.find(id);
   if (i != _ThreadData.cend()) {
      old_data = (*i).second;
   }
   _ThreadData[id] = data;
  //## end cSystemUtils::SetThreadData%1100592011.body
}

PTR_T cSystemUtils::GetThreadData ()
{
  //## begin cSystemUtils::GetThreadData%1100592012.body preserve=yes
   ULONG_T id = ThreadId();
   THREAD_DATA_MAP_T::const_iterator i = _ThreadData.find(id);
   if (i != _ThreadData.cend()) {
      return (*i).second;
   } else {
      return NULL;
   }
  //## end cSystemUtils::GetThreadData%1100592012.body
}

ULONG_T cSystemUtils::Allocated ()
{
  //## begin cSystemUtils::Allocated%1106400837.body preserve=yes
   return _Allocated;
  //## end cSystemUtils::Allocated%1106400837.body
}

ULONG_T cSystemUtils::AllocatedBlocks ()
{
  //## begin cSystemUtils::AllocatedBlocks%1116507649.body preserve=yes
   return _AllocatedBlocks;
  //## end cSystemUtils::AllocatedBlocks%1116507649.body
}

void cSystemUtils::MsgBox (CONST_STRING_T title, CONST_STRING_T message)
{
  //## begin cSystemUtils::MsgBox%1116323884.body preserve=yes
#if defined(_WIN32)
   MessageBox(NULL, message, title, MB_OK|MB_SYSTEMMODAL|MB_ICONSTOP);
#elif defined(__linux__)
PORT_LEVEL_3
ErrorPrintf("%s: %s\n", title, message);
InfoPrintf("%s: %s\n", title, message);
#else
NO_PLATFORM
#endif
  //## end cSystemUtils::MsgBox%1116323884.body
}

void cSystemUtils::SetArchitectureFlags (ULONG_T flags)
{
  //## begin cSystemUtils::SetArchitectureFlags%1130348758.body preserve=yes
   if (flags & RESTRICT_TO_SINGLE_CPU) {
#if defined(_WIN32)
      HANDLE phnd = GetCurrentProcess();
      DWORD process_mask = 0;
      DWORD system_mask = 0;
      BOOL success = GetProcessAffinityMask(phnd, &process_mask, &system_mask);
      if (success) {
         if (process_mask != 0x00000001) {
            /// more than one logical processor available for the process
            /// f.e. hyperthreading capable and enabled processors
            /// f.e. SMP board with more than one processor
            success = SetProcessAffinityMask(phnd, 0x00000001);
            if (success) {
               /// use only one processor to execute threads
            } else {
               int err = GetLastError();
            }
         }
         /// only one logical processor available
      } else {
         int err = GetLastError();
      }
#elif defined(__linux__)
PORT_LEVEL_5
#else
NO_PLATFORM
#endif
   }
  //## end cSystemUtils::SetArchitectureFlags%1130348758.body
}

MEMORY_BLOCK_T * cSystemUtils::MemoryBlock (void *memory)
{
  //## begin cSystemUtils::MemoryBlock%1106400838.body preserve=yes
   MEMORY_BLOCK_MAP_T::const_iterator i = _MemoryBlocks.find(memory);
   if (i == _MemoryBlocks.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cSystemUtils::MemoryBlock%1106400838.body
}

// Additional Declarations
  //## begin cSystemUtils%3B8A23E00182.declarations preserve=yes

#undef OVERLOAD_NEW_DELETE
#ifdef OVERLOAD_NEW_DELETE

unsigned long long _allocatedObjects = 0;

void * operator new [] (size_t size)
{
   _allocatedObjects++;
   void * memory = calloc(1, size);
   if (memory == 0) {
      throw std::bad_alloc();
   }
   memset(memory, -1, size);
   return memory;
}

void operator delete [] (void * p)
{
   free(p);
   _allocatedObjects--;
}

void * operator new (size_t size)
{
   _allocatedObjects++;
   void * memory = calloc(1, size);
   if (memory == 0) {
      throw std::bad_alloc();
   }
   memset(memory, -1, size);
   return memory;
}

void operator delete (void * p)
{
   free(p);
   _allocatedObjects--;
}

#endif

BOOL_T cSystemUtils::IsMainThread()
{
   if (ThreadId() == _MainThreadId) {
      return true;
   } else {
      return false;
   }
}

ULONG_T cSystemUtils::MainThreadId()
{
   return _MainThreadId;
}

void cSystemUtils::SetMainThread()
{
   _MainThreadId = ThreadId();
}

  //## end cSystemUtils%3B8A23E00182.declarations

//## begin module%3B8A23E00182.epilog preserve=yes
//## end module%3B8A23E00182.epilog

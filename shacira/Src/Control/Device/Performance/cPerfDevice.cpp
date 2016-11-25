//## begin module%428C87EE01F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%428C87EE01F4.cm

//## begin module%428C87EE01F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%428C87EE01F4.cp

//## Module: cPerfDevice%428C87EE01F4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\Performance\cPerfDevice.cpp

//## begin module%428C87EE01F4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%428C87EE01F4.additionalIncludes

//## begin module%428C87EE01F4.includes preserve=yes
//## end module%428C87EE01F4.includes

// cChannel
#include "System/Channel/cChannel.h"
// cPerfDevice
#include "Control/Device/Performance/cPerfDevice.h"
//## begin module%428C87EE01F4.additionalDeclarations preserve=yes

#define PERF_BUFFER_SPECIFICATION  "perf"
#define BLOCKS_ALLOCATED  "nblock"
#define TRANSIENT_OBJECTS  "nobj"
#define CPU_TIME  "cputime"
#define CPU_UTILIZATION  "cputil"
#define MEMORY  "nmem"
#define THREADS  "nthread"
#define VIRTUAL_MEMORY  "nvirtmem"
#define REFRESH_CMD  "refresh"
#define GDI_OBJECTS  "ngdiobjects"
#define USER_OBJECTS  "nuserobjects"

#define CHANNEL_BUFFER_SPECIFICATION  "channel"

unsigned long _VirtualMemory = 0;
unsigned long _TransientObjects = 0;

//## end module%428C87EE01F4.additionalDeclarations


// Class cPerfDevice 







cPerfDevice::cPerfDevice()
  //## begin cPerfDevice::cPerfDevice%.hasinit preserve=no
      : _PerfObject(NULL), _Start(false), _ProcessId(0)
  //## end cPerfDevice::cPerfDevice%.hasinit
  //## begin cPerfDevice::cPerfDevice%.initialization preserve=yes
  //## end cPerfDevice::cPerfDevice%.initialization
{
  //## begin cPerfDevice::cPerfDevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cPerfDevice::cPerfDevice%.body
}

cPerfDevice::cPerfDevice(const cPerfDevice &right)
  //## begin cPerfDevice::cPerfDevice%copy.hasinit preserve=no
      : _PerfObject(NULL), _Start(false), _ProcessId(0)
  //## end cPerfDevice::cPerfDevice%copy.hasinit
  //## begin cPerfDevice::cPerfDevice%copy.initialization preserve=yes
  //## end cPerfDevice::cPerfDevice%copy.initialization
{
  //## begin cPerfDevice::cPerfDevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPerfDevice::cPerfDevice%copy.body
}

cPerfDevice::cPerfDevice (cConfigurationObject *config_obj, cCell *cell)
  //## begin cPerfDevice::cPerfDevice%1116506566.hasinit preserve=no
      : _PerfObject(NULL), _Start(false), _ProcessId(0)
  //## end cPerfDevice::cPerfDevice%1116506566.hasinit
  //## begin cPerfDevice::cPerfDevice%1116506566.initialization preserve=yes
   , cDevice(config_obj, cell)
  //## end cPerfDevice::cPerfDevice%1116506566.initialization
{
  //## begin cPerfDevice::cPerfDevice%1116506566.body preserve=yes
   memset(&_PerfData, 0, sizeof(_PerfData));
   memset(&_BackupPerfData, 0, sizeof(_BackupPerfData));
   memset(_Channels, 0, sizeof(_Channels));
   _PerfObject = new cPerformance;
   _ProcessId = cSystemUtils::ProcessId();
  //## end cPerfDevice::cPerfDevice%1116506566.body
}


cPerfDevice::~cPerfDevice()
{
  //## begin cPerfDevice::~cPerfDevice%.body preserve=yes
   DELETE_OBJECT(cPerformance,_PerfObject)
  //## end cPerfDevice::~cPerfDevice%.body
}



//## Other Operations (implementation)
void cPerfDevice::Start ()
{
  //## begin cPerfDevice::Start%1116506567.body preserve=yes
  //## end cPerfDevice::Start%1116506567.body
}

void cPerfDevice::Stop ()
{
  //## begin cPerfDevice::Stop%1116506568.body preserve=yes
  //## end cPerfDevice::Stop%1116506568.body
}

void cPerfDevice::Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size)
{
  //## begin cPerfDevice::Cache%1116506569.body preserve=yes
  //## end cPerfDevice::Cache%1116506569.body
}

void cPerfDevice::Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements)
{
  //## begin cPerfDevice::Buffer%1116506570.body preserve=yes
  //## end cPerfDevice::Buffer%1116506570.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1116506572.body preserve=yes
   ULONG_T lval = 0;
   Get(buf_spec, name, lval);
   value = (UCHAR_T)lval;
  //## end cPerfDevice::Get%1116506572.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1116506573.body preserve=yes
   ULONG_T lval = 0;
   Get(buf_spec, name, lval);
   value = (UCHAR_T)lval;
  //## end cPerfDevice::Get%1116506573.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1116506574.body preserve=yes
   if (IDENTIFIER_EQUAL(buf_spec, PERF_BUFFER_SPECIFICATION)) {
      if (IDENTIFIER_EQUAL(name, BLOCKS_ALLOCATED)) {
         value = _PerfData.blocks_allocated;
      } else if (IDENTIFIER_EQUAL(name, TRANSIENT_OBJECTS)) {
         value = _PerfData.transient_objects;
         _TransientObjects = value;
      } else if (IDENTIFIER_EQUAL(name, CPU_TIME)) {
         DOUBLE_T fval = _PerfObject->CPUTime(_ProcessId);
         value = (ULONG_T)fval;
      } else if (IDENTIFIER_EQUAL(name, CPU_UTILIZATION)) {
         value = _PerfObject->Utilization(_ProcessId);
      } else if (IDENTIFIER_EQUAL(name, THREADS)) {
         value = _PerfObject->Threads(_ProcessId);
      } else if (IDENTIFIER_EQUAL(name, MEMORY)) {
         value = _PerfObject->Memory(_ProcessId);
      } else if (IDENTIFIER_EQUAL(name, VIRTUAL_MEMORY)) {
         value = _PerfObject->VirtualMemory(_ProcessId);
         _VirtualMemory = value;
      } else if (IDENTIFIER_EQUAL(name, GDI_OBJECTS)) {
         value = _PerfObject->GDIObjects();
      } else if (IDENTIFIER_EQUAL(name, USER_OBJECTS)) {
         value = _PerfObject->UserObjects();
      } else {
         value = 0;
      }
   } else if (IDENTIFIER_EQUAL(buf_spec, CHANNEL_BUFFER_SPECIFICATION)) {
      ULONG_T channel_index = 0;
      if (sscanf(name, "name_%d", &channel_index) == 1) {
      } else if (sscanf(name, "size_%d", &channel_index) == 1) {
         cChannel * channel = cChannel::GetChannel(channel_index);
         if (channel != NULL) {
            value = channel->Size();
         }
      } else if (sscanf(name, "fill_%d", &channel_index) == 1) {
         cChannel * channel = cChannel::GetChannel(channel_index);
         if (channel != NULL) {
            value = channel->Fill();
         }
      }
   }
  //## end cPerfDevice::Get%1116506574.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1116506575.body preserve=yes
   CHAR_T sval[0x200] = {0};
   if (IDENTIFIER_EQUAL(buf_spec, PERF_BUFFER_SPECIFICATION)) {
      if (IDENTIFIER_EQUAL(name, BLOCKS_ALLOCATED)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, TRANSIENT_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, CPU_TIME)) {
         DOUBLE_T fval = 0;
         Get(buf_spec, name, fval);
         SafePrintf(sval, sizeof(sval), "%f", fval);
      } else if (IDENTIFIER_EQUAL(name, CPU_UTILIZATION)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, THREADS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, MEMORY)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, VIRTUAL_MEMORY)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
       } else if (IDENTIFIER_EQUAL(name, GDI_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
      } else if (IDENTIFIER_EQUAL(name, USER_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
     } else {
         SafePrintf(sval, sizeof(sval), "0");
      }
      value = sval;
   } else if (IDENTIFIER_EQUAL(buf_spec, CHANNEL_BUFFER_SPECIFICATION)) {
      ULONG_T channel_index = 0;
      if (sscanf(name, "name_%d", &channel_index) == 1) {
         cChannel * channel = cChannel::GetChannel(channel_index);
         if (channel != NULL) {
            value = channel->get_Name();
         }
      } else {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         SafePrintf(sval, sizeof(sval), "%d", lval);
         value = sval;
      }
   }
  //## end cPerfDevice::Get%1116506575.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1116507645.body preserve=yes
   DOUBLE_T fval = 0;
   if (IDENTIFIER_EQUAL(buf_spec, PERF_BUFFER_SPECIFICATION)) {
      if (IDENTIFIER_EQUAL(name, BLOCKS_ALLOCATED)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, TRANSIENT_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, CPU_TIME)) {
         fval = _PerfObject->CPUTime(_ProcessId);
      } else if (IDENTIFIER_EQUAL(name, CPU_UTILIZATION)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, THREADS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, MEMORY)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, VIRTUAL_MEMORY)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, GDI_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else if (IDENTIFIER_EQUAL(name, USER_OBJECTS)) {
         ULONG_T lval = 0;
         Get(buf_spec, name, lval);
         fval = (DOUBLE_T)lval;
      } else {
         fval = 0;
      }
      value = fval;
   } else if (IDENTIFIER_EQUAL(buf_spec, CHANNEL_BUFFER_SPECIFICATION)) {
      ULONG_T lval = 0;
      Get(buf_spec, name, lval);
      value = (DOUBLE_T)lval;
   }
  //## end cPerfDevice::Get%1116507645.body
}

void cPerfDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags)
{
  //## begin cPerfDevice::Set%1116506576.body preserve=yes
   ULONG_T lval = value;
   Set(buf_spec, name, lval);
  //## end cPerfDevice::Set%1116506576.body
}

void cPerfDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags)
{
  //## begin cPerfDevice::Set%1116506577.body preserve=yes
   ULONG_T lval = value;
   Set(buf_spec, name, lval);
  //## end cPerfDevice::Set%1116506577.body
}

void cPerfDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags)
{
  //## begin cPerfDevice::Set%1116506578.body preserve=yes
   if (IDENTIFIER_EQUAL(name, BLOCKS_ALLOCATED)) {
   } else if (IDENTIFIER_EQUAL(name, TRANSIENT_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, CPU_TIME)) {
   } else if (IDENTIFIER_EQUAL(name, CPU_UTILIZATION)) {
   } else if (IDENTIFIER_EQUAL(name, THREADS)) {
   } else if (IDENTIFIER_EQUAL(name, MEMORY)) {
   } else if (IDENTIFIER_EQUAL(name, VIRTUAL_MEMORY)) {
   } else if (IDENTIFIER_EQUAL(name, GDI_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, USER_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, REFRESH_CMD)) {
      if (value != 0) {
         Refresh();
      }
   }
  //## end cPerfDevice::Set%1116506578.body
}

void cPerfDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags)
{
  //## begin cPerfDevice::Set%1116507646.body preserve=yes
   if (IDENTIFIER_EQUAL(name, BLOCKS_ALLOCATED)) {
   } else if (IDENTIFIER_EQUAL(name, TRANSIENT_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, CPU_TIME)) {
   } else if (IDENTIFIER_EQUAL(name, CPU_UTILIZATION)) {
   } else if (IDENTIFIER_EQUAL(name, THREADS)) {
   } else if (IDENTIFIER_EQUAL(name, MEMORY)) {
   } else if (IDENTIFIER_EQUAL(name, VIRTUAL_MEMORY)) {
   } else if (IDENTIFIER_EQUAL(name, GDI_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, USER_OBJECTS)) {
   } else if (IDENTIFIER_EQUAL(name, REFRESH_CMD)) {
      ULONG_T lval = strtoul(value, NULL, 0);
      if (lval != 0) {
         Refresh();
      }
   }
  //## end cPerfDevice::Set%1116507646.body
}

void cPerfDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags)
{
  //## begin cPerfDevice::Set%1116507647.body preserve=yes
  //## end cPerfDevice::Set%1116507647.body
}

void cPerfDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value)
{
  //## begin cPerfDevice::Cast%1116506579.body preserve=yes
  //## end cPerfDevice::Cast%1116506579.body
}

void cPerfDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cPerfDevice::Read%1116506580.body preserve=yes
  //## end cPerfDevice::Read%1116506580.body
}

void cPerfDevice::Refresh ()
{
  //## begin cPerfDevice::Refresh%1116507648.body preserve=yes
   memset(_Channels, 0, sizeof(_Channels));
   memcpy(&_BackupPerfData, &_PerfData, sizeof(_BackupPerfData));
   memset(&_PerfData, 0, sizeof(_PerfData));
   _PerfData.blocks_allocated = cSystemUtils::AllocatedBlocks();
   _PerfData.transient_objects = cTransientObject::get_ObjectCount();
   _PerfObject->Refresh();
   ULONG_T pid = cSystemUtils::ProcessId();
   _PerfData.cpu_time = _PerfObject->CPUTime(pid);
   _PerfData.cpu_utilization = _PerfObject->Utilization(pid);
   _PerfData.memory = _PerfObject->Memory(pid);
   _PerfData.virtual_memory = _PerfObject->VirtualMemory(pid);
   _PerfData.threads = _PerfObject->Threads(pid);
   _PerfData.user_objects = _PerfObject->UserObjects();
   _PerfData.gdi_objects = _PerfObject->GDIObjects();
   if (_PerfData.blocks_allocated != _BackupPerfData.blocks_allocated) {
      Changed(PERF_BUFFER_SPECIFICATION, BLOCKS_ALLOCATED);
   }
   if (_PerfData.transient_objects != _BackupPerfData.transient_objects) {
      Changed(PERF_BUFFER_SPECIFICATION, TRANSIENT_OBJECTS);
   }
   if (_PerfData.cpu_time != _BackupPerfData.cpu_time) {
      Changed(PERF_BUFFER_SPECIFICATION, CPU_TIME);
   }
   if (_PerfData.cpu_utilization != _BackupPerfData.cpu_utilization) {
      Changed(PERF_BUFFER_SPECIFICATION, CPU_UTILIZATION);
   }
   if (_PerfData.memory != _BackupPerfData.memory) {
      Changed(PERF_BUFFER_SPECIFICATION, MEMORY);
   }
   if (_PerfData.virtual_memory != _BackupPerfData.virtual_memory) {
      Changed(PERF_BUFFER_SPECIFICATION, VIRTUAL_MEMORY);
   }
   if (_PerfData.threads != _BackupPerfData.threads) {
      Changed(PERF_BUFFER_SPECIFICATION, THREADS);
   }
   if (_PerfData.user_objects != _BackupPerfData.user_objects) {
      Changed(PERF_BUFFER_SPECIFICATION, USER_OBJECTS);
   }
   if (_PerfData.gdi_objects != _BackupPerfData.gdi_objects) {
      Changed(PERF_BUFFER_SPECIFICATION, GDI_OBJECTS);
   }
   ULONG_T channel_count = cChannel::GetChannelCount();
   for (ULONG_T i=0; i<channel_count; i++) {
      cChannel * channel = cChannel::GetChannel(i);
      if (channel != NULL) {
         _Channels[i] = channel;
         char name[100] = {0};
         SafePrintf(name, sizeof(name), "name_%d", i);
         Changed(CHANNEL_BUFFER_SPECIFICATION, name);
         SafePrintf(name, sizeof(name), "size_%d", i);
         Changed(CHANNEL_BUFFER_SPECIFICATION, name);
         SafePrintf(name, sizeof(name), "fill_%d", i);
         Changed(CHANNEL_BUFFER_SPECIFICATION, name);
      }
   }
  //## end cPerfDevice::Refresh%1116507648.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1121073529.body preserve=yes
  //## end cPerfDevice::Get%1121073529.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, LONG_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1121073530.body preserve=yes
  //## end cPerfDevice::Get%1121073530.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1121073531.body preserve=yes
  //## end cPerfDevice::Get%1121073531.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, STRING_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1121073532.body preserve=yes
  //## end cPerfDevice::Get%1121073532.body
}

void cPerfDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T &value, ULONG_T flags)
{
  //## begin cPerfDevice::Get%1121073533.body preserve=yes
  //## end cPerfDevice::Get%1121073533.body
}

// Additional Declarations
  //## begin cPerfDevice%428C87EE01F4.declarations preserve=yes
  //## end cPerfDevice%428C87EE01F4.declarations

//## begin module%428C87EE01F4.epilog preserve=yes
//## end module%428C87EE01F4.epilog

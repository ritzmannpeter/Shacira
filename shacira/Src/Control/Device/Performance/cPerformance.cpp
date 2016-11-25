
#include "cPerformance.h"

#if defined(_WIN32)

DWORD PX_PROCESS;
DWORD PX_PROCESS_CPU;
DWORD PX_PROCESS_PRIV;
DWORD PX_PROCESS_USER;
DWORD PX_PROCESS_WORKING_SET;
DWORD PX_PROCESS_PEAK_WS;
DWORD PX_PROCESS_PRIO;
DWORD PX_PROCESS_ELAPSE;
DWORD PX_PROCESS_ID;
DWORD PX_PROCESS_PRIVATE_PAGE;
DWORD PX_PROCESS_VIRTUAL_SIZE;
DWORD PX_PROCESS_PEAK_VS;
DWORD PX_PROCESS_FAULT_COUNT;
DWORD PX_PROCESS_PAGED_POOL_QUOTA;
DWORD PX_PROCESS_PEAK_PAGED_POOL_QUOTA;
DWORD PX_PROCESS_NONPAGED_POOL_QUOTA;
DWORD PX_PROCESS_PEAK_PAGED_POOL;
DWORD PX_PROCESS_PEAK_NONPAGED_POOL;
DWORD PX_PROCESS_CUR_PAGED_POOL;
DWORD PX_PROCESS_CUR_NONPAGED_POOL;
DWORD PX_PROCESS_PAGED_POOL_LIMIT;
DWORD PX_PROCESS_NONPAGED_POOL_LIMIT;

DWORD PX_THREAD;
DWORD PX_THREAD_CPU;
DWORD PX_THREAD_PRIV;
DWORD PX_THREAD_USER;
DWORD PX_THREAD_START;
DWORD PX_THREAD_SWITCHES;
DWORD PX_THREAD_PRIO;
DWORD PX_THREAD_BASE_PRIO;
DWORD PX_THREAD_ELAPSE;

DWORD PX_THREAD_DETAILS;
DWORD PX_THREAD_PC;

DWORD PX_IMAGE;
DWORD PX_IMAGE_NOACCESS;
DWORD PX_IMAGE_READONLY;
DWORD PX_IMAGE_READWRITE;
DWORD PX_IMAGE_WRITECOPY;
DWORD PX_IMAGE_EXECUTABLE;
DWORD PX_IMAGE_EXE_READONLY;
DWORD PX_IMAGE_EXE_READWRITE;
DWORD PX_IMAGE_EXE_WRITECOPY;

DWORD PX_PROCESS_ADDRESS_SPACE;
DWORD PX_PROCESS_PRIVATE_NOACCESS;
DWORD PX_PROCESS_PRIVATE_READONLY;
DWORD PX_PROCESS_PRIVATE_READWRITE;
DWORD PX_PROCESS_PRIVATE_WRITECOPY;
DWORD PX_PROCESS_PRIVATE_EXECUTABLE;
DWORD PX_PROCESS_PRIVATE_EXE_READONLY;
DWORD PX_PROCESS_PRIVATE_EXE_READWRITE;
DWORD PX_PROCESS_PRIVATE_EXE_WRITECOPY;

DWORD PX_PROCESS_MAPPED_NOACCESS;
DWORD PX_PROCESS_MAPPED_READONLY;
DWORD PX_PROCESS_MAPPED_READWRITE;
DWORD PX_PROCESS_MAPPED_WRITECOPY;
DWORD PX_PROCESS_MAPPED_EXECUTABLE;
DWORD PX_PROCESS_MAPPED_EXE_READONLY;
DWORD PX_PROCESS_MAPPED_EXE_READWRITE;
DWORD PX_PROCESS_MAPPED_EXE_WRITECOPY;

DWORD PX_PROCESS_IMAGE_NOACCESS;
DWORD PX_PROCESS_IMAGE_READONLY;
DWORD PX_PROCESS_IMAGE_READWRITE;
DWORD PX_PROCESS_IMAGE_WRITECOPY;
DWORD PX_PROCESS_IMAGE_EXECUTABLE;
DWORD PX_PROCESS_IMAGE_EXE_READONLY;
DWORD PX_PROCESS_IMAGE_EXE_READWRITE;
DWORD PX_PROCESS_IMAGE_EXE_WRITECOPY;

#endif

static cPerformance * _PerfObject = NULL;

#if (WINVER < 0x0500)

HMODULE cPerformance::_User32DllModule = NULL;

GETGUIRESOURCES_T cPerformance::_GetGuiResourcesAddr = NULL;

#endif

cPerformance::cPerformance()
{
#if defined(_WIN32)
   memset(_ProcessData, 0, sizeof(_ProcessData));
   memset(_BackupProcessData, 0, sizeof(_BackupProcessData));
   for (int i=0; i<MAX_PROCESSES; i++) {
      _ProcessData[i].id = -1; 
   }
   _PerfKey = HKEY_PERFORMANCE_DATA;  // get perf data from this key
   _MachineKey = HKEY_LOCAL_MACHINE;  // get title index from this key
   _PerfDataSize = 50*1024;           // start with 50K
   _PerfData = NULL;
   _LastRefresh = 0;
   _Elapsed = 0;
   if (SetPerfIndices()) {
      _PerfObject = this;
   }
#endif
}

cPerformance::~cPerformance()
{
}

void cPerformance::Refresh()
{
#if defined(_WIN32)
   _PerfData = RefreshPerfData(_PerfKey, _ThreadObjIndices, _PerfData, &_PerfDataSize);
   PPERF_OBJECT process_object = FindObject(_PerfData, PX_PROCESS);
   if (process_object != NULL) {
      RefreshData(process_object);
   }
#endif
}

void cPerformance::Print(BOOL_T only_me)
{
#if defined(_WIN32)
   if (only_me) {
      ULONG_T pi = GetCurrentProcessId();
      printf("p %s %04d", Name(pi), pi);
      printf(" %03d %%", Utilization(pi));
      printf(" %d kB", Memory(pi));
      printf(" %d kB", VirtualMemory(pi));
      printf(" t %d", Threads(pi));
      printf("\n");
   } else {
      for (int i=0; i<MAX_PROCESSES; i++) {
         if (_ProcessData[i].id != -1 &&
            _ProcessData[i].utilization != 0 ||
//             strncmp(_ProcessData[i].name, "mosaic", 5) == 0 ||
             false) {
#define direct_printx
#ifdef direct_print
            printf("p %s %04d", _ProcessData[i].name, _ProcessData[i].id);
            printf(" %03d %%", _ProcessData[i].utilization);
            printf(" %d kB", _ProcessData[i].memory);
            printf(" %d kB", _ProcessData[i].virt_memory);
            printf(" t %d", _ProcessData[i].threads);
#else
            ULONG_T pi = _ProcessData[i].id;
            printf("p %s %04d", Name(pi), pi);
            printf(" %03d %%", Utilization(pi));
            printf(" %d kB", Memory(pi));
            printf(" %d kB", VirtualMemory(pi));
            printf(" t %d", Threads(pi));
#endif
            printf("\n");
         }
      }
      printf("\n");
   }
#endif
}

void cPerformance::PrintMemory(FILE * stream)
{
#if defined(_WIN32)
   fprintf(stream, "memory statistics:\n");
   for (int i=0; i<MAX_PROCESSES; i++) {
      if (_ProcessData[i].id != -1) {
         fprintf(stream, "%s %d kB", _ProcessData[i].name, _ProcessData[i].virt_memory);
         fprintf(stream, "\n");
      }
   }
#endif
}

CONST_STRING_T cPerformance::Name(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->name;
   }
#endif
   return "??";
}

double cPerformance::CPUTime(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->cpu;
   }
#endif
   return 0;
}

ULONG_T cPerformance::Utilization(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->utilization;
   }
#endif
   return 0;
}

ULONG_T cPerformance::Memory(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->memory;
   }
#endif
   return 0;
}

ULONG_T cPerformance::VirtualMemory(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->virt_memory;
   }
#endif
   return 0;
}

#if defined(_WIN32)
#if (WINVER < 0x0500)
DWORD cPerformance::GetGuiResources(HANDLE hprocess, DWORD flags)
{
   if (_User32DllModule == NULL) {
      _User32DllModule = LoadLibrary("USER32.dll");
   }
   if (_User32DllModule != NULL) {
      if (_GetGuiResourcesAddr == NULL) {
         _GetGuiResourcesAddr = (GETGUIRESOURCES_T)GetProcAddress(_User32DllModule, "GetGuiResources");
      }
      if (_GetGuiResourcesAddr != NULL) {
         return _GetGuiResourcesAddr(hprocess, flags);
      }
   }
   return 0;
}
#endif
#endif

ULONG_T cPerformance::GDIObjects()
{
#if defined(_WIN32)
   return GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
#else
   return 0;
#endif
}

ULONG_T cPerformance::UserObjects()
{
#if defined(_WIN32)
   return GetGuiResources(GetCurrentProcess(), GR_USEROBJECTS);
#else
   return 0;
#endif
}

ULONG_T cPerformance::Threads(ULONG_T process_id)
{
#if defined(_WIN32)
   PROCESS_T * process = FindProcessById(process_id);
   if (process != NULL) {
      return process->threads;
   }
#endif
   return 0;
}

BOOL_T cPerformance::IsRunning(CONST_STRING_T process_name, BOOL_T exclude_me)
{
#if defined(_WIN32)
   for (int i=0; i<MAX_PROCESSES; i++) {
      if (_ProcessData[i].id != -1) {
         if (_strnicmp(process_name, _ProcessData[i].name, strlen(process_name)) == 0) {
            if (exclude_me) {
               int my_id = GetCurrentProcessId();
               int process_id = _ProcessData[i].id;
               if (my_id != process_id) {
                  return true;
               }
            } else {
               return true;
            }
         }
      }
   }
#endif
   return false;
}

BOOL_T cPerformance::GetProcessId(CONST_STRING_T process_name, ULONG_T &process_id, BOOL_T exclude_me)
{
#if defined(_WIN32)
   for (int i=0; i<MAX_PROCESSES; i++) {
      if (_ProcessData[i].id != -1) {
         if (_strnicmp(process_name, _ProcessData[i].name, strlen(process_name)) == 0) {
            if (exclude_me) {
               if (GetCurrentProcessId() != _ProcessData[i].id) {
                  process_id = _ProcessData[i].id;
                  return true;
               }
            } else {
               process_id = _ProcessData[i].id;
               return true;
            }
         }
      }
   }
#endif
   return false;
}

// private methods

BOOL_T cPerformance::SetPerfIndices()
{
#if defined(_WIN32)
   DWORD last;
   LPTSTR title_buf;
   LPTSTR * title;
   DWORD rc = 0;

   rc = GetPerfTitleSz(_MachineKey, _PerfKey, &title_buf, &title, &last);
   if (rc != ERROR_SUCCESS) {
      return false;
   }
   
   PX_PROCESS = GetPerfIndex(title, last, PN_PROCESS);
   PX_PROCESS_CPU = GetPerfIndex(title, last, PN_PROCESS_CPU);
   PX_PROCESS_PRIV = GetPerfIndex(title, last, PN_PROCESS_PRIV);
   PX_PROCESS_USER = GetPerfIndex(title, last, PN_PROCESS_USER);
   PX_PROCESS_WORKING_SET = GetPerfIndex(title, last, PN_PROCESS_WORKING_SET);
   PX_PROCESS_PEAK_WS = GetPerfIndex(title, last, PN_PROCESS_PEAK_WS);
   PX_PROCESS_PRIO = GetPerfIndex(title, last, PN_PROCESS_PRIO);
   PX_PROCESS_ELAPSE = GetPerfIndex(title, last, PN_PROCESS_ELAPSE);
   PX_PROCESS_ID = GetPerfIndex(title, last, PN_PROCESS_ID);
   PX_PROCESS_PRIVATE_PAGE = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_PAGE);
   PX_PROCESS_VIRTUAL_SIZE = GetPerfIndex(title, last, PN_PROCESS_VIRTUAL_SIZE);
   PX_PROCESS_PEAK_VS = GetPerfIndex(title, last, PN_PROCESS_PEAK_VS);
   PX_PROCESS_FAULT_COUNT = GetPerfIndex(title, last, PN_PROCESS_FAULT_COUNT);

   PX_THREAD = GetPerfIndex(title, last, PN_THREAD);
   PX_THREAD_CPU = GetPerfIndex(title, last, PN_THREAD_CPU);
   PX_THREAD_PRIV = GetPerfIndex(title, last, PN_THREAD_PRIV);
   PX_THREAD_USER = GetPerfIndex(title, last, PN_THREAD_USER);
   PX_THREAD_START = GetPerfIndex(title, last, PN_THREAD_START);
   PX_THREAD_SWITCHES = GetPerfIndex(title, last, PN_THREAD_SWITCHES);
   PX_THREAD_PRIO = GetPerfIndex(title, last, PN_THREAD_PRIO);
   PX_THREAD_BASE_PRIO = GetPerfIndex(title, last, PN_THREAD_BASE_PRIO);
   PX_THREAD_ELAPSE = GetPerfIndex(title, last, PN_THREAD_ELAPSE);

   PX_THREAD_DETAILS = GetPerfIndex(title, last, PN_THREAD_DETAILS);
   PX_THREAD_PC = GetPerfIndex(title, last, PN_THREAD_PC);

   PX_IMAGE = GetPerfIndex(title, last, PN_IMAGE);
   PX_IMAGE_NOACCESS = GetPerfIndex(title, last, PN_IMAGE_NOACCESS);
   PX_IMAGE_READONLY = GetPerfIndex(title, last, PN_IMAGE_READONLY);
   PX_IMAGE_READWRITE = GetPerfIndex(title, last, PN_IMAGE_READWRITE);
   PX_IMAGE_WRITECOPY = GetPerfIndex(title, last, PN_IMAGE_WRITECOPY);
   PX_IMAGE_EXECUTABLE = GetPerfIndex(title, last, PN_IMAGE_EXECUTABLE);
   PX_IMAGE_EXE_READONLY = GetPerfIndex(title, last, PN_IMAGE_EXE_READONLY);
   PX_IMAGE_EXE_READWRITE = GetPerfIndex(title, last, PN_IMAGE_EXE_READWRITE);
   PX_IMAGE_EXE_WRITECOPY = GetPerfIndex(title, last, PN_IMAGE_EXE_WRITECOPY);

   PX_PROCESS_ADDRESS_SPACE = GetPerfIndex(title, last, PN_PROCESS_ADDRESS_SPACE);
   PX_PROCESS_PRIVATE_NOACCESS = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_NOACCESS);
   PX_PROCESS_PRIVATE_READONLY = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_READONLY);
   PX_PROCESS_PRIVATE_READWRITE = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_READWRITE);
   PX_PROCESS_PRIVATE_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_WRITECOPY);
   PX_PROCESS_PRIVATE_EXECUTABLE = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_EXECUTABLE);
   PX_PROCESS_PRIVATE_EXE_READONLY = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_EXE_READONLY);
   PX_PROCESS_PRIVATE_EXE_READWRITE = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_EXE_READWRITE);
   PX_PROCESS_PRIVATE_EXE_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_PRIVATE_EXE_WRITECOPY);

   PX_PROCESS_MAPPED_NOACCESS = GetPerfIndex(title, last, PN_PROCESS_MAPPED_NOACCESS);
   PX_PROCESS_MAPPED_READONLY = GetPerfIndex(title, last, PN_PROCESS_MAPPED_READONLY);
   PX_PROCESS_MAPPED_READWRITE = GetPerfIndex(title, last, PN_PROCESS_MAPPED_READWRITE);
   PX_PROCESS_MAPPED_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_MAPPED_WRITECOPY);
   PX_PROCESS_MAPPED_EXECUTABLE = GetPerfIndex(title, last, PN_PROCESS_MAPPED_EXECUTABLE);
   PX_PROCESS_MAPPED_EXE_READONLY = GetPerfIndex(title, last, PN_PROCESS_MAPPED_EXE_READONLY);
   PX_PROCESS_MAPPED_EXE_READWRITE = GetPerfIndex(title, last, PN_PROCESS_MAPPED_EXE_READWRITE);
   PX_PROCESS_MAPPED_EXE_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_MAPPED_EXE_WRITECOPY);

   PX_PROCESS_IMAGE_NOACCESS = GetPerfIndex(title, last, PN_PROCESS_IMAGE_NOACCESS);
   PX_PROCESS_IMAGE_READONLY = GetPerfIndex(title, last, PN_PROCESS_IMAGE_READONLY);
   PX_PROCESS_IMAGE_READWRITE = GetPerfIndex(title, last, PN_PROCESS_IMAGE_READWRITE);
   PX_PROCESS_IMAGE_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_IMAGE_WRITECOPY);
   PX_PROCESS_IMAGE_EXECUTABLE = GetPerfIndex(title, last, PN_PROCESS_IMAGE_EXECUTABLE);
   PX_PROCESS_IMAGE_EXE_READONLY = GetPerfIndex(title, last, PN_PROCESS_IMAGE_EXE_READONLY);
   PX_PROCESS_IMAGE_EXE_READWRITE = GetPerfIndex(title, last, PN_PROCESS_IMAGE_EXE_READWRITE);
   PX_PROCESS_IMAGE_EXE_WRITECOPY = GetPerfIndex(title, last, PN_PROCESS_IMAGE_EXE_WRITECOPY);

   wsprintf(_ThreadObjIndices, TEXT("%ld %ld"), PX_PROCESS, PX_THREAD);
   wsprintf(_CostlyObjIndices, TEXT("%ld %ld %ld"),
            PX_PROCESS_ADDRESS_SPACE, PX_IMAGE, PX_THREAD_DETAILS);
   LocalFree(title_buf);
   LocalFree(title);
#endif
   return true;
}

DWORD cPerformance::GetPerfIndex(LPTSTR title[], DWORD last_index,LPTSTR name)
{
#if defined(_WIN32)
   DWORD index;
   for (index = 0; index <= last_index; index++) {
      if (title[index]) {
         if (!lstrcmpi(title[index], name)) {
            return index;
         }
      }
   }
#endif
   return 0;
}

PPERF_DATA cPerformance::RefreshPerfData(HKEY key, LPTSTR object_index, PPERF_DATA data, DWORD * data_size)
{
#if defined(_WIN32)
   _Elapsed = GetTickCount() - _LastRefresh;
   _LastRefresh = GetTickCount();
   if (GetPerfData(key, object_index, &data, data_size) == ERROR_SUCCESS) {
      return data;
   }
#endif
   return NULL;
}

void cPerformance::RefreshData(PPERF_OBJECT object)
{
#if defined(_WIN32)
   DWORD V_PROCESS_CPU = 0;
   DWORD V_PROCESS_PRIV = 0;
   DWORD V_PROCESS_USER = 0;
   DWORD V_PROCESS_WORKING_SET = 0;
   DWORD V_PROCESS_PEAK_WS = 0;
   DWORD V_PROCESS_PRIO = 0;
   DWORD V_PROCESS_ELAPSE = 0;
   DWORD V_PROCESS_ID = 0;
   DWORD V_PROCESS_PRIVATE_PAGE = 0;
   DWORD V_PROCESS_VIRTUAL_SIZE = 0;
   DWORD V_PROCESS_PEAK_VS = 0;
   DWORD V_PROCESS_FAULT_COUNT = 0;
   DWORD V_PROCESS_PAGED_POOL_QUOTA = 0;
   DWORD V_PROCESS_PEAK_PAGED_POOL_QUOTA = 0;
   DWORD V_PROCESS_NONPAGED_POOL_QUOTA = 0;
   DWORD V_PROCESS_PEAK_PAGED_POOL = 0;
   DWORD V_PROCESS_PEAK_NONPAGED_POOL = 0;
   DWORD V_PROCESS_CUR_PAGED_POOL = 0;
   DWORD V_PROCESS_CUR_NONPAGED_POOL = 0;
   DWORD V_PROCESS_PAGED_POOL_LIMIT = 0;
   DWORD V_PROCESS_NONPAGED_POOL_LIMIT = 0;

   memcpy(_BackupProcessData, _ProcessData, sizeof(_BackupProcessData));
   memset(_ProcessData, 0, sizeof(_ProcessData));
   for (int i=0; i<MAX_PROCESSES; i++) {
      _ProcessData[i].id = -1; 
   }

   PPERF_INSTANCE instance;
   INT inst_index = 0;
   if (object) {
      instance = FirstInstance(object);
      while (instance && inst_index < object->NumInstances) {
         PPERF_COUNTER counter;
         ULONG_T process_id = -1;
         ULONG_T process_memory = 0;
         ULONG_T process_virt_memory = 0;
         double cpu_time = 0;
         double priv_time = 0;
         LARGE_INTEGER * cpu;
         LARGE_INTEGER * priv;
         if (counter = FindCounter (object, PX_PROCESS_CPU)) {
            cpu = (LARGE_INTEGER*)CounterData(instance, counter);
            cpu_time  = Li2Double(*cpu);
         }
         if (counter = FindCounter (object, PX_PROCESS_PRIV)) {
            priv = (LARGE_INTEGER*)CounterData (instance, counter);
            priv_time = Li2Double(*priv);
         }
         if (counter = FindCounter (object, PX_PROCESS_USER)) {
            V_PROCESS_USER = *(DWORD *)CounterData(instance, counter);
         }
         if (counter = FindCounter (object, PX_PROCESS_WORKING_SET)) {
            V_PROCESS_WORKING_SET = (*(DWORD *)CounterData(instance, counter)) / 1024;
            process_memory = V_PROCESS_WORKING_SET;
         }
         if (counter = FindCounter (object, PX_PROCESS_PEAK_WS)) {
            V_PROCESS_PEAK_WS = *(DWORD *)CounterData(instance, counter);
         }
         if (counter = FindCounter (object, PX_PROCESS_PRIO)) {
            V_PROCESS_PRIO = *(DWORD *)CounterData(instance, counter);
         }
         if (counter = FindCounter (object, PX_PROCESS_ELAPSE)) {
            V_PROCESS_ELAPSE = *(DWORD *)CounterData(instance, counter);
         }
         if (counter = FindCounter (object, PX_PROCESS_ID)) {
            V_PROCESS_ID = *(DWORD *)CounterData(instance, counter);
            process_id = V_PROCESS_ID;
         }
         if (counter = FindCounter (object, PX_PROCESS_PRIVATE_PAGE)) {
            V_PROCESS_PRIVATE_PAGE = (*(DWORD *)CounterData(instance, counter)) / 1024;
         }
         if (counter = FindCounter (object, PX_PROCESS_VIRTUAL_SIZE)) {
            V_PROCESS_VIRTUAL_SIZE = (*(DWORD*)CounterData(instance, counter)) / 1024;
            process_virt_memory = V_PROCESS_PRIVATE_PAGE;
         }
         TIME_FIELD cpu_time_field;
         TIME_FIELD last_time_field;
         FormatTimeFields(cpu_time/1.0e7, &cpu_time_field);
         double last_cpu_time = GetLastCPUTime(process_id);
         FormatTimeFields(last_cpu_time/1.0e7, &last_time_field);
         double diff_time = MilliSeconds(&cpu_time_field) - MilliSeconds(&last_time_field);
         if (_Elapsed > 0) {
            diff_time = diff_time / _Elapsed;
            diff_time *= 100;
         }
         long utilization = (long)diff_time;
         if (utilization > 100) utilization = 100;
         if (utilization < 0) utilization = 0;
         if (process_id != -1 && inst_index < MAX_PROCESSES) {
            PROCESS_T * process = &(_ProcessData[inst_index]);
            if (process != NULL) {
               wsprintf(process->name, TEXT("%ls"), InstanceName(instance));
               process->id = process_id;
               process->cpu = cpu_time;
               process->utilization = utilization;
               process->memory = process_memory;
               process->virt_memory = process_virt_memory;
               PPERF_OBJECT thread_object = NULL;                    // pointer to process objects
               thread_object = FindObject(_PerfData, PX_THREAD);
               process->threads = ThreadCount(inst_index, thread_object);
            }
         }
         instance = NextInstance(instance);
         inst_index++;
      }
   }
#endif
}

void cPerformance::FormatTimeFields(double time, TIME_FIELD * time_field)
{
#if defined(_WIN32)
   INT i;
   double f;
   f = time/3600;
   time_field->hours = i = (int)f;
   f = f - i;
   time_field->mins = i = (int)(f = f * 60);
   f = f - i;
   time_field->secs = i = (int)(f = f * 60);
   f = f - i;
   time_field->msecs = (int)(f * 1000);
#endif
}

DWORD cPerformance::MilliSeconds(TIME_FIELD * time_field)
{
#if defined(_WIN32)
   DWORD secs = time_field->hours * 3600;
   secs *= time_field->mins * 60;
   secs += time_field->secs;
   DWORD msecs = secs * 1000;
   msecs += time_field->msecs;
   return msecs;
#else
   return 0;
#endif
}

double cPerformance::GetLastCPUTime(ULONG_T process_id)
{
#if defined(_WIN32)
   for (int i=0; i<MAX_PROCESSES; i++) {
      if (_BackupProcessData[i].id == process_id) {
         return _BackupProcessData[i].cpu;
      }
   }
#endif
   return 0;
}

DWORD cPerformance::ThreadCount(DWORD parent_index, PPERF_OBJECT object)
{
#if defined(_WIN32)
   DWORD count = 0;
   PPERF_INSTANCE instance;
   INT ins_index = 0;
   if (object) {
      instance = FirstInstance(object);
      while (instance && ins_index < object->NumInstances) {
         if (parent_index == instance->ParentObjectInstance) {
            count++;
         }
         instance = NextInstance (instance);
         ins_index++;
      }
   }
   return count;
#else
   return 0;
#endif
}

PROCESS_T * cPerformance::FindProcessById(ULONG_T process_id, BOOL_T background_data)
{
#if defined(_WIN32)
   for (int i=0; i<MAX_PROCESSES; i++) {
      if (_ProcessData[i].id == process_id) {
         return &(_ProcessData[i]);
      }
   }
#endif
   return NULL;
}

extern "C" {

void PrintMemStatistics(FILE * stream)
{
#if defined(_WIN32)
   try {
      if (_PerfObject != NULL && stream != NULL) {
         _PerfObject->PrintMemory(stream);
      }
   } catch (...) {
   }
#endif
}

}


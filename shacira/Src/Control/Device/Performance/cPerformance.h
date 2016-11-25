
#ifdef _WIN32

#include <windows.h>
#include <winperf.h>
#include "Control/Device/Performance/perfdata.h"
#if (WINVER < 0x0500)
#define GR_GDIOBJECTS     0       /* Count of GDI objects */
#define GR_USEROBJECTS    1       /* Count of USER objects */
typedef DWORD (WINAPI*GETGUIRESOURCES_T)(HANDLE hProcess, DWORD uiFlags);
#endif

#else

typedef char TCHAR;
typedef int INT;
typedef int HKEY;
typedef void * LPTSTR;
typedef void * PPERF_OBJECT;
typedef void * PPERF_DATA;
typedef unsigned long DWORD;
typedef void * HMODULE;
typedef void * GETGUIRESOURCES_T;

#endif

#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES     150
#define INDEX_STR_LEN      10
#define PROCESS_NAME_SIZE 100

typedef unsigned long ULONG_T;
typedef bool BOOL_T;
typedef const char * CONST_STRING_T;

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct _TIME_FIELD TIME_FIELD;
struct _TIME_FIELD
{
   INT hours;
   INT mins;
   INT secs;
   INT msecs;
};

typedef struct _process
{
   TCHAR name[PROCESS_NAME_SIZE];
   ULONG_T id;
   double cpu;
   ULONG_T utilization;
   ULONG_T memory;
   ULONG_T virt_memory;
   ULONG_T threads;
}  PROCESS_T;

class cPerformance
{
public:
   cPerformance();
   virtual ~cPerformance();
   void Refresh();
   void Print(BOOL_T only_me = false);
   void PrintMemory(FILE * stream);
   CONST_STRING_T Name(ULONG_T process_id);
   double CPUTime(ULONG_T process_id);
   ULONG_T Utilization(ULONG_T process_id);
   ULONG_T Memory(ULONG_T process_id);
   ULONG_T VirtualMemory(ULONG_T process_id);
   ULONG_T Threads(ULONG_T process_id);
   // get the count used GDI Objects of this process
   static ULONG_T GDIObjects();
   // get the count used User Objects of this process
   static ULONG_T UserObjects();
   BOOL_T IsRunning(CONST_STRING_T process_name, BOOL_T exclude_me = false);
   BOOL_T GetProcessId(CONST_STRING_T process_name, ULONG_T &process_id, BOOL_T exclude_me = false);
private:
   BOOL_T SetPerfIndices();
   DWORD GetPerfIndex(LPTSTR title[], DWORD last_index, LPTSTR name);
   PPERF_DATA RefreshPerfData(HKEY key, LPTSTR object_index, PPERF_DATA data, DWORD * data_size);
   void RefreshData(PPERF_OBJECT object);
   void FormatTimeFields(double time, TIME_FIELD * time_field);
   DWORD MilliSeconds(TIME_FIELD * time_field);
   double GetLastCPUTime(ULONG_T process_id);
   DWORD ThreadCount(DWORD parent_index, PPERF_OBJECT object);
   PROCESS_T * FindProcessById(ULONG_T process_id, BOOL_T background_data = false);
private:
#ifdef _WIN32
#if (WINVER < 0x0500)
   static HMODULE _User32DllModule;
   static GETGUIRESOURCES_T _GetGuiResourcesAddr;
   static DWORD GetGuiResources(HANDLE hprocess, DWORD flags);
#endif
#endif
   HKEY _PerfKey;
   HKEY _MachineKey;
   DWORD _PerfDataSize;
   PPERF_DATA _PerfData;
   TCHAR _ThreadObjIndices[2*INDEX_STR_LEN];
   TCHAR _CostlyObjIndices[3*INDEX_STR_LEN];
   PROCESS_T _ProcessData[MAX_PROCESSES];
   PROCESS_T _BackupProcessData[MAX_PROCESSES];
   ULONG_T _LastRefresh;
   ULONG_T _Elapsed;
};




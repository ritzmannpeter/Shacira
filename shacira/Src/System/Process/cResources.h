//## begin module%3DD3BCC70122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3BCC70122.cm

//## begin module%3DD3BCC70122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3BCC70122.cp

//## Module: cResources%3DD3BCC70122; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cResources.h

#ifndef cResources_h
#define cResources_h 1

//## begin module%3DD3BCC70122.includes preserve=yes
//## end module%3DD3BCC70122.includes

// eb_sema
#include "base/eb_sema.hpp"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cOptions;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cMemoryConsole;
class __DLL_EXPORT__ cStandardConsole;
class __DLL_EXPORT__ cConsole;
class __DLL_EXPORT__ cFileConsole;
class __DLL_EXPORT__ cSocketConsole;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3DD3BCC70122.additionalDeclarations preserve=yes

typedef std::map<STRING_T, cConsole *> CONSOLE_MAP_T;

#define MAX_FLAGS                    32
#define PF_ITF_UNITS                  1
#define PF_REFERENCE_CACHE            2
#define PF_FAST_STARTUP               3
#define PF_DELAYED_ORB_INIT           4
#define PF_CACHE_EXCEPTION            5
#define PF_LOAD_PERSISTENT_DATA       6
#define PF_CHECK_DEVICE_MAPPING       7
#define PF_EMIT_CHANGES               8
#define PF_ENABLE_SHADOW_DATASET      9
#define PF_CLEANUP_ON_STARTUP_ERROR  10
#define PF_REFERENCE_SET_VARIABLES   11
#define PF_NONSTANDARD_CONTEXT       12
#define PF_ALLOW_SET_FROM_DEVICE     13
#define PF_ALARM_INFO_FOR_REAL_ALARM 14
#define PF_KILL_PROGRAM_AT_STOP_PROC 15
//## end module%3DD3BCC70122.additionalDeclarations


//## begin cResources%3DD3BCC70122.preface preserve=yes
//## end cResources%3DD3BCC70122.preface

//## Class: cResources%3DD3BCC70122
//	cRessources adds static functionality to a shacira
//	process.
//	Functionality includes global informations such as the
//	definition of shacira based locations (paths) or Logging
//	functionality.
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD3C9F903B4;cConsole { -> F}
//## Uses: <unnamed>%3DD3CAE20110;cStandardConsole { -> F}
//## Uses: <unnamed>%3DD3CAE6017A;cMemoryConsole { -> F}
//## Uses: <unnamed>%3DD3CAEA0003;cSocketConsole { -> F}
//## Uses: <unnamed>%3DD3D38E02E9;cFileConsole { -> F}
//## Uses: <unnamed>%3DD3D66601C4;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3DD3F274033D;cMutexSem { -> }
//## Uses: <unnamed>%3DD3F2A402F6;cObjectLock { -> F}
//## Uses: <unnamed>%3DD4B59B005E;cSHProcess { -> F}
//## Uses: <unnamed>%400D7B44005D;cOptions { -> F}

class __DLL_EXPORT__ cResources 
{
  //## begin cResources%3DD3BCC70122.initialDeclarations preserve=yes
public:
  //## end cResources%3DD3BCC70122.initialDeclarations

    //## Constructors (generated)
      cResources();

      cResources(const cResources &right);

    //## Constructors (specified)
      //## Operation: cResources%1047561050
      //	When constructing a cRessource object with process
      //	command line arguments, options that defined on the
      //	command line are stored in the static object and can be
      //	queried using the GetOption method.
      cResources (int argc, char **argv);

      //## Operation: cResources%1047561051
      cResources (ULONG_T h_inst, CONST_STRING_T cmd_line);

    //## Destructor (generated)
      virtual ~cResources();


    //## Other Operations (specified)
      //## Operation: EPrintf%1037286964
      //	This method prints a formatted message into the shacira
      //	error log file.
      static void EPrintf (CONST_STRING_T fmt_str, ... );

      //## Operation: IPrintf%1037286965
      //	This method prints a formatted message into the shacira
      //	log file.
      static void IPrintf (CONST_STRING_T fmt_str, ... );

      //## Operation: FPrintf%1116319885
      //	This method prints a formatted message into the shacira
      //	fatal error log file.
      static void FPrintf (CONST_STRING_T fmt_str, ... );

      //## Operation: LogPath%1038473719
      //	Method to query the current log path. This is the path
      //	where log file are written.
      static STRING_T LogPath ();

      //## Operation: ConfigPath%1074625638
      //	Method to query the current configuration path. This is
      //	the path where configuration files must be placed to.
      static STRING_T ConfigPath ();

      //## Operation: ModelPath%1074625639
      //	Method to query the current model path. This is the path
      //	where model files must be placed to.
      static STRING_T ModelPath ();

      //## Operation: DataPath%1074625640
      //	Method to query the current data path. This is the path
      //	where persistent data is written to.
      static STRING_T DataPath ();

      //## Operation: AppDataPath%1108976194
      static STRING_T AppDataPath ();

      static BOOL_T IsArgsFileFound();

      //## Operation: GetOption%1074682883
      //	Method to query string type options.
      static void GetOption (CONST_STRING_T option_name, STRING_T &value);

      //## Operation: GetOption%1074682884
      //	Method to query integral type options.
      static void GetOption (CONST_STRING_T option_name, LONG_T &value);

      //## Operation: GetOption%1074682885
      //	Method to query floating point type options.
      static void GetOption (CONST_STRING_T option_name, DOUBLE_T &value);

      //## Operation: GetOption%1074682886
      //	Method to query bool type options.
      static void GetOption (CONST_STRING_T option_name, BOOL_T &value);

      //## Operation: Exit%1037286967
      //	This metod exits the associated process returning er_
      //	code.
      static INT_T Exit (INT_T exit_code, BOOL_T popup = true);

      //## Operation: ShutDown%1037349735
      //	This method shuts down the associated process.
      static void ShutDown ();

      //## Operation: RegisterProcess%1037349736
      //	This method registers a process of type cSHProcess.
      static void RegisterProcess (cSHProcess *process);

      //## Operation: ProcessTerminated%1108818875
      //	This flag shows if the associated process is terminated
      //	or not.
      static BOOL_T ProcessTerminated ();

      //## Operation: Filter%1037286968
      static long __stdcall Filter (_EXCEPTION_POINTERS *exceptions);

      //## Operation: FlagSet%1108819738
      //	Method too query a certain flag.
      static BOOL_T FlagSet (ULONG_T flag);

      //## Operation: SetFlag%1108819739
      //	This method sets a flag on cRessources. cResources flags
      //	are global flags that can be set and retrieved by every
      //	application code that includes cResources.
      static void SetFlag (ULONG_T flag);

      //## Operation: ResetFlag%1108819740
      //	This method resets a flag on cRessources.
      static void ResetFlag (ULONG_T flag);

      //## Operation: GetVersion%1121669292
      //	Returns the Shacira version string.
      static CONST_STRING_T GetVersion ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: UseDebugLog%4237147402FD
      static BOOL_T get_UseDebugLog ();
      static void set_UseDebugLog (BOOL_T value);

      //## Attribute: LogGenerations%42305CB401A5
      static ULONG_T get_LogGenerations ();
      static void set_LogGenerations (ULONG_T value);

      //## Attribute: LogFileSize%42305CD30128
      static ULONG_T get_LogFileSize ();
      static void set_LogFileSize (ULONG_T value);

      //## Attribute: LogFileName%4013D8330251
      static STRING_T get_LogFileName ();
      static void set_LogFileName (STRING_T value);

      //## Attribute: DefaultConsole%4060280E004E
      static cConsole * get_DefaultConsole ();
      static void set_DefaultConsole (cConsole * value);

      //## Attribute: DefaultLanguage%4549BF39006D
      static STRING_T get_DefaultLanguage ();
      static void set_DefaultLanguage (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cResources%3DD3BCC70122.public preserve=yes

      // <-MW- 2005-04-19
      // Intended to be called as StoreLocation(__FILE__,__LINE__) to remember
      // the current source file name and current line number for the following
      // EPrintf() or IPrintf()
      static void StoreLocation(const char *file, int line);

      class __DLL_EXPORT__ cPrint {
      public:
         cPrint(const char *file, int line);
         void Error (CONST_STRING_T fmt_str, ... );
         void Info (CONST_STRING_T fmt_str, ... );
         void FatalError (CONST_STRING_T fmt_str, ... );
      private:
         const char *_current_file;
         int _current_line;
      };

      static void vEPrintf (CONST_STRING_T fmt_str, va_list args);
      static void vIPrintf (CONST_STRING_T fmt_str, va_list args);
      static void vFPrintf (CONST_STRING_T fmt_str, va_list args);

      // -MW->

      //## end cResources%3DD3BCC70122.public
  protected:
    // Data Members for Class Attributes

      //## begin cResources::UseDebugLog%4237147402FD.attr preserve=no  public: static BOOL_T {U} true
      static BOOL_T _UseDebugLog;
      //## end cResources::UseDebugLog%4237147402FD.attr

      //## begin cResources::LogGenerations%42305CB401A5.attr preserve=no  public: static ULONG_T {U} 2
      static ULONG_T _LogGenerations;
      //## end cResources::LogGenerations%42305CB401A5.attr

      //## begin cResources::LogFileSize%42305CD30128.attr preserve=no  public: static ULONG_T {U} 0x40000
      static ULONG_T _LogFileSize;
      //## end cResources::LogFileSize%42305CD30128.attr

      //## begin cResources::LogFileName%4013D8330251.attr preserve=no  public: static STRING_T {U} "Shacira.log"
      static STRING_T _LogFileName;
      //## end cResources::LogFileName%4013D8330251.attr

      //## begin cResources::DefaultConsole%4060280E004E.attr preserve=no  public: static cConsole * {U} 
      static cConsole *_DefaultConsole;
      //## end cResources::DefaultConsole%4060280E004E.attr

      //## begin cResources::DefaultLanguage%4549BF39006D.attr preserve=no  public: static STRING_T {U} "de"
      static STRING_T _DefaultLanguage;
      //## end cResources::DefaultLanguage%4549BF39006D.attr

      //## begin cResources::Process%3DD4B5820030.attr preserve=no  implementation: static cSHProcess * {U} NULL
      static cSHProcess *_Process;
      //## end cResources::Process%3DD4B5820030.attr

      //## begin cResources::Options%400E5C2D0213.attr preserve=no  implementation: static cOptions * {U} NULL
      static cOptions *_Options;
      //## end cResources::Options%400E5C2D0213.attr

      //## begin cResources::Log%4013D856002E.attr preserve=no  implementation: static BOOL_T {U} true
      static BOOL_T _Log;
      //## end cResources::Log%4013D856002E.attr

    // Additional Protected Declarations
      //## begin cResources%3DD3BCC70122.protected preserve=yes
      //## end cResources%3DD3BCC70122.protected

  private:
    // Additional Private Declarations
      //## begin cResources%3DD3BCC70122.private preserve=yes

      // <-MW- 2005-04-19
      // Temporary stored filename and line number from StoreLocation()
      // to EPrintf() or IPrintf()
      static const char *_current_file;
      static int _current_line;
      // -MW->

      //## end cResources%3DD3BCC70122.private
  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetVersion%1121668880
      //	Sets the Shacira version string.
      static void SetVersion ();

      //## Operation: Initialize%1037286970
      static void Initialize (CONST_STRING_T log_file = NULL);

      //## Operation: PrintException%1037286969
      static void PrintException (_EXCEPTION_POINTERS *exceptions);

      //## Operation: SetFullPath%1038473721
      static void SetFullPath (STRING_T &path);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Process%3DD4B5820030
      static cSHProcess * get_Process ();

      //## Attribute: Options%400E5C2D0213
      static cOptions * get_Options ();

      //## Attribute: Log%4013D856002E
      static BOOL_T get_Log ();
      static void set_Log (BOOL_T value);

    // Data Members for Class Attributes

      //## Attribute: LogPath%3DD3C67601D1
      //## begin cResources::LogPath%3DD3C67601D1.attr preserve=no  implementation: static STRING_T {U} "Log"
      static STRING_T _LogPath;
      //## end cResources::LogPath%3DD3C67601D1.attr

      //## Attribute: ConfigPath%3DE5D8A8009A
      //## begin cResources::ConfigPath%3DE5D8A8009A.attr preserve=no  implementation: static STRING_T {U} "Cfg"
      static STRING_T _ConfigPath;
      //## end cResources::ConfigPath%3DE5D8A8009A.attr

      //## Attribute: DataPath%400D72190177
      //## begin cResources::DataPath%400D72190177.attr preserve=no  implementation: static STRING_T {U} "Data"
      static STRING_T _DataPath;
      //## end cResources::DataPath%400D72190177.attr

      //## Attribute: AppDataPath%4219A20801D4
      //## begin cResources::AppDataPath%4219A20801D4.attr preserve=no  implementation: static STRING_T {U} "Internal"
      static STRING_T _AppDataPath;
      //## end cResources::AppDataPath%4219A20801D4.attr

      //## Attribute: ModelPath%400D7234032C
      //## begin cResources::ModelPath%400D7234032C.attr preserve=no  implementation: static STRING_T {U} "Model"
      static STRING_T _ModelPath;
      //## end cResources::ModelPath%400D7234032C.attr

      //## Attribute: RefCount%3E70820B02FD
      //## begin cResources::RefCount%3E70820B02FD.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _RefCount;
      //## end cResources::RefCount%3E70820B02FD.attr

      //## Attribute: Argc%3E70824D034B
      //## begin cResources::Argc%3E70824D034B.attr preserve=no  implementation: static int {U} 0
      static int _Argc;
      //## end cResources::Argc%3E70824D034B.attr

      //## Attribute: Argv%3E7082630280
      //## begin cResources::Argv%3E7082630280.attr preserve=no  implementation: static char ** {U} NULL
      static char **_Argv;
      //## end cResources::Argv%3E7082630280.attr

      //## Attribute: InstanceHandle%3E7082880203
      //## begin cResources::InstanceHandle%3E7082880203.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _InstanceHandle;
      //## end cResources::InstanceHandle%3E7082880203.attr

      //## Attribute: DefaultLogFile%4060278B0251
      //## begin cResources::DefaultLogFile%4060278B0251.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _DefaultLogFile;
      //## end cResources::DefaultLogFile%4060278B0251.attr

      //## Attribute: ErrorLogFile%422DD40102CE
      //## begin cResources::ErrorLogFile%422DD40102CE.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _ErrorLogFile;
      //## end cResources::ErrorLogFile%422DD40102CE.attr

      //## Attribute: FatalLogFile%4289B2B4000F
      //## begin cResources::FatalLogFile%4289B2B4000F.attr preserve=no  implementation: static STRING_T {U} 
      static STRING_T _FatalLogFile;
      //## end cResources::FatalLogFile%4289B2B4000F.attr

      //## Attribute: Flags%42173E3300DA
      //## begin cResources::Flags%42173E3300DA.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _Flags;
      //## end cResources::Flags%42173E3300DA.attr

    // Additional Implementation Declarations
      //## begin cResources%3DD3BCC70122.implementation preserve=yes
      //## end cResources%3DD3BCC70122.implementation

};

//## begin cResources%3DD3BCC70122.postscript preserve=yes
//## end cResources%3DD3BCC70122.postscript

// Class cResources 

//## begin module%3DD3BCC70122.epilog preserve=yes
//## end module%3DD3BCC70122.epilog


#endif

//## begin module%4005259C0000.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4005259C0000.cm

//## begin module%4005259C0000.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4005259C0000.cp

//## Module: cCCSInterface%4005259C0000; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\Interface\cCCSInterface.h

#ifndef cCCSInterface_h
#define cCCSInterface_h 1

//## begin module%4005259C0000.includes preserve=yes
//## end module%4005259C0000.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
#include "System/Database/cContext.h"

class __DLL_EXPORT__ cResources;
class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cOptions;
class __DLL_EXPORT__ cMemoryConsole;
class __DLL_EXPORT__ cStandardConsole;
class __DLL_EXPORT__ cFileConsole;
class __DLL_EXPORT__ cSocketConsole;
class __DLL_EXPORT__ cConfiguration;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cSockets;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cLocalChannel;
class __DLL_EXPORT__ cChannel;
class __DLL_EXPORT__ cCellProcess;
class __DLL_EXPORT__ cBroker;
class __DLL_EXPORT__ cEventAdapter;
class __DLL_EXPORT__ cDataChangeAdapter;
class __DLL_EXPORT__ cNodeList;
class __DLL_EXPORT__ cNode;

//## begin module%4005259C0000.additionalDeclarations preserve=yes
//## end module%4005259C0000.additionalDeclarations


//## begin cCCSInterface%4005259C0000.preface preserve=yes
//## end cCCSInterface%4005259C0000.preface

//## Class: cCCSInterface%4005259C0000
//## Category: GUIFramework::Interface%4005268A008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4005279E0157;cNode { -> F}
//## Uses: <unnamed>%40052F0B00BB;cResources { -> F}
//## Uses: <unnamed>%40052F1C02FD;cOptions { -> F}
//## Uses: <unnamed>%40052F3002DE;cConfigurationObject { -> }
//## Uses: <unnamed>%40052F4A002E;cCellProcess { -> F}
//## Uses: <unnamed>%40052FA40280;cSockets { -> F}
//## Uses: <unnamed>%40052FBA0196;cBroker { -> F}
//## Uses: <unnamed>%40053100000F;cMemoryConsole { -> F}
//## Uses: <unnamed>%4005310C0203;cSocketConsole { -> F}
//## Uses: <unnamed>%4005311A0157;cFileConsole { -> F}
//## Uses: <unnamed>%400531CE00AB;cStandardConsole { -> F}
//## Uses: <unnamed>%400532AC02EE;cConfiguration { -> F}
//## Uses: <unnamed>%400533B20000;cContext { -> F}
//## Uses: <unnamed>%400533D602FD;cChannel { -> F}
//## Uses: <unnamed>%4010249C033C;cFileSystemUtils { -> F}
//## Uses: <unnamed>%40C6D28C03C8;cLocalChannel { -> F}

class __DLL_EXPORT__ cCCSInterface 
{
  //## begin cCCSInterface%4005259C0000.initialDeclarations preserve=yes
public:
  //## end cCCSInterface%4005259C0000.initialDeclarations

    //## Constructors (generated)
      cCCSInterface();

      cCCSInterface(const cCCSInterface &right);

    //## Constructors (specified)
      //## Operation: cCCSInterface%1074080278
      cCCSInterface (int argc, char **argv);

    //## Destructor (generated)
      virtual ~cCCSInterface();


    //## Other Operations (specified)
      //## Operation: Load%1074080279
      BOOL_T Load ();

      //## Operation: Start%1091612889
      BOOL_T Start ();

      //## Operation: Stop%1120214653
      BOOL_T Stop ();

      //## Operation: NodeList%1074080280
      cNodeList * NodeList ();

      //## Operation: Lock%1088517107
      void Lock ();

      //## Operation: Unlock%1088517108
      void Unlock ();

      //## Operation: PrepareProcess%1097343822
      BOOL_T PrepareProcess ();

      //## Operation: LoadRemote%1097333007
      BOOL_T LoadRemote (cContext *context);

      //## Operation: Process%1097343821
      cSHProcess * Process ();

  public:
    // Additional Public Declarations
      //## begin cCCSInterface%4005259C0000.public preserve=yes
      static void SetUiUpdateFunction(UI_UPDATE_FUNCTION_T function);
      //## end cCCSInterface%4005259C0000.public

  protected:
    // Data Members for Associations

      //## Association: GUIFramework::Interface::<unnamed>%40053857005D
      //## Role: cCCSInterface::NodeList%40053857033C
      //## begin cCCSInterface::NodeList%40053857033C.role preserve=no  public: cNodeList { -> 1RFHN}
      cNodeList *_NodeList;
      //## end cCCSInterface::NodeList%40053857033C.role

      //## Association: GUIFramework::Interface::<unnamed>%42E618680186
      //## Role: cCCSInterface::EventAdapters%42E61869005D
      //## Qualifier: name%42E618B800AB; STRING_T
      //## begin cCCSInterface::EventAdapters%42E61869005D.role preserve=no  public: cEventAdapter { -> 0..nRFHN}
      std::map<STRING_T, cEventAdapter*> _EventAdapters;
      //## end cCCSInterface::EventAdapters%42E61869005D.role

      //## Association: GUIFramework::Interface::<unnamed>%42E6186C0000
      //## Role: cCCSInterface::DataChangeAdapters%42E6186C0251
      //## Qualifier: name%42E618D30271; STRING_T
      //## begin cCCSInterface::DataChangeAdapters%42E6186C0251.role preserve=no  public: cDataChangeAdapter { -> 0..nRFHN}
      std::map<STRING_T, cDataChangeAdapter*> _DataChangeAdapters;
      //## end cCCSInterface::DataChangeAdapters%42E6186C0251.role

      //## Association: GUIFramework::Interface::<unnamed>%4110B0AB007D
      //## Role: cCCSInterface::Process%4110B0AB0399
      //## begin cCCSInterface::Process%4110B0AB0399.role preserve=no  public: cSHProcess { -> 1RFHN}
      cSHProcess *_Process;
      //## end cCCSInterface::Process%4110B0AB0399.role

    // Additional Protected Declarations
      //## begin cCCSInterface%4005259C0000.protected preserve=yes
      //## end cCCSInterface%4005259C0000.protected

  private:
    // Additional Private Declarations
      //## begin cCCSInterface%4005259C0000.private preserve=yes
      //## end cCCSInterface%4005259C0000.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Context%1074080285
      cContext * Context (cSHProcess *process, CONST_STRING_T name, ULONG_T timeout = 10000);

    // Data Members for Class Attributes

      //## Attribute: Argc%4005301B031C
      //## begin cCCSInterface::Argc%4005301B031C.attr preserve=no  implementation: int {U} 0
      int _Argc;
      //## end cCCSInterface::Argc%4005301B031C.attr

      //## Attribute: Argv%4005303D031C
      //## begin cCCSInterface::Argv%4005303D031C.attr preserve=no  implementation: char ** {U} NULL
      char **_Argv;
      //## end cCCSInterface::Argv%4005303D031C.attr

      //## Attribute: ConfigFile%401023E00290
      //## begin cCCSInterface::ConfigFile%401023E00290.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ConfigFile;
      //## end cCCSInterface::ConfigFile%401023E00290.attr

      //## Attribute: RootName%4005324702DE
      //## begin cCCSInterface::RootName%4005324702DE.attr preserve=no  implementation: STRING_T {U} "CCSApplication"
      STRING_T _RootName;
      //## end cCCSInterface::RootName%4005324702DE.attr

      //## Attribute: Loaded%40053E590128
      //## begin cCCSInterface::Loaded%40053E590128.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Loaded;
      //## end cCCSInterface::Loaded%40053E590128.attr

      //## Attribute: ProcessObject%41682A6E009C
      //## begin cCCSInterface::ProcessObject%41682A6E009C.attr preserve=no  implementation: cConfigurationObject * {U} NULL
      cConfigurationObject *_ProcessObject;
      //## end cCCSInterface::ProcessObject%41682A6E009C.attr

      //## Attribute: RootContext%42E8EB63036B
      //## begin cCCSInterface::RootContext%42E8EB63036B.attr preserve=no  implementation: cContext * {U} NULL
      cContext *_RootContext;
      //## end cCCSInterface::RootContext%42E8EB63036B.attr

    // Additional Implementation Declarations
      //## begin cCCSInterface%4005259C0000.implementation preserve=yes
      //## end cCCSInterface%4005259C0000.implementation

};

//## begin cCCSInterface%4005259C0000.postscript preserve=yes
//## end cCCSInterface%4005259C0000.postscript

// Class cCCSInterface 

//## begin module%4005259C0000.epilog preserve=yes
//## end module%4005259C0000.epilog


#endif

//## begin module%3DD8B83600E4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD8B83600E4.cm

//## begin module%3DD8B83600E4.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3DD8B83600E4.cp

//## Module: cEventChannelWrapper%3DD8B83600E4; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cEventChannelWrapper.h

#ifndef cEventChannelWrapper_h
#define cEventChannelWrapper_h 1

//## begin module%3DD8B83600E4.includes preserve=yes
//## end module%3DD8B83600E4.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cSystemUtils;
class __DLL_EXPORT__ cSysProcess;
class __DLL_EXPORT__ cCosEventChannelProxy;
class __DLL_EXPORT__ cEventChannelManager;

//## begin module%3DD8B83600E4.additionalDeclarations preserve=yes
//## end module%3DD8B83600E4.additionalDeclarations


//## begin cEventChannelWrapper%3DD8B83600E4.preface preserve=yes
//## end cEventChannelWrapper%3DD8B83600E4.preface

//## Class: cEventChannelWrapper%3DD8B83600E4
//## Category: Apps::ChannelMgr%3DD8C17600FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD8B83600E6;cConfigurationObject { -> F}
//## Uses: <unnamed>%3DD8B83600E7; { -> F}
//## Uses: <unnamed>%3DD8B840021F;cSysProcess { -> F}
//## Uses: <unnamed>%3E70BE0C029F;cCosEventChannelProxy { -> F}
//## Uses: <unnamed>%3E70BF96006D;cSystemUtils { -> F}

class __DLL_EXPORT__ cEventChannelWrapper : public cControlThread  //## Inherits: <unnamed>%3DD938C501EC
{
  //## begin cEventChannelWrapper%3DD8B83600E4.initialDeclarations preserve=yes
public:
  //## end cEventChannelWrapper%3DD8B83600E4.initialDeclarations

    //## Constructors (generated)
      cEventChannelWrapper();

      cEventChannelWrapper(const cEventChannelWrapper &right);

    //## Constructors (specified)
      //## Operation: cEventChannelWrapper%1037610185
      cEventChannelWrapper (cEventChannelManager *process, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cEventChannelWrapper();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ChannelType%3DD8B83600F0
      INT_T get_ChannelType () const;
      void set_ChannelType (INT_T value);

      //## Attribute: Active%3DD8B83600F1
      BOOL_T get_Active () const;
      void set_Active (BOOL_T value);

      //## Attribute: ProcessId%3DD8B83600F2
      ULONG_T get_ProcessId () const;
      void set_ProcessId (ULONG_T value);

      //## Attribute: Computer%3DD8B83600F3
      STRING_T get_Computer () const;
      void set_Computer (STRING_T value);

      //## Attribute: ChannelName%3DD8B83600F4
      STRING_T get_ChannelName () const;
      void set_ChannelName (STRING_T value);

      //## Attribute: ProcessName%3DD8B83600F5
      STRING_T get_ProcessName () const;
      void set_ProcessName (STRING_T value);

      //## Attribute: ProcessArgs%3DD8B83600F6
      STRING_T get_ProcessArgs () const;
      void set_ProcessArgs (STRING_T value);

      //## Attribute: IOR%3DD8B83600F7
      STRING_T get_IOR () const;
      void set_IOR (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cEventChannelWrapper%3DD8B83600E4.public preserve=yes
      //## end cEventChannelWrapper%3DD8B83600E4.public

  protected:

    //## Other Operations (specified)
      //## Operation: AddServices%1037610198
      virtual void AddServices () = 0;

      //## Operation: StartProcess%1037610196
      void StartProcess ();

      //## Operation: StopProcess%1037610197
      void StopProcess ();

    // Data Members for Class Attributes

      //## begin cEventChannelWrapper::ChannelType%3DD8B83600F0.attr preserve=no  public: INT_T {U} 
      INT_T _ChannelType;
      //## end cEventChannelWrapper::ChannelType%3DD8B83600F0.attr

      //## begin cEventChannelWrapper::Active%3DD8B83600F1.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Active;
      //## end cEventChannelWrapper::Active%3DD8B83600F1.attr

      //## begin cEventChannelWrapper::ProcessId%3DD8B83600F2.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ProcessId;
      //## end cEventChannelWrapper::ProcessId%3DD8B83600F2.attr

      //## begin cEventChannelWrapper::Computer%3DD8B83600F3.attr preserve=no  public: STRING_T {U} 
      STRING_T _Computer;
      //## end cEventChannelWrapper::Computer%3DD8B83600F3.attr

      //## begin cEventChannelWrapper::ChannelName%3DD8B83600F4.attr preserve=no  public: STRING_T {U} 
      STRING_T _ChannelName;
      //## end cEventChannelWrapper::ChannelName%3DD8B83600F4.attr

      //## begin cEventChannelWrapper::ProcessName%3DD8B83600F5.attr preserve=no  public: STRING_T {U} 
      STRING_T _ProcessName;
      //## end cEventChannelWrapper::ProcessName%3DD8B83600F5.attr

      //## begin cEventChannelWrapper::ProcessArgs%3DD8B83600F6.attr preserve=no  public: STRING_T {U} 
      STRING_T _ProcessArgs;
      //## end cEventChannelWrapper::ProcessArgs%3DD8B83600F6.attr

      //## begin cEventChannelWrapper::IOR%3DD8B83600F7.attr preserve=no  public: STRING_T {U} 
      STRING_T _IOR;
      //## end cEventChannelWrapper::IOR%3DD8B83600F7.attr

    // Data Members for Associations

      //## Association: Apps::ChannelMgr::<unnamed>%3DD8C21E0235
      //## Role: cEventChannelWrapper::Process%3DD8C21F01DC
      //## begin cEventChannelWrapper::Process%3DD8C21F01DC.role preserve=no  public: cEventChannelManager {0..n -> 1RFHN}
      cEventChannelManager *_Process;
      //## end cEventChannelWrapper::Process%3DD8C21F01DC.role

      //## Association: Apps::ChannelMgr::<unnamed>%3DD922C40110
      //## Role: cEventChannelWrapper::ChannelProcess%3DD922C4037D
      //## begin cEventChannelWrapper::ChannelProcess%3DD922C4037D.role preserve=no  public: cSysProcess { -> 0..1RFHN}
      cSysProcess *_ChannelProcess;
      //## end cEventChannelWrapper::ChannelProcess%3DD922C4037D.role

    // Additional Protected Declarations
      //## begin cEventChannelWrapper%3DD8B83600E4.protected preserve=yes
      //## end cEventChannelWrapper%3DD8B83600E4.protected

  private:
    // Additional Private Declarations
      //## begin cEventChannelWrapper%3DD8B83600E4.private preserve=yes
      //## end cEventChannelWrapper%3DD8B83600E4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cEventChannelWrapper%3DD8B83600E4.implementation preserve=yes
      //## end cEventChannelWrapper%3DD8B83600E4.implementation

};

//## begin cEventChannelWrapper%3DD8B83600E4.postscript preserve=yes
//## end cEventChannelWrapper%3DD8B83600E4.postscript

// Class cEventChannelWrapper 

//## begin module%3DD8B83600E4.epilog preserve=yes
//## end module%3DD8B83600E4.epilog


#endif

//## begin module%43141F4F033D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43141F4F033D.cm

//## begin module%43141F4F033D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43141F4F033D.cp

//## Module: cOPCRequestHandler%43141F4F033D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOPCRequestHandler.h

#ifndef cOPCRequestHandler_h
#define cOPCRequestHandler_h 1

//## begin module%43141F4F033D.includes preserve=yes
//## end module%43141F4F033D.includes

// cRequestHandler
#include "System/Process/cRequestHandler.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cOPCClientProcess;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cRemoteContext;

//## begin module%43141F4F033D.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cContext*> CONTEXT_MAP_T;
typedef std::map<STRING_T,STRING_T> SERVER_MAP_T;

#define READ_VAR_FAILED    -100
#define WRITE_VAR_FAILED   -101
#define NO_ACCESS          -102
#define NO_VAR_REF         -103
#define NO_CONTEXT         -104
#define RANGE_ERROR        -105

#define MINIMUM_ERROR      -200
#define MAXIMUM_ERROR      -201

#define NO_CONNECTION      -300
#define UNKNOWN_ERROR      -301

#define OPC_E_READ_FAILED  ((HRESULT)0xE0040001L)
#define OPC_E_WRITE_FAILED ((HRESULT)0xE0040002L)

//## end module%43141F4F033D.additionalDeclarations


//## begin cOPCRequestHandler%43141F4F033D.preface preserve=yes
//## end cOPCRequestHandler%43141F4F033D.preface

//## Class: cOPCRequestHandler%43141F4F033D
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43142EF4014B;cContext { -> F}
//## Uses: <unnamed>%43142F310293;cSHProcess { -> F}
//## Uses: <unnamed>%43142F7401E8;cVarDef { -> F}
//## Uses: <unnamed>%431431BC0196;cVarRef { -> F}
//## Uses: <unnamed>%431845110020;cOPCClientProcess { -> F}
//## Uses: <unnamed>%43A0839402F9;cSHFile { -> F}
//## Uses: <unnamed>%43A126C6011D;cFileSystemUtils { -> F}
//## Uses: <unnamed>%43D89B72008B;cProxy { -> F}
//## Uses: <unnamed>%440FE8C40204;cRemoteContext { -> F}

class __DLL_EXPORT__ cOPCRequestHandler : public cRequestHandler  //## Inherits: <unnamed>%43141F690233
{
  //## begin cOPCRequestHandler%43141F4F033D.initialDeclarations preserve=yes
public:
  //## end cOPCRequestHandler%43141F4F033D.initialDeclarations

    //## Constructors (generated)
      cOPCRequestHandler();

      cOPCRequestHandler(const cOPCRequestHandler &right);

    //## Constructors (specified)
      //## Operation: cOPCRequestHandler%1125391951
      cOPCRequestHandler (cSHProcess *process, CONST_STRING_T handler_name);

    //## Destructor (generated)
      virtual ~cOPCRequestHandler();


    //## Other Operations (specified)
      //## Operation: SetConnectionInfoFile%1134632034
      void SetConnectionInfoFile (CONST_STRING_T file);

      //## Operation: RefreshItems%1125391952
      virtual BOOL_T RefreshItems ();

      //## Operation: SetItemDefinition%1125393495
      virtual void SetItemDefinition (cVarRef *var_ref, CONST_STRING_T context_name, cRemoteContext *context, CONST_STRING_T var_name, WORD quality, DWORD access_rights, VARTYPE opc_datatype);

      //## Operation: AddContext%1125393499
      BOOL_T AddContext (CONST_STRING_T context_name, cContext *context);

      //## Operation: AddServer%1141820977
      void AddServer (CONST_STRING_T server_name);

      //## Operation: RemoveServer%1141820978
      void RemoveServer (CONST_STRING_T server_name);

      //## Operation: Context%1125393500
      cContext * Context (CONST_STRING_T context_name);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: LocalServer%440ECD640128
      BOOL_T get_LocalServer () const;
      void set_LocalServer (BOOL_T value);

      //## Attribute: OnlyDedicated%440ECE0B035B
      BOOL_T get_OnlyDedicated () const;
      void set_OnlyDedicated (BOOL_T value);

      //## Attribute: ServerMap%440ECD8B03E7
      SERVER_MAP_T get_ServerMap () const;
      void set_ServerMap (SERVER_MAP_T value);

  public:
    // Additional Public Declarations
      //## begin cOPCRequestHandler%43141F4F033D.public preserve=yes
      //## end cOPCRequestHandler%43141F4F033D.public

  protected:
    // Data Members for Class Attributes

      //## begin cOPCRequestHandler::LocalServer%440ECD640128.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _LocalServer;
      //## end cOPCRequestHandler::LocalServer%440ECD640128.attr

      //## begin cOPCRequestHandler::OnlyDedicated%440ECE0B035B.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _OnlyDedicated;
      //## end cOPCRequestHandler::OnlyDedicated%440ECE0B035B.attr

      //## begin cOPCRequestHandler::ServerMap%440ECD8B03E7.attr preserve=no  public: SERVER_MAP_T {U} 
      SERVER_MAP_T _ServerMap;
      //## end cOPCRequestHandler::ServerMap%440ECD8B03E7.attr

      //## Attribute: ConnectionInfoFile%43A121E00333
      //## begin cOPCRequestHandler::ConnectionInfoFile%43A121E00333.attr preserve=no  protected: STRING_T {U} 
      STRING_T _ConnectionInfoFile;
      //## end cOPCRequestHandler::ConnectionInfoFile%43A121E00333.attr

      //## Attribute: ContextMap%43142DD80034
      //## begin cOPCRequestHandler::ContextMap%43142DD80034.attr preserve=no  protected: CONTEXT_MAP_T {U} 
      CONTEXT_MAP_T _ContextMap;
      //## end cOPCRequestHandler::ContextMap%43142DD80034.attr

    // Additional Protected Declarations
      //## begin cOPCRequestHandler%43141F4F033D.protected preserve=yes
      //## end cOPCRequestHandler%43141F4F033D.protected

  private:
    // Additional Private Declarations
      //## begin cOPCRequestHandler%43141F4F033D.private preserve=yes
      //## end cOPCRequestHandler%43141F4F033D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: VarSpec%1125393504
      BOOL_T VarSpec (cVarDef *var_def, WORD &quality, DWORD &access_rights, VARTYPE &opc_datatype);

      //## Operation: UpdateContextInfo%1134592366
      void UpdateContextInfo ();

      //## Operation: IsSupported%1141821098
      BOOL_T IsSupported (CONST_STRING_T server_name, cContext *context);

    // Additional Implementation Declarations
      //## begin cOPCRequestHandler%43141F4F033D.implementation preserve=yes
      //## end cOPCRequestHandler%43141F4F033D.implementation

};

//## begin cOPCRequestHandler%43141F4F033D.postscript preserve=yes
//## end cOPCRequestHandler%43141F4F033D.postscript

// Class cOPCRequestHandler 

//## begin module%43141F4F033D.epilog preserve=yes
//## end module%43141F4F033D.epilog


#endif

//## begin module%42DD14750128.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DD14750128.cm

//## begin module%42DD14750128.cp preserve=no
//	Copyright © 2002 - 2016 by
//	2i Industrial Informatics GmbH
//## end module%42DD14750128.cp

//## Module: cClients%42DD14750128; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\ClientData\cClients.h

#ifndef cClients_h
#define cClients_h 1

//## begin module%42DD14750128.includes preserve=yes
//## end module%42DD14750128.includes

// eb_sema
#include "base/eb_sema.hpp"
// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cClientData;

//## begin module%42DD14750128.additionalDeclarations preserve=yes

#define USER_CLIENTS_ID_START       100
#define USER_CLIENTS_CAPACITY       400
#define USER_CLIENTS_ID_MAX         USER_CLIENTS_CAPACITY
#define IS_INTERFACE_ID(id)         (id > 0 && id < USER_CLIENTS_ID_START)
typedef cClientData * CLIENT_VECTOR_T[USER_CLIENTS_ID_MAX];

class cTimeoutControl : public cControlThread
{
public:
   cTimeoutControl()
   {
      _Name = "Client Timeout Control";
      _Started = false;
   };
   virtual ~cTimeoutControl()
   {
   };
   virtual INT_T MainFunc(void * extra);
   void Launch();
private:
   INT_T CheckClients();
private:
   BOOL_T _Started;
};

//## end module%42DD14750128.additionalDeclarations


//## begin cClients%42DD14750128.preface preserve=yes
//## end cClients%42DD14750128.preface

//## Class: cClients%42DD14750128
//## Category: Client::ClientData%42DD144803B9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42DD14A0032C;cMutexSem { -> }
//## Uses: <unnamed>%42DD14B80290;cClientData { -> F}
//## Uses: <unnamed>%42DE04490242;cTransientObject { -> F}
//## Uses: <unnamed>%42DEA5D403A9;cControlThread { -> }

class __DLL_EXPORT__ cClients 
{
  //## begin cClients%42DD14750128.initialDeclarations preserve=yes
public:
friend class cTimeoutControl;
  //## end cClients%42DD14750128.initialDeclarations

    //## Constructors (generated)
      cClients();

      cClients(const cClients &right);

    //## Destructor (generated)
      virtual ~cClients();


    //## Other Operations (specified)
      //## Operation: GetClientData%1121785240
      static cClientData * GetClientData (ULONG_T id);

      //## Operation: AllocClient%1141202704
      static cClientData * AllocClient (ULONG_T client_id);

      //## Operation: AllocClient%1121785244
      static cClientData * AllocClient (CONST_STRING_T user_name, CONST_STRING_T password);

      //## Operation: RemoveClient%1121785241
      static BOOL_T RemoveClient (ULONG_T id);

      //## Operation: AddObject%1121845388
      static void AddObject (cTransientObject *object);

      //## Operation: Exit%1121933608
      static void Exit ();

      //## Operation: GetConnected%1121933609
      static BOOL_T GetConnected ();

      //## Operation: SetConnected%1121933610
      static void SetConnected (BOOL_T value);

      //## Operation: GetCurrentClients%1121933611
      static ULONG_T GetCurrentClients ();

    // Data Members for Class Attributes

      //## Attribute: ClientAccessMutex%42DD15C50148
      //## begin cClients::ClientAccessMutex%42DD15C50148.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _ClientAccessMutex;
      //## end cClients::ClientAccessMutex%42DD15C50148.attr

  public:
    // Additional Public Declarations
      //## begin cClients%42DD14750128.public preserve=yes
      //## end cClients%42DD14750128.public

  protected:
    // Additional Protected Declarations
      //## begin cClients%42DD14750128.protected preserve=yes
      //## end cClients%42DD14750128.protected

  private:
    // Additional Private Declarations
      //## begin cClients%42DD14750128.private preserve=yes
      //## end cClients%42DD14750128.private

  private: //## implementation
    // Data Members for Class Attributes

     //## Attribute: CurrentClients%42DF63D303A9
      //## begin cClients::CurrentClients%42DF63D303A9.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _CurrentClients;
      //## end cClients::CurrentClients%42DF63D303A9.attr

      //## Attribute: Connected%42DF6295032C
      //## begin cClients::Connected%42DF6295032C.attr preserve=no  implementation: static BOOL_T {U} false
      static BOOL_T _Connected;
      //## end cClients::Connected%42DF6295032C.attr

      //## Attribute: ClientData%42DD14D60157
      //## begin cClients::ClientData%42DD14D60157.attr preserve=no  implementation: static CLIENT_VECTOR_T {U} 
      static CLIENT_VECTOR_T _ClientData;
      //## end cClients::ClientData%42DD14D60157.attr

      //## Attribute: TimeoutControl%42DEA5DF004E
      //## begin cClients::TimeoutControl%42DEA5DF004E.attr preserve=no  implementation: static cTimeoutControl {U} 
      static cTimeoutControl _TimeoutControl;
      //## end cClients::TimeoutControl%42DEA5DF004E.attr

    // Additional Implementation Declarations
      //## begin cClients%42DD14750128.implementation preserve=yes
      //## end cClients%42DD14750128.implementation

};

//## begin cClients%42DD14750128.postscript preserve=yes
//## end cClients%42DD14750128.postscript

// Class cClients 

//## begin module%42DD14750128.epilog preserve=yes
//## end module%42DD14750128.epilog


#endif

//## begin module%4039D85100CB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039D85100CB.cm

//## begin module%4039D85100CB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039D85100CB.cp

//## Module: cPersistenceManager%4039D85100CB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistenceManager.h

#ifndef cPersistenceManager_h
#define cPersistenceManager_h 1

//## begin module%4039D85100CB.includes preserve=yes
//## end module%4039D85100CB.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cConnector
#include "System/Channel/cConnector.h"

class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cLocalVariable;
class __DLL_EXPORT__ cStorage;
class __DLL_EXPORT__ cBBRAMStorage;
class __DLL_EXPORT__ cFileStorage;

//## begin module%4039D85100CB.additionalDeclarations preserve=yes

typedef std::map<UCHAR_T, cStorage*> STORAGE_MAP_T;

//## end module%4039D85100CB.additionalDeclarations


//## begin cPersistenceManager%4039D85100CB.preface preserve=yes
//## end cPersistenceManager%4039D85100CB.preface

//## Class: cPersistenceManager%4039D85100CB
//	This connector handles data persistence connecting to
//	data change events.
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4039E9C8003E;cDataChange { -> F}
//## Uses: <unnamed>%4039F6DE006D;cVariable { -> F}
//## Uses: <unnamed>%403A095401D4;cStorage { -> F}
//## Uses: <unnamed>%403A0FBF02BF;cFileStorage { -> F}
//## Uses: <unnamed>%403A0FC7029F;cBBRAMStorage { -> F}
//## Uses: <unnamed>%403B2A7E02CE;cLocalVariable { -> F}
//## Uses: <unnamed>%45BF88F4029F;cFileSystemUtils { -> }

class __DLL_EXPORT__ cPersistenceManager : public cConnector  //## Inherits: <unnamed>%4039D8C7007D
{
  //## begin cPersistenceManager%4039D85100CB.initialDeclarations preserve=yes
public:
  //## end cPersistenceManager%4039D85100CB.initialDeclarations

    //## Constructors (generated)
      cPersistenceManager();

      cPersistenceManager(const cPersistenceManager &right);

    //## Constructors (specified)
      //## Operation: cPersistenceManager%1077539619
      cPersistenceManager (cContext *context);

      //## Operation: cPersistenceManager%1191907813
      cPersistenceManager (cContext *context, UCHAR_T dset_type);

    //## Destructor (generated)
      virtual ~cPersistenceManager();


    //## Other Operations (specified)
      //## Operation: Object%1077533272
      //	Method that is called when an incoming object arrives at
      //	the back end of the associated channel.
      virtual void Object (cTransientObject *object);

      //## Operation: SetUp%1077539620
      void SetUp ();

      //## Operation: Storage%1077542663
      cStorage * Storage (UCHAR_T ptype, UCHAR_T dset_type = 0);

      //## Operation: LoadPersistentData%1170178871
      void LoadPersistentData ();

      //## Operation: Save%1191857028
      void Save ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DataInitialized%40B362CB03C8
      BOOL_T get_DataInitialized () const;

  public:
    // Additional Public Declarations
      //## begin cPersistenceManager%4039D85100CB.public preserve=yes
      void Clear();
      void SetBuffered(BOOL_T state);
      //## end cPersistenceManager%4039D85100CB.public

  protected:
    // Data Members for Class Attributes

      //## begin cPersistenceManager::DataInitialized%40B362CB03C8.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _DataInitialized;
      //## end cPersistenceManager::DataInitialized%40B362CB03C8.attr

    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%4039F2F70138
      //## Role: cPersistenceManager::Context%4039F2F80157
      //## begin cPersistenceManager::Context%4039F2F80157.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cPersistenceManager::Context%4039F2F80157.role

    // Additional Protected Declarations
      //## begin cPersistenceManager%4039D85100CB.protected preserve=yes
      //## end cPersistenceManager%4039D85100CB.protected

  private:
    // Additional Private Declarations
      //## begin cPersistenceManager%4039D85100CB.private preserve=yes
      //## end cPersistenceManager%4039D85100CB.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetUpShadow%1191857029
      void SetUpShadow ();

    // Data Members for Class Attributes

      //## Attribute: Storages%403A09740213
      //## begin cPersistenceManager::Storages%403A09740213.attr preserve=no  implementation: STORAGE_MAP_T {U} 
      STORAGE_MAP_T _Storages;
      //## end cPersistenceManager::Storages%403A09740213.attr

    // Additional Implementation Declarations
      //## begin cPersistenceManager%4039D85100CB.implementation preserve=yes
      //## end cPersistenceManager%4039D85100CB.implementation

};

//## begin cPersistenceManager%4039D85100CB.postscript preserve=yes
//## end cPersistenceManager%4039D85100CB.postscript

// Class cPersistenceManager 

//## begin module%4039D85100CB.epilog preserve=yes
//## end module%4039D85100CB.epilog


#endif

//## begin module%41CAB08A031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41CAB08A031C.cm

//## begin module%41CAB08A031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41CAB08A031C.cp

//## Module: cExtendedObjectRing%41CAB08A031C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cExtendedObjectRing.h

#ifndef cExtendedObjectRing_h
#define cExtendedObjectRing_h 1

//## begin module%41CAB08A031C.includes preserve=yes
//## end module%41CAB08A031C.includes

// eb_ring
#include "base/eb_ring.hpp"
// eb_sema
#include "base/eb_sema.hpp"
// cFlatObject
#include "System/Structs/cFlatObject.h"

class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%41CAB08A031C.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cMutexSem*> RING_MUTEX_MAP_T;

//## end module%41CAB08A031C.additionalDeclarations


//## begin cExtendedObjectRing%41CAB08A031C.preface preserve=yes
//## end cExtendedObjectRing%41CAB08A031C.preface

//## Class: cExtendedObjectRing%41CAB08A031C
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%41CAB28A0138;cTransientObject { -> F}
//## Uses: <unnamed>%41CAB2D401E4;cRingRawSafe { -> F}
//## Uses: <unnamed>%41CAB348037A;cStringUtils { -> F}
//## Uses: <unnamed>%41CAB36D0271;cFileSystemUtils { -> F}
//## Uses: <unnamed>%41CAB3BB002E;cSHFile { -> F}
//## Uses: <unnamed>%41D437530203;cMutexSem { -> }
//## Uses: <unnamed>%41D437DA01A5;cObjectLock { -> F}
//## Uses: <unnamed>%4236EA1D00DA;cRingRaw { -> F}

class __DLL_EXPORT__ cExtendedObjectRing : public cFlatObject  //## Inherits: <unnamed>%41CAB0CC02EE
{
  //## begin cExtendedObjectRing%41CAB08A031C.initialDeclarations preserve=yes
public:
  //## end cExtendedObjectRing%41CAB08A031C.initialDeclarations

    //## Constructors (generated)
      cExtendedObjectRing();

      cExtendedObjectRing(const cExtendedObjectRing &right);

    //## Constructors (specified)
      //## Operation: cExtendedObjectRing%1103802860
      cExtendedObjectRing (cVarRef* var_ref, ULONG_T refresh_interval = 0);

      //## Operation: cExtendedObjectRing%1103802861
      cExtendedObjectRing (BUF_T buffer, ULONG_T bufsize);

    //## Destructor (generated)
      virtual ~cExtendedObjectRing();


    //## Other Operations (specified)
      //## Operation: AddObject%1103802854
      //	Adds an object to the ring.
      virtual void AddObject (cTransientObject *object);

      //## Operation: GetObject%1103802855
      //	Gets the the object at pos index.
      virtual cTransientObject * GetObject (ULONG_T index);

      //## Operation: GetFirstObject%1103802862
      //	Gets the first (youngest) object of the ring..
      virtual cTransientObject * GetFirstObject ();

      //## Operation: GetLastObject%1103802863
      //	Gets the last (oldest) object of the ring..
      virtual cTransientObject * GetLastObject ();

      //## Operation: Save%1103802857
      virtual void Save (cTransientObject *object = NULL);

      //## Operation: Load%1103802858
      virtual void Load ();

      //## Operation: Refresh%1110025035
      virtual void Refresh ();

      //## Operation: Used%1103802864
      ULONG_T Used ();

      //## Operation: Count%1103802865
      ULONG_T Count ();

      //## Operation: Clear%1106841438
      virtual void Clear ();

      //## Operation: RingMutex%1108453910
      cMutexSem * RingMutex ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SaveInterval%41CAB185004E
      ULONG_T get_SaveInterval () const;

      //## Attribute: RefreshInterval%4229B90E01C5
      ULONG_T get_RefreshInterval () const;

  public:
    // Additional Public Declarations
      //## begin cExtendedObjectRing%41CAB08A031C.public preserve=yes
      //## end cExtendedObjectRing%41CAB08A031C.public

  protected:
    // Data Members for Class Attributes

      //## begin cExtendedObjectRing::SaveInterval%41CAB185004E.attr preserve=no  public: ULONG_T {U} 300
      ULONG_T _SaveInterval;
      //## end cExtendedObjectRing::SaveInterval%41CAB185004E.attr

      //## begin cExtendedObjectRing::RefreshInterval%4229B90E01C5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RefreshInterval;
      //## end cExtendedObjectRing::RefreshInterval%4229B90E01C5.attr

    // Data Members for Associations

      //## Association: System::Structs::<unnamed>%41D2E20400EA
      //## Role: cExtendedObjectRing::VarRef%41D2E205002E
      //## begin cExtendedObjectRing::VarRef%41D2E205002E.role preserve=no  public: cVarRef { -> 0..1RFHN}
      cVarRef *_VarRef;
      //## end cExtendedObjectRing::VarRef%41D2E205002E.role

    // Additional Protected Declarations
      //## begin cExtendedObjectRing%41CAB08A031C.protected preserve=yes
      //## end cExtendedObjectRing%41CAB08A031C.protected

  private:
    // Additional Private Declarations
      //## begin cExtendedObjectRing%41CAB08A031C.private preserve=yes
      //## end cExtendedObjectRing%41CAB08A031C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: LoadObject%1104428022
      void LoadObject (cTransientObject *object = NULL);

      //## Operation: SetPersistenceFiles%1103802859
      void SetPersistenceFiles ();

      //## Operation: LoadRemote%1243005934
      void LoadRemote ();

      //## Operation: GetNextObjectFromBuffer%1243005935
      BOOL_T GetNextObjectFromBuffer (CONST_STRING_T object_buffer, STRING_T &serialized_object);

    // Data Members for Class Attributes

      //## Attribute: PersistenceFile%41CAB185005E
      //## begin cExtendedObjectRing::PersistenceFile%41CAB185005E.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _PersistenceFile;
      //## end cExtendedObjectRing::PersistenceFile%41CAB185005E.attr

      //## Attribute: BackupFile%4229B6BD00CB
      //## begin cExtendedObjectRing::BackupFile%4229B6BD00CB.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _BackupFile;
      //## end cExtendedObjectRing::BackupFile%4229B6BD00CB.attr

      //## Attribute: SyncFile%4229B6C10167
      //## begin cExtendedObjectRing::SyncFile%4229B6C10167.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _SyncFile;
      //## end cExtendedObjectRing::SyncFile%4229B6C10167.attr

      //## Attribute: LastSave%41CAB185006D
      //## begin cExtendedObjectRing::LastSave%41CAB185006D.attr preserve=no  implementation: cTimeObject {U} 
      cTimeObject _LastSave;
      //## end cExtendedObjectRing::LastSave%41CAB185006D.attr

      //## Attribute: LastRefresh%4229B946006D
      //## begin cExtendedObjectRing::LastRefresh%4229B946006D.attr preserve=no  implementation: cTimeObject {U} 
      cTimeObject _LastRefresh;
      //## end cExtendedObjectRing::LastRefresh%4229B946006D.attr

      //## Attribute: Ring%41CAB1BF02BF
      //## begin cExtendedObjectRing::Ring%41CAB1BF02BF.attr preserve=no  implementation: cRingRaw * {U} NULL
      cRingRaw *_Ring;
      //## end cExtendedObjectRing::Ring%41CAB1BF02BF.attr

      //## Attribute: SafeRing%4236EA5F034B
      //## begin cExtendedObjectRing::SafeRing%4236EA5F034B.attr preserve=no  implementation: cRingRawSafe * {U} NULL
      cRingRawSafe *_SafeRing;
      //## end cExtendedObjectRing::SafeRing%4236EA5F034B.attr

      //## Attribute: RingMutexes%4211A9DE034B
      //## begin cExtendedObjectRing::RingMutexes%4211A9DE034B.attr preserve=no  implementation: static RING_MUTEX_MAP_T {U} 
      static RING_MUTEX_MAP_T _RingMutexes;
      //## end cExtendedObjectRing::RingMutexes%4211A9DE034B.attr

      //## Attribute: ObjectsPending%4229BDBB01F4
      //## begin cExtendedObjectRing::ObjectsPending%4229BDBB01F4.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _ObjectsPending;
      //## end cExtendedObjectRing::ObjectsPending%4229BDBB01F4.attr

      //## Attribute: CurrentBufPos%4A16C3AE0132
      //## begin cExtendedObjectRing::CurrentBufPos%4A16C3AE0132.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _CurrentBufPos;
      //## end cExtendedObjectRing::CurrentBufPos%4A16C3AE0132.attr

      //## Attribute: RemoteRing%4A16C5920383
      //## begin cExtendedObjectRing::RemoteRing%4A16C5920383.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _RemoteRing;
      //## end cExtendedObjectRing::RemoteRing%4A16C5920383.attr

      //## Attribute: RemoteBuffer%4A16C5CC0319
      //## begin cExtendedObjectRing::RemoteBuffer%4A16C5CC0319.attr preserve=no  implementation: BUF_T {U} NULL
      BUF_T _RemoteBuffer;
      //## end cExtendedObjectRing::RemoteBuffer%4A16C5CC0319.attr

    // Additional Implementation Declarations
      //## begin cExtendedObjectRing%41CAB08A031C.implementation preserve=yes
      //## end cExtendedObjectRing%41CAB08A031C.implementation

};

//## begin cExtendedObjectRing%41CAB08A031C.postscript preserve=yes
//## end cExtendedObjectRing%41CAB08A031C.postscript

// Class cExtendedObjectRing 

//## begin module%41CAB08A031C.epilog preserve=yes
//## end module%41CAB08A031C.epilog


#endif

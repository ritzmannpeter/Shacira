//## begin module%3A6BF14C0281.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A6BF14C0281.cm

//## begin module%3A6BF14C0281.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A6BF14C0281.cp

//## Module: cTransientObject%3A6BF14C0281; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cTransientObject.h

#ifndef cTransientObject_h
#define cTransientObject_h 1

//## begin module%3A6BF14C0281.includes preserve=yes
//## end module%3A6BF14C0281.includes

// eb_sema
#include "base/eb_sema.hpp"
// cCustomFunctions
#include "System/cCustomFunctions.h"
// cTimeObject
#include "System/cTimeObject.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"

class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cRequest;
class __DLL_EXPORT__ cProgress;
class __DLL_EXPORT__ cUserInfo;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cAlarm;
class __DLL_EXPORT__ cJobEntry;
class __DLL_EXPORT__ cJobSpec;
class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cState;
class __DLL_EXPORT__ cStaticObject;
class __DLL_EXPORT__ cEvent;
class __DLL_EXPORT__ cCosEventChannelProxy;
class __DLL_EXPORT__ cCorbaCellProxy;

//## begin module%3A6BF14C0281.additionalDeclarations preserve=yes
class cMemPool;
class cGarbageCollector;

#include "base/base_ex.h"
using namespace ecl;

#include "Pack_1"

#define IDENTIFIER_LENGTH        32
#define TEXT_LENGTH              64

typedef struct {
   ATOMIC_T object_ident;
   ULONG_T type;
   ULONG_T sub_type;
   ULONG_T event_code;
   ULONG_T time_stamp;
   char cell_name[IDENTIFIER_LENGTH+1];
   char source_name[IDENTIFIER_LENGTH+1];
   char key[IDENTIFIER_LENGTH+1];
}  TRANSIENT_OBJECT_T;

#include "UnPack"

#define BEGIN_PATTERN	0xABCDEF
#define END_PATTERN		0xABCDEF

#define RELEASE_OBJECT(o) o->Release();

typedef void (*SYNCHRONIZATION_ERROR_T)(cTransientObject * object);

//## end module%3A6BF14C0281.additionalDeclarations


//## begin cTransientObject%3A6BF14C0281.preface preserve=yes
//## end cTransientObject%3A6BF14C0281.preface

//## Class: cTransientObject%3A6BF14C0281
//	Transient objects are used to communicate structured
//	informations through the Shacira channel system. An
//	object that inherits from cTransient can be instantiated
//	in arbitrary classes that inherit from cStaticObject
//	classes and can be raised through the method Raise
//	Event() to be feeded into the Shacira channel system.
//	From this point of view, transient objects can be
//	considered as signals that transport information of
//	arbitrary complexity.
//	Performance considerations led to a realization with
//	object pointers and reference counting. When transient
//	objects are sent through the Shacira channel system the
//	reference count is increased and decreased automatically
//	if necessary.
//	A receiver of a transient object should increment the
//	reference count when it stores the object pointer for
//	later use.
//	When a transient object is no longer used it must be
//	released through the method Release().
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC8D5D10252;cMutexSem { -> }
//## Uses: <unnamed>%3BA21BDD016F;cTimeObject { -> }
//## Uses: <unnamed>%3E5A68FB0026;cTransferObject { -> }
//## Uses: <unnamed>%3E5B44B2031B;cInfo { -> F}
//## Uses: <unnamed>%3E5B44BB018E;cState { -> F}
//## Uses: <unnamed>%3E5B44CC0391;cProxy { -> F}
//## Uses: <unnamed>%3E5B44D60219;cEvent { -> F}
//## Uses: <unnamed>%3E5B44E1007A;cDataChange { -> F}
//## Uses: <unnamed>%3E5B44F20147;cJobSpec { -> F}
//## Uses: <unnamed>%3E5B45050130;cJobEntry { -> F}
//## Uses: <unnamed>%3E5B450D0344;cAlarm { -> F}
//## Uses: <unnamed>%3E70AFA10109;cCorbaCellProxy { -> F}
//## Uses: <unnamed>%3E70AFAC03A9;cCosEventChannelProxy { -> F}
//## Uses: <unnamed>%419856F100AB;cUserInfo { -> F}
//## Uses: <unnamed>%41F127290280;cObjectLock { -> F}
//## Uses: <unnamed>%42CBD3500251;cProgress { -> F}
//## Uses: <unnamed>%43108689008E;cCustomFunctions { -> }
//## Uses: <unnamed>%4326CC4601D4;cRequest { -> F}

class __DLL_EXPORT__ cTransientObject 
{
  //## begin cTransientObject%3A6BF14C0281.initialDeclarations preserve=yes
public:
    //## Constructors (generated)
      cTransientObject();

      cTransientObject(const cTransientObject &right);

    //## Constructors (specified)
      //## Operation: cTransientObject%985248929
      cTransientObject (cStaticObject *source);

    //## Destructor (generated)
   virtual ~cTransientObject();

    //## Other Operations (specified)
      //## Operation: AddRef%982663969
      //	AddRef increases the reference count of a transient
      //	object.
      void AddRef ();

      //## Operation: Release%982663970
      //	Releases decreases the reference count of a transient
      //	object. If the reference count reaches zero the object
      //	will be deleted.
      void Release ();

      //## Operation: Serialize%1023780985
      //	Virtual method to serialize a transient object to a
      //	string that represents the internal state ofthe object.
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023780986
      //	Construct constructs a transient object from its
      //	serialized representation. The method returns true if
      //	the construction succeeds, false otherwise.
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

      //## Operation: Parse%1046160463
      //	The static method Parse is used to check object type and
      //	validity in advance of constructing a serialized object.
      static cTransientObject * Parse (CONST_STRING_T serialized_obj);

      //## Operation: IsInvalid%1047469644
      //	This method checks validity of a transient object.
      BOOL_T IsInvalid ();

      //## Operation: Source%1094030185
      //	Returns the source (a static object) from which the
      //	event object originated.
      virtual cStaticObject * Source ();

      //## Operation: ConstructObject%1125156840
      static cTransientObject * ConstructObject (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ObjectCount%3A9242F001F3
      static ATOMIC_T get_ObjectCount ();

      //## Attribute: ObjectNo%3A9FEAA100E4
      static ATOMIC_T get_ObjectNo ();

      //## Attribute: ObjectIdent%3A9FE9F80357
      ATOMIC_T get_ObjectIdent () const;
      void set_ObjectIdent (ATOMIC_T value);

      //## Attribute: Type%3A6BFFAC02AB
      ULONG_T get_Type () const;
      void set_Type (ULONG_T value);

      //## Attribute: SubType%3FBF550A000F
      ULONG_T get_SubType () const;
      void set_SubType (ULONG_T value);

      //## Attribute: EventCode%3ED39DC901B5
      ULONG_T get_EventCode () const;
      void set_EventCode (ULONG_T value);

      //## Attribute: TimeStamp%3AF412B0004B
      cTimeObject get_TimeStamp () const;
      void set_TimeStamp (cTimeObject value);

      //## Attribute: CellName%3BC1E82502B0
      STRING_T get_CellName () const;
      void set_CellName (STRING_T value);

      //## Attribute: SourceName%3E5A63C3016F
      STRING_T get_SourceName () const;
      void set_SourceName (STRING_T value);

      //## Attribute: ObjectFlags%419B0FC001F4
      ULONG_T get_ObjectFlags () const;
      void set_ObjectFlags (ULONG_T value);

      //## Attribute: Key%3E5B7E9102F6
      STRING_T get_Key () const;
      void set_Key (STRING_T value);

      //## Attribute: UserName%41AC6364000F
      STRING_T get_UserName () const;
      void set_UserName (STRING_T value);

      //## Attribute: RefCount%3A9242F00243
      ATOMIC_T get_RefCount () const;

    // Data Members for Class Attributes

      //## begin cTransientObject::Type%3A6BFFAC02AB.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _Type;
      //## end cTransientObject::Type%3A6BFFAC02AB.attr

  public:
    // Additional Public Declarations
      //## begin cTransientObject%3A6BF14C0281.public preserve=yes
      //## end cTransientObject%3A6BF14C0281.public

  protected:

    //## Other Operations (specified)
      //## Operation: SerializeBase%1046095018
      //	This method serialzies only the cTransientObject state
      //	of a transient object.
      void SerializeBase (cTransferObject &transfer_obj);

      //## Operation: ConstructBase%1046095019
      //	This method constructs only the cTransientObject state
      //	of a transient object.
      BOOL_T ConstructBase (cTransferObject &transfer_obj);

    // Data Members for Class Attributes

      //## begin cTransientObject::ObjectCount%3A9242F001F3.attr preserve=no  public: static ATOMIC_T {U} 0
      static ATOMIC_T _ObjectCount;
      //## end cTransientObject::ObjectCount%3A9242F001F3.attr

      //## begin cTransientObject::ObjectNo%3A9FEAA100E4.attr preserve=no  public: static ATOMIC_T {U} 0
      static ATOMIC_T _ObjectNo;
      //## end cTransientObject::ObjectNo%3A9FEAA100E4.attr

      //## begin cTransientObject::ObjectIdent%3A9FE9F80357.attr preserve=no  public: ATOMIC_T {U} 0
      ATOMIC_T _ObjectIdent;
      //## end cTransientObject::ObjectIdent%3A9FE9F80357.attr

      //## begin cTransientObject::SubType%3FBF550A000F.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _SubType;
      //## end cTransientObject::SubType%3FBF550A000F.attr

      //## begin cTransientObject::EventCode%3ED39DC901B5.attr preserve=no  public: ULONG_T {U} UNDEFINED
      ULONG_T _EventCode;
      //## end cTransientObject::EventCode%3ED39DC901B5.attr

      //## begin cTransientObject::TimeStamp%3AF412B0004B.attr preserve=no  public: cTimeObject {U} 
      cTimeObject _TimeStamp;
      //## end cTransientObject::TimeStamp%3AF412B0004B.attr

      //## begin cTransientObject::CellName%3BC1E82502B0.attr preserve=no  public: STRING_T {U} 
      STRING_T _CellName;
      //## end cTransientObject::CellName%3BC1E82502B0.attr

      //## begin cTransientObject::SourceName%3E5A63C3016F.attr preserve=no  public: STRING_T {U} 
      STRING_T _SourceName;
      //## end cTransientObject::SourceName%3E5A63C3016F.attr

      //## begin cTransientObject::ObjectFlags%419B0FC001F4.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ObjectFlags;
      //## end cTransientObject::ObjectFlags%419B0FC001F4.attr

      //## begin cTransientObject::Key%3E5B7E9102F6.attr preserve=no  public: STRING_T {U} 
      STRING_T _Key;
      //## end cTransientObject::Key%3E5B7E9102F6.attr

      //## begin cTransientObject::UserName%41AC6364000F.attr preserve=no  public: STRING_T {U} 
      STRING_T _UserName;
      //## end cTransientObject::UserName%41AC6364000F.attr

      //## begin cTransientObject::RefCount%3A9242F00243.attr preserve=no  public: ATOMIC_T {U} 
      ATOMIC_T _RefCount;
      //## end cTransientObject::RefCount%3A9242F00243.attr

    // Data Members for Associations

      //## Association: System::Objects::<unnamed>%3E5A6280023D
      //## Role: cTransientObject::Source%3E5A6281016C
      //## begin cTransientObject::Source%3E5A6281016C.role preserve=no  public: cStaticObject { -> 0..1RFHN}
      cStaticObject *_Source;
      //## end cTransientObject::Source%3E5A6281016C.role

    // Additional Protected Declarations
      //## begin cTransientObject%3A6BF14C0281.protected preserve=yes
      //## end cTransientObject%3A6BF14C0281.protected

  private:
    // Additional Private Declarations
      //## begin cTransientObject%3A6BF14C0281.private preserve=yes
      //## end cTransientObject%3A6BF14C0281.private

public: //## implementation
    // Data Members for Class Attributes

      //## Attribute: BeginPattern%3E6F1E130222
      //## begin cTransientObject::BeginPattern%3E6F1E130222.attr preserve=no  implementation: ULONG_T {U} BEGIN_PATTERN
      ULONG_T _BeginPattern;
      //## end cTransientObject::BeginPattern%3E6F1E130222.attr

      //## Attribute: EndPattern%3E6F1DEF001F
      //## begin cTransientObject::EndPattern%3E6F1DEF001F.attr preserve=no  implementation: ULONG_T {U} END_PATTERN
      ULONG_T _EndPattern;
      //## end cTransientObject::EndPattern%3E6F1DEF001F.attr

      //## Attribute: ConstructObjectFuncAddress%4310870E0207
      //## begin cTransientObject::ConstructObjectFuncAddress%4310870E0207.attr preserve=no  implementation: static OBJECT_FACTORY_T {U} NULL
      static OBJECT_FACTORY_T _ConstructObjectFuncAddress;
      //## end cTransientObject::ConstructObjectFuncAddress%4310870E0207.attr

    // Additional Implementation Declarations
      //## begin cTransientObject%3A6BF14C0281.implementation preserve=yes
      static cMemPool * _MemPool;
      static cGarbageCollector * _GarbageCollector;
      static SYNCHRONIZATION_ERROR_T _SynchronizationError;
      void SynchronizationError();
      ATOMIC_T _Deleted;
public:
      static void InitializeObjectManagement(cMemPool * pool);
      static void InitializeObjectManagement(cGarbageCollector * collector);
      static bool CheckObjectManagement(STRING_T & result);
      static void ClearGarbage();
      static void SetSynchronizationError(SYNCHRONIZATION_ERROR_T error_function);
      void * operator new(size_t);
      void operator delete(void * memory);
      //## end cTransientObject%3A6BF14C0281.implementation
};

//## begin cTransientObject%3A6BF14C0281.postscript preserve=yes
//## end cTransientObject%3A6BF14C0281.postscript

// Class cTransientObject 

//## begin module%3A6BF14C0281.epilog preserve=yes
//## end module%3A6BF14C0281.epilog


#endif

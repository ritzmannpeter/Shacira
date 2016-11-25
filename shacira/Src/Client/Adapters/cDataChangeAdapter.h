//## begin module%3D063A9A01D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D063A9A01D3.cm

//## begin module%3D063A9A01D3.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D063A9A01D3.cp

//## Module: cDataChangeAdapter%3D063A9A01D3; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cDataChangeAdapter.h

#ifndef cDataChangeAdapter_h
#define cDataChangeAdapter_h 1

//## begin module%3D063A9A01D3.includes preserve=yes
//## end module%3D063A9A01D3.includes

// cPtrList
#include "System/Memory/cPtrList.h"
// cAdapter
#include "System/Channel/cAdapter.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cVarRef;

//## begin module%3D063A9A01D3.additionalDeclarations preserve=yes

typedef std::map<STRING_T, cPtrList*> VAR_REF_MAP_T;

//## end module%3D063A9A01D3.additionalDeclarations


//## begin cDataChangeAdapter%3D063A9A01D3.preface preserve=yes
//## end cDataChangeAdapter%3D063A9A01D3.preface

//## Class: cDataChangeAdapter%3D063A9A01D3
//## Category: Client::Adapters%3DCC05190174
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D0705CA036D;cVarRef { -> F}
//## Uses: <unnamed>%3D077ED80270;cDataChange { -> F}
//## Uses: <unnamed>%3D0DCEA300C6;cPtrList { -> }
//## Uses: <unnamed>%40E17A020109;cObjectLock { -> F}

class __DLL_EXPORT__ cDataChangeAdapter : public cAdapter  //## Inherits: <unnamed>%3F86C55801A5
{
  //## begin cDataChangeAdapter%3D063A9A01D3.initialDeclarations preserve=yes
public:
  //## end cDataChangeAdapter%3D063A9A01D3.initialDeclarations

    //## Constructors (generated)
      cDataChangeAdapter();

      cDataChangeAdapter(const cDataChangeAdapter &right);

    //## Destructor (generated)
      virtual ~cDataChangeAdapter();


    //## Other Operations (specified)
      //## Operation: Object%1043311228
      virtual void Object (cTransientObject *object);

      //## Operation: VarRefs%1024051746
      cPtrList * VarRefs (CONST_STRING_T name);

      //## Operation: VarRefCount%1024310614
      void VarRefCount (ULONG_T value);

      //## Operation: RegisterVar%1047319824
      virtual void RegisterVar (cVarRef *var_ref);

      //## Operation: UnRegisterVar%1047319825
      virtual void UnRegisterVar (cVarRef *var_ref);

      //## Operation: Lock%1088517104
      void Lock ();

      //## Operation: Unlock%1088517106
      void Unlock ();

  public:
    // Additional Public Declarations
      //## begin cDataChangeAdapter%3D063A9A01D3.public preserve=yes
      //## end cDataChangeAdapter%3D063A9A01D3.public

  protected:
    // Additional Protected Declarations
      //## begin cDataChangeAdapter%3D063A9A01D3.protected preserve=yes
      //## end cDataChangeAdapter%3D063A9A01D3.protected

  private:
    // Additional Private Declarations
      //## begin cDataChangeAdapter%3D063A9A01D3.private preserve=yes
      //## end cDataChangeAdapter%3D063A9A01D3.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: VarRefs%3D09CB6703C5
      //## begin cDataChangeAdapter::VarRefs%3D09CB6703C5.attr preserve=no  protected: VAR_REF_MAP_T {U} 
      VAR_REF_MAP_T _VarRefs;
      //## end cDataChangeAdapter::VarRefs%3D09CB6703C5.attr

      //## Attribute: VarRefVec%3D0DCEC70063
      //## begin cDataChangeAdapter::VarRefVec%3D0DCEC70063.attr preserve=no  protected: cPtrList ** {U} NULL
      cPtrList **_VarRefVec;
      //## end cDataChangeAdapter::VarRefVec%3D0DCEC70063.attr

      //## Attribute: VarRefCount%3D0DD1F9036D
      //## begin cDataChangeAdapter::VarRefCount%3D0DD1F9036D.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _VarRefCount;
      //## end cDataChangeAdapter::VarRefCount%3D0DD1F9036D.attr

    // Additional Implementation Declarations
      //## begin cDataChangeAdapter%3D063A9A01D3.implementation preserve=yes
      //## end cDataChangeAdapter%3D063A9A01D3.implementation

};

//## begin cDataChangeAdapter%3D063A9A01D3.postscript preserve=yes
//## end cDataChangeAdapter%3D063A9A01D3.postscript

// Class cDataChangeAdapter 

//## begin module%3D063A9A01D3.epilog preserve=yes
//## end module%3D063A9A01D3.epilog


#endif

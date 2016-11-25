//## begin module%421209C300FA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%421209C300FA.cm

//## begin module%421209C300FA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%421209C300FA.cp

//## Module: cRefCache%421209C300FA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cRefCache.h

#ifndef cRefCache_h
#define cRefCache_h 1

//## begin module%421209C300FA.includes preserve=yes
//## end module%421209C300FA.includes


class cMutexSem;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cDataChangeAdapter;

//## begin module%421209C300FA.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cVarRef*> VAR_REF_CACHE_T;
typedef std::map<STRING_T,cFuncRef*> FUNC_REF_CACHE_T;

//## end module%421209C300FA.additionalDeclarations


//## begin cRefCache%421209C300FA.preface preserve=yes
//## end cRefCache%421209C300FA.preface

//## Class: cRefCache%421209C300FA
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42120A950138;cVarRef { -> F}
//## Uses: <unnamed>%42120A9D01F4;cFuncRef { -> F}
//## Uses: <unnamed>%421346180251;cDataChangeAdapter { -> F}
//## Uses: <unnamed>%421347AA0213;cMutexSem { -> F}

class __DLL_EXPORT__ cRefCache 
{
  //## begin cRefCache%421209C300FA.initialDeclarations preserve=yes
public:
  //## end cRefCache%421209C300FA.initialDeclarations

    //## Constructors (generated)
      cRefCache();

      cRefCache(const cRefCache &right);

    //## Constructors (specified)
      //## Operation: cRefCache%1108478923
      cRefCache (cContext *context);

    //## Destructor (generated)
      virtual ~cRefCache();


    //## Other Operations (specified)
      //## Operation: VarRef%1108478924
      cVarRef * VarRef (CONST_STRING_T spec);

      //## Operation: FuncRef%1108478925
      cFuncRef * FuncRef (CONST_STRING_T spec);

      //## Operation: AddVarRef%1108478926
      void AddVarRef (CONST_STRING_T spec, cVarRef *var_ref);

      //## Operation: AddFuncRef%1108478927
      void AddFuncRef (CONST_STRING_T spec, cFuncRef *func_ref);

      //## Operation: RegisterVarRefs%1108559440
      BOOL_T RegisterVarRefs (cDataChangeAdapter *adapter);

  public:
    // Additional Public Declarations
      //## begin cRefCache%421209C300FA.public preserve=yes
      //## end cRefCache%421209C300FA.public

  protected:
    // Data Members for Associations

      //## Association: <unnamed>%42120B2C001F
      //## Role: cRefCache::Context%42120B2D005D
      //## begin cRefCache::Context%42120B2D005D.role preserve=no  public: cContext {1 -> 1RFHN}
      cContext *_Context;
      //## end cRefCache::Context%42120B2D005D.role

    // Additional Protected Declarations
      //## begin cRefCache%421209C300FA.protected preserve=yes
      //## end cRefCache%421209C300FA.protected

  private:
    // Additional Private Declarations
      //## begin cRefCache%421209C300FA.private preserve=yes
      //## end cRefCache%421209C300FA.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: RegisterVarRef%1108559441
      BOOL_T RegisterVarRef (cVarRef *var_ref, cDataChangeAdapter *adapter);

    // Data Members for Class Attributes

      //## Attribute: VarRefs%42120A110271
      //## begin cRefCache::VarRefs%42120A110271.attr preserve=no  implementation: VAR_REF_CACHE_T {U} 
      VAR_REF_CACHE_T _VarRefs;
      //## end cRefCache::VarRefs%42120A110271.attr

      //## Attribute: FuncRefs%42120A3E0000
      //## begin cRefCache::FuncRefs%42120A3E0000.attr preserve=no  implementation: FUNC_REF_CACHE_T {U} 
      FUNC_REF_CACHE_T _FuncRefs;
      //## end cRefCache::FuncRefs%42120A3E0000.attr

      //## Attribute: CacheMutex%4213478D02CE
      //## begin cRefCache::CacheMutex%4213478D02CE.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _CacheMutex;
      //## end cRefCache::CacheMutex%4213478D02CE.attr

    // Additional Implementation Declarations
      //## begin cRefCache%421209C300FA.implementation preserve=yes
      //## end cRefCache%421209C300FA.implementation

};

//## begin cRefCache%421209C300FA.postscript preserve=yes
//## end cRefCache%421209C300FA.postscript

// Class cRefCache 

//## begin module%421209C300FA.epilog preserve=yes
//## end module%421209C300FA.epilog


#endif

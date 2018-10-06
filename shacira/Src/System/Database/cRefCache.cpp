//## begin module%421209C300FA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%421209C300FA.cm

//## begin module%421209C300FA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%421209C300FA.cp

//## Module: cRefCache%421209C300FA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cRefCache.cpp

//## begin module%421209C300FA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%421209C300FA.additionalIncludes

//## begin module%421209C300FA.includes preserve=yes
//## end module%421209C300FA.includes

// eb_sema
#include "base/eb_sema.hpp"
// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cRefCache
#include "System/Database/cRefCache.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
//## begin module%421209C300FA.additionalDeclarations preserve=yes
//## end module%421209C300FA.additionalDeclarations


// Class cRefCache 



//## begin cRefCache::CacheMutex%4213478D02CE.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cRefCache::_CacheMutex;
//## end cRefCache::CacheMutex%4213478D02CE.attr


cRefCache::cRefCache()
  //## begin cRefCache::cRefCache%.hasinit preserve=no
      : _Context(NULL)
  //## end cRefCache::cRefCache%.hasinit
  //## begin cRefCache::cRefCache%.initialization preserve=yes
  //## end cRefCache::cRefCache%.initialization
{
  //## begin cRefCache::cRefCache%.body preserve=yes
_ASSERT_UNCOND
  //## end cRefCache::cRefCache%.body
}

cRefCache::cRefCache(const cRefCache &right)
  //## begin cRefCache::cRefCache%copy.hasinit preserve=no
      : _Context(NULL)
  //## end cRefCache::cRefCache%copy.hasinit
  //## begin cRefCache::cRefCache%copy.initialization preserve=yes
  //## end cRefCache::cRefCache%copy.initialization
{
  //## begin cRefCache::cRefCache%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRefCache::cRefCache%copy.body
}

cRefCache::cRefCache (cContext *context)
  //## begin cRefCache::cRefCache%1108478923.hasinit preserve=no
      : _Context(NULL)
  //## end cRefCache::cRefCache%1108478923.hasinit
  //## begin cRefCache::cRefCache%1108478923.initialization preserve=yes
  //## end cRefCache::cRefCache%1108478923.initialization
{
  //## begin cRefCache::cRefCache%1108478923.body preserve=yes
   _Context = context;
  //## end cRefCache::cRefCache%1108478923.body
}


cRefCache::~cRefCache()
{
  //## begin cRefCache::~cRefCache%.body preserve=yes
  //## end cRefCache::~cRefCache%.body
}



//## Other Operations (implementation)
cVarRef * cRefCache::VarRef (CONST_STRING_T spec)
{
  //## begin cRefCache::VarRef%1108478924.body preserve=yes
   VAR_REF_CACHE_T::const_iterator i = _VarRefs.find(spec);
   if (i == _VarRefs.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cRefCache::VarRef%1108478924.body
}

cFuncRef * cRefCache::FuncRef (CONST_STRING_T spec)
{
  //## begin cRefCache::FuncRef%1108478925.body preserve=yes
   FUNC_REF_CACHE_T::const_iterator i = _FuncRefs.find(spec);
   if (i == _FuncRefs.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cRefCache::FuncRef%1108478925.body
}

void cRefCache::AddVarRef (CONST_STRING_T spec, cVarRef *var_ref)
{
  //## begin cRefCache::AddVarRef%1108478926.body preserve=yes
   cObjectLock __lock__(&_CacheMutex);
   _VarRefs[spec] = var_ref;
  //## end cRefCache::AddVarRef%1108478926.body
}

void cRefCache::AddFuncRef (CONST_STRING_T spec, cFuncRef *func_ref)
{
  //## begin cRefCache::AddFuncRef%1108478927.body preserve=yes
   cObjectLock __lock__(&_CacheMutex);
   _FuncRefs[spec] = func_ref;
  //## end cRefCache::AddFuncRef%1108478927.body
}

BOOL_T cRefCache::RegisterVarRefs (cDataChangeAdapter *adapter)
{
  //## begin cRefCache::RegisterVarRefs%1108559440.body preserve=yes
   cObjectLock __lock__(&_CacheMutex);
   VAR_REF_CACHE_T::const_iterator i = _VarRefs.cbegin();
   while (i != _VarRefs.cend()) {
      cVarRef * var_ref = (*i).second;
      RegisterVarRef(var_ref, adapter);
      i++;
   }
   return true;
  //## end cRefCache::RegisterVarRefs%1108559440.body
}

BOOL_T cRefCache::RegisterVarRef (cVarRef *var_ref, cDataChangeAdapter *adapter)
{
  //## begin cRefCache::RegisterVarRef%1108559441.body preserve=yes
   try {
      if (var_ref != NULL) {
         if (adapter != NULL) {
            var_ref->Register(adapter);
         } else {
            ErrorPrintf("no adapter to register variable reference %s: %p\n",
                        var_ref->_Spec.c_str(), var_ref);
            return false;
         }
      }
   } catch(cError & e) {
      ErrorPrintf("%s registering variable reference %s: %p\n",
                  e.ErrMsg().c_str(), var_ref->_Spec.c_str(), var_ref);
      return false;
   } catch(...) {
      ErrorPrintf("unhandled exception registering variable reference %s: %p\n",
                  var_ref->_Spec.c_str(), var_ref);
      return false;
   }
   return true;
  //## end cRefCache::RegisterVarRef%1108559441.body
}

// Additional Declarations
  //## begin cRefCache%421209C300FA.declarations preserve=yes
  //## end cRefCache%421209C300FA.declarations

//## begin module%421209C300FA.epilog preserve=yes
//## end module%421209C300FA.epilog

//## begin module%3D063A9A01D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D063A9A01D3.cm

//## begin module%3D063A9A01D3.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D063A9A01D3.cp

//## Module: cDataChangeAdapter%3D063A9A01D3; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cDataChangeAdapter.cpp

//## begin module%3D063A9A01D3.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D063A9A01D3.additionalIncludes

//## begin module%3D063A9A01D3.includes preserve=yes
//## end module%3D063A9A01D3.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
//## begin module%3D063A9A01D3.additionalDeclarations preserve=yes

#define AllocRefVec(value)    ((cPtrList**)cSystemUtils::Alloc(sizeof(cPtrList*)*value))
#define DeleteRefVec(vec)     (cSystemUtils::Free(vec))

//## end module%3D063A9A01D3.additionalDeclarations


// Class cDataChangeAdapter 







cDataChangeAdapter::cDataChangeAdapter()
  //## begin cDataChangeAdapter::cDataChangeAdapter%.hasinit preserve=no
      : _VarRefVec(NULL), _VarRefCount(0)
  //## end cDataChangeAdapter::cDataChangeAdapter%.hasinit
  //## begin cDataChangeAdapter::cDataChangeAdapter%.initialization preserve=yes
  //## end cDataChangeAdapter::cDataChangeAdapter%.initialization
{
  //## begin cDataChangeAdapter::cDataChangeAdapter%.body preserve=yes
  //## end cDataChangeAdapter::cDataChangeAdapter%.body
}

cDataChangeAdapter::cDataChangeAdapter(const cDataChangeAdapter &right)
  //## begin cDataChangeAdapter::cDataChangeAdapter%copy.hasinit preserve=no
      : _VarRefVec(NULL), _VarRefCount(0)
  //## end cDataChangeAdapter::cDataChangeAdapter%copy.hasinit
  //## begin cDataChangeAdapter::cDataChangeAdapter%copy.initialization preserve=yes
  //## end cDataChangeAdapter::cDataChangeAdapter%copy.initialization
{
  //## begin cDataChangeAdapter::cDataChangeAdapter%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDataChangeAdapter::cDataChangeAdapter%copy.body
}


cDataChangeAdapter::~cDataChangeAdapter()
{
  //## begin cDataChangeAdapter::~cDataChangeAdapter%.body preserve=yes
   if (_VarRefVec != NULL) {
      for (unsigned long i=0; i<_VarRefCount; i++) {
         cPtrList * var_ref_list = _VarRefVec[i];
         if (var_ref_list != NULL) delete var_ref_list;
      }
      DeleteRefVec(_VarRefVec);
   }
  //## end cDataChangeAdapter::~cDataChangeAdapter%.body
}



//## Other Operations (implementation)
void cDataChangeAdapter::Object (cTransientObject *object)
{
  //## begin cDataChangeAdapter::Object%1043311228.body preserve=yes
   cObjectLock __lock__(&_LockMutex);
   ULONG_T object_type = object->get_Type();
   if (object_type != OT_DATA_CHANGE) {
//      ErrorPrintf("invalid object type %d directed to data change adapter\n", object_type);
      return;
   }
   cDataChange * data_change = (cDataChange*)object;
   if (_VarRefVec != NULL) {
      long var_id = data_change->get_VarId();
      if (var_id > 0 && (unsigned long)var_id < _VarRefCount) {
         cPtrList * var_ref_list = _VarRefVec[var_id];
         if (var_ref_list != NULL) {
            cPtrList::cConstIterator i = var_ref_list->Begin();
            if (i.First()) {
               do {
                  cVarRef * var_ref = (cVarRef*)i.Ptr();
                  if (var_ref != NULL) {
                     if (var_ref->Matches(data_change)) {
                        UCHAR_T data_type = var_ref->DataType();
                        if (data_type == SH_BYTE ||
                            data_type == SH_OBJECT) {
                           BUF_T buf = data_change->get_BufPtr();
                           if (buf != NULL) {
                              var_ref->NewValue(buf,
                                                data_change->get_TimeOffset(),
                                                data_change->get_ValueSize(),
                                                data_change->get_DataSet());
                           }
                        } else {
                           var_ref->NewValue(data_change->get_Value().c_str(),
                                             data_change->get_TimeOffset(),
                                             data_change->get_ValueSize(),
                                             data_change->get_DataSet());
                        }
                     }
                  }
               } while (i.Next());
            }
         }
      }
   }
   cPtrList * var_ref_list = VarRefs(data_change->get_VarName().c_str());
   if (var_ref_list != NULL) {
      cPtrList::cConstIterator i = var_ref_list->Begin();
      if (i.First()) {
         do {
            cVarRef * var_ref = (cVarRef*)i.Ptr();
            if (var_ref != NULL) {
               if (var_ref->Matches(data_change)) {
                  UCHAR_T data_type = var_ref->DataType();
                  if (data_type == SH_BYTE ||
                     data_type == SH_OBJECT) {
                     BUF_T buf = data_change->get_BufPtr();
                     if (buf != NULL) {
                        var_ref->NewValue(buf,
                                          data_change->get_TimeOffset(),
                                          data_change->get_ValueSize(),
                                          data_change->get_DataSet());
                     }
                  } else {
                     var_ref->NewValue(data_change->get_Value().c_str(),
                                       data_change->get_TimeOffset(),
                                       data_change->get_ValueSize(),
                                       data_change->get_DataSet());
                  }
               }
            }
         } while (i.Next());
      }
   }
  //## end cDataChangeAdapter::Object%1043311228.body
}

cPtrList * cDataChangeAdapter::VarRefs (CONST_STRING_T name)
{
  //## begin cDataChangeAdapter::VarRefs%1024051746.body preserve=yes
   VAR_REF_MAP_T::const_iterator i = _VarRefs.find(name);
   if (i != _VarRefs.end()) {
      return (*i).second;
   } else {
      return NULL;
   }
  //## end cDataChangeAdapter::VarRefs%1024051746.body
}

void cDataChangeAdapter::VarRefCount (ULONG_T value)
{
  //## begin cDataChangeAdapter::VarRefCount%1024310614.body preserve=yes
   if (value > 0 && _VarRefCount == 0) {
      cPtrList ** ref_vec = AllocRefVec(value);
      if (ref_vec != NULL) {
         _VarRefVec = ref_vec;
         _VarRefCount = value;
      }
   } else if (value > _VarRefCount) {
      cPtrList ** old_ref_vec = _VarRefVec;
      cPtrList ** ref_vec = AllocRefVec(value);
      if (ref_vec != NULL) {
         _VarRefVec = ref_vec;
         _VarRefCount = value;
         for (unsigned long i=0; i<_VarRefCount; i++) {
            _VarRefVec[i] = old_ref_vec[i];
         }
         DeleteRefVec(old_ref_vec);
      }
   }
  //## end cDataChangeAdapter::VarRefCount%1024310614.body
}

void cDataChangeAdapter::RegisterVar (cVarRef *var_ref)
{
  //## begin cDataChangeAdapter::RegisterVar%1047319824.body preserve=yes
   if (_VarRefVec != NULL) {
      // try to register using var_id
      long var_id = var_ref->_VarId;
      if (var_id >= 0 && (unsigned long)var_id < _VarRefCount) {
         cPtrList * var_ref_list = _VarRefVec[var_id];
         if (var_ref_list == NULL) {
            var_ref_list = new cPtrList;
            _VarRefVec[var_id] = var_ref_list;
         }
         var_ref_list->Add((void*)var_ref);
         return;
      }
   }
   // try to find using var_name
   CONST_STRING_T var_name = var_ref->_Name.c_str();
   VAR_REF_MAP_T::const_iterator i = _VarRefs.find(var_name);
   cPtrList * var_ref_list = NULL;
   if (i == _VarRefs.end()) {
      var_ref_list = new cPtrList;
      var_ref_list->Add((void*)var_ref);
      _VarRefs[var_name] = var_ref_list;
   } else {
      var_ref_list = (*i).second;
      var_ref_list->Add((void*)var_ref);
   }
  //## end cDataChangeAdapter::RegisterVar%1047319824.body
}

void cDataChangeAdapter::UnRegisterVar (cVarRef *var_ref)
{
  //## begin cDataChangeAdapter::UnRegisterVar%1047319825.body preserve=yes
   if (_VarRefVec != NULL) {
      // try to find using var_id
      long var_id = var_ref->_VarId;
      if (var_id >= 0 && (unsigned long)var_id < _VarRefCount) {
         cPtrList * var_ref_list = _VarRefVec[var_id];
         if (var_ref_list != NULL) {
            var_ref_list->Remove((void*)var_ref);
            return;
         }
      }
   }
   // try to find using var_name
   VAR_REF_MAP_T::const_iterator i = _VarRefs.find(var_ref->_Name.c_str());
   if (i != _VarRefs.end()) {
      cPtrList * var_ref_list = (*i).second;
      var_ref_list->Remove(var_ref);
   }
  //## end cDataChangeAdapter::UnRegisterVar%1047319825.body
}

void cDataChangeAdapter::Lock ()
{
  //## begin cDataChangeAdapter::Lock%1088517104.body preserve=yes
   _LockMutex.request();
  //## end cDataChangeAdapter::Lock%1088517104.body
}

void cDataChangeAdapter::Unlock ()
{
  //## begin cDataChangeAdapter::Unlock%1088517106.body preserve=yes
   _LockMutex.release();
  //## end cDataChangeAdapter::Unlock%1088517106.body
}

// Additional Declarations
  //## begin cDataChangeAdapter%3D063A9A01D3.declarations preserve=yes
  //## end cDataChangeAdapter%3D063A9A01D3.declarations

//## begin module%3D063A9A01D3.epilog preserve=yes
//## end module%3D063A9A01D3.epilog

///## begin module%41CAB08A031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41CAB08A031C.cm

//## begin module%41CAB08A031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41CAB08A031C.cp

//## Module: cExtendedObjectRing%41CAB08A031C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cExtendedObjectRing.cpp

//## begin module%41CAB08A031C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41CAB08A031C.additionalIncludes

//## begin module%41CAB08A031C.includes preserve=yes
//## end module%41CAB08A031C.includes

// cStringUtils
#include "System/cStringUtils.h"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cExtendedObjectRing
#include "System/Structs/cExtendedObjectRing.h"

//## begin module%41CAB08A031C.additionalDeclarations preserve=yes

/// PR 13.06.06 - reconstructing objects that incorporate cr lf
/// PR 08.01.09 - fixed bug that may crash output functions in ErrorPrintf/cSystemUtils::DebugConsolePrintf
//                when output control characters (%...) are embedded in the serialized transient object string
/// PR 28.05.09 - changed error to info reporting in case of distinct object types contained in a ring buffer

#undef USE_SAFE_RING
#ifdef USE_SAFE_RING
#define RING() _SafeRing
#else
#define RING() _Ring
#endif

#define SAVE_INTERVAL 300
#include "Client/RemoteDatabase/cRemoteContext.h"
#include "System/Process/cCellProxy.h"

//## end module%41CAB08A031C.additionalDeclarations


// Class cExtendedObjectRing 










//## begin cExtendedObjectRing::RingMutexes%4211A9DE034B.attr preserve=no  implementation: static RING_MUTEX_MAP_T {U} 
RING_MUTEX_MAP_T cExtendedObjectRing::_RingMutexes;
//## end cExtendedObjectRing::RingMutexes%4211A9DE034B.attr



cExtendedObjectRing::cExtendedObjectRing()
  //## begin cExtendedObjectRing::cExtendedObjectRing%.hasinit preserve=no
      : _SaveInterval(SAVE_INTERVAL), _RefreshInterval(0), _Ring(NULL), _SafeRing(NULL), _ObjectsPending(false), _CurrentBufPos(0), _RemoteRing(false), _RemoteBuffer(NULL), _VarRef(NULL)
  //## end cExtendedObjectRing::cExtendedObjectRing%.hasinit
  //## begin cExtendedObjectRing::cExtendedObjectRing%.initialization preserve=yes
  //## end cExtendedObjectRing::cExtendedObjectRing%.initialization
{
  //## begin cExtendedObjectRing::cExtendedObjectRing%.body preserve=yes
_ASSERT_UNCOND
  //## end cExtendedObjectRing::cExtendedObjectRing%.body
}

cExtendedObjectRing::cExtendedObjectRing(const cExtendedObjectRing &right)
  //## begin cExtendedObjectRing::cExtendedObjectRing%copy.hasinit preserve=no
      : _SaveInterval(SAVE_INTERVAL), _RefreshInterval(0), _Ring(NULL), _SafeRing(NULL), _ObjectsPending(false), _CurrentBufPos(0), _RemoteRing(false), _RemoteBuffer(NULL), _VarRef(NULL)
  //## end cExtendedObjectRing::cExtendedObjectRing%copy.hasinit
  //## begin cExtendedObjectRing::cExtendedObjectRing%copy.initialization preserve=yes
  //## end cExtendedObjectRing::cExtendedObjectRing%copy.initialization
{
  //## begin cExtendedObjectRing::cExtendedObjectRing%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cExtendedObjectRing::cExtendedObjectRing%copy.body
}

cExtendedObjectRing::cExtendedObjectRing (cVarRef* var_ref, ULONG_T refresh_interval)
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802860.hasinit preserve=no
      : _SaveInterval(SAVE_INTERVAL), _RefreshInterval(0), _Ring(NULL), _SafeRing(NULL), _ObjectsPending(false), _CurrentBufPos(0), _RemoteRing(false), _RemoteBuffer(NULL), _VarRef(NULL)
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802860.hasinit
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802860.initialization preserve=yes
  , cFlatObject(var_ref)
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802860.initialization
{
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802860.body preserve=yes
   cContext * context = var_ref->_Context;
   if (context != NULL && context->IsRemote()) {
      _RemoteRing = true;
   }
   _VarRef = var_ref;
   _RefreshInterval = refresh_interval;
   if (_VarRef != NULL) {
      SetObjectName(_VarRef->_Spec.c_str());
   } else {
      SetObjectName("unspecified");
   }
   ULONG_T element_size = sizeof(cTransientObject*);
   ULONG_T bufsize = GetObjectDataSize();
   if (_RemoteRing) {
      _RemoteBuffer = (BUF_T)cSystemUtils::Alloc(bufsize);
      ULONG_T elements = (bufsize - (2 * sizeof(cRingBase::RING))) / element_size;
#ifdef USE_SAFE_RING
      try {
         _SafeRing = new cRingRawSafe(elements, element_size, _RemoteBuffer, bufsize, false, cRingBase::putOverwrite);
      } catch (cErrBase & e) {
         _SafeRing = new cRingRawSafe(elements, element_size, _RemoteBuffer, bufsize, true, cRingBase::putOverwrite);
      }
#else
      try {
         _Ring = new cRingRaw(elements, element_size, _RemoteBuffer, bufsize, false, cRingBase::putOverwrite);
      } catch (cErrBase & e) {
         _Ring = new cRingRaw(elements, element_size, _RemoteBuffer, bufsize, true, cRingBase::putOverwrite);
      }
#endif
      LoadRemote();
   } else {
      BUF_T buffer = (BUF_T)GetObjectData();
      SetPersistenceFiles();
      if (bufsize <= (2 * sizeof(cRingBase::RING))) {
         throw cError(RING_BUFFER_NO_SPACE, 0,
                      cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE + bufsize).c_str(),
                      cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE + (2 * sizeof(cRingBase::RING)) + element_size).c_str());
      } else {
         ULONG_T elements = (bufsize - (2 * sizeof(cRingBase::RING))) / element_size;
#ifdef USE_SAFE_RING
         try {
            _SafeRing = new cRingRawSafe(elements, element_size, buffer, bufsize, false, cRingBase::putOverwrite);
         } catch (cErrBase & e) {
            _SafeRing = new cRingRawSafe(elements, element_size, buffer, bufsize, true, cRingBase::putOverwrite);
         }
#else
         try {
            _Ring = new cRingRaw(elements, element_size, buffer, bufsize, false, cRingBase::putOverwrite);
         } catch (cErrBase & e) {
            _Ring = new cRingRaw(elements, element_size, buffer, bufsize, true, cRingBase::putOverwrite);
         }
#endif
      }
   }
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802860.body
}

cExtendedObjectRing::cExtendedObjectRing (BUF_T buffer, ULONG_T bufsize)
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802861.hasinit preserve=no
      : _SaveInterval(SAVE_INTERVAL), _RefreshInterval(0), _Ring(NULL), _SafeRing(NULL), _ObjectsPending(false), _CurrentBufPos(0), _RemoteRing(false), _RemoteBuffer(NULL), _VarRef(NULL)
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802861.hasinit
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802861.initialization preserve=yes
  , cFlatObject(buffer, bufsize)
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802861.initialization
{
  //## begin cExtendedObjectRing::cExtendedObjectRing%1103802861.body preserve=yes
   ULONG_T element_size = sizeof(cTransientObject*);
   PTR_T data = GetObjectData();
   ULONG_T data_size = GetObjectDataSize();
   if (bufsize <= (2 * sizeof(cRingBase::RING))) {
      throw cError(RING_BUFFER_NO_SPACE, 0,
                   cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE + data_size).c_str(),
                   cConvUtils::StringValue(FLAT_OBJECT_HEADER_SIZE + (2 * sizeof(cRingBase::RING)) + element_size).c_str());
   } else {
      ULONG_T elements = (data_size - (2 * sizeof(cRingBase::RING))) / element_size;
      SetPersistenceFiles();
#ifdef USE_SAFE_RING
      try {
         _SafeRing = new cRingRawSafe(elements, element_size, data, data_size, false, cRingBase::putOverwrite);
      } catch (cErrBase & e) {
         _SafeRing = new cRingRawSafe(elements, element_size, data, data_size, true, cRingBase::putOverwrite);
      }
#else
      try {
         _Ring = new cRingRaw(elements, element_size, data, data_size, false, cRingBase::putOverwrite);
      } catch (cErrBase & e) {
         _Ring = new cRingRaw(elements, element_size, data, data_size, true, cRingBase::putOverwrite);
      }
#endif
   }
  //## end cExtendedObjectRing::cExtendedObjectRing%1103802861.body
}


cExtendedObjectRing::~cExtendedObjectRing()
{
  //## begin cExtendedObjectRing::~cExtendedObjectRing%.body preserve=yes
   if (_RemoteRing) {
      Clear();
      if (_RemoteBuffer != NULL) {
         cSystemUtils::Free(_RemoteBuffer);
      }
   }
   if (_Ring != NULL) {
      delete _Ring;
   }
   if (_SafeRing != NULL) {
      delete _SafeRing;
   }
  //## end cExtendedObjectRing::~cExtendedObjectRing%.body
}



//## Other Operations (implementation)
void cExtendedObjectRing::AddObject (cTransientObject *object)
{
  //## begin cExtendedObjectRing::AddObject%1103802854.body preserve=yes
   cObjectLock __lock__(RingMutex());
   _ObjectsPending = true;
   ULONG_T count = RING()->getCount();
   ULONG_T used = RING()->getUsed();
   if (RING()->isFull()) {
      cTransientObject * release_object = NULL;
      if (RING()->peek(0, &release_object, sizeof(release_object))) {
         if (release_object != NULL) {
            release_object->Release();
         } else {
            int dummy = 0;
         }
      }
   }
   object->AddRef();
   RING()->put(&object, sizeof(cTransientObject*));
   if (!_RemoteRing) {
      if (_RefreshInterval == 0) {
         if (_VarRef != NULL) {
            _VarRef->Refresh();
         }
         _LastRefresh.Now();
         _ObjectsPending = false;
      }
      ULONG_T elapsed = _LastSave.Elapsed();
      if (elapsed > _SaveInterval) {
         _LastSave.Now();
         Save();
      } else {
         Save(object);
      }
   }
  //## end cExtendedObjectRing::AddObject%1103802854.body
}

cTransientObject * cExtendedObjectRing::GetObject (ULONG_T index)
{
  //## begin cExtendedObjectRing::GetObject%1103802855.body preserve=yes
   ULONG_T used = Used();
   if (index < used) {
      cTransientObject * object = NULL;
      if (RING()->peek(index, &object, sizeof(object))) {
         if (object != NULL) {
            object->AddRef();
            return object;
         } else {
            return NULL;
         }
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cExtendedObjectRing::GetObject%1103802855.body
}

cTransientObject * cExtendedObjectRing::GetFirstObject ()
{
  //## begin cExtendedObjectRing::GetFirstObject%1103802862.body preserve=yes
   return GetObject(0);
  //## end cExtendedObjectRing::GetFirstObject%1103802862.body
}

cTransientObject * cExtendedObjectRing::GetLastObject ()
{
  //## begin cExtendedObjectRing::GetLastObject%1103802863.body preserve=yes
   ULONG_T used = Used();
   if (used > 0) {
      return GetObject(used - 1);
   } else {
      return NULL;
   }
  //## end cExtendedObjectRing::GetLastObject%1103802863.body
}

void cExtendedObjectRing::Save (cTransientObject *object)
{
  //## begin cExtendedObjectRing::Save%1103802857.body preserve=yes
   if (_RemoteRing) {
      return;
   }
   cObjectLock __lock__(RingMutex());
   cSHFile persistence_file(_PersistenceFile.c_str());
   cSHFile backup_file(_BackupFile.c_str());
   cSHFile sync_file(_SyncFile.c_str());
   if (object == NULL) {
      if (backup_file.Exists()) {
         backup_file.Remove();
      }
      if (persistence_file.Exists()) {
         persistence_file.Move(_BackupFile.c_str());
      }
      if (sync_file.Exists()) {
         sync_file.Remove();
      }
      if (persistence_file.Open(FILE_ACCESS_APPEND)) {
         STRING_T serialized_object;
         ULONG_T i = 0;
         cTransientObject * object = GetObject(i);
         int t = 0;
         BOOL_T distinct_objects = false;
         int dt = 0;
         int dtc = 0;
         while (object != NULL) {
            if (t == 0) {
               t = object->get_Type();
            } else {
               int tc = object->get_Type();
               if (t != tc) {
                  distinct_objects = true;
                  dt = t;
                  dtc = tc;
               }
            }
            serialized_object += object->Serialize();
            serialized_object += "\n";
            object->Release();
            i++;
            object = GetObject(i);
         }
         if (distinct_objects) {
            InfoPrintf("distinct object types (%d,%d) found in%s\n", dt, dtc, _PersistenceFile.c_str());
         }
         ULONG_T write_len = serialized_object.size();
         if (!persistence_file.WriteBlock((void*)serialized_object.c_str(), write_len)) {
            ErrorPrintf("failed to write block to %s (errno %d)\n", _PersistenceFile.c_str(), errno);
         }
         persistence_file.Close();
      }
      if (sync_file.Open(FILE_ACCESS_APPEND)) {
         sync_file.Printf("sync");
         sync_file.Close();
      }
   } else {
      if (persistence_file.Open(FILE_ACCESS_APPEND)) {
         STRING_T serialized_object;
         serialized_object = object->Serialize();
         serialized_object += "\n";
         ULONG_T write_len = serialized_object.size();
         ULONG_T nwrite = persistence_file.Write((void*)serialized_object.c_str(), write_len);
         if (write_len < nwrite) {
            ErrorPrintf("failed to write to %s (errno %d)\n", _PersistenceFile.c_str(), errno);
         }
         persistence_file.Close();
         cFileSystemUtils::FlushFile(_PersistenceFile.c_str());
      }
   }
  //## end cExtendedObjectRing::Save%1103802857.body
}

void cExtendedObjectRing::Load ()
{
  //## begin cExtendedObjectRing::Load%1103802858.body preserve=yes
   if (_RemoteRing) {
      return;
   }
   cObjectLock __lock__(RingMutex());
   InfoPrintf("load persistent objects of %s ...\n", GetObjectName());
   ULONG_T t = cSystemUtils::RealtimeOffset();
   ULONG_T object_count = 0;
   STRING_T src_file;
   if (cFileSystemUtils::FileExists(_SyncFile.c_str())) {
      src_file = _PersistenceFile;
   } else {
      if (cFileSystemUtils::FileExists(_BackupFile.c_str())) {
         src_file = _BackupFile;
      } else {
         src_file = _PersistenceFile;
      }
   }
   if (!cSHFile::IsAsciiFile(src_file.c_str())) {
      ErrorPrintf("invalid file: %s is not ascii\n", src_file.c_str());
      if (cFileSystemUtils::FileExists(src_file.c_str())) {
         int i = 0;
         char file_addition[0x200] = {0};
         SafePrintf(file_addition, sizeof(file_addition), "_%d.err", i);
         STRING_T error_file = src_file + file_addition;
         while (cFileSystemUtils::FileExists(error_file.c_str())) {
            i++;
            SafePrintf(file_addition, sizeof(file_addition), "_%d.err", i);
            error_file = src_file + file_addition;
         }
         int rc = rename(src_file.c_str(), error_file.c_str());
         if (rc != 0) {
            int error = GetLastError();
            ErrorPrintf("failed to rename file %s to %s: %d\n", src_file.c_str(), error_file.c_str(), error);
         }
      }
      src_file = _BackupFile;
   }
   cSHFile sync_file(_SyncFile.c_str());
   if (!cFileSystemUtils::FileExists(src_file.c_str())) {
      src_file = _PersistenceFile;
   }
   cSHFile file(src_file.c_str());
   if (file.Exists()) {
      if (file.Open()) {
         STRING_T serialized_object;
         while (file.ReadLine(serialized_object)) {
            try {
               while (serialized_object[serialized_object.size()-1] != ')') {
                  STRING_T fragment;
                  if (file.ReadLine(fragment)) {
                     serialized_object += fragment.c_str();
                  } else {
                     break;
                  }
               }
               STRING_T obj_header;
               STRING_T obj_data;
               cTransientObject * object = cTransientObject::Parse(serialized_object.c_str());
               if (object != NULL) {
                  LoadObject(object);
                  object_count++;
                  RELEASE_OBJECT(object)
               } else {
                  int size = serialized_object.size();
                  if (size > 0x4000) {
                     ErrorPrintf("unable to construct object in cExtendedObjectRing::Load\n");
                  } else {
                     // check for format control characters in the serialized object string
                     // if so, this could crash output functions
                     bool has_format_controls = false;
                     int i = 0;
                     for (i=0; i<size; i++) {
                        if (serialized_object[i] == '%') {
                           has_format_controls = true;
                        }
                     }
                     if (has_format_controls) {
                        ErrorPrintf("unable to construct object in cExtendedObjectRing::Load\n");
                     } else {
                        ErrorPrintf("unable to construct %s in cExtendedObjectRing::Load\n", serialized_object.c_str());
                     }
                  }
               }
            } catch (cError & e) {
               ErrorPrintf("%s\nin cExtendedObjectRing::Load %s\n", (const char *)e, GetObjectName());
            } catch (...) {
               ErrorPrintf("unhandled exception in cExtendedObjectRing::Load %s\n", GetObjectName());
            }
         }
         file.Close();
      }
   }
   InfoPrintf("load persistent objects (%d) of %s done %d\n", object_count, GetObjectName(), cSystemUtils::RealtimeOffset() - t);
  //## end cExtendedObjectRing::Load%1103802858.body
}

void cExtendedObjectRing::Refresh ()
{
  //## begin cExtendedObjectRing::Refresh%1110025035.body preserve=yes
   if (_RemoteRing) {
      return;
   }
   cObjectLock __lock__(RingMutex());
   ULONG_T elapsed = _LastRefresh.Elapsed();
   if (elapsed > _RefreshInterval && _ObjectsPending) {
      if (_VarRef != NULL) {
         _VarRef->Refresh();
      }
      _LastRefresh.Now();
      _ObjectsPending = false;
   }
  //## end cExtendedObjectRing::Refresh%1110025035.body
}

ULONG_T cExtendedObjectRing::Used ()
{
  //## begin cExtendedObjectRing::Used%1103802864.body preserve=yes
   return RING()->getUsed();
  //## end cExtendedObjectRing::Used%1103802864.body
}

ULONG_T cExtendedObjectRing::Count ()
{
  //## begin cExtendedObjectRing::Count%1103802865.body preserve=yes
   return RING()->getCount();
  //## end cExtendedObjectRing::Count%1103802865.body
}

void cExtendedObjectRing::Clear ()
{
  //## begin cExtendedObjectRing::Clear%1106841438.body preserve=yes
   cObjectLock __lock__(RingMutex());
   int used = Used();
   try {
      while (used--) {
         cTransientObject * release_object = NULL;
         RING()->get(&release_object, sizeof(release_object));
         if (release_object != NULL) {
            release_object->Release();
         } else {
            int dummy = 0;
         }
      }
   } catch (...) {
      int dummy = 0;
      return;
   }
   if (!_RemoteRing) {
      if (_VarRef != NULL) {
         _VarRef->Refresh();
      }
      _LastRefresh.Now();
      _ObjectsPending = false;
      Save();
   }
  //## end cExtendedObjectRing::Clear%1106841438.body
}

cMutexSem * cExtendedObjectRing::RingMutex ()
{
  //## begin cExtendedObjectRing::RingMutex%1108453910.body preserve=yes
   static cMutexSem * _GlobalMutex = NULL;
   if (_GlobalMutex == NULL) {
      _GlobalMutex = new cMutexSem;
   }
   cObjectLock __lock__(_GlobalMutex);
   RING_MUTEX_MAP_T::const_iterator i = _RingMutexes.find(GetObjectName());
   if (i == _RingMutexes.cend()) {
      cMutexSem * mutex = new cMutexSem;
      const char * object_name = GetObjectName();
      try {
         _RingMutexes[GetObjectName()] = mutex;
      } catch (...) {
         object_name = GetObjectName();
         ErrorPrintf("get RingMutex this %p\n", this);
         ErrorPrintf("get RingMutex object name %p\n", object_name);
         ErrorPrintf("get RingMutex object name=%s\n", object_name);
      }
      return mutex;
   } else {
      return (*i).second;
   }
  //## end cExtendedObjectRing::RingMutex%1108453910.body
}

void cExtendedObjectRing::LoadObject (cTransientObject *object)
{
  //## begin cExtendedObjectRing::LoadObject%1104428022.body preserve=yes
   object->AddRef();
   ULONG_T count = RING()->getCount();
   ULONG_T used = RING()->getUsed();
   if (RING()->isFull()) {
      cTransientObject * release_object = NULL;
      if (RING()->peek(0, &release_object, sizeof(release_object))) {
         if (release_object != NULL) {
            ULONG_T ref_count = release_object->get_RefCount();
            if (ref_count > 1) {
               release_object->Release();
            } else {
               release_object->Release();
               int dummy = 0;
            }
         }
      }
   }
   RING()->put(&object, sizeof(cTransientObject*));
  //## end cExtendedObjectRing::LoadObject%1104428022.body
}

void cExtendedObjectRing::SetPersistenceFiles ()
{
  //## begin cExtendedObjectRing::SetPersistenceFiles%1103802859.body preserve=yes
   STRING_T base_path = cResources::DataPath();
   STRING_T file_name = GetObjectName();
   cStringUtils::Replace(file_name, "[", "_");
   cStringUtils::Replace(file_name, "]", "_");
   STRING_T path = cFileSystemUtils::AppendPath(base_path.c_str(), file_name.c_str());
   _PersistenceFile = path;
   _BackupFile = path;;
   _SyncFile = path;;
   _PersistenceFile += ".pst";
   _BackupFile += ".bak";
   _SyncFile += ".snc";
  //## end cExtendedObjectRing::SetPersistenceFiles%1103802859.body
}

void cExtendedObjectRing::LoadRemote ()
{
  //## begin cExtendedObjectRing::LoadRemote%1243005934.body preserve=yes
   if (!_RemoteRing) {
      return;
   }
   _CurrentBufPos = 0;
   if (_VarRef != NULL) {
      cRemoteContext * context = (cRemoteContext*)_VarRef->_Context;
      if (context != NULL && context->IsRemote()) {
         cCellProxy * cell_proxy = context->Proxy();
         STRING_T var_name = _VarRef->VarName();
         long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
         _VarRef->GetIndices(i1, i2, i3, i4);
         STRING_T serialized_objects = cell_proxy->GetRing(var_name.c_str(), i1, i2, i3, i4, 0);
         STRING_T serialized_object;
         while (GetNextObjectFromBuffer(serialized_objects.c_str(), serialized_object)) {
            STRING_T obj_header;
            STRING_T obj_data;
            cTransientObject * object = cTransientObject::Parse(serialized_object.c_str());
            if (object != NULL) {
               LoadObject(object);
               RELEASE_OBJECT(object)
            } else {
               int size = serialized_object.size();
               if (size > 0x4000) {
                  ErrorPrintf("unable to construct object in cExtendedObjectRing::Load\n");
               } else {
                  // check for format control characters in the serialized object string
                  // if so, this could crash output functions
                  bool has_format_controls = false;
                  int i = 0;
                  for (i=0; i<size; i++) {
                     if (serialized_object[i] == '%') {
                        has_format_controls = true;
                     }
                  }
                  if (has_format_controls) {
                     ErrorPrintf("unable to construct object in cExtendedObjectRing::Load\n");
                  } else {
                     ErrorPrintf("unable to construct %s in cExtendedObjectRing::Load\n", serialized_object.c_str());
                  }
               }
            }
         }
      }
   }
  //## end cExtendedObjectRing::LoadRemote%1243005934.body
}

BOOL_T cExtendedObjectRing::GetNextObjectFromBuffer (CONST_STRING_T object_buffer, STRING_T &serialized_object)
{
  //## begin cExtendedObjectRing::GetNextObjectFromBuffer%1243005935.body preserve=yes
   serialized_object = "";
   char c = object_buffer[_CurrentBufPos];
   if (c == 0) {
      return false;
   }
   while (true) {
      if (c == 1) {
         _CurrentBufPos++;
         return true;
      } else if (c == 0) {
         return true;
      }
      serialized_object += c;
      _CurrentBufPos++;
      c = object_buffer[_CurrentBufPos];
   }
  //## end cExtendedObjectRing::GetNextObjectFromBuffer%1243005935.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cExtendedObjectRing::get_SaveInterval () const
{
  //## begin cExtendedObjectRing::get_SaveInterval%41CAB185004E.get preserve=no
  return _SaveInterval;
  //## end cExtendedObjectRing::get_SaveInterval%41CAB185004E.get
}

ULONG_T cExtendedObjectRing::get_RefreshInterval () const
{
  //## begin cExtendedObjectRing::get_RefreshInterval%4229B90E01C5.get preserve=no
  return _RefreshInterval;
  //## end cExtendedObjectRing::get_RefreshInterval%4229B90E01C5.get
}

// Additional Declarations
  //## begin cExtendedObjectRing%41CAB08A031C.declarations preserve=yes
  //## end cExtendedObjectRing%41CAB08A031C.declarations

//## begin module%41CAB08A031C.epilog preserve=yes
//## end module%41CAB08A031C.epilog

//## begin module%4039D85100CB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039D85100CB.cm

//## begin module%4039D85100CB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039D85100CB.cp

//## Module: cPersistenceManager%4039D85100CB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistenceManager.cpp

//## begin module%4039D85100CB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4039D85100CB.additionalIncludes

//## begin module%4039D85100CB.includes preserve=yes

/// PR 05.07.07 - storage write operations now are supplied with the unit code,
///               that associates a specific physical unit with the stored value

//## end module%4039D85100CB.includes

// cDataChange
#include "System/Objects/cDataChange.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cStorage
#include "Control/LocalDatabase/cStorage.h"
// cPersistenceManager
#include "Control/LocalDatabase/cPersistenceManager.h"
// cBBRAMStorage
#include "Control/LocalDatabase/cBBRAMStorage.h"
// cFileStorage
#include "Control/LocalDatabase/cFileStorage.h"
// cSimpleStorage
#include "Control/LocalDatabase/cSetupStorage.h"
//## begin module%4039D85100CB.additionalDeclarations preserve=yes

#include "Control/LocalDatabase/cPersistentVariable.h"
#define COPY_VALUES(data_type,src,dst,i1,i2,i3,i4) \
try { \
   if (IS_NUMBER(data_type) || \
       IS_STRING(data_type)) { \
      STRING_T value; \
      src->Get(value, i1, i2, i3, i4); \
      dst->Set(value.c_str(), i1, i2, i3, i4, VF_BUFFERED); \
   } else if (data_type == SH_BYTE) {  \
      ULONG_T element_size = backup_variable->ValueSize(); \
      BUF_T value = NULL; \
      src->Get(value, i1, i2, i3, i4); \
      dst->Set(value, element_size, i1, i2, i3, i4, VF_BUFFERED); \
   } \
} catch (cError & e) { \
   ErrorPrintf("%s loading persistent data of variable %s(%d,%d,%d,%d)\n", \
               e.ErrMsg().c_str(), var_name.c_str(), i1, i2, i3, i4); \
} catch (...) { \
   ErrorPrintf("unhandled exception loading persistent data of variable %s(%d,%d,%d,%d)\n", \
               var_name.c_str(), i1, i2, i3, i4); \
}
                  
#include <math.h>
static DOUBLE_T FixedDecimal (DOUBLE_T dval, UCHAR_T precision)
{
   DOUBLE_T d = dval;
   ULONG_T i = 0;
   for (i=0; i<precision; i++) {
      d *= 10;
   }
   double c = ceil(d);
   double f = floor(d);
   double fraction = d - f;
   if (fraction < 0.5) {
      return f;
   } else {
      return c;
   }
}

//## end module%4039D85100CB.additionalDeclarations


// Class cPersistenceManager 





cPersistenceManager::cPersistenceManager()
  //## begin cPersistenceManager::cPersistenceManager%.hasinit preserve=no
      : _DataInitialized(false), _Context(NULL)
  //## end cPersistenceManager::cPersistenceManager%.hasinit
  //## begin cPersistenceManager::cPersistenceManager%.initialization preserve=yes
  //## end cPersistenceManager::cPersistenceManager%.initialization
{
  //## begin cPersistenceManager::cPersistenceManager%.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistenceManager::cPersistenceManager%.body
}

cPersistenceManager::cPersistenceManager(const cPersistenceManager &right)
  //## begin cPersistenceManager::cPersistenceManager%copy.hasinit preserve=no
      : _DataInitialized(false), _Context(NULL)
  //## end cPersistenceManager::cPersistenceManager%copy.hasinit
  //## begin cPersistenceManager::cPersistenceManager%copy.initialization preserve=yes
  //## end cPersistenceManager::cPersistenceManager%copy.initialization
{
  //## begin cPersistenceManager::cPersistenceManager%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistenceManager::cPersistenceManager%copy.body
}

cPersistenceManager::cPersistenceManager (cContext *context)
  //## begin cPersistenceManager::cPersistenceManager%1077539619.hasinit preserve=no
      : _DataInitialized(false), _Context(NULL)
  //## end cPersistenceManager::cPersistenceManager%1077539619.hasinit
  //## begin cPersistenceManager::cPersistenceManager%1077539619.initialization preserve=yes
  //## end cPersistenceManager::cPersistenceManager%1077539619.initialization
{
  //## begin cPersistenceManager::cPersistenceManager%1077539619.body preserve=yes
_ASSERT_COND(context != NULL)
   STRING_T name = context->get_Name();
   name += ".";
   name += "PersistenceManager";
   _Name = name;
   _Context = context;
   SetUp();
  //## end cPersistenceManager::cPersistenceManager%1077539619.body
}

cPersistenceManager::cPersistenceManager (cContext *context, UCHAR_T dset_type)
  //## begin cPersistenceManager::cPersistenceManager%1191907813.hasinit preserve=no
      : _DataInitialized(false), _Context(NULL)
  //## end cPersistenceManager::cPersistenceManager%1191907813.hasinit
  //## begin cPersistenceManager::cPersistenceManager%1191907813.initialization preserve=yes
  //## end cPersistenceManager::cPersistenceManager%1191907813.initialization
{
  //## begin cPersistenceManager::cPersistenceManager%1191907813.body preserve=yes
_ASSERT_COND(context != NULL)
   STRING_T name = context->get_Name();
   name += ".";
   name += "ShadowManager";
   _Name = name;
   _Context = context;
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      SetUpShadow();
   }
  //## end cPersistenceManager::cPersistenceManager%1191907813.body
}


cPersistenceManager::~cPersistenceManager()
{
  //## begin cPersistenceManager::~cPersistenceManager%.body preserve=yes
   STORAGE_MAP_T::const_iterator i = _Storages.cbegin();
   while (i != _Storages.cend()) {
      cStorage * storage = (*i).second;
      delete storage;
      i++;
   }
  //## end cPersistenceManager::~cPersistenceManager%.body
}



//## Other Operations (implementation)
void cPersistenceManager::Object (cTransientObject *object)
{
  //## begin cPersistenceManager::Object%1077533272.body preserve=yes
   UCHAR_T object_type = (UCHAR_T)object->get_Type();
   if (object_type != OT_DATA_CHANGE) {
      return;
   }
   cDataChange * data_change = (cDataChange*)object;
   ULONG_T dataset = data_change->get_DataSet();
   if (dataset != 0) {
      return;
   }
   UCHAR_T data_type = (UCHAR_T)data_change->get_DataType();
   ULONG_T pos = data_change->get_Pos();
   UCHAR_T ptype = (UCHAR_T)data_change->get_PersistenceType();
   UCHAR_T precision = (UCHAR_T)data_change->get_Precision();
   cStorage * storage = Storage(ptype);
   if (storage == NULL) {
      ErrorPrintf("failed to retrieve storage for persistence type %d\n", (int)ptype);
      return;
   }
   switch (data_type) {
   case SH_CHAR:
      {
         CHAR_T val = 0;
         if (precision > 0) {
   			DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (CHAR_T)FixedDecimal(dval, precision);
         } else {
            val = (CHAR_T)atol(data_change->get_Value().c_str());
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)(UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T val = 0;
         if (precision > 0) {
   			DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (UCHAR_T)FixedDecimal(dval, precision);
         } else {
            val = (UCHAR_T)strtoul(data_change->get_Value().c_str(), NULL, 0);
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_SHORT:
      {
         SHORT_T val = 0;
         if (precision > 0) {
   			DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (SHORT_T)FixedDecimal(dval, precision);
         } else {
            val = (SHORT_T)atol(data_change->get_Value().c_str());
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T val = 0;
         if (precision > 0) {
            DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (USHORT_T)FixedDecimal(dval, precision);
         } else {
            val = (USHORT_T)strtoul(data_change->get_Value().c_str(), NULL, 0);
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_LONG:
      {
         LONG_T val = 0;
         if (precision > 0) {
   			DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (LONG_T)FixedDecimal(dval, precision);
         } else {
            val = (LONG_T)atol(data_change->get_Value().c_str());
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T val = 0;
         if (precision > 0) {
   			DOUBLE_T dval = atof(data_change->get_Value().c_str());
            val = (ULONG_T)FixedDecimal(dval, precision);
         } else {
            val = (ULONG_T)strtoul(data_change->get_Value().c_str(), NULL, 0);
         }
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T val = (FLOAT_T)atof(data_change->get_Value().c_str());
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T val = (DOUBLE_T)atof(data_change->get_Value().c_str());
         storage->Write(data_change->get_VarName().c_str(), pos, (CONST_BUF_T)&val, sizeof(val), (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_STRING:
      storage->Write(data_change->get_VarName().c_str(), pos,
                     (CONST_BUF_T)data_change->get_Value().c_str(),
                     data_change->get_Value().size(), (UCHAR_T)data_change->get_UnitCode());
      break;
   case SH_WSTRING:
_ASSERT_UNCOND
      break;
   case SH_BYTE:
      {
         BUF_T buf = data_change->get_BufPtr();
         if (buf == NULL) {
            ErrorPrintf("failed to retrieve buffer from data change object\n");
            return;
         }
         ULONG_T size = data_change->get_ValueSize();
         storage->Write(data_change->get_VarName().c_str(), pos, buf, size, (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   case SH_OBJECT:
      {
         BUF_T buf = data_change->get_BufPtr();
         if (buf == NULL) {
            ErrorPrintf("failed to retrieve buffer from data change object\n");
            return;
         }
         ULONG_T size = data_change->get_ValueSize();
         storage->Write(data_change->get_VarName().c_str(), pos, buf, size, (UCHAR_T)data_change->get_UnitCode());
      }
      break;
   default:
_ASSERT_UNCOND
   }
  //## end cPersistenceManager::Object%1077533272.body
}

void cPersistenceManager::SetUp ()
{
  //## begin cPersistenceManager::SetUp%1077539620.body preserve=yes
   STRING_LIST_T variables;
   _Context->VariableNames(variables);
   ULONG_T var_count = variables.size();
   STRING_T var_name;
   STRING_LIST_T::const_iterator i = variables.cbegin();
   while (i != variables.cend()) {
      CONST_STRING_T var_name = (*i).c_str();
      cLocalVariable * variable = (cLocalVariable*)_Context->Variable(var_name);
      if (variable != NULL) {
         UCHAR_T data_type = variable->DataType();
         UCHAR_T persistence_type = variable->PersistenceType();
         UCHAR_T var_type = variable->VarType();
         ULONG_T dims = variable->Dims();
         ULONG_T dim0 = 0;
         ULONG_T dim1 = 0;
         ULONG_T dim2 = 0;
         ULONG_T dim3 = 0;
         if (dims > 0) dim0 = variable->DimSize(0);
         if (dims > 1) dim1 = variable->DimSize(1);
         if (dims > 2) dim2 = variable->DimSize(2);
         if (dims > 3) dim3 = variable->DimSize(3);
         ULONG_T elements = variable->Elements();
         ULONG_T element_size = variable->ValueSize();
         if (persistence_type != UNDEFINED && persistence_type != SH_RAM) {
            cStorage * storage = Storage(persistence_type);
            storage->AddVariable(variable);
         }
      } else {
         int dummy = 0;
      }
      i++;
   }
   STORAGE_MAP_T::const_iterator j = _Storages.cbegin();
   while (j != _Storages.cend()) {
      cStorage * storage = (*j).second;
      storage->Initialize();
      storage->SetUp();
      if (storage->get_DataInitialized()) {
         _DataInitialized = true;
         if (cResources::FlagSet(PF_LOAD_PERSISTENT_DATA)) {
            LoadPersistentData();
         }
      }
      j++;
   }
  //## end cPersistenceManager::SetUp%1077539620.body
}

cStorage * cPersistenceManager::Storage (UCHAR_T ptype, UCHAR_T dset_type)
{
  //## begin cPersistenceManager::Storage%1077542663.body preserve=yes
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
#define STORAGE_KEY(p,d) (((ULONG_T)d<<8) + p)
      ULONG_T key = STORAGE_KEY(ptype,dset_type);      
      cStorage * storage = NULL;
      STORAGE_MAP_T::const_iterator i = _Storages.find(ptype);
      if (i == _Storages.cend()) {
         switch (ptype) {
         case SH_FILE:
            storage = new cFileStorage(_Context->get_Name().c_str(), false, dset_type);
            _Storages[ptype] = storage;
            break;
         case SH_BBRAM:
            storage = new cBBRAMStorage;
            _Storages[ptype] = storage;
            break;
         case SH_SETUP_PST:
            STRING_T file_name = _Context->get_Name();
            file_name += "Setup";
            storage = new cSetupStorage(file_name.c_str());
            _Storages[ptype] = storage;
            break;
         }
      } else {
         storage = (*i).second;
      }
      return storage;
   } else {
      cStorage * storage = NULL;
      STORAGE_MAP_T::const_iterator i = _Storages.find(ptype);
      if (i == _Storages.cend()) {
         switch (ptype) {
         case SH_FILE:
            storage = new cFileStorage(_Context->get_Name().c_str());
            _Storages[ptype] = storage;
            break;
         case SH_BBRAM:
            storage = new cBBRAMStorage;
            _Storages[ptype] = storage;
            break;
         case SH_SETUP_PST:
            STRING_T file_name = _Context->get_Name();
            file_name += "Setup";
            storage = new cSetupStorage(file_name.c_str());
            _Storages[ptype] = storage;
            break;
         }
      } else {
         storage = (*i).second;
      }
      return storage;
   }
  //## end cPersistenceManager::Storage%1077542663.body
}

void cPersistenceManager::LoadPersistentData ()
{
  //## begin cPersistenceManager::LoadPersistentData%1170178871.body preserve=yes
   STRING_T backup_file = cFileStorage::BackupFile(_Context->get_Name().c_str());
   try {
      if (cFileSystemUtils::FileExists(backup_file.c_str())) {
         cFileStorage * backup_storage = new cFileStorage(backup_file.c_str(), true);
         backup_storage->Initialize();
         cContext * backup_context = backup_storage->Parse();
         if (backup_context != NULL) {
            STRING_LIST_T var_names;
            backup_context->VariableNames(var_names);
            STRING_LIST_T::const_iterator i = var_names.cbegin();
            while (i != var_names.cend()) {
               STRING_T var_name = (*i);
               cVariable * backup_variable = backup_context->Variable(var_name.c_str());
               cVariable * variable = _Context->Variable(var_name.c_str());
               if (backup_variable != NULL && variable != NULL) {
#if (SHACIRA_MINOR > 3) && (SHACIRA_BUG_FIX > 0)
                  /// datatype stored in persistence file
#else
                  try {
                     ((cPersistentVariable*)backup_variable)->SetDataType(variable->DataType());
                  } catch (...) {
                  }
#endif
                  UCHAR_T data_type = backup_variable->DataType();
                  int dim_size[4] = {-1, -1, -1, -1};
                  int dims = backup_variable->Dims();
                  if (dims > 0) dim_size[0] = backup_variable->DimSize(0);
                  if (dims > 1) dim_size[1] = backup_variable->DimSize(1);
                  if (dims > 2) dim_size[2] = backup_variable->DimSize(2);
                  if (dims > 3) dim_size[3] = backup_variable->DimSize(3);
                  LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
                  if (dims == 0) {
                     COPY_VALUES(data_type,backup_variable,variable,i1,i2,i3,i4)
                  } else if (dims == 1) {
                     for (i1=0; i1<dim_size[0]; i1++) {
                        COPY_VALUES(data_type,backup_variable,variable,i1,i2,i3,i4)
                     }
                  } else if (dims == 2) {
                     for (i1=0; i1<dim_size[0]; i1++) {
                        for (i2=0; i2<dim_size[1]; i2++) {
                           COPY_VALUES(data_type,backup_variable,variable,i1,i2,i3,i4)
                        }
                     }
                  } else if (dims == 3) {
                     for (i1=0; i1<dim_size[0]; i1++) {
                        for (i2=0; i2<dim_size[1]; i2++) {
                           for (i3=0; i3<dim_size[2]; i3++) {
                              COPY_VALUES(data_type,backup_variable,variable,i1,i2,i3,i4)
                           }
                        }
                     }
                  } else if (dims == 4) {
                     for (i1=0; i1<dim_size[0]; i1++) {
                        for (i2=0; i2<dim_size[1]; i2++) {
                           for (i3=0; i3<dim_size[2]; i3++) {
                              for (i4=0; i4<dim_size[3]; i4++) {
                                 COPY_VALUES(data_type,backup_variable,variable,i1,i2,i3,i4)
                              }
                           }
                        }
                     }
                  }
               }
               i++;
            }
         }
         delete backup_storage;
      }
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
   } catch (...) {
      printf("unhandled exception loading storage data from %s\n", backup_file.c_str());
   }
  //## end cPersistenceManager::LoadPersistentData%1170178871.body
}

void cPersistenceManager::Save ()
{
  //## begin cPersistenceManager::Save%1191857028.body preserve=yes
   STORAGE_MAP_T::const_iterator j = _Storages.cbegin();
   while (j != _Storages.cend()) {
      cStorage * storage = (*j).second;
      storage->Save();
      storage->Flush();
      j++;
   }
  //## end cPersistenceManager::Save%1191857028.body
}

void cPersistenceManager::SetUpShadow ()
{
  //## begin cPersistenceManager::SetUpShadow%1191857029.body preserve=yes
   UCHAR_T dset_type = SHADOW_DATASET;
   STRING_LIST_T variables;
   _Context->VariableNames(variables);
   ULONG_T var_count = variables.size();
   STRING_T var_name;
   STRING_LIST_T::const_iterator i = variables.cbegin();
   while (i != variables.cend()) {
      CONST_STRING_T var_name = (*i).c_str();
      cLocalVariable * variable = (cLocalVariable*)_Context->Variable(var_name);
      if (variable != NULL) {
         UCHAR_T data_type = variable->DataType();
         UCHAR_T persistence_type = variable->PersistenceType();
         UCHAR_T var_type = variable->VarType();
         ULONG_T dims = variable->Dims();
         ULONG_T dim0 = 0;
         ULONG_T dim1 = 0;
         ULONG_T dim2 = 0;
         ULONG_T dim3 = 0;
         if (dims > 0) dim0 = variable->DimSize(0);
         if (dims > 1) dim1 = variable->DimSize(1);
         if (dims > 2) dim2 = variable->DimSize(2);
         if (dims > 3) dim3 = variable->DimSize(3);
         ULONG_T elements = variable->Elements();
         ULONG_T element_size = variable->ValueSize();
         if (persistence_type != UNDEFINED && persistence_type != SH_RAM) {
            cStorage * storage = Storage(persistence_type, dset_type);
            storage->AddVariable(variable);
         }
      } else {
         int dummy = 0;
      }
      i++;
   }
   STORAGE_MAP_T::const_iterator j = _Storages.cbegin();
   while (j != _Storages.cend()) {
      cStorage * storage = (*j).second;
      storage->Initialize();
      storage->SetUp();
      if (storage->get_DataInitialized()) {
         _DataInitialized = true;
         if (cResources::FlagSet(PF_LOAD_PERSISTENT_DATA)) {
            LoadPersistentData();
         }
      }
      j++;
   }
  //## end cPersistenceManager::SetUpShadow%1191857029.body
}

void cPersistenceManager::Clear()
{
   STORAGE_MAP_T::const_iterator j = _Storages.cbegin();
   while (j != _Storages.cend()) {
      cStorage * storage = (*j).second;
      storage->Clear();
      j++;
   }
}

void cPersistenceManager::SetBuffered(BOOL_T state)
{
   STORAGE_MAP_T::const_iterator j = _Storages.cbegin();
   while (j != _Storages.cend()) {
      cStorage * storage = (*j).second;
      storage->SetBuffered(state);
      j++;
   }
};

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cPersistenceManager::get_DataInitialized () const
{
  //## begin cPersistenceManager::get_DataInitialized%40B362CB03C8.get preserve=no
  return _DataInitialized;
  //## end cPersistenceManager::get_DataInitialized%40B362CB03C8.get
}

// Additional Declarations
  //## begin cPersistenceManager%4039D85100CB.declarations preserve=yes
  //## end cPersistenceManager%4039D85100CB.declarations

//## begin module%4039D85100CB.epilog preserve=yes
//## end module%4039D85100CB.epilog



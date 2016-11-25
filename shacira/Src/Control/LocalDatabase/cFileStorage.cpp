//## begin module%403A0EB402BF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%403A0EB402BF.cm

//## begin module%403A0EB402BF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%403A0EB402BF.cp

//## Module: cFileStorage%403A0EB402BF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cFileStorage.cpp

//## begin module%403A0EB402BF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%403A0EB402BF.additionalIncludes

//## begin module%403A0EB402BF.includes preserve=yes
/// PR 31.07.14 - added file buffering
//## end module%403A0EB402BF.includes

// cContext
#include "System/Database/cContext.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cPersistentVariable
#include "Control/LocalDatabase/cPersistentVariable.h"
// cFileStorage
#include "Control/LocalDatabase/cFileStorage.h"
//## begin module%403A0EB402BF.additionalDeclarations preserve=yes

#include "Control/LocalDatabase/cLocalVariable.h"
static UCHAR_T DataType(int element_size)
{
   switch (element_size) {
   case 1: return SH_UCHAR;
   case 2: return SH_USHORT;
   case 4: return SH_ULONG;
   case 8: return SH_DOUBLE;
   default: return SH_STRING;
   }
}

//## end module%403A0EB402BF.additionalDeclarations


// Class cFileStorage 





cFileStorage::cFileStorage()
  //## begin cFileStorage::cFileStorage%.hasinit preserve=no
      : _File(NULL)
  //## end cFileStorage::cFileStorage%.hasinit
  //## begin cFileStorage::cFileStorage%.initialization preserve=yes
  //## end cFileStorage::cFileStorage%.initialization
{
  //## begin cFileStorage::cFileStorage%.body preserve=yes
   _DataFileName = DataFile();
   _BackupFile = BackupFile();
   _TempFile = TempFile();
   _File = new cSHFile(_DataFileName.c_str());
   _CmpBufSize = _File->Size();
   if (_CmpBufSize > 0) {
      _CmpBuffer = (BUF_T)cSystemUtils::Alloc(_CmpBufSize);
      if (_File->Open(FILE_MODE_BINARY|FILE_ACCESS_READ_ONLY)) {
         _File->Read(_CmpBuffer, _CmpBufSize, _CmpBufSize);
         _File->Close();
      }
   } else {
      InfoPrintf("size of data file %s is zero\n", _DataFileName.c_str());
   }
  //## end cFileStorage::cFileStorage%.body
}

cFileStorage::cFileStorage(const cFileStorage &right)
  //## begin cFileStorage::cFileStorage%copy.hasinit preserve=no
      : _File(NULL)
  //## end cFileStorage::cFileStorage%copy.hasinit
  //## begin cFileStorage::cFileStorage%copy.initialization preserve=yes
  //## end cFileStorage::cFileStorage%copy.initialization
{
  //## begin cFileStorage::cFileStorage%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFileStorage::cFileStorage%copy.body
}

cFileStorage::cFileStorage (CONST_STRING_T name, BOOL_T persistence_file, ULONG_T dataset)
  //## begin cFileStorage::cFileStorage%1122619256.hasinit preserve=no
      : _File(NULL)
  //## end cFileStorage::cFileStorage%1122619256.hasinit
  //## begin cFileStorage::cFileStorage%1122619256.initialization preserve=yes
  //## end cFileStorage::cFileStorage%1122619256.initialization
{
  //## begin cFileStorage::cFileStorage%1122619256.body preserve=yes
   if (dataset == SHADOW_DATASET) {
      _ShadowDataset = true;
   }
   _Name = name;
   if (persistence_file) {
      _DataFileName = name;
   } else {
      _DataFileName = DataFile(name, dataset);
      _BackupFile = BackupFile(name, dataset);
   }
   _TempFile = TempFile(name, dataset);
   _File = new cSHFile(_DataFileName.c_str());
   _CmpBufSize = _File->Size();
   if (_CmpBufSize > 0) {
      _CmpBuffer = (BUF_T)cSystemUtils::Alloc(_CmpBufSize);
      if (_File->Open(FILE_MODE_BINARY|FILE_ACCESS_READ_ONLY)) {
         _File->Read(_CmpBuffer, _CmpBufSize, _CmpBufSize);
         _File->Close();
      }
   } else {
      InfoPrintf("size of data file %s is zero\n", _DataFileName.c_str());
   }
  //## end cFileStorage::cFileStorage%1122619256.body
}


cFileStorage::~cFileStorage()
{
  //## begin cFileStorage::~cFileStorage%.body preserve=yes
   DELETE_OBJECT(cSHFile, _File)
  //## end cFileStorage::~cFileStorage%.body
}



//## Other Operations (implementation)
void cFileStorage::SetUp ()
{
  //## begin cFileStorage::SetUp%1077542666.body preserve=yes
   if (_CmpBuffer != NULL) {
      DATA_HEADER_T * header = (DATA_HEADER_T *)_Buffer;
      DATA_HEADER_T * cmp_header = (DATA_HEADER_T *)_CmpBuffer;
      VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_Buffer + header->dir_start);
      VAR_ENTRY_T * cmp_dir = (VAR_ENTRY_T*)(_CmpBuffer + cmp_header->dir_start);
      ULONG_T vars = header->vars;
      BOOL_T buffer_dirty = false;
      ULONG_T dir_entry = 0;      
      if (vars == cmp_header->vars) {
         for (ULONG_T i=0; i< vars; i++) {
            if (strcmp(dir->var_name, cmp_dir->var_name) != 0) {
               ErrorPrintf("Detected dirty storage: differences in variable name %s / %s\n",
                           dir->var_name, cmp_dir->var_name);
               buffer_dirty = true;
               break;
            }
            if (dir->dims != cmp_dir->dims) {
               ErrorPrintf("Detected dirty storage: differences in variable structure %s: %d / %d\n",
                           dir->var_name, dir->dims, cmp_dir->dims);
               buffer_dirty = true;
               break;
            }
            for (ULONG_T j=0; j<dir->dims; j++) {
               if (dir->dim_size[j] != cmp_dir->dim_size[j]) {
                  ErrorPrintf("Detected dirty storage: differences in variable dimension size %s:%d %d / %d\n",
                              dir->var_name, dir->dims, dir->dim_size[j], cmp_dir->dim_size[j]);
                  buffer_dirty = true;
                  break;
               }
               if (buffer_dirty) break;
            }
            if (dir->data_offset != cmp_dir->data_offset) {
               ErrorPrintf("Detected dirty storage: differences in variable start offset %s: %x / %x\n",
                            dir->var_name, dir->data_offset, cmp_dir->data_offset);
               buffer_dirty = true;
               break;
            }
            if (dir->elements != cmp_dir->elements) {
               ErrorPrintf("Detected dirty storage: differences in variable element count %s: %d / %d\n",
                            dir->var_name, dir->elements, cmp_dir->elements);
               buffer_dirty = true;
               break;
            }
            if (dir->element_size != cmp_dir->element_size) {
               ErrorPrintf("Detected dirty storage: differences in variable element size %s: %d / %d\n",
                            dir->var_name, dir->element_size, cmp_dir->element_size);
               buffer_dirty = true;
               break;
            }
            if (dir->data_size != cmp_dir->data_size) {
               ErrorPrintf("Detected dirty storage: differences in directory size: %d / %d\n",
                           dir->data_size, cmp_dir->data_size);
               buffer_dirty = true;
               break;
            }
            dir_entry++;
            dir++;
            cmp_dir++;
         }
         if (buffer_dirty) {
            cSystemUtils::Free(_CmpBuffer);
            _CmpBuffer = NULL;
         } else {
            memcpy(_Buffer, _CmpBuffer, _BufSize);
         }
      } else {
         ErrorPrintf("Detected dirty header storage: differences in number of variables %d / %d\n", vars, cmp_header->vars);
         cSystemUtils::Free(_CmpBuffer);
         _CmpBuffer = NULL;
      }
   }
   if (_CmpBuffer != NULL) {
      InfoPrintf("File based storage resync\n");
      Load();
   } else {
      _DataInitialized = true;
      InfoPrintf("Initializing file based storage\n");
      if (cResources::FlagSet(PF_LOAD_PERSISTENT_DATA)) {
         cSHFile backup_file(_BackupFile.c_str());
         if (backup_file.Exists()) {
            backup_file.Remove();
         }
         _File->Move(_BackupFile.c_str());
      }
      if (_File->Open(FILE_MODE_BINARY|FILE_MODE_CREATE)) {
         _File->Write(_Buffer, _BufSize);
         _File->Close();
      }
      if (_ShadowDataset) {
         _CmpBuffer = _Buffer;
         _CmpBufSize = _BufSize;
      }
   }
  //## end cFileStorage::SetUp%1077542666.body
}

void cFileStorage::WriteThrough (BUF_T buffer, ULONG_T address, ULONG_T size)
{
  //## begin cFileStorage::WriteThrough%1077548346.body preserve=yes
   if (_Buffered) {
      int dummy = 0;
   } else {
      cObjectLock __lock__(&_FileMutex);
      if (_File->Open(FILE_MODE_BINARY)) {
         if (_File->Seek(address)) {
            _File->Write(buffer, size);
            _File->Close();
            cFileSystemUtils::FlushFile(_File->Path().c_str());
         }
      }
   }
  //## end cFileStorage::WriteThrough%1077548346.body
}

cContext * cFileStorage::Parse ()
{
  //## begin cFileStorage::Parse%1145513554.body preserve=yes
   if (_CmpBuffer != NULL &&
       _CmpBufSize > sizeof(VAR_ENTRY_T)) {
      cContext * context = new cContext;
      DATA_HEADER_T * header = (DATA_HEADER_T *)_CmpBuffer;
      VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_CmpBuffer + header->dir_start);
      ULONG_T vars = header->vars;
      BOOL_T buffer_dirty = false;
      ULONG_T dir_entry = 0;      
      if (vars == header->vars) {
         for (ULONG_T i=0; i<vars; i++) {
            STRING_T var_name = dir->var_name;
            int dims = dir->dims;
            int dim1_size = dir->dim_size[0];
            int dim2_size = dir->dim_size[1];
            int dim3_size = dir->dim_size[2];
            int dim4_size = dir->dim_size[3];
            if (dims < 0 ||
                dims > 4 ||
                dim1_size < 0 ||
                dim2_size < 0 ||
                dim3_size < 0 ||
                dim4_size < 0) {
               return NULL;
            }
            int elements = dir->elements;
            int element_size = dir->element_size;
//            UCHAR_T data_type = DataType(element_size);
            UCHAR_T data_type = (UCHAR_T)dir->data_type;
            ULONG_T length = element_size;
            if (length == 1 ||
                length == 2 ||
                length == 4 ||
                length == 8) {
               length = 1;
            }
            cVarDef * var_def = new cVarDef(var_name.c_str(), data_type, length, 0, true);
            if (dims > 0) {
               var_def->AddDim(0, dim1_size);
            }
            if (dims > 1) {
               var_def->AddDim(1, dim2_size);
            }
            if (dims > 2) {
               var_def->AddDim(2, dim3_size);
            }
            if (dims > 3) {
               var_def->AddDim(3, dim4_size);
            }
            context->AddVarDef(var_name.c_str(), var_def);
            var_def->_Context = context;
            int offset = dir->data_offset;
            void * buf = &(_CmpBuffer[offset]);
            ULONG_T buf_size = dir->data_size;
            cVariable * variable = new cPersistentVariable(var_def, buf, buf_size);
            var_def->_Variable = variable;
            dir_entry++;
            VAR_ENTRY_T * entry = DirEntry(var_name.c_str());
            if (entry == NULL) {
               _VarEntries[var_name] = dir;
            }
            dir++;
         }
         return context;
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cFileStorage::Parse%1145513554.body
}

STRING_T cFileStorage::DataFile (CONST_STRING_T name, ULONG_T dataset)
{
  //## begin cFileStorage::DataFile%1191857030.body preserve=yes
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      STRING_T file_name = name;
      if (dataset == SHADOW_DATASET) {
         file_name += ".shd";
      } else {
         file_name += ".dat";
      }
      file_name = cFileSystemUtils::AppendPath(cResources::DataPath().c_str(), file_name.c_str());
      return file_name;
   } else {
      STRING_T file_name = name;
      file_name += ".dat";
      file_name = cFileSystemUtils::AppendPath(cResources::DataPath().c_str(), file_name.c_str());
      return file_name;
   }
  //## end cFileStorage::DataFile%1191857030.body
}

STRING_T cFileStorage::BackupFile (CONST_STRING_T name, ULONG_T dataset)
{
  //## begin cFileStorage::BackupFile%1191857031.body preserve=yes
   STRING_T file_name = name;
   file_name += ".bak";
   file_name = cFileSystemUtils::AppendPath(cResources::DataPath().c_str(), file_name.c_str());
   return file_name;
  //## end cFileStorage::BackupFile%1191857031.body
}

STRING_T cFileStorage::TempFile (CONST_STRING_T name, ULONG_T dataset)
{
  //## begin cFileStorage::BackupFile%1191857031.body preserve=yes
   STRING_T file_name = name;
   file_name += ".tmp";
   file_name = cFileSystemUtils::AppendPath(cResources::DataPath().c_str(), file_name.c_str());
   return file_name;
  //## end cFileStorage::BackupFile%1191857031.body
}

void cFileStorage::Flush ()
{
  //## begin cFileStorage::FlushOutput%1191857033.body preserve=yes
#define ATOMIC_FLUSH
#ifdef ATOMIC_FLUSH
   cObjectLock __lock__(&_FileMutex);
   cSHFile backup_file(_BackupFile.c_str());
   if (backup_file.Exists()) {
      backup_file.Remove();
   }
   _File->Move(_BackupFile.c_str());
   cSHFile temp_file(_TempFile.c_str());
   if (temp_file.Open(FILE_MODE_BINARY|FILE_MODE_CREATE)) {
      temp_file.Write(_Buffer, _BufSize);
      temp_file.Close();
      cFileSystemUtils::FlushFile(temp_file.Path().c_str());
      temp_file.Move(_File->Path().c_str());
   } else {
      ErrorPrintf("failed to open temporary file %s\n", _TempFile.c_str());
   }
#else
   if (_File->Open(FILE_MODE_BINARY)) {
      if (_File->Seek(0)) {
         _File->Write(_Buffer, _BufSize);
         _File->Close();
         cFileSystemUtils::FlushFile(_File->get_Path().c_str());
      }
   }
#endif
  //## end cFileStorage::FlushOutput%1191857033.body
}

void cFileStorage::Clear ()
{
   cFileSystemUtils::RemoveFile(_DataFileName.c_str());
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cFileStorage::get_Name () const
{
  //## begin cFileStorage::get_Name%42E9CF1C01A5.get preserve=no
  return _Name;
  //## end cFileStorage::get_Name%42E9CF1C01A5.get
}

// Additional Declarations
  //## begin cFileStorage%403A0EB402BF.declarations preserve=yes
  //## end cFileStorage%403A0EB402BF.declarations

//## begin module%403A0EB402BF.epilog preserve=yes
//## end module%403A0EB402BF.epilog

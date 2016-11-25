//## begin module%4039D91C00DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039D91C00DA.cm

//## begin module%4039D91C00DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039D91C00DA.cp

//## Module: cStorage%4039D91C00DA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cStorage.cpp

//## begin module%4039D91C00DA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4039D91C00DA.additionalIncludes

//## begin module%4039D91C00DA.includes preserve=yes

/// PR 30.01.07 - added datatype to dir entries and version numbers
///               and signature to header (active when shacira version >= 1.4.1)
/// PR 05.07.07 - added physical unit sensitivity to stored data
/// PR 31.07.14 - added virtual interface for file buffering

//## end module%4039D91C00DA.includes

// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cStorage
#include "Control/LocalDatabase/cStorage.h"
//## begin module%4039D91C00DA.additionalDeclarations preserve=yes
//## end module%4039D91C00DA.additionalDeclarations


// Class cStorage 











cStorage::cStorage()
  //## begin cStorage::cStorage%.hasinit preserve=no
      : _DataInitialized(false), _DataSize(0), _StateSize(0), _BufSize(0), _Buffer(NULL), _CmpBufSize(0), _CmpBuffer(NULL), _ShadowDataset(false), _Buffered(false)
  //## end cStorage::cStorage%.hasinit
  //## begin cStorage::cStorage%.initialization preserve=yes
  //## end cStorage::cStorage%.initialization
{
  //## begin cStorage::cStorage%.body preserve=yes
  //## end cStorage::cStorage%.body
}

cStorage::cStorage(const cStorage &right)
  //## begin cStorage::cStorage%copy.hasinit preserve=no
      : _DataInitialized(false), _DataSize(0), _StateSize(0), _BufSize(0), _Buffer(NULL), _CmpBufSize(0), _CmpBuffer(NULL), _ShadowDataset(false), _Buffered(false)
  //## end cStorage::cStorage%copy.hasinit
  //## begin cStorage::cStorage%copy.initialization preserve=yes
  //## end cStorage::cStorage%copy.initialization
{
  //## begin cStorage::cStorage%copy.body preserve=yes
  //## end cStorage::cStorage%copy.body
}


cStorage::~cStorage()
{
  //## begin cStorage::~cStorage%.body preserve=yes
   if (_Buffer != NULL) {
      cSystemUtils::Free(_Buffer);
   }
  //## end cStorage::~cStorage%.body
}



//## Other Operations (implementation)
void cStorage::AddVariable (cLocalVariable *variable)
{
  //## begin cStorage::AddVariable%1191857034.body preserve=yes
   STRING_T var_name = variable->VarName();
   _Variables[var_name.c_str()] = variable;
   _DataSize += variable->Elements() * variable->ValueSize();
   _StateSize += variable->Elements();
  //## end cStorage::AddVariable%1191857034.body
}

void cStorage::Initialize ()
{
  //## begin cStorage::Initialize%1191857035.body preserve=yes
   ULONG_T var_count = _Variables.size();
   _BufSize = sizeof(DATA_HEADER_T) +
              (sizeof(VAR_ENTRY_T) * var_count) +
              _DataSize + _StateSize;
   _Buffer = (BUF_T)cSystemUtils::Alloc(_BufSize);
   DATA_HEADER_T * header = (DATA_HEADER_T*)_Buffer;
   header->signature = PERSISTENCE_SIGNATURE;
   header->major = SHACIRA_MAJOR;
   header->minor = SHACIRA_MINOR;
   header->bug_fix = SHACIRA_BUG_FIX;
   header->size = _BufSize;
   header->vars = var_count;
   header->dir_start = sizeof(DATA_HEADER_T);
   header->data_start = header->dir_start + (sizeof(VAR_ENTRY_T) * var_count);
   header->state_start = header->dir_start + ((sizeof(VAR_ENTRY_T) * var_count) + _DataSize);
   VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_Buffer + header->dir_start);
   std::map<STRING_T, cLocalVariable*>::const_iterator i = _Variables.begin();
   ULONG_T data_offset = header->data_start;
   ULONG_T state_offset = header->state_start;
   while (i != _Variables.end()) {
      cLocalVariable * variable = (*i).second;
      STRING_T var_name = variable->VarName().c_str();
      memcpy(dir->var_name, var_name.c_str(), var_name.size());
      dir->data_offset = data_offset;
      dir->state_offset = state_offset;
      dir->dims = variable->Dims();
      if (dir->dims > 0) dir->dim_size[0] = variable->DimSize(0);
      if (dir->dims > 1) dir->dim_size[1] = variable->DimSize(1);
      if (dir->dims > 2) dir->dim_size[2] = variable->DimSize(2);
      if (dir->dims > 3) dir->dim_size[3] = variable->DimSize(3);
      dir->elements = variable->Elements();
      dir->element_size = variable->ValueSize();
      dir->data_size = dir->elements * dir->element_size;
      dir->state_size = dir->elements;
      dir->data_type = variable->DataType();
      data_offset += dir->data_size;
      state_offset += dir->state_size;
      _VarEntries[dir->var_name] = dir;
      dir++;
      i++;
   }
  //## end cStorage::Initialize%1191857035.body
}

void cStorage::Load ()
{
  //## begin cStorage::Load%1191857037.body preserve=yes
   if (_ShadowDataset) {
      LoadShadowDataset();
      return;
   }
   DATA_HEADER_T * header = (DATA_HEADER_T *)_Buffer;
   DATA_HEADER_T * cmp_header = (DATA_HEADER_T *)_CmpBuffer;
   VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_Buffer + header->dir_start);
   VAR_ENTRY_T * cmp_dir = (VAR_ENTRY_T*)(_CmpBuffer + cmp_header->dir_start);
   ULONG_T vars = header->vars;
   for (ULONG_T i=0; i<vars; i++) {
      STRING_T var_name = dir->var_name;
      cLocalVariable * variable = Variable(var_name.c_str());
      if (variable != NULL) {
         BUF_T dst_data_buf = variable->GetBuf();
         if (dst_data_buf != NULL) {
            BUF_T src_data_buf = BufAddress(dir->data_offset);
            ULONG_T size = variable->GetBufSize();
            memcpy(dst_data_buf, src_data_buf, size);
            if (variable->get_Initialized()) {
               ErrorPrintf("warning: reset values of variable %s\n", variable->VarName().c_str());
            }
            UCHAR_T code = 0;
            ULONG_T elements = dir->elements;
            UCHAR_T * src_state_buf = BufAddress(dir->state_offset);
            ULONG_T pos = 0;
            for (pos=0; pos<elements; pos++) {
               code = *src_state_buf; 
               variable->SetUnitCode(pos, code);
               src_state_buf++;
            }
            variable->set_Initialized(true);
         }
      }
      dir++;
   }
  //## end cStorage::Load%1191857037.body
}

void cStorage::Save ()
{
  //## begin cStorage::Save%1191857038.body preserve=yes
   if (_ShadowDataset) {
      SaveShadowDataset();
      return;
   }
  //## end cStorage::Save%1191857038.body
}

void cStorage::Write (CONST_STRING_T var_name, ULONG_T pos, CONST_BUF_T buffer, ULONG_T len, UCHAR_T unit_code)
{
  //## begin cStorage::Write%1191857039.body preserve=yes
   VAR_ENTRY_T * dir = DirEntry(var_name);
   if (dir != NULL) {
      ULONG_T buf_len = dir->element_size;
      ULONG_T data_address = dir->data_offset + (pos * dir->element_size);
      ULONG_T state_address = dir->state_offset + pos;
      BUF_T data_buf = BufAddress(data_address);
      if (buf_len < len) {
         len = buf_len;
      }
      memcpy(data_buf, buffer, len);
      if (buf_len > len) {
         memset(&data_buf[len], 0, buf_len - len);
      }
      WriteThrough(data_buf, data_address, buf_len);
      if (state_address < _BufSize) {
         UCHAR_T * state_buf = BufAddress(state_address);
         *state_buf = unit_code;
         WriteThrough(state_buf, state_address, 1);
      }
   }
  //## end cStorage::Write%1191857039.body
}

ULONG_T cStorage::GetAddress (CONST_STRING_T var_name, ULONG_T pos)
{
  //## begin cStorage::GetAddress%1191857043.body preserve=yes
   ULONG_T address = 0;
   VAR_ENTRY_T * dir = DirEntry(var_name);
   if (dir != NULL) {
      ULONG_T absolute_pos = pos * dir->element_size;
      address = dir->data_offset + absolute_pos;
   }
   return address;
  //## end cStorage::GetAddress%1191857043.body
}

ULONG_T cStorage::GetElementSize (CONST_STRING_T var_name)
{
  //## begin cStorage::GetElementSize%1191857044.body preserve=yes
   ULONG_T element_size = 0;
   cLocalVariable * variable = Variable(var_name);
   if (variable != NULL) {
      cVarDef * var_def = variable->_VarDef;
      element_size = var_def->ElementSize();
   }
   return element_size;
  //## end cStorage::GetElementSize%1191857044.body
}

VAR_ENTRY_T * cStorage::DirEntry (CONST_STRING_T var_name)
{
  //## begin cStorage::DirEntry%1191857045.body preserve=yes
   std::map<STRING_T,VAR_ENTRY_T*>::const_iterator i = _VarEntries.find(var_name);
   if (i == _VarEntries.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cStorage::DirEntry%1191857045.body
}

BUF_T cStorage::BufAddress (ULONG_T address)
{
  //## begin cStorage::BufAddress%1191857046.body preserve=yes
   return (_Buffer + address);
  //## end cStorage::BufAddress%1191857046.body
}

ULONG_T cStorage::DataAddress (ULONG_T address)
{
  //## begin cStorage::DataAddress%1191857047.body preserve=yes
   return address;
  //## end cStorage::DataAddress%1191857047.body
}

cLocalVariable * cStorage::Variable (CONST_STRING_T var_name)
{
  //## begin cStorage::Variable%1191857048.body preserve=yes
   std::map<STRING_T,cLocalVariable*>::const_iterator i = _Variables.find(var_name);
   if (i == _Variables.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cStorage::Variable%1191857048.body
}

void cStorage::LoadShadowDataset ()
{
  //## begin cStorage::LoadShadowDataset%1191857049.body preserve=yes
   DATA_HEADER_T * header = (DATA_HEADER_T *)_Buffer;
   DATA_HEADER_T * cmp_header = (DATA_HEADER_T *)_CmpBuffer;
   VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_Buffer + header->dir_start);
   VAR_ENTRY_T * cmp_dir = (VAR_ENTRY_T*)(_CmpBuffer + cmp_header->dir_start);
   ULONG_T vars = header->vars;
   for (ULONG_T i=0; i<vars; i++) {
      STRING_T var_name = dir->var_name;
      cLocalVariable * variable = Variable(var_name.c_str());
      if (variable != NULL) {
         BUF_T dst_data_buf = variable->GetBuf(SHADOW_DATASET);
         if (dst_data_buf != NULL) {
            BUF_T src_data_buf = BufAddress(dir->data_offset);
            ULONG_T size = variable->GetBufSize();
            memcpy(dst_data_buf, src_data_buf, size);
            UCHAR_T code = 0;
            ULONG_T elements = dir->elements;
            UCHAR_T * src_state_buf = BufAddress(dir->state_offset);
            ULONG_T pos = 0;
            for (pos=0; pos<elements; pos++) {
               code = *src_state_buf; 
               variable->SetUnitCode(pos, code, SHADOW_DATASET);
               src_state_buf++;
            }
         }
      }
      dir++;
   }
  //## end cStorage::LoadShadowDataset%1191857049.body
}

void cStorage::SaveShadowDataset ()
{
  //## begin cStorage::SaveShadowDataset%1191857050.body preserve=yes
   DATA_HEADER_T * header = (DATA_HEADER_T *)_Buffer;
   DATA_HEADER_T * cmp_header = (DATA_HEADER_T *)_CmpBuffer;
   VAR_ENTRY_T * dir = (VAR_ENTRY_T*)(_Buffer + header->dir_start);
   VAR_ENTRY_T * cmp_dir = (VAR_ENTRY_T*)(_CmpBuffer + cmp_header->dir_start);
   ULONG_T vars = header->vars;
   for (ULONG_T i=0; i<vars; i++) {
      STRING_T var_name = dir->var_name;
      cLocalVariable * variable = Variable(var_name.c_str());
      if (variable != NULL) {
         BUF_T dst_data_buf = variable->GetBuf(SHADOW_DATASET);
         if (dst_data_buf != NULL) {
            BUF_T src_data_buf = BufAddress(dir->data_offset);
            ULONG_T size = variable->GetBufSize();
            memcpy(src_data_buf, dst_data_buf, size);
            UCHAR_T code = 0;
            ULONG_T elements = dir->elements;
            UCHAR_T * dst_state_buf = BufAddress(dir->state_offset);
            ULONG_T pos = 0;
            for (pos=0; pos<elements; pos++) {
               code = variable->UnitCode(pos, SHADOW_DATASET);
               *dst_state_buf = code; 
               dst_state_buf++;
            }
         }
      }
      dir++;
   }
  //## end cStorage::SaveShadowDataset%1191857050.body
}

void cStorage::Flush ()
{
  //## begin cStorage::FlushOutput%1191857042.body preserve=yes
  //## end cStorage::FlushOutput%1191857042.body
}

void cStorage::Clear()
{
}

void cStorage::SetBuffered(BOOL_T state)
{
   if (state != _Buffered) {
      _Buffered = state;
      if (!_Buffered) {
         Flush();
      }
   }
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cStorage::get_DataInitialized () const
{
  //## begin cStorage::get_DataInitialized%470A567F02EF.get preserve=no
  return _DataInitialized;
  //## end cStorage::get_DataInitialized%470A567F02EF.get
}

// Additional Declarations
  //## begin cStorage%4039D91C00DA.declarations preserve=yes
  //## end cStorage%4039D91C00DA.declarations

//## begin module%4039D91C00DA.epilog preserve=yes
//## end module%4039D91C00DA.epilog

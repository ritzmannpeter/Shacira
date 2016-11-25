//## begin module%444727B902E0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%444727B902E0.cm

//## begin module%444727B902E0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%444727B902E0.cp

//## Module: cPersistentVariable%444727B902E0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistentVariable.cpp

//## begin module%444727B902E0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%444727B902E0.additionalIncludes

//## begin module%444727B902E0.includes preserve=yes

/// PR 02.01.07 - temporary incomplete fix of missing data types
///               by using external information through ::SetDataType(...)

//## end module%444727B902E0.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cPersistentVariable
#include "Control/LocalDatabase/cPersistentVariable.h"
//## begin module%444727B902E0.additionalDeclarations preserve=yes

#define VALUE_ADDRESS(pos,size) (_Buffer + (pos*size))

//## end module%444727B902E0.additionalDeclarations


// Class cPersistentVariable 



cPersistentVariable::cPersistentVariable()
  //## begin cPersistentVariable::cPersistentVariable%.hasinit preserve=no
      : _Buffer(NULL), _BufSize(0)
  //## end cPersistentVariable::cPersistentVariable%.hasinit
  //## begin cPersistentVariable::cPersistentVariable%.initialization preserve=yes
  //## end cPersistentVariable::cPersistentVariable%.initialization
{
  //## begin cPersistentVariable::cPersistentVariable%.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistentVariable::cPersistentVariable%.body
}

cPersistentVariable::cPersistentVariable(const cPersistentVariable &right)
  //## begin cPersistentVariable::cPersistentVariable%copy.hasinit preserve=no
      : _Buffer(NULL), _BufSize(0)
  //## end cPersistentVariable::cPersistentVariable%copy.hasinit
  //## begin cPersistentVariable::cPersistentVariable%copy.initialization preserve=yes
  //## end cPersistentVariable::cPersistentVariable%copy.initialization
{
  //## begin cPersistentVariable::cPersistentVariable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistentVariable::cPersistentVariable%copy.body
}

cPersistentVariable::cPersistentVariable (cVarDef *var_def, void *buf, ULONG_T buf_size)
  //## begin cPersistentVariable::cPersistentVariable%1145514031.hasinit preserve=no
      : _Buffer(NULL), _BufSize(0)
  //## end cPersistentVariable::cPersistentVariable%1145514031.hasinit
  //## begin cPersistentVariable::cPersistentVariable%1145514031.initialization preserve=yes
      , cVariable(var_def)
  //## end cPersistentVariable::cPersistentVariable%1145514031.initialization
{
  //## begin cPersistentVariable::cPersistentVariable%1145514031.body preserve=yes
   _BufSize = buf_size;
   _Buffer = (BUF_T)cSystemUtils::Alloc(_BufSize);
   memcpy(_Buffer, buf, _BufSize);
  //## end cPersistentVariable::cPersistentVariable%1145514031.body
}


cPersistentVariable::~cPersistentVariable()
{
  //## begin cPersistentVariable::~cPersistentVariable%.body preserve=yes
   if (_Buffer != NULL) {
      cSystemUtils::Free(_Buffer);
   }
  //## end cPersistentVariable::~cPersistentVariable%.body
}



//## Other Operations (implementation)
void cPersistentVariable::Get (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514032.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (CHAR_T)lval;
  //## end cPersistentVariable::Get%1145514032.body
}

void cPersistentVariable::Get (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514033.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (UCHAR_T)lval;
  //## end cPersistentVariable::Get%1145514033.body
}

void cPersistentVariable::Get (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514034.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (SHORT_T)lval;
  //## end cPersistentVariable::Get%1145514034.body
}

void cPersistentVariable::Get (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514035.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (USHORT_T)lval;
  //## end cPersistentVariable::Get%1145514035.body
}

void cPersistentVariable::Get (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514036.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = *val;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (LONG_T)*val;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Get%1145514036.body
}

void cPersistentVariable::Get (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514037.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (ULONG_T)lval;
  //## end cPersistentVariable::Get%1145514037.body
}

void cPersistentVariable::Get (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514038.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = *val;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (FLOAT_T)*val;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Get%1145514038.body
}

void cPersistentVariable::Get (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514039.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = (DOUBLE_T)*val;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         value = *val;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Get%1145514039.body
}

void cPersistentVariable::Get (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514040.body preserve=yes
   char num_buf[0x50] = {0};
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_UCHAR:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_SHORT:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_USHORT:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_LONG:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_ULONG:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%d", (int)(*(ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_FLOAT:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%f", (double)(*(FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_DOUBLE:
      {
         SafePrintf(num_buf, sizeof(num_buf), "%f", (double)(*(DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize())));
      }
      break;
   case SH_BYTE: break;
   case SH_STRING:
      value = (CONST_STRING_T)VALUE_ADDRESS(pos, _VarDef->ElementSize());
      break;
   case SH_WSTRING: break;
   }
   value = num_buf;
  //## end cPersistentVariable::Get%1145514040.body
}

void cPersistentVariable::Get (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514041.body preserve=yes
  //## end cPersistentVariable::Get%1145514041.body
}

void cPersistentVariable::Get (BUF_T &buf_ptr, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514042.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   buf_ptr = (BUF_T)VALUE_ADDRESS(pos, _VarDef->ElementSize());;
  //## end cPersistentVariable::Get%1145514042.body
}

void cPersistentVariable::Get (BUF_T &buf_ptr, ULONG_T &size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
}

void cPersistentVariable::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Get%1145514043.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   memcpy(buf, (BUF_T)VALUE_ADDRESS(pos, _VarDef->ElementSize()), _MIN_(len, _VarDef->ElementSize()));
  //## end cPersistentVariable::Get%1145514043.body
}

void cPersistentVariable::Set (CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514044.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514044.body
}

void cPersistentVariable::Set (UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514045.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514045.body
}

void cPersistentVariable::Set (SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514046.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514046.body
}

void cPersistentVariable::Set (USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514047.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514047.body
}

void cPersistentVariable::Set (LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514048.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (SHORT_T)value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (USHORT_T)value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (LONG_T)value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (ULONG_T)value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (FLOAT_T)value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (DOUBLE_T)value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514048.body
}

void cPersistentVariable::Set (ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514049.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (SHORT_T)value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (USHORT_T)value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (LONG_T)value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (ULONG_T)value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (FLOAT_T)value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (DOUBLE_T)value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514049.body
}

void cPersistentVariable::Set (FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514050.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (SHORT_T)value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (USHORT_T)value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (LONG_T)value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (ULONG_T)value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (FLOAT_T)value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (DOUBLE_T)value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514050.body
}

void cPersistentVariable::Set (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514051.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)value;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)value;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (SHORT_T)value;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (USHORT_T)value;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (LONG_T)value;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (ULONG_T)value;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (FLOAT_T)value;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (DOUBLE_T)value;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
  //## end cPersistentVariable::Set%1145514051.body
}

void cPersistentVariable::Set (CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514052.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   switch (_VarDef->_DataType) {
   case SH_CHAR:
      {
         CHAR_T * val = (CHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (CHAR_T)atol(value);
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * val = (UCHAR_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (UCHAR_T)strtoul(value, NULL, 0);
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * val = (SHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (SHORT_T)atol(value);
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * val = (USHORT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (USHORT_T)strtoul(value, NULL, 0);
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * val = (LONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (LONG_T)atol(value);
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * val = (ULONG_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (ULONG_T)strtoul(value, NULL, 0);
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * val = (FLOAT_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (FLOAT_T)atof(value);
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * val = (DOUBLE_T*)VALUE_ADDRESS(pos, _VarDef->ElementSize());
         *val = (DOUBLE_T)atof(value);
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }

  //## end cPersistentVariable::Set%1145514052.body
}

void cPersistentVariable::Set (CONST_WSTRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514053.body preserve=yes
  //## end cPersistentVariable::Set%1145514053.body
}

void cPersistentVariable::Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::Set%1145514054.body preserve=yes
  //## end cPersistentVariable::Set%1145514054.body
}

void cPersistentVariable::GetMinimum (LONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cPersistentVariable::GetMinimum%1145514055.body preserve=yes
  //## end cPersistentVariable::GetMinimum%1145514055.body
}

void cPersistentVariable::GetMinimum (ULONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cPersistentVariable::GetMinimum%1145514056.body preserve=yes
  //## end cPersistentVariable::GetMinimum%1145514056.body
}

void cPersistentVariable::GetMinimum (FLOAT_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMinimum%1145514057.body preserve=yes
  //## end cPersistentVariable::GetMinimum%1145514057.body
}

void cPersistentVariable::GetMinimum (DOUBLE_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMinimum%1145514058.body preserve=yes
  //## end cPersistentVariable::GetMinimum%1145514058.body
}

void cPersistentVariable::GetMinimum (STRING_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMinimum%1145514059.body preserve=yes
  //## end cPersistentVariable::GetMinimum%1145514059.body
}

void cPersistentVariable::GetMaximum (LONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cPersistentVariable::GetMaximum%1145514060.body preserve=yes
  //## end cPersistentVariable::GetMaximum%1145514060.body
}

void cPersistentVariable::GetMaximum (ULONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cPersistentVariable::GetMaximum%1145514061.body preserve=yes
  //## end cPersistentVariable::GetMaximum%1145514061.body
}

void cPersistentVariable::GetMaximum (FLOAT_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMaximum%1145514062.body preserve=yes
  //## end cPersistentVariable::GetMaximum%1145514062.body
}

void cPersistentVariable::GetMaximum (DOUBLE_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMaximum%1145514063.body preserve=yes
  //## end cPersistentVariable::GetMaximum%1145514063.body
}

void cPersistentVariable::GetMaximum (STRING_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cPersistentVariable::GetMaximum%1145514064.body preserve=yes
  //## end cPersistentVariable::GetMaximum%1145514064.body
}

void cPersistentVariable::SetDataType (UCHAR_T data_type)
{
  //## begin cPersistentVariable::SetDataType%1170178870.body preserve=yes
   if (_VarDef != NULL) {
      _VarDef->_DataType = data_type;
   }
  //## end cPersistentVariable::SetDataType%1170178870.body
}

ULONG_T cPersistentVariable::GetObject (cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::GetObject%1238436646.body preserve=yes
   return 0;
  //## end cPersistentVariable::GetObject%1238436646.body
}

void cPersistentVariable::SetObject (const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cPersistentVariable::SetObject%1238436647.body preserve=yes
  //## end cPersistentVariable::SetObject%1238436647.body
}

// Additional Declarations
  //## begin cPersistentVariable%444727B902E0.declarations preserve=yes
  //## end cPersistentVariable%444727B902E0.declarations

//## begin module%444727B902E0.epilog preserve=yes
//## end module%444727B902E0.epilog


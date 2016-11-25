//## begin module%3C6A7DFE0288.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C6A7DFE0288.cm

//## begin module%3C6A7DFE0288.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C6A7DFE0288.cp

//## Module: cValueBuffer%3C6A7DFE0288; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cValueBuffer.cpp

//## begin module%3C6A7DFE0288.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C6A7DFE0288.additionalIncludes

//## begin module%3C6A7DFE0288.includes preserve=yes
//## end module%3C6A7DFE0288.includes

// cSHVariant
#include "System/Database/cSHVariant.h"
// cValueBuffer
#include "Control/LocalDatabase/cValueBuffer.h"
//## begin module%3C6A7DFE0288.additionalDeclarations preserve=yes

#define ABSOLUTE_POS(pos) (pos *_ElementSize)

#define COMPANY         "2i Industrial Informatics GmbH"
#define START_PATTERN   0x01234
#define END_PATTERN     0x56789

typedef struct start_signature {
   ULONG_T pattern;
   const char * company;
}  START_SIGNATURE;

typedef struct end_signature {
   USHORT_T filler;
   ULONG_T pattern;
}  END_SIGNATURE;


static void MemoryCopy(void * dst, const char * src, int len)
{
//InfoPrintf("memcpy1(%p,%p,%d)\n", dst, src, len);
    memcpy(dst, src, len);
}

static void MemoryCopy(void * dst, const unsigned char * src, int len)
{
//InfoPrintf("memcpy2(%p,%p,%d)\n", dst, src, len);
    memcpy(dst, src, len);
}

static void MemoryCopy(void * dst, const unsigned short * src, int len)
{
//InfoPrintf("memcpy3(%p,%p,%d)\n", dst, src, len);
    memcpy(dst, src, len);
}

static void MemoryCopy(void * dst, void * src, int len)
{
//InfoPrintf("memcpy4(%p,%p,%d)\n", dst, src, len);
    memcpy(dst, src, len);
}

static void MemorySet(void * buf, int c, int len)
{
//InfoPrintf("memset(%p,%d,%d)\n", buf, c, len);
    memset(buf, c, len);
}

//## end module%3C6A7DFE0288.additionalDeclarations


// Class cValueBuffer 






cValueBuffer::cValueBuffer()
  //## begin cValueBuffer::cValueBuffer%.hasinit preserve=no
      : _DataType(UNDEFINED), _Elements(0), _ElementSize(0), _Size(0), _Buffer(NULL)
  //## end cValueBuffer::cValueBuffer%.hasinit
  //## begin cValueBuffer::cValueBuffer%.initialization preserve=yes
  //## end cValueBuffer::cValueBuffer%.initialization
{
  //## begin cValueBuffer::cValueBuffer%.body preserve=yes
_ASSERT_UNCOND
  //## end cValueBuffer::cValueBuffer%.body
}

cValueBuffer::cValueBuffer(const cValueBuffer &right)
  //## begin cValueBuffer::cValueBuffer%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _Elements(0), _ElementSize(0), _Size(0), _Buffer(NULL)
  //## end cValueBuffer::cValueBuffer%copy.hasinit
  //## begin cValueBuffer::cValueBuffer%copy.initialization preserve=yes
  //## end cValueBuffer::cValueBuffer%copy.initialization
{
  //## begin cValueBuffer::cValueBuffer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cValueBuffer::cValueBuffer%copy.body
}

cValueBuffer::cValueBuffer (UCHAR_T data_type, ULONG_T elements, ULONG_T element_size)
  //## begin cValueBuffer::cValueBuffer%1013620385.hasinit preserve=no
      : _DataType(UNDEFINED), _Elements(0), _ElementSize(0), _Size(0), _Buffer(NULL)
  //## end cValueBuffer::cValueBuffer%1013620385.hasinit
  //## begin cValueBuffer::cValueBuffer%1013620385.initialization preserve=yes
  //## end cValueBuffer::cValueBuffer%1013620385.initialization
{
  //## begin cValueBuffer::cValueBuffer%1013620385.body preserve=yes
   _DataType = data_type;
   _Elements = elements;
   _ElementSize = element_size;
   _Size = elements * element_size;
   _Buffer = AllocBuf(_Size);
  //## end cValueBuffer::cValueBuffer%1013620385.body
}


cValueBuffer::~cValueBuffer()
{
  //## begin cValueBuffer::~cValueBuffer%.body preserve=yes
   if (_Buffer != NULL) FreeBuf(_Buffer);
  //## end cValueBuffer::~cValueBuffer%.body
}



//## Other Operations (implementation)
ULONG_T cValueBuffer::ValueSize ()
{
  //## begin cValueBuffer::ValueSize%1071244255.body preserve=yes
   return _ElementSize;
  //## end cValueBuffer::ValueSize%1071244255.body
}

void cValueBuffer::Get (ULONG_T pos, CHAR_T &value)
{
  //## begin cValueBuffer::Get%1056464037.body preserve=yes
   LONG_T temp_val = 0;
   Get(pos, temp_val);
   value = (CHAR_T)temp_val;
  //## end cValueBuffer::Get%1056464037.body
}

void cValueBuffer::Get (ULONG_T pos, UCHAR_T &value)
{
  //## begin cValueBuffer::Get%1056464038.body preserve=yes
   LONG_T temp_val = 0;
   Get(pos, temp_val);
   value = (UCHAR_T)temp_val;
  //## end cValueBuffer::Get%1056464038.body
}

void cValueBuffer::Get (ULONG_T pos, SHORT_T &value)
{
  //## begin cValueBuffer::Get%1056464039.body preserve=yes
   LONG_T temp_val = 0;
   Get(pos, temp_val);
   value = (SHORT_T)temp_val;
  //## end cValueBuffer::Get%1056464039.body
}

void cValueBuffer::Get (ULONG_T pos, USHORT_T &value)
{
  //## begin cValueBuffer::Get%1056464040.body preserve=yes
   LONG_T temp_val = 0;
   Get(pos, temp_val);
   value = (USHORT_T)temp_val;
  //## end cValueBuffer::Get%1056464040.body
}

void cValueBuffer::Get (ULONG_T pos, LONG_T &value)
{
  //## begin cValueBuffer::Get%1015514460.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * data = (long*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         value = (LONG_T)*data;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1015514460.body
}

void cValueBuffer::Get (ULONG_T pos, ULONG_T &value)
{
  //## begin cValueBuffer::Get%1056464041.body preserve=yes
   LONG_T temp_val = 0;
   Get(pos, temp_val);
   value = (ULONG_T)temp_val;
  //## end cValueBuffer::Get%1056464041.body
}

void cValueBuffer::Get (ULONG_T pos, FLOAT_T &value)
{
  //## begin cValueBuffer::Get%1056464042.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         char * data = (char*)&_Buffer[absolute_pos];
         char lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         UCHAR_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         SHORT_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         USHORT_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_LONG:
      {
         long * data = (long*)&_Buffer[absolute_pos];
         long lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         ULONG_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         FLOAT_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         DOUBLE_T lval = *data;
         value = (FLOAT_T)lval;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1056464042.body
}

void cValueBuffer::Get (ULONG_T pos, DOUBLE_T &value)
{
  //## begin cValueBuffer::Get%1015514462.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         char * data = (char*)&_Buffer[absolute_pos];
         char lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         UCHAR_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         SHORT_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         USHORT_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_LONG:
      {
         long * data = (long*)&_Buffer[absolute_pos];
         long lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         ULONG_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         FLOAT_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         DOUBLE_T lval = *data;
         value = (DOUBLE_T)lval;
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1015514462.body
}

void cValueBuffer::Get (ULONG_T pos, STRING_T &value)
{
  //## begin cValueBuffer::Get%1015514458.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * data = (LONG_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         cSHVariant::Float2String(value, (FLOAT_T)*data);
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         cSHVariant::Double2String(value, (DOUBLE_T)*data);
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING:
      {
         void * data = &_Buffer[absolute_pos];
         CHAR_T * buf = (CHAR_T*)cSystemUtils::Alloc(_ElementSize + sizeof(CHAR_T));
         MemoryCopy(buf, data, _ElementSize);
         value = buf;
         cSystemUtils::Free(buf);
         return;
      }
      break;
   case SH_WSTRING:
      {
         void * data = &_Buffer[absolute_pos];
         WCHAR_T * buf = (WCHAR_T*)cSystemUtils::Alloc(_ElementSize + sizeof(WCHAR_T));
         MemoryCopy(buf, data, _ElementSize);
         value = cSHVariant::Wide2String(buf);
         cSystemUtils::Free(buf);
         return;
      }
      break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1015514458.body
}

void cValueBuffer::Get (ULONG_T pos, WSTRING_T &value)
{
  //## begin cValueBuffer::Get%1056464044.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * data = (LONG_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         cSHVariant::Long2String(value, (LONG_T)*data);
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         cSHVariant::Float2String(value, (FLOAT_T)*data);
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         cSHVariant::Double2String(value, (DOUBLE_T)*data);
         return;
      }
      break;
   case SH_BYTE: break;
   case SH_STRING:
      {
         void * data = &_Buffer[absolute_pos];
         CHAR_T * buf = (CHAR_T*)cSystemUtils::Alloc(_ElementSize + sizeof(CHAR_T));
         MemoryCopy(buf, data, _ElementSize);
         value = cSHVariant::String2Wide(buf);
         cSystemUtils::Free(buf);
         return;
      }
      break;
   case SH_WSTRING:
      {
         void * data = &_Buffer[absolute_pos];
         WCHAR_T * buf = (WCHAR_T*)cSystemUtils::Alloc(_ElementSize + sizeof(WCHAR_T));
         MemoryCopy(buf, data, _ElementSize);
         value = buf;
         cSystemUtils::Free(buf);
         return;
      }
      break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1056464044.body
}

void cValueBuffer::Get (ULONG_T pos, BUF_T &buf)
{
  //## begin cValueBuffer::Get%1071244156.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_SHORT:
      {
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_USHORT:
      {
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_LONG:
      {
         LONG_T * data = (LONG_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_ULONG:
      {
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_BYTE:
      {
         buf = &_Buffer[absolute_pos];
         return;
      }
      break;
   case SH_STRING:
      {
         void * data = &_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_WSTRING:
      {
         void * data = &_Buffer[absolute_pos];
         buf = (BUF_T)data;
         return;
      }
      break;
   case SH_OBJECT:
      {
         void ** data = (void**)&_Buffer[absolute_pos];
         buf = (BUF_T)*data;
         return;
      }
      break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1071244156.body
}

void cValueBuffer::Get (ULONG_T pos, BUF_T buf, ULONG_T len, ULONG_T buf_size)
{
  //## begin cValueBuffer::Get%1071244157.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR: break;
   case SH_UCHAR: break;
   case SH_SHORT: break;
   case SH_USHORT: break;
   case SH_LONG: break;
   case SH_ULONG: break;
   case SH_FLOAT: break;
   case SH_DOUBLE: break;
   case SH_BYTE:
      {
         ULONG_T size = _MIN_(_ElementSize, len);
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         MemoryCopy(buf, data, size);
         LONG_T fill = len - size;
         if (fill > 0) MemorySet((buf + size), 0, fill);
         return;
      }
      break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
  //## end cValueBuffer::Get%1071244157.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, CHAR_T value)
{
  //## begin cValueBuffer::Set%1056464045.body preserve=yes
   return Set(pos, (LONG_T)value);
  //## end cValueBuffer::Set%1056464045.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, UCHAR_T value)
{
  //## begin cValueBuffer::Set%1056464046.body preserve=yes
   return Set(pos, (LONG_T)value);
  //## end cValueBuffer::Set%1056464046.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, SHORT_T value)
{
  //## begin cValueBuffer::Set%1056464047.body preserve=yes
   return Set(pos, (LONG_T)value);
  //## end cValueBuffer::Set%1056464047.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, USHORT_T value)
{
  //## begin cValueBuffer::Set%1056464048.body preserve=yes
   return Set(pos, (LONG_T)value);
  //## end cValueBuffer::Set%1056464048.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, LONG_T value)
{
  //## begin cValueBuffer::Set%1015514461.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   BOOL_T data_changed = false;
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T lval = (CHAR_T)value;
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T lval = (UCHAR_T)value;
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_SHORT:
      {
         SHORT_T lval = (SHORT_T)value;
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_USHORT:
      {
         USHORT_T lval = (USHORT_T)value;
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_LONG:
      {
         LONG_T lval = (long)value;
         LONG_T * data = (long*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_ULONG:
      {
         ULONG_T lval = value;
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T lval = (FLOAT_T)value;
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T lval = (DOUBLE_T)value;
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_BYTE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
_ASSERT_UNCOND
   default:
_ASSERT_UNCOND
   }
   return data_changed;
  //## end cValueBuffer::Set%1015514461.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, ULONG_T value)
{
  //## begin cValueBuffer::Set%1056464049.body preserve=yes
   return Set(pos, (LONG_T)value);
  //## end cValueBuffer::Set%1056464049.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, FLOAT_T value)
{
  //## begin cValueBuffer::Set%1056464050.body preserve=yes
// PR 02.03.05
//   return Set(pos, (DOUBLE_T)value);
// implemented direct because of precision problems between real data types
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   BOOL_T data_changed = false;
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T lval = (CHAR_T)value;
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T lval = (UCHAR_T)value;
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_SHORT:
      {
         SHORT_T lval = (SHORT_T)value;
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_USHORT:
      {
         USHORT_T lval = (USHORT_T)value;
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_LONG:
      {
         LONG_T lval = (LONG_T)value;
         LONG_T * data = (LONG_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_ULONG:
      {
         ULONG_T lval = (ULONG_T)value;
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T lval = value;
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T lval = value;
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
_ASSERT_UNCOND
   default:
_ASSERT_UNCOND
   }
   return data_changed;
  //## end cValueBuffer::Set%1056464050.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, DOUBLE_T value)
{
  //## begin cValueBuffer::Set%1015514463.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   BOOL_T data_changed = false;
   switch (_DataType) {
   case SH_CHAR:
      {
         CHAR_T lval = (CHAR_T)value;
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_UCHAR:
      {
         UCHAR_T lval = (UCHAR_T)value;
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_SHORT:
      {
         SHORT_T lval = (SHORT_T)value;
         SHORT_T * data = (SHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_USHORT:
      {
         USHORT_T lval = (USHORT_T)value;
         USHORT_T * data = (USHORT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_LONG:
      {
         LONG_T lval = (LONG_T)value;
         LONG_T * data = (LONG_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_ULONG:
      {
         ULONG_T lval = (ULONG_T)value;
         ULONG_T * data = (ULONG_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_FLOAT:
      {
         FLOAT_T lval = (FLOAT_T)value;
         FLOAT_T * data = (FLOAT_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_DOUBLE:
      {
         DOUBLE_T lval = value;
         DOUBLE_T * data = (DOUBLE_T*)&_Buffer[absolute_pos];
         if (*data != lval) {
            data_changed = true;
            *data = lval;
         }
      }
      break;
   case SH_BYTE:
   case SH_STRING:
   case SH_WSTRING:
_ASSERT_UNCOND
   default:
_ASSERT_UNCOND
   }
   return data_changed;
  //## end cValueBuffer::Set%1015514463.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, UCHAR_T *buf, ULONG_T len)
{
  //## begin cValueBuffer::Set%1056464051.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR: break;
   case SH_UCHAR: break;
   case SH_SHORT: break;
   case SH_USHORT: break;
   case SH_LONG: break;
   case SH_ULONG: break;
   case SH_FLOAT: break;
   case SH_DOUBLE: break;
   case SH_BYTE:
      {
         ULONG_T size = _MIN_(_ElementSize, len);
         UCHAR_T * data = (UCHAR_T*)&_Buffer[absolute_pos];
         MemoryCopy(data, buf, size);
         LONG_T fill = _ElementSize - size;
         if (fill > 0) MemorySet((data + size), 0, fill);
         return true;
      }
      break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
   return false;
  //## end cValueBuffer::Set%1056464051.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, CHAR_T *value)
{
  //## begin cValueBuffer::Set%1015514459.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   BOOL_T data_changed = false;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_FLOAT:
   case SH_DOUBLE:
_ASSERT_UNCOND
   case SH_STRING:
      {
         ULONG_T size = _MIN_(cSHVariant::MemSize(value),_ElementSize);
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         if (cSHVariant::StrCmp(data, value) != 0) {
            data_changed = true; 
            MemoryCopy(data, value, size);
            LONG_T fill = _ElementSize - cSHVariant::MemSize(value);
            if (fill > 0) {
               MemorySet((data + size), 0, fill);
            }
         }
      }
      break;
   case SH_WSTRING:
      {
         WSTRING_T temp_val = cSHVariant::String2Wide(value);
         ULONG_T size = _MIN_(cSHVariant::MemSize(value), _ElementSize);
         WCHAR_T * data = (WCHAR_T*)&_Buffer[absolute_pos];
         if (cSHVariant::StrCmp((CONST_WSTRING_T)data, (CONST_WSTRING_T)value) != 0) {
            data_changed = true; 
            MemoryCopy(data, (const unsigned short *)temp_val.c_str(), size);
            LONG_T fill = _ElementSize - cSHVariant::MemSize(temp_val.c_str());
            if (fill > 0) MemorySet((data + size), 0, fill);
         }
      }
      break;
   }
   return data_changed;
  //## end cValueBuffer::Set%1015514459.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, const CHAR_T *value)
{
  //## begin cValueBuffer::Set%1056464053.body preserve=yes
   return Set(pos, (CHAR_T *)value);
  //## end cValueBuffer::Set%1056464053.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, WCHAR_T *value)
{
  //## begin cValueBuffer::Set%1056464052.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   BOOL_T data_changed = false;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_FLOAT:
   case SH_DOUBLE:
_ASSERT_UNCOND
   case SH_STRING:
      {
         STRING_T temp_val = cSHVariant::Wide2String(value);
         ULONG_T size = _MIN_(cSHVariant::MemSize(temp_val.c_str()), _ElementSize);
         CHAR_T * data = (CHAR_T*)&_Buffer[absolute_pos];
         if (cSHVariant::StrCmp(data, temp_val.c_str()) != 0) {
            data_changed = true; 
            MemoryCopy(data, temp_val.c_str(), size);
            LONG_T fill = _ElementSize - cSHVariant::MemSize(temp_val.c_str());
            if (fill > 0) MemorySet((data + size), 0, fill);
         }
      }
      break;
   case SH_WSTRING:
      {
         ULONG_T size = _MIN_(cSHVariant::MemSize(value), _ElementSize);
         WCHAR_T * data = (WCHAR_T*)&_Buffer[absolute_pos];
         if (cSHVariant::StrCmp(data, value) != 0) {
            data_changed = true; 
            MemoryCopy(data, value, size);
            LONG_T fill = _ElementSize - cSHVariant::MemSize(value);
            if (fill > 0) MemorySet(((char*)data + size), 0, fill);
         }
      }
      break;
   }
   return data_changed;
  //## end cValueBuffer::Set%1056464052.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, const WCHAR_T *value)
{
  //## begin cValueBuffer::Set%1056464054.body preserve=yes
   return Set(pos, (WCHAR_T *)value);
  //## end cValueBuffer::Set%1056464054.body
}

BOOL_T cValueBuffer::Set (ULONG_T pos, CONST_BUF_T buf, ULONG_T len)
{
  //## begin cValueBuffer::Set%1071244158.body preserve=yes
   ULONG_T absolute_pos = ABSOLUTE_POS(pos);
   switch (_DataType) {
   case SH_CHAR: break;
   case SH_UCHAR: break;
   case SH_SHORT: break;
   case SH_USHORT: break;
   case SH_LONG: break;
   case SH_ULONG: break;
   case SH_FLOAT: break;
   case SH_DOUBLE: break;
   case SH_BYTE:
      {
         ULONG_T size = _MIN_(_ElementSize, len);
         UCHAR_T * data = (BUF_T)&_Buffer[absolute_pos];
         MemoryCopy(data, buf, size);
         LONG_T fill = len - size;
         if (fill > 0) MemorySet((data + size), 0, fill);
         return true;
      }
      break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   }
_ASSERT_UNCOND
   return false;
  //## end cValueBuffer::Set%1071244158.body
}

BUF_T cValueBuffer::GetBuf ()
{
  //## begin cValueBuffer::GetBuf%1077613264.body preserve=yes
   return _Buffer;
  //## end cValueBuffer::GetBuf%1077613264.body
}

ULONG_T cValueBuffer::GetBufSize ()
{
  //## begin cValueBuffer::GetBufSize%1077613265.body preserve=yes
   return _Size;
  //## end cValueBuffer::GetBufSize%1077613265.body
}

UCHAR_T * cValueBuffer::AllocBuf (ULONG_T size)
{
  //## begin cValueBuffer::AllocBuf%1056621172.body preserve=yes
   ULONG_T alloc_size = size + sizeof(START_SIGNATURE) + sizeof (END_SIGNATURE);
   UCHAR_T * buf = (UCHAR_T*)cSystemUtils::Alloc(alloc_size);
   START_SIGNATURE * start_sig = (START_SIGNATURE*)buf;
   END_SIGNATURE * end_sig = (END_SIGNATURE*)(buf + size + sizeof(START_SIGNATURE));
   start_sig->pattern = START_PATTERN;
   start_sig->company = COMPANY;
   end_sig->pattern = END_PATTERN;
   buf += sizeof(START_SIGNATURE);
   return buf;
  //## end cValueBuffer::AllocBuf%1056621172.body
}

void cValueBuffer::FreeBuf (UCHAR_T *buf)
{
  //## begin cValueBuffer::FreeBuf%1056621173.body preserve=yes
   cSystemUtils::Free(buf - sizeof(START_SIGNATURE));
  //## end cValueBuffer::FreeBuf%1056621173.body
}

// Additional Declarations
  //## begin cValueBuffer%3C6A7DFE0288.declarations preserve=yes
  //## end cValueBuffer%3C6A7DFE0288.declarations

//## begin module%3C6A7DFE0288.epilog preserve=yes
//## end module%3C6A7DFE0288.epilog

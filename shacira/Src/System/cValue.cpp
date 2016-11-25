
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "string"
#include "cValue.h"

static unsigned long wstrlen(const wide_char * str)
{
   unsigned long size = 0;
   const wide_char * str_ptr = str;
   while (*str_ptr != 0) {
      size++;
      str_ptr++;
   }
   return size;
}

#define A_SET(var, value) var = value;
#define A_INCREMENT(var) ++var;
#define A_DECREMENT(var) --var;

unsigned long cValue::_Allocations = 0;

/// constructors
cValue::cValue(const cValue & right)
{
   Initialize();
   Clone(right);
}

cValue::cValue(const char * v)
{
   Initialize();
   _Size = strlen(v);
   _Type = string;
   _Buffer = AllocBuffer(_Size+1);
   Copy((void*)_Buffer->buffer, v, _Size);
}

cValue::cValue(const wide_char * v)
{
   Initialize();
   _Size = wstrlen(v) * sizeof(wide_char);
   _Type = wide_string;
   _Buffer = AllocBuffer(_Size + sizeof(wide_char));
   Copy((void*)_Buffer->buffer, v, _Size);
}

cValue::cValue(const void * v, unsigned long size)
{
   Initialize();
   _Type = byte;
   _Size = size;
   _Buffer = AllocBuffer(_Size);
   Copy((void*)_Buffer->buffer, v, _Size);
}

/// destructor
cValue::~cValue()
{
   FreeResources();
}

/// assignment operator
cValue cValue::operator =(const cValue & right)
{
   Clone(right);
   return *this;
}

/// type operators

cValue::operator bool()
{
	if (_IntegerValue == 0) {
		return false;
	} else {
		return true;
	}
}

cValue::operator char()
{
   return (char)_IntegerValue;
}

cValue::operator short()
{
   return (short)_IntegerValue;
}

cValue::operator int()
{
   return (int)_IntegerValue;
}

cValue::operator long()
{
   return (long)_IntegerValue;
}

cValue::operator unsigned char()
{
   return (unsigned char)(unsigned long)_IntegerValue;
}

cValue::operator unsigned short()
{
   return (unsigned short)(unsigned long)_IntegerValue;
}

cValue::operator unsigned int()
{
   return (unsigned int)(unsigned long)_IntegerValue;
}

cValue::operator unsigned long()
{
   return (unsigned long)_IntegerValue;
}

cValue::operator float()
{
   return (float)_RealValue;
}

cValue::operator double()
{
   return (double)_RealValue;
}

cValue::operator const char *()
{
   return (const char*)(_Buffer->buffer);
}

cValue::operator const wide_char *()
{
   return (const wide_char*)(_Buffer->buffer);
}

cValue::operator const void *()
{
   return (void*)(_Buffer->buffer);
}

/// other public methods
const char * cValue::String()
{
   return (const char*)_Buffer;
}

const wide_char * cValue::WideString()
{
   return (const wide_char*)_Buffer;
}



/// protected methods

void cValue::Initialize()
{
   _Type = nil;
   _Size = 0;
   _IntegerValue = 0;
   _RealValue = 0;
   _Buffer = NULL;
}

void cValue::Copy(void * destination, const void * source, unsigned long size)
{
   memcpy(destination, source, size);
}

void cValue::Clone(const cValue & right)
{
   _Type = right._Type;
   _Size = right._Size;
   switch (_Type) {
   case integer:
      _IntegerValue = right._IntegerValue;
      break;
   case real:
      _RealValue = right._RealValue;
      break;
   case string:
      A_INCREMENT(right._Buffer->ref_count);
      FreeResources();
      _Buffer = right._Buffer;
      break;
   case wide_string:
      A_INCREMENT(right._Buffer->ref_count);
      FreeResources();
      _Buffer = right._Buffer;
      break;
   case byte:
      A_INCREMENT(right._Buffer->ref_count);
      FreeResources();
      _Buffer = right._Buffer;
      break;
   }
}

void cValue::FreeResources()
{
   if (_Buffer != NULL) {
      int ref_count = A_DECREMENT(_Buffer->ref_count);
      if (ref_count == 0) {
         FreeBuffer(_Buffer);
         _Buffer = NULL;
      }
   }
}

BUFFER_T * cValue::AllocBuffer(unsigned long size)
{
   _Allocations++;
   BUFFER_T * buffer = (BUFFER_T*)calloc(1, sizeof(*buffer));
   A_SET(buffer->ref_count,1);
   buffer->buffer = (void*)calloc(1, size);
   buffer->size = size;
   return buffer;
}

void cValue::FreeBuffer(BUFFER_T * buffer)
{
   _Allocations--;
   free(buffer->buffer);
   free(buffer);
}

#ifdef TEST_ONLY

#define ARRAY_SIZE 10000
static cValue * v_vec[ARRAY_SIZE] = {0};
void TestValues()
{
   cValue v1(50);
   cValue v2(50.33);
   cValue v3("hallo is bins");
   int i = 0;
   for (i=0; i<ARRAY_SIZE; i++) {
      char name[0x100] = {0};
      SafePrintf(name, sizeof(name), "string_%d", i);
      v_vec[i] = new cValue(name);
      SafePrintf(name, sizeof(name), "string_2_%d", i);
      *v_vec[i] = cValue(name);
      *v_vec[i] = cValue(name);
      const char * s = *(v_vec[i]);
      *(v_vec[i]) = name;
      *(v_vec[i]) = name;
      s = *(v_vec[i]);
   }
   printf("allocated %d\n", cValue::Allocations());
   for (i=0; i<ARRAY_SIZE; i++) {
      const char * s = *(v_vec[i]);
      cValue v = *(v_vec[i]);
      printf("%s\n", s);
      delete(v_vec[i]);
   }
   cValue value;
   int len = 5;
   if (len < (int)value) {
      value = 88;
   }
   unsigned long ulen = 5;
   if (ulen < (unsigned long)value) {
      value = 88;
   }
   if (ulen < (long)value) {
      value = 88;
   }
   if (ulen < (double)value) {
      value = 88;
   }
   v1 = "heinz";
   v1 = v3;
   int n = v1;
   const char * s = v1;
}

#endif

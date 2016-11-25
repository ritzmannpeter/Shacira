
#include "cValue.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "string"

void TestValues()
{
   cValue v1(50);
   cValue v2(50.33);
   cValue v3("hallo is bins");
   cValue * v_vec[10000] = {0};
   int i = 0;
   for (i=0; i<10000; i++) {
      char name[0x100] = {0};
      sprintf(name, "string_%d", i);
      v_vec[i] = new cValue(name);
      int j = 0;
      for (j=i; j>=0; j--) {
         *v_vec[j] = *v_vec[i];
      }
   }
   for (i=0; i<10000; i++) {
      const char * s = *(v_vec[i]);
      printf("%s\n", s);
      delete(v_vec[i]);
   }
   v1 = "heinz";
   v1 = v3;
   int n = v1;
   const char * s = v1;

}

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
   Clone(*this, right);
}

cValue::cValue(const char * v)
{
   Initialize();
   _Size = strlen(v);
   _Type = string;
   _Buffer = (const void*)Alloc(_Size + 1);
   Copy((void*)_Buffer, v, _Size);
}

cValue::cValue(const wide_char * v)
{
   Initialize();
   _Size = wstrlen(v) * sizeof(wide_char);
   _Type = wide_string;
   _Buffer = (const void*)Alloc(_Size + sizeof(wide_char));
   Copy((void*)_Buffer, v, _Size);
}

cValue::cValue(const void * v, unsigned long size)
{
   Initialize();
   _Type = byte;
   _Size = size;
   _Buffer = (const void*)Alloc(_Size);
   Copy((void*)_Buffer, v, _Size);
}

/// destructor
cValue::~cValue()
{
   int ref_count = A_DECREMENT(_RefCount);
   if (ref_count == 0) {
      FreeResources();
   }
}

/// assignment operator
cValue cValue::operator =(const cValue & right)
{
   Clone(*this, right);
   return *this;
}

/// type operators
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
   return (unsigned char)_UIntegerValue;
}

cValue::operator unsigned short()
{
   return (unsigned short)_UIntegerValue;
}

cValue::operator unsigned int()
{
   return (unsigned int)_UIntegerValue;
}

cValue::operator unsigned long()
{
   return (unsigned long)_UIntegerValue;
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
   return (const char*)_Buffer;
}

cValue::operator const wide_char *()
{
   return (const wide_char*)_Buffer;
}

cValue::operator const void *()
{
   return (void*)_Buffer;
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
   A_SET(_RefCount, 1);
   _Type = nil;
   _Size = 0;
   _IntegerValue = 0;
   _UIntegerValue = 0;
   _RealValue = 0;
   _Buffer = NULL;
}

void cValue::Copy(void * destination, const void * source, unsigned long size)
{
   memcpy(destination, source, size);
}

void * cValue::Alloc(unsigned long size)
{
   _Allocations++;
   return calloc(1, size);
}

void cValue::Free(void * mem)
{
   _Allocations--;
   free(mem);
}

void cValue::Clone(cValue & left, const cValue & right)
{
   A_INCREMENT(_RefCount);
   left._Type = right._Type;
   left._Size = right._Size;
   switch (_Type) {
   case integer:
      left._IntegerValue = right._IntegerValue;
      break;
   case uinteger:
      left._UIntegerValue = right._UIntegerValue;
      break;
   case real:
      left._RealValue = right._RealValue;
      break;
   case string:
      left._Buffer = right._Buffer;
      break;
   case wide_string:
      left._Buffer = right._Buffer;
      break;
   case byte:
      left._Buffer = right._Buffer;
      break;
   }
}

void cValue::FreeResources()
{
   if (_Buffer != NULL) {
      Free((void*)_Buffer);
   }
}


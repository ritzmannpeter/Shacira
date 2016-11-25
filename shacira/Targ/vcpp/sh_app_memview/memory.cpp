
#include "memory.h"

#define MEM_SIZE  0x2000

Memory::Memory()
{
   _Changed = false;
   _SharedMemory = NULL;
   _Memory = NULL;
   _Address = 0;
   _AddressWidth = 1;
}

Memory::~Memory()
{
}

void Memory::SetMemoryName(CONST_STRING_T memory_name)
{
   if (strcmp(memory_name, _MemoryName.c_str())) {
      if (_SharedMemory != NULL) {
         delete _SharedMemory;
         _SharedMemory = NULL;
         _Memory = NULL;
         _MemoryName = "";
      }
//      _SharedMemory = new cSharedMem(memory_name, cSharedMem::memOpenOrCreate, MEM_SIZE);
      try {
         _SharedMemory = new cSharedMem(memory_name, cSharedMem::memOpen, MEM_SIZE);
      } catch (...) {
         return;
      }
      _Memory = _SharedMemory->getAdr();
      _MemoryName = memory_name;
      _Changed = true;
   }
}

void Memory::SetAddress(ULONG_T address)
{
   if (_Address != address) {
      _Address = address;
      _Changed = true;
   }
}

void Memory::SetAddressWidth(UCHAR_T width)
{
   if (width == 1 ||
       width == 2 ||
       width == 4) {
      if (_AddressWidth != width) {
         _Changed = true;
         _AddressWidth = width;
      }
   }
}

STRING_T Memory::GetMemoryName()
{
   return _MemoryName;
}

void * Memory::GetMemory()
{
   return _Memory;
}

ULONG_T Memory::GetValue(ULONG_T address)
{
   try {
      UCHAR_T * cptr = NULL;
      USHORT_T * sptr = NULL;
      ULONG_T * lptr = NULL;
      if (_Memory == NULL) return -1;
      int i = address + _Address;
      switch (_AddressWidth) {
      case 1: 
         cptr = &(((UCHAR_T*)_Memory)[i]);
         return *cptr;
      case 2: 
         sptr = &(((USHORT_T*)_Memory)[i]);
         return *sptr;
      case 4: 
         lptr = &(((ULONG_T*)_Memory)[i]);
         return *lptr;
      }
      return 0;
   } catch (...) {
      return 0xaaaaaaaa;
   }
}

void Memory::SetValue(ULONG_T address, ULONG_T value)
{
   try {
      UCHAR_T * cptr = NULL;
      USHORT_T * sptr = NULL;
      ULONG_T * lptr = NULL;
      if (_Memory == NULL) {
         return;
      }
//      int i = address + _Address;
      int i = address;
      switch (_AddressWidth) {
      case 1: 
         cptr = &(((UCHAR_T*)_Memory)[i]);
         *cptr = (UCHAR_T)value;
         break;
      case 2: 
         sptr = &(((USHORT_T*)_Memory)[i]);
         *sptr = (USHORT_T)value;
         break;
      case 4: 
         lptr = &(((ULONG_T*)_Memory)[i]);
         *lptr = value;
         break;
      }
      return;
   } catch (...) {
      return;
   }
}

UCHAR_T Memory::GetAddressWidth()
{
   return _AddressWidth;
}

ULONG_T Memory::GetAddress()
{
   return _Address;
}

BOOL_T Memory::Changed()
{
   if (_Changed) {
      _Changed = false;
      return true;
   } else {
      return false;
   }
}


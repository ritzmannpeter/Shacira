
#ifndef MEMORY_H
#define MEMORY_H

#include "FirstHeader.h"
#include "base/eb_shmem.hpp"

class Memory
{
public:
   Memory();
   virtual ~Memory();
public:
   void SetMemoryName(CONST_STRING_T memory_name);
   void SetAddress(ULONG_T address);
   void SetAddressWidth(UCHAR_T width);
   STRING_T GetMemoryName();
   void * GetMemory();
   ULONG_T GetValue(ULONG_T address);
   void SetValue(ULONG_T address, ULONG_T value);
   UCHAR_T GetAddressWidth();
   ULONG_T GetAddress();
   BOOL_T Changed();
private:
   BOOL_T _Changed;
   STRING_T _MemoryName;
   cSharedMem * _SharedMemory;
   void * _Memory;
   ULONG_T _Address;
   UCHAR_T _AddressWidth;
};

#endif // MEMORY_H

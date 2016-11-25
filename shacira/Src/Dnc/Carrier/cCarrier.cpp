//## begin module%3B97BB680370.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B97BB680370.cm

//## begin module%3B97BB680370.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B97BB680370.cp

//## Module: cCarrier%3B97BB680370; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\Carrier\cCarrier.cpp

//## begin module%3B97BB680370.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B97BB680370.additionalIncludes

//## begin module%3B97BB680370.includes preserve=yes

#include "Dnc/CarItf/CarItf.h"

//## end module%3B97BB680370.includes

// cCarrier
#include "Dnc/Carrier/cCarrier.h"
//## begin module%3B97BB680370.additionalDeclarations preserve=yes

class cTimeDiff {
private:
   STRING_T _Function;
   DWORD _Time;
public:
   cTimeDiff(CONST_STRING_T function);
   virtual ~cTimeDiff();
};

cTimeDiff::cTimeDiff(CONST_STRING_T function)
{
   _Function = function;
   _Time = GetTickCount();
}

cTimeDiff::~cTimeDiff()
{
   DWORD time = GetTickCount();
   DWORD diff = time - _Time;
   printf("%s %d ticks\n", _Function.c_str(), diff);
}

#ifdef __cplusplus
extern "C" {
#endif

static cCarrier * _Carrier = NULL;
static void InstantiateCarrier()
{
   if (_Carrier == NULL) {
      _Carrier = new cCarrier;
   }
}

int BASIC_Check()
{
   try {
      InstantiateCarrier();
      int size = _Carrier->Size();
      return size;
   } catch (cError & e) {
      return e.get_ErrCode();
   } catch (...) {
      return CARRIER_UNHANDLED_EXCEPTION;
   }
}

int BASIC_Read(long address, long size, void * buffer)
{
   try {
      InstantiateCarrier();
      int nread = _Carrier->Read(address, (unsigned char *)buffer, 10000, size);
      if (nread == size) {
         return 0;
      } else {
         return nread;
      }
   } catch (cError & e) {
      return e.get_ErrCode();
   } catch (...) {
      return CARRIER_UNHANDLED_EXCEPTION;
   }
}

int BASIC_Write(long address, long size, void * buffer)
{
   try {
      InstantiateCarrier();
      int nwrite = _Carrier->Write(address, (unsigned char *)buffer, size);
      if (nwrite == size) {
         return 0;
      } else {
         return nwrite;
      }
   } catch (cError & e) {
      return e.get_ErrCode();
   } catch (...) {
      return CARRIER_UNHANDLED_EXCEPTION;
   }
}


#ifdef __cplusplus
}
#endif

//## end module%3B97BB680370.additionalDeclarations


// Class cCarrier 




cCarrier::cCarrier()
  //## begin cCarrier::cCarrier%.hasinit preserve=no
  //## end cCarrier::cCarrier%.hasinit
  //## begin cCarrier::cCarrier%.initialization preserve=yes
  //## end cCarrier::cCarrier%.initialization
{
  //## begin cCarrier::cCarrier%.body preserve=yes
   _Handle = CARITF_Open();
   _Carrier = this;
  //## end cCarrier::cCarrier%.body
}

cCarrier::cCarrier(const cCarrier &right)
  //## begin cCarrier::cCarrier%copy.hasinit preserve=no
  //## end cCarrier::cCarrier%copy.hasinit
  //## begin cCarrier::cCarrier%copy.initialization preserve=yes
  //## end cCarrier::cCarrier%copy.initialization
{
  //## begin cCarrier::cCarrier%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCarrier::cCarrier%copy.body
}

cCarrier::cCarrier (CONST_STRING_T name)
  //## begin cCarrier::cCarrier%999800100.hasinit preserve=no
  //## end cCarrier::cCarrier%999800100.hasinit
  //## begin cCarrier::cCarrier%999800100.initialization preserve=yes
  //## end cCarrier::cCarrier%999800100.initialization
{
  //## begin cCarrier::cCarrier%999800100.body preserve=yes
   _Handle = CARITF_Open();
   _Carrier = this;
  //## end cCarrier::cCarrier%999800100.body
}


cCarrier::~cCarrier()
{
  //## begin cCarrier::~cCarrier%.body preserve=yes
   if (_Handle != INVALID_HANDLE) CloseHandle(_Handle);
   _Carrier = NULL;
  //## end cCarrier::~cCarrier%.body
}



//## Other Operations (implementation)
LONG_T cCarrier::Read (ULONG_T address, UCHAR_T *buf, ULONG_T buf_size, LONG_T amount)
{
  //## begin cCarrier::Read%999800097.body preserve=yes
CHECK_CARRIER_HANDLE
cTimeDiff time("Read");
   return CARITF_Read(_Handle, address, buf, buf_size, amount);
  //## end cCarrier::Read%999800097.body
}

LONG_T cCarrier::Write (ULONG_T address, UCHAR_T *buf, LONG_T amount)
{
  //## begin cCarrier::Write%999800098.body preserve=yes
CHECK_CARRIER_HANDLE
   return CARITF_Write(_Handle, address, buf, amount);
  //## end cCarrier::Write%999800098.body
}

LONG_T cCarrier::Size ()
{
  //## begin cCarrier::Size%999800099.body preserve=yes
CHECK_CARRIER_HANDLE
cTimeDiff time("Check");
   return CARITF_Check(_Handle);
  //## end cCarrier::Size%999800099.body
}

// Additional Declarations
  //## begin cCarrier%3B97BB680370.declarations preserve=yes
  //## end cCarrier%3B97BB680370.declarations

//## begin module%3B97BB680370.epilog preserve=yes
//## end module%3B97BB680370.epilog

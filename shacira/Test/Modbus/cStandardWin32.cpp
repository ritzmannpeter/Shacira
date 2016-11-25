/*.sm.***********************************************************************
*
*  MODULE-NAME:
*     cStandardWin32.cpp - This Module covers a wrapper for the access functionality
* 								   to win32 serial I/O-functions.
*
*  BESCHREIBUNG:
*
*  UMGEBUNG:
*     ZIELRECHNER:
*     ENTWICKLUNGSRECHNER:
*     UEBERSETZER:
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   09.09.99
*     AUTOR(EN):  -PR-  Peter Ritzmann      TELEFON: 07621/45205-0
*
*  HISTORY:
*     09.09.99  -PR-  First implementation based on C-module stdw32.c
*
*  BEMERKUNGEN:
*     ...
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*  DATENTYPEN:
*
*  VARIABLEN:
*
*.EM.***********************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "cStandardWin32.h"

// dst (destination addresses the WIN32 device, src (source) addresses the
// view of the module user

static unsigned char SrcStopBits(unsigned char dst_stopbits)
{
   switch(dst_stopbits) {
   case ONESTOPBIT: return 1;
   case TWOSTOPBITS: return 2;
   default: return 1;
   }
}

static unsigned char DstStopBits(unsigned char src_stopbits)
{
   switch (src_stopbits) {
   case 1: return ONESTOPBIT;
   case 2: return TWOSTOPBITS;
   default: return ONESTOPBIT;
   }
}

static short SrcStartBits(unsigned char dst_startbits)
{
   // not covered by the WIN32 API
   return dst_startbits;
}

static short DstStartBits(unsigned char src_startbits)
{
   // not covered by the WIN32 API
   return src_startbits;
}

static ParityTypes SrcParity(unsigned char dst_parity)
{
   switch (dst_parity) {
   case NOPARITY: return None;
   case ODDPARITY: return Odd;
   case EVENPARITY: return Even;
   case MARKPARITY: return Mark;
   case SPACEPARITY: return Space;
   default: return None;
   }
}

static unsigned char DstParity(ParityTypes src_parity)
{
   switch (src_parity) {
   case None: return NOPARITY;
   case Odd: return ODDPARITY;
   case Even: return EVENPARITY;
   case Mark: return MARKPARITY;
   case Space: return SPACEPARITY;
   default: return NOPARITY;
   }
}


cStandardBase::cStandardBase()
  //## begin cStandardBase::cStandardBase%.hasinit preserve=no
  //## end cStandardBase::cStandardBase%.hasinit
  //## begin cStandardBase::cStandardBase%.initialization preserve=yes
  //## end cStandardBase::cStandardBase%.initialization
{
  //## begin cStandardBase::cStandardBase%.body preserve=yes
   memset(_PortName, 0, sizeof(_PortName));
   _PortHandle = NULL;
  //## end cStandardBase::cStandardBase%.body
}

cStandardBase::~cStandardBase()
{
  //## begin cStandardBase::~cStandardBase%.body preserve=yes
   Close();
  //## end cStandardBase::~cStandardBase%.body
}

void cStandardBase::Open()
{
   if (_PortName[0] == '\0') {
      printf("no port name specified\n");
      exit(-1);
   }
   Close();

   HANDLE handle;
   DCB dcb = {0};
   char port_name[32] = {0};
   sprintf(port_name, "\\\\.\\%s", _PortName);
   if ((handle = CreateFile(port_name,
                            GENERIC_WRITE | GENERIC_READ,
                            0, NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL)) != INVALID_HANDLE_VALUE) {
      int rc;
      if ((rc = InitDevice(handle)) == 0) {
         _PortHandle = handle;
      } else {
         CloseHandle(handle);
         printf("failed to initialize device %s\n", port_name);
         exit(-1);
      }
   } else {
      printf("failed to open device %s\n", port_name);
      exit(-1);
   }
}

void cStandardBase::Close()
{
   if (_PortHandle != NULL) {
      FlushInput();
      FlushOutput();
      HANDLE handle = _PortHandle;
      _PortHandle = NULL;
      CloseHandle(handle);
   }
}

#define _CHECK_COM_HANDLE__(port_name) \
if (_PortHandle == NULL) { \
   printf("invalid handle for port %s\n", port_name); \
   exit(-1); \
}

unsigned long cStandardBase::Read(void * buf, unsigned long amount,
                                  unsigned long timeout)
{
_CHECK_COM_HANDLE__(_PortName)
   unsigned long nread;
   COMMTIMEOUTS timeouts = {0};
   timeouts.ReadIntervalTimeout = 0;
   timeouts.ReadTotalTimeoutMultiplier = 0;
   timeouts.ReadTotalTimeoutConstant = timeout;
   if (SetCommTimeouts(_PortHandle, &timeouts)) {
      if (ReadFile(_PortHandle, buf, amount, &nread, NULL) == 0) {
         printf("failed to read on device %s\n", _PortName);
         exit(-1);
      }
      return nread;
   } else {
      printf("failed to set comm params on device %s\n", _PortName);
      exit(-1);
   }
   return 0;
}

unsigned long cStandardBase::Write(const void * buf, unsigned long amount)
{
_CHECK_COM_HANDLE__(_PortName)
   unsigned long nwrite;
   if (WriteFile(_PortHandle, buf, amount, &nwrite, NULL) == 0) {
      printf("failed to write on device %s\n", _PortName);
      exit(-1);
   }
   return nwrite;
}

void cStandardBase::FlushInput()
{
_CHECK_COM_HANDLE__(_PortName)
   PurgeComm(_PortHandle, PURGE_RXCLEAR);
}

void cStandardBase::FlushOutput()
{
_CHECK_COM_HANDLE__(_PortName)
   PurgeComm(_PortHandle, PURGE_TXCLEAR);
}

void cStandardBase::SetBaudRate(unsigned long baud_rate)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to set baudrate on device %s\n", _PortName);
      exit(-1);
   } else {
      dcb.BaudRate = baud_rate;
      if (!SetCommState(_PortHandle, &dcb)) {
         printf("failed to set baudrate on device %s\n", _PortName);
         exit(-1);
      }
   }
}

unsigned long cStandardBase::GetBaudRate()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get baudrate on device %s\n", _PortName);
      exit(-1);
   } else {
      return dcb.BaudRate;
   }
   return 0;
}

void cStandardBase::SetCharLen(unsigned char char_length)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      dcb.ByteSize = (unsigned char)char_length;
      if (!SetCommState(_PortHandle, &dcb)) {
         printf("failed to set comm state on device %s\n", _PortName);
         exit(-1);
      }
   }
}

unsigned char cStandardBase::GetCharLen()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      return dcb.ByteSize;
   }
   return 0;
}

void cStandardBase::SetStartBits(unsigned char start_bits)
{
}

unsigned char cStandardBase::GetStartBits()
{
   return 1;
}

void cStandardBase::SetStopBits(unsigned char stop_bits)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      dcb.StopBits = DstStopBits(stop_bits);
      if (!SetCommState(_PortHandle, &dcb)) {
         printf("failed to set comm state on device %s\n", _PortName);
         exit(-1);
      }
   }
}

unsigned char cStandardBase::GetStopBits()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      return SrcStopBits(dcb.StopBits);
   }
   return 0;
}

void cStandardBase::SetParity(ParityTypes parity)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      dcb.Parity = DstParity(parity);
      if (!SetCommState(_PortHandle, &dcb)) {
         printf("failed to set comm state on device %s\n", _PortName);
         exit(-1);
      }
   }
}

ParityTypes cStandardBase::GetParity()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
      return SrcParity(dcb.Parity);
   }
#ifdef __MSCPP__
   return UndefinedParity;
#endif
}

void cStandardBase::SetHandshake(HandshakeTypes handshake)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
// must be done
   }
}

HandshakeTypes cStandardBase::GetHandshake()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      printf("failed to get comm state on device %s\n", _PortName);
      exit(-1);
   } else {
// must be done
      return NoHandshake;
   }
#ifdef __MSCPP__
   return NoHandshake;
#endif
}

void cStandardBase::SetTimeout(unsigned long timeout)
{
_CHECK_COM_HANDLE__(_PortName)
   COMMTIMEOUTS timeouts = {0};
   timeouts.ReadIntervalTimeout = 0;
   timeouts.ReadTotalTimeoutMultiplier = 0;
   timeouts.ReadTotalTimeoutConstant = timeout;
   if (!SetCommTimeouts(_PortHandle, &timeouts)) {
      printf("failed to set comm timeouts on device %s\n", _PortName);
      exit(-1);
   }
}

unsigned long cStandardBase::GetTimeout()
{
_CHECK_COM_HANDLE__(_PortName)
   COMMTIMEOUTS timeouts = {0};
   if (GetCommTimeouts(_PortHandle, &timeouts)) {
      return timeouts.ReadTotalTimeoutConstant;
   } else {
      printf("failed to get comm timeouts on device %s\n", _PortName);
      exit(-1);
   }
#ifdef __MSCPP__
   return 0;
#endif
}

void cStandardBase::ResetDevice()
{
}

const char * cStandardBase::GetPortName()
{
   return _PortName;
}

void cStandardBase::SetPortName(const char * name)
{
   if (strlen(name) < sizeof(_PortName)) {
      sprintf(_PortName, "%s", name);
   } else {
      printf("port name %s too long\n", name);
      exit(-1);
   }
}

int cStandardBase::InitDevice(HANDLE handle)
{
   DCB dcb = {0};
   if (!GetCommState(handle, &dcb)) {
      return GetLastError();
   } else {
      dcb.fOutxCtsFlow = FALSE;
      dcb.fOutxDsrFlow = FALSE;
      dcb.fDtrControl = DTR_CONTROL_DISABLE;
      dcb.fRtsControl = RTS_CONTROL_DISABLE;
      dcb.fOutX  = FALSE;
      dcb.fInX = FALSE;
      dcb.fParity = TRUE;
      if (!SetCommState(handle, &dcb)) {
         return GetLastError();
      } else {
         return 0;
      }
   }
}



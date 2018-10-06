
#if defined(_WIN32)

#include "FirstHeader.h"
#include <stddef.h>
#include <stdio.h>
#include "cStandardBase.h"
#include "System/cError.h"

// dst (destination addresses the _WIN32 device, src (source) addresses the
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
   // not covered by the _WIN32 API
   return dst_startbits;
}

static short DstStartBits(unsigned char src_startbits)
{
   // not covered by the _WIN32 API
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
      throw cError(STDSER_NO_PORT_NAME, 0);
   }
   Close();

   #define MAXRETRIES 3
   #define RETRY_DELAY 800

   BOOL_T success = false;
   int retries = 0;
   int error = 0;
   HANDLE handle;
   DCB dcb = {0};
   char port_name[32] = {0};
   SafePrintf(port_name, sizeof(port_name), "\\\\.\\%s", _PortName);

   do {
      handle = CreateFile(port_name, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if (handle == INVALID_HANDLE_VALUE) {
         error = (int)GetLastError();

         if (error == ERROR_ACCESS_DENIED) {
            retries++;
            Sleep(RETRY_DELAY);
            continue;
         }
         else {
            // An error occurred.
            break;
         }
      }

      success = true;
      break;
   } while (retries < MAXRETRIES);

   if (success) {
      int rc;
      if ((rc = InitDevice(handle)) == 0) {
         _PortHandle = handle;
      } else {
         CloseHandle(handle);
         throw cError(STDSER_SET_COMM_STATE, rc, port_name);
      }
   } else {
     throw cError(STDSER_CREATE_FILE, error, _PortName);
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
   throw cError(STDSER_INVALID_HANDLE, 0, port_name); \
}

unsigned long cStandardBase::Read(void * buf, unsigned long amount,
                                  unsigned long timeout)
{
_CHECK_COM_HANDLE__(_PortName)
   unsigned long nread;
   COMMTIMEOUTS timeouts = {0};
   if (timeout > 0) {
      timeouts.ReadIntervalTimeout = 0;
      timeouts.ReadTotalTimeoutMultiplier = 0;
      timeouts.ReadTotalTimeoutConstant = timeout;
   } else {
      timeouts.ReadIntervalTimeout = MAXDWORD;
      timeouts.ReadTotalTimeoutMultiplier = 0;
      timeouts.ReadTotalTimeoutConstant = timeout;
   }
   if (SetCommTimeouts(_PortHandle, &timeouts)) {
      if (ReadFile(_PortHandle, buf, amount, &nread, NULL) == 0) {
         throw cError(STDSER_READ_FILE, GetLastError(), _PortName);
      }
      return nread;
   } else {
      throw cError(STDSER_SET_COMM_TIMEOUTS, GetLastError(), _PortName);
   }
}

unsigned long cStandardBase::Write(const void * buf, unsigned long amount)
{
_CHECK_COM_HANDLE__(_PortName)
   unsigned long nwrite;
   if (WriteFile(_PortHandle, buf, amount, &nwrite, NULL) == 0) {
      throw cError(STDSER_WRITE_FILE, GetLastError(), _PortName);
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
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      dcb.BaudRate = baud_rate;
      if (!SetCommState(_PortHandle, &dcb)) {
         throw cError(STDSER_SET_COMM_STATE, GetLastError(), _PortName);
      }
   }
}

unsigned long cStandardBase::GetBaudRate()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
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
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      dcb.ByteSize = (unsigned char)char_length;
      if (!SetCommState(_PortHandle, &dcb)) {
         throw cError(STDSER_SET_COMM_STATE, GetLastError(), _PortName);
      }
   }
}

unsigned char cStandardBase::GetCharLen()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      return dcb.ByteSize;
   }
   return 0;
}

void cStandardBase::SetStartBits(unsigned char start_bits)
{
_CHECK_COM_HANDLE__(_PortName)
// not used in win32
}

unsigned char cStandardBase::GetStartBits()
{
_CHECK_COM_HANDLE__(_PortName)
   return 1;
}

void cStandardBase::SetStopBits(unsigned char stop_bits)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      dcb.StopBits = DstStopBits(stop_bits);
      if (!SetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_SET_COMM_STATE, GetLastError(), _PortName);
      }
   }
}

unsigned char cStandardBase::GetStopBits()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      return SrcStopBits(dcb.StopBits);
   }
#ifdef __MSCPP__
   return 0;
#endif
}

void cStandardBase::SetParity(ParityTypes parity)
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
      dcb.Parity = DstParity(parity);
      if (!SetCommState(_PortHandle, &dcb)) {
         throw cError(STDSER_SET_COMM_STATE, GetLastError(), _PortName);
      }
   }
}

ParityTypes cStandardBase::GetParity()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
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
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
   } else {
// must be done
   }
}

HandshakeTypes cStandardBase::GetHandshake()
{
_CHECK_COM_HANDLE__(_PortName)
   DCB dcb = {0};
   if (!GetCommState(_PortHandle, &dcb)) {
      throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
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
      throw cError(STDSER_SET_COMM_TIMEOUTS, GetLastError(), _PortName);
   }
}

unsigned long cStandardBase::GetTimeout()
{
_CHECK_COM_HANDLE__(_PortName)
   COMMTIMEOUTS timeouts = {0};
   if (GetCommTimeouts(_PortHandle, &timeouts)) {
      return timeouts.ReadTotalTimeoutConstant;
   } else {
      throw cError(STDSER_GET_COMM_TIMEOUTS, GetLastError(), _PortName);
   }
#ifdef __MSCPP__
   return 0;
#endif
}

void cStandardBase::GetState(COM_STATE_T * com_state)
{
_CHECK_COM_HANDLE__(_PortName)
   DWORD errors = 0;
   COMSTAT com_stat = {0};
   DCB dcb = {0};
   if (ClearCommError(_PortHandle, &errors, &com_stat)) {
      if (GetCommState(_PortHandle, &dcb)) {
         TranslateState(com_state, errors, &com_stat, &dcb);
      } else {
         throw cError(STDSER_GET_COMM_STATE, GetLastError(), _PortName);
      }
   } else {
      throw cError(STDSER_CLEAR_COMM_ERROR, GetLastError(), _PortName);
   }
}

void cStandardBase::ResetDevice()
{
_CHECK_COM_HANDLE__(_PortName)
   if (InitDevice(_PortHandle) == 0) {
      unsigned long errors = 0;
      if (ClearCommError(_PortHandle, &errors, NULL)) {

      } else {
// ?
      }
   }
}

const char * cStandardBase::GetPortName()
{
   return _PortName;
}

void cStandardBase::SetPortName(const char * name)
{
   if (strlen(name) < sizeof(_PortName)) {
      SafePrintf(_PortName, sizeof(_PortName), "%s", name);
   } else {
      throw cError(STDSER_PORT_NAME_SIZE, 0, name);
   }
}

void cStandardBase::TranslateState(COM_STATE_T * com_state, unsigned long errors,
                                   COMSTAT * com_stat, DCB * dcb)
{
   if (com_state != NULL &&
       com_stat != NULL &&
       dcb != NULL) {
      com_state->errors = errors;
      if (com_stat->fCtsHold) com_state->act_state |= CTS_HOLD;
      if (com_stat->fDsrHold) com_state->act_state |= DSR_HOLD;
      if (com_stat->fRlsdHold) com_state->act_state |= RLSD_HOLD;
      if (com_stat->fXoffHold) com_state->act_state |= XOFF_HOLD;
      if (com_stat->fXoffSent) com_state->act_state |= XOFF_SENT;
      if (com_stat->fEof) com_state->act_state |= EOF_REACHED;
      if (com_stat->fTxim) com_state->act_state |= TXIM;

      if (dcb->fBinary) com_state->set_state |= MODE_BINARY;
      if (dcb->fParity) com_state->set_state |= MODE_PARITY;
      if (dcb->fOutxCtsFlow) com_state->set_state |= MODE_OUTXCTSFLOW;
      if (dcb->fOutxDsrFlow) com_state->set_state |= MODE_OUTXDSRFLOW;
      if (dcb->fDsrSensitivity) com_state->set_state |= MODE_DSRSENSITIVITY;
      if (dcb->fTXContinueOnXoff) com_state->set_state |= MODE_TXCONTINUEONXOFF;
      if (dcb->fOutX) com_state->set_state |= MODE_OUTX;
      if (dcb->fInX) com_state->set_state |= MODE_INX;
      if (dcb->fErrorChar) com_state->set_state |= MODE_ERRORCHAR;
      if (dcb->fNull) com_state->set_state |= MODE_NULL;
      if (dcb->fAbortOnError) com_state->set_state |= MODE_ABORTONERROR;

      com_state->in_queue_size = com_stat->cbInQue;
      com_state->out_queue_size = com_stat->cbOutQue;
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
//      dcb.fDtrControl = DTR_CONTROL_DISABLE;
//      dcb.fRtsControl = RTS_CONTROL_DISABLE;
dcb.fDtrControl = DTR_CONTROL_ENABLE;
dcb.fRtsControl = RTS_CONTROL_ENABLE;
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

#endif






#ifndef __cStandardBase__
#define __cStandardBase__

#include "shacira.h"
#include "Control/SerialChannel/cSerialChannel.h"

#ifdef _WIN32
#include <windows.h>
#endif

class cStandardBase {
public:
   cStandardBase();
   ~cStandardBase();
   void Open();
   void Close();
   unsigned long Read(void * buf, unsigned long amount, unsigned long timeout);
   unsigned long Write(const void * buf, unsigned long amount);
   void FlushInput();
   void FlushOutput();
   void SetBaudRate(unsigned long baud_rate);
   unsigned long GetBaudRate();
   void SetCharLen(unsigned char char_length);
   unsigned char GetCharLen();
   void SetStartBits(unsigned char start_bits);
   unsigned char GetStartBits();
   void SetStopBits(unsigned char stop_bits);
   unsigned char GetStopBits();
   void SetParity(ParityTypes parity);
   ParityTypes GetParity();
   void SetHandshake(HandshakeTypes handshake);
   HandshakeTypes GetHandshake();
   void SetTimeout(unsigned long timeout);
   unsigned long GetTimeout();
   void GetState(COM_STATE_T * com_state);
   const char * GetPortName();
   void SetPortName(const char * name);
   void ResetDevice();
private:
   char _PortName[0x200];
#if defined(_WIN32)
   HANDLE _PortHandle;
   int InitDevice(HANDLE handle);
   void TranslateState(COM_STATE_T * com_state, unsigned long errors,
                       COMSTAT * com_stat, DCB * dcb);
#endif
#if defined(__linux__)
   int _Handle;
#define INDEFINITE   -1
   long _ReadTimeout;
   CONST_STRING_T _TTYName;
   CONST_STRING_T TTYName(CONST_STRING_T port_name);
   void SetReadTimeout(long timeout);
   void InitializeDevice();
   void InitializeAttributes();
#endif
};


#endif



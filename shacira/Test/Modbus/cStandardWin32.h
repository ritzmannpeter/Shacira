
#ifndef __cStandardBase__
#define __cStandardBase__

#ifdef __WIN32__
#include <windows.h>
#endif

typedef enum {UndefinedParity=-1,Even, Odd, Mark, Space, None} ParityTypes;
typedef enum {UndefinedDirection=-1,Input, Output} DirectionTypes;
typedef enum {UndefinedHandshake=-1,NoHandshake=0,InputSW=0x01,InputHW=0x02,
              OutputSW=0x04,OutputHW=0x08} HandshakeTypes;

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
   const char * GetPortName();
   void SetPortName(const char * name);
   void ResetDevice();
private:
   char _PortName[128];
   HANDLE _PortHandle;
   int InitDevice(HANDLE handle);
};

#endif



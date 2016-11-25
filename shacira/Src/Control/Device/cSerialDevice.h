//	Copyright © 2002 - 2007 by
//	2i Industrial Informatics GmbH

#ifndef cSerialDevice_h
#define cSerialDevice_h 1

#include "Control/Device/cDevice.h"

#define DIR_INPUT     0
#define DIR_OUTPUT    1

typedef struct _test_params
{
   ULONG_T baud_rate;
   ParityTypes parity;
   UCHAR_T char_len;
   UCHAR_T stop_bits;
}  TEST_PARAMS_T;

class __DLL_EXPORT__ cSerialDevice : public cDevice
{
public:
   cSerialDevice();
   cSerialDevice(cConfigurationObject *config_obj, cCell *cell);
   virtual ~cSerialDevice();
   inline ULONG_T GetBaudRate()
   {
      if (_SerialChannel == NULL) {
         return 0;
      } else {
         return _SerialChannel->GetBaudRate();
      }
   };
   inline void SetBaudRate(ULONG_T baud_rate)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetBaudRate(baud_rate);
      }
   };
   inline UCHAR_T GetStopBits()
   {
      if (_SerialChannel == NULL) {
         return 0;
      } else {
         return _SerialChannel->GetStopBits();
      }
   };
   inline void SetStopBits(UCHAR_T stop_bits)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetStopBits(stop_bits);
      }
   };
   inline UCHAR_T GetStartBits()
   {
      if (_SerialChannel == NULL) {
         return 0;
      } else {
         return _SerialChannel->GetStartBits();
      }
   };
   inline void SetStartBits(UCHAR_T start_bits)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetStartBits(start_bits);
      }
   };
   inline UCHAR_T GetCharLen()
   {
      if (_SerialChannel == NULL) {
         return 0;
      } else {
         return _SerialChannel->GetCharLen();
      }
   };
   inline void SetCharLen(UCHAR_T data_len)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetCharLen(data_len);
      }
   };
   inline ParityTypes GetParity()
   {
      if (_SerialChannel == NULL) {
         return None;
      } else {
         return _SerialChannel->GetParity();
      }
   };
   inline void SetParity(ParityTypes parity)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetParity(parity);
      }
   };
   inline HandshakeTypes GetHandshake()
   {
      if (_SerialChannel == NULL) {
         return NoHandshake;
      } else {
         return _SerialChannel->GetHandshake();
      }
   };
   inline void SetHandshake(HandshakeTypes handshake)
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->SetHandshake(handshake);
      }
   };
   inline LONG_T Read(UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout)
   {
      if (_SerialChannel == NULL) {
         return -1;
      } else {
         LONG_T rc = _SerialChannel->Read(buffer, amount, timeout);
         if ((bool)Parameter("Verbose") == true) {
            if (rc > 0) {
               PrintBuf((const char*)buffer, rc, DIR_INPUT);
            }
         }
         return rc;
      }
   };
   inline LONG_T Write(UCHAR_T *buffer, ULONG_T amount)
   {
      if (_SerialChannel == NULL) {
         return -1;
      } else {
         if ((bool)Parameter("Verbose") == true) {
            PrintBuf((const char*)buffer, amount, DIR_OUTPUT);
         }
         return _SerialChannel->Write(buffer, amount);
      }
   };
   inline void FlushInput()
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->FlushInput();
      }
   };
   inline void FlushOutput()
   {
      if (_SerialChannel == NULL) {
         return;
      } else {
         _SerialChannel->FlushOutput();
      }
   };
   inline BOOL_T SendChar(UCHAR_T c)
   {
      if (_SerialChannel == NULL) {
         return false;
      } else {
         if ((bool)Parameter("Verbose") == true) {
            char buf[2] = {0};
            buf[0] = c;
            PrintBuf((const char*)buf, 1, DIR_OUTPUT);
         }
         return _SerialChannel->SendChar(c);
      }
   };
   inline INT_T GetChar(ULONG_T timeout)
   {
      if (_SerialChannel == NULL) {
         return EOF;
      } else {
         INT_T c = _SerialChannel->GetChar(timeout);
         if (c != EOF) {
            if ((bool)Parameter("Verbose") == true) {
               char buf[2] = {0};
               buf[0] = c;
               PrintBuf((const char*)buf, 1, DIR_INPUT);
            }
         }
         return c;
      }
   };

protected:
   cSerialChannel * _SerialChannel;
   cMutexSem _SerialChannelMutex;
   TEST_PARAMS_T _TestParams;
protected:
   BOOL_T InitializeInterface();
   BOOL_T FreeInterface();
private:
   void PrintBuf (CONST_STRING_T buf, ULONG_T len, INT_T direction);
   void SetDirection(INT_T direction);
   STRING_T Format(CONST_STRING_T buf, ULONG_T len);
private:
   int _ActDirection;
};

#endif

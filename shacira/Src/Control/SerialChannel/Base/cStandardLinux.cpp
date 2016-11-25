
#ifdef __linux__

#include "FirstHeader.h"
#include <stddef.h>
#include <stdio.h>
#include "cStandardBase.h"
#include "System/cError.h"
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#define INVALID_HANDLE     -1
#define NO_DEBUG

static void inline PrintBuffer(int dir, const char * buf, unsigned long len)
{
#ifdef NO_DEBUG
   return;
#endif
static int direction = 2;
   if (direction != dir) {
      if (dir == 0) {
         printf("\n<-- ");
      } else {
         printf("\n--> ");
      }
      direction = dir;
   }
   unsigned long i = 0;
   for (i=0; i<len; i++) {
      char c = buf[i];
      if (isprint(c)) {
         printf("%c", c);
      } else {
         printf("[%d]", (int)c);
      }
   }
}

static unsigned short ParityCtrl(ParityTypes parity)
{
   switch (parity) {
   case None: return 0x0000;
   case Odd: return PARENB|PARODD;
   case Even: return PARENB;
   default: return 0x0000;
   }
}

ParityTypes Parity(tcflag_t ctrl)
{
   return None;
PORT_LEVEL_5
#ifdef mapdoc
   switch (ctrl) {
   case None: return 0x0000;
   case Odd: return PARENB|PARODD;
   case Even: return PARENB;
   default: return 0x0000;
   }
#endif
}

static unsigned short StopbitCtrl(unsigned char stopbits)
{
   switch (stopbits) {
   case 0: return 0x0000;
   case 1: return 0x0000;
   case 2: return CSTOPB;
   default: return 0x0000;
   }
}

static unsigned char Stopbit(tcflag_t ctrl)
{
   return 1;
PORT_LEVEL_5
#ifdef mapdoc
   switch (ctrl) {
   case 0: return 0x0000;
   case 1: return 0x0000;
   case 2: return CSTOPB;
   default: return 0x0000;
   }
#endif
}

static unsigned short CharlenCtrl(unsigned char charlen)
{
   switch (charlen) {
   case 5: return CS5;
   case 6: return CS6;
   case 7: return CS7;
   case 8: return CS8;
   default: return CS8;
   }
}

static unsigned char Charlen(tcflag_t ctrl)
{
   return 8;
PORT_LEVEL_5
#ifdef mapdoc
   switch (ctrl) {
   case 5: return CS5;
   case 6: return CS6;
   case 7: return CS7;
   case 8: return CS8;
   default: return CS8;
   }
#endif
}

static speed_t BaudrateCtrl(unsigned long baud)
{
   switch (baud) {
   case 1200:   return B1200;
   case 2400:   return B2400;
   case 4800:   return B4800;
   case 9600:   return B9600;
   case 19200:  return B19200;
   case 38400:  return B38400;
   case 57600:  return B57600;
   case 115200: return B115200;
   default:     return B9600;
   }
}

static unsigned long Baudrate(speed_t baudrate_ctrl)
{
   switch (baudrate_ctrl) {
   case B1200:   return 1200;
   case B2400:   return 2400;
   case B4800:   return 4800;
   case B9600:   return 9600;
   case B19200:  return 19200;
   case B38400:  return 38400;
   case B57600:  return 57600;
   case B115200: return 115200;
   default:     return 9600;
   }
}

cStandardBase::cStandardBase()
  //## begin cStandardBase::cStandardBase%.hasinit preserve=no
  //## end cStandardBase::cStandardBase%.hasinit
  //## begin cStandardBase::cStandardBase%.initialization preserve=yes
  //## end cStandardBase::cStandardBase%.initialization
{
  //## begin cStandardBase::cStandardBase%.body preserve=yes
   _Handle = INVALID_HANDLE;
   _ReadTimeout = INDEFINITE;
   memset(_PortName, 0, sizeof(_PortName));
   _TTYName = "no tty";
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
//InfoPrintf("open %s\n", _TTYName);
   InitializeDevice();
   _Handle = open(_TTYName, O_RDWR);
   if (_Handle != INVALID_HANDLE) {
      InitializeAttributes();
   } else {
      int err = errno;
      ErrorPrintf("error open %s: %d\n", _PortName, err);
      throw cError(STDSER_CREATE_FILE, err, _PortName);
   }
}

void cStandardBase::Close()
{
   if (_Handle != INVALID_HANDLE) {
      close(_Handle);
   }
}

#define _CHECK_COM_HANDLE__(port_name) \
if (_Handle == INVALID_HANDLE) { \
   throw cError(STDSER_INVALID_HANDLE, 0, port_name); \
}

unsigned long cStandardBase::Read(void * buf, unsigned long amount,
                                  unsigned long timeout)
{
//InfoPrintf("read %d timeout %d on port %s\n", amount, timeout, _TTYName);
_CHECK_COM_HANDLE__(_PortName)
   SetReadTimeout((long)timeout);
   int nread = read(_Handle, buf, amount);
   if (nread < 0) {
      int err = errno;
      if (err != 11) {
         ErrorPrintf("error read %s: %d\n", _PortName, err);
      }
      throw cError(STDSER_READ_FILE, err, _PortName);
   }
   PrintBuffer(0, (const char *)buf, nread);
   return nread < 0 ? : 0, nread;
}

unsigned long cStandardBase::Write(const void * buf, unsigned long amount)
{
_CHECK_COM_HANDLE__(_PortName)
   int nwrite = write(_Handle, buf, amount);
   if (nwrite < 0) {
      int err = errno;
      ErrorPrintf("error write %s: %d\n", _PortName, err);
      throw cError(STDSER_WRITE_FILE, err, _PortName);
   }
   PrintBuffer(1, (const char *)buf, nwrite);
   return nwrite < 0 ? : 0, nwrite;
}

void cStandardBase::FlushInput()
{
_CHECK_COM_HANDLE__(_PortName)
   if (tcflush(_Handle, TCIFLUSH) < 0) {
      int err = errno;
      ErrorPrintf("error flush input %s: %d\n", _PortName, err);
   }
}

void cStandardBase::FlushOutput()
{
_CHECK_COM_HANDLE__(_PortName)
   if (tcflush(_Handle, TCOFLUSH) < 0) {
      int err = errno;
      ErrorPrintf("error flush output %s: %d\n", _PortName, err);
   }
}

void cStandardBase::SetBaudRate(unsigned long baud_rate)
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      cfsetispeed (&attr, BaudrateCtrl(baud_rate));
      cfsetospeed (&attr, BaudrateCtrl(baud_rate));
      if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_SET_COMM_STATE, err, _PortName);
      }
InfoPrintf("set baudrate to %d\n", baud_rate);
   }
}

unsigned long cStandardBase::GetBaudRate()
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      unsigned long baudrate = Baudrate(cfgetispeed(&attr));
      return baudrate;
   }
}

void cStandardBase::SetCharLen(unsigned char char_length)
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      attr.c_cflag |= CharlenCtrl(char_length);
      if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_SET_COMM_STATE, err, _PortName);
      }
InfoPrintf("set charlen to %d\n", (int)char_length);
   }
}

unsigned char cStandardBase::GetCharLen()
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      unsigned char charlen = Charlen(attr.c_cflag);
      return charlen;
   }
}

void cStandardBase::SetStartBits(unsigned char start_bits)
{
_CHECK_COM_HANDLE__(_PortName)
}

unsigned char cStandardBase::GetStartBits()
{
_CHECK_COM_HANDLE__(_PortName)
return 0;
}

void cStandardBase::SetStopBits(unsigned char stop_bits)
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      attr.c_cflag |= StopbitCtrl(stop_bits);
      if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_SET_COMM_STATE, err, _PortName);
      }
   }
}

unsigned char cStandardBase::GetStopBits()
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      unsigned char stopbits = Stopbit(attr.c_cflag);
      return stopbits;
   }
}

void cStandardBase::SetParity(ParityTypes parity)
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      attr.c_cflag |= ParityCtrl(parity);
      if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_SET_COMM_STATE, err, _PortName);
      }
   }
}

ParityTypes cStandardBase::GetParity()
{
_CHECK_COM_HANDLE__(_PortName)
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      ParityTypes parity = Parity(attr.c_cflag);
      return parity;
   }
}

void cStandardBase::SetHandshake(HandshakeTypes handshake)
{
_CHECK_COM_HANDLE__(_PortName)
PORT_LEVEL_5
}

HandshakeTypes cStandardBase::GetHandshake()
{
_CHECK_COM_HANDLE__(_PortName)
PORT_LEVEL_5
return NoHandshake;
}

void cStandardBase::SetTimeout(unsigned long timeout)
{
_CHECK_COM_HANDLE__(_PortName)
}

unsigned long cStandardBase::GetTimeout()
{
_CHECK_COM_HANDLE__(_PortName)
PORT_LEVEL_5
return 0;
}

void cStandardBase::GetState(COM_STATE_T * com_state)
{
_CHECK_COM_HANDLE__(_PortName)
PORT_LEVEL_5
}

void cStandardBase::ResetDevice()
{
_CHECK_COM_HANDLE__(_PortName)
PORT_LEVEL_5
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
      throw cError(STDSER_PORT_NAME_SIZE, 0, name);
   }
}

CONST_STRING_T cStandardBase::TTYName(CONST_STRING_T port_name)
{
   if (_stricmp(port_name, "com1") == 0) {
      return "/dev/ttyS0";
   } else if (_stricmp(port_name, "com2") == 0) {
      return "/dev/ttyS1";
   } else if (_stricmp(port_name, "com3") == 0) {
      return "/dev/ttyS2";
   } else if (_stricmp(port_name, "com4") == 0) {
      return "/dev/ttyS3";
   }
   return "/dev/null";
}

void cStandardBase::SetReadTimeout(long timeout)
{
   if (timeout == _ReadTimeout) {
      return;
   } else {
      unsigned long conv_timeout = timeout / 100;
      unsigned char set_timeout = (conv_timeout > 0xff) ? 0xff : (unsigned char)conv_timeout;
      struct termios attr = {0};
      if (tcgetattr(_Handle, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_GET_COMM_TIMEOUTS, err, _PortName);
      } else {
         if (timeout == INDEFINITE || timeout == 0) {
            attr.c_cc[VTIME] = 0;       /// no inter character timeout
            attr.c_cc[VMIN] = 1;        /// block until first character 
         } else {
            attr.c_cc[VTIME] = set_timeout;
            attr.c_cc[VMIN] = 0;
         }
         if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
            int err = errno;
            ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
            throw cError(STDSER_SET_COMM_TIMEOUTS, err, _PortName);
         } else {
            _ReadTimeout = timeout;
         }
      }
   }
}

void cStandardBase::InitializeDevice()
{
   _TTYName = TTYName(_PortName);
   int handle = open(_TTYName, O_RDWR|O_NONBLOCK);
   if (handle != INVALID_HANDLE) {
      try {
         struct termios attr = {0};
         bzero(&attr, sizeof(attr));
         attr.c_iflag = IGNBRK | IXON | IXOFF;
         attr.c_oflag &= ~(OPOST);
         attr.c_cflag = ParityCtrl(None) |
                        StopbitCtrl(1) |
                        CharlenCtrl(8) |
                        CLOCAL |     /* Disable modem control signals (wichtig!) */
                        CREAD;       /* allow input to be received               */
         attr.c_cflag &= ~(CRTSCTS); /* no hardware flow control                 */
         attr.c_lflag &= ~(ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL|IEXTEN);
         unsigned long baudrate = 9600;
         cfsetispeed (&attr, BaudrateCtrl(baudrate));
         cfsetospeed (&attr, BaudrateCtrl(baudrate));
         if (tcsetattr(handle, TCSANOW, &attr) < 0) {
            int err = errno;
            ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         }
         close(handle);
      } catch (...) {
         ErrorPrintf("unhandled exception when initializing device %s: %d\n", _PortName, errno);
      }
   } else {
      ErrorPrintf("error open %s: %d\n", _PortName, errno);
      throw cError(STDSER_CREATE_FILE, errno, _PortName);
   }
}

void cStandardBase::InitializeAttributes()
{
   struct termios attr = {0};
   if (tcgetattr(_Handle, &attr) < 0) {
      int err = errno;
      ErrorPrintf("error tcgetattr %s: %d line %d\n", _PortName, err, __LINE__);
      throw cError(STDSER_GET_COMM_STATE, err, _PortName);
   } else {
      attr.c_iflag = IGNBRK | IXON | IXOFF;
      attr.c_oflag &= ~(OPOST);
      attr.c_cflag = ParityCtrl(None) |
                     StopbitCtrl(1) |
                     CharlenCtrl(8) |
                     CLOCAL |     /* Disable modem control signals (wichtig!) */
                     CREAD;       /* allow input to be received               */
      attr.c_cflag &= ~(CRTSCTS); /* no hardware flow control                 */
      attr.c_lflag &= ~(ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL|IEXTEN);
      unsigned long baudrate = 9600;
      cfsetispeed (&attr, BaudrateCtrl(baudrate));
      cfsetospeed (&attr, BaudrateCtrl(baudrate));
      if (tcsetattr(_Handle, TCSANOW, &attr) < 0) {
         int err = errno;
         ErrorPrintf("error tcsetattr %s: %d line %d\n", _PortName, err, __LINE__);
         throw cError(STDSER_SET_COMM_STATE, err, _PortName);
      }
   }
}

#endif


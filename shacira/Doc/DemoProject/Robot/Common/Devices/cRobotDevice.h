
#ifndef _crobotdevice_h
#define _crobotdevice_h

#include "Control/SerialChannel/cSerialChannel.h"
#include "Control/Device/cDevice.h"
#include "Control/Cell/cCell.h"
#include "System/Config/cConfigurationObject.h"

#include "VirAs/object_defs.h"
#include "cCommands.h"

class RobotDeviceThread;

class cRobotDevice : public cDevice
{
public:
   cRobotDevice();
   //cRobotDevice(const cRobotDevice &right);
   cRobotDevice(cConfigurationObject * config_obj, cCell * cell);
   virtual ~cRobotDevice();
   virtual void Start();
   virtual void Stop();
   virtual void Cache(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Buffer(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements = 1);
   virtual void UseBuffer(CONST_STRING_T buf_spec);
   virtual void Read(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Write(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual void Read(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Write(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual BOOL_T ObjectSetParam(CONST_STRING_T name, CONST_STRING_T value);
   virtual void Download();
#ifdef use_direct
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, USHORT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, STRING_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, WSTRING_T &value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, USHORT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, CONST_STRING_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, CONST_WSTRING_T value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, WSTRING_T &value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_WSTRING_T value, ULONG_T flags = 0);
#endif

	void ProcessDataBlock(unsigned char*);
	UCHAR* cRobotDevice::GetCurve();
protected:
	cSerialChannel * _SerialChannel;
    ULONG_T _BaudRate;
    ParityTypes _Parity;
    HandshakeTypes _Handshake;
    UCHAR_T _CharLen;
    UCHAR_T _StartBits;
    UCHAR_T _StopBits;
	RobotDeviceThread * _DeviceThread;

	Virtual_Asuro_T _Asuro;
	unsigned char _Buf[20];
	UCHAR_T _DataPresent;
	UCHAR_T _CurveBuf[2][250];
	UINT_T _cnt;
};

#endif

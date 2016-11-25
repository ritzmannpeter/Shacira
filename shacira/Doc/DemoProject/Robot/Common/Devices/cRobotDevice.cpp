
//#include <string>

#include "FirstHeader.h"
#include "cRobotDevice.h"
#include "System/ApplicationInterface.h"
#include "base/eb_thread.hpp"

#include "Protocol/defs.h"
#include "Protocol/meta.h"
#include "Protocol/queue_handle.h"
#include "Protocol/state_machine.h"



#include "System/Database/cVariable.h"



REGISTER_DEVICE("RobotDevice", cRobotDevice)

static cSerialChannel * _CurrentChannel = NULL;


#ifdef __cplusplus
extern "C" {
#endif

unsigned char RecByte_serial()
{
	if (_CurrentChannel != NULL) {
		return (unsigned char)_CurrentChannel->GetChar(50);
	} else {
		return 0;
	}
}

void SendByte_serial(unsigned char c)
{
	if (_CurrentChannel != NULL) {
		_CurrentChannel->SendChar(c);
	}
}

#ifdef __cplusplus
}
#endif

static UCHAR_T led_value = 0;

class RobotDeviceThread : public cThread
{
public:
	RobotDeviceThread(cRobotDevice * device)
	{
		_Terminated = false;
		_Device = device;
	};
	virtual int onMain(void *extra)
	{
      SetCommunication(SendByte_serial, RecByte_serial);
      Queue_T out_queue = {0};
      Queue_T in_queue = {0};
      SetOutQueue(&out_queue);
      SetInQueue(&in_queue);
	  InitStateMachine( &AddData2InQueue );

		while (!_Terminated) {
/*
			if(str1[0]) AddData2OutQueue(str1,i);
			str1[i=0]=0;
*/
			SendFromOutQueue();
/*
			for(h=0;h<30;h++){
				str1[h]=0;
*/
				unsigned char * char_ptr;
				unsigned char c = 0;
		    ComputeByte(RecByte());
				if( char_ptr = GetFromInQueue(&c) )
				{
					//printf("processing.\t\v");
					//* \todo Implementieren oder kopieren
					_Device->ProcessDataBlock(char_ptr);
				
				}
            //cSystemUtils::Suspend(10);
			//led_value++;
			
			//_Device->Changed("test","front_led");
			
/*
			}
*/
		}
		return 0;
	};
	void Stop()
	{
		_Terminated = true;
	};
protected:
	cRobotDevice * _Device;
	bool _Terminated;
private:

};


cRobotDevice::cRobotDevice()
{
_ASSERT_UNCOND
}

/*cRobotDevice::cRobotDevice(const cRobotDevice &right) : cDevice(right)
{
_ASSERT_UNCOND
}*/

cRobotDevice::cRobotDevice (cConfigurationObject * config_obj, cCell * cell)
   : cDevice(config_obj, cell), _SerialChannel(NULL)
{
    cConfigurationObject * serial_channel_obj = config_obj->PropertyValue("SerialChannel", NULL_OBJECT);
	if (serial_channel_obj != NULL) {
	   _BaudRate = config_obj->PropertyValue("BaudRate", _BaudRate);
	   _Parity = cSerialChannel::ParityType(config_obj->PropertyValue("Parity", "None").c_str());
		_Handshake = cSerialChannel::HandshakeType(config_obj->PropertyValue("Handshake", "None").c_str());
		_CharLen = (UCHAR_T)config_obj->PropertyValue("CharLen", (ULONG_T)_CharLen);
		_StartBits = (UCHAR_T)config_obj->PropertyValue("StartBits", (ULONG_T)_StartBits);
	   _StopBits = (UCHAR_T)config_obj->PropertyValue("StopBits", (ULONG_T)_StopBits);
      _SerialChannel = cSerialChannelFactory::CreateSerialChannel(serial_channel_obj);
      _SerialChannel->Open();
      _SerialChannel->SetBaudRate(_BaudRate);
      _SerialChannel->SetCharLen(_CharLen);
      _SerialChannel->SetStartBits(_StartBits);
      _SerialChannel->SetStopBits(_StopBits);
      _SerialChannel->SetParity(_Parity);
	  _CurrentChannel = _SerialChannel;
		_DeviceThread = new RobotDeviceThread(this);
	
    }
//	_ComAs.SetFkt(&AddData2OutQueue);
	_cnt=_DataPresent=0;

}

cRobotDevice::~cRobotDevice()
{
}

void cRobotDevice::Start ()
{
	_DeviceThread->start();
}

void cRobotDevice::Stop ()
{
	_DeviceThread->Stop();
}

void cRobotDevice::Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cRobotDevice::Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements)
{
}

void cRobotDevice::UseBuffer (CONST_STRING_T buf_spec)
{
}

void cRobotDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
}

void cRobotDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{

}

void cRobotDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
	std::string s=name;
	/* *(UCHAR_T*)buf = led_value; */
	if(s=="front_led"){
		*(UCHAR_T*)buf = _Asuro.front_led;
	}
	if(s=="back_led_l"){
		*(UCHAR_T*)buf = _Asuro.back_l_led;
	}
	if(s=="back_led_r"){
		*(UCHAR_T*)buf = _Asuro.back_r_led;
	}
	if(s=="engine_r") *(UCHAR_T*)buf = _Asuro.right_engine.speed;
	if(s=="engine_r_d") *(UCHAR_T*)buf = _Asuro.right_engine.dir;
	if(s=="engine_l") *(UCHAR_T*)buf = _Asuro.left_engine.speed;
	if(s=="engine_l_d") *(UCHAR_T*)buf = _Asuro.left_engine.dir;
	if(s=="linedata_l"){
		*(USHORT*)buf = _Asuro.left_line.data;

	}
	if(s=="linedata_r"){
		*(USHORT*)buf = _Asuro.right_line.data;

	}
	if(s=="data_present")
	{
		*(UCHAR_T*)buf = _DataPresent;
	}
	if(s=="curve_buf")
	{
		//buf_dize
		int len = buf_size;
		if(sizeof(_CurveBuf)<len) len=sizeof(_CurveBuf);
		memcpy(buf,&_CurveBuf[0][0],len);
	//	*(UCHAR_T*)buf = _DataPresent;
	}
}

void cRobotDevice::Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags)
{
	int i=0;
	unsigned char _Buf[20];
	std::string s=name;
	_Buf[i++]=SET_COMMAND;
	_Buf[i++]=123;
	if(s=="front_led"){

		_Buf[i++] = LED_FRONT;
		_Buf[i++] = *(UCHAR_T*)buf;
		

	}
	else if(s=="back_led_l"){

		_Buf[i++] = LED_BACK_LEFT;
		_Buf[i++] = *(UCHAR_T*)buf;
		

	}
	else if(s=="back_led_r"){

		_Buf[i++] = LED_BACK_RIGHT;
		_Buf[i++] = *(UCHAR_T*)buf;

	}

	/** \todo split dir and speed in 2 requests/responses also the status led
	 */
	else if(s=="engine_r"){
		_Buf[i++] = ENGINE_RIGHT_SPEED;
		//_Buf[i++] = 1;//*(UCHAR_T*)&buf[0];
		_Buf[i++] = *(UCHAR_T*)(buf);

	}

	else if(s=="engine_r_d"){
		_Buf[i++] = ENGINE_RIGHT_DIR;
		_Buf[i++] = *(UCHAR_T*)buf;
		//_Buf[i++] = 150;
	}
	else if(s=="engine_l"){
		_Buf[i++] = ENGINE_LEFT_SPEED;
		//_Buf[i++] = 1;//*(UCHAR_T*)&buf[0];
		_Buf[i++] = *(UCHAR_T*)(buf);
	}

	else if(s=="engine_l_d"){
		_Buf[i++] = ENGINE_LEFT_DIR;
		_Buf[i++] = *(UCHAR_T*)buf;
		//_Buf[i++] = 150;
	}

	AddData2OutQueue(_Buf,(unsigned char)i);
}

BOOL_T cRobotDevice::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
   return false;
}

void cRobotDevice::Download()
{
}

void cRobotDevice::ProcessDataBlock(unsigned char* data)
{
	switch (data[0]) {
		case ERROR_RESPONSE:
			/*printf("\nGot Error:\t");
			switch (*(data+1)) {
				case ERR_BUFFER_OVERFLOW:
					printf("Buffer overflow\n");
					break;
				case ERR_BUSY:
					printf("Busy\n");
					break;
				case ERR_CHECKSUM:
					printf("Checksum\n");
					break;
				case ERR_INCOMPLETE_FRAME:
					printf("Frame incomplete\n");
					break;
				case ERR_TIMEOUT:
					printf("Timeout\n");
					break;
				case ERR_UNKNOWN_COMMAND:
					printf("Command unknown\n");
					break;
				default:
					printf("Error unknown\n");
					break;
			}
			break;*/
		
		case RESP_COMMAND:
			//printf("\n Response Arrived!\n");
			//SetAsuro(&data[1],12);
			//PrintAsuroStatus();
			switch (data[2]) {
				case LED_FRONT:
					/*if(len > 0)*/ _Asuro.front_led = data[3];
					Changed("test","front_led");
					//else SendError(ERR_INCOMPLETE_FRAME);
					break;
				case LED_STATUS:
					/*if(len > 0)*/ _Asuro.status_led = data[3];
					Changed("test","status_led");
					//else SendError(ERR_INCOMPLETE_FRAME);
					break;
				case LED_BACK_LEFT:
					/*if(len > 0)*/ _Asuro.back_l_led = data[3];
					Changed("test","back_led_l");
					//else SendError(ERR_INCOMPLETE_FRAME);
					break;
				case LED_BACK_RIGHT:
					/*if(len > 0)*/_Asuro.back_r_led = data[3];
					Changed("test","back_led_r");
					//else SendError(ERR_INCOMPLETE_FRAME);
					break;
				case ENGINE_LEFT_SPEED:
					/*if(len > 1){ */
						//_Asuro.left_engine.dir = data[3];
						_Asuro.left_engine.speed = data[3];
						Changed("test","engine_l");
						//Changed("test","engine_l_d");
						//Changed("test","front_led");
					/*}
					else SendError(ERR_INCOMPLETE_FRAME);*/
					break;
				case ENGINE_LEFT_DIR:
					/*if(len > 1){ */
						_Asuro.left_engine.dir = data[3];
						//_Asuro.left_engine.speed = data[4];
						//Changed("test","engine_l");
						Changed("test","engine_l_d");
						//Changed("test","front_led");
					/*}
					else SendError(ERR_INCOMPLETE_FRAME);*/
					break;

				case ENGINE_RIGHT_SPEED:
					/*if(len > 1){ */
						//_Asuro.right_engine.dir = data[3];
						_Asuro.right_engine.speed = data[3];
						Changed("test","engine_r");
						//Changed("test","engine_r_d");
					/*}
					else SendError(ERR_INCOMPLETE_FRAME);*/
					break;
				case ENGINE_RIGHT_DIR:
					/*if(len > 1){ */
						_Asuro.right_engine.dir = data[3];
						//_Asuro.right_engine.speed = data[4];
						//Changed("test","engine_r");
						Changed("test","engine_r_d");
					/*}
					else SendError(ERR_INCOMPLETE_FRAME);*/
					break;

				case LINE_DATA:
					/*if(len > 1){*/
						_Asuro.left_line.data = *(USHORT*)&(data[3]);
						_Asuro.right_line.data = *(USHORT*)&(data[5]);
						
						Changed("test","linedata_l");
						Changed("test","linedata_r");


						if(1/*!_DataPresent*/){

							//cVariable * var = context->Variable("graphic_buffer");

							/*if(!var){
								var->Set( (UCHAR)_Asuro.left_line.data,0,_cnt,-1,-1,0);
								var->Set( (UCHAR)_Asuro.right_line.data,1,_cnt,-1,-1,0);
							}*/

							_CurveBuf[0][_cnt] = (UCHAR)_Asuro.left_line.data;
							_CurveBuf[1][_cnt] = (UCHAR)_Asuro.right_line.data;

							_cnt++;
							if(_cnt==250){
								_cnt=0;
								_DataPresent = !_DataPresent;
								Changed("test","data_present");
								Changed("test","curve_buf");
							}
						}
						
						//asuro.right_line.data = data[1];
						//asuro.right_engine.speed = data[2];
					/*}
					else SendError(ERR_INCOMPLETE_FRAME);*/
					break;

			break;
				
		default:
			//printf("\nRecieved Data: Command unknown\n");
			break;	
			}
}}

UCHAR* cRobotDevice::GetCurve()
{
	return &_CurveBuf[0][0];
}
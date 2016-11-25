//## begin module%3FD8D20D01A5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FD8D20D01A5.cm

//## begin module%3FD8D20D01A5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FD8D20D01A5.cp

//## Module: cGrabberDevice%3FD8D20D01A5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cGrabberDevice.cpp

//## begin module%3FD8D20D01A5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FD8D20D01A5.additionalIncludes

//## begin module%3FD8D20D01A5.includes preserve=yes

#include "System/Sys/cFileSystemUtils.h"

//## end module%3FD8D20D01A5.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cImage
#include "System/Database/cImage.h"
// cGrabberDevice
#include "Control/Device/cGrabberDevice.h"
//## begin module%3FD8D20D01A5.additionalDeclarations preserve=yes

#define CHECK_CHANNEL(channel,channels) \
if (channel < 0 || channel >= EAGLE_MAX_CHANNELS) { \
   return; \
}; 

#define CHECK_HANDLE(handle) \
if (handle == NULL) { \
   return; \
}; 

//## end module%3FD8D20D01A5.additionalDeclarations


// Class cGrabberDevice 























//## begin cGrabberDevice::Falcon%4083B3D303A9.attr preserve=no  implementation: static cFalcon {U} 
cFalcon cGrabberDevice::_Falcon;
//## end cGrabberDevice::Falcon%4083B3D303A9.attr

//## begin cGrabberDevice::UEye%4083B3F9030D.attr preserve=no  implementation: static cUEye {U} 
cUEye cGrabberDevice::_UEye;
//## end cGrabberDevice::UEye%4083B3F9030D.attr

cGrabberDevice::cGrabberDevice()
  //## begin cGrabberDevice::cGrabberDevice%.hasinit preserve=no
      : _XSize(640), _YSize(480), _PixSize(8), _ColorCount(256), _Contrast(0), _Brightness(0), _Channel(0), _CamType(CAMTYPE_EAGLE), _BoardID(0), _CameraID(0), _CaptureMode(false), _Handle(NULL), _Pid(0), _PixelClock(0), _USBDelay(100), _SyncDelay(100), _VideoBuffer(NULL), _Sequence(0), _Grabber(NULL), _VideoMode(0), _ActGain(0), _ActExposure(0), _MinExposureTime(0), _MaxExposureTime(0), _IntervallExposureTime(0)
  //## end cGrabberDevice::cGrabberDevice%.hasinit
  //## begin cGrabberDevice::cGrabberDevice%.initialization preserve=yes
  //## end cGrabberDevice::cGrabberDevice%.initialization
{
  //## begin cGrabberDevice::cGrabberDevice%.body preserve=yes
_ASSERT_UNCOND
  //## end cGrabberDevice::cGrabberDevice%.body
}

cGrabberDevice::cGrabberDevice(const cGrabberDevice &right)
  //## begin cGrabberDevice::cGrabberDevice%copy.hasinit preserve=no
      : _XSize(640), _YSize(480), _PixSize(8), _ColorCount(256), _Contrast(0), _Brightness(0), _Channel(0), _CamType(CAMTYPE_EAGLE), _BoardID(0), _CameraID(0), _CaptureMode(false), _Handle(NULL), _Pid(0), _PixelClock(0), _USBDelay(100), _SyncDelay(100), _VideoBuffer(NULL), _Sequence(0), _Grabber(NULL), _VideoMode(0), _ActGain(0), _ActExposure(0), _MinExposureTime(0), _MaxExposureTime(0), _IntervallExposureTime(0)
  //## end cGrabberDevice::cGrabberDevice%copy.hasinit
  //## begin cGrabberDevice::cGrabberDevice%copy.initialization preserve=yes
  //## end cGrabberDevice::cGrabberDevice%copy.initialization
{
  //## begin cGrabberDevice::cGrabberDevice%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGrabberDevice::cGrabberDevice%copy.body
}

cGrabberDevice::cGrabberDevice (cConfigurationObject *config_obj, cCell *cell)
  //## begin cGrabberDevice::cGrabberDevice%1071171007.hasinit preserve=no
      : _XSize(640), _YSize(480), _PixSize(8), _ColorCount(256), _Contrast(0), _Brightness(0), _Channel(0), _CamType(CAMTYPE_EAGLE), _BoardID(0), _CameraID(0), _CaptureMode(false), _Handle(NULL), _Pid(0), _PixelClock(0), _USBDelay(100), _SyncDelay(100), _VideoBuffer(NULL), _Sequence(0), _Grabber(NULL), _VideoMode(0), _ActGain(0), _ActExposure(0), _MinExposureTime(0), _MaxExposureTime(0), _IntervallExposureTime(0)
  //## end cGrabberDevice::cGrabberDevice%1071171007.hasinit
  //## begin cGrabberDevice::cGrabberDevice%1071171007.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cGrabberDevice::cGrabberDevice%1071171007.initialization
{
  //## begin cGrabberDevice::cGrabberDevice%1071171007.body preserve=yes
   BOOL_T params_present = false;
   memset(&_BoardInfo, 0, sizeof(_BoardInfo));
   memset(&_SensorInfo, 0, sizeof(_SensorInfo));
   _BoardID = config_obj->PropertyValue("BoardID", _BoardID);
   _CameraID = config_obj->PropertyValue("CameraID", _CameraID);
   _Channel = config_obj->PropertyValue("Channel", _Channel);
   _XSize = config_obj->PropertyValue("XSize", _XSize);
   _YSize = config_obj->PropertyValue("YSize", _YSize);
   _PixSize = config_obj->PropertyValue("PixSize", _PixSize);
   _ColorCount = config_obj->PropertyValue("ColorCount", _ColorCount);
   _PixelClock = config_obj->PropertyValue("PixelClock", (LONG_T)_PixelClock);
   _USBDelay = config_obj->PropertyValue("USBDelay", _USBDelay);
   _SyncDelay = config_obj->PropertyValue("SyncDelay", _SyncDelay);
   _CaptureMode = config_obj->PropertyValue("CaptureMode", _CaptureMode);
   _Contrast = config_obj->PropertyValue("Contrast", _Contrast);
   _Brightness = config_obj->PropertyValue("Brightness", _Brightness);
   _VideoMode = config_obj->PropertyValue("VideoMode", _VideoMode);
   if (_Simulated) {
      _VideoBuffer = (char*)cSystemUtils::Alloc(_XSize * _YSize * _PixSize);
   } else {
      int ret = 0;
      _CamType = config_obj->PropertyValue("CamType", _CamType);
      BOOL_T new_handle = false;
      if (_CamType == CAMTYPE_UEYE) {
         _Grabber = new cIdsGrabber("uEye_api.dll");
         _Handle = _UEye.OpenHandle(_Grabber, _CameraID);
         STRING_T file_name = _Name;
         file_name += ".ini";
         STRING_T config_path = cResources::ConfigPath();
         STRING_T file = cFileSystemUtils::AppendPath(config_path.c_str(), file_name.c_str());
         if (cFileSystemUtils::FileExists(file.c_str())) {
            InfoPrintf("loading parameter file %s for camera %s\n", file.c_str(), _Name.c_str());
            ret = _Grabber->LoadParameters(_Handle, file.c_str());
            if (ret == IS_SUCCESS) {
               params_present = true;
            } else {
               ErrorPrintf("failed to load parameter file %s: %d: %s\n",
                           file.c_str(), BoardError(), BoardErrorString().c_str());
            }
         } else {
            InfoPrintf("no parameter file %s for camera %s\n", file.c_str(), _Name.c_str());
         }
      } else {
         _Grabber = new cIdsGrabber("falcon.dll");
         _Handle = _Falcon.OpenHandle(_Grabber, _BoardID, new_handle);
      }
      if (_CamType == CAMTYPE_UEYE || new_handle == true) {
         ret = _Grabber->GetBoardInfo(_Handle, &_BoardInfo);
         if (ret != IS_SUCCESS) throw cError(GRABBER_BOARD_INFO, BoardError(), BoardErrorString().c_str());
         ret = _Grabber->GetSensorInfo(_Handle, &_SensorInfo);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SENSOR_INFO, BoardError(), BoardErrorString().c_str());
         ret = _Grabber->SetDisplayMode(_Handle, IS_SET_DM_DIB);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SET_DISPLAY_MODE, BoardError(), BoardErrorString().c_str());
         ret = _Grabber->SetImageSize(_Handle, _XSize, _YSize);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SET_IMAGE_SIZE, BoardError(), BoardErrorString().c_str(),
                                                cConvUtils::StringValue(_XSize).c_str(), cConvUtils::StringValue(_YSize).c_str());
         UCHAR_T color_mode = IS_SET_CM_Y8;
         ret = _Grabber->SetColorMode(_Handle, color_mode);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SET_COLOR_MODE, BoardError(), BoardErrorString().c_str(),
                                             cConvUtils::StringValue(color_mode).c_str());
         ret = _Grabber->AllocImageMem(_Handle, _XSize, _YSize, _PixSize, &_VideoBuffer, &_Pid);
         if (ret != IS_SUCCESS) throw cError(GRABBER_ALLOC_IMAGE_MEM, BoardError(), BoardErrorString().c_str(),
                                             cConvUtils::StringValue(_PixSize).c_str());
         ret = _Grabber->SetImageMem(_Handle, _VideoBuffer, _Pid);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SET_IMAGE_MEM, BoardError(), BoardErrorString().c_str());
         if (_CamType == CAMTYPE_EAGLE) {
            _Falcon.SetVideoBuffer(_VideoBuffer, _BoardID);
         }
         UCHAR_T capture_mode = IS_SET_CM_FRAME;
         ret = _Grabber->SetCaptureMode(_Handle, capture_mode);
         if (ret != IS_SUCCESS) throw cError(GRABBER_SET_CAPTURE_MODE, BoardError(), BoardErrorString().c_str(),
                                             cConvUtils::StringValue(capture_mode).c_str());
         if (_CaptureMode) {
            ret = _Grabber->CaptureVideo(_Handle, IS_WAIT);
            if (ret != IS_SUCCESS) {
               int err = BoardError();
               if (err != 0) {
                  throw cError(GRABBER_CAPTURE_VIDEO, BoardError(), BoardErrorString().c_str());
               }
            }
         }

         ret = _Grabber->GetExposureRange(_Handle, &_MinExposureTime, &_MaxExposureTime, &_IntervallExposureTime);

      }
      if (_CamType == CAMTYPE_EAGLE) {
         _VideoBuffer = _Falcon.GetVideoBuffer(_BoardID);
      }
      if (_CamType == CAMTYPE_UEYE) {
         if (!params_present) {
            if (_PixelClock > 10 && _PixelClock < 60) {
               ret = _Grabber->SetPixelClock(_Handle, _PixelClock);
               if (ret != IS_SUCCESS) throw cError(GRABBER_SET_IMAGE_SIZE, BoardError(), BoardErrorString().c_str(),
                                                cConvUtils::StringValue(_XSize).c_str(), cConvUtils::StringValue(_YSize).c_str());
            }
            double rate = 0, new_rate = 0;
            if (_XSize == 640) {
               rate = 30;
            } else if (_XSize == 1280) {
               rate = 10;
            }
            if (rate > 0) _Grabber->SetFrameRate(_Handle, rate, &new_rate);
            if (_Contrast > 0 && _Contrast < 511) {
               ret = _Grabber->SetContrast(_Handle, _Contrast);
               if (ret != IS_SUCCESS) throw cError(GRABBER_SET_CONTRAST, BoardError(), BoardErrorString().c_str());
            }
            if (_Brightness > 0 && _Brightness < 256) {
               ret = _Grabber->SetBrightness(_Handle, _Brightness);
               if (ret != IS_SUCCESS) throw cError(GRABBER_SET_BRIGHTNESS, BoardError(), BoardErrorString().c_str());
            }
         }
	  }
   }
  //## end cGrabberDevice::cGrabberDevice%1071171007.body
}


cGrabberDevice::~cGrabberDevice()
{
  //## begin cGrabberDevice::~cGrabberDevice%.body preserve=yes
   if (_Simulated) {
      cSystemUtils::Free(_VideoBuffer);
   } else {
      if (_Handle != NULL) {
         if (_Grabber != NULL) {
            _Grabber->FreeImageMem(_Handle, _VideoBuffer, _Pid);
            _Grabber->ExitBoard(_Handle);
         }
      }
      DELETE_OBJECT(cIdsGrabber, _Grabber)
   }
  //## end cGrabberDevice::~cGrabberDevice%.body
}



//## Other Operations (implementation)
void cGrabberDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cGrabberDevice::Read%1071171008.body preserve=yes
   cObjectLock __lock__(&_ChannelMutex);
   if (_Simulated) {
      char seq[32] = {0};
      STRING_T DeviceName = (STRING_T) this->get_Name() + ".raw";			// GH Simuliert-Bilder Namensbenennung in [Device Name].raw geaendert
      SafePrintf(seq, sizeof(seq), "%s", DeviceName.c_str());
      FILE * stream = fopen(seq, "rb");
      if (stream != NULL) {
         try {
            cImage image(_XSize, _YSize, (UCHAR_T)_PixSize, _ColorCount, (BUF_T)buf, buf_size);
            BUF_T dest = image.GetImageData();
            ULONG_T image_size = image.GetImageSize();
            int nread = fread(dest, 1, image_size, stream);
            fclose(stream);
            _Sequence++;
         } catch (...) {
         }
      } else {
         try {
            cImage image(_XSize, _YSize, (UCHAR_T)_PixSize, _ColorCount, (BUF_T)buf, buf_size);
            BUF_T dest = image.GetImageData();
            int image_size = image.GetImageSize();
            int pos = 0;
            for (pos=0; pos<image_size; pos++) {
               unsigned char pixel = (unsigned char)(rand()%255);
               dest[pos] = pixel;
            }
            _Sequence++;
         } catch (...) {
         }
      }
   } else {
      CHECK_HANDLE(_Handle)
      if (_CamType == CAMTYPE_EAGLE) {
         if (IDENTIFIER_EQUAL(name, "Image")) {
            ReadEagle(buf_spec, len, buf, buf_size);
         } else if (IDENTIFIER_EQUAL(name, "Channel")) {
         }
      } else if (_CamType == CAMTYPE_UEYE) {
         if (IDENTIFIER_EQUAL(name, "Image")) {
            ReadUEye(buf_spec, len, buf, buf_size);
         } else if (IDENTIFIER_EQUAL(name, "Channel")) {
         }
      }
   }
  //## end cGrabberDevice::Read%1071171008.body
}


void cGrabberDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags)
{
	if (IDENTIFIER_EQUAL(buf_spec, "Setting")) 
	{
		if (IDENTIFIER_EQUAL(name, "Gain")) 
		{
			value = _ActGain;
		} 
		else if (IDENTIFIER_EQUAL(name, "Shutter"))
		{
			value = _ActExposure;
		} 
	}
}

void cGrabberDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags)
{
	LONG_T lval = 0;
	Get(buf_spec, name, lval);
	value = (ULONG_T)lval;
}


void cGrabberDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags)
{
	if (IDENTIFIER_EQUAL(buf_spec, "Setting")) 
	{
		if (IDENTIFIER_EQUAL(name, "Gain")) 
		{
			_ActGain = value;
			if (!_Simulated)
				_Grabber->SetHardwareGain(_Handle, _ActGain, 0, 0, 0);
		} 
		else if (IDENTIFIER_EQUAL(name, "Shutter"))
		{
			_ActExposure = value;
			double diffTime = _MaxExposureTime - _MinExposureTime;
			double actTime = _MinExposureTime + ((diffTime * value) / 100);
			if (!_Simulated)
				_Grabber->SetExposureTime(_Handle, actTime, &actTime);  
		} 
	}
}


void cGrabberDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags)
{
	Set(buf_spec, name, (LONG_T)value);
}


DOUBLE_T cGrabberDevice::GetParameter(CONST_STRING_T parameter_id) const
{
   if (strcmp(parameter_id, "ImageWidth") == 0) {
      return _XSize;
   } else if (strcmp(parameter_id, "ImageHeight") == 0) {
      return _YSize;
   }
   return 0;
}

int cGrabberDevice::BoardError ()
{
  //## begin cGrabberDevice::BoardError%1071756311.body preserve=yes
   char * err_string = NULL;
   int err_code = 0;
   int ret = _Grabber->GetError(_Handle, &err_code, &err_string);
   return err_code;
  //## end cGrabberDevice::BoardError%1071756311.body
}

STRING_T cGrabberDevice::BoardErrorString ()
{
  //## begin cGrabberDevice::BoardErrorString%1071756312.body preserve=yes
   STRING_T _err_string;
   char * err_string = NULL;
   int err_code = 0;
   int ret = _Grabber->GetError(_Handle, &err_code, &err_string);
   _err_string = err_string;
   return _err_string;
  //## end cGrabberDevice::BoardErrorString%1071756312.body
}

void cGrabberDevice::SetChannel (INT_T channel)
{
  //## begin cGrabberDevice::SetChannel%1076246973.body preserve=yes
   cObjectLock __lock__(&_ChannelMutex);
   int source;
   switch (channel) {
   case 0: source = IS_SET_VIDEO_IN_1; break;
   case 1: source = IS_SET_VIDEO_IN_2; break;
   case 2: source = IS_SET_VIDEO_IN_3; break;
   case 3: source = IS_SET_VIDEO_IN_4; break;
   default: throw cError(GRABBER_INVALID_CHANNEL, 0, cConvUtils::StringValue(channel).c_str());
   }
   int ret = _Grabber->SetVideoInput(_Handle, source);
   if (ret != IS_SUCCESS) throw cError(GRABBER_SET_VIDEO_INPUT, BoardError(), BoardErrorString().c_str(),
                                       cConvUtils::StringValue(channel).c_str());
   if (_SyncDelay) cSystemUtils::Suspend(_SyncDelay);
//if (_SyncDelay) Beep(200, _SyncDelay);
  //## end cGrabberDevice::SetChannel%1076246973.body
}

void cGrabberDevice::SetVideoMode (INT_T mode)
{
   //cObjectLock __lock__(&_ModeMutex);
   int videoMode;
   switch (mode)
   {
   case 0:
	   videoMode = IS_SET_VM_NTSC;
	   break;
   case 1:
	   videoMode = IS_SET_VM_NTSC;
	   break;
   case 2:
	   videoMode = IS_SET_VM_SECAM;
	   break;
   case 3:
	   videoMode = IS_SET_VM_AUTO;
	   break;
   default:
	   throw cError(GRABBER_INVALID_VIDEO_MODE, 0, cConvUtils::StringValue(mode).c_str());
   }
   int ret = _Grabber->SetVideoMode(_Handle, videoMode);
   if (ret != IS_SUCCESS)
	   throw cError(GRABBER_SET_VIDEO_MODE, BoardError(), BoardErrorString().c_str(), cConvUtils::StringValue(mode).c_str());
   if (_SyncDelay)
	   cSystemUtils::Suspend(_SyncDelay);
}

void cGrabberDevice::ReadUEye (CONST_STRING_T buf_spec, ULONG_T len, void *buf, ULONG_T buf_size)
{
  //## begin cGrabberDevice::ReadUEye%1077900819.body preserve=yes
   if (_USBDelay > 0) cSystemUtils::Suspend(_USBDelay);
//if (_USBDelay > 0) Beep(600, _USBDelay);
   int ret = 0;
   cImage image(_XSize, _YSize, (UCHAR_T)_PixSize, _ColorCount, (BUF_T)buf, buf_size);
   BUF_T dest = image.GetImageData();

   if (!_CaptureMode) {
ULONG_T t = GetTickCount();
      int retries = 3;
	  ret = _Grabber->FreezeVideo(_Handle, IS_WAIT);
      while (retries-- && ret != IS_SUCCESS) {
		  ret = _Grabber->FreezeVideo(_Handle, IS_WAIT);
//		throw cError(GRABBER_COPY_IMAGE_MEM, BoardError(), BoardErrorString().c_str());
		  ErrorPrintf("failed to freeze: %s\n", BoardErrorString().c_str());
	  }
	  if (ret != IS_SUCCESS) {
	      ULONG_T size = image.GetImageSize();
		  memset(dest, 0, size);
		  ErrorPrintf("cleared image of size %d\n", size);
		  return;
	  }
      printf("Freeze %d: %d\n", _CameraID, GetTickCount() - t);
   }
   ret = _Grabber->CopyImageMem(_Handle, _VideoBuffer, _Pid, (char*)dest);
   if (ret != IS_SUCCESS) {
//	   throw cError(GRABBER_COPY_IMAGE_MEM, BoardError(), BoardErrorString().c_str());
		ErrorPrintf("failed to copy: %s\n", BoardErrorString().c_str());
   }
  //## end cGrabberDevice::ReadUEye%1077900819.body
}

void cGrabberDevice::ReadEagle (CONST_STRING_T buf_spec, ULONG_T len, void *buf, ULONG_T buf_size)
{
  //## begin cGrabberDevice::ReadEagle%1076250332.body preserve=yes
   INT_T channel = VideoChannel(buf_spec);
   if (channel == NO_CHANNEL || channel >= EAGLE_MAX_CHANNELS) {
      return;
   }
   INT_T act_channel = ActChannel();
   if (act_channel == NO_CHANNEL || act_channel >= EAGLE_MAX_CHANNELS) {
      return;
   } else if (channel != act_channel) {
      SetChannel(channel);
   }

   INT_T videoMode = VideoMode();
   if ((videoMode < IS_SET_VM_PAL) || (videoMode > IS_SET_VM_AUTO))
   {
	   return;
   }
   INT_T act_videoMode = ActVideoMode();
   if (act_videoMode < IS_SET_VM_PAL || (act_videoMode > IS_SET_VM_AUTO))
   {
      return;
   }
   else if (videoMode != act_videoMode)
   {
	   SetVideoMode(videoMode);
   }

   int ret = 0;

   if (!_CaptureMode) {
      ret = _Grabber->FreezeVideo(_Handle, IS_WAIT);
      if (ret != IS_SUCCESS) throw cError(GRABBER_COPY_IMAGE_MEM, BoardError(), BoardErrorString().c_str());
   }

   cImage image(_XSize, _YSize, (UCHAR_T)_PixSize, _ColorCount, (BUF_T)buf, buf_size);
   BUF_T dest = image.GetImageData();
   ret = _Grabber->CopyImageMem(_Handle, _VideoBuffer, _Pid, (char*)dest);
   if (ret != IS_SUCCESS) throw cError(GRABBER_COPY_IMAGE_MEM, BoardError(), BoardErrorString().c_str());
  //## end cGrabberDevice::ReadEagle%1076250332.body
}

INT_T cGrabberDevice::VideoChannel (CONST_STRING_T buf_spec)
{
  //## begin cGrabberDevice::VideoChannel%1076250333.body preserve=yes
return _Channel;
   INT_T channel = NO_CHANNEL;
   int params = sscanf(buf_spec, "Channel%d", &channel);
   if (params == 1) {
      return channel;
   } else {
      return NO_CHANNEL;
   }
  //## end cGrabberDevice::VideoChannel%1076250333.body
}

INT_T cGrabberDevice::VideoMode ()
{
	return _VideoMode;
}

INT_T cGrabberDevice::ActChannel ()
{
  //## begin cGrabberDevice::ActChannel%1076250334.body preserve=yes
   int act_channel = _Grabber->SetVideoInput(_Handle, IS_GET_VIDEO_IN);
   return act_channel;
  //## end cGrabberDevice::ActChannel%1076250334.body
}

INT_T cGrabberDevice::ActVideoMode ()
{
   int act_videoMode = _Grabber->SetVideoMode(_Handle, IS_GET_VIDEO_MODE);
   return act_videoMode;
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cGrabberDevice::get_XSize () const
{
  //## begin cGrabberDevice::get_XSize%3FE2ED670203.get preserve=no
  return _XSize;
  //## end cGrabberDevice::get_XSize%3FE2ED670203.get
}

void cGrabberDevice::set_XSize (ULONG_T value)
{
  //## begin cGrabberDevice::set_XSize%3FE2ED670203.set preserve=no
  _XSize = value;
  //## end cGrabberDevice::set_XSize%3FE2ED670203.set
}

ULONG_T cGrabberDevice::get_YSize () const
{
  //## begin cGrabberDevice::get_YSize%3FE2ED8E037A.get preserve=no
  return _YSize;
  //## end cGrabberDevice::get_YSize%3FE2ED8E037A.get
}

void cGrabberDevice::set_YSize (ULONG_T value)
{
  //## begin cGrabberDevice::set_YSize%3FE2ED8E037A.set preserve=no
  _YSize = value;
  //## end cGrabberDevice::set_YSize%3FE2ED8E037A.set
}

ULONG_T cGrabberDevice::get_PixSize () const
{
  //## begin cGrabberDevice::get_PixSize%3FE2EDD8006D.get preserve=no
  return _PixSize;
  //## end cGrabberDevice::get_PixSize%3FE2EDD8006D.get
}

void cGrabberDevice::set_PixSize (ULONG_T value)
{
  //## begin cGrabberDevice::set_PixSize%3FE2EDD8006D.set preserve=no
  _PixSize = value;
  //## end cGrabberDevice::set_PixSize%3FE2EDD8006D.set
}

ULONG_T cGrabberDevice::get_ColorCount () const
{
  //## begin cGrabberDevice::get_ColorCount%4040866600FA.get preserve=no
  return _ColorCount;
  //## end cGrabberDevice::get_ColorCount%4040866600FA.get
}

void cGrabberDevice::set_ColorCount (ULONG_T value)
{
  //## begin cGrabberDevice::set_ColorCount%4040866600FA.set preserve=no
  _ColorCount = value;
  //## end cGrabberDevice::set_ColorCount%4040866600FA.set
}

LONG_T cGrabberDevice::get_Contrast () const
{
  //## begin cGrabberDevice::get_Contrast%430057A90232.get preserve=no
  return _Contrast;
  //## end cGrabberDevice::get_Contrast%430057A90232.get
}

void cGrabberDevice::set_Contrast (LONG_T value)
{
  //## begin cGrabberDevice::set_Contrast%430057A90232.set preserve=no
  _Contrast = value;
  //## end cGrabberDevice::set_Contrast%430057A90232.set
}

LONG_T cGrabberDevice::get_Brightness () const
{
  //## begin cGrabberDevice::get_Brightness%430057C4006D.get preserve=no
  return _Brightness;
  //## end cGrabberDevice::get_Brightness%430057C4006D.get
}

void cGrabberDevice::set_Brightness (LONG_T value)
{
  //## begin cGrabberDevice::set_Brightness%430057C4006D.set preserve=no
  _Brightness = value;
  //## end cGrabberDevice::set_Brightness%430057C4006D.set
}

ULONG_T cGrabberDevice::get_Channel () const
{
  //## begin cGrabberDevice::get_Channel%40263CF30177.get preserve=no
  return _Channel;
  //## end cGrabberDevice::get_Channel%40263CF30177.get
}

void cGrabberDevice::set_Channel (ULONG_T value)
{
  //## begin cGrabberDevice::set_Channel%40263CF30177.set preserve=no
  _Channel = value;
  //## end cGrabberDevice::set_Channel%40263CF30177.set
}

ULONG_T cGrabberDevice::get_VideoMode () const
{
  return _VideoMode;
}

void cGrabberDevice::set_VideoMode (ULONG_T value)
{
  _VideoMode = value;
}

ULONG_T cGrabberDevice::get_CamType () const
{
  //## begin cGrabberDevice::get_CamType%403F758E009C.get preserve=no
  return _CamType;
  //## end cGrabberDevice::get_CamType%403F758E009C.get
}

void cGrabberDevice::set_CamType (ULONG_T value)
{
  //## begin cGrabberDevice::set_CamType%403F758E009C.set preserve=no
  _CamType = value;
  //## end cGrabberDevice::set_CamType%403F758E009C.set
}

ULONG_T cGrabberDevice::get_BoardID () const
{
  //## begin cGrabberDevice::get_BoardID%4049C9C80213.get preserve=no
  return _BoardID;
  //## end cGrabberDevice::get_BoardID%4049C9C80213.get
}

void cGrabberDevice::set_BoardID (ULONG_T value)
{
  //## begin cGrabberDevice::set_BoardID%4049C9C80213.set preserve=no
  _BoardID = value;
  //## end cGrabberDevice::set_BoardID%4049C9C80213.set
}

ULONG_T cGrabberDevice::get_CameraID () const
{
  //## begin cGrabberDevice::get_CameraID%4083AC7D0167.get preserve=no
  return _CameraID;
  //## end cGrabberDevice::get_CameraID%4083AC7D0167.get
}

void cGrabberDevice::set_CameraID (ULONG_T value)
{
  //## begin cGrabberDevice::set_CameraID%4083AC7D0167.set preserve=no
  _CameraID = value;
  //## end cGrabberDevice::set_CameraID%4083AC7D0167.set
}

BOOL_T cGrabberDevice::get_CaptureMode () const
{
  //## begin cGrabberDevice::get_CaptureMode%40869BA50271.get preserve=no
  return _CaptureMode;
  //## end cGrabberDevice::get_CaptureMode%40869BA50271.get
}

void cGrabberDevice::set_CaptureMode (BOOL_T value)
{
  //## begin cGrabberDevice::set_CaptureMode%40869BA50271.set preserve=no
  _CaptureMode = value;
  //## end cGrabberDevice::set_CaptureMode%40869BA50271.set
}

// Additional Declarations
  //## begin cGrabberDevice%3FD8D20D01A5.declarations preserve=yes
  //## end cGrabberDevice%3FD8D20D01A5.declarations

//## begin module%3FD8D20D01A5.epilog preserve=yes
//## end module%3FD8D20D01A5.epilog

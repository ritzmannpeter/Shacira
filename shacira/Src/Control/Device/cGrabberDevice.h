//## begin module%3FD8D20D01A5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FD8D20D01A5.cm

//## begin module%3FD8D20D01A5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FD8D20D01A5.cp

//## Module: cGrabberDevice%3FD8D20D01A5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cGrabberDevice.h

#ifndef cGrabberDevice_h
#define cGrabberDevice_h 1

//## begin module%3FD8D20D01A5.includes preserve=yes

#ifdef _WIN32

#include "Control/Device/Ids/cIdsGrabber.h"

#else

class cIdsGrabber;
typedef int * HIDS;
typedef int BOARDINFO;
typedef int SENSORINFO;
typedef int * cFalcon;
typedef int * cUEye;

#endif

//## end module%3FD8D20D01A5.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cImage;

//## begin module%3FD8D20D01A5.additionalDeclarations preserve=yes

#define CAMTYPE_EAGLE   1
#define CAMTYPE_UEYE    2
#define NO_CHANNEL   -1

//## end module%3FD8D20D01A5.additionalDeclarations


//## begin cGrabberDevice%3FD8D20D01A5.preface preserve=yes
//## end cGrabberDevice%3FD8D20D01A5.preface

//## Class: cGrabberDevice%3FD8D20D01A5
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40263ABA0128;cObjectLock { -> F}
//## Uses: <unnamed>%403082E60000;cImage { -> F}

class __DLL_EXPORT__ cGrabberDevice : public cDevice  //## Inherits: <unnamed>%3FD8D22E0148
{
  //## begin cGrabberDevice%3FD8D20D01A5.initialDeclarations preserve=yes
public:
  //## end cGrabberDevice%3FD8D20D01A5.initialDeclarations

    //## Constructors (generated)
      cGrabberDevice();

      cGrabberDevice(const cGrabberDevice &right);

    //## Constructors (specified)
      //## Operation: cGrabberDevice%1071171007
      cGrabberDevice (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cGrabberDevice();


    //## Other Operations (specified)
      //## Operation: Read%1071171008
      virtual void Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

	  virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags = 0);
	  virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);
	  virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags = 0);
	  virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);

      virtual DOUBLE_T GetParameter(CONST_STRING_T parameter_id) const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: XSize%3FE2ED670203
      ULONG_T get_XSize () const;
      void set_XSize (ULONG_T value);

      //## Attribute: YSize%3FE2ED8E037A
      ULONG_T get_YSize () const;
      void set_YSize (ULONG_T value);

      //## Attribute: PixSize%3FE2EDD8006D
      ULONG_T get_PixSize () const;
      void set_PixSize (ULONG_T value);

      //## Attribute: ColorCount%4040866600FA
      ULONG_T get_ColorCount () const;
      void set_ColorCount (ULONG_T value);

      //## Attribute: Contrast%430057A90232
      LONG_T get_Contrast () const;
      void set_Contrast (LONG_T value);

      //## Attribute: Brightness%430057C4006D
      LONG_T get_Brightness () const;
      void set_Brightness (LONG_T value);

      //## Attribute: Channel%40263CF30177
      ULONG_T get_Channel () const;
      void set_Channel (ULONG_T value);

      //## Attribute: CamType%403F758E009C
      ULONG_T get_CamType () const;
      void set_CamType (ULONG_T value);

      //## Attribute: BoardID%4049C9C80213
      ULONG_T get_BoardID () const;
      void set_BoardID (ULONG_T value);

      //## Attribute: CameraID%4083AC7D0167
      ULONG_T get_CameraID () const;
      void set_CameraID (ULONG_T value);

      //## Attribute: CaptureMode%40869BA50271
      BOOL_T get_CaptureMode () const;
      void set_CaptureMode (BOOL_T value);
	  
      ULONG_T get_VideoMode () const;
      void set_VideoMode (ULONG_T value);

    // Data Members for Class Attributes

      //## Attribute: ChannelMutex%40263A8602BF
      //## begin cGrabberDevice::ChannelMutex%40263A8602BF.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _ChannelMutex;
      //## end cGrabberDevice::ChannelMutex%40263A8602BF.attr

  public:
    // Additional Public Declarations
      //## begin cGrabberDevice%3FD8D20D01A5.public preserve=yes
      //## end cGrabberDevice%3FD8D20D01A5.public

  protected:
    // Data Members for Class Attributes

      //## begin cGrabberDevice::XSize%3FE2ED670203.attr preserve=no  public: ULONG_T {U} 640
      ULONG_T _XSize;
      //## end cGrabberDevice::XSize%3FE2ED670203.attr

      //## begin cGrabberDevice::YSize%3FE2ED8E037A.attr preserve=no  public: ULONG_T {U} 480
      ULONG_T _YSize;
      //## end cGrabberDevice::YSize%3FE2ED8E037A.attr

      //## begin cGrabberDevice::PixSize%3FE2EDD8006D.attr preserve=no  public: ULONG_T {U} 8
      ULONG_T _PixSize;
      //## end cGrabberDevice::PixSize%3FE2EDD8006D.attr

      //## begin cGrabberDevice::ColorCount%4040866600FA.attr preserve=no  public: ULONG_T {U} 256
      ULONG_T _ColorCount;
      //## end cGrabberDevice::ColorCount%4040866600FA.attr

      //## begin cGrabberDevice::Contrast%430057A90232.attr preserve=no  public: LONG_T {U} 0
      LONG_T _Contrast;
      //## end cGrabberDevice::Contrast%430057A90232.attr

      //## begin cGrabberDevice::Brightness%430057C4006D.attr preserve=no  public: LONG_T {U} 0
      LONG_T _Brightness;
      //## end cGrabberDevice::Brightness%430057C4006D.attr

      //## begin cGrabberDevice::Channel%40263CF30177.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Channel;
      //## end cGrabberDevice::Channel%40263CF30177.attr

      //## begin cGrabberDevice::CamType%403F758E009C.attr preserve=no  public: ULONG_T {U} CAMTYPE_EAGLE
      ULONG_T _CamType;
      //## end cGrabberDevice::CamType%403F758E009C.attr

      //## begin cGrabberDevice::BoardID%4049C9C80213.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _BoardID;
      //## end cGrabberDevice::BoardID%4049C9C80213.attr

      //## begin cGrabberDevice::CameraID%4083AC7D0167.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _CameraID;
      //## end cGrabberDevice::CameraID%4083AC7D0167.attr

      //## begin cGrabberDevice::CaptureMode%40869BA50271.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _CaptureMode;
      //## end cGrabberDevice::CaptureMode%40869BA50271.attr

      ULONG_T _VideoMode;

    // Additional Protected Declarations
      //## begin cGrabberDevice%3FD8D20D01A5.protected preserve=yes
      //## end cGrabberDevice%3FD8D20D01A5.protected

  private:
    // Additional Private Declarations
      //## begin cGrabberDevice%3FD8D20D01A5.private preserve=yes
      //## end cGrabberDevice%3FD8D20D01A5.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: BoardError%1071756311
      int BoardError ();

      //## Operation: BoardErrorString%1071756312
      STRING_T BoardErrorString ();

      //## Operation: SetChannel%1076246973
      void SetChannel (INT_T channel);

      //## Operation: ReadUEye%1077900819
      void ReadUEye (CONST_STRING_T buf_spec, ULONG_T len, void *buf, ULONG_T buf_size);

      //## Operation: ReadEagle%1076250332
      void ReadEagle (CONST_STRING_T buf_spec, ULONG_T len, void *buf, ULONG_T buf_size);

      //## Operation: VideoChannel%1076250333
      INT_T VideoChannel (CONST_STRING_T buf_spec);

      //## Operation: ActChannel%1076250334
      INT_T ActChannel ();
	  
      INT_T VideoMode ();

      void SetVideoMode (INT_T videoMode);
	  
      INT_T ActVideoMode ();

    // Data Members for Class Attributes

      //## Attribute: Handle%3FE1B3F101F4
      //## begin cGrabberDevice::Handle%3FE1B3F101F4.attr preserve=no  implementation: HIDS {U} NULL
      HIDS _Handle;
      //## end cGrabberDevice::Handle%3FE1B3F101F4.attr

      //## Attribute: BoardInfo%3FE1BDC403C8
      //## begin cGrabberDevice::BoardInfo%3FE1BDC403C8.attr preserve=no  implementation: BOARDINFO {U} 
      BOARDINFO _BoardInfo;
      //## end cGrabberDevice::BoardInfo%3FE1BDC403C8.attr

      //## Attribute: SensorInfo%4049CB1303C8
      //## begin cGrabberDevice::SensorInfo%4049CB1303C8.attr preserve=no  implementation: SENSORINFO {U} 
      SENSORINFO _SensorInfo;
      //## end cGrabberDevice::SensorInfo%4049CB1303C8.attr

      //## Attribute: Pid%3FE2EDAD00AB
      //## begin cGrabberDevice::Pid%3FE2EDAD00AB.attr preserve=no  implementation: int {U} 0
      int _Pid;
      //## end cGrabberDevice::Pid%3FE2EDAD00AB.attr

      //## Attribute: PixelClock%407E65A901D4
      //## begin cGrabberDevice::PixelClock%407E65A901D4.attr preserve=no  implementation: int {U} 0
      int _PixelClock;
      //## end cGrabberDevice::PixelClock%407E65A901D4.attr

      //## Attribute: USBDelay%40837C15030D
      //## begin cGrabberDevice::USBDelay%40837C15030D.attr preserve=no  implementation: ULONG_T {U} 100
      ULONG_T _USBDelay;
      //## end cGrabberDevice::USBDelay%40837C15030D.attr

      //## Attribute: SyncDelay%4083A4A002DE
      //## begin cGrabberDevice::SyncDelay%4083A4A002DE.attr preserve=no  implementation: ULONG_T {U} 100
      ULONG_T _SyncDelay;
      //## end cGrabberDevice::SyncDelay%4083A4A002DE.attr

      //## Attribute: VideoBuffer%3FE2EDBC00EA
      //## begin cGrabberDevice::VideoBuffer%3FE2EDBC00EA.attr preserve=no  implementation: char * {U} NULL
      char *_VideoBuffer;
      //## end cGrabberDevice::VideoBuffer%3FE2EDBC00EA.attr

      //## Attribute: Sequence%3FE492CA00AB
      //## begin cGrabberDevice::Sequence%3FE492CA00AB.attr preserve=no  implementation: int {U} 0
      int _Sequence;
      //## end cGrabberDevice::Sequence%3FE492CA00AB.attr

      //## Attribute: Grabber%4049D6AB0119
      //## begin cGrabberDevice::Grabber%4049D6AB0119.attr preserve=no  implementation: cIdsGrabber * {U} NULL
      cIdsGrabber *_Grabber;
      //## end cGrabberDevice::Grabber%4049D6AB0119.attr

      //## Attribute: Falcon%4083B3D303A9
      //## begin cGrabberDevice::Falcon%4083B3D303A9.attr preserve=no  implementation: static cFalcon {U} 
      static cFalcon _Falcon;
      //## end cGrabberDevice::Falcon%4083B3D303A9.attr

      //## Attribute: UEye%4083B3F9030D
      //## begin cGrabberDevice::UEye%4083B3F9030D.attr preserve=no  implementation: static cUEye {U} 
      static cUEye _UEye;
      //## end cGrabberDevice::UEye%4083B3F9030D.attr

    // Additional Implementation Declarations
      //## begin cGrabberDevice%3FD8D20D01A5.implementation preserve=yes
      //## end cGrabberDevice%3FD8D20D01A5.implementation

	  int _ActGain;
	  int _ActExposure;
	  double _MinExposureTime;
	  double _MaxExposureTime;
	  double _IntervallExposureTime;
};

//## begin cGrabberDevice%3FD8D20D01A5.postscript preserve=yes
//## end cGrabberDevice%3FD8D20D01A5.postscript

// Class cGrabberDevice 

//## begin module%3FD8D20D01A5.epilog preserve=yes
//## end module%3FD8D20D01A5.epilog


#endif

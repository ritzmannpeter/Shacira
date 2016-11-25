//## begin module%3A51D539000C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A51D539000C.cm

//## begin module%3A51D539000C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A51D539000C.cp

//## Module: cCell%3A51D539000C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cCell.h

#ifndef cCell_h
#define cCell_h 1

//## begin module%3A51D539000C.includes preserve=yes
//## end module%3A51D539000C.includes

// cStaticObject
#include "System/Objects/cStaticObject.h"

class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cStringUtils;
class cMutexSem;
class __DLL_EXPORT__ cInfo;
class __DLL_EXPORT__ cProgress;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cSharedLibrary;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cLocalContext;
class __DLL_EXPORT__ cDevice;
class __DLL_EXPORT__ cDeviceFactory;

//## begin module%3A51D539000C.additionalDeclarations preserve=yes
//## end module%3A51D539000C.additionalDeclarations


//## begin cCell%3A51D539000C.preface preserve=yes
//## end cCell%3A51D539000C.preface

//## Class: cCell%3A51D539000C
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A791BD300F6;cConfigurationObject { -> F}
//## Uses: <unnamed>%3B18E228003A;cTokenizer { -> F}
//## Uses: <unnamed>%3B8A7EEA012B;cStringUtils { -> F}
//## Uses: <unnamed>%3CFF985101B0;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3FE6DA2200AB;cDeviceFactory { -> F}
//## Uses: <unnamed>%4156D79E01E0;cMutexSem { -> F}
//## Uses: <unnamed>%4198B603007D;cSharedLibrary { -> F}
//## Uses: <unnamed>%42E7BF740232;cProgress { -> F}
//## Uses: <unnamed>%42E7C5EB034B;cInfo { -> F}
//## Uses: <unnamed>%42EA28BE02FD;cContext { -> F}

class __DLL_EXPORT__ cCell : public cStaticObject  //## Inherits: <unnamed>%3E144147002E
{
  //## begin cCell%3A51D539000C.initialDeclarations preserve=yes
public:
  //## end cCell%3A51D539000C.initialDeclarations

    //## Constructors (generated)
      cCell();

      cCell(const cCell &right);

    //## Constructors (specified)
      //## Operation: cCell%978422270
      cCell (cLocalContext *context, cConfigurationObject *config_obj);
      cCell (cLocalContext *context);

    //## Destructor (generated)
      virtual ~cCell();


    //## Other Operations (specified)
      //## Operation: Event%983863599
      virtual void Event (cTransientObject *object);

      //## Operation: Start%982075365
      void Start ();

      //## Operation: Stop%983778357
      void Stop ();

      //## Operation: Device%1047978426
      cDevice * Device (CONST_STRING_T device_name);

      //## Operation: ResolveItem%1072085848
      BOOL_T ResolveItem (CONST_STRING_T path, STRING_T &device_name, STRING_T &item_name);

      //## Operation: SetDeviceValue%1122475165
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value);

      //## Operation: GetDeviceValue%1078912378
      //	Gets the value directly from a device. Device and value
      //	address are specified through an URL.
      void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value);

      //## Operation: SetDevicesBuffered%1091556105
      void SetDevicesBuffered (BOOL_T state);

      //## Operation: GetDevicesBuffered%1126515329
      BOOL_T GetDevicesBuffered ();

      //## Operation: SetDevicesCached%1091556106
      void SetDevicesCached (BOOL_T state);

      //## Operation: GetDevicesCached%1126515330
      BOOL_T GetDevicesCached ();

      //## Operation: Save%1122475167
      virtual void Save (UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Download%1122475168
      //	The download method activates a download of all device
      //	data hold in a database.
      virtual void Download (ULONG_T ctrl = 0);

      //## Operation: Upload%1122475169
      //	The upload method activates an upload of all device data
      //	hold in devices.
      virtual void Upload (ULONG_T ctrl = 0);

      //## Operation: SetProgress%1120661021
      void SetProgress (ULONG_T indicator, ULONG_T value);

      //## Operation: Context%1122641992
      cContext * Context ();

  public:
    // Additional Public Declarations
      //## begin cCell%3A51D539000C.public preserve=yes
      //## end cCell%3A51D539000C.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%3FE6C19601C5
      //## Role: cCell::Devices%3FE6C19701D4
      //## Qualifier: name%3FE6C1C402FD; STRING_T
      //## begin cCell::Devices%3FE6C19701D4.role preserve=no  public: cDevice { -> 0..nRFHN}
      std::map<STRING_T, cDevice*> _Devices;
      //## end cCell::Devices%3FE6C19701D4.role

      //## Association: Control::LocalDatabase::<unnamed>%3EDDE2760399
      //## Role: cCell::LocalContext%3EDDE27802DE
      //## begin cCell::LocalContext%3EDDE27802DE.role preserve=no  public: cLocalContext {1 -> 1RFHN}
      cLocalContext *_LocalContext;
      //## end cCell::LocalContext%3EDDE27802DE.role

    // Additional Protected Declarations
      //## begin cCell%3A51D539000C.protected preserve=yes
      //## end cCell%3A51D539000C.protected

  private:
    // Additional Private Declarations
      //## begin cCell%3A51D539000C.private preserve=yes
      //## end cCell%3A51D539000C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartDevices%1072801792
      void StartDevices ();

      //## Operation: StopDevices%1072801793
      void StopDevices ();

      //## Operation: SplitAddress%1082991645
      void SplitAddress (CONST_STRING_T address, STRING_T &device_name, STRING_T &new_address);

    // Data Members for Class Attributes

      //## Attribute: DevicesBuffered%411B67170232
      //## begin cCell::DevicesBuffered%411B67170232.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _DevicesBuffered;
      //## end cCell::DevicesBuffered%411B67170232.attr

      //## Attribute: DevicesCached%411B6739005D
      //## begin cCell::DevicesCached%411B6739005D.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _DevicesCached;
      //## end cCell::DevicesCached%411B6739005D.attr

    // Additional Implementation Declarations
      //## begin cCell%3A51D539000C.implementation preserve=yes
      //## end cCell%3A51D539000C.implementation

};

//## begin cCell%3A51D539000C.postscript preserve=yes
//## end cCell%3A51D539000C.postscript

// Class cCell 

//## begin module%3A51D539000C.epilog preserve=yes
//## end module%3A51D539000C.epilog


#endif

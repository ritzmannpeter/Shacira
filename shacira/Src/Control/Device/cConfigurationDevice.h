//## begin module%408CFEAE0138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%408CFEAE0138.cm

//## begin module%408CFEAE0138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%408CFEAE0138.cp

//## Module: cConfigurationDevice%408CFEAE0138; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cConfigurationDevice.h

#ifndef cConfigurationDevice_h
#define cConfigurationDevice_h 1

//## begin module%408CFEAE0138.includes preserve=yes
//## end module%408CFEAE0138.includes

// cConfiguration
#include "System/Config/cConfiguration.h"
// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%408CFEAE0138.additionalDeclarations preserve=yes
//## end module%408CFEAE0138.additionalDeclarations


//## begin cConfigurationDevice%408CFEAE0138.preface preserve=yes
//## end cConfigurationDevice%408CFEAE0138.preface

//## Class: cConfigurationDevice%408CFEAE0138
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%408D572F031C;cFileSystemUtils { -> F}
//## Uses: <unnamed>%408D575503A9;cConfiguration { -> }

class __DLL_EXPORT__ cConfigurationDevice : public cDevice  //## Inherits: <unnamed>%408CFEE200BB
{
  //## begin cConfigurationDevice%408CFEAE0138.initialDeclarations preserve=yes
public:
  //## end cConfigurationDevice%408CFEAE0138.initialDeclarations

    //## Constructors (generated)
      cConfigurationDevice();

      cConfigurationDevice(const cConfigurationDevice &right);

    //## Constructors (specified)
      //## Operation: cConfigurationDevice%1082991647
      cConfigurationDevice (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cConfigurationDevice();


    //## Other Operations (specified)
      //## Operation: Start%1082991648
      virtual void Start ();

      //## Operation: Stop%1082991649
      virtual void Stop ();

      //## Operation: Cache%1082991650
      virtual void Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size);

      //## Operation: Buffer%1082991651
      virtual void Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T elements = 1);

      //## Operation: Get%1082991653
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags = 0);

      //## Operation: Get%1082991654
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1082991655
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1082991656
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags = 0);

      //## Operation: Set%1082991657
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags = 0);

      //## Operation: Set%1082991658
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, LONG_T value, ULONG_T flags = 0);

      //## Operation: Set%1082991659
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);

      //## Operation: Cast%1082991660
      virtual void Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value);

      //## Operation: Read%1082991661
      virtual void Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

  public:
    // Additional Public Declarations
      //## begin cConfigurationDevice%408CFEAE0138.public preserve=yes
      //## end cConfigurationDevice%408CFEAE0138.public

  protected:
    // Additional Protected Declarations
      //## begin cConfigurationDevice%408CFEAE0138.protected preserve=yes
      //## end cConfigurationDevice%408CFEAE0138.protected

  private:
    // Additional Private Declarations
      //## begin cConfigurationDevice%408CFEAE0138.private preserve=yes
      //## end cConfigurationDevice%408CFEAE0138.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Configuration%408D4B59004E
      //## begin cConfigurationDevice::Configuration%408D4B59004E.attr preserve=no  implementation: cConfiguration * {U} NULL
      cConfiguration *_Configuration;
      //## end cConfigurationDevice::Configuration%408D4B59004E.attr

    // Additional Implementation Declarations
      //## begin cConfigurationDevice%408CFEAE0138.implementation preserve=yes
      //## end cConfigurationDevice%408CFEAE0138.implementation

};

//## begin cConfigurationDevice%408CFEAE0138.postscript preserve=yes
//## end cConfigurationDevice%408CFEAE0138.postscript

// Class cConfigurationDevice 

//## begin module%408CFEAE0138.epilog preserve=yes
//## end module%408CFEAE0138.epilog


#endif

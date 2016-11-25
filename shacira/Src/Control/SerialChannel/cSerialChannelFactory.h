//## begin module%3DDDF56602D1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDDF56602D1.cm

//## begin module%3DDDF56602D1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDDF56602D1.cp

//## Module: cSerialChannelFactory%3DDDF56602D1; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSerialChannelFactory.h

#ifndef cSerialChannelFactory_h
#define cSerialChannelFactory_h 1

//## begin module%3DDDF56602D1.includes preserve=yes
//## end module%3DDDF56602D1.includes

// cSocketChannel
#include "Control/SerialChannel/cSocketChannel.h"
// cVirtualSocketChannel
#include "Control/SerialChannel/cVirtualSocketChannel.h"
// cStandardChannel
#include "Control/SerialChannel/cStandardChannel.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cSerialChannel;

//## begin module%3DDDF56602D1.additionalDeclarations preserve=yes
//## end module%3DDDF56602D1.additionalDeclarations


//## begin cSerialChannelFactory%3DDDF56602D1.preface preserve=yes
//## end cSerialChannelFactory%3DDDF56602D1.preface

//## Class: cSerialChannelFactory%3DDDF56602D1
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DDDF61701E5;cConfigurationObject { -> F}
//## Uses: <unnamed>%3DDDF89A0280;cStandardChannel { -> }
//## Uses: <unnamed>%3DDDF89C026F;cVirtualSocketChannel { -> }
//## Uses: <unnamed>%3DDDF89F00C5;cSocketChannel { -> }
//## Uses: <unnamed>%3DDDFB84005C;cConvUtils { -> F}

class __DLL_EXPORT__ cSerialChannelFactory 
{
  //## begin cSerialChannelFactory%3DDDF56602D1.initialDeclarations preserve=yes
public:
  //## end cSerialChannelFactory%3DDDF56602D1.initialDeclarations

    //## Constructors (generated)
      cSerialChannelFactory();

      cSerialChannelFactory(const cSerialChannelFactory &right);

    //## Destructor (generated)
      virtual ~cSerialChannelFactory();


    //## Other Operations (specified)
      //## Operation: CreateSerialChannel%1037956852
      static cSerialChannel * CreateSerialChannel (cConfigurationObject *config_obj);

      //## Operation: CreateSerialChannel%1037956853
      static cSerialChannel * CreateSerialChannel (INT_T type);

      //## Operation: CreateCustomChannel%1079341315
      static cSerialChannel * CreateCustomChannel (CONST_STRING_T object_type, cConfigurationObject *config_obj, cStaticObject *related_object);

      //## Operation: CreateDLLChannel%1079341316
      static cSerialChannel * CreateDLLChannel (CONST_STRING_T object_type, cConfigurationObject *config_obj, cStaticObject *related_object);

  public:
    // Additional Public Declarations
      //## begin cSerialChannelFactory%3DDDF56602D1.public preserve=yes
      //## end cSerialChannelFactory%3DDDF56602D1.public

  protected:
    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3E2C3E9400C5
      //## Role: cSerialChannelFactory::Channels%3E2C3E950293
      //## Qualifier: name%3E2C406E0211; STRING_T
      //## begin cSerialChannelFactory::Channels%3E2C3E950293.role preserve=no  public: static cSerialChannel { -> 0..nRFHN}
      static std::map<STRING_T, cSerialChannel*> _Channels;
      //## end cSerialChannelFactory::Channels%3E2C3E950293.role

    // Additional Protected Declarations
      //## begin cSerialChannelFactory%3DDDF56602D1.protected preserve=yes
      //## end cSerialChannelFactory%3DDDF56602D1.protected

  private:
    // Additional Private Declarations
      //## begin cSerialChannelFactory%3DDDF56602D1.private preserve=yes
      //## end cSerialChannelFactory%3DDDF56602D1.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSerialChannelFactory%3DDDF56602D1.implementation preserve=yes
      //## end cSerialChannelFactory%3DDDF56602D1.implementation

};

//## begin cSerialChannelFactory%3DDDF56602D1.postscript preserve=yes
//## end cSerialChannelFactory%3DDDF56602D1.postscript

// Class cSerialChannelFactory 

//## begin module%3DDDF56602D1.epilog preserve=yes
//## end module%3DDDF56602D1.epilog


#endif

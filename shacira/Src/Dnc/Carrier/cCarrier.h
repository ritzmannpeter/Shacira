//## begin module%3B97BB680370.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B97BB680370.cm

//## begin module%3B97BB680370.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B97BB680370.cp

//## Module: cCarrier%3B97BB680370; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\Carrier\cCarrier.h

#ifndef cCarrier_h
#define cCarrier_h 1

//## begin module%3B97BB680370.includes preserve=yes
//## end module%3B97BB680370.includes

//## begin module%3B97BB680370.additionalDeclarations preserve=yes

#define INVALID_HANDLE  INVALID_HANDLE_VALUE
#define CHECK_CARRIER_HANDLE if (_Handle == INVALID_HANDLE) throw cError(CARRIER_INVALID_HANDLE, 0);

#define CARRIER_INVALID_HANDLE   -11700
#define CARRIER_WINAPI_ERROR     -11701

//## end module%3B97BB680370.additionalDeclarations


//## begin cCarrier%3B97BB680370.preface preserve=yes
//## end cCarrier%3B97BB680370.preface

//## Class: cCarrier%3B97BB680370
//	This class realizes a driver object to read blocks of
//	data from an EEPROM-Carrier
//## Category: Dnc::Carrier%3B97BB340195
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCarrier 
{
  //## begin cCarrier%3B97BB680370.initialDeclarations preserve=yes
public:
  //## end cCarrier%3B97BB680370.initialDeclarations

    //## Constructors (generated)
      cCarrier();

      cCarrier(const cCarrier &right);

    //## Constructors (specified)
      //## Operation: cCarrier%999800100
      cCarrier (CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cCarrier();


    //## Other Operations (specified)
      //## Operation: Read%999800097
      LONG_T Read (ULONG_T address, UCHAR_T *buf, ULONG_T buf_size, LONG_T amount);

      //## Operation: Write%999800098
      LONG_T Write (ULONG_T address, UCHAR_T *buf, LONG_T amount);

      //## Operation: Size%999800099
      LONG_T Size ();

  public:
    // Additional Public Declarations
      //## begin cCarrier%3B97BB680370.public preserve=yes
      //## end cCarrier%3B97BB680370.public

  protected:
    // Additional Protected Declarations
      //## begin cCarrier%3B97BB680370.protected preserve=yes
      //## end cCarrier%3B97BB680370.protected

  private:
    // Additional Private Declarations
      //## begin cCarrier%3B97BB680370.private preserve=yes
      //## end cCarrier%3B97BB680370.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Handle%3B97BF6B0218
      //## begin cCarrier::Handle%3B97BF6B0218.attr preserve=no  implementation: HANDLE {U} 
      HANDLE _Handle;
      //## end cCarrier::Handle%3B97BF6B0218.attr

    // Additional Implementation Declarations
      //## begin cCarrier%3B97BB680370.implementation preserve=yes
      //## end cCarrier%3B97BB680370.implementation

};

//## begin cCarrier%3B97BB680370.postscript preserve=yes
//## end cCarrier%3B97BB680370.postscript

// Class cCarrier 

//## begin module%3B97BB680370.epilog preserve=yes
//## end module%3B97BB680370.epilog


#endif

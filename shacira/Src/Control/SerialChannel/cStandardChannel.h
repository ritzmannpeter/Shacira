//## begin module%3728746C01CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3728746C01CA.cm

//## begin module%3728746C01CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3728746C01CA.cp

//## Module: cStandardChannel%3728746C01CA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cStandardChannel.h

#ifndef cStandardChannel_h
#define cStandardChannel_h 1

//## begin module%3728746C01CA.includes preserve=yes

#include "Control/SerialChannel/Base/cStandardBase.h"

//## end module%3728746C01CA.includes

// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"

class __DLL_EXPORT__ cConfigurationObject;

//## begin module%3728746C01CA.additionalDeclarations preserve=yes
//## end module%3728746C01CA.additionalDeclarations


//## begin cStandardChannel%3728746C01CA.preface preserve=yes
//## end cStandardChannel%3728746C01CA.preface

//## Class: cStandardChannel%3728746C01CA
//	cStandardChannel handles serial communication over
//	standard communication ports that are offered by the
//	underlying system.
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A6C2AA7011C; { -> }
//## Uses: <unnamed>%3AE527800241;cConfigurationObject { -> F}

class __DLL_EXPORT__ cStandardChannel : public cSerialChannel  //## Inherits: <unnamed>%3728790D03A4
{
  //## begin cStandardChannel%3728746C01CA.initialDeclarations preserve=yes
public:
  //## end cStandardChannel%3728746C01CA.initialDeclarations

    //## Constructors (generated)
      cStandardChannel();

      cStandardChannel(const cStandardChannel &right);

    //## Constructors (specified)
      //## Operation: cStandardChannel%980152396
      cStandardChannel (cConfigurationObject *config_obj);

      //## Operation: cStandardChannel%1069326619
      cStandardChannel (CONST_STRING_T port_name);

    //## Destructor (generated)
      virtual ~cStandardChannel();


    //## Other Operations (specified)
      //## Operation: GetBaudRate%980176536
      virtual ULONG_T GetBaudRate ();

      //## Operation: SetBaudRate%980152397
      virtual void SetBaudRate (ULONG_T baud_rate);

      //## Operation: GetStopBits%980152398
      virtual UCHAR_T GetStopBits ();

      //## Operation: SetStopBits%980152399
      virtual void SetStopBits (UCHAR_T stop_bits);

      //## Operation: GetStartBits%980152400
      virtual UCHAR_T GetStartBits ();

      //## Operation: SetStartBits%980152401
      virtual void SetStartBits (UCHAR_T start_bits);

      //## Operation: GetCharLen%980152402
      virtual UCHAR_T GetCharLen ();

      //## Operation: SetCharLen%980152403
      virtual void SetCharLen (UCHAR_T data_len);

      //## Operation: GetParity%980152404
      virtual ParityTypes GetParity ();

      //## Operation: SetParity%980152405
      virtual void SetParity (ParityTypes parity);

      //## Operation: GetHandshake%980239688
      virtual HandshakeTypes GetHandshake ();

      //## Operation: SetHandshake%980239689
      virtual void SetHandshake (HandshakeTypes handshake);

      //## Operation: GetTimeout%980152406
      virtual ULONG_T GetTimeout ();

      //## Operation: SetTimeout%980152407
      virtual void SetTimeout (ULONG_T timeout);

      //## Operation: GetState%1014886111
      virtual void GetState (COM_STATE_T *state);

      //## Operation: Open%980168055
      virtual void Open ();

      //## Operation: Close%980168056
      virtual void Close ();

      //## Operation: Reset%1014806626
      virtual void Reset (INT_T type);

      //## Operation: Read%934378728
      virtual LONG_T Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout);

      //## Operation: Write%934378729
      virtual LONG_T Write (UCHAR_T *buffer, ULONG_T amount);

      //## Operation: FlushInput%934378732
      virtual void FlushInput ();

      //## Operation: FlushOutput%934378733
      virtual void FlushOutput ();

      //## Operation: GetPortName%980168057
      virtual CONST_STRING_T GetPortName ();

      //## Operation: SetPortName%980168058
      virtual void SetPortName (CONST_STRING_T name);

  public:
    // Additional Public Declarations
      //## begin cStandardChannel%3728746C01CA.public preserve=yes
      //## end cStandardChannel%3728746C01CA.public

  protected:
    // Additional Protected Declarations
      //## begin cStandardChannel%3728746C01CA.protected preserve=yes
      //## end cStandardChannel%3728746C01CA.protected

  private:
    // Additional Private Declarations
      //## begin cStandardChannel%3728746C01CA.private preserve=yes
      //## end cStandardChannel%3728746C01CA.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: BaseChannel%3A6C2BFA001F
      //## begin cStandardChannel::BaseChannel%3A6C2BFA001F.attr preserve=no  implementation: cStandardBase {U} 
      cStandardBase _BaseChannel;
      //## end cStandardChannel::BaseChannel%3A6C2BFA001F.attr

    // Additional Implementation Declarations
      //## begin cStandardChannel%3728746C01CA.implementation preserve=yes
      //## end cStandardChannel%3728746C01CA.implementation

};

//## begin cStandardChannel%3728746C01CA.postscript preserve=yes
//## end cStandardChannel%3728746C01CA.postscript

// Class cStandardChannel 

//## begin module%3728746C01CA.epilog preserve=yes
//## end module%3728746C01CA.epilog


#endif

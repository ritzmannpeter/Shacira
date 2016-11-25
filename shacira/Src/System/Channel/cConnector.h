//## begin module%3F85177902CE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F85177902CE.cm

//## begin module%3F85177902CE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F85177902CE.cp

//## Module: cConnector%3F85177902CE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cConnector.h

#ifndef cConnector_h
#define cConnector_h 1

//## begin module%3F85177902CE.includes preserve=yes
//## end module%3F85177902CE.includes

// cAdapter
#include "System/Channel/cAdapter.h"
// cChannel
#include "System/Channel/cChannel.h"

class __DLL_EXPORT__ cTransientObject;

//## begin module%3F85177902CE.additionalDeclarations preserve=yes
//## end module%3F85177902CE.additionalDeclarations


//## begin cConnector%3F85177902CE.preface preserve=yes
//## end cConnector%3F85177902CE.preface

//## Class: cConnector%3F85177902CE
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F85195E009C;cTransientObject { -> F}
//## Uses: <unnamed>%3FFE7C37038A;cChannel { -> }

class __DLL_EXPORT__ cConnector : public cAdapter  //## Inherits: <unnamed>%3F85179D038A
{
  //## begin cConnector%3F85177902CE.initialDeclarations preserve=yes
public:
  //## end cConnector%3F85177902CE.initialDeclarations

    //## Constructors (generated)
      cConnector();

      cConnector(const cConnector &right);

    //## Destructor (generated)
      virtual ~cConnector();


    //## Other Operations (specified)
      //## Operation: ObjectGetParam%1075904921
      virtual BOOL_T ObjectGetParam (CONST_STRING_T name, STRING_T &value);

      //## Operation: ObjectSetParam%1075904922
      virtual BOOL_T ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value);

      //## Operation: Connect%1073642253
      //	Connects the back end of the channel to the front end of
      //	"front_end"
      void Connect (cChannel *channel);

      //## Operation: Disconnect%1073642254
      //	Disconnects a channel from the back end of the channel
      void Disconnect (cChannel *channel);

      //## Operation: Object%1065687231
      //	Method that is called when an incoming object arrives at
      //	the back end of the associated channel.
      virtual void Object (cTransientObject *object);

  public:
    // Additional Public Declarations
      //## begin cConnector%3F85177902CE.public preserve=yes
      //## end cConnector%3F85177902CE.public

  protected:

    //## Other Operations (specified)
      //## Operation: Emit%1073642242
      //	Emit emits an object.
      void Emit (cTransientObject *object);

    // Data Members for Class Attributes

      //## Attribute: Channels%3FFE7A9D037A
      //## begin cConnector::Channels%3FFE7A9D037A.attr preserve=no  protected: CHANNEL_LIST_T {U} 
      CHANNEL_LIST_T _Channels;
      //## end cConnector::Channels%3FFE7A9D037A.attr

    // Additional Protected Declarations
      //## begin cConnector%3F85177902CE.protected preserve=yes
      //## end cConnector%3F85177902CE.protected

  private:
    // Additional Private Declarations
      //## begin cConnector%3F85177902CE.private preserve=yes
      //## end cConnector%3F85177902CE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cConnector%3F85177902CE.implementation preserve=yes
      //## end cConnector%3F85177902CE.implementation

};

//## begin cConnector%3F85177902CE.postscript preserve=yes
//## end cConnector%3F85177902CE.postscript

// Class cConnector 

//## begin module%3F85177902CE.epilog preserve=yes
//## end module%3F85177902CE.epilog


#endif

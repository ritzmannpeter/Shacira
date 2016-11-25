//## begin module%3EDB31F402EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDB31F402EE.cm

//## begin module%3EDB31F402EE.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3EDB31F402EE.cp

//## Module: cCorbaProxy%3EDB31F402EE; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\System\Objects\cCorbaProxy.h

#ifndef cCorbaProxy_h
#define cCorbaProxy_h 1

//## begin module%3EDB31F402EE.includes preserve=yes
//## end module%3EDB31F402EE.includes

// cProxy
#include "System/Objects/cProxy.h"
//## begin module%3EDB31F402EE.additionalDeclarations preserve=yes
//## end module%3EDB31F402EE.additionalDeclarations


//## begin cCorbaProxy%3EDB31F402EE.preface preserve=yes
//## end cCorbaProxy%3EDB31F402EE.preface

//## Class: cCorbaProxy%3EDB31F402EE
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class cCorbaProxy : public cProxy  //## Inherits: <unnamed>%3EDB40BD008C
{
  //## begin cCorbaProxy%3EDB31F402EE.initialDeclarations preserve=yes
  //## end cCorbaProxy%3EDB31F402EE.initialDeclarations

  public:
    //## Constructors (generated)
      cCorbaProxy();

      cCorbaProxy(const cCorbaProxy &right);

    //## Destructor (generated)
      virtual ~cCorbaProxy();


    //## Other Operations (specified)
      //## Operation: Serialize%1054547840
      virtual STRING_T Serialize ();

      //## Operation: Construct%1054547841
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IOR%3EDB325600BB
      STRING_T get_IOR () const;
      void set_IOR (STRING_T value);

    // Additional Public Declarations
      //## begin cCorbaProxy%3EDB31F402EE.public preserve=yes
      //## end cCorbaProxy%3EDB31F402EE.public

  protected:

    //## Other Operations (specified)
      //## Operation: SetItf%1054547842
      void SetItf ();

      //## Operation: ReleaseItf%1054547843
      void ReleaseItf ();

    // Data Members for Class Attributes

      //## begin cCorbaProxy::IOR%3EDB325600BB.attr preserve=no  public: STRING_T {U} 
      STRING_T _IOR;
      //## end cCorbaProxy::IOR%3EDB325600BB.attr

    // Additional Protected Declarations
      //## begin cCorbaProxy%3EDB31F402EE.protected preserve=yes
      //## end cCorbaProxy%3EDB31F402EE.protected

  private:
    // Additional Private Declarations
      //## begin cCorbaProxy%3EDB31F402EE.private preserve=yes
      //## end cCorbaProxy%3EDB31F402EE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCorbaProxy%3EDB31F402EE.implementation preserve=yes
      //## end cCorbaProxy%3EDB31F402EE.implementation

};

//## begin cCorbaProxy%3EDB31F402EE.postscript preserve=yes
//## end cCorbaProxy%3EDB31F402EE.postscript

// Class cCorbaProxy 

//## begin module%3EDB31F402EE.epilog preserve=yes
//## end module%3EDB31F402EE.epilog


#endif

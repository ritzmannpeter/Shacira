//## begin module%3EBFAF27035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EBFAF27035B.cm

//## begin module%3EBFAF27035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EBFAF27035B.cp

//## Module: cEventControl%3EBFAF27035B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cEventControl.h

#ifndef cEventControl_h
#define cEventControl_h 1

//## begin module%3EBFAF27035B.includes preserve=yes
//## end module%3EBFAF27035B.includes


class __DLL_EXPORT__ cTransientObject;

//## begin module%3EBFAF27035B.additionalDeclarations preserve=yes
//## end module%3EBFAF27035B.additionalDeclarations


//## begin cEventControl%3EBFAF27035B.preface preserve=yes
//## end cEventControl%3EBFAF27035B.preface

//## Class: cEventControl%3EBFAF27035B
//## Category: Client::Adapters%3DCC05190174
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FBF631C0167;cTransientObject { -> F}

class __DLL_EXPORT__ cEventControl 
{
  //## begin cEventControl%3EBFAF27035B.initialDeclarations preserve=yes
public:
  //## end cEventControl%3EBFAF27035B.initialDeclarations

    //## Constructors (generated)
      cEventControl();

      cEventControl(const cEventControl &right);

    //## Destructor (generated)
      virtual ~cEventControl();


    //## Other Operations (specified)
      //## Operation: Object%1052744774
      virtual void Object (cTransientObject *object);

  public:
    // Additional Public Declarations
      //## begin cEventControl%3EBFAF27035B.public preserve=yes
      //## end cEventControl%3EBFAF27035B.public

  protected:
    // Additional Protected Declarations
      //## begin cEventControl%3EBFAF27035B.protected preserve=yes
      //## end cEventControl%3EBFAF27035B.protected

  private:
    // Additional Private Declarations
      //## begin cEventControl%3EBFAF27035B.private preserve=yes
      //## end cEventControl%3EBFAF27035B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cEventControl%3EBFAF27035B.implementation preserve=yes
      //## end cEventControl%3EBFAF27035B.implementation

};

//## begin cEventControl%3EBFAF27035B.postscript preserve=yes
//## end cEventControl%3EBFAF27035B.postscript

// Class cEventControl 

//## begin module%3EBFAF27035B.epilog preserve=yes
//## end module%3EBFAF27035B.epilog


#endif

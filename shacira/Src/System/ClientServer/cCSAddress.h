//## begin module%410274BB007D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410274BB007D.cm

//## begin module%410274BB007D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%410274BB007D.cp

//## Module: cCSAddress%410274BB007D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cCSAddress.h

#ifndef cCSAddress_h
#define cCSAddress_h 1

//## begin module%410274BB007D.includes preserve=yes
//## end module%410274BB007D.includes

//## begin module%410274BB007D.additionalDeclarations preserve=yes
//## end module%410274BB007D.additionalDeclarations


//## begin cCSAddress%410274BB007D.preface preserve=yes
//## end cCSAddress%410274BB007D.preface

//## Class: cCSAddress%410274BB007D
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCSAddress 
{
  //## begin cCSAddress%410274BB007D.initialDeclarations preserve=yes
public:
  //## end cCSAddress%410274BB007D.initialDeclarations

    //## Constructors (generated)
      cCSAddress();

      cCSAddress(const cCSAddress &right);

    //## Destructor (generated)
      virtual ~cCSAddress();


    //## Other Operations (specified)
      //## Operation: Sender%1090862819
      virtual const char * Sender ();

  public:
    // Additional Public Declarations
      //## begin cCSAddress%410274BB007D.public preserve=yes
      //## end cCSAddress%410274BB007D.public

  protected:
    // Additional Protected Declarations
      //## begin cCSAddress%410274BB007D.protected preserve=yes
      //## end cCSAddress%410274BB007D.protected

  private:
    // Additional Private Declarations
      //## begin cCSAddress%410274BB007D.private preserve=yes
      //## end cCSAddress%410274BB007D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCSAddress%410274BB007D.implementation preserve=yes
      //## end cCSAddress%410274BB007D.implementation

};

//## begin cCSAddress%410274BB007D.postscript preserve=yes
//## end cCSAddress%410274BB007D.postscript

// Class cCSAddress 

//## begin module%410274BB007D.epilog preserve=yes
//## end module%410274BB007D.epilog


#endif

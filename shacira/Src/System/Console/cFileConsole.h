//## begin module%3DD3D0B601DE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3D0B601DE.cm

//## begin module%3DD3D0B601DE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3D0B601DE.cp

//## Module: cFileConsole%3DD3D0B601DE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cFileConsole.h

#ifndef cFileConsole_h
#define cFileConsole_h 1

//## begin module%3DD3D0B601DE.includes preserve=yes
//## end module%3DD3D0B601DE.includes

// cConsole
#include "System/Console/cConsole.h"

class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3DD3D0B601DE.additionalDeclarations preserve=yes
//## end module%3DD3D0B601DE.additionalDeclarations


//## begin cFileConsole%3DD3D0B601DE.preface preserve=yes
//## end cFileConsole%3DD3D0B601DE.preface

//## Class: cFileConsole%3DD3D0B601DE
//## Category: System::Console%3DC92CF602A4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD3D367035B;cFileSystemUtils { -> F}

class __DLL_EXPORT__ cFileConsole : public cConsole  //## Inherits: <unnamed>%3DD3D11A03E1
{
  //## begin cFileConsole%3DD3D0B601DE.initialDeclarations preserve=yes
public:
  //## end cFileConsole%3DD3D0B601DE.initialDeclarations

    //## Constructors (generated)
      cFileConsole();

      cFileConsole(const cFileConsole &right);

    //## Constructors (specified)
      //## Operation: cFileConsole%1037286975
      cFileConsole (CONST_STRING_T file_name);

    //## Destructor (generated)
      virtual ~cFileConsole();


    //## Other Operations (specified)
      //## Operation: Write%1037286976
      virtual void Write (CONST_STRING_T text);

      //## Operation: Read%1037286977
      virtual LONG_T Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout = 0);

      //## Operation: FlushInput%1037286978
      virtual void FlushInput ();

      //## Operation: FlushOutput%1037286979
      virtual void FlushOutput ();

  public:
    // Additional Public Declarations
      //## begin cFileConsole%3DD3D0B601DE.public preserve=yes
      //## end cFileConsole%3DD3D0B601DE.public

  protected:
    // Additional Protected Declarations
      //## begin cFileConsole%3DD3D0B601DE.protected preserve=yes
      //## end cFileConsole%3DD3D0B601DE.protected

  private:
    // Additional Private Declarations
      //## begin cFileConsole%3DD3D0B601DE.private preserve=yes
      //## end cFileConsole%3DD3D0B601DE.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: File%3DD3D18603E6
      //## begin cFileConsole::File%3DD3D18603E6.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _File;
      //## end cFileConsole::File%3DD3D18603E6.attr

    // Additional Implementation Declarations
      //## begin cFileConsole%3DD3D0B601DE.implementation preserve=yes
      //## end cFileConsole%3DD3D0B601DE.implementation

};

//## begin cFileConsole%3DD3D0B601DE.postscript preserve=yes
//## end cFileConsole%3DD3D0B601DE.postscript

// Class cFileConsole 

//## begin module%3DD3D0B601DE.epilog preserve=yes
//## end module%3DD3D0B601DE.epilog


#endif

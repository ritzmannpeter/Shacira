//## begin module%3D413C3F0290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D413C3F0290.cm

//## begin module%3D413C3F0290.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D413C3F0290.cp

//## Module: cStandardConsole%3D413C3F0290; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cStandardConsole.h

#ifndef cStandardConsole_h
#define cStandardConsole_h 1

//## begin module%3D413C3F0290.includes preserve=yes
//## end module%3D413C3F0290.includes

// cConsole
#include "System/Console/cConsole.h"
//## begin module%3D413C3F0290.additionalDeclarations preserve=yes
//## end module%3D413C3F0290.additionalDeclarations


//## begin cStandardConsole%3D413C3F0290.preface preserve=yes
//## end cStandardConsole%3D413C3F0290.preface

//## Class: cStandardConsole%3D413C3F0290
//## Category: System::Console%3DC92CF602A4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cStandardConsole : public cConsole  //## Inherits: <unnamed>%3D413C5F00CA
{
  //## begin cStandardConsole%3D413C3F0290.initialDeclarations preserve=yes
public:
  //## end cStandardConsole%3D413C3F0290.initialDeclarations

    //## Constructors (generated)
      cStandardConsole();

      cStandardConsole(const cStandardConsole &right);

    //## Constructors (specified)
      //## Operation: cStandardConsole%1027676084
      cStandardConsole (FILE *stream, INT_T direction = DIRECTION_OUTPUT);

    //## Destructor (generated)
      virtual ~cStandardConsole();


    //## Other Operations (specified)
      //## Operation: Write%1037267664
      virtual void Write (CONST_STRING_T text);

      //## Operation: Read%1037267665
      virtual LONG_T Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout = 0);

      //## Operation: FlushInput%1037267667
      virtual void FlushInput ();

      //## Operation: FlushOutput%1037267668
      virtual void FlushOutput ();

  public:
    // Additional Public Declarations
      //## begin cStandardConsole%3D413C3F0290.public preserve=yes
      //## end cStandardConsole%3D413C3F0290.public

  protected:
    // Additional Protected Declarations
      //## begin cStandardConsole%3D413C3F0290.protected preserve=yes
      //## end cStandardConsole%3D413C3F0290.protected

  private:
    // Additional Private Declarations
      //## begin cStandardConsole%3D413C3F0290.private preserve=yes
      //## end cStandardConsole%3D413C3F0290.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Stream%3D413D1202EE
      //## begin cStandardConsole::Stream%3D413D1202EE.attr preserve=no  implementation: FILE * {U} NULL
      FILE *_Stream;
      //## end cStandardConsole::Stream%3D413D1202EE.attr

    // Additional Implementation Declarations
      //## begin cStandardConsole%3D413C3F0290.implementation preserve=yes
      //## end cStandardConsole%3D413C3F0290.implementation

};

//## begin cStandardConsole%3D413C3F0290.postscript preserve=yes
//## end cStandardConsole%3D413C3F0290.postscript

// Class cStandardConsole 

//## begin module%3D413C3F0290.epilog preserve=yes
//## end module%3D413C3F0290.epilog


#endif

//## begin module%3D402C9600B0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D402C9600B0.cm

//## begin module%3D402C9600B0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D402C9600B0.cp

//## Module: cConsole%3D402C9600B0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cConsole.h

#ifndef cConsole_h
#define cConsole_h 1

//## begin module%3D402C9600B0.includes preserve=yes
//## end module%3D402C9600B0.includes

// cStaticObject
#include "System/Objects/cStaticObject.h"
//## begin module%3D402C9600B0.additionalDeclarations preserve=yes

#define DIRECTION_INPUT    0
#define DIRECTION_OUTPUT   1
#define DIRECTION_BOTH     2

#define CHECK_DIRECTION(direction) \
if (_Direction != DIRECTION_BOTH && _Direction != direction) throw cError(CONSOLE_INVALID_DIRECTION, 0, _Name.c_str()); 

//## end module%3D402C9600B0.additionalDeclarations


//## begin cConsole%3D402C9600B0.preface preserve=yes
//## end cConsole%3D402C9600B0.preface

//## Class: cConsole%3D402C9600B0
//## Category: System::Console%3DC92CF602A4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cConsole : public cStaticObject  //## Inherits: <unnamed>%3DD37BFB01D4
{
  //## begin cConsole%3D402C9600B0.initialDeclarations preserve=yes
public:
  //## end cConsole%3D402C9600B0.initialDeclarations

    //## Constructors (generated)
      cConsole();

      cConsole(const cConsole &right);

    //## Constructors (specified)
      //## Operation: cConsole%1037267669
      cConsole (INT_T direction);

    //## Destructor (generated)
      virtual ~cConsole();


    //## Other Operations (specified)
      //## Operation: Write%1027605558
      virtual void Write (CONST_STRING_T text);

      //## Operation: Read%1037267666
      virtual LONG_T Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout = 0);

      //## Operation: FlushInput%1037267670
      virtual void FlushInput ();

      //## Operation: FlushOutput%1037267671
      virtual void FlushOutput ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Direction%3DD378E900BB
      INT_T get_Direction () const;

  public:
    // Additional Public Declarations
      //## begin cConsole%3D402C9600B0.public preserve=yes
      //## end cConsole%3D402C9600B0.public

  protected:
    // Data Members for Class Attributes

      //## begin cConsole::Direction%3DD378E900BB.attr preserve=no  public: INT_T {U} 
      INT_T _Direction;
      //## end cConsole::Direction%3DD378E900BB.attr

    // Additional Protected Declarations
      //## begin cConsole%3D402C9600B0.protected preserve=yes
      //## end cConsole%3D402C9600B0.protected

  private:
    // Additional Private Declarations
      //## begin cConsole%3D402C9600B0.private preserve=yes
      //## end cConsole%3D402C9600B0.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cConsole%3D402C9600B0.implementation preserve=yes
      //## end cConsole%3D402C9600B0.implementation

};

//## begin cConsole%3D402C9600B0.postscript preserve=yes
//## end cConsole%3D402C9600B0.postscript

// Class cConsole 

//## begin module%3D402C9600B0.epilog preserve=yes
//## end module%3D402C9600B0.epilog


#endif

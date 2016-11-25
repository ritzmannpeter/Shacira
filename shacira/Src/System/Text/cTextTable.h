//## begin module%412B31000119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412B31000119.cm

//## begin module%412B31000119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412B31000119.cp

//## Module: cTextTable%412B31000119; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Text\cTextTable.h

#ifndef cTextTable_h
#define cTextTable_h 1

//## begin module%412B31000119.includes preserve=yes

#include "System/Text/SystemText.h"

//## end module%412B31000119.includes

// eb_sema
#include "base/eb_sema.hpp"

class __DLL_EXPORT__ cObjectLock;

//## begin module%412B31000119.additionalDeclarations preserve=yes
//## end module%412B31000119.additionalDeclarations


//## begin cTextTable%412B31000119.preface preserve=yes
//## end cTextTable%412B31000119.preface

//## Class: cTextTable%412B31000119
//## Category: System::Text%412B30C4000F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%424A62740242;cMutexSem { -> }
//## Uses: <unnamed>%424A6295001F;cObjectLock { -> F}

class __DLL_EXPORT__ cTextTable 
{
  //## begin cTextTable%412B31000119.initialDeclarations preserve=yes
public:
  //## end cTextTable%412B31000119.initialDeclarations

    //## Constructors (generated)
      cTextTable();

      cTextTable(const cTextTable &right);

    //## Constructors (specified)
      //## Operation: cTextTable%1093344846
      cTextTable (TEXT_ENTRY_T *table);

    //## Destructor (generated)
      virtual ~cTextTable();


    //## Other Operations (specified)
      //## Operation: GetText%1093344844
      virtual CONST_STRING_T GetText (ULONG_T text_id);

  public:
    // Additional Public Declarations
      //## begin cTextTable%412B31000119.public preserve=yes
      //## end cTextTable%412B31000119.public

  protected:
    // Additional Protected Declarations
      //## begin cTextTable%412B31000119.protected preserve=yes
      //## end cTextTable%412B31000119.protected

  private:
    // Additional Private Declarations
      //## begin cTextTable%412B31000119.private preserve=yes
      //## end cTextTable%412B31000119.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: LoadTable%1093344847
      void LoadTable (TEXT_ENTRY_T *table);

    // Data Members for Class Attributes

      //## Attribute: Min%412B417303A9
      //## begin cTextTable::Min%412B417303A9.attr preserve=no  private: ULONG_T {U} 0xffffffff
      ULONG_T _Min;
      //## end cTextTable::Min%412B417303A9.attr

      //## Attribute: Max%412B418F02BF
      //## begin cTextTable::Max%412B418F02BF.attr preserve=no  private: ULONG_T {U} 0
      ULONG_T _Max;
      //## end cTextTable::Max%412B418F02BF.attr

      //## Attribute: Size%412B41A0035B
      //## begin cTextTable::Size%412B41A0035B.attr preserve=no  private: ULONG_T {U} 0
      ULONG_T _Size;
      //## end cTextTable::Size%412B41A0035B.attr

      //## Attribute: StringTable%412B41B503C8
      //## begin cTextTable::StringTable%412B41B503C8.attr preserve=no  private: CONST_STRING_T * {U} NULL
      CONST_STRING_T *_StringTable;
      //## end cTextTable::StringTable%412B41B503C8.attr

      //## Attribute: TableMutex%424A624002DE
      //## begin cTextTable::TableMutex%424A624002DE.attr preserve=no  private: cMutexSem {U} 
      cMutexSem _TableMutex;
      //## end cTextTable::TableMutex%424A624002DE.attr

    // Additional Implementation Declarations
      //## begin cTextTable%412B31000119.implementation preserve=yes
      //## end cTextTable%412B31000119.implementation

};

//## begin cTextTable%412B31000119.postscript preserve=yes
//## end cTextTable%412B31000119.postscript

// Class cTextTable 

//## begin module%412B31000119.epilog preserve=yes
//## end module%412B31000119.epilog


#endif

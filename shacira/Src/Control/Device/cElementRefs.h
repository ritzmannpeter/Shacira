//## begin module%3FE1928F0203.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE1928F0203.cm

//## begin module%3FE1928F0203.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE1928F0203.cp

//## Module: cElementRefs%3FE1928F0203; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cElementRefs.h

#ifndef cElementRefs_h
#define cElementRefs_h 1

//## begin module%3FE1928F0203.includes preserve=yes
//## end module%3FE1928F0203.includes

// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cPtrList;
class __DLL_EXPORT__ cLocalVariable;

//## begin module%3FE1928F0203.additionalDeclarations preserve=yes

typedef std::map<STRING_T,cPtrList*> NAME_MAP_T;
typedef std::map<ULONG_T,cPtrList*> ADDRESS_MAP_T;

//## end module%3FE1928F0203.additionalDeclarations


//## begin cElementRefs%3FE1928F0203.preface preserve=yes
//## end cElementRefs%3FE1928F0203.preface

//## Class: cElementRefs%3FE1928F0203; implementation
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FE1942901B5;cPtrList { -> F}
//## Uses: <unnamed>%3FE1943B0119;cDevice { -> }
//## Uses: <unnamed>%3FE1945802BF;cLocalVariable { -> F}

class __DLL_EXPORT__ cElementRefs 
{
  //## begin cElementRefs%3FE1928F0203.initialDeclarations preserve=yes
public:
  //## end cElementRefs%3FE1928F0203.initialDeclarations

    //## Constructors (generated)
      cElementRefs();

      cElementRefs(const cElementRefs &right);

    //## Destructor (generated)
      virtual ~cElementRefs();


    //## Other Operations (specified)
      //## Operation: AddRef%1071741897
      void AddRef (ULONG_T address, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: AddRef%1071741898
      void AddRef (CONST_STRING_T name, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: GetRefs%1071741899
      virtual cPtrList * GetRefs (ULONG_T address);

      //## Operation: GetRefs%1071741900
      virtual cPtrList * GetRefs (CONST_STRING_T name);

  public:
    // Additional Public Declarations
      //## begin cElementRefs%3FE1928F0203.public preserve=yes
      //## end cElementRefs%3FE1928F0203.public

  protected:
    // Additional Protected Declarations
      //## begin cElementRefs%3FE1928F0203.protected preserve=yes
      //## end cElementRefs%3FE1928F0203.protected

  private:
    // Additional Private Declarations
      //## begin cElementRefs%3FE1928F0203.private preserve=yes
      //## end cElementRefs%3FE1928F0203.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: NameMap%3FE19BA0033C
      //## begin cElementRefs::NameMap%3FE19BA0033C.attr preserve=no  private: NAME_MAP_T {U} 
      NAME_MAP_T _NameMap;
      //## end cElementRefs::NameMap%3FE19BA0033C.attr

      //## Attribute: AddressMap%3FE19BC002AF
      //## begin cElementRefs::AddressMap%3FE19BC002AF.attr preserve=no  private: ADDRESS_MAP_T {U} 
      ADDRESS_MAP_T _AddressMap;
      //## end cElementRefs::AddressMap%3FE19BC002AF.attr

    // Additional Implementation Declarations
      //## begin cElementRefs%3FE1928F0203.implementation preserve=yes
      //## end cElementRefs%3FE1928F0203.implementation

};

//## begin cElementRefs%3FE1928F0203.postscript preserve=yes
//## end cElementRefs%3FE1928F0203.postscript

// Class cElementRefs 

//## begin module%3FE1928F0203.epilog preserve=yes
//## end module%3FE1928F0203.epilog


#endif

//## begin module%3E00548802D6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00548802D6.cm

//## begin module%3E00548802D6.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00548802D6.cp

//## Module: cMapping%3E00548802D6; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cMapping.h

#ifndef cMapping_h
#define cMapping_h 1

//## begin module%3E00548802D6.includes preserve=yes
//## end module%3E00548802D6.includes

// cVarDef
#include "System/Database/cVarDef.h"

class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cDevice;

//## begin module%3E00548802D6.additionalDeclarations preserve=yes

#define UNUSED_ADDRESS ((ULONG_T)0xFFFFFFFF)
#define UNUSED_BITPOS  ((UCHAR_T)0xFF)
#define NOT_CACHED     ((ULONG_T)0)

typedef struct map_item {
   CONST_STRING_T device_name;
   cDevice * device;
   CONST_STRING_T buf_spec;
   UCHAR_T data_type;
   ULONG_T size;
   ULONG_T address;
   CONST_STRING_T name;
   UCHAR_T bit_pos_b;
   UCHAR_T bit_pos_e;
   cVarDef * var_def;
   ULONG_T pos;
   BOOL_T enabled;
}  MAP_ITEM_T;

//## end module%3E00548802D6.additionalDeclarations


//## begin cMapping%3E00548802D6.preface preserve=yes
//## end cMapping%3E00548802D6.preface

//## Class: cMapping%3E00548802D6
//	Implements a mapping object, that holds the mapping
//	information of a variable definition.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FD98E7C008C;cDevice { -> F}
//## Uses: <unnamed>%411A44C20213;cVarDef { -> }

class __DLL_EXPORT__ cMapping 
{
  //## begin cMapping%3E00548802D6.initialDeclarations preserve=yes
public:
  //## end cMapping%3E00548802D6.initialDeclarations

    //## Constructors (generated)
      cMapping();

      cMapping(const cMapping &right);

    //## Constructors (specified)
      //## Operation: cMapping%1071222102
      cMapping (ULONG_T item_count);

    //## Destructor (generated)
      virtual ~cMapping();


    //## Other Operations (specified)
      //## Operation: SetConvFunc%1041236870
      void SetConvFunc (cFuncRef *conv_func);

      //## Operation: SetItem%1071222103
      void SetItem (ULONG_T pos, MAP_ITEM_T *item);

      //## Operation: MapItem%1042459999
      MAP_ITEM_T * MapItem (ULONG_T pos);

    // Data Members for Class Attributes

      //## Attribute: PhysSpec%3E22ED590002
      //## begin cMapping::PhysSpec%3E22ED590002.attr preserve=no  public: STRING_T {U} 
      STRING_T _PhysSpec;
      //## end cMapping::PhysSpec%3E22ED590002.attr

      //## Attribute: DataType%3E22AE4903C0
      //## begin cMapping::DataType%3E22AE4903C0.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cMapping::DataType%3E22AE4903C0.attr

      //## Attribute: Length%3FD9970C0242
      //## begin cMapping::Length%3FD9970C0242.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _Length;
      //## end cMapping::Length%3FD9970C0242.attr

      //## Attribute: Precision%4242D1600128
      //## begin cMapping::Precision%4242D1600128.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _Precision;
      //## end cMapping::Precision%4242D1600128.attr

      //## Attribute: ItemCount%3E22AE4903CA
      //## begin cMapping::ItemCount%3E22AE4903CA.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _ItemCount;
      //## end cMapping::ItemCount%3E22AE4903CA.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E14047B0224
      //## Role: cMapping::ConvFunc%3E14047C01A3
      //## begin cMapping::ConvFunc%3E14047C01A3.role preserve=no  public: cFuncRef { -> 0..1RFHN}
      cFuncRef *_ConvFunc;
      //## end cMapping::ConvFunc%3E14047C01A3.role

  public:
    // Additional Public Declarations
      //## begin cMapping%3E00548802D6.public preserve=yes
      //## end cMapping%3E00548802D6.public

  protected:
    // Additional Protected Declarations
      //## begin cMapping%3E00548802D6.protected preserve=yes
      //## end cMapping%3E00548802D6.protected

  private:
    // Additional Private Declarations
      //## begin cMapping%3E00548802D6.private preserve=yes
      //## end cMapping%3E00548802D6.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: MapItems%3FD98D3400AB
      //## begin cMapping::MapItems%3FD98D3400AB.attr preserve=no  implementation: MAP_ITEM_T ** {U} NULL
      MAP_ITEM_T **_MapItems;
      //## end cMapping::MapItems%3FD98D3400AB.attr

    // Additional Implementation Declarations
      //## begin cMapping%3E00548802D6.implementation preserve=yes
      //## end cMapping%3E00548802D6.implementation

};

//## begin cMapping%3E00548802D6.postscript preserve=yes
//## end cMapping%3E00548802D6.postscript

// Class cMapping 

//## begin module%3E00548802D6.epilog preserve=yes
//## end module%3E00548802D6.epilog


#endif

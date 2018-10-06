//## begin module%3E003A1F00CC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E003A1F00CC.cm

//## begin module%3E003A1F00CC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E003A1F00CC.cp

//## Module: cRemoteVar%3E003A1F00CC; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\RemoteDatabase\cRemoteVar.h

#ifndef cRemoteVar_h
#define cRemoteVar_h 1

//## begin module%3E003A1F00CC.includes preserve=yes
//## end module%3E003A1F00CC.includes

// cVariable
#include "System/Database/cVariable.h"

class __DLL_EXPORT__ cCellProxy;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cRemoteContext;

//## begin module%3E003A1F00CC.additionalDeclarations preserve=yes
//## end module%3E003A1F00CC.additionalDeclarations


//## begin cRemoteVar%3E003A1F00CC.preface preserve=yes
//## end cRemoteVar%3E003A1F00CC.preface

//## Class: cRemoteVar%3E003A1F00CC
//## Category: Client::RemoteDatabase%3DFF22EE0346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E25936D018B;cVarDef { -> F}
//## Uses: <unnamed>%3EDDD3CE029F;cRemoteContext { -> F}
//## Uses: <unnamed>%411A11E0031C;cSHVariant { -> F}

class __DLL_EXPORT__ cRemoteVar : public cVariable  //## Inherits: <unnamed>%3E003A4D00D2
{
  //## begin cRemoteVar%3E003A1F00CC.initialDeclarations preserve=yes
public:
  //## end cRemoteVar%3E003A1F00CC.initialDeclarations

    //## Constructors (generated)
      cRemoteVar();

      cRemoteVar(const cRemoteVar &right);

    //## Constructors (specified)
      //## Operation: cRemoteVar%1040202765
      cRemoteVar (cVarDef *var_def, cCellProxy *cellProxy=NULL);

    //## Destructor (generated)
      virtual ~cRemoteVar();


    //## Other Operations (specified)
      //## Operation: Get%1071244182
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244183
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244184
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244185
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244186
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244187
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244188
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244189
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244190
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244191
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244192
      virtual void Get (BUF_T &buf_ptr, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void Get (BUF_T &buf_ptr, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244193
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Refresh%1133172777
      virtual void Refresh (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244194
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244195
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244196
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244197
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244198
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244199
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244200
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244201
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244202
      virtual void Set (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244203
      virtual void Set (CONST_WSTRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244204
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMinimum%1089103319
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103320
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103321
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103322
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089203190
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103323
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103324
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103325
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103326
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetObject%1238436648
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436649
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMaximum%1089203191
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

    // Data Members for Associations

      //## Association: Client::RemoteDatabase::<unnamed>%3E258EC302F7
      //## Role: cRemoteVar::CellProxy%3E258EC5008D
      //## begin cRemoteVar::CellProxy%3E258EC5008D.role preserve=no  public: cCellProxy { -> 1RFHN}
      cCellProxy *_CellProxy;
      //## end cRemoteVar::CellProxy%3E258EC5008D.role

  public:
    // Additional Public Declarations
      //## begin cRemoteVar%3E003A1F00CC.public preserve=yes
      //## end cRemoteVar%3E003A1F00CC.public

  protected:
    // Additional Protected Declarations
      //## begin cRemoteVar%3E003A1F00CC.protected preserve=yes
      //## end cRemoteVar%3E003A1F00CC.protected

  private:
    // Additional Private Declarations
      //## begin cRemoteVar%3E003A1F00CC.private preserve=yes
      //## end cRemoteVar%3E003A1F00CC.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetMemoryType%1092218358
      //	This method filters remote buffer access to memory type
      //	variables.
      BOOL_T GetMemoryType (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMemoryType%1092218355
      //	This method filters remote buffer access to memory type
      //	variables.
      BOOL_T GetMemoryType (BUF_T &buf_ptr, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMemoryType%1092218356
      //	This method filters remote buffer access to memory type
      //	variables.
      BOOL_T GetMemoryType (BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetMemoryType%1092218357
      //	This method filters string based set access to memory
      //	type variables.
      BOOL_T SetMemoryType (CONST_WSTRING_T value, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetMemoryType%1092218359
      //	This method filters string based set access to memory
      //	type variables.
      BOOL_T SetMemoryType (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

    // Additional Implementation Declarations
      //## begin cRemoteVar%3E003A1F00CC.implementation preserve=yes
      //## end cRemoteVar%3E003A1F00CC.implementation

};

//## begin cRemoteVar%3E003A1F00CC.postscript preserve=yes
//## end cRemoteVar%3E003A1F00CC.postscript

// Class cRemoteVar 

//## begin module%3E003A1F00CC.epilog preserve=yes
//## end module%3E003A1F00CC.epilog


#endif

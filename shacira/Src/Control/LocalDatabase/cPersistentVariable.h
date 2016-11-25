//## begin module%444727B902E0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%444727B902E0.cm

//## begin module%444727B902E0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%444727B902E0.cp

//## Module: cPersistentVariable%444727B902E0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistentVariable.h

#ifndef cPersistentVariable_h
#define cPersistentVariable_h 1

//## begin module%444727B902E0.includes preserve=yes
//## end module%444727B902E0.includes

// cVariable
#include "System/Database/cVariable.h"

class __DLL_EXPORT__ cVarDef;

//## begin module%444727B902E0.additionalDeclarations preserve=yes
//## end module%444727B902E0.additionalDeclarations


//## begin cPersistentVariable%444727B902E0.preface preserve=yes
//## end cPersistentVariable%444727B902E0.preface

//## Class: cPersistentVariable%444727B902E0
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%444727B902E2;cVarDef { -> F}

class __DLL_EXPORT__ cPersistentVariable : public cVariable  //## Inherits: <unnamed>%444727B902E1
{
  //## begin cPersistentVariable%444727B902E0.initialDeclarations preserve=yes
public:
  //## end cPersistentVariable%444727B902E0.initialDeclarations

    //## Constructors (generated)
      cPersistentVariable();

      cPersistentVariable(const cPersistentVariable &right);

    //## Constructors (specified)
      //## Operation: cPersistentVariable%1145514031
      cPersistentVariable (cVarDef *var_def, void *buf, ULONG_T buf_size);

    //## Destructor (generated)
      virtual ~cPersistentVariable();


    //## Other Operations (specified)
      //## Operation: Get%1145514032
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514033
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514034
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514035
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514036
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514037
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514038
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514039
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514040
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514041
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514042
      virtual void Get (BUF_T &buf_ptr, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void Get (BUF_T &buf, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1145514043
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514044
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514045
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514046
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514047
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514048
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514049
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514050
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514051
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514052
      virtual void Set (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514053
      virtual void Set (CONST_WSTRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1145514054
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMinimum%1145514055
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1145514056
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1145514057
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1145514058
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1145514059
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1145514060
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1145514061
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1145514062
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1145514063
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1145514064
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: SetDataType%1170178870
      void SetDataType (UCHAR_T data_type);

      //## Operation: GetObject%1238436646
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436647
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

  public:
    // Additional Public Declarations
      //## begin cPersistentVariable%444727B902E0.public preserve=yes
     BUF_T Buffer() const {return _Buffer;};
      //## end cPersistentVariable%444727B902E0.public

  protected:
    // Additional Protected Declarations
      //## begin cPersistentVariable%444727B902E0.protected preserve=yes
      //## end cPersistentVariable%444727B902E0.protected

  private:
    // Additional Private Declarations
      //## begin cPersistentVariable%444727B902E0.private preserve=yes
      //## end cPersistentVariable%444727B902E0.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Buffer%444727B903C7
      //## begin cPersistentVariable::Buffer%444727B903C7.attr preserve=no  implementation: BUF_T {U} NULL
      BUF_T _Buffer;
      //## end cPersistentVariable::Buffer%444727B903C7.attr

      //## Attribute: BufSize%444727B903C8
      //## begin cPersistentVariable::BufSize%444727B903C8.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _BufSize;
      //## end cPersistentVariable::BufSize%444727B903C8.attr

    // Additional Implementation Declarations
      //## begin cPersistentVariable%444727B902E0.implementation preserve=yes
      //## end cPersistentVariable%444727B902E0.implementation

};

//## begin cPersistentVariable%444727B902E0.postscript preserve=yes
//## end cPersistentVariable%444727B902E0.postscript

// Class cPersistentVariable 

//## begin module%444727B902E0.epilog preserve=yes
//## end module%444727B902E0.epilog


#endif


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cPersistentVariable%4445FA940138.initialDeclarations preserve=no
public:
//## end cPersistentVariable%4445FA940138.initialDeclarations

#endif

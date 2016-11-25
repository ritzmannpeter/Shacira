//## begin module%4113C89D00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4113C89D00AB.cm

//## begin module%4113C89D00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4113C89D00AB.cp

//## Module: cFileVariable%4113C89D00AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFileVariable.h

#ifndef cFileVariable_h
#define cFileVariable_h 1

//## begin module%4113C89D00AB.includes preserve=yes
//## end module%4113C89D00AB.includes

// cVariable
#include "System/Database/cVariable.h"

class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cVariableValues;

//## begin module%4113C89D00AB.additionalDeclarations preserve=yes
//## end module%4113C89D00AB.additionalDeclarations


//## begin cFileVariable%4113C89D00AB.preface preserve=yes
//## end cFileVariable%4113C89D00AB.preface

//## Class: cFileVariable%4113C89D00AB
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4113D175032C;cVarDef { -> F}
//## Uses: <unnamed>%4115FF72007D;cVariableValues { -> F}

class __DLL_EXPORT__ cFileVariable : public cVariable  //## Inherits: <unnamed>%4113C8B70271
{
  //## begin cFileVariable%4113C89D00AB.initialDeclarations preserve=yes
public:
  //## end cFileVariable%4113C89D00AB.initialDeclarations

    //## Constructors (generated)
      cFileVariable();

      cFileVariable(const cFileVariable &right);

    //## Constructors (specified)
      //## Operation: cFileVariable%1091815614
      cFileVariable (cVarDef *var_def);

    //## Destructor (generated)
      virtual ~cFileVariable();


    //## Other Operations (specified)
      //## Operation: UnitText%1111426862
      //	Returns the string that contains the current physical
      //	dimension of a variable.
      virtual STRING_T UnitText ();

      //## Operation: Get%1091815650
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815651
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815652
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815653
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815654
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815655
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815656
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815657
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815658
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815659
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815660
      virtual void Get (BUF_T &buf, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void Get (BUF_T &buf, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1091815661
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815662
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815663
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815664
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815665
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815666
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815667
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815668
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815669
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815670
      virtual void Set (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815671
      virtual void Set (CONST_WSTRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1091815672
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMinimum%1091815677
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1091815678
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1091815679
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1091815680
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1091815681
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1091815682
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1091815683
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1091815684
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1091815685
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1091815686
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetObject%1238436640
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436641
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

  public:
    // Additional Public Declarations
      //## begin cFileVariable%4113C89D00AB.public preserve=yes
      //## end cFileVariable%4113C89D00AB.public

  protected:
    // Additional Protected Declarations
      //## begin cFileVariable%4113C89D00AB.protected preserve=yes
      //## end cFileVariable%4113C89D00AB.protected

  private:
    // Additional Private Declarations
      //## begin cFileVariable%4113C89D00AB.private preserve=yes
      //## end cFileVariable%4113C89D00AB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFileVariable%4113C89D00AB.implementation preserve=yes
      //## end cFileVariable%4113C89D00AB.implementation

};

//## begin cFileVariable%4113C89D00AB.postscript preserve=yes
//## end cFileVariable%4113C89D00AB.postscript

// Class cFileVariable 

//## begin module%4113C89D00AB.epilog preserve=yes
//## end module%4113C89D00AB.epilog


#endif

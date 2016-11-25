//## begin module%3F39224B03B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F39224B03B9.cm

//## begin module%3F39224B03B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F39224B03B9.cp

//## Module: cStateVariable%3F39224B03B9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cStateVariable.h

#ifndef cStateVariable_h
#define cStateVariable_h 1

//## begin module%3F39224B03B9.includes preserve=yes
//## end module%3F39224B03B9.includes

// cVariable
#include "System/Database/cVariable.h"

class __DLL_EXPORT__ cControlState;

//## begin module%3F39224B03B9.additionalDeclarations preserve=yes
//## end module%3F39224B03B9.additionalDeclarations


//## begin cStateVariable%3F39224B03B9.preface preserve=yes
//## end cStateVariable%3F39224B03B9.preface

//## Class: cStateVariable%3F39224B03B9
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cStateVariable : public cVariable  //## Inherits: <unnamed>%3F392279029F
{
  //## begin cStateVariable%3F39224B03B9.initialDeclarations preserve=yes
public:
  //## end cStateVariable%3F39224B03B9.initialDeclarations

    //## Constructors (generated)
      cStateVariable();

      cStateVariable(const cStateVariable &right);

    //## Constructors (specified)
      //## Operation: cStateVariable%1060709190
      cStateVariable (cVarDef *var_def, cControlState *state);

    //## Destructor (generated)
      virtual ~cStateVariable();


    //## Other Operations (specified)
      //## Operation: ValueSize%1071244257
      ULONG_T ValueSize ();

      //## Operation: Get%1060709191
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709192
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709193
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709194
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709195
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709196
      //	Retrieves the value of a variable specified by name and
      //	indices into a long.
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709197
      //	Retrieves the value of a variable specified by name and
      //	indices into a double.
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709198
      //	Retrieves the value of a variable specified by name and
      //	indices into a double.
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709199
      //	Retrieves the value of a variable specified by name and
      //	indices into a double.
      virtual void Get (UCHAR_T *buf, ULONG_T buf_len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709200
      //	Retrieves the value of a variable specified by name and
      //	indices into a string.
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1060709201
      //	Retrieves the value of a variable specified by name and
      //	indices into a string.
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244251
      virtual void Get (BUF_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void Get (BUF_T &buf, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244252
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709202
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709203
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a double value.
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709204
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a double value.
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709205
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709206
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a signed long value.
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709207
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a double value.
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709208
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709209
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709210
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (UCHAR_T *value, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709211
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (CHAR_T *value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709212
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (const CHAR_T *value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709213
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (WCHAR_T *value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1060709214
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a conatant string value.
      virtual void Set (const WCHAR_T *value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244253
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMinimum%1089103351
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103352
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103353
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103354
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089203194
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103355
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103356
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103357
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103358
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089203195
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetObject%1238436642
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436643
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

  public:
    // Additional Public Declarations
      //## begin cStateVariable%3F39224B03B9.public preserve=yes
      //## end cStateVariable%3F39224B03B9.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F392513002E
      //## Role: cStateVariable::State%3F392514029F
      //## begin cStateVariable::State%3F392514029F.role preserve=no  public: cControlState { -> 1RFHN}
      cControlState *_State;
      //## end cStateVariable::State%3F392514029F.role

    // Additional Protected Declarations
      //## begin cStateVariable%3F39224B03B9.protected preserve=yes
      //## end cStateVariable%3F39224B03B9.protected

  private:
    // Additional Private Declarations
      //## begin cStateVariable%3F39224B03B9.private preserve=yes
      //## end cStateVariable%3F39224B03B9.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cStateVariable%3F39224B03B9.implementation preserve=yes
      //## end cStateVariable%3F39224B03B9.implementation

};

//## begin cStateVariable%3F39224B03B9.postscript preserve=yes
//## end cStateVariable%3F39224B03B9.postscript

// Class cStateVariable 

//## begin module%3F39224B03B9.epilog preserve=yes
//## end module%3F39224B03B9.epilog


#endif

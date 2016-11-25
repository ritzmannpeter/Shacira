//## begin module%3F4A3223032C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4A3223032C.cm

//## begin module%3F4A3223032C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F4A3223032C.cp

//## Module: cVariant%3F4A3223032C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cVariant.h

#ifndef cVariant_h
#define cVariant_h 1

//## begin module%3F4A3223032C.includes preserve=yes
//## end module%3F4A3223032C.includes

//## begin module%3F4A3223032C.additionalDeclarations preserve=yes
//## end module%3F4A3223032C.additionalDeclarations


//## begin cVariant%3F4A3223032C.preface preserve=yes
//## end cVariant%3F4A3223032C.preface

//## Class: cVariant%3F4A3223032C
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cVariant 
{
  //## begin cVariant%3F4A3223032C.initialDeclarations preserve=yes
public:
  //## end cVariant%3F4A3223032C.initialDeclarations

    //## Constructors (generated)
      cVariant();

      cVariant(const cVariant &right);

    //## Constructors (specified)
      //## Operation: cVariant%1061986944
      cVariant (CHAR_T value);

      //## Operation: cVariant%1061986945
      cVariant (UCHAR_T value);

      //## Operation: cVariant%1061986946
      cVariant (SHORT_T value);

      //## Operation: cVariant%1061986947
      cVariant (USHORT_T value);

      //## Operation: cVariant%1061824381
      cVariant (LONG_T value);

      //## Operation: cVariant%1061986948
      cVariant (ULONG_T value);

      //## Operation: cVariant%1061829456
      cVariant (FLOAT_T value);

      //## Operation: cVariant%1061829457
      cVariant (DOUBLE_T value);

      //## Operation: cVariant%1061986955
      cVariant (STRING_T value);

      //## Operation: cVariant%1061986956
      cVariant (WSTRING_T value);

      //## Operation: cVariant%1061986957
      cVariant (CONST_WSTRING_T value);

      //## Operation: cVariant%1061986958
      cVariant (CONST_STRING_T value);

    //## Destructor (generated)
      virtual ~cVariant();


    //## Other Operations (specified)
      //## Operation: DataType%1061829452
      UCHAR_T DataType ();

      //## Operation: DataType%1061829454
      void DataType (UCHAR_T data_type);

      //## Operation: operator CHAR_T%1061986949
      operator CHAR_T ();

      //## Operation: operator UCHAR_T%1061986950
      operator UCHAR_T ();

      //## Operation: operator SHORT_T%1061986951
      operator SHORT_T ();

      //## Operation: operator USHORT_T%1061986952
      operator USHORT_T ();

      //## Operation: operator LONG_T%1061829453
      operator LONG_T ();

      //## Operation: operator ULONG_T%1061986953
      operator ULONG_T ();

      //## Operation: operator FLOAT_T%1061829458
      operator FLOAT_T ();

      //## Operation: operator DOUBLE_T%1061986954
      operator DOUBLE_T ();

      //## Operation: operator STRING_T%1061986959
      operator STRING_T ();

      //## Operation: operator WSTRING_T%1061986960
      operator WSTRING_T ();

      //## Operation: operator CONST_WSTRING_T%1061986961
      operator CONST_WSTRING_T ();

      //## Operation: operator CONST_STRING_T%1061986962
      operator CONST_STRING_T ();

      //## Operation: TypeName%1061829455
      static STRING_T TypeName (UCHAR_T data_type);

      //## Operation: TypeSize%1061986963
      static ULONG_T TypeSize (UCHAR_T data_type);

      //## Operation: StrLen%1061986964
      static ULONG_T StrLen (CONST_STRING_T str);

      //## Operation: StrLen%1061986965
      static ULONG_T StrLen (CONST_WSTRING_T str);

      //## Operation: StrCmp%1061986966
      static INT_T StrCmp (CONST_STRING_T str1, CONST_STRING_T str2);

      //## Operation: StrCmp%1061986967
      static INT_T StrCmp (CONST_WSTRING_T str1, CONST_WSTRING_T str2);

      //## Operation: MemSize%1061986968
      static ULONG_T MemSize (CONST_STRING_T str);

      //## Operation: MemSize%1061986969
      static ULONG_T MemSize (CONST_WSTRING_T str);

      //## Operation: String2Wide%1061986970
      static WSTRING_T String2Wide (CONST_STRING_T str);

      //## Operation: Wide2String%1061986971
      static STRING_T Wide2String (CONST_WSTRING_T str);

      //## Operation: Real2Double%1061986972
      static DOUBLE_T Real2Double (CONST_STRING_T str);

      //## Operation: Real2Double%1061986973
      static DOUBLE_T Real2Double (CONST_WSTRING_T str);

      //## Operation: Real2Float%1061986974
      static FLOAT_T Real2Float (CONST_STRING_T str);

      //## Operation: Real2Float%1061986975
      static FLOAT_T Real2Float (CONST_WSTRING_T str);

      //## Operation: Dec2Long%1061986976
      static LONG_T Dec2Long (CONST_STRING_T str);

      //## Operation: Dec2Long%1061986977
      static LONG_T Dec2Long (CONST_WSTRING_T str);

      //## Operation: Long2String%1061986978
      static void Long2String (STRING_T &str, LONG_T value, UCHAR_T radix = 10);

      //## Operation: Long2String%1061986979
      static void Long2String (WSTRING_T &str, LONG_T value, UCHAR_T radix = 10);

      //## Operation: Float2String%1061986980
      static void Float2String (STRING_T &str, FLOAT_T value, UCHAR_T precision = 0);

      //## Operation: Float2String%1061986981
      static void Float2String (WSTRING_T &str, FLOAT_T value, UCHAR_T precision = 0);

      //## Operation: Double2String%1061986982
      static void Double2String (STRING_T &str, DOUBLE_T value, UCHAR_T precision = 0);

      //## Operation: Double2String%1061986983
      static void Double2String (WSTRING_T &str, DOUBLE_T value, UCHAR_T precision = 0);

  public:
    // Additional Public Declarations
      //## begin cVariant%3F4A3223032C.public preserve=yes
      //## end cVariant%3F4A3223032C.public

  protected:
    // Additional Protected Declarations
      //## begin cVariant%3F4A3223032C.protected preserve=yes
      //## end cVariant%3F4A3223032C.protected

  private:
    // Additional Private Declarations
      //## begin cVariant%3F4A3223032C.private preserve=yes
      //## end cVariant%3F4A3223032C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: DataType%3F4A3266035B
      //## begin cVariant::DataType%3F4A3266035B.attr preserve=no  implementation: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cVariant::DataType%3F4A3266035B.attr

      //## Attribute: LVal%3F4A3F69000F
      //## begin cVariant::LVal%3F4A3F69000F.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _LVal;
      //## end cVariant::LVal%3F4A3F69000F.attr

      //## Attribute: DVal%3F4A42CA02CE
      //## begin cVariant::DVal%3F4A42CA02CE.attr preserve=no  implementation: DOUBLE_T {U} 0
      DOUBLE_T _DVal;
      //## end cVariant::DVal%3F4A42CA02CE.attr

    // Additional Implementation Declarations
      //## begin cVariant%3F4A3223032C.implementation preserve=yes
      //## end cVariant%3F4A3223032C.implementation

};

//## begin cVariant%3F4A3223032C.postscript preserve=yes
//## end cVariant%3F4A3223032C.postscript

// Class cVariant 

//## begin module%3F4A3223032C.epilog preserve=yes
//## end module%3F4A3223032C.epilog


#endif

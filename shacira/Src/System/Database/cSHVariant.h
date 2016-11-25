//## begin module%3EF2E1D8008C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EF2E1D8008C.cm

//## begin module%3EF2E1D8008C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EF2E1D8008C.cp

//## Module: cSHVariant%3EF2E1D8008C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cSHVariant.h

#ifndef cSHVariant_h
#define cSHVariant_h 1

//## begin module%3EF2E1D8008C.includes preserve=yes
//## end module%3EF2E1D8008C.includes

//## begin module%3EF2E1D8008C.additionalDeclarations preserve=yes
//## end module%3EF2E1D8008C.additionalDeclarations


//## begin cSHVariant%3EF2E1D8008C.preface preserve=yes
//## end cSHVariant%3EF2E1D8008C.preface

//## Class: cSHVariant%3EF2E1D8008C
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cSHVariant 
{
  //## begin cSHVariant%3EF2E1D8008C.initialDeclarations preserve=yes
public:
  //## end cSHVariant%3EF2E1D8008C.initialDeclarations

    //## Constructors (generated)
      cSHVariant();

      cSHVariant(const cSHVariant &right);

    //## Constructors (specified)
      //## Operation: cSHVariant%1071244309
      cSHVariant (UCHAR_T data_type);

    //## Destructor (generated)
      virtual ~cSHVariant();


    //## Other Operations (specified)
      //## Operation: Get%1071244133
      virtual void Get (CHAR_T &value);

      //## Operation: Get%1071244134
      virtual void Get (UCHAR_T &value);

      //## Operation: Get%1071244135
      virtual void Get (SHORT_T &value);

      //## Operation: Get%1071244136
      virtual void Get (USHORT_T &value);

      //## Operation: Get%1071244137
      virtual void Get (LONG_T &value);

      //## Operation: Get%1071244138
      virtual void Get (ULONG_T &value);

      //## Operation: Get%1071244139
      virtual void Get (FLOAT_T &value);

      //## Operation: Get%1071244140
      virtual void Get (DOUBLE_T &value);

      //## Operation: Get%1071244141
      virtual void Get (STRING_T &value, UCHAR_T precision = 0);

      //## Operation: Get%1071244142
      virtual void Get (WSTRING_T &value, UCHAR_T precision = 0);

      //## Operation: Get%1071244143
      virtual void Get (BUF_T &buf);

      //## Operation: Set%1071244145
      virtual void Set (CHAR_T value);

      //## Operation: Set%1071244146
      virtual void Set (UCHAR_T value);

      //## Operation: Set%1071244147
      virtual void Set (SHORT_T value);

      //## Operation: Set%1071244148
      virtual void Set (USHORT_T value);

      //## Operation: Set%1071244149
      virtual void Set (LONG_T value);

      //## Operation: Set%1071244150
      virtual void Set (ULONG_T value);

      //## Operation: Set%1071244151
      virtual void Set (FLOAT_T value);

      //## Operation: Set%1071244152
      virtual void Set (DOUBLE_T value);

      //## Operation: Set%1071244153
      virtual void Set (CONST_STRING_T value);

      //## Operation: Set%1071244154
      virtual void Set (CONST_WSTRING_T value);

      //## Operation: Set%1073740506
      virtual void Set (BUF_T buf);

      //## Operation: TypeName%1056195555
      static STRING_T TypeName (UCHAR_T data_type);

      //## Operation: String2Wide%1056375604
      static WSTRING_T String2Wide (CONST_STRING_T str);

      //## Operation: Wide2String%1056195556
      static STRING_T Wide2String (CONST_WSTRING_T str);

      //## Operation: Real2Double%1056195557
      static DOUBLE_T Real2Double (CONST_STRING_T str);

      //## Operation: Real2Double%1056375592
      static DOUBLE_T Real2Double (CONST_WSTRING_T str);

      //## Operation: Real2Float%1056375594
      static FLOAT_T Real2Float (CONST_STRING_T str);

      //## Operation: Real2Float%1056375593
      static FLOAT_T Real2Float (CONST_WSTRING_T str);

      //## Operation: Hex2Ulong%1056375595
      static ULONG_T Hex2Ulong (CONST_STRING_T str);

      //## Operation: Hex2Ulong%1056375596
      static ULONG_T Hex2Ulong (CONST_WSTRING_T str);

      //## Operation: Dec2Long%1056375599
      static LONG_T Dec2Long (CONST_STRING_T str);

      //## Operation: Dec2Long%1056375600
      static LONG_T Dec2Long (CONST_WSTRING_T str);

      //## Operation: BCD2Long%1056375605
      static LONG_T BCD2Long (CONST_STRING_T str);

      //## Operation: BCD2Long%1056375606
      static LONG_T BCD2Long (CONST_WSTRING_T str);

      //## Operation: KMBCD2Long%1056375607
      static LONG_T KMBCD2Long (CONST_STRING_T str);

      //## Operation: KMBCD2Long%1056375608
      static LONG_T KMBCD2Long (CONST_WSTRING_T str);

      //## Operation: Long2String%1056447736
      static void Long2String (STRING_T &str, LONG_T value, UCHAR_T radix = 10);

      //## Operation: Long2String%1056447737
      static void Long2String (WSTRING_T &str, LONG_T value, UCHAR_T radix = 10);

      //## Operation: ULong2String%1236356396
      static void ULong2String (STRING_T &str, ULONG_T value, UCHAR_T radix = 10);

      //## Operation: ULong2String%1236356397
      static void ULong2String (WSTRING_T &str, ULONG_T value, UCHAR_T radix = 10);

      //## Operation: Float2String%1056447738
      static void Float2String (STRING_T &str, FLOAT_T value, UCHAR_T precision = 0);

      //## Operation: Float2String%1056447739
      static void Float2String (WSTRING_T &str, FLOAT_T value, UCHAR_T precision = 0);

      //## Operation: Double2String%1056447740
      static void Double2String (STRING_T &str, DOUBLE_T value, UCHAR_T precision = 0);

      //## Operation: Double2String%1056447741
      static void Double2String (WSTRING_T &str, DOUBLE_T value, UCHAR_T precision = 0);

      //## Operation: StrLen%1056195558
      static ULONG_T StrLen (CONST_STRING_T str);

      //## Operation: StrLen%1056195559
      static ULONG_T StrLen (CONST_WSTRING_T str);

      //## Operation: StrCmp%1056621170
      static INT_T StrCmp (CONST_STRING_T str1, CONST_STRING_T str2);

      //## Operation: StrCmp%1056621171
      static INT_T StrCmp (CONST_WSTRING_T str1, CONST_WSTRING_T str2);

      //## Operation: MemSize%1056478821
      static ULONG_T MemSize (CONST_STRING_T str);

      //## Operation: MemSize%1056478822
      static ULONG_T MemSize (CONST_WSTRING_T str);

      //## Operation: TypeSize%1056478823
      static ULONG_T TypeSize (UCHAR_T data_type);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DataType%3EF32B4F032C
      UCHAR_T get_DataType () const;
      void set_DataType (UCHAR_T value);

  public:
    // Additional Public Declarations
      //## begin cSHVariant%3EF2E1D8008C.public preserve=yes
      //## end cSHVariant%3EF2E1D8008C.public

  protected:
    // Data Members for Class Attributes

      //## begin cSHVariant::DataType%3EF32B4F032C.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cSHVariant::DataType%3EF32B4F032C.attr

    // Additional Protected Declarations
      //## begin cSHVariant%3EF2E1D8008C.protected preserve=yes
      //## end cSHVariant%3EF2E1D8008C.protected

  private:
    // Additional Private Declarations
      //## begin cSHVariant%3EF2E1D8008C.private preserve=yes
      //## end cSHVariant%3EF2E1D8008C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: LONG_Value%3EF32CDE033C
      //## begin cSHVariant::LONG_Value%3EF32CDE033C.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _LONG_Value;
      //## end cSHVariant::LONG_Value%3EF32CDE033C.attr

      //## Attribute: FLOAT_Value%3EF32D1C0251
      //## begin cSHVariant::FLOAT_Value%3EF32D1C0251.attr preserve=no  implementation: FLOAT_T {U} 0
      FLOAT_T _FLOAT_Value;
      //## end cSHVariant::FLOAT_Value%3EF32D1C0251.attr

      //## Attribute: DOUBLE_Value%3EF32D1C0252
      //## begin cSHVariant::DOUBLE_Value%3EF32D1C0252.attr preserve=no  implementation: DOUBLE_T {U} 0
      DOUBLE_T _DOUBLE_Value;
      //## end cSHVariant::DOUBLE_Value%3EF32D1C0252.attr

      //## Attribute: STRING_Value%3EF4434B0119
      //## begin cSHVariant::STRING_Value%3EF4434B0119.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _STRING_Value;
      //## end cSHVariant::STRING_Value%3EF4434B0119.attr

      //## Attribute: WSTRING_Value%3EF4438403B9
      //## begin cSHVariant::WSTRING_Value%3EF4438403B9.attr preserve=no  implementation: WSTRING_T {U} 
      WSTRING_T _WSTRING_Value;
      //## end cSHVariant::WSTRING_Value%3EF4438403B9.attr

      //## Attribute: BUF_Value%3EF442E70177
      //## begin cSHVariant::BUF_Value%3EF442E70177.attr preserve=no  implementation: BUF_T {U} NULL
      BUF_T _BUF_Value;
      //## end cSHVariant::BUF_Value%3EF442E70177.attr

    // Additional Implementation Declarations
      //## begin cSHVariant%3EF2E1D8008C.implementation preserve=yes
      //## end cSHVariant%3EF2E1D8008C.implementation

};

//## begin cSHVariant%3EF2E1D8008C.postscript preserve=yes
//## end cSHVariant%3EF2E1D8008C.postscript

// Class cSHVariant 

//## begin module%3EF2E1D8008C.epilog preserve=yes
//## end module%3EF2E1D8008C.epilog


#endif

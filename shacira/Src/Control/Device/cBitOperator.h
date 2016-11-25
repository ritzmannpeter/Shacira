//## begin module%40A1F8F50157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A1F8F50157.cm

//## begin module%40A1F8F50157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A1F8F50157.cp

//## Module: cBitOperator%40A1F8F50157; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cBitOperator.h

#ifndef cBitOperator_h
#define cBitOperator_h 1

//## begin module%40A1F8F50157.includes preserve=yes
//## end module%40A1F8F50157.includes

//## begin module%40A1F8F50157.additionalDeclarations preserve=yes
#define SWAP_WORD(w_val)      (((w_val & 0x00ff) << 8)+((w_val & 0xff00) >> 8))
#define SWAP_DWORD(dw_val)    (((dw_val & 0x0000ffff) << 16) + ((dw_val & 0xffff0000) >> 16))
#define HIGH_WORD(dw_val)     ((unsigned short)(dw_val & 0x0000ffff))
#define LOW_WORD(dw_val)      ((unsigned short)((dw_val & 0xffff0000) >> 16))
#define MK_LONG(high,low)     (low+(high<<16))
#define GET_BIT_B(b_val,pos)   (b_val & (1 << (pos)))
#define GET_BIT_W(w_val,pos)   (w_val & (1 << (pos)))
#define GET_BIT_DW(dw_val,pos) (dw_val & (1 << (pos)))
#define SET_BIT_B(b_val,pos)   (b_val | (1 << (pos)))
#define SET_BIT_W(w_val,pos)   (w_val | (1 << (pos)))
#define SET_BIT_DW(dw_val,pos) (dw_val | (1 << (pos)))
#define RESET_BIT_B(b_val,pos)   ((b_val) & ~(1 << (pos)))
#define RESET_BIT_W(w_val,pos)   ((w_val) & ~(1 << (pos)))
#define RESET_BIT_DW(dw_val,pos)  ((dw_val) & ~(1 << (pos)))

USHORT_T byte_to_word(USHORT_T word_value);
ULONG_T byte_to_long(ULONG_T long_value);
ULONG_T word_to_long(ULONG_T long_value);
FLOAT_T byte_to_float(FLOAT_T float_value);
DOUBLE_T byte_to_double(DOUBLE_T double_value);

//## end module%40A1F8F50157.additionalDeclarations


//## begin cBitOperator%40A1F8F50157.preface preserve=yes
//## end cBitOperator%40A1F8F50157.preface

//## Class: cBitOperator%40A1F8F50157
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cBitOperator 
{
  //## begin cBitOperator%40A1F8F50157.initialDeclarations preserve=yes
public:
  //## end cBitOperator%40A1F8F50157.initialDeclarations

    //## Constructors (generated)
      cBitOperator();

      cBitOperator(const cBitOperator &right);

    //## Constructors (specified)
      //## Operation: cBitOperator%1084360927
      cBitOperator (UCHAR_T granularity);

    //## Destructor (generated)
      virtual ~cBitOperator();


    //## Other Operations (specified)
      //## Operation: SetValue%1084360911
      virtual void SetValue (UCHAR_T data_type, UCHAR_T value);

      //## Operation: SetValue%1084360912
      virtual void SetValue (UCHAR_T data_type, USHORT_T value);

      //## Operation: SetValue%1084360913
      virtual void SetValue (UCHAR_T data_type, ULONG_T value);

      //## Operation: SetValue%1084360914
      virtual void SetValue (UCHAR_T data_type, CHAR_T value);

      //## Operation: SetValue%1084360915
      virtual void SetValue (UCHAR_T data_type, SHORT_T value);

      //## Operation: SetValue%1084360916
      virtual void SetValue (UCHAR_T data_type, LONG_T value);

      //## Operation: SetValue%1110194499
      virtual void SetValue (UCHAR_T data_type, FLOAT_T value);

      //## Operation: SetValue%1110194500
      virtual void SetValue (UCHAR_T data_type, DOUBLE_T value);

      //## Operation: operator UCHAR_T%1084360917
      virtual operator UCHAR_T ();

      //## Operation: operator USHORT_T%1084360918
      virtual operator USHORT_T ();

      //## Operation: operator ULONG_T%1084360919
      virtual operator ULONG_T ();

      //## Operation: operator CHAR_T%1084360920
      virtual operator CHAR_T ();

      //## Operation: operator SHORT_T%1084360921
      virtual operator SHORT_T ();

      //## Operation: operator LONG_T%1084360922
      virtual operator LONG_T ();

      //## Operation: operator FLOAT_T%1110194501
      virtual operator FLOAT_T ();

      //## Operation: operator DOUBLE_T%1110194502
      virtual operator DOUBLE_T ();

      //## Operation: SetBit%1084360923
      virtual void SetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: ResetBit%1084360924
      virtual void ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetBit%1084360966
      virtual UCHAR_T GetBit (UCHAR_T pos, CONST_STRING_T buf_spec = NULL);

      //## Operation: SetPattern%1084360925
      virtual void SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: GetPattern%1084360926
      virtual ULONG_T GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec = NULL);

      //## Operation: BytePos%1084360928
      virtual UCHAR_T BytePos (UCHAR_T data_type, UCHAR_T bit_pos);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Granularity%40A1F98A0203
      UCHAR_T get_Granularity () const;
      void set_Granularity (UCHAR_T value);

  public:
    // Additional Public Declarations
      //## begin cBitOperator%40A1F8F50157.public preserve=yes
      //## end cBitOperator%40A1F8F50157.public

  protected:
    // Data Members for Class Attributes

      //## begin cBitOperator::Granularity%40A1F98A0203.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _Granularity;
      //## end cBitOperator::Granularity%40A1F98A0203.attr

      //## Attribute: DataType%40A20B9201E4
      //## begin cBitOperator::DataType%40A20B9201E4.attr preserve=no  protected: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cBitOperator::DataType%40A20B9201E4.attr

      //## Attribute: CHAR_Value%40A20BAB0203
      //## begin cBitOperator::CHAR_Value%40A20BAB0203.attr preserve=no  protected: UCHAR_T {U} 0
      UCHAR_T _CHAR_Value;
      //## end cBitOperator::CHAR_Value%40A20BAB0203.attr

      //## Attribute: SHORT_Value%40A20BCA034B
      //## begin cBitOperator::SHORT_Value%40A20BCA034B.attr preserve=no  protected: SHORT_T {U} 0
      SHORT_T _SHORT_Value;
      //## end cBitOperator::SHORT_Value%40A20BCA034B.attr

      //## Attribute: LONG_Value%40A20BDB0203
      //## begin cBitOperator::LONG_Value%40A20BDB0203.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _LONG_Value;
      //## end cBitOperator::LONG_Value%40A20BDB0203.attr

      //## Attribute: FLOAT_Value%40A21463005D
      //## begin cBitOperator::FLOAT_Value%40A21463005D.attr preserve=no  protected: FLOAT_T {U} 0
      FLOAT_T _FLOAT_Value;
      //## end cBitOperator::FLOAT_Value%40A21463005D.attr

      //## Attribute: DOUBLE_Value%40A2148B0177
      //## begin cBitOperator::DOUBLE_Value%40A2148B0177.attr preserve=no  protected: DOUBLE_T {U} 0
      DOUBLE_T _DOUBLE_Value;
      //## end cBitOperator::DOUBLE_Value%40A2148B0177.attr

    // Additional Protected Declarations
      //## begin cBitOperator%40A1F8F50157.protected preserve=yes
      //## end cBitOperator%40A1F8F50157.protected

  private:
    // Additional Private Declarations
      //## begin cBitOperator%40A1F8F50157.private preserve=yes
      //## end cBitOperator%40A1F8F50157.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cBitOperator%40A1F8F50157.implementation preserve=yes
      //## end cBitOperator%40A1F8F50157.implementation

};

//## begin cBitOperator%40A1F8F50157.postscript preserve=yes
//## end cBitOperator%40A1F8F50157.postscript

// Class cBitOperator 

//## begin module%40A1F8F50157.epilog preserve=yes
//## end module%40A1F8F50157.epilog


#endif

//## begin module%3C7FAFB50192.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7FAFB50192.cm

//## begin module%3C7FAFB50192.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7FAFB50192.cp

//## Module: cConvUtils%3C7FAFB50192; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cConvUtils.h

#ifndef cConvUtils_h
#define cConvUtils_h 1

//## begin module%3C7FAFB50192.includes preserve=yes
//## end module%3C7FAFB50192.includes


class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cStringBuffer;

//## begin module%3C7FAFB50192.additionalDeclarations preserve=yes
//## end module%3C7FAFB50192.additionalDeclarations


//## begin cConvUtils%3C7FAFB50192.preface preserve=yes
//## end cConvUtils%3C7FAFB50192.preface

//## Class: cConvUtils%3C7FAFB50192
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C7FB3C3039D;cStringUtils { -> F}

class __DLL_EXPORT__ cConvUtils 
{
  //## begin cConvUtils%3C7FAFB50192.initialDeclarations preserve=yes
public:
  //## end cConvUtils%3C7FAFB50192.initialDeclarations

    //## Constructors (generated)
      cConvUtils();

      cConvUtils(const cConvUtils &right);

    //## Destructor (generated)
      virtual ~cConvUtils();


    //## Other Operations (specified)
      //## Operation: CharBuf2LPWSTR%1014996958
      //	Conversion function from character buffer to windows
      //	LPWSTR.
      static LPWSTR CharBuf2LPWSTR (CONST_STRING_T buf);

      //## Operation: LPWSTR2CharBuf%1014996959
      //	Conversion function from character buffer to windows
      //	LPWSTR.
      static CONST_STRING_T LPWSTR2CharBuf (LPWSTR wide_string, CHAR_T *buf, INT_T buf_size);

      //## Operation: StringValue%1014996960
      static STRING_T StringValue (DOUBLE_T value);

      //## Operation: StringValue%1014996962
      static STRING_T StringValue (FLOAT_T value);

      //## Operation: StringValue%1014996961
      static STRING_T StringValue (LONG_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996963
      static STRING_T StringValue (ULONG_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996965
      static STRING_T StringValue (UINT_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996966
      static STRING_T StringValue (SHORT_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996967
      static STRING_T StringValue (USHORT_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996964
      static STRING_T StringValue (INT_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996968
      static STRING_T StringValue (CHAR_T value, INT_T radix = 10);

      //## Operation: StringValue%1014996969
      static STRING_T StringValue (UCHAR_T value, INT_T radix = 10);

      //## Operation: IsNumeric%1037360042
      static BOOL_T IsNumeric (CONST_STRING_T value);

      //## Operation: SubstParams%1075899383
      static STRING_T SubstParams (CONST_STRING_T text, CONST_STRING_T p1 = NULL, CONST_STRING_T p2 = NULL, CONST_STRING_T p3 = NULL, CONST_STRING_T p4 = NULL);

      //## Operation: DataTypeFromString%1038418270
      static void DataTypeFromString (CONST_STRING_T value, CHAR_T &data_type, USHORT_T &length, UCHAR_T &precision);

      //## Operation: FormatValue%1038473727
      static STRING_T FormatValue (CONST_STRING_T value, CHAR_T data_type = UNDEFINED, USHORT_T length = 0, UCHAR_T precision = 0);

      //## Operation: Buf2BCD%1092134509
      static ULONG_T Buf2BCD(STRING_T &bcd_value, BUF_T buf, ULONG_T len);
      // cStringBuffer based method Buf2BCD
      static ULONG_T Buf2BCD(cStringBuffer &bcd_value, BUF_T buf, ULONG_T len);

      //## Operation: BCD2Buf%1092134510
      static ULONG_T BCD2Buf (CONST_STRING_T bcd_str, BUF_T buf, ULONG_T buf_size);

      //## Operation: Compress%1092134511
      static ULONG_T Compress (BUF_T comp_buf, ULONG_T buf_size, BUF_T buf, ULONG_T len, ULONG_T type = 0);

      //## Operation: Decompress%1092134512
      static ULONG_T Decompress (BUF_T decomp_buf, ULONG_T buf_size, BUF_T buf, ULONG_T len, ULONG_T type = 0);

      //## Operation: Buf2String%1092208313
      static ULONG_T Buf2String(STRING_T &text, BUF_T buf, ULONG_T len);
      // cStringBuffer based method Buf2String
      static ULONG_T Buf2String(cStringBuffer &text, BUF_T buf, ULONG_T len);

      //## Operation: String2Buf%1092208314
      static ULONG_T String2Buf (CONST_STRING_T text, BUF_T buf, ULONG_T buf_size);
      static ULONG_T BCDBufSize (ULONG_T text_size);
      static ULONG_T BCDTextSize (ULONG_T buf_size);

      //## Operation: ExtractBCDSequence%1092208315
      static ULONG_T ExtractBCDSequence (STRING_T &bcd_sequence, CONST_STRING_T text);

      //## Operation: IsPureString%1096898762
      static BOOL_T IsPureString (CONST_STRING_T text);

      //## Operation: Ptr2String%1122544049
      static ULONG_T Ptr2String (STRING_T &text, PTR_T ptr);

      //## Operation: String2Ptr%1122544050
      static ULONG_T String2Ptr (PTR_T &ptr, CONST_STRING_T text);

  public:
    // Additional Public Declarations
      //## begin cConvUtils%3C7FAFB50192.public preserve=yes
      //## end cConvUtils%3C7FAFB50192.public

  protected:
    // Additional Protected Declarations
      //## begin cConvUtils%3C7FAFB50192.protected preserve=yes
      //## end cConvUtils%3C7FAFB50192.protected

  private:
    // Additional Private Declarations
      //## begin cConvUtils%3C7FAFB50192.private preserve=yes
      //## end cConvUtils%3C7FAFB50192.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: FormatReal%1038473728
      static void FormatReal (STRING_BUF_T value, UCHAR_T precision);

      //## Operation: FormatInt%1151939529
      static void FormatInt (STRING_BUF_T value, UCHAR_T precision);

    // Additional Implementation Declarations
      //## begin cConvUtils%3C7FAFB50192.implementation preserve=yes
      //## end cConvUtils%3C7FAFB50192.implementation

};

//## begin cConvUtils%3C7FAFB50192.postscript preserve=yes
//## end cConvUtils%3C7FAFB50192.postscript

// Class cConvUtils 

//## begin module%3C7FAFB50192.epilog preserve=yes
//## end module%3C7FAFB50192.epilog


#endif

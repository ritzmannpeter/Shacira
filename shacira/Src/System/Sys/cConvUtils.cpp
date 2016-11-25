//## begin module%3C7FAFB50192.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7FAFB50192.cm

//## begin module%3C7FAFB50192.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7FAFB50192.cp

//## Module: cConvUtils%3C7FAFB50192; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cConvUtils.cpp

//## begin module%3C7FAFB50192.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C7FAFB50192.additionalIncludes

//## begin module%3C7FAFB50192.includes preserve=yes

/// PR 23.02.07 - added ' and " to pure string check
/// PR 26.01.16 - added two cStringBuffer based methosds:
///               ULONG_T Buf2BCD(cStringBuffer &bcd_value, BUF_T buf, ULONG_T len)
///               ULONG_T Buf2String(cStringBuffer &text, BUF_T buf, ULONG_T len)

//## end module%3C7FAFB50192.includes

// cStringUtils
#include "System/cStringUtils.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
#include "System/Sys/cStringBuffer.h"
//## begin module%3C7FAFB50192.additionalDeclarations preserve=yes

#if defined(__linux__)

typedef short WCHAR;

#endif

static CHAR_T HexChars[16] =
{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static CHAR_T HexValue(UCHAR_T value)
{
   return HexChars[value];
}

static UCHAR_T ByteValue(CHAR_T value)
{
   UCHAR_T result = 0;
   if ( value <= '9' ) {
      result = value - '0';
   }
   else if (( value >= 'A' ) && ( value <= 'F' )) {
      result = value - 'A' + 10;
   }
   else if (( value >= 'a' ) && ( value <= 'f' )) {
      result = value - 'a' + 10;
   }
   return result;
}

static UCHAR_T ByteValue(CHAR_T * value)
{ 
   UCHAR_T high = ByteValue(value[0]);
   UCHAR_T low = ByteValue(value[1]);
   return (high << 4) | low;
}


static ULONG_T CompressText(BUF_T comp_buf, BUF_T text, ULONG_T len)
{
   ULONG_T i=0, j=0;
   UCHAR_T count = 0;
   while (i<len) {
      if (i+1 < len && text[i] < 128 && text[i] == text[i+1]) {
         /* mindestens 2 Zeichen sind gleich */
         for (count=2 ;
              i + count < len && text[i] == text[i + count] && count<255 ;
              count++) {
         }  
         comp_buf[j++] = text[i] | 0x80;     /* Zeichen + 128 */
         comp_buf[j++] = count;              /* Anzahl Zeichen */
         i += count;
      } else {
         comp_buf[j++] = text[i++] & 0x7F;   /* hoechstes Bit ausmaskieren */
      }
   }
   return j;
}


static ULONG_T DeCompressText(BUF_T text_buf, BUF_T comp_text, ULONG_T len )
{
   ULONG_T i=0, j=0, count=0;
   while (i<len ) {
      if ((comp_text[i] & 0x80) == 0x80) {
         /* Zeichen kommt mehrmals vor */
         for (count=comp_text[i+1] ; count > 0 ; count-- ) {
            text_buf[j++] = comp_text[i] & 0x7f;     /* - 128 */
         }
         i += 2;
      } else {
         text_buf[j++] = comp_text[i++];
      }
   }
   return j;
}

static ULONG_T Comp(BUF_T comp_buf, BUF_T text, ULONG_T len)
{
   ULONG_T i=0, j=0;
   UCHAR_T count = 0;
   while (i<len) {
      if (i+1 < len && text[i] > 128 && text[i] == text[i+1]) {
         /* mindestens 2 Zeichen sind gleich */
         for (count=2 ;
              i + count < len && text[i] == text[i + count] && count<255 ;
              count++) {
         }  
         comp_buf[j++] = text[i] & 0x7f;     /* Zeichen + 128 */
         comp_buf[j++] = count;              /* Anzahl Zeichen */
         i += count;
      } else {
         comp_buf[j++] = text[i++] | 0x80;   /* hoechstes Bit ausmaskieren */
      }
   }
   return j;
}


static ULONG_T DeComp(BUF_T text_buf, BUF_T comp_text, ULONG_T len )
{
   ULONG_T i=0, j=0, count=0;
   while (i<len ) {
      if ((comp_text[i] & 0x80) == 0x80) {
         /* Zeichen kommt mehrmals vor */
         for (count=comp_text[i+1] ; count > 0 ; count-- ) {
            text_buf[j++] = comp_text[i] | 0x80;     /* - 128 */
         }
         i += 2;
      } else {
         text_buf[j++] = comp_text[i++];
      }
   }
   return j;
}

//## end module%3C7FAFB50192.additionalDeclarations


// Class cConvUtils 

cConvUtils::cConvUtils()
  //## begin cConvUtils::cConvUtils%.hasinit preserve=no
  //## end cConvUtils::cConvUtils%.hasinit
  //## begin cConvUtils::cConvUtils%.initialization preserve=yes
  //## end cConvUtils::cConvUtils%.initialization
{
  //## begin cConvUtils::cConvUtils%.body preserve=yes
  //## end cConvUtils::cConvUtils%.body
}

cConvUtils::cConvUtils(const cConvUtils &right)
  //## begin cConvUtils::cConvUtils%copy.hasinit preserve=no
  //## end cConvUtils::cConvUtils%copy.hasinit
  //## begin cConvUtils::cConvUtils%copy.initialization preserve=yes
  //## end cConvUtils::cConvUtils%copy.initialization
{
  //## begin cConvUtils::cConvUtils%copy.body preserve=yes
  //## end cConvUtils::cConvUtils%copy.body
}


cConvUtils::~cConvUtils()
{
  //## begin cConvUtils::~cConvUtils%.body preserve=yes
  //## end cConvUtils::~cConvUtils%.body
}



//## Other Operations (implementation)
LPWSTR cConvUtils::CharBuf2LPWSTR (CONST_STRING_T buf)
{
  //## begin cConvUtils::CharBuf2LPWSTR%1014996958.body preserve=yes
#ifdef _WIN32
   int len = strlen(buf);
   WCHAR* wide_buf = new WCHAR[len+1];
   MultiByteToWideChar(CP_ACP, 0, buf, -1, wide_buf, len+1);
   LPWSTR wide_string = SysAllocString(wide_buf);
   delete [] wide_buf;
   return wide_string;
#elif defined(__linux__)
PORT_LEVEL_5
return NULL;
#else
NO_PLATFORM
#endif
  //## end cConvUtils::CharBuf2LPWSTR%1014996958.body
}

CONST_STRING_T cConvUtils::LPWSTR2CharBuf (LPWSTR wide_string, CHAR_T *buf, INT_T buf_size)
{
  //## begin cConvUtils::LPWSTR2CharBuf%1014996959.body preserve=yes
#ifdef _WIN32
   WideCharToMultiByte(CP_ACP, 0, wide_string, -1, buf, buf_size, NULL, NULL);
   return buf;
#elif defined(__linux__)
PORT_LEVEL_5
return NULL;
#else
NO_PLATFORM
#endif
  //## end cConvUtils::LPWSTR2CharBuf%1014996959.body
}

STRING_T cConvUtils::StringValue (DOUBLE_T value)
{
  //## begin cConvUtils::StringValue%1014996960.body preserve=yes
   char cval[64] = {0};
   SafePrintf(cval, sizeof(cval), "%f", value);
   STRING_T sval = cStringUtils::RTrim(cval, '0');
   sval = cStringUtils::RTrim(sval.c_str(), '.');
   return sval;
  //## end cConvUtils::StringValue%1014996960.body
}

STRING_T cConvUtils::StringValue (FLOAT_T value)
{
  //## begin cConvUtils::StringValue%1014996962.body preserve=yes
   char cval[64] = {0};
   SafePrintf(cval, sizeof(cval), "%f", value);
   STRING_T sval = cStringUtils::RTrim(cval, '0');
   sval = cStringUtils::RTrim(sval.c_str(), '.');
   return sval;
  //## end cConvUtils::StringValue%1014996962.body
}

STRING_T cConvUtils::StringValue (LONG_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996961.body preserve=yes
   char cval[32] = {0};
   ltoa(value, cval, radix);
   return cval;
  //## end cConvUtils::StringValue%1014996961.body
}

STRING_T cConvUtils::StringValue (ULONG_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996963.body preserve=yes
   char cval[32] = {0};
   ltoa(value, cval, radix);
   return cval;
  //## end cConvUtils::StringValue%1014996963.body
}

STRING_T cConvUtils::StringValue (UINT_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996965.body preserve=yes
   return StringValue((ULONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996965.body
}

STRING_T cConvUtils::StringValue (SHORT_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996966.body preserve=yes
   return StringValue((LONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996966.body
}

STRING_T cConvUtils::StringValue (USHORT_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996967.body preserve=yes
   return StringValue((ULONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996967.body
}

STRING_T cConvUtils::StringValue (INT_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996964.body preserve=yes
   return StringValue((LONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996964.body
}

STRING_T cConvUtils::StringValue (CHAR_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996968.body preserve=yes
   return StringValue((LONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996968.body
}

STRING_T cConvUtils::StringValue (UCHAR_T value, INT_T radix)
{
  //## begin cConvUtils::StringValue%1014996969.body preserve=yes
   return StringValue((ULONG_T)value, radix);
  //## end cConvUtils::StringValue%1014996969.body
}

BOOL_T cConvUtils::IsNumeric (CONST_STRING_T value)
{
  //## begin cConvUtils::IsNumeric%1037360042.body preserve=yes
   int size = strlen(value);
   if (size == 0) return false;
   int decimal_points = 0;
   for (int i=0; i<size; i++) {
      int c = value[i];
      if (i == 0 && (c == '-' || c == '+')) {
         // numeric sign
      } else {
         if (c == '.') {
            if (decimal_points == 0) {
               decimal_points++;
            } else {
               return false;
            }
         } else if (!isdigit(c)) {
            return false;
         }
      }
   }
   return true;
  //## end cConvUtils::IsNumeric%1037360042.body
}

STRING_T cConvUtils::SubstParams (CONST_STRING_T text, CONST_STRING_T p1, CONST_STRING_T p2, CONST_STRING_T p3, CONST_STRING_T p4)
{
  //## begin cConvUtils::SubstParams%1075899383.body preserve=yes
   STRING_T new_text = text;
   if (p1 != NULL) new_text = cStringUtils::Replace(new_text, "#1", p1);
   if (p2 != NULL) new_text = cStringUtils::Replace(new_text, "#2", p2);
   if (p3 != NULL) new_text = cStringUtils::Replace(new_text, "#3", p3);
   if (p4 != NULL) new_text = cStringUtils::Replace(new_text, "#4", p4);
   return new_text;
  //## end cConvUtils::SubstParams%1075899383.body
}

void cConvUtils::DataTypeFromString (CONST_STRING_T value, CHAR_T &data_type, USHORT_T &length, UCHAR_T &precision)
{
  //## begin cConvUtils::DataTypeFromString%1038418270.body preserve=yes
   int size = strlen(value);
   if (size == 0) return;
   int decimal_points = 0;
   for (int i=0; i<size; i++) {
      int c = value[i];
      if (c == '.') {
         if (decimal_points == 0) {
            decimal_points++;
            data_type = SH_DOUBLE;
         } else {
            data_type = SH_STRING;
            return;
         }
      } else if (isdigit(c)) {
         if (decimal_points == 1) precision++;
      } else {
         data_type = SH_STRING;
         return;
      }
   }
   if (decimal_points == 0) {
      data_type = SH_LONG;
   } else {
      data_type = SH_DOUBLE;
   }
  //## end cConvUtils::DataTypeFromString%1038418270.body
}

STRING_T cConvUtils::FormatValue (CONST_STRING_T value, CHAR_T data_type, USHORT_T length, UCHAR_T precision)
{
  //## begin cConvUtils::FormatValue%1038473727.body preserve=yes
   char buf[128] = {0};
   BOOL_T not_null = (strlen(value) > 0);
   LONG_T slong = 0;
   ULONG_T ulong = 0;
   float real = 0;
   switch (data_type) {
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
      if (not_null) slong = atol(value); 
      SafePrintf(buf, sizeof(buf), "%d", slong);
      FormatInt(buf, precision);
      break;
   case SH_UCHAR:
   case SH_USHORT:
   case SH_ULONG:
      if (not_null) ulong = strtoul(value, NULL, 0); 
      SafePrintf(buf, sizeof(buf), "%d", ulong);
      FormatInt(buf, precision);
      break;
   case SH_FLOAT:
   case SH_DOUBLE:
      if (not_null) sscanf(value, "%f", &real);
      SafePrintf(buf, sizeof(buf), "%f", real);
      FormatReal(buf, precision);
      break;
   case SH_STRING:
   case SH_WSTRING:
      return value;
   default: return "?";
   }
   return buf;
  //## end cConvUtils::FormatValue%1038473727.body
}

ULONG_T cConvUtils::Buf2BCD (STRING_T &bcd_value, BUF_T buf, ULONG_T len)
{
  //## begin cConvUtils::Buf2BCD%1092134509.body preserve=yes
   ULONG_T size = (len * 2) + 1;
   CHAR_T * bcd_buf = (CHAR_T*)cSystemUtils::CachedAlloc("sepp", GetCurrentThreadId(), 0, 0, 0, size);
   CHAR_T * bcd_ptr = bcd_buf;
   UCHAR_T * buf_ptr = buf;
   for (ULONG_T i=0; i < len; i++) {
      UCHAR_T c = *buf_ptr;
      UCHAR_T high = (c & 0xf0) >> 4;
      *bcd_ptr = HexValue(high);
//      *bcd_ptr = HexChars[high];
      bcd_ptr++;
      UCHAR_T low = c & 0x0f;
      *bcd_ptr = HexValue(low);
//      *bcd_ptr = HexChars[low];
      bcd_ptr++;
      buf_ptr++;
   }
   bcd_value += bcd_buf;
   return bcd_value.size();
  //## end cConvUtils::Buf2BCD%1092134509.body
}

ULONG_T cConvUtils::Buf2BCD(cStringBuffer &bcd_value, BUF_T buf, ULONG_T len)
{
   //## begin cConvUtils::Buf2BCD%1092134509.body preserve=yes
   ULONG_T size = (len * 2) + 1;
   CHAR_T * bcd_buf = (CHAR_T*)cSystemUtils::CachedAlloc("sepp", GetCurrentThreadId(), 0, 0, 0, size);
   CHAR_T * bcd_ptr = bcd_buf;
   UCHAR_T * buf_ptr = buf;
   for (ULONG_T i = 0; i < len; i++) {
      UCHAR_T c = *buf_ptr;
      UCHAR_T high = (c & 0xf0) >> 4;
      *bcd_ptr = HexValue(high);
      //      *bcd_ptr = HexChars[high];
      bcd_ptr++;
      UCHAR_T low = c & 0x0f;
      *bcd_ptr = HexValue(low);
      //      *bcd_ptr = HexChars[low];
      bcd_ptr++;
      buf_ptr++;
   }
   bcd_value += bcd_buf;
   return bcd_value.size();
   //## end cConvUtils::Buf2BCD%1092134509.body
}

ULONG_T cConvUtils::BCD2Buf(CONST_STRING_T bcd_str, BUF_T buf, ULONG_T buf_size)
{
  //## begin cConvUtils::BCD2Buf%1092134510.body preserve=yes
   ULONG_T bcd_len = strlen(bcd_str) / 2;
   if (buf_size < bcd_len) {
      return 0;
   }
   BUF_T dst_ptr = buf;
   char * str_ptr = (char*)bcd_str;
   for (ULONG_T i=0; i<bcd_len; i++) {
      *dst_ptr = ByteValue(str_ptr);
      str_ptr += 2;
      dst_ptr++;
   }
   return bcd_len;
  //## end cConvUtils::BCD2Buf%1092134510.body
}

ULONG_T cConvUtils::Compress (BUF_T comp_buf, ULONG_T buf_size, BUF_T buf, ULONG_T len, ULONG_T type)
{
  //## begin cConvUtils::Compress%1092134511.body preserve=yes
   return CompressText(comp_buf, buf, len);
//   return Comp(comp_buf, buf, len);
  //## end cConvUtils::Compress%1092134511.body
}

ULONG_T cConvUtils::Decompress (BUF_T decomp_buf, ULONG_T buf_size, BUF_T buf, ULONG_T len, ULONG_T type)
{
  //## begin cConvUtils::Decompress%1092134512.body preserve=yes
   return DeCompressText(decomp_buf, buf, len);
//   return DeComp(decomp_buf, buf, len);
  //## end cConvUtils::Decompress%1092134512.body
}

ULONG_T cConvUtils::Buf2String(STRING_T &text, BUF_T buf, ULONG_T len)
{
   //## begin cConvUtils::Buf2String%1092208313.body preserve=yes
   text = "bcd('";
   Buf2BCD(text, buf, len);
   text += "')";
   return text.size();
   //## end cConvUtils::Buf2String%1092208313.body
}

ULONG_T cConvUtils::Buf2String(cStringBuffer &text, BUF_T buf, ULONG_T len)
{
   //## begin cConvUtils::Buf2String%1092208313.body preserve=yes
   text += "bcd('";
   Buf2BCD(text, buf, len);
   text += "')";
   return text.size();
   //## end cConvUtils::Buf2String%1092208313.body
}

ULONG_T cConvUtils::String2Buf(CONST_STRING_T text, BUF_T buf, ULONG_T buf_size)
{
  //## begin cConvUtils::String2Buf%1092208314.body preserve=yes
   STRING_T bcd_sequence;
   ULONG_T bcd_len = ExtractBCDSequence(bcd_sequence, text);
   if (bcd_len > 0) {
      return BCD2Buf(bcd_sequence.c_str(), buf, buf_size);
   } else {
      return 0;
   }
  //## end cConvUtils::String2Buf%1092208314.body
}

ULONG_T cConvUtils::BCDBufSize (ULONG_T text_size)
{
   // BCDTextSize inverted
   ULONG_T size = (text_size - 7) / 2;
   return size;
}

ULONG_T cConvUtils::BCDTextSize (ULONG_T buf_size)
{
   // BCDBufSize inverted
   ULONG_T size = (buf_size * 2) + 7;
   return size;
}

ULONG_T cConvUtils::ExtractBCDSequence (STRING_T &bcd_sequence, CONST_STRING_T text)
{
  //## begin cConvUtils::ExtractBCDSequence%1092208315.body preserve=yes
   char c[2] = {0};
   const char * header = "bcd('";
   ULONG_T header_size = strlen(header);
   if (strnicmp(text, header, header_size) == 0) {
      CONST_STRING_T text_ptr = &text[header_size];
      ULONG_T text_len = strlen(text);
      for (ULONG_T i=0; i<text_len; i++) {
         c[0] = *text_ptr;
         if (c[0] == '\'') {
            return i;
         }
         bcd_sequence += c;
         text_ptr++;
      }
   }
   return 0;
  //## end cConvUtils::ExtractBCDSequence%1092208315.body
}

#define CHAR_TEST
#ifdef CHAR_TEST
void charTest()
{
   char c[10] = {0};
   c[0] = '\n';
   c[1] = '\r';
   c[2] = '\t';
   c[3] = '\\';
   c[4] = '\'';
   c[5] = '\"';
   c[6] = '<';
   c[7] = '>';
   c[8] = '&';
   c[9] = '§';
   char chex[10] = {0};
   chex[0] = (char)0x0a;
   chex[1] = (char)0x0d;
   chex[2] = (char)0x09;
   chex[3] = (char)0x5c;
   chex[4] = (char)0x27;
   chex[5] = (char)0x22;
   chex[6] = (char)0x3c;
   chex[7] = (char)0x3e;
   chex[8] = (char)0x26;
   chex[9] = (char)0xa7;
   int i = 0;
   for (int i=0; i<sizeof(c); i++) {
      bool equal = c[i] == chex[i];
      printf("%d: 0x = %x : %s\n", (int)c[i], (int)chex[i], equal ? "true" : "false");
   }
}
#endif

BOOL_T cConvUtils::IsPureString (CONST_STRING_T text)
{
  //## begin cConvUtils::IsPureString%1096898762.body preserve=yes
   ULONG_T len = strlen(text);
   CONST_STRING_T str_ptr = text;
   ULONG_T i = 0;
   while (i < len) {
      char c = *str_ptr;
#define USE_CHAR_TEST
#ifdef USE_CHAR_TEST
      // char based test
      if (c == '\n') return false;
      if (c == '\r') return false;
      if (c == '\t') return false;
      if (c == '\\') return false;
      if (c == '\'') return false;
      if (c == '\"') return false;
      if (c == '<') return false;
      if (c == '>') return false;
      if (c == '&') return false;
      if (c == '§') return false;
#else
      // hex based test
      if (c == (char)0x0a) return false;
      if (c == (char)0x0d) return false;
      if (c == (char)0x09) return false;
      if (c == (char)0x5c) return false;
      if (c == (char)0x27) return false;
      if (c == (char)0x22) return false;
      if (c == (char)0x3c) return false;
      if (c == (char)0x3e) return false;
      if (c == (char)0x26) return false;
      if (c == (char)0x7a) return false;
#endif
      if ((unsigned char)c < (unsigned char)' ') {
         return false;
      }
      str_ptr++;
      i++;
   }
   return true;
  //## end cConvUtils::IsPureString%1096898762.body
}

ULONG_T cConvUtils::Ptr2String (STRING_T &text, PTR_T ptr)
{
  //## begin cConvUtils::Ptr2String%1122544049.body preserve=yes
   char buf[0x200] = {0};
   SafePrintf(buf, sizeof(buf), "memory'%p'", ptr);
   text = buf;
   return 0;
  //## end cConvUtils::Ptr2String%1122544049.body
}

ULONG_T cConvUtils::String2Ptr (PTR_T &ptr, CONST_STRING_T text)
{
  //## begin cConvUtils::String2Ptr%1122544050.body preserve=yes
   PTR_T _ptr = NULL;
   int params = sscanf(text, "memory'%p'", &_ptr);
   if (params == 1) {
      ptr = _ptr;
   }
   return 0;
  //## end cConvUtils::String2Ptr%1122544050.body
}

void cConvUtils::FormatReal (STRING_BUF_T value, UCHAR_T precision)
{
  //## begin cConvUtils::FormatReal%1038473728.body preserve=yes
   BOOL_T precZero = false;
   if (precision == 0) precZero = true; //return;
   unsigned int len = strlen(value);
   BOOL_T decimal_point = false;
   for (unsigned int i=0; i<len; i++) {
      if (decimal_point && precision == 0) {
         value[i] = '\0';
         return;
      }
      if (decimal_point) precision--;
      if (value[i] == '.') {
         if (precZero == true) {
            value[i] = '\0';
            return;
         }
         decimal_point = true;
      }
   }
  //## end cConvUtils::FormatReal%1038473728.body
}

void cConvUtils::FormatInt (STRING_BUF_T value, UCHAR_T precision)
{
  //## begin cConvUtils::FormatInt%1151939529.body preserve=yes
   if (precision >= 0) {
      DOUBLE_T dval = atof(value);
      char value_buf[64] = {0};
      switch (precision) {
      case 0: SafePrintf(value_buf, sizeof(value_buf), "%.0f", dval); break;
      case 1: SafePrintf(value_buf, sizeof(value_buf), "%.1f", dval); break;
      case 2: SafePrintf(value_buf, sizeof(value_buf), "%.2f", dval); break;
      case 3: SafePrintf(value_buf, sizeof(value_buf), "%.3f", dval); break;
      case 4: SafePrintf(value_buf, sizeof(value_buf), "%.4f", dval); break;
      case 5: SafePrintf(value_buf, sizeof(value_buf), "%.5f", dval); break;
      case 6: SafePrintf(value_buf, sizeof(value_buf), "%.6f", dval); break;
      default: SafePrintf(value_buf, sizeof(value_buf), "%f", dval);
      }
      memcpy(value, value_buf, _MIN_(sizeof(value), sizeof(value_buf)));
   }
  //## end cConvUtils::FormatInt%1151939529.body
}

// Additional Declarations
  //## begin cConvUtils%3C7FAFB50192.declarations preserve=yes
  //## end cConvUtils%3C7FAFB50192.declarations

//## begin module%3C7FAFB50192.epilog preserve=yes
//## end module%3C7FAFB50192.epilog

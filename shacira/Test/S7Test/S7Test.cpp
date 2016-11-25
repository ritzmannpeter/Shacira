
#include "stdio.h"
#include "windows.h"
#include "PCS7EASY.h"


#define UNDEFINED      		0
#define SH_VOID      		1
#define SH_CHAR			2
#define SH_UCHAR		3
#define SH_SHORT		4
#define SH_USHORT		5
#define SH_LONG			6
#define SH_ULONG		7
#define SH_FLOAT		8
#define SH_DOUBLE		9
#define SH_STRING		10
#define SH_WSTRING		11
#define SH_BYTE                 12
#define SH_OBJECT               13
#define SH_BIT_8                14
#define SH_BIT_16               15
#define SH_BIT_32               16

typedef char CHAR_T;
typedef unsigned char UCHAR_T;
typedef short SHORT_T;
typedef unsigned short USHORT_T;
typedef long LONG_T;
typedef unsigned long ULONG_T;
typedef UCHAR_T BIT_8_T;
typedef USHORT_T BIT_16_T;
typedef ULONG_T BIT_32_T;
typedef int INT_T;
typedef const char * CONST_STRING_T;

class cError
{
public:
   cError(INT_T err_code, LONG_T native_code, CONST_STRING_T param1 = NULL,
          CONST_STRING_T param2 = NULL,
          CONST_STRING_T param3 = NULL,
          CONST_STRING_T param4 = NULL)
      {
      };

};

class DummyString {
public:
   const char * c_str() {return "das is n string";};
};

class cConvUtils
{
private:
   static DummyString _String;
public:
   static DummyString StringValue(INT_T value) {return _String;};
   
};

DummyString cConvUtils::_String;

#define DEVICE_INVALID_DATATYPE  -999

#define SWAP_WORD(w_val)      (((w_val & 0x00ff) << 8)+((w_val & 0xff00) >> 8))
#define SWAP_DWORD(dw_val)    (((dw_val & 0x0000ffff) << 16) + ((dw_val & 0xffff0000) >> 16))
#define HIGH_WORD(dw_val)     ((unsigned short)(dw_val & 0x0000ffff))
#define LOW_WORD(dw_val)      ((unsigned short)((dw_val & 0xffff0000) >> 16))
#define LONG(high,low)        (low+(high<<16))
#define GET_BIT_B(b_val,pos)   (b_val & (1 << (pos)))
#define GET_BIT_W(w_val,pos)   (w_val & (1 << (pos)))
#define GET_BIT_DW(dw_val,pos) (dw_val & (1 << (pos)))
#define SET_BIT_B(b_val,pos)   (b_val | (1 << (pos)))
#define SET_BIT_W(w_val,pos)   (w_val | (1 << (pos)))
#define SET_BIT_DW(dw_val,pos) (dw_val | (1 << (pos)))
#define RESET_BIT_B(b_val,pos)   ((b_val) & ~(1 << (pos)))
#define RESET_BIT_W(w_val,pos)   ((w_val) & ~(1 << (pos)))
#define RESET_BIT_DW(dw_val,pos)  ((dw_val) & ~(1 << (pos)))


static unsigned short byte_to_word(unsigned short word_value)
{
   return SWAP_WORD(word_value);
}

static unsigned long byte_to_long(unsigned long long_value)
{
   unsigned short high = HIGH_WORD(long_value);
   unsigned short low = LOW_WORD(long_value);
   high = SWAP_WORD(high);
   low = SWAP_WORD(low);
   return LONG(high,low);
}

static unsigned long word_to_long(unsigned long long_value)
{
   return SWAP_DWORD(long_value);
}

class BitOperator {
public:
   BitOperator();
   void SetValue(UCHAR_T data_type, void * value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, UCHAR_T value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, USHORT_T value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, ULONG_T value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, CHAR_T value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, SHORT_T value, UCHAR_T granularity = 1);
   void SetValue(UCHAR_T data_type, LONG_T value, UCHAR_T granularity = 1);
   virtual operator UCHAR_T ();
   virtual operator USHORT_T ();
   virtual operator ULONG_T ();
   virtual operator CHAR_T ();
   virtual operator SHORT_T ();
   virtual operator LONG_T ();
   virtual void SetBit(UCHAR_T pos);
   virtual void ResetBit(UCHAR_T pos);
   virtual UCHAR_T GetBit(UCHAR_T pos);
   virtual void SetPattern(ULONG_T pattern, UCHAR_T pos, UCHAR_T length);
   virtual ULONG_T GetPattern(UCHAR_T pos, UCHAR_T length);
private:
   UCHAR_T _Granularity;
   UCHAR_T _DataType;
   UCHAR_T _CHAR_Value;
   USHORT_T _SHORT_Value;
   ULONG_T _LONG_Value;
};

void BitOperator::SetValue(UCHAR_T data_type, void * value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = *(UCHAR_T*)value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word(*(USHORT_T*)value);
      break;
   case SH_BIT_16:
      _SHORT_Value = *(USHORT_T*)value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(*(ULONG_T*)value);
      break;
   case SH_BIT_32:
      _LONG_Value = *(ULONG_T*)value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, UCHAR_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word(value);
      break;
   case SH_BIT_16:
      _SHORT_Value = value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, USHORT_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = (UCHAR_T)value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word(value);
      break;
   case SH_BIT_16:
      _SHORT_Value = value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, ULONG_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = (UCHAR_T)value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word((UCHAR_T)value);
      break;
   case SH_BIT_16:
      _SHORT_Value = (USHORT_T)value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, CHAR_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word(value);
      break;
   case SH_BIT_16:
      _SHORT_Value = value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, SHORT_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = (UCHAR_T)value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word(value);
      break;
   case SH_BIT_16:
      _SHORT_Value = value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetValue(UCHAR_T data_type, LONG_T value, UCHAR_T granularity)
{
   _Granularity = granularity;
   _DataType = data_type;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = (UCHAR_T)value;
      break;
   case SH_SHORT:
   case SH_USHORT:
      _SHORT_Value = byte_to_word((UCHAR_T)value);
      break;
   case SH_BIT_16:
      _SHORT_Value = (USHORT_T)value;
      break;
   case SH_LONG:
   case SH_ULONG:
      _LONG_Value = byte_to_long(value);
      break;
   case SH_BIT_32:
      _LONG_Value = value;
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

BitOperator::operator UCHAR_T ()
{
   return _CHAR_Value;
}

BitOperator::operator USHORT_T ()
{
   return _SHORT_Value;
}

BitOperator::operator ULONG_T ()
{
   return _LONG_Value;
}

BitOperator::operator CHAR_T ()
{
   return _CHAR_Value;
}

BitOperator::operator SHORT_T ()
{
   return _SHORT_Value;
}

BitOperator::operator LONG_T ()
{
   return _LONG_Value;
}

void BitOperator::SetBit(UCHAR_T pos)
{
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = SET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      _SHORT_Value = SET_BIT_W(_SHORT_Value, pos);
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      _LONG_Value = SET_BIT_DW(_LONG_Value, pos);
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::ResetBit(UCHAR_T pos)
{
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = RESET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      _SHORT_Value = RESET_BIT_W(_SHORT_Value, pos);
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      _LONG_Value = RESET_BIT_DW(_LONG_Value, pos);
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

UCHAR_T BitOperator::GetBit(UCHAR_T pos)
{
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      return GET_BIT_B(_CHAR_Value, pos) > 0;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      return GET_BIT_W(_SHORT_Value, pos) > 0;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      return GET_BIT_DW(_LONG_Value, pos) > 0;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

void BitOperator::SetPattern(ULONG_T pattern, UCHAR_T pos, UCHAR_T length)
{
   UCHAR_T i;
   UCHAR_T set;
   UCHAR_T shift;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      shift = 8 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _CHAR_Value = SET_BIT_B(_CHAR_Value, pos+i);
         } else {
            _CHAR_Value = RESET_BIT_B(_CHAR_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      shift = 16 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _SHORT_Value = SET_BIT_W(_SHORT_Value, pos+i);
         } else {
            _SHORT_Value = RESET_BIT_W(_SHORT_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      shift = 32 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _LONG_Value = SET_BIT_DW(_LONG_Value, pos+i);
         } else {
            _LONG_Value = RESET_BIT_DW(_LONG_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}

ULONG_T BitOperator::GetPattern(UCHAR_T pos, UCHAR_T length)
{
   ULONG_T pattern = 0;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      pattern = ((0xff << (8 - length)) >> (8 - length)) << pos;
      return (_CHAR_Value & pattern) >> pos;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      pattern = ((0xffff << (16 - length)) >> (16 - length)) << pos;
      return (_SHORT_Value & pattern) >> pos;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      pattern = ((0xffffffff << (32 - length)) >> (32 - length)) << pos;
      return (_LONG_Value & pattern) >> pos;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
}


int main(int argc, char* argv[])
{
#ifdef OP_TEST
   unsigned long lvalue;
   //lvalue = byte_to_long(-5555555);
   lvalue = 0;
   unsigned short svalue;
   //svalue = 0x1234;
   svalue = 0;
   BitOperator cast;
   cast.SetValue(SH_BIT_32, &lvalue);
   cast.SetPattern(0xabcd, 8, 16);
   long bit_field;
   bit_field = cast.GetPattern(8, 16);
   bit_field = cast;
   printf("%08.08x\n", bit_field);
   //printf("%d\n", bit_field);
   return 0;
#else
   long hnd = 0;
   int err = 0;
   hnd = ES7OpenEx(0, 2, 1, 19200, 300, 0);
   if (hnd >= 0) {
      unsigned long ulong_value = word_to_long(0x12345678);
      unsigned short ushort_value[2] = {0};
      unsigned char uchar_value[4] = {0};
      *(long*)(uchar_value) = word_to_long(0x12345678);
      ushort_value[0] = *(unsigned short *)(uchar_value);
      ushort_value[1] = *(unsigned short *)(&uchar_value[2]);
#ifdef WRITE_IT
      err = ES7WrW(hnd, 'D', 81, 0, 2, (LPWORD)ushort_value);
      if (err == 0) {
         printf("write W (0,2) %08.08x\n", ulong_value);
      } else {
         printf("failed to write: %d\n", err);
      }
#endif
      ulong_value = 0;
      err = ES7RdDW(hnd, 'D', 81, 0, 1, (LPDWORD)&ulong_value);
      if (err == 0) {
         printf("read DW (0,1) %08.08x\n", ulong_value);
      } else {
         printf("failed to write %d\n", err);
      }
      err = ES7RdW(hnd, 'D', 81, 0, 2, (LPWORD)&ushort_value);
      if (err == 0) {
         for (int i=0; i<2; i++) {
            printf("read W (0,2) %04.04x\n", ushort_value[i]);
         }
         ulong_value = *(unsigned long*)&(ushort_value);
         printf("%08.08x\n", ulong_value);
         ulong_value = word_to_long(ulong_value);
         printf("%08.08x\n", ulong_value);
      } else {
         printf("failed to write %d\n", err);
      }
      err = ES7RdB(hnd, 'D', 81, 0, 4, (LPBYTE)&uchar_value);
      if (err == 0) {
         for (int i=0; i<4; i++) {
            printf("read B (0,4) %02.02x\n", uchar_value[i]);
         }
         ulong_value = *(unsigned long*)&(uchar_value);
         printf("%08.08x\n", ulong_value);
         ulong_value = byte_to_long(ulong_value);
         printf("%08.08x\n", ulong_value);
         USHORT_T usval = *(unsigned short*)&(uchar_value);
         printf("%04.04x\n", usval);
      } else {
         printf("failed to write %d\n", err);
      }
      ES7Close(hnd);
   } else {
      printf("failed tow open: %d\n");
   }
	return 0;
#endif
}


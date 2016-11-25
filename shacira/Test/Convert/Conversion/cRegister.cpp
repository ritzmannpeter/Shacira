
#include "FirstHeader.h"
#include "cRegister.h"
#include "cFMFatFile.h"

cRegister::cRegister(cFMFatFile * file, cSubfile * subfile, REGISTER_T * reg)
{
   _File = file;
   _Elements = 1;
   _Subfile = subfile;
   _RegNo = reg->reg_no;
   _SubfileId = reg->subfile_id;
   _RegType = reg->reg_type;
   _Size = reg->size;
   _ValueSize = reg->value_size;
   int i = 0;
   unsigned_8 * byte_ptr = NULL;
   unsigned_16 * short_ptr = NULL;
   unsigned_32 * long_ptr = NULL;
   int rt = GET_REG_TYPE(reg->reg_type);
   switch (rt) {
   case REG_NOTYPE:     // Bits
      _Values.resize(1);
      byte_ptr = (unsigned_8*)reg->buffer;
      _Values[0] = *byte_ptr;
      break;
   case REG_INT:
      _Values.resize(1);
      short_ptr = (unsigned_16*)reg->buffer;
      _Values[0] = *short_ptr;
      break;
   case REG_DINT:
      _Values.resize(1);
      long_ptr = (unsigned_32*)reg->buffer;
      _Values[0] = *long_ptr;
      break;
   case REG_LONG:
      _Values.resize(1);
      long_ptr = (unsigned_32*)reg->buffer;
      _Values[0] = *long_ptr;
      break;
   case REG_INT10:
      _Values.resize(10);
      short_ptr = (unsigned_16*)reg->buffer;
      for (i=0; i<10; i++) {
         _Values[i] = *short_ptr;
         short_ptr++;
      }
      _Elements = 10;
      break;
   case REG_INT20:
      _Values.resize(20);
      short_ptr = (unsigned_16*)reg->buffer;
      for (i=0; i<20; i++) {
         _Values[i] = *short_ptr;
         short_ptr++;
      }
      _Elements = 20;
      break;
   case REG_LONG10:
      _Values.resize(10);
      long_ptr = (unsigned_32*)reg->buffer;
      for (i=0; i<10; i++) {
         _Values[i] = *long_ptr;
         long_ptr++;
      }
      _Elements = 10;
      break;
   case REG_LONG20:
      _Values.resize(20);
      long_ptr = (unsigned_32*)reg->buffer;
      for (i=0; i<20; i++) {
         _Values[i] = *long_ptr;
         long_ptr++;
      }
      _Elements = 20;
      break;
   case REG_INJTAB:
      break;
   default:
      break;
   }
   subfile->AddRegister(this);
   _Precision = 0;
   _HasDescription = false;
}

cRegister::~cRegister()
{
}

void cRegister::Print(STRING_T & doc)
{
char temp_buf[0x2000] = {0};
   sprintf(temp_buf, "register %d dimsize %d value: %d\n",
           _RegNo, _Values.size(), _Values[0]);
   doc += temp_buf;
}

LONG_T cRegister::LongValue(LONG_T index)
{
   if (index == -1) {
      if (_Values.size() == 1) {
         return _Values[0];
      } else {
         return 0;
      }
   } else {
      if (index < (int)_Values.size()) {
         return _Values[index];
      } else {
         return 0;
      }
   }
}

DOUBLE_T cRegister::DoubleValue(LONG_T index)
{
   return (DOUBLE_T)LongValue(index);
}

STRING_T cRegister::StringValue(LONG_T index)
{
   LONG_T lval = LongValue(index);
   char sval[0x40] = {0};
   if (_Precision == 0) {
      sprintf(sval, "%d", lval);
   } else {
      DOUBLE_T dval = 0;
      ULONG_T div = 10;
      int i = 0;
      for (i=1; i<_Precision; i++) {
         div *= 10;
      }
      dval = (DOUBLE_T)lval / div;
      switch (_Precision) {
      case 1:
         sprintf(sval, "%.1f", dval);
         break;
      case 2:
         sprintf(sval, "%.2f", dval);
         break;
      case 3:
         sprintf(sval, "%.3f", dval);
         break;
      default:
         sprintf(sval, "%f", dval);
         break;
      }
   }
   return sval;
}

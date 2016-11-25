
#include "cLiteWString.h"
#include <malloc.h>

static short EMPTY_STRING[2] = {0};

static short * StrAlloc(unsigned long size)
{
   return (short*)calloc(1, size * sizeof(short));
}

static void StrFree(short * string)
{
   free(string);
}

static unsigned long wstrlen(const short * string)
{
   return 0;
}

static void wstrcpy(short * dst, const short * src)
{
}

static void wstrncpy(short * dst, const short * src, unsigned long len)
{
}

cLiteWString::cLiteWString()
{
   _String = NULL;
   _RefCount = 0;
}

cLiteWString::cLiteWString(const cLiteWString & right)
{
   _String = NULL;
   _RefCount = 0;
   const short * string = right.c_str();
   unsigned long len = wstrlen(string);
   if (len > 0) {
      _String = StrAlloc(len+1);
      wstrcpy(_String, string);
   }
}

cLiteWString::cLiteWString(const short * string)
{
   _String = NULL;
   _RefCount = 0;
   int len = wstrlen(string);
   _String = StrAlloc(len+1);
   wstrcpy(_String, string);
}

cLiteWString::cLiteWString(const short * string, unsigned long len)
{
   _String = NULL;
   _RefCount = 0;
   _String = StrAlloc(len+1);
   wstrncpy(_String, string, len);
}

cLiteWString::~cLiteWString()
{
   if (_String != NULL) {
      StrFree(_String);
      _String = NULL;
   }
}

const short * cLiteWString::c_str() const
{
   if (_String == NULL) {
      return EMPTY_STRING;
   } else {
      return _String;
   }
}

const unsigned long cLiteWString::size() const
{
   if (_String == NULL) {
      return 0;
   } else {
      return wstrlen(_String);
   }
}

cLiteWString cLiteWString::operator +(const cLiteWString & right)
{
   const short * str1 = _String;
   const short * str2 = right.c_str();
   const unsigned long size1 = size();
   const unsigned long size2 = right.size();
   unsigned long new_size = size1 + size2;
   short * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cLiteWString new_string = cLiteWString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cLiteWString cLiteWString::operator +(const short * right)
{
   const short * str1 = _String;
   const short * str2 = right;
   const unsigned long size1 = size();
   unsigned long size2 = wstrlen(right);
   unsigned long new_size = size1 + size2;
   short * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   cLiteWString new_string = cLiteWString(new_buf);
   StrFree(new_buf);
   return new_string;
}

cLiteWString cLiteWString::operator +=(const cLiteWString & right)
{
   const short * str1 = _String;
   const short * str2 = right.c_str();
   const unsigned long size1 = size();
   const unsigned long size2 = right.size();
   unsigned long new_size = size1 + size2;
   short * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteWString cLiteWString::operator +=(const short * right)
{
   const short * str1 = _String;
   const short * str2 = right;
   const unsigned long size1 = size();
   const unsigned long size2 = wstrlen(right);
   unsigned long new_size = size1 + size2;
   short * new_buf = StrAlloc(new_size+1);
   if (str1 != NULL &&
       size1 > 0) {
      memcpy(new_buf, str1, size1);
   }
   if (str2 != NULL &&
       size2 > 0) {
      memcpy(&new_buf[size1], str2, size2);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteWString cLiteWString::operator =(const cLiteWString & right)
{
   short * new_buf = NULL;
   const short * string = right.c_str();
   const unsigned long size = right.size();
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      wstrcpy(new_buf, string);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

cLiteWString cLiteWString::operator =(const short * right)
{
   short * new_buf = NULL;
   const short * string = right;
   const unsigned long size = wstrlen(right);
   if (size > 0) {
      new_buf = StrAlloc(size+1);
      wstrcpy(new_buf, string);
   }
   if (_String != NULL) {
      StrFree(_String);
   }
   _String = new_buf;
   return *this;
}

short cLiteWString::operator [](unsigned long index)
{
   if (_String == NULL) {
      return 0;
   } else {   
      if (index < size()) {
         return _String[index];
      } else {
         return 0;
      }
   }
}

bool cLiteWString::operator ==(const cLiteWString & right)
{
   if (_String == NULL) {
      if (right._String == NULL) {
         return true;
      } else {
         if (_String[0] == 0) {
            return true;
         } else {
            return false;
         }
      }
   } else {   
      int i = 0;
      while (true) {
         if (_String[i] == 0 || right._String[i] == 0) {
            return (_String[i] == right._String[i]);
         } else {
            if (_String[i] != right._String[i]) {
               return false;
            }
         }
         i++;
      }
      return true;
   }
}

bool cLiteWString::operator !=(const cLiteWString & right)
{
   return !(cLiteWString::operator==(right));
}

void cLiteWString::clear()
{
}



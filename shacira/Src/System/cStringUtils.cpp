//## begin module%3B8A254C02DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B8A254C02DA.cm

//## begin module%3B8A254C02DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B8A254C02DA.cp

//## Module: cStringUtils%3B8A254C02DA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cStringUtils.cpp

//## begin module%3B8A254C02DA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B8A254C02DA.additionalIncludes

//## begin module%3B8A254C02DA.includes preserve=yes
//## end module%3B8A254C02DA.includes

// cStringUtils
#include "System/cStringUtils.h"
//## begin module%3B8A254C02DA.additionalDeclarations preserve=yes

#ifdef __NO_SHACIRA__
#include <malloc.h>
#define __SH_ALLOC__(s) calloc(1,s)
#define __SH_FREE__(p) free(p)
#else
#define __SH_ALLOC__(s) cSystemUtils::Alloc(s)
#define __SH_FREE__(p) cSystemUtils::Free(p)
#endif

//## end module%3B8A254C02DA.additionalDeclarations


// Class cStringUtils 

cStringUtils::cStringUtils()
  //## begin cStringUtils::cStringUtils%.hasinit preserve=no
  //## end cStringUtils::cStringUtils%.hasinit
  //## begin cStringUtils::cStringUtils%.initialization preserve=yes
  //## end cStringUtils::cStringUtils%.initialization
{
  //## begin cStringUtils::cStringUtils%.body preserve=yes
  //## end cStringUtils::cStringUtils%.body
}

cStringUtils::cStringUtils(const cStringUtils &right)
  //## begin cStringUtils::cStringUtils%copy.hasinit preserve=no
  //## end cStringUtils::cStringUtils%copy.hasinit
  //## begin cStringUtils::cStringUtils%copy.initialization preserve=yes
  //## end cStringUtils::cStringUtils%copy.initialization
{
  //## begin cStringUtils::cStringUtils%copy.body preserve=yes
  //## end cStringUtils::cStringUtils%copy.body
}


cStringUtils::~cStringUtils()
{
  //## begin cStringUtils::~cStringUtils%.body preserve=yes
  //## end cStringUtils::~cStringUtils%.body
}



//## Other Operations (implementation)
STRING_T cStringUtils::Trim (CONST_STRING_T str, CHAR_T trim_char)
{
  //## begin cStringUtils::Trim%998934605.body preserve=yes
   char buffer[2048] = {0};
   unsigned int buffer_size = 0;
   char * buffer_ptr = NULL;
   int str_len = strlen(str);
   if (str_len < sizeof(buffer) - 1) {
      buffer_size = sizeof(buffer);
      buffer_ptr = buffer;
   } else {
      buffer_size = (str_len + 100);
      buffer_ptr = (char*)__SH_ALLOC__(buffer_size);
      if (buffer_ptr == NULL) return str;
   }
   const char * result = Trim(str, buffer_ptr, buffer_size, trim_char);
   if (str_len >= sizeof(buffer) - 1) {
		__SH_FREE__(buffer_ptr);
   }
   return result;
  //## end cStringUtils::Trim%998934605.body
}

CONST_STRING_T cStringUtils::Trim (CONST_STRING_T str, CHAR_T *buf, UINT_T buf_size, CHAR_T trim_char)
{
  //## begin cStringUtils::Trim%998934606.body preserve=yes
   bool started = false;
   unsigned int str_len = strlen(str);
   if (str_len >= buf_size) return NULL;
   const char * str_ptr = str;
   char * buf_ptr = buf;
   for (unsigned int i=0; i<=str_len; i++) {
      char c = *str_ptr;
      if (!started) {
         if (c == trim_char) {
            str_ptr++;
         } else {
            started = true;
            *buf_ptr = c;
            str_ptr++;
            buf_ptr++;
         }
      } else {
         *buf_ptr = c;
         str_ptr++;
         buf_ptr++;
      }
   }
   int j;
   for (j=strlen(buf)-1; j>=0; j--) {
      char c = buf[j];
      if (c != trim_char) break;
   }
   j++;
   buf[j] = '\0';
   return buf;
  //## end cStringUtils::Trim%998934606.body
}

STRING_T cStringUtils::LTrim (CONST_STRING_T str, CHAR_T trim_char)
{
  //## begin cStringUtils::LTrim%998912330.body preserve=yes
   STRING_T new_buffer = str;
   int str_len = strlen(str);
   int buffer_size = str_len + 1;
   int start_pos = 0;
   if (str[start_pos] == trim_char) {
      int i = start_pos;
      for (i=start_pos; i<str_len; i++) {
         if (str[i] != trim_char) {
            break;
         }
      }
      if (i >= str_len) {
         // string is empty or contains only strip characters
         new_buffer = "";
      } else {
         start_pos = i;
         char * copy_buffer = (char*)cSystemUtils::Alloc(buffer_size);
         memcpy(copy_buffer, &str[start_pos], str_len- start_pos);
         new_buffer = copy_buffer;
         cSystemUtils::Free(copy_buffer);
      }
   }
   return new_buffer;
  //## end cStringUtils::LTrim%998912330.body
}

STRING_T cStringUtils::RTrim (CONST_STRING_T str, CHAR_T trim_char)
{
  //## begin cStringUtils::RTrim%998912331.body preserve=yes
   STRING_T new_buffer = str;
   int str_len = strlen(str);
   int buffer_size = str_len + 1;
   int end_pos = str_len - 1;
   if (str[end_pos] == trim_char) {
      int i = end_pos;
      for (i=end_pos; i>=0; i--) {
         if (str[i] != trim_char) {
            break;
         }
      }
      if (i < 0) {
         // string is empty or contains only strip characters
         new_buffer = "";
      } else {
         end_pos = i;
         char * copy_buffer = (char*)cSystemUtils::Alloc(buffer_size);
         memcpy(copy_buffer, str, end_pos + 1);
         new_buffer = copy_buffer;
         cSystemUtils::Free(copy_buffer);
      }
   }
   return new_buffer;
  //## end cStringUtils::RTrim%998912331.body
}

INT_T cStringUtils::Find (STRING_T &str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::Find%1001511106.body preserve=yes
   return str.find(sub_str);
  //## end cStringUtils::Find%1001511106.body
}

INT_T cStringUtils::Find (CONST_STRING_T str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::Find%1001511107.body preserve=yes
   STRING_T _str = str;
   return Find(_str, sub_str);
  //## end cStringUtils::Find%1001511107.body
}

INT_T cStringUtils::FindFirstOf (STRING_T &str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::FindFirstOf%998912332.body preserve=yes
   return str.find_first_of(sub_str);
  //## end cStringUtils::FindFirstOf%998912332.body
}

INT_T cStringUtils::FindFirstOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::FindFirstOf%998912333.body preserve=yes
   STRING_T _str = str;
   return FindFirstOf(_str, sub_str);
  //## end cStringUtils::FindFirstOf%998912333.body
}

INT_T cStringUtils::FindLastOf (STRING_T &str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::FindLastOf%998912334.body preserve=yes
   return str.find_last_of(sub_str);
  //## end cStringUtils::FindLastOf%998912334.body
}

INT_T cStringUtils::FindLastOf (CONST_STRING_T str, CONST_STRING_T sub_str)
{
  //## begin cStringUtils::FindLastOf%998912335.body preserve=yes
   STRING_T _str = str;
   return FindLastOf(_str, sub_str);
  //## end cStringUtils::FindLastOf%998912335.body
}

STRING_T cStringUtils::Left (STRING_T &str, UINT_T len)
{
  //## begin cStringUtils::Left%998912336.body preserve=yes
   if (len > str.size()) {
      return str.c_str();
   } else {
      return STRING_T(str.c_str(), len);
   }
  //## end cStringUtils::Left%998912336.body
}

STRING_T cStringUtils::Left (CONST_STRING_T str, UINT_T len)
{
  //## begin cStringUtils::Left%998912337.body preserve=yes
   STRING_T _str = str;
   return Left(_str, len);
  //## end cStringUtils::Left%998912337.body
}

STRING_T cStringUtils::Right (STRING_T &str, UINT_T len)
{
  //## begin cStringUtils::Right%998912338.body preserve=yes
   if (len > str.size()) {
      return str.c_str();
   } else {
      int pos = str.size() - len;
      return &str.c_str()[pos];
   }
  //## end cStringUtils::Right%998912338.body
}

STRING_T cStringUtils::Right (CONST_STRING_T str, UINT_T len)
{
  //## begin cStringUtils::Right%998912339.body preserve=yes
   STRING_T _str = str;
   return Right(_str, len);
  //## end cStringUtils::Right%998912339.body
}

STRING_T cStringUtils::Replace (STRING_T &str, CONST_STRING_T sub_str, CONST_STRING_T rep_str)
{
  //## begin cStringUtils::Replace%998912354.body preserve=yes
   int sub_len = strlen(sub_str);
   int rep_len = strlen(rep_str);
   STRING_T new_string = str.c_str();
   int search_pos = 0;
   int pos = new_string.find(sub_str, search_pos);
   while (pos >= 0) {
      new_string.replace(pos, sub_len, rep_str);
      search_pos = pos + rep_len;
      pos = new_string.find(sub_str, search_pos);
   }
   return new_string;
  //## end cStringUtils::Replace%998912354.body
}

void cStringUtils::LeftSplit (CONST_STRING_T str, STRING_T &head, STRING_T &tail, CHAR_T separator)
{
  //## begin cStringUtils::LeftSplit%1082991646.body preserve=yes
   char delimiters[2] = {0};
   delimiters[0] = separator;
   int pos = FindFirstOf(str, delimiters);
   if (pos < 0) {
      head = str;
      tail = "";
   } else {
      head = Left(str, pos);
      tail = Right(str, strlen(str) - (pos + 1));
   }
  //## end cStringUtils::LeftSplit%1082991646.body
}

void cStringUtils::GetStringSequence (CONST_STRING_T str, STRING_T &sequence, int &nchars, CHAR_T separator)
{
  //## begin cStringUtils::GetStringSequence%1108111661.body preserve=yes
   char buffer[2] = {0};
   int i, len = strlen(str);
   int separator_count = 0;
   nchars = 0;
   for (i=0; i<len; i++) {
      char c = str[i];
      if (c == separator) {
         if (separator_count == 0) {
            separator_count++;
         } else if (separator_count == 1) {
            nchars++;
            return;
         }
      } else {
         if (separator_count == 0) {
            // ignore
         } else if (separator_count == 1) {
            buffer[0] = c;
            sequence += buffer;
         } else {
            return;
         }
      }
      nchars++;
   }
  //## end cStringUtils::GetStringSequence%1108111661.body
}

// Additional Declarations
  //## begin cStringUtils%3B8A254C02DA.declarations preserve=yes
  //## end cStringUtils%3B8A254C02DA.declarations

//## begin module%3B8A254C02DA.epilog preserve=yes
//## end module%3B8A254C02DA.epilog

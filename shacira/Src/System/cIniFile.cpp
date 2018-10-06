//## begin module%3DC930C0035D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DC930C0035D.cm

//## begin module%3DC930C0035D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DC930C0035D.cp

//## Module: cIniFile%3DC930C0035D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cIniFile.cpp

//## begin module%3DC930C0035D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DC930C0035D.additionalIncludes

//## begin module%3DC930C0035D.includes preserve=yes
//## end module%3DC930C0035D.includes

// cTokenizer
#include "System/cTokenizer.h"
// cIniFile
#include "System/cIniFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3DC930C0035D.additionalDeclarations preserve=yes
//## end module%3DC930C0035D.additionalDeclarations


// Class cIniFile 





cIniFile::cIniFile()
  //## begin cIniFile::cIniFile%.hasinit preserve=no
  //## end cIniFile::cIniFile%.hasinit
  //## begin cIniFile::cIniFile%.initialization preserve=yes
  //## end cIniFile::cIniFile%.initialization
{
  //## begin cIniFile::cIniFile%.body preserve=yes
_ASSERT_UNCOND
  //## end cIniFile::cIniFile%.body
}

cIniFile::cIniFile(const cIniFile &right)
  //## begin cIniFile::cIniFile%copy.hasinit preserve=no
  //## end cIniFile::cIniFile%copy.hasinit
  //## begin cIniFile::cIniFile%copy.initialization preserve=yes
  //## end cIniFile::cIniFile%copy.initialization
{
  //## begin cIniFile::cIniFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cIniFile::cIniFile%copy.body
}

cIniFile::cIniFile (CONST_STRING_T file_name)
  //## begin cIniFile::cIniFile%1036595113.hasinit preserve=no
  //## end cIniFile::cIniFile%1036595113.hasinit
  //## begin cIniFile::cIniFile%1036595113.initialization preserve=yes
  //## end cIniFile::cIniFile%1036595113.initialization
{
  //## begin cIniFile::cIniFile%1036595113.body preserve=yes
   _FileName = cFileSystemUtils::FullPath(file_name);
   if (!cFileSystemUtils::FileExists(_FileName.c_str())) {
//      InfoPrintf("Ini file %s does not exist\n", _FileName.c_str());
   } else {
      LoadFile(_FileName.c_str());
   }
  //## end cIniFile::cIniFile%1036595113.body
}


cIniFile::~cIniFile()
{
  //## begin cIniFile::~cIniFile%.body preserve=yes
   CHAPTER_VECTOR_T::const_iterator i = _Chapters.cbegin();
   while (i != _Chapters.cend()) {
      cChapter * chapter = (*i);
      delete chapter;
      i++;
   }
  //## end cIniFile::~cIniFile%.body
}



//## Other Operations (implementation)
BOOL_T cIniFile::Exists ()
{
  //## begin cIniFile::Exists%1036595115.body preserve=yes
   if (cFileSystemUtils::FileExists(_FileName.c_str())) {
      return true;
   } else {
      return false;
   }
  //## end cIniFile::Exists%1036595115.body
}

ULONG_T cIniFile::ReadChapters (STRING_VECTOR_T &chapters)
{
  //## begin cIniFile::ReadChapters%1036595116.body preserve=yes
   int old_size = chapters.size();
   int noof_chapters = _Chapters.size();
   chapters.resize(noof_chapters);
   int new_size = chapters.size();
   for (int i=old_size; i<new_size; i++) {
      chapters[i] = _Chapters[i - old_size]->_Name.c_str();
   }
   return _Chapters.size();
  //## end cIniFile::ReadChapters%1036595116.body
}

ULONG_T cIniFile::ReadKeys (CONST_STRING_T chapter_name, STRING_VECTOR_T &keys)
{
  //## begin cIniFile::ReadKeys%1036595117.body preserve=yes
   cChapter * chapter = Chapter(chapter_name);
   if (chapter != NULL) {
      return chapter->ReadKeys(keys);
   } else {
      return 0;
   }
  //## end cIniFile::ReadKeys%1036595117.body
}

STRING_T cIniFile::ReadValue (CONST_STRING_T chapter_name, CONST_STRING_T key_name, CONST_STRING_T default_value)
{
  //## begin cIniFile::ReadValue%1036595118.body preserve=yes
   cChapter * chapter = Chapter(chapter_name);
   if (chapter == NULL) return default_value;
   STRING_T key_value = chapter->ReadKeyValue(key_name);
   if (key_value.size() == 0) return default_value;
   return key_value;
  //## end cIniFile::ReadValue%1036595118.body
}

void cIniFile::ReadValue (char *buf, ULONG_T buf_size, CONST_STRING_T chapter_name, CONST_STRING_T key_name, CONST_STRING_T default_value)
{
  //## begin cIniFile::ReadValue%1134632033.body preserve=yes
   memset(buf, 0, buf_size);
   memcpy(buf, default_value, _MIN_(strlen(default_value), buf_size - 1));
   cChapter * chapter = Chapter(chapter_name);
   if (chapter == NULL) {
      return;
   }
   STRING_T key_value = chapter->ReadKeyValue(key_name);
   if (key_value.size() > 0) {
      memset(buf, 0, buf_size);
      memcpy(buf, key_value.c_str(), _MIN_(key_value.size(), buf_size - 1));
   }
  //## end cIniFile::ReadValue%1134632033.body
}

LONG_T cIniFile::ReadLong (CONST_STRING_T chapter_name, CONST_STRING_T key_name, LONG_T default_value)
{
  //## begin cIniFile::ReadLong%1036595119.body preserve=yes
   cChapter * chapter = Chapter(chapter_name);
   if (chapter == NULL) return default_value;
   STRING_T key_value = chapter->ReadKeyValue(key_name);
   if (key_value.size() == 0) return default_value;
   return atol(key_value.c_str());
  //## end cIniFile::ReadLong%1036595119.body
}

BOOL_T cIniFile::ReadBool (CONST_STRING_T chapter_name, CONST_STRING_T key_name, BOOL_T default_value)
{
  //## begin cIniFile::ReadBool%1036595120.body preserve=yes
   cChapter * chapter = Chapter(chapter_name);
   if (chapter == NULL) return default_value;
   STRING_T key_value = chapter->ReadKeyValue(key_name);
   if (key_value.size() == 0) return default_value;
   if (_stricmp("true", key_value.c_str()) == 0) {
      return true;
   } else {
      return false;
   }
  //## end cIniFile::ReadBool%1036595120.body
}

BOOL_T cIniFile::WriteValue (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value)
{
  //## begin cIniFile::WriteValue%1037097989.body preserve=yes
   cFileSystemUtils::WriteProfileString(chapter, key, value, _FileName.c_str());
   return true;
  //## end cIniFile::WriteValue%1037097989.body
}

BOOL_T cIniFile::WriteLong (CONST_STRING_T chapter, CONST_STRING_T key, LONG_T value)
{
  //## begin cIniFile::WriteLong%1037097990.body preserve=yes
   char s_value[32] = {0};
   ltoa(value, s_value, 10);
   WriteValue(chapter, key, s_value);
   return true;
  //## end cIniFile::WriteLong%1037097990.body
}

BOOL_T cIniFile::WriteBool (CONST_STRING_T chapter, CONST_STRING_T key, BOOL_T value)
{
  //## begin cIniFile::WriteBool%1037097991.body preserve=yes
   const char * s_value = value ? "true" : "false";
   WriteValue(chapter, key, s_value);
   return true;
  //## end cIniFile::WriteBool%1037097991.body
}

void cIniFile::AddChapter (cChapter *chapter)
{
  //## begin cIniFile::AddChapter%1036595121.body preserve=yes
   int size = _Chapters.size();
   _Chapters.resize(size+1);
   _Chapters[size] = chapter;
  //## end cIniFile::AddChapter%1036595121.body
}

void cIniFile::LoadFile (CONST_STRING_T file_name)
{
  //## begin cIniFile::LoadFile%1036595122.body preserve=yes
   cChapter * act_chapter = NULL;
   char read_buf[8192];
   FILE * stream = fopen(file_name, "r");
   if (stream != NULL) {
      memset(read_buf, 0, sizeof(read_buf));
      int len = ReadLine(read_buf, sizeof(read_buf), stream);
      while (len >= 0) {
         if (len > 0) {
            cChapter * chapter = NewChapter(read_buf);
            if (chapter != NULL) {
               if (act_chapter != NULL) {
                  AddChapter(act_chapter);
               }
               act_chapter = chapter;
            } else {
               cKey * key = NewKey(read_buf);
               if (key != NULL) {
                  if (act_chapter != NULL) {
                     act_chapter->AddKey(key);
                  }
               }
            }
         }
         memset(read_buf, 0, sizeof(read_buf));
         len = ReadLine(read_buf, sizeof(read_buf), stream);
      }
      if (act_chapter != NULL) {
         AddChapter(act_chapter);
      }
      fclose(stream);
   }
  //## end cIniFile::LoadFile%1036595122.body
}

INT_T cIniFile::ReadLine (CHAR_T *buf, ULONG_T buf_len, FILE *stream)
{
  //## begin cIniFile::ReadLine%1036595123.body preserve=yes
   int len = 0;
   char * buf_ptr = buf;
   ULONG_T i = 0;
   for (i=0; i<buf_len-1; i++) {
      int c = fgetc(stream);
      if (c == EOF) {
         if (len == 0) {
            return -1;
         } else {
            return len;
         }
      }
      if (c == '\n') {
         if (len > 0) {
            char last_char = *(buf_ptr-1);
            if (last_char == '\\') {
               len--;
               buf_ptr--;
               continue;
            } else {
               break;
            }
         } else {
            break;
         }
      } else if (c == ';' && len == 0) {
         while (c != EOF && c != '\n') {
            c = fgetc(stream);
         }
         break;
      }
      *buf_ptr = (char)c;
      buf_ptr++;
      len++;
   }
   if (i == buf_len-1) {
      throw cError(INI_FILE_LINE_LENGTH_EXCEEDED, 0,
                   cConvUtils::StringValue(buf_len).c_str(),
                   _FileName.c_str());
   }
   return len;
  //## end cIniFile::ReadLine%1036595123.body
}

cChapter * cIniFile::NewChapter (CONST_STRING_T buf)
{
  //## begin cIniFile::NewChapter%1036595124.body preserve=yes
   char chapter_name[128] = {0};
   if (sscanf(buf, "[%[^]]]", chapter_name) == 1) {
      cChapter * chapter = new cChapter(chapter_name);
      return chapter;
   }
   return NULL;
  //## end cIniFile::NewChapter%1036595124.body
}

cChapter * cIniFile::Chapter (CONST_STRING_T chapter_name)
{
  //## begin cIniFile::Chapter%1036595125.body preserve=yes
   int size = _Chapters.size();
   for (int i=0; i<size; i++) {
      cChapter * chapter = _Chapters[i];
      if (strcmp(chapter_name, chapter->_Name.c_str()) == 0) return chapter;
   }
   return NULL;
  //## end cIniFile::Chapter%1036595125.body
}

cKey * cIniFile::NewKey (CONST_STRING_T buf)
{
  //## begin cIniFile::NewKey%1036595126.body preserve=yes
   STRING_T key_name;
   cTokenizer tokenizer(buf, strlen(buf));
   const char * token = tokenizer.GetToken("=");
   if (token != NULL) {
      key_name = token;
      token = tokenizer.GetToken();
      if (token != NULL) {
         cKey * key = new cKey(key_name.c_str(), token);
         return key;
      }
   }
   return NULL;
  //## end cIniFile::NewKey%1036595126.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cIniFile::get_FileName () const
{
  //## begin cIniFile::get_FileName%3DC930C00384.get preserve=no
  return _FileName;
  //## end cIniFile::get_FileName%3DC930C00384.get
}

// Additional Declarations
  //## begin cIniFile%3DC930C0035D.declarations preserve=yes
  //## end cIniFile%3DC930C0035D.declarations

//## begin module%3DC930C0035D.epilog preserve=yes
//## end module%3DC930C0035D.epilog

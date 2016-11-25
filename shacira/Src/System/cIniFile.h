//## begin module%3DC930C0035D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DC930C0035D.cm

//## begin module%3DC930C0035D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DC930C0035D.cp

//## Module: cIniFile%3DC930C0035D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cIniFile.h

#ifndef cIniFile_h
#define cIniFile_h 1

//## begin module%3DC930C0035D.includes preserve=yes
//## end module%3DC930C0035D.includes

// cError
#include "System/cError.h"

class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3DC930C0035D.additionalDeclarations preserve=yes

class cKey
{
public:
   STRING_T _Key;
   STRING_T _Value;
public:
   cKey(CONST_STRING_T key, CONST_STRING_T value)
   {
      _Key = key;
      _Value = value;
   };
   virtual ~cKey()
   {
   };
};

typedef std::vector<cKey*> KEY_VECTOR_T;

class cChapter
{
public:
   STRING_T _Name;
   KEY_VECTOR_T _Keys;
public:
   cChapter(CONST_STRING_T name) {_Name = name;};
   virtual ~cChapter()
   {
      int size = _Keys.size();
      for (int i=0; i<size; i++) {
         delete _Keys[i];
      }
   };
   void AddKey(cKey * key)
   {
      int size = _Keys.size();
      _Keys.resize(size+1);
      _Keys[size] = key;
   };
   unsigned long ReadKeys(STRING_VECTOR_T & keys)
   {
      int old_size = keys.size();
      int noof_keys = _Keys.size();
      keys.resize(noof_keys);
      int new_size = keys.size();
      for (int i=old_size; i<new_size; i++) {
         keys[i] = _Keys[i - old_size]->_Key.c_str();
      }
      return _Keys.size();
   };
   STRING_T ReadKeyValue(CONST_STRING_T key_name)
   {
      cKey * key = Key(key_name);
      if (key == NULL) {
         return "";
      } else {
         return key->_Value.c_str();
      }
   };
private:
   cKey * Key(CONST_STRING_T key_name)
   {
      int size = _Keys.size();
      for (int i=0; i<size; i++) {
         cKey * key = _Keys[i];
         if (strcmp(key_name, key->_Key.c_str()) == 0) return key;
      }
      return NULL;
   };
};

typedef std::vector<cChapter*> CHAPTER_VECTOR_T;

//## end module%3DC930C0035D.additionalDeclarations


//## begin cIniFile%3DC930C0035D.preface preserve=yes
//## end cIniFile%3DC930C0035D.preface

//## Class: cIniFile%3DC930C0035D
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DC930C0035E;cError { -> }
//## Uses: <unnamed>%3DC936520368;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3DC936660186;cTokenizer { -> F}

class __DLL_EXPORT__ cIniFile 
{
  //## begin cIniFile%3DC930C0035D.initialDeclarations preserve=yes
public:
  //## end cIniFile%3DC930C0035D.initialDeclarations

    //## Constructors (generated)
      cIniFile();

      cIniFile(const cIniFile &right);

    //## Constructors (specified)
      //## Operation: cIniFile%1036595113
      cIniFile (CONST_STRING_T file_name);

    //## Destructor (generated)
      virtual ~cIniFile();


    //## Other Operations (specified)
      //## Operation: Exists%1036595115
      BOOL_T Exists ();

      //## Operation: ReadChapters%1036595116
      ULONG_T ReadChapters (STRING_VECTOR_T &chapters);

      //## Operation: ReadKeys%1036595117
      ULONG_T ReadKeys (CONST_STRING_T chapter_name, STRING_VECTOR_T &keys);

      //## Operation: ReadValue%1036595118
      STRING_T ReadValue (CONST_STRING_T chapter_name, CONST_STRING_T key_name, CONST_STRING_T default_value = "");

      //## Operation: ReadValue%1134632033
      void ReadValue (char *buf, ULONG_T buf_size, CONST_STRING_T chapter_name, CONST_STRING_T key_name, CONST_STRING_T default_value = "");

      //## Operation: ReadLong%1036595119
      LONG_T ReadLong (CONST_STRING_T chapter_name, CONST_STRING_T key_name, LONG_T default_value = 0);

      //## Operation: ReadBool%1036595120
      BOOL_T ReadBool (CONST_STRING_T chapter_name, CONST_STRING_T key_name, BOOL_T default_value = false);

      //## Operation: WriteValue%1037097989
      BOOL_T WriteValue (CONST_STRING_T chapter, CONST_STRING_T key, CONST_STRING_T value);

      //## Operation: WriteLong%1037097990
      BOOL_T WriteLong (CONST_STRING_T chapter, CONST_STRING_T key, LONG_T value);

      //## Operation: WriteBool%1037097991
      BOOL_T WriteBool (CONST_STRING_T chapter, CONST_STRING_T key, BOOL_T value);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: FileName%3DC930C00384
      STRING_T get_FileName () const;

  public:
    // Additional Public Declarations
      //## begin cIniFile%3DC930C0035D.public preserve=yes
      //## end cIniFile%3DC930C0035D.public

  protected:
    // Data Members for Class Attributes

      //## begin cIniFile::FileName%3DC930C00384.attr preserve=no  public: STRING_T {U} 
      STRING_T _FileName;
      //## end cIniFile::FileName%3DC930C00384.attr

    // Additional Protected Declarations
      //## begin cIniFile%3DC930C0035D.protected preserve=yes
      //## end cIniFile%3DC930C0035D.protected

  private:
    // Additional Private Declarations
      //## begin cIniFile%3DC930C0035D.private preserve=yes
      //## end cIniFile%3DC930C0035D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AddChapter%1036595121
      void AddChapter (cChapter *chapter);

      //## Operation: LoadFile%1036595122
      void LoadFile (CONST_STRING_T file_name);

      //## Operation: ReadLine%1036595123
      INT_T ReadLine (CHAR_T *buf, ULONG_T buf_len, FILE *stream);

      //## Operation: NewChapter%1036595124
      cChapter * NewChapter (CONST_STRING_T buf);

      //## Operation: Chapter%1036595125
      cChapter * Chapter (CONST_STRING_T chapter_name);

      //## Operation: NewKey%1036595126
      cKey * NewKey (CONST_STRING_T buf);

    // Data Members for Class Attributes

      //## Attribute: Chapters%3DC930C00385
      //## begin cIniFile::Chapters%3DC930C00385.attr preserve=no  implementation: CHAPTER_VECTOR_T {U} 
      CHAPTER_VECTOR_T _Chapters;
      //## end cIniFile::Chapters%3DC930C00385.attr

    // Additional Implementation Declarations
      //## begin cIniFile%3DC930C0035D.implementation preserve=yes
      //## end cIniFile%3DC930C0035D.implementation

};

//## begin cIniFile%3DC930C0035D.postscript preserve=yes
//## end cIniFile%3DC930C0035D.postscript

// Class cIniFile 

//## begin module%3DC930C0035D.epilog preserve=yes
//## end module%3DC930C0035D.epilog


#endif

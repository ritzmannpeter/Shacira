//## begin module%3C42C8DA0041.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C42C8DA0041.cm

//## begin module%3C42C8DA0041.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C42C8DA0041.cp

//## Module: cTypeFactory%3C42C8DA0041; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cTypeFactory.cpp

//## begin module%3C42C8DA0041.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C42C8DA0041.additionalIncludes

//## begin module%3C42C8DA0041.includes preserve=yes

#include "System/Sys/cSHFile.h"

//## end module%3C42C8DA0041.includes

// cTokenizer
#include "System/cTokenizer.h"
// cIniFile
#include "System/cIniFile.h"
// cStringUtils
#include "System/cStringUtils.h"
// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cTypeDef
#include "System/Config/cTypeDef.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3C42C8DA0041.additionalDeclarations preserve=yes
//## end module%3C42C8DA0041.additionalDeclarations


// Class cTypeFactory 








cTypeFactory::cTypeFactory()
  //## begin cTypeFactory::cTypeFactory%.hasinit preserve=no
      : _DefFile("Shacira.def")
  //## end cTypeFactory::cTypeFactory%.hasinit
  //## begin cTypeFactory::cTypeFactory%.initialization preserve=yes
  //## end cTypeFactory::cTypeFactory%.initialization
{
  //## begin cTypeFactory::cTypeFactory%.body preserve=yes
   STRING_VECTOR_T empty;
   Load(_DefFile.c_str(), empty);
  //## end cTypeFactory::cTypeFactory%.body
}

cTypeFactory::cTypeFactory(const cTypeFactory &right)
  //## begin cTypeFactory::cTypeFactory%copy.hasinit preserve=no
      : _DefFile("Shacira.def")
  //## end cTypeFactory::cTypeFactory%copy.hasinit
  //## begin cTypeFactory::cTypeFactory%copy.initialization preserve=yes
  //## end cTypeFactory::cTypeFactory%copy.initialization
{
  //## begin cTypeFactory::cTypeFactory%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTypeFactory::cTypeFactory%copy.body
}

cTypeFactory::cTypeFactory (CONST_STRING_T def_file, STRING_VECTOR_T path)
  //## begin cTypeFactory::cTypeFactory%1011171075.hasinit preserve=no
      : _DefFile("Shacira.def")
  //## end cTypeFactory::cTypeFactory%1011171075.hasinit
  //## begin cTypeFactory::cTypeFactory%1011171075.initialization preserve=yes
  //## end cTypeFactory::cTypeFactory%1011171075.initialization
{
  //## begin cTypeFactory::cTypeFactory%1011171075.body preserve=yes
//   _DefFile = def_file;
   Load(_DefFile.c_str(), path);
   STRING_T config_path = cResources::ConfigPath();
   STRING_T app_def_file = cFileSystemUtils::AppendPath(config_path.c_str(), "application.def");
   cSHFile file(app_def_file.c_str());
   if (file.Exists()) {
      Load(app_def_file.c_str(), path);
   }
  //## end cTypeFactory::cTypeFactory%1011171075.body
}


cTypeFactory::~cTypeFactory()
{
  //## begin cTypeFactory::~cTypeFactory%.body preserve=yes
   std::map<STRING_T, cTypeDef*>::const_iterator i = _TypeDefs.cbegin();
   while (i != _TypeDefs.cend()) {
      cTypeDef * type_def = (*i).second;
      if (type_def != NULL) delete type_def;
      i++;
   }
   _TypeDefs.clear();
  //## end cTypeFactory::~cTypeFactory%.body
}



//## Other Operations (implementation)
BaseTypes cTypeFactory::BaseType (CONST_STRING_T name)
{
  //## begin cTypeFactory::BaseType%1011013290.body preserve=yes
   cTypeDef * type_def = Definition(name);
   if (type_def != NULL) {
      return type_def->get_BaseType();
   } else {
      return UndefinedBaseType;
   }
  //## end cTypeFactory::BaseType%1011013290.body
}

cTypeDef * cTypeFactory::Definition (CONST_STRING_T name)
{
  //## begin cTypeFactory::Definition%1011013292.body preserve=yes
   std::map<STRING_T, cTypeDef*>::const_iterator def = _TypeDefs.find(name);
   if (def == _TypeDefs.cend()) {
      return NULL;
   } else {
      return (*def).second;
   }
  //## end cTypeFactory::Definition%1011013292.body
}

BOOL_T cTypeFactory::ParseList (CONST_STRING_T buffer, STRING_LIST_T &string_list)
{
  //## begin cTypeFactory::ParseList%1011095979.body preserve=yes
   const char * token = NULL;
   cTokenizer tokenizer(buffer, strlen(buffer));
   while ((token = tokenizer.GetToken(",")) != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      token = sval.c_str();
      string_list.push_back(token);
   }
   return true;
  //## end cTypeFactory::ParseList%1011095979.body
}

BOOL_T cTypeFactory::ParseList (CONST_STRING_T buffer, DOUBLE_LIST_T &real_list)
{
  //## begin cTypeFactory::ParseList%1011095980.body preserve=yes
   const char * token = NULL;
   cTokenizer tokenizer(buffer, strlen(buffer));
   while ((token = tokenizer.GetToken(",")) != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      token = sval.c_str();
      double fval = atof(token);
      real_list.push_back(fval);
   }
   return true;
  //## end cTypeFactory::ParseList%1011095980.body
}

BOOL_T cTypeFactory::ParseRange (CONST_STRING_T buffer, DOUBLE_T &min, DOUBLE_T &max)
{
  //## begin cTypeFactory::ParseRange%1011095981.body preserve=yes
   const char * token = NULL;
   cTokenizer tokenizer(buffer, strlen(buffer));
   int i = 0;
   while ((token = tokenizer.GetToken(",")) != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      token = sval.c_str();
      double fval = atof(token);
      if (i == 0) min = fval;
      if (i == 1 && strlen(token) > 0) return false;
      if (i == 2) max = fval;
      i++;
   }
   return true;
  //## end cTypeFactory::ParseRange%1011095981.body
}

void cTypeFactory::ParseType (CONST_STRING_T buffer, STRING_T &type_name, BOOL_T &is_vector)
{
  //## begin cTypeFactory::ParseType%1011095982.body preserve=yes
   cTokenizer tokenizer(buffer, strlen(buffer));
   const char * token = tokenizer.GetToken("<");
   if (token != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      token = sval.c_str();
      if (strcmp(token, "Vector") == 0) {
         token = tokenizer.GetToken(">");
         if (token != NULL) {
            sval = cStringUtils::Trim(token);
            token = sval.c_str();
            if (strlen(token) > 0) {
               is_vector = true;
               type_name = token;
            }
         } else {
            throw cError(CONFIG_INVALID_TYPESPEC, 0, buffer);
         }
      } else {
         is_vector = false;
         type_name = buffer;
      }
   } else {
      throw cError(CONFIG_NO_TYPESPEC, 0);
   }
   //## end cTypeFactory::ParseType%1011095982.body
}

void cTypeFactory::Load (CONST_STRING_T def_file_name, STRING_VECTOR_T &path)
{
  //## begin cTypeFactory::Load%1011013289.body preserve=yes
   AddBasicTypes();
   STRING_T def_file;
   for (unsigned int i=0; i<path.size(); i++) {
      def_file = cFileSystemUtils::AppendPath(path[i].c_str(), def_file_name);
      if (LoadFile(def_file.c_str())) {
         return;
      }
   }
   throw cError(CONFIG_FILE_NOT_FOUND, 0, def_file_name);
  //## end cTypeFactory::Load%1011013289.body
}

BOOL_T cTypeFactory::LoadFile (CONST_STRING_T def_file)
{
  //## begin cTypeFactory::LoadFile%1037089035.body preserve=yes
   cIniFile ini_file(def_file);
   if (!ini_file.Exists()) return false;
   STRING_VECTOR_T chapters;
   ini_file.ReadChapters(chapters);
   STRING_VECTOR_T::const_iterator _chapter = chapters.cbegin();
   while (_chapter != chapters.cend()) {
      STRING_T obj_name = (*_chapter).c_str();
      STRING_T type_name = ini_file.ReadValue(obj_name.c_str(), "Type", "");
      cTypeDef * type_def = Definition(obj_name.c_str());
      BOOL_T reused = false;
      if (type_def == NULL) {
         type_def = new cTypeDef(obj_name.c_str(), this);
         _TypeDefs[obj_name.c_str()] = type_def;
      } else {
         reused = true;
      }
      if (strcmp(type_name.c_str(), "Object") == 0 ||
          reused) {
         type_def->SetBaseType(ObjectDef);
         STRING_VECTOR_T properties;
         ini_file.ReadKeys(obj_name.c_str(), properties);
         STRING_VECTOR_T::const_iterator property = properties.cbegin();
         while (property != properties.cend()) {
            STRING_T property_name = (*property).c_str();
            if (strcmp(property_name.c_str(), "Type") != 0) {
               STRING_T property_type = ini_file.ReadValue(obj_name.c_str(), property_name.c_str(), "");;
               type_def->SetPropertyDef(property_name.c_str(), property_type.c_str());
            }
            property++;
         }
      } else {
         STRING_T range = ini_file.ReadValue(obj_name.c_str(), "Range", "");
         if (strcmp(type_name.c_str(), "Numeric") == 0) {
            type_def->SetBaseType(Numeric);
            type_def->SetRange(range.c_str());
         } else if (strcmp(type_name.c_str(), "String") == 0) {
            type_def->SetBaseType(String);
            type_def->SetRange(range.c_str());
         } else {
            type_def->SetBaseType(TypeDef);
            type_def->SetDefName(type_name.c_str());
         }
      }
      _chapter++;
   }
   std::map<STRING_T, cTypeDef*>::const_iterator def = _TypeDefs.cbegin();
   while (def != _TypeDefs.cend()) {
      cTypeDef * type_def = (*def).second;
      type_def->Resolve();
      def++;
   }
   return true;
  //## end cTypeFactory::LoadFile%1037089035.body
}

void cTypeFactory::AddBasicTypes ()
{
  //## begin cTypeFactory::AddBasicTypes%1011021295.body preserve=yes
   cTypeDef * type_def = NULL;
   // String
   type_def = new cTypeDef("String", this);
   type_def->SetBaseType(String);
   type_def->SetRangeType(Unlimited);
   _TypeDefs["String"] = type_def;
   // Numeric
   type_def = new cTypeDef("Numeric", this);
   type_def->SetBaseType(Numeric);
   type_def->SetRangeType(Unlimited);
   _TypeDefs["Numeric"] = type_def;
  //## end cTypeFactory::AddBasicTypes%1011021295.body
}

// Additional Declarations
  //## begin cTypeFactory%3C42C8DA0041.declarations preserve=yes
  //## end cTypeFactory%3C42C8DA0041.declarations

//## begin module%3C42C8DA0041.epilog preserve=yes
//## end module%3C42C8DA0041.epilog

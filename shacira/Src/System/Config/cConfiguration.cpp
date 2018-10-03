//## begin module%3A54333102CF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A54333102CF.cm

//## begin module%3A54333102CF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A54333102CF.cp

//## Module: cConfiguration%3A54333102CF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cConfiguration.cpp

//## begin module%3A54333102CF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A54333102CF.additionalIncludes

//## begin module%3A54333102CF.includes preserve=yes
//## end module%3A54333102CF.includes

// cTokenizer
#include "System/cTokenizer.h"
// cIniFile
#include "System/cIniFile.h"
// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cConfiguration
#include "System/Config/cConfiguration.h"
// cProperty
#include "System/Config/cProperty.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3A54333102CF.additionalDeclarations preserve=yes
//## end module%3A54333102CF.additionalDeclarations


// Class cConfiguration 





cConfiguration::cConfiguration()
  //## begin cConfiguration::cConfiguration%.hasinit preserve=no
      : _TypeFactory(NULL)
  //## end cConfiguration::cConfiguration%.hasinit
  //## begin cConfiguration::cConfiguration%.initialization preserve=yes
  //## end cConfiguration::cConfiguration%.initialization
{
  //## begin cConfiguration::cConfiguration%.body preserve=yes
_ASSERT_UNCOND
  //## end cConfiguration::cConfiguration%.body
}

cConfiguration::cConfiguration(const cConfiguration &right)
  //## begin cConfiguration::cConfiguration%copy.hasinit preserve=no
      : _TypeFactory(NULL)
  //## end cConfiguration::cConfiguration%copy.hasinit
  //## begin cConfiguration::cConfiguration%copy.initialization preserve=yes
  //## end cConfiguration::cConfiguration%copy.initialization
{
  //## begin cConfiguration::cConfiguration%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConfiguration::cConfiguration%copy.body
}

cConfiguration::cConfiguration (CONST_STRING_T config_file_name)
  //## begin cConfiguration::cConfiguration%1011095973.hasinit preserve=no
      : _TypeFactory(NULL)
  //## end cConfiguration::cConfiguration%1011095973.hasinit
  //## begin cConfiguration::cConfiguration%1011095973.initialization preserve=yes
  //## end cConfiguration::cConfiguration%1011095973.initialization
{
  //## begin cConfiguration::cConfiguration%1011095973.body preserve=yes
   STRING_T config_file = cFileSystemUtils::FullPath(config_file_name);
   STRING_VECTOR_T files;
   STRING_VECTOR_T path;
   STRING_T def_file_name;
   AddPath(cFileSystemUtils::DirName(config_file.c_str()).c_str());
   cIniFile ini_file(config_file.c_str());
   if (!ini_file.Exists()) {
      throw cError(CONFIG_FILE_NOT_FOUND, 0, config_file.c_str());
   }

   def_file_name = ini_file.ReadValue("Configuration", "DefFile", "");
   if (def_file_name.size() == 0) {
      throw cError(CONFIG_NO_DEFFILE_SPEC, 0, config_file.c_str());
   }

   _TypeFactory = new cTypeFactory(def_file_name.c_str(), _Path);

   
   
   
   Load(config_file.c_str());
   cConfigurationObject * config_obj = Object("Configuration");
   if (config_obj == NULL) {
      throw cError(CONFIG_NO_CONFIGOBJECT_SPEC, 0, config_file.c_str());
   }
   config_obj->PropertyValue("Path", path);
   unsigned int i = 0;
   for (i=0; i<path.size(); i++) {
      AddPath(cFileSystemUtils::FullPath(path[i].c_str()).c_str());
   }
   config_obj->PropertyValue("Files", files);
   for (i=0; i<files.size(); i++) {
      Load(files[i].c_str());
   }
   Resolve();
  //## end cConfiguration::cConfiguration%1011095973.body
}


cConfiguration::~cConfiguration()
{
  //## begin cConfiguration::~cConfiguration%.body preserve=yes
   std::map<STRING_T, cConfigurationObject*>::const_iterator i = _ConfigurationObjects.cbegin();
   while (i != _ConfigurationObjects.cend()) {
      cConfigurationObject * object = (*i).second;
      DELETE_OBJECT(cConfigurationObject, object)
      i++;
   }
   _ConfigurationObjects.clear();
  //## end cConfiguration::~cConfiguration%.body
}



//## Other Operations (implementation)
cTypeFactory * cConfiguration::TypeFactory () const
{
  //## begin cConfiguration::TypeFactory%1011095976.body preserve=yes
   return _TypeFactory;
  //## end cConfiguration::TypeFactory%1011095976.body
}

cConfigurationObject * cConfiguration::Object (CONST_STRING_T name) const
{
  //## begin cConfiguration::Object%978594334.body preserve=yes
   std::map<STRING_T,cConfigurationObject*>::const_iterator i = _ConfigurationObjects.find(name);
   if (i == _ConfigurationObjects.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cConfiguration::Object%978594334.body
}

ULONG_T cConfiguration::ObjectList (STRING_LIST_T &object_list, CONST_STRING_T type_name)
{
  //## begin cConfiguration::ObjectList%1011204313.body preserve=yes
   std::map<STRING_T, cConfigurationObject*>::const_iterator i = _ConfigurationObjects.cbegin();
   while (i != _ConfigurationObjects.cend()) {
      cConfigurationObject * object = (*i).second;
      if (object != NULL) {
         if (type_name == NULL) {
            object_list.push_back((*i).first);
         } else {
            STRING_T object_type_name = object->get_TypeName().c_str();
            if (IDENTIFIER_EQUAL(type_name, object_type_name.c_str())) {
               object_list.push_back((*i).first);
            }
         }
      }
      i++;
   }
   return object_list.size();
  //## end cConfiguration::ObjectList%1011204313.body
}

void cConfiguration::Resolve ()
{
  //## begin cConfiguration::Resolve%1011095991.body preserve=yes
   std::map<STRING_T, cConfigurationObject*>::const_iterator i = _ConfigurationObjects.cbegin();
   while (i != _ConfigurationObjects.cend()) {
      cConfigurationObject * object = (*i).second;
      object->Resolve();
      i++;
   }
  //## end cConfiguration::Resolve%1011095991.body
}

void cConfiguration::Save ()
{
  //## begin cConfiguration::Save%978594328.body preserve=yes
   std::map<STRING_T, cConfigurationObject*>::const_iterator i = _ConfigurationObjects.cbegin();
   while (i != _ConfigurationObjects.cend()) {
      cConfigurationObject * object = (*i).second;
      object->Save();
      i++;
   }
  //## end cConfiguration::Save%978594328.body
}

CONST_STRING_T cConfiguration::DefaultConfigFile ()
{
  //## begin cConfiguration::DefaultConfigFile%1037033504.body preserve=yes
   return "Shacira.cfg";
  //## end cConfiguration::DefaultConfigFile%1037033504.body
}

void cConfiguration::AddPath (CONST_STRING_T path)
{
  //## begin cConfiguration::AddPath%1037033505.body preserve=yes
   int index = _Path.size();
   _Path.resize(index+1);
   _Path[index] = path;
  //## end cConfiguration::AddPath%1037033505.body
}

void cConfiguration::Load (CONST_STRING_T config_file_name)
{
  //## begin cConfiguration::Load%1037033506.body preserve=yes
   STRING_T config_file;
   for (unsigned int i=0; i<_Path.size(); i++) {
      config_file = cFileSystemUtils::AppendPath(_Path[i].c_str(), config_file_name);
      if (LoadFile(config_file.c_str())) {
         return;
      }
   }
   throw cError(CONFIG_FILE_NOT_FOUND, 0, config_file_name);
  //## end cConfiguration::Load%1037033506.body
}

BOOL_T cConfiguration::LoadFile (CONST_STRING_T config_file)
{
  //## begin cConfiguration::LoadFile%1011171077.body preserve=yes
   cIniFile ini_file(config_file);
   if (!ini_file.Exists()) {
      return false;
   }
   STRING_VECTOR_T chapters;
   ini_file.ReadChapters(chapters);
   STRING_VECTOR_T::const_iterator _chapter = chapters.cbegin();
   while (_chapter != chapters.cend()) {
      STRING_T obj_name = (*_chapter).c_str();
      STRING_T obj_type = ini_file.ReadValue(obj_name.c_str(), "Type", "no type");
      cConfigurationObject * object = new cConfigurationObject(this, obj_name.c_str(), obj_type.c_str(), config_file);
      if (Object(obj_name.c_str()) == NULL) {
         STRING_VECTOR_T keys;
         ini_file.ReadKeys(obj_name.c_str(), keys);
         STRING_VECTOR_T::const_iterator _key = keys.cbegin();
         while (_key != keys.cend()) {
            STRING_T property_name = (*_key).c_str();
            STRING_T value = ini_file.ReadValue(obj_name.c_str(), property_name.c_str(), "");
            if (!IDENTIFIER_EQUAL("Type", property_name.c_str())) {
               cProperty * property = new cProperty(object, property_name.c_str(), value.c_str());
               object->SetProperty(property);
            }
            _key++;
         }
         _ConfigurationObjects[obj_name.c_str()] = object;
      } else {
         throw cError(CONFIG_AMBIGUOUS_OBJECT, 0, obj_name.c_str());
      }
      _chapter++;
   }
   return true;
  //## end cConfiguration::LoadFile%1011171077.body
}

// Additional Declarations
  //## begin cConfiguration%3A54333102CF.declarations preserve=yes
  //## end cConfiguration%3A54333102CF.declarations

//## begin module%3A54333102CF.epilog preserve=yes
//## end module%3A54333102CF.epilog

//## begin module%411212750138.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411212750138.cm

//## begin module%411212750138.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%411212750138.cp

//## Module: cSubFile%411212750138; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cSubFile.cpp

//## begin module%411212750138.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%411212750138.additionalIncludes

//## begin module%411212750138.includes preserve=yes
//## end module%411212750138.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cVariable
#include "System/Database/cVariable.h"
// cSubFile
#include "Control/LocalDatabase/cSubFile.h"
#include "System/Sys/cStringBuffer.h"

//## begin module%411212750138.additionalDeclarations preserve=yes

/// PR 28.01.16 - added cStringBuffer based method cSubFile::PrintVariables(cStringBuffer &buf)
///               that avoids extensive memory consumption

//## end module%411212750138.additionalDeclarations


// Class cSubFile 



cSubFile::cSubFile()
  //## begin cSubFile::cSubFile%.hasinit preserve=no
  //## end cSubFile::cSubFile%.hasinit
  //## begin cSubFile::cSubFile%.initialization preserve=yes
  //## end cSubFile::cSubFile%.initialization
{
  //## begin cSubFile::cSubFile%.body preserve=yes
_ASSERT_UNCOND
  //## end cSubFile::cSubFile%.body
}

cSubFile::cSubFile(const cSubFile &right)
  //## begin cSubFile::cSubFile%copy.hasinit preserve=no
  //## end cSubFile::cSubFile%copy.hasinit
  //## begin cSubFile::cSubFile%copy.initialization preserve=yes
  //## end cSubFile::cSubFile%copy.initialization
{
  //## begin cSubFile::cSubFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSubFile::cSubFile%copy.body
}

cSubFile::cSubFile (CONST_STRING_T name)
  //## begin cSubFile::cSubFile%1091705311.hasinit preserve=no
  //## end cSubFile::cSubFile%1091705311.hasinit
  //## begin cSubFile::cSubFile%1091705311.initialization preserve=yes
  //## end cSubFile::cSubFile%1091705311.initialization
{
  //## begin cSubFile::cSubFile%1091705311.body preserve=yes
   _Name = name;
  //## end cSubFile::cSubFile%1091705311.body
}


cSubFile::~cSubFile()
{
  //## begin cSubFile::~cSubFile%.body preserve=yes
  //## end cSubFile::~cSubFile%.body
}



//## Other Operations (implementation)
void cSubFile::AddVariable (CONST_STRING_T name, cVariable *variable)
{
  //## begin cSubFile::AddVariable%1091699609.body preserve=yes
   _Variables[name] = variable;
  //## end cSubFile::AddVariable%1091699609.body
}

void cSubFile::PrintVariables(STRING_T &buf)
{
   //## begin cSubFile::PrintVariables%1092126570.body preserve=yes
   STRING_T db;
   db += "database ";
   db += _Name.c_str();
   db += " {\n";
   std::map<STRING_T, cVariable*>::const_iterator i = _Variables.cbegin();
   while (i != _Variables.cend()) {
      STRING_T var_name = (*i).first;
      cVariable * variable = (*i).second;
      cVarDef * var_def = variable->_VarDef;
      if (var_def != NULL) {
         STRING_T var_spec;
         var_def->Unparse(var_spec, IGN_DESCRIPTION | IGN_UNIT_TEXT | USE_DATASET_PRECISION);
         db += var_spec.c_str();
      }
      i++;
   }
   db += "};\n";
   buf = db;
   //## end cSubFile::PrintVariables%1092126570.body
}

void cSubFile::PrintVariables(cStringBuffer &buf)
{
   //## begin cSubFile::PrintVariables%1092126570.body preserve=yes
   buf += "database ";
   buf += _Name.c_str();
   buf += " {\n";
   std::map<STRING_T, cVariable*>::const_iterator i = _Variables.cbegin();
   while (i != _Variables.cend()) {
      STRING_T var_name = (*i).first;
      cVariable * variable = (*i).second;
      cVarDef * var_def = variable->_VarDef;
      if (var_def != NULL) {
         var_def->Unparse(buf, IGN_DESCRIPTION | IGN_UNIT_TEXT | USE_DATASET_PRECISION);
      }
      i++;
   }
   buf += "};\n";
   //## end cSubFile::PrintVariables%1092126570.body
}

void cSubFile::ExportVariables(STRING_T &buf, CONST_STRING_T separator)
{
   //## begin cSubFile::PrintVariables%1092126570.body preserve=yes
   STRING_T db;
   //db += "database ";
   //db += _Name.c_str();
   //db += " {\n";
   std::map<STRING_T, cVariable*>::const_iterator i = _Variables.begin();
   while (i != _Variables.end()) {
      STRING_T var_name = (*i).first;
      cVariable * variable = (*i).second;
      cVarDef * var_def = variable->_VarDef;
      if (var_def != NULL) {
         STRING_T var_spec;
         var_def->Unparse(var_spec, IGN_DESCRIPTION | IGN_UNIT_TEXT | USE_DATASET_PRECISION | USE_EXPORT_FORMAT, separator);
         db += var_spec.c_str();
      }
      i++;
   }
   buf = db;
   //## end cSubFile::PrintVariables%1092126570.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSubFile::get_Name () const
{
  //## begin cSubFile::get_Name%411219CC006D.get preserve=no
  return _Name;
  //## end cSubFile::get_Name%411219CC006D.get
}

// Additional Declarations
  //## begin cSubFile%411212750138.declarations preserve=yes
  //## end cSubFile%411212750138.declarations

//## begin module%411212750138.epilog preserve=yes
//## end module%411212750138.epilog

//## begin module%3B87B9CC0371.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B87B9CC0371.cm

//## begin module%3B87B9CC0371.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3B87B9CC0371.cp

//## Module: cOptions%3B87B9CC0371; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cOptions.cpp

//## begin module%3B87B9CC0371.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B87B9CC0371.additionalIncludes

//## begin module%3B87B9CC0371.includes preserve=yes
//## end module%3B87B9CC0371.includes

// cOptions
#include "System/Process/cOptions.h"
// cSHFile
#include "System/Sys/cSHFile.h"
//## begin module%3B87B9CC0371.additionalDeclarations preserve=yes
//## end module%3B87B9CC0371.additionalDeclarations


// Class cOptions 


cOptions::cOptions()
  //## begin cOptions::cOptions%.hasinit preserve=no
  //## end cOptions::cOptions%.hasinit
  //## begin cOptions::cOptions%.initialization preserve=yes
  //## end cOptions::cOptions%.initialization
{
  //## begin cOptions::cOptions%.body preserve=yes
  //## end cOptions::cOptions%.body
}

cOptions::cOptions(const cOptions &right)
  //## begin cOptions::cOptions%copy.hasinit preserve=no
  //## end cOptions::cOptions%copy.hasinit
  //## begin cOptions::cOptions%copy.initialization preserve=yes
  //## end cOptions::cOptions%copy.initialization
{
  //## begin cOptions::cOptions%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cOptions::cOptions%copy.body
}

cOptions::cOptions (int argc, char **argv)
  //## begin cOptions::cOptions%998750938.hasinit preserve=no
  //## end cOptions::cOptions%998750938.hasinit
  //## begin cOptions::cOptions%998750938.initialization preserve=yes
  //## end cOptions::cOptions%998750938.initialization
{
  //## begin cOptions::cOptions%998750938.body preserve=yes
   STRING_T option_string = ReadArgs();
   Parse(option_string.c_str());
   option_string = "";;
   for (int i=1; i<argc; i++) {
      if (i > 1) option_string += " ";
      option_string += argv[i];
   }
   Parse(option_string.c_str());
  //## end cOptions::cOptions%998750938.body
}


cOptions::~cOptions()
{
  //## begin cOptions::~cOptions%.body preserve=yes
  //## end cOptions::~cOptions%.body
}



//## Other Operations (implementation)
void cOptions::SetOption (CONST_STRING_T option_name, CONST_STRING_T value)
{
  //## begin cOptions::SetOption%1074682887.body preserve=yes
   _Options[option_name] = value;
  //## end cOptions::SetOption%1074682887.body
}

void cOptions::GetOption (CONST_STRING_T option_name, STRING_T &value)
{
  //## begin cOptions::GetOption%1074682888.body preserve=yes
   STRING_T option_value;
   if (Option(option_name, option_value)) {
      value = option_value;
   }
  //## end cOptions::GetOption%1074682888.body
}

void cOptions::GetOption (CONST_STRING_T option_name, LONG_T &value)
{
  //## begin cOptions::GetOption%1074682889.body preserve=yes
   STRING_T option_value;
   if (Option(option_name, option_value)) {
      value = atol(option_value.c_str());
   }
  //## end cOptions::GetOption%1074682889.body
}

void cOptions::GetOption (CONST_STRING_T option_name, DOUBLE_T &value)
{
  //## begin cOptions::GetOption%1074682890.body preserve=yes
   STRING_T option_value;
   if (Option(option_name, option_value)) {
      value = atof(option_value.c_str());
   }
  //## end cOptions::GetOption%1074682890.body
}

void cOptions::GetOption (CONST_STRING_T option_name, BOOL_T &value)
{
  //## begin cOptions::GetOption%1074682891.body preserve=yes
   STRING_T option_value;
   if (Option(option_name, option_value)) {
      const char * oval = option_value.c_str();
      if (_stricmp(oval, "true") == 0) {
         value = true;
      } else if (_stricmp(oval, "yes") == 0) {
         value = true;
      } else if (_stricmp(oval, "wahr") == 0) {
         value = true;
      } else if (_stricmp(oval, "ja") == 0) {
         value = true;
      } else if (_stricmp(oval, "false") == 0) {
         value = false;
      } else if (_stricmp(oval, "no") == 0) {
         value = false;
      } else if (_stricmp(oval, "falsch") == 0) {
         value = false;
      } else if (_stricmp(oval, "nein") == 0) {
         value = false;
      } else {
         LONG_T lval = atol(oval);
         if (lval == 0) {
            value = false;
         } else {
            value = true;
         }
      }
   }
  //## end cOptions::GetOption%1074682891.body
}

BOOL_T cOptions::IsSet (CONST_STRING_T option_name)
{
  //## begin cOptions::IsSet%998750940.body preserve=yes
   STRING_T value;
   return Option(option_name, value);
  //## end cOptions::IsSet%998750940.body
}

BOOL_T cOptions::IsArgsFileFound () 
{
   cSHFile file("args");
   return file.Exists() ? true : false;
}

BOOL_T cOptions::Option (CONST_STRING_T option_name, STRING_T &value)
{
  //## begin cOptions::Option%1074682892.body preserve=yes
   STRING_MAP_T::const_iterator i = _Options.find(option_name);
   if (i == _Options.end()) {
      return false;
   } else {
      value = (*i).second.c_str();
      return true;
   }
  //## end cOptions::Option%1074682892.body
}

void cOptions::Parse (CONST_STRING_T option_string)
{
  //## begin cOptions::Parse%1074682894.body preserve=yes
#define SINIT        0
#define SNAME        1
#define SVALUE       2
#define SSEPARATOR   3
#define SWHITE       4
   char state = SNAME;
   CONST_STRING_T ptr = option_string;
   STRING_T name;
   STRING_T value;
   while (*ptr != 0) {
      char c = *ptr;
      if (c == '=') {
         state = SSEPARATOR;
      } else if (c == ' ' ||
                 c == '\t' ||
                 c == '\n' ||
                 c == '\r') {
         if (state != SSEPARATOR) {
            state = SWHITE;
         }
         // ignore white spaces
      } else {
         if (state == SNAME) {
            name += c;
         } else if (state == SVALUE) {
            value += c;
         } else if (state == SSEPARATOR) {
            state = SVALUE;
            value += c;
         } else if (state == SWHITE) {
            state = SNAME;
            if (name.size() > 0) {
               SetOption(name.c_str(), value.c_str());
               name = "";;
               value = "";;
            }
            name += c;
         }
      }
      ptr++;
   }
   if (name.size() > 0) {
      SetOption(name.c_str(), value.c_str());
   }
  //## end cOptions::Parse%1074682894.body
}

STRING_T cOptions::ReadArgs ()
{
  //## begin cOptions::ReadArgs%1074682895.body preserve=yes
   STRING_T args;
   STRING_T line;
   cSHFile file("args");
   if (file.Open(FILE_ACCESS_READ_ONLY)) {
      while (file.ReadLine(line)) {
         if (line.size() > 0
             && line[0] != ';') {
            args += " ";
            args += line.c_str();
         }
      }
      file.Close();
   }
   return args;
  //## end cOptions::ReadArgs%1074682895.body
}

// Additional Declarations
  //## begin cOptions%3B87B9CC0371.declarations preserve=yes
  //## end cOptions%3B87B9CC0371.declarations

//## begin module%3B87B9CC0371.epilog preserve=yes
//## end module%3B87B9CC0371.epilog

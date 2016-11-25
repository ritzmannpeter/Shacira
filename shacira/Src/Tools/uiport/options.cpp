
#include "options.h"

cOptions & options()
{
   static cOptions _options;
   return _options;
}

static string parameterFromText(const string & text)
{
   string parameter;
   int pos = (int)text.find(' ');
   if (pos > 0) {
      parameter = text.substr(0, pos);
   } else {
      parameter = text;
   }
   return parameter;
}

cOption::cOption(const string & name, const string & code, const string & parameterName, const string & description)
   : _name(name), _code(code), _parameterName(parameterName), _description(description), _set(false)
{
}

cOption::cOption(const string & name, const string & code, const string & description)
   : _name(name), _code(code), _description(description), _set(false)
{
}


bool cOptions::parseArgs(int argc, char ** argv)
{
   string command;
   int i = 0;
   for (i=0; i<argc; i++) {
      const char * arg = argv[i];
      command += arg;
      command += ' ';
   }
   string argString;
   for (i=1; i<argc; i++) {
      const char * arg = argv[i];
      argString += arg;
      argString += ' ';
   }
   string code;
   string parameter;
   string tail;
   while (getNextArg(argString, code, parameter, tail)) {
      setOption(code, parameter);
      argString = tail;
   }
   return true;
}

bool cOptions::addOption(const string & name, const string & code, const string & parameterName, const string & description)
{
   if (hasOption(name)) {
      return false;
   } else {
      cOption * option = new cOption(name, code, parameterName, description);
      _optionMap[name] = option;
      return true;
   }
}

bool cOptions::addOption(const string & name, const string & code, const string & description)
{
   if (hasOption(name)) {
      return false;
   } else {
      cOption * option = new cOption(name, code, description);
      _optionMap[name] = option;
      return true;
   }
}

const cOption * cOptions::getOption(const string & name) const
{
   OPTION_MAP_T::const_iterator i = _optionMap.find(name);
   if (i == _optionMap.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

string cOptions::usage() const
{
   string usage;
   OPTION_MAP_T::const_iterator i = _optionMap.begin();
   while (i != _optionMap.end()) {
      const cOption * option = (*i).second;
      usage += option->code();
      if (option->hasParameter()) {
         usage += "<";
         usage += option->parameterName();
         usage += ">";
      }
      usage += " : ";
      usage += option->description();
      usage += "\n";
      i++;
   }
   return usage;
}

void cOptions::setOption(const string & code, const string & parameter)
{
   OPTION_MAP_T::const_iterator i = _optionMap.begin();
   while (i != _optionMap.end()) {
      cOption * option = (*i).second;
      if (code == option->code()) {
         option->set(true);
         option->setParameter(parameter);
         return;
      }
      i++;
   }
}

string cOptions::parameter(const string & name) const
{
   const cOption * option = getOption(name);
   if (option == NULL) {
      return "";
   } else {
      return option->parameter();
   }
}

bool cOptions::isSet(const string & name) const
{
   const cOption * option = getOption(name);
   if (option == NULL) {
      return false;
   } else {
      return option->set();
   }
}

bool cOptions::getNextArg(const string & argString, string & code, string & parameter, string & tail)
{
   if (argString.empty()) {
      return false;
   } else {
      int length = (int)argString.size();
      int startPos = (int)argString.find('-');
      string tempString = argString.substr(startPos+1, length);
      int endPos = (int)tempString.find('-');
      if (endPos < 0) {
         endPos = length;
      }
      if (startPos >= 0 && endPos >= 0) {
         code = argString.substr(startPos, 2);
         parameter = argString.substr(startPos + 3, endPos - startPos - 2);
#ifdef test
string t = trim("      heinz .              fuzzy     ");
t = trim("heinz .     fuzzy");
t = trim("  a   b c d e f g");
t = trim("a b c       d e f g    ");
#endif
         parameter = trim(parameter);
         tail = argString.substr(endPos, length);
         return true;
      } else {
         return false;
      }
   }
}

string cOptions::trim(const string & text)
{
   string trimmedText = text;
   bool trimIt = false;
   int textLen = (int)text.size();
   int startPos = 0;
   int endPos = textLen - 1;
   int i = 0;
   for (i=0; i<textLen; i++) {
      if (text[i] == ' ') {
         startPos++;
         trimIt = true;
      } else {
         break;
      }
   }
   for (i=textLen-1; i>=0; i--) {
      if (text[i] == ' ') {
         endPos--;
         trimIt = true;
      } else {
         break;
      }
   }
   if (trimIt) {
      int trimLen = endPos - startPos + 1;
      trimmedText = text.substr(startPos, trimLen);
   }
   return trimmedText;
}


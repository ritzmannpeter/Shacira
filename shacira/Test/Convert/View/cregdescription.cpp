
#include "FirstHeader.h"
#include "cRegDescription.h"

/// register descriptions are stored in a register description file
/// with the following format: (one line per register)
/// <register no>;<register description(text)>;<precision>;
/// when the first character of the line is a semicolon,
/// the description will be ignored, this property corresponds
/// with the register filter that can be enabled (registers that have no
/// description are not displayed, see slot SelectFile of cSubfileList).
/// the last column (precision) can be ommitted (default is 0)

cRegDescription::cRegDescription(CONST_STRING_T line)
{
   _RegNo = 0;
   _IsValid = false;
   _Precision = 0;
   Parse(line);
}

cRegDescription::~cRegDescription()
{
}

void cRegDescription::Parse(CONST_STRING_T line)
{
   if (strlen(line) > 0) {
      if (line[0] != ';') {
         char text[0x400] = {0};
         int reg_no = 0;
         int precision = 0;
         int params = sscanf(line, "%d;%[^;];%d", &reg_no, text, &precision);
         if (params == 3) {
            _RegNo = reg_no;
            _Text = text;
            _Precision = precision;
            if (_Text.size() > 0) {
               _IsValid = true;
            }
         } else {
            params = sscanf(line, "%d;%[^;];", &reg_no, text, precision);
            if (params == 2) {
               _RegNo = reg_no;
               _Text = text;
               _Precision = precision;
               if (_Text.size() > 0) {
                  _IsValid = true;
               }
            }
         }
      }
   }
}

cRegDescriptions::cRegDescriptions()
{
}

cRegDescriptions::~cRegDescriptions()
{
   Clear();
}

void cRegDescriptions::Load(CONST_STRING_T file)
{
   FILE * stream = fopen(file, "r");
   if (stream != NULL) {
      char line[0x400] = {0};
      char * line_ptr = NULL;
      while ((line_ptr = fgets(line, sizeof(line), stream)) != NULL) {
         cRegDescription * reg_description = new cRegDescription(line);
         if (reg_description->_IsValid) {
            _RegDescriptions[reg_description->_RegNo] = reg_description;
         } else {
            delete reg_description;
         }
      }
      fclose(stream);
   }
}

void cRegDescriptions::Clear()
{
   REG_DESCRIPTION_MAP_T::const_iterator i = _RegDescriptions.begin();
   while (i != _RegDescriptions.end()) {
      delete (*i).second;
      i++;
   }
   _RegDescriptions.clear();
}

BOOL_T cRegDescriptions::Present(LONG_T reg_no)
{
   REG_DESCRIPTION_MAP_T::const_iterator i = _RegDescriptions.find(reg_no);
   if (i != _RegDescriptions.end()) {
      if ((*i).second->_IsValid) {
         return true;
      }
   }
   return false;
}

STRING_T cRegDescriptions::Text(LONG_T reg_no)
{
   REG_DESCRIPTION_MAP_T::const_iterator i = _RegDescriptions.find(reg_no);
   if (i != _RegDescriptions.end()) {
      return (*i).second->_Text;
   }
   return "";
}

UCHAR_T cRegDescriptions::Precision(LONG_T reg_no)
{
   REG_DESCRIPTION_MAP_T::const_iterator i = _RegDescriptions.find(reg_no);
   if (i != _RegDescriptions.end()) {
      return (*i).second->_Precision;
   }
   return 0;
}


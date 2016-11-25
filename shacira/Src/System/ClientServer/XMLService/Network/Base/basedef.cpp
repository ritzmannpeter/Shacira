
#include "basedef.h"

bool writeToFile(const string & file, const string & data)
{
   unsigned long size = (unsigned long)data.size();
   ofstream outFile(file.c_str());
   if (outFile.is_open()) {
      outFile.write(data.c_str(), size);
      outFile.close();
      return true;
   } else {
      return false;
   }
}

bool readFileContent(const string & file, string & data)
{
   data.clear();
   ifstream inFile(file.c_str());
   if (inFile.is_open()) {
      string line;
      while (getline(inFile, line)) {
         data += line;
#ifdef lassma // utf8 stuff use utf8 library from resources
         // check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
         string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
         if (end_it != line.end()) {
            cout << "Invalid UTF-8 encoding detected at line " << line_count << "\n";
            cout << "This part is fine: " << string(line.begin(), end_it) << "\n";
         }
         // Get the line length (at least for the valid part)
         int length = utf8::distance(line.begin(), end_it);
         cout << "Length of line " << line_count << " is " << length <<  "\n";
         // Convert it to utf-16
         vector<unsigned short> utf16line;
         utf8::utf8to16(line.begin(), end_it, back_inserter(utf16line));
         // And back to utf-8
         string utf8line; 
         utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(utf8line));
         // Confirm that the conversion went OK:
         if (utf8line != string(line.begin(), end_it)) {
            cout << "Error in UTF-16 conversion at line: " << line_count << "\n";        
            line_count++;
         }
#endif
      }
      return true;
   } else {
      return false;
   }
}



#ifndef _basedef_h_
#define _basedef_h_

#include <stddef.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

typedef unsigned char OCTET_T;
typedef size_t LENGTH_T;

inline string ntos(size_t n)
{
   stringstream ss;
   ss << n;
   return ss.str();
}

inline string itos(int n)
{
   stringstream ss;
   ss << n;
   return ss.str();
}

inline string utos(unsigned int n)
{
   stringstream ss;
   ss << n;
   return ss.str();
}

inline string dtos(double d)
{
   stringstream ss;
   ss << d;
   return ss.str();
}

inline string toLower(const string & str)
{
   string lower = str;
   std::transform(lower.begin(), lower.end(), lower.begin(), tolower);
   return lower;
}

inline string toUpper(const string & str)
{
   string upper = str;
   std::transform(upper.begin(), upper.end(), upper.begin(), toupper);
   return upper;
}

inline bool nextCSVToken(int & pos, string & token, const string & line)
{
   token = "";
   if (pos == (int)line.size()) {
      return false;
   } else {
      int i = 0;
      int size = (int)line.size();
      for (i = pos; i<size; i++) {
         if (line[i] == ';') {
            pos = i + 1;
            return true;
         } else {
            token += line[i];
         }
      }
      pos = i;
      return true;
   }
}

inline string unspecificPath(const string & path)
{
   string unspecificPath = path;
   int len = (int)unspecificPath.size();
   int i = 0;
   for (i=0; i<len; i++) {
      if (unspecificPath[i] == '\\') {
         unspecificPath[i] = '/';
      }
   }
   return unspecificPath;
}

bool writeToFile(const string & file, const string & data);
bool readFileContent(const string & file, string & data);

//#define SYS_ERROR(msg)
typedef std::list<string> STRING_LIST_T;

#endif

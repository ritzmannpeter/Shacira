
#ifndef _options_h_
#define _options_h_

#include <string>
#include <map>
using namespace std;

class cOption
{
public:
   cOption(const string & name, const string & code, const string & parameterName, const string & description);
   cOption(const string & name, const string & code, const string & description);
   inline string name() const {return _name;};
   inline string code() const {return _code;};
   inline bool hasParameter() const {return !_parameterName.empty();};
   inline string parameterName() const {return _parameterName;};
   inline string parameter() const {return _parameter;};
   inline void setParameter(string value) {_parameter = value;};
   inline string description() const {return _description;};
   inline bool set() const {return _set;};
   inline void set(bool value) {_set = value;};
private:
   string _name;
   string _code;
   string _parameter;
   string _parameterName;
   string _description;
   bool _set;
};
typedef std::map<string, cOption*> OPTION_MAP_T;

class cOptions
{
public:
   cOptions() {};
   bool addOption(const string & name, const string & code, const string & parameterName, const string & description);
   bool addOption(const string & name, const string & code, const string & description);
   bool parseArgs(int argc, char ** argv);
   const cOption * getOption(const string & name) const;
   inline bool hasOption(const string & name) const {return (getOption(name) != NULL);};
   inline const OPTION_MAP_T optionMap() const {return _optionMap;};
   string usage() const;
   void setOption(const string & code, const string & parameter);
   string parameter(const string & name) const;
   bool isSet(const string & name) const;
private:
   bool getNextArg(const string & argString, string & code, string & parameter, string & tail);
   string trim(const string & text);
private:
   OPTION_MAP_T _optionMap;
};

cOptions & options();

#endif // _options_h_

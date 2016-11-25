#include <stdio.h>
#include <iostream>
#include "StyxValue.h"

using namespace styx;


int main(int argc, char* argv[])
{ StyxValue v;
  v = 3+3;
  long& l = v;
  l += 3;
  cout << "L=" << l << ",V=" << (long)v << "\n";
  v = "hallo";
  string& s = v;
  s += " heike";
  cout << "S=" << s << ",V=" << (string)v << "\n";
  v = (void*)&v;
  void*& p = v;
  p = (void*)main;
  cout << "P=" << p << ",V=" << (void*)v << "\n";
  v = vector<StyxValue>();
  ((vector<StyxValue>&)v).push_back(1);
  ((vector<StyxValue>&)v).push_back(2);
  ((vector<StyxValue>&)v).push_back(3);
  vector<StyxValue>& a = v;
  a.push_back(4);
  for( size_t cnt=a.size(), i=0; i < cnt; ++i )
    cout << "A=" << (long)a[i] << "\n";
  for( size_t cnt=((vector<StyxValue>&)v).size(), i=0; i < cnt; ++i )
    cout << "V=" << (long)(((vector<StyxValue>&)v)[i]) << "\n";
  v = map<string,StyxValue>();
  map<string,StyxValue>& m1 = v;
  m1["key1"] = "val1";
  m1["key2"] = "val2";
  m1["key3"] = "val3";
  map<string,StyxValue> m = v;
  m["key4"] = "val4";
  map<string,StyxValue>::iterator pos = m.begin();
  for( ; pos != m.end(); ++pos )
    cout << "M[" << (*pos).first << "]=" << (string)(*pos).second << "\n";
  for( pos = ((map<string,StyxValue>&)v).begin(); 
       pos != ((map<string,StyxValue>&)v).end(); ++pos )
    cout << "V[" << (*pos).first << "]=" << (string)(*pos).second << "\n";
  return 0;
}


#ifndef _system_h_
#define _system_h_

#include <string>
using namespace std;

int getCurrentThreadId();
unsigned long realtimeOffset();
bool getAppDataDir(string & directory);
bool getCurrentWorkingDirectory(string & directory);
bool setCurrentWorkingDirectory(string & directory);


#endif


#ifndef _comm_h_
#define _comm_h_

#include "Base/basedef.h"

#ifdef _USRDLL

#define COMM_EXPORT __declspec(dllexport)

#else

#define COMM_EXPORT

#endif

inline void commAssert(const char * message, const char * file, int line)
{
#if (_MSC_VER < 1300)
#pragma message("conflicts merging vc6 stl and stl port")
//   cerr << message << " file " << file << " line " << line << endl;
#else
   cerr << message << " file " << file << " line " << line << endl;
#endif
}
#define COMM_ASSERT(message) commAssert(message, __FILE__, __LINE__);

#endif // _comm_h_

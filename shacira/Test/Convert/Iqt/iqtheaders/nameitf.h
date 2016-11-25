
#ifndef __nameitf__
#define __nameitf__

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dcmd_name.h>
/*.EI.***********************************************************************/

GLOBAL int SetNameInfo(const char * name, struct info * info);
GLOBAL int GetNameInfo(const char * name, struct info * info);

#endif /* __nameitf__ */

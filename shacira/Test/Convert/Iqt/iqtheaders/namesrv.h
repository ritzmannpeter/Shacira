
#ifndef __namesrv__
#define __namesrv__

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/


#define NAME_LOC			1

typedef struct
{	int nid;
	int pid;
	int chid;
}	NameLocate;

typedef struct info
{	short info_type;
	union
	{	NameLocate name_loc;
	}	msg;
} INFO;

#endif /* __namesrv__ */

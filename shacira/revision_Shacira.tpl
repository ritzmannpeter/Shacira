
#ifndef _revision_Shacira_h
#define _revision_Shacira_h

#include "shacira_version.h"

#define SHACIRA_REVISION  		"r$WCREV$"
#define SHACIRA_COMITTED_DATE  	"$WCDATE$"
#define SHACIRA_URL	  			"$WCURL$"

const char * RevisionInfo(int part = 0)
{
   if (part == 0) {
      return SHACIRA_REVISION;
   } else if (part == 1) {
      return SHACIRA_COMITTED_DATE;
   } else if (part == 2) {
      return SHACIRA_URL;
   }
   return SHACIRA_REVISION;
}

#endif


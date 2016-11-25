
#ifndef __comm__
#define __comm__


// Data type definitions
#define COMM_TYPE_LONG       1
#define COMM_TYPE_DOUBLE     2
#define COMM_TYPE_TEXT       3
#define COMM_TYPE_BOOL       4

// Data permission definitions
#define COMM_PERM_NOACCESS   0
#define COMM_PERM_READONLY   1
#define COMM_PERM_WRITEONLY  2
#define COMM_PERM_READWRITE  3


int StartCommServer();

#endif  /* __comm__ */


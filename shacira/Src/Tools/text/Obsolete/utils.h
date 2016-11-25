
#ifndef _utils_h_
#define _utils_h_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char * GetArg(int i, int argc, char*argv[], int opt_len);
bool ReadLine(FILE * file, char * buf, unsigned long buf_size);
unsigned long GetToken(const char * source, char * token_buf, unsigned long token_buf_size, char delimiter);

#endif

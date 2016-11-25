
#ifndef _utilities_h_
#define _utilities_h_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if defined(_WIN32)
#include <windows.h>
#else
#endif

void GetWorkingDirectory(char * buf, unsigned long buf_size);
void GetFullPath(const char * path, char * buf, unsigned long buf_size);
void AppendPath(const char * path, char * buf, unsigned long buf_size);
void StripFileName(char * path);
bool IsRelativePath(const char * path);
unsigned long GetToken(const char * str, const char delimiter,
                       char * buf, unsigned long buf_size);
bool FileExists(const char * file_name);
void FileTime(const char * file_name, char * buf, unsigned long buf_size);
const char * SearchFile(const char * file_name,
                        char * buf, unsigned long buf_size,
                        const char * path_list, const char * rel_path = NULL);
const char * GetArg(int i, int argc, char*argv[], int opt_len);
bool ReadLine(FILE * file, char * buf, unsigned long buf_size);
void ReplaceChar(char * str, char rep, char subst);

#endif

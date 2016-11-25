
#pragma warning(disable:4067) /* unexpected tokens following preprocessor directive - expected a newline */
#pragma warning(disable:4101) /* Unreferenzierte lokale Variable */
#pragma warning(disable:4786) /* identifier was truncated to '255' characters in the debug information */
#pragma warning(disable:4503) /* decorated name length exceeded, name was truncated */
#pragma warning(disable:4800) /* Variable wird auf booleschen Wert ('True' oder 'False') gesetzt (Auswirkungen auf Leistungsverhalten moeglich) */

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <string>
#include <list>
#include <map>
typedef std::string STRING_T;
typedef std::list<STRING_T> STRING_LIST_T;
typedef std::map<STRING_T,STRING_T> STRING_MAP_T;

#define MAX_FILE_NAME_LENGTH  0x200
#define INVALID_FIND_HANDLE ((void*)NULL)
typedef void * FIND_HANDLE_T;
typedef struct _find_data {
   char file_name[MAX_FILE_NAME_LENGTH];
   unsigned long file_attributes;
}  FIND_DATA_T;
#define FATTR_DIRECTORY 0x00000001

#if defined(_WIN32)

static FIND_HANDLE_T FirstFile(const char * spec, FIND_DATA_T * find_data)
{
   memset(find_data, 0, sizeof(*find_data));
   WIN32_FIND_DATA _find_data;
   HANDLE find_handle = FindFirstFile(spec, &_find_data);
   if (find_handle == INVALID_HANDLE_VALUE) {
      return INVALID_FIND_HANDLE;
   } else {
      strcpy(find_data->file_name, _find_data.cFileName);
      if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
         find_data->file_attributes |= FATTR_DIRECTORY;
      }
      return find_handle;
   }
}

static int NextFile(FIND_HANDLE_T find_handle, FIND_DATA_T * find_data)
{
   memset(find_data, 0, sizeof(*find_data));
   WIN32_FIND_DATA _find_data;
   int result = FindNextFile(find_handle, &_find_data);
   if (result == 0) {
      return 0;
   } else {
      strcpy(find_data->file_name, _find_data.cFileName);
      if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
         find_data->file_attributes |= FATTR_DIRECTORY;
      }
      return 1;
   }
}

#else

#endif

static int SearchFor(const char * str, const char * s_str)
{
   int s_len = strlen(s_str);
   const char * s_ptr = str;
   int s_end = strlen(str) - s_len;
   if (s_end < 0) {
      return -1;
   }
   int i = 0;
   for (i=0; i<s_end; i++) {
      if (strncmp(s_ptr, s_str, s_len) == 0) {
         return i;
      }
      s_ptr++;
   }
   return -1;
}

static const char * Strip(char * text)
{
   const char * text_ptr = text;
   int len = strlen(text);
   int i = 0;
   for (i=0; i<len; i++) {
      int c = text[i];
      if (c == ' ') {
         text_ptr++;
      } else {
         break;
      }
   }
   for (i=len-1; i>=0; i--) {
      int c = text[i];
      if (c == ' ') {
         text[i] = 0;
      } else {
         break;
      }
   }
   return text_ptr;
}

static STRING_T Replace(const char * str, const char * sub_str, const char * rep_str)
{
   int sub_len = strlen(sub_str);
   int rep_len = strlen(rep_str);
   STRING_T new_string = str;
   int search_pos = 0;
   int pos = new_string.find(sub_str, search_pos);
   while (pos >= 0) {
      new_string.replace(pos, sub_len, rep_str);
      search_pos = pos + rep_len;
      pos = new_string.find(sub_str, search_pos);
   }
   return new_string;
}

static bool CheckFor_get_(const char * text)
{
   int len = strlen(text);
   if (len > 4) {
      int i = 0;
      for (i=0; i<len; i++) {
         if (strncmp(&(text[i]), "get_", 4) == 0) {
            char c = text[i+4];
            if (isalpha(c) && isupper(c)) {
               int first_pos = i - 1;
               if (first_pos < 0) {
                  return true;
               } else {
                  c = text[first_pos];
                  if (c == ' ' ||
                      c == '.' ||
                      c == ';' ||
                      c == ':' ||
                      c == '>' ||
                      c == '=' ||
                      c == '<' ||
                      c == '-' ||
                      c == '(' ||
                      c == ')' ||
                      c == '{' ||
                      c == '}' ||
                      c == '[' ||
                      c == ']' ||
                      c == '/' ||
                      c == '*' ||
                      c == '!' ||
                      c == '~' ||
                      c == '^' ||
                      c == '~' ||
                      c == '|') {
                     return true;
                  }
               }
            }
         }
      }
   }
   return false;
}

static bool CheckFor_set_(const char * text)
{
   int len = strlen(text);
   if (len > 4) {
      int i = 0;
      for (i=0; i<len; i++) {
         if (strncmp(&(text[i]), "set_", 4) == 0) {
            char c = text[i+4];
            if (isalpha(c) && isupper(c)) {
               int first_pos = i - 1;
               if (first_pos < 0) {
                  return true;
               } else {
                  c = text[first_pos];
                  if (c == ' ' ||
                      c == '.' ||
                      c == ';' ||
                      c == ':' ||
                      c == '>' ||
                      c == '=' ||
                      c == '<' ||
                      c == '-' ||
                      c == '(' ||
                      c == ')' ||
                      c == '{' ||
                      c == '}' ||
                      c == '[' ||
                      c == ']' ||
                      c == '/' ||
                      c == '*' ||
                      c == '!' ||
                      c == '~' ||
                      c == '^' ||
                      c == '~' ||
                      c == '|') {
                     return true;
                  }
               }
            }
         }
      }
   }
   return false;
}

static bool ProcessLine(FILE * output_file, FILE * log_file, const char * line, int line_no)
{
   STRING_T comp_line = line;
   STRING_T _line;
   int pos = SearchFor(line, "//##");
   if (pos == 0) {
      fprintf(log_file, "%05.05d:del>>>:%s", line_no, line);
      return true;
   } else if (pos > 0) {
      char buf[0x1000] = {0};
      if (pos > ((sizeof(buf)-1))) {
         pos = (sizeof(buf)-1);
      }
      memcpy(buf, line, pos);
      const char * stripped_buf = Strip(buf);
      int len = strlen(buf);
      if (len == 0) {
         fprintf(log_file, "%05.05d:del>>>:%s", line_no, line);
         return true;
      } else {
         buf[len] = '\n';
      }
      _line = buf;
   } else {
      _line = line;
   }
#ifdef DOESNT_WORK
   if (CheckFor_get_(_line.c_str())) {
      _line = Replace(_line.c_str(), "get_", "");
   }
   if (CheckFor_set_(_line.c_str())) {
      _line = Replace(_line.c_str(), "set_", "Set");
   }
#endif
   fprintf(output_file, "%s", _line.c_str());
   if (comp_line == _line) {
      return false;
   } else {
      fprintf(log_file, "%05.05d:old;>>>%s", line_no, comp_line.c_str());
      fprintf(log_file, "%05.05d:new:<<<%s", line_no, _line.c_str());
      return true;
   }
}

static char _LineBuf[0x2000] = {0};

static int ProcessFile(const char * file, FILE * glfile)
{
   bool changed = false;
   char backup_file[0x400] = {0};
   char output_file[0x400] = {0};
   char log_file[0x400] = {0};
   sprintf(backup_file, "%s.backup", file);
   sprintf(output_file, "%s.output", file);
   sprintf(log_file, "%s.derlog", file);
   const char * input_file = backup_file;
   int rc = rename(file, backup_file);
   if (rc != 0) {
      printf("failed to rename %s\n", file);
   }
   FILE * ifile = fopen(input_file, "r");
   if (ifile == NULL) {
      fprintf(stderr, "cannot open input file %s\n", input_file);
      return -1;
   }
   FILE * ofile = fopen(output_file, "w");
   if (ofile == NULL) {
      fprintf(stderr, "cannot open output file %s\n", output_file);
      fclose(ifile);
      return -1;
   }
   FILE * lfile = fopen(log_file, "w");
   if (lfile == NULL) {
      fprintf(stderr, "cannot open log file %s\n", log_file);
      fclose(ifile);
      fclose(ofile);
      return -1;
   }
   char * line = 0;
   int changed_lines = 0;
   int line_no = 1;
   while (line = fgets(_LineBuf, sizeof(_LineBuf), ifile)) {
      if (ProcessLine(ofile, lfile, line, line_no)) {
         changed = true;
         changed_lines++;
      }
      line_no++;
   }
   if (changed_lines > 0) {
      fprintf(glfile, "file %s: changed %d lines\n", file, changed_lines);
   }
   fclose(ifile);
   fclose(ofile);
   fclose(lfile);
   if (changed) {
      printf("file %s has changed\n", file);
      rc = rename(output_file, file);
      if (rc != 0) {
         printf("failed to rename %s\n", output_file);
      }
   } else {
      printf("file %s no changes\n", file);
      rc = remove(output_file);
      if (rc != 0) {
         printf("failed to remove %s\n", output_file);
      } else {
         rc = rename(backup_file, file);
         if (rc != 0) {
            printf("failed to remove %s\n", backup_file);
         } else {
            rc = remove(log_file);
            if (rc != 0) {
               printf("failed to remove %s\n", log_file);
            }
         }
      }
   }
   return 0;
}

typedef void (*PROCESS_FUNC_T)(const char * file);

class cFileEnumerator
{
public:
   cFileEnumerator(const char * path);
   virtual ~cFileEnumerator();
   void AddPattern(const char * pattern);
   void Process(const char * path, PROCESS_FUNC_T pfunc);
protected:
   void Process(const char * path, const char * pattern, PROCESS_FUNC_T pfunc);
protected:
   STRING_T _RootPath;
   STRING_MAP_T _Patterns;
};

cFileEnumerator::cFileEnumerator(const char * path)
{
   _RootPath = path;
}

cFileEnumerator::~cFileEnumerator()
{
}

void cFileEnumerator::AddPattern(const char * pattern)
{
   _Patterns[pattern] = pattern;
}

void cFileEnumerator::Process(const char * path, PROCESS_FUNC_T pfunc)
{
   STRING_MAP_T::const_iterator i = _Patterns.begin();
   while (i != _Patterns.end()) {
      STRING_T pattern = (*i).second;
      Process(path, pattern.c_str(), pfunc);
      i++;
   }
}

void cFileEnumerator::Process(const char * path, const char * pattern, PROCESS_FUNC_T pfunc)
{
   FIND_DATA_T find_data = {0};
   FIND_HANDLE_T find_handle = INVALID_FIND_HANDLE;
   char * spec = (char*)calloc(1, 0x1000);
   if (strlen(path) > 0) {
      sprintf(spec, "%s/%s", path, pattern);
   } else {
      sprintf(spec, "%s", pattern);
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         STRING_T file_name = find_data.file_name;
         char file[0x400] = {0};
         sprintf(file, "%s/%s", path, file_name.c_str());
         pfunc(file);
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   if (strlen(path) > 0) {
      sprintf(spec, "%s/*", path);
   } else {
      sprintf(spec, "*");
   }
   find_handle = FirstFile(spec, &find_data);
   if (find_handle != INVALID_FIND_HANDLE) {
      int found = 1;
      while (found) {
         if (find_data.file_attributes & FATTR_DIRECTORY) {
            if (find_data.file_name[0] != '.') {
               char * new_path = (char*)calloc(1, 0x1000);
               if (strlen(path) > 0) {
                  sprintf(new_path, "%s/%s", path, find_data.file_name);
               } else {
                  sprintf(new_path, "%s", find_data.file_name);
               }
               Process(new_path, pattern, pfunc);
               free(new_path);
            }
         }
         found = NextFile(find_handle, &find_data);
      }
      FindClose(find_handle);
   }
   free(spec);
}

FILE * _GLFile = NULL;
static void DeRational(const char * file)
{
   printf("%s\n", file);
   ProcessFile(file, _GLFile);
}

int main(int argc, char* argv[])
{
   int i = 0;
   char root_path[0x100] = {0};
   DWORD len = GetCurrentDirectory(sizeof(root_path), root_path);
#ifdef lassma
   for (i=1; i<argc; i++) {
      if (strncmp(argv[i], "-r", 2) == 0) {
         if (strlen(argv[i]) == 2) {
            if (i < argc) {
               i++;
               pp_file = argv[i];
            }
         } else {
            strcpy(ppfile, &(argv[i])[2]);
            pp_file = ppfile;
         }
      } else if (strncmp(argv[i], "-o", 2) == 0) {
         if (strlen(argv[i]) == 2) {
            if (i < argc) {
               i++;
               output_file = argv[i];
            }
         } else {
            strcpy(outfile, &(argv[i])[2]);
            output_file = outfile;
         }
      } else {
         input_file = argv[i];
      }
   }
#endif

   const char * global_log_file = "derational.log";
   _GLFile = fopen(global_log_file, "w");
   if (_GLFile == NULL) {
      fprintf(stderr, "cannot open global log file %s\n", global_log_file);
      return -1;
   }
   cFileEnumerator file_enum(root_path);
   file_enum.AddPattern("*.h");
   file_enum.AddPattern("*.cpp");
   file_enum.Process(root_path, DeRational);
   fclose(_GLFile);   
   return 0;
}



#include "webintegration.h"
#include "Client/GatewayInterface/cGatewayInterface.h"

static int _GatewayInitialized = 0;
static unsigned long _BufSize = 0x20000;
static char _CellName[0x200];

static void InitializeGatewayInterface()
{
   int err = 0;
   if (!_GatewayInitialized) {
      int err = GIInit(0, 20000, "localhost");
      if (err >= 0 ||
          err == GATEWAY_INTERFACE_ALREADY_INITIALIZED) {
         _GatewayInitialized = 1;
sprintf(_CellName, "sepp");
      }
   }
}

static TranslateVar(const char * var_spec, char_t * buffer, unsigned long buffer_size)
{
   int err = 0;
   InitializeGatewayInterface();
   if (_GatewayInitialized) {
      memset(buffer, 0, buffer_size);
      err = GIGetValue(_CellName, var_spec, buffer, buffer_size);
      if (err != 0) {
         sprintf(buffer, "?1");
      }
   } else {
      sprintf(buffer, "?2");
   }
}


static int GetNextName(char * name, char * list)
{
   int len = strlen(list);
   int i = 0, nchars = 0;
   for (i=0; i<len; i++) {
      char c = list[i];
      if (c == '\0') {
         break;
      } else if (c == ',') {
         nchars++;
         break;
      } else {
         name[nchars] = c;
         nchars++;
      }
   }
   return nchars;
}

static void CellList(char_t * new_buffer, unsigned long new_buffer_size)
{
   int err = 0;
   InitializeGatewayInterface();
   if (_GatewayInitialized) {
      char clist[0x500] = {0};
      memset(new_buffer, 0, new_buffer_size);
      err = GIGetContextList(clist, sizeof(clist));
      if (err != 0) {
         sprintf(new_buffer, "?1");
      } else {
         int name_len = 0;
         char * dst_buf_ptr = new_buffer;
         char * src_buf_ptr = clist;
         char context_name[0x200];
         memset(context_name, 0, sizeof(context_name));
         name_len = GetNextName(context_name, src_buf_ptr);
         while (name_len > 0) {
            sprintf(dst_buf_ptr, "<A HREF=\"/shacira/%s/faq.htm\">das is maschine %s</A> <BR>", context_name, context_name);
            dst_buf_ptr = new_buffer + strlen(new_buffer);
            src_buf_ptr += name_len;
            memset(context_name, 0, sizeof(context_name));
            name_len = GetNextName(context_name, src_buf_ptr);
         }
      }
   } else {
      sprintf(new_buffer, "?2");
   }
}

static void TranslatePage(char_t * buffer, char_t * new_buffer, unsigned long new_buffer_size)
{
   int nchars = 0;
   int variables_to_process = 1;
   char white_space[128] ={0};
   char var_spec[128] = {0};
   int params, len = strlen(buffer);
   char * head = calloc(1, len * 2);
   char_t * buf_ptr = buffer;
   char_t * translated_buf_ptr = new_buffer;
   InitializeGatewayInterface();
   while (variables_to_process) {
      params = sscanf(buf_ptr, "%[^$]$var(%[^)])%n", head, var_spec, &nchars);
      if (params == 2) {
         char value[0x200] = {0};
         memcpy(translated_buf_ptr, head, strlen(head));
         translated_buf_ptr += strlen(head);
         TranslateVar(var_spec, value, sizeof(value));
         memcpy(translated_buf_ptr, value, strlen(value));
         translated_buf_ptr += strlen(value);
         buf_ptr += nchars;
         memset(var_spec, 0, sizeof(var_spec));
         memset(white_space, 0, sizeof(white_space));
         memset(head, 0, len);
      } else {
         memcpy(translated_buf_ptr, buf_ptr, strlen(buf_ptr));
         variables_to_process = 0;
      }
   }
   free(head);
}

static void GetPage(const char * page, char_t * buffer, unsigned long buffer_size)
{
   int err = 0;
   InitializeGatewayInterface();
   memset(buffer, 0, buffer_size);
   err = GIGetPage(_CellName, page, buffer, buffer_size);
   if (err != 0) {
      sprintf(buffer, "page %s: gateway error %d", page, err);
   }
}

int ShaciraHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,
                   int arg, char_t *url, char_t *path, char_t *query)
{
#define READ_SIZE 512
#define ORIGINAL  1
#define SHACIRA   2
   int buf_len = 0;
   int mode = 0;
   char_t * buffer = NULL;
   char_t * new_buffer = NULL;
   int buffer_size = 0x20000;
   int new_buffer_size = (buffer_size * 2) + 0x1000;
   int i = 0, params = 0;
   char * buf_ptr = NULL;
   char page_name[0x200] = {0};
   char page_body[0x100] = {0};
   char page_extension[0x100] = {0};
   char cell_name[0x200] = {0};
   char space[0x200] = {0};
   char file[0x200] = {0};
   FILE * stream = NULL;
#ifdef lassma
   if (strncmp(path, "/shacira/", 9) == 0) {
      mode = SHACIRA;
      page_name = &(path[9]);
   } else if (strncmp(path, "/original/", 10) == 0) {
      mode = ORIGINAL;
      page_name = &(path[10]);
   } else {
      return 0;
   }
#endif
   params = sscanf(path, "/shacira/%[^/]/%s", cell_name, page_name);
   if (params == 2) {
      mode = SHACIRA;
      memcpy(_CellName, cell_name, sizeof(_CellName));
   } else {
      params = sscanf(path, "/shacira/%s", page_name);
      if (params == 1) {
         mode = SHACIRA;
      } else {
         params = sscanf(path, "/org/%s", page_name);
         if (params == 1) {
            mode = ORIGINAL;
         } else {
            return 0;
         }
      }
   }
   websHeader(wp);
   if (page_name != NULL) {
      params = sscanf(page_name, "%[^.].%s", page_body, page_extension);
      if (params == 2) {
         if (*page_extension == 'x' ||
             *page_extension == 'X' ||
             *page_extension == 'h' ||
             *page_extension == 'H' ||
             *page_extension == 'a' ||
             *page_extension == 'A') {
         } else {
            return 0;
         }
      } else {
         return 0;
      }
      if (strcmp(page_name, "list.htm") == 0) {
         new_buffer = (char_t*)calloc(1, new_buffer_size);
         CellList(new_buffer, new_buffer_size);
      } else {
         buffer = (char_t*)calloc(1, buffer_size);
         new_buffer = (char_t*)calloc(1, new_buffer_size);
         sprintf(file, "%s/shacira/%s", wp->dir, page_name);
         stream = fopen(file, "r");
         buf_ptr = buffer;
         if (stream != NULL) {
            int nread = fread((void*)buf_ptr, 1, READ_SIZE, stream);
            while (nread > 0) {
               buf_ptr += READ_SIZE;            
               nread = fread((void*)buf_ptr, 1, READ_SIZE, stream);
            }
            fclose(stream);
            if (mode == SHACIRA) {
               TranslatePage(buffer, new_buffer, new_buffer_size);
            } else {
               memcpy(new_buffer, buffer, new_buffer_size);
            }
         } else {
            GetPage(page_name, new_buffer, new_buffer_size);
         }
         free(buffer);
      }
      buf_len = strlen(new_buffer);
      websWriteBlock(wp, new_buffer, buf_len);
      free(new_buffer);
   }
   websFooter(wp);
   websDone(wp, 200);
   return 1;
}






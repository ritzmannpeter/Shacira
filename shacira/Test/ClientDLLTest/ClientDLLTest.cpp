
#include "FirstHeader.h"
#include "Apps/ClientDLL/ClientDLL.h"

static void GetVar(CLIENT_HANDLE hnd, const char * var_name,
                   unsigned long i1 = -1, unsigned long i2 = -1, unsigned long i3 = -1, unsigned long i4 = -1)
{
   char value[64] = {0};
   long err = CLIENT_GetVariable(hnd, var_name, i1, i2, i3, i4, value, sizeof(value));
   if (err == 0) {
      printf("Variable %s: %s\n", var_name, value);
   } else {
      char err_string[512] = {0};
      CLIENT_GetErrorString(hnd, err_string, sizeof(err_string));
      printf("Fehler beim Lesen von Variable %s\n%s\n", var_name, err_string);
   }
}

static void SetVar(CLIENT_HANDLE hnd, const char * var_name, const char * value,
                   unsigned long i1 = -1, unsigned long i2 = -1, unsigned long i3 = -1, unsigned long i4 = -1)
{
   long err = CLIENT_SetVariable(hnd, var_name, i1, i2, i3, i4, value, strlen(value));
   if (err == 0) {
      printf("Variable %s set to %s\n", var_name, value);
   } else {
      char err_string[512] = {0};
      CLIENT_GetErrorString(hnd, err_string, sizeof(err_string));
      printf("Fehler beim Schreiben von Variable %s\n%s\n", var_name, err_string);
   }
}

int main(int argc, char* argv[])
{
   char err_string[512] = {0};
   long err = CLIENT_Init("ClientProcess");
   if (err != 0) {
      CLIENT_GetErrorString(0, err_string, sizeof(err_string));
      printf("Fehler %d: %s\n", err, err_string);
   }
   CLIENT_HANDLE hnd = CLIENT_Connect("Nela");
   if (hnd == INVALID_CLIENT_HANDLE) {
      CLIENT_GetErrorString(0, err_string, sizeof(err_string));
      printf("Fehler %d: %s\n", err, err_string);
   }
   while (42) {
      GetVar(hnd, "pqmQuality");
      GetVar(hnd, "pqmFocus");
      GetVar(hnd, "pqmFogging");
      GetVar(hnd, "pqmCTP");
      GetVar(hnd, "xxxpqmCTPQuality");
      long lval = rand() % 4;
      char new_value[64] = {0};
      sprintf(new_value, "%d", lval);
      SetVar(hnd, "pqmEnergy", new_value);
      Sleep(100);
   }
   CLIENT_Release(hnd);
   CLIENT_Exit();
   return 0;
}



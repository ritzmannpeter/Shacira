
#include "cSocketApi.h"
#include "cServer.h"
#include "cServiceHandler.h"

#include <stdio.h>

int main(int argc, char **argv)
{
   unsigned short port = 20000;
   int max_connections = 10;
   cServer server(port, max_connections);
   int rc = server.Start();
   return rc;
}



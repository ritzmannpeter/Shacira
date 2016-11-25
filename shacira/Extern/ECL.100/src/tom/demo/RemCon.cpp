// ===========================================================================
// RemCon.cpp                                            Remote Console Client
//                                                        Autor: Markus Wuertz
// ---------------------------------------------------------------------------
//
// Ausfuehrbarer Remote Console Client
//
// ===========================================================================


#include "base/eb_cmdarg.hpp"
#include "base/eb_str.hpp"
#include "base/eb_err.hpp"

#include "tom/et_concli.hpp"


int main( int argc, char *argv[] )
{
   //cBase::SetDebugMask( cBase::GetDebugMask() | cBase::dbgInfo );

   cCmdArg arg_line( argc, argv );
   const char *arg;
   bool option;

   cString server;
   cString client;

   while ( (arg = arg_line.getNext()) != NULL ) {
      option = *arg == '/' || *arg == '-';
      if ( option && (!stricmp(arg+1,"server") || !stricmp(arg+1,"s")) ) {
         server = arg_line.getNext();
      } else if ( option && (!stricmp(arg+1,"client") || !stricmp(arg+1,"c")) ) {
         client = arg_line.getNext();
      } else if (!option && server.Length() == 0) {
         server = arg;
      } else if (!option && client.Length() == 0) {
         client = arg;
      } else {
         cout << "Usage: " << arg_line.getModule() <<
            " [[-S] <servername>] [[-C] <clientname>]" << endl;
         return 1;
      }
   }

   try {
      cConClient cc( client, server );

      do {
         if ( cc.getState() == cConClient::stLogin) {
            cc.onlineLoop();
         } else if ( cc.getState() == cConClient::stLogout ) {
            cc.offlineLoop();
         }
      } while ( cc.getState() != cConClient::stEnd );
   } catch (cErrBase& err) {
      cerr << "Error: " << err << endl;
   };

   return 0;
}


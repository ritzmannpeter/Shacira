
#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cSockets.h"
#include "Orb/cBroker.h"
#include "Orb/cCosEventChannelProxy.h"
#include "System/Comm/cProxyReceiver.h"
#include "System/Channel/cChannelProxy.h"
#include "System/Channel/cAdapter.h"
#include "System/Channel/cCOSChannel.h"

class cPrintAdapter : public cAdapter
{
public:
   cPrintAdapter() {};
   virtual ~cPrintAdapter() {};
   virtual void Object(cTransientObject * object)
   {
      STRING_T serialized_object = object->Serialize();
      printf("%s\n", serialized_object.c_str());
      Beep(100,100);
   };
};


int main(int argc, char* argv[])
{
   try {
      cResources resources(argc, argv);
      cSockets::Initialize();
		cBroker::Initialize();
      LONG_T port = 21001;
      cResources::GetOption("Port", port);
      STRING_T ip_addr = "127.0.0.1";
      cResources::GetOption("IpAddress", ip_addr);
      STRING_T channel_name = "FC";
      cResources::GetOption("ChannelName", channel_name);
      cProxyReceiver receiver(port, ip_addr.c_str());
      cCosEventChannelProxy * proxy = NULL;
      receiver.Start();
      printf("waiting for proxy on %s at address %s port %d\n", channel_name, ip_addr, port);
      while (true) {
         Sleep(1000);
         proxy = (cCosEventChannelProxy*)receiver.ChannelProxy(channel_name.c_str());
         if (proxy == NULL) {
            printf(".");
         } else {
            cCOSChannel * channel = new cCOSChannel(channel_name.c_str(), proxy);
            cPrintAdapter * adapter = new cPrintAdapter;
            channel->Connect(adapter);
            printf("\nlistening to channel %s\n", channel_name);
            break;
         }
      }
      while (true) {
         Sleep(1000);
      }
   } catch (cError & e) {
      printf("%s\n", (const char *)e);
   } catch (...) {
      printf("Unhandled exception\n");
   }
   return 0;
}

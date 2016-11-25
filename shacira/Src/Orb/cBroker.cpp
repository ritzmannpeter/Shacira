//## begin module%3C4EA4E60266.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EA4E60266.cm

//## begin module%3C4EA4E60266.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EA4E60266.cp

//## Module: cBroker%3C4EA4E60266; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Orb\cBroker.cpp

//## begin module%3C4EA4E60266.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C4EA4E60266.additionalIncludes

//## begin module%3C4EA4E60266.includes preserve=yes
//## end module%3C4EA4E60266.includes

// cBroker
#include "Orb/cBroker.h"
//## begin module%3C4EA4E60266.additionalDeclarations preserve=yes

void IORInfo(CONST_STRING_T ior, STRING_T & ip_addr, ULONG_T & port);

#define IS_BROKER_ACTIVE if (_Broker != NULL) throw cError(ORB_BROKER_ACTIVE, 0);
#define IS_BROKER_INACTIVE if (_Broker == NULL) throw cError(ORB_BROKER_INACTIVE, 0);
#define IS_ORB_ACTIVE if (_Orb == NULL_ORB) throw cError(ORB_ORB_INACTIVE, 0, _ORBName.c_str());
#define IS_POA_ACTIVE if (_Poa == NULL_POA) throw cError(ORB_POA_INACTIVE, 0, _ORBName.c_str());

//## end module%3C4EA4E60266.additionalDeclarations


// Class cBroker 

//## begin cBroker::RefCount%3DD2A43D0365.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cBroker::_RefCount = 0;
//## end cBroker::RefCount%3DD2A43D0365.attr

//## begin cBroker::Mutex%3DD2A43D036F.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cBroker::_Mutex;
//## end cBroker::Mutex%3DD2A43D036F.attr

//## begin cBroker::Orb%3DD2A5C90116.attr preserve=no  implementation: static CORBA::ORB_var {U} NULL_ORB
CORBA::ORB_var cBroker::_Orb = NULL_ORB;
//## end cBroker::Orb%3DD2A5C90116.attr

//## begin cBroker::ORBName%3DD2AB0E0198.attr preserve=no  implementation: static STRING_T {U} "Unknown"
STRING_T cBroker::_ORBName = "Unknown";
//## end cBroker::ORBName%3DD2AB0E0198.attr

//## begin cBroker::Broker%3E89C19C0157.attr preserve=no  implementation: static cBroker * {U} NULL
cBroker *cBroker::_Broker = NULL;
//## end cBroker::Broker%3E89C19C0157.attr

cBroker::cBroker()
  //## begin cBroker::cBroker%.hasinit preserve=no
  //## end cBroker::cBroker%.hasinit
  //## begin cBroker::cBroker%.initialization preserve=yes
  //## end cBroker::cBroker%.initialization
{
  //## begin cBroker::cBroker%.body preserve=yes
#ifdef __VISIBROKER__
   _Name = _ORBName = "VisiBroker";
#else
   _Name = _ORBName = "OmniORB";
#endif
   cObjectLock __lock__(&_Mutex);
   _RefCount++;
   if (_RefCount > 1) return;
   try {
      StartBroker();
      Start();
   } catch(CORBA::SystemException& ex) {
      ErrorPrintf("CORBA::SystemException: %s\n", (CONST_STRING_T)ex._name());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch(CORBA::Exception& ex) {
      ErrorPrintf("CORBA::Exception: %s\n", (CONST_STRING_T)ex._name());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch(omniORB::fatalException& ex) {
      ErrorPrintf("CORBA::fatalException: %s:%d: %s\n", (CONST_STRING_T)ex.file(), ex.line(), ex.errmsg());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch (...) {
      ErrorPrintf("unhandled exception in cLocalContext::ActivateCorbaObject\n");
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   }
  //## end cBroker::cBroker%.body
}

cBroker::cBroker(const cBroker &right)
  //## begin cBroker::cBroker%copy.hasinit preserve=no
  //## end cBroker::cBroker%copy.hasinit
  //## begin cBroker::cBroker%copy.initialization preserve=yes
  //## end cBroker::cBroker%copy.initialization
{
  //## begin cBroker::cBroker%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBroker::cBroker%copy.body
}

cBroker::cBroker (INT_T argc, CHAR_T **argv)
  //## begin cBroker::cBroker%1037211078.hasinit preserve=no
  //## end cBroker::cBroker%1037211078.hasinit
  //## begin cBroker::cBroker%1037211078.initialization preserve=yes
  //## end cBroker::cBroker%1037211078.initialization
{
  //## begin cBroker::cBroker%1037211078.body preserve=yes
#ifdef __VISIBROKER__
   _Name = _ORBName = "VisiBroker";
#else
   _Name = _ORBName = "OmniORB";
#endif
   cObjectLock __lock__(&_Mutex);
   _RefCount++;
   if (_RefCount > 1) return;
   try {
      StartBroker(argc, argv);
      Start();
   } catch(CORBA::SystemException& ex) {
      ErrorPrintf("CORBA::SystemException: %s\n", (CONST_STRING_T)ex._name());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch(CORBA::Exception& ex) {
      ErrorPrintf("CORBA::Exception: %s\n", (CONST_STRING_T)ex._name());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch(omniORB::fatalException& ex) {
      ErrorPrintf("CORBA::fatalException: %s:%d: %s\n", (CONST_STRING_T)ex.file(), ex.line(), ex.errmsg());
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   } catch (...) {
      ErrorPrintf("unhandled exception in cLocalContext::ActivateCorbaObject\n");
      throw cError(ORB_START_FAILURE, 0, _Name.c_str());
   }
  //## end cBroker::cBroker%1037211078.body
}


cBroker::~cBroker()
{
  //## begin cBroker::~cBroker%.body preserve=yes
   cObjectLock __lock__(&_Mutex);
   _RefCount--;
   if (_RefCount > 0) return;
   StopBroker();
   Stop();
  //## end cBroker::~cBroker%.body
}



//## Other Operations (implementation)
void cBroker::Initialize (INT_T argc, CHAR_T **argv)
{
  //## begin cBroker::Initialize%1049215549.body preserve=yes
	if (_Broker == NULL) {
		if (argc == 0 || argv == NULL) {
			_Broker = new cBroker;
		} else {
			_Broker = new cBroker(argc, argv);
		}
	}
  //## end cBroker::Initialize%1049215549.body
}

void cBroker::Cleanup ()
{
  //## begin cBroker::Cleanup%1111081373.body preserve=yes
	if (_Broker != NULL) {
      delete _Broker;
	}
  //## end cBroker::Cleanup%1111081373.body
}

INT_T cBroker::MainFunc (void *extra)
{
  //## begin cBroker::MainFunc%1021469768.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
#ifdef lassma
   try {
      _Boa->impl_is_ready();
   } catch(CORBA::SystemException & e) {
      ErrorPrintf("Corba System exception in object implementation\n");
   } catch(CORBA::Exception & e) {
      ErrorPrintf("Corba exception in object implementation\n");
   } catch (...) { \
      ErrorPrintf("unhamdled exception in object implementation\n");
   }
#else
   while (!_Terminated && !_Terminating) {
      cSystemUtils::Suspend(1000);
   }
#endif
   return 0;
MAINFUNC_EPILOG
  //## end cBroker::MainFunc%1021469768.body
}

CORBA::ORB * cBroker::Orb ()
{
  //## begin cBroker::Orb%1011787178.body preserve=yes
   IS_ORB_ACTIVE
   return _Orb;
  //## end cBroker::Orb%1011787178.body
}

void cBroker::DecodeIOR (CONST_STRING_T ior, STRING_T &ip_addr, ULONG_T &port)
{
  //## begin cBroker::DecodeIOR%1124461687.body preserve=yes
   STRING_T version;
   STRING_T ip_host;
   STRING_T ip_port;
   STRING_T object_key;
   if (IsCorbaLocURI(ior, version, ip_host, ip_port, object_key)) {
      ip_addr = ip_host;
      port = strtoul(ip_port.c_str(), NULL, 0);
   } else {
      IORInfo(ior, ip_addr, port);
   }
  //## end cBroker::DecodeIOR%1124461687.body
}

#ifdef doku
// if the port, the created object is listening to
// should be always the same port, th  following intialization code
// can be used:
   int _argc = 3;
   char * _argv[4];
   _argv[0] = argv[0];
   _argv[1] = "-ORBendPoint";
   _argv[2] = "giop:tcp::21009";
   _argv[3] = NULL;
   CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);
#endif

void cBroker::StartBroker (INT_T argc, CHAR_T **argv)
{
  //## begin cBroker::StartBroker%1037188598.body preserve=yes
   if (_Orb == NULL_ORB) {
      int _argc = argc;
      CHAR_T * _argv[20] = {0};
      int argno = 0;
      for (argno=0; argno<argc; argno++) {
         _argv[argno] = argv[argno];
      }
      AddAdditionalParams(_argc, _argv);
      _Orb = CORBA::ORB_init(_argc, _argv, OMNI_ORB_IDENTIFIER);
      if (_UseCorbaLoc) {
         CORBA::Object_var obj = _Orb->resolve_initial_references("omniINSPOA");
         _Poa = PortableServer::POA::_narrow(obj);
      } else {
         CORBA::Object_var obj = _Orb->resolve_initial_references("RootPOA");
         _Poa = PortableServer::POA::_narrow(obj);
      }
      PortableServer::POAManager_var pman = cBroker::Poa()->the_POAManager();
      pman->activate();
   }
  //## end cBroker::StartBroker%1037188598.body
}

void cBroker::AddAdditionalParams(INT_T & argc, CHAR_T ** argv)
{
   int argno = argc;
   if (GetUseCorbaLoc()) {
      // use a fixed port, to which the object is listening to
      static char endpoint_spec[0x200] = {0};
      argv[argno] = "-ORBendPoint";
      argno++;
      argc++;
      SafePrintf(endpoint_spec, sizeof(endpoint_spec), "giop:tcp::%d", ObjectDefaultPort());
      argv[argno] = endpoint_spec;
      argno++;
      argc++;
   }
   if (GetORBTraceLevel() > 0) {
      static char trace_level[0x100] = {0};
      argv[argno] = "-ORBtraceLevel";
      argno++;
      argc++;
      SafePrintf(trace_level, sizeof(trace_level), "%d", GetORBTraceLevel());
      argv[argno] = trace_level;
      argno++;
      argc++;
   }
}

void cBroker::StopBroker ()
{
  //## begin cBroker::StopBroker%1037188599.body preserve=yes
   if (_Orb != NULL_ORB) {
      try {
         _Orb->destroy();
	   } catch(CORBA::SystemException & e) {
         ErrorPrintf("Corba System exception while destroying Orb\n");
	   } catch(CORBA::Exception & e) {
         ErrorPrintf("Corba exception while destroying Orb\n");
	   } catch (...) { \
         ErrorPrintf("unhamdled exception while destroying Orb\n");
	   }
   }
   _Orb = NULL_ORB;
  //## end cBroker::StopBroker%1037188599.body
}

// Additional Declarations
  //## begin cBroker%3C4EA4E60266.declarations preserve=yes
   PortableServer::POA_var cBroker::_Poa = NULL_POA;
   bool cBroker::_UseCorbaLoc = false;
   int cBroker::_ObjectDefaultPort = 21009;
   int cBroker::_ORBTraceLevel = 0;
   PortableServer::POA * cBroker::Poa()
   {
      IS_POA_ACTIVE
      return _Poa;
   }
   void cBroker::SetUseCorbaLoc(bool use_corba_loc)
   {
      _UseCorbaLoc = use_corba_loc;
   }
   bool cBroker::GetUseCorbaLoc()
   {
      return _UseCorbaLoc;
   }
   void cBroker::SetORBTraceLevel(int level)
   {
      _ORBTraceLevel = level;
   }
   int cBroker::GetORBTraceLevel()
   {
      return _ORBTraceLevel;
   }
   void cBroker::SetObjectDefaultPort(int port)
   {
      _ObjectDefaultPort = port;
   }

   int cBroker::GetObjectDefaultPort()
   {
      return _ObjectDefaultPort;
   }

   int cBroker::ObjectDefaultPort()
   {
      return _ObjectDefaultPort;
   }

   bool cBroker::IsCorbaLocURI(CONST_STRING_T ior, STRING_T &version, STRING_T &ip_addr, STRING_T &port, STRING_T &object_key)
   {
      // test if the supplied ior is a CorbaLoc URI
      char v[0x100] = {0};
      char protocol[0x100] = {0};
      char ip[0x200] = {0};
      char ip2[0x200] = {0};
      char p[0x200] = {0};
      char p2[0x200] = {0};
      char id[0x200] = {0};
      int params = sscanf(ior, "corbaloc::%[^:]:%[^/]/%s", &ip, &p, &id);
      if (params == 3) {
         ip_addr = ip;
         port = p;
         object_key = id;
         return true;
      }
      params = sscanf(ior, "corbaloc:%[^:]:%[^:]:%[^/]/%s", &protocol, &ip, &p, &id);
      if (params == 4) {
         ip_addr = ip;
         port = p;
         object_key = id;
         return true;
      }
      params = sscanf(ior, "corbaloc::%[^:]:%[^,],iiop:%[^:]:%[^/]/%s", &ip, &p, &ip2, &p2, &id);
      if (params == 5) {
         ip_addr = ip;
         port = p;
         object_key = id;
         return true;
      }
      params = sscanf(ior, "corbaloc:%[^:]:%[^:]:%[^,],iiop:%[^:]:%[^/]/%s", &protocol, &ip, &p, &ip2, &p2, &id);
      if (params == 6) {
         ip_addr = ip;
         port = p;
         object_key = id;
         return true;
      }
      return false;
   }
  //## end cBroker%3C4EA4E60266.declarations

//## begin module%3C4EA4E60266.epilog preserve=yes
//## end module%3C4EA4E60266.epilog

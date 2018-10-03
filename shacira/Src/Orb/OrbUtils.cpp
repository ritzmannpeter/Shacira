
#include "FirstHeader.h"
#include <string.h>
#include <stdlib.h>

#include <CORBA.h>

#ifdef HAVE_STD
#  include <iostream>
#  include <iomanip>
   using namespace std;
#else
#  include <iostream.h>
#  include <iomanip.h>
#endif

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#ifndef Swap16
#define Swap16(s) ((((s) & 0xff) << 8) | (((s) >> 8) & 0xff))
#else
#error "Swap16 has already been defined"
#endif

#ifndef Swap32
#define Swap32(l) ((((l) & 0xff000000) >> 24) | \
		   (((l) & 0x00ff0000) >> 8)  | \
		   (((l) & 0x0000ff00) << 8)  | \
		   (((l) & 0x000000ff) << 24))
#else
#error "Swap32 has already been defined"
#endif

#define POA_NAME_SEP            '\xff'
#define TRANSIENT_SUFFIX_SEP    '\xfe'
#define TRANSIENT_SUFFIX_SIZE   8

static int
get_poa_info(_CORBA_Unbounded_Sequence_Octet& key,
	     _CORBA_Unbounded_Sequence_String& poas_out,
	     int& transient_out,
	     _CORBA_Unbounded_Sequence_Octet& id_out)
{
  const char* k = (const char*) key.NP_data();
  int len = key.length();
  const char* kend = k + len;

  poas_out.length(1);
  poas_out[0] = CORBA::string_dup("root");

  if( *k != TRANSIENT_SUFFIX_SEP && *k != POA_NAME_SEP )  return 0;

  while( k < kend && *k == POA_NAME_SEP ) {

    k++;
    const char* name = k;

    while( k < kend && *k && *k != POA_NAME_SEP && *k != TRANSIENT_SUFFIX_SEP )
      k++;

    if( k == kend )  return 0;

    char* nm = new char[k - name + 1];
    memcpy(nm, name, k - name);
    nm[k - name] = '\0';
    poas_out.length(poas_out.length() + 1);
    poas_out[poas_out.length() - 1] = nm;
  }

  if( k == kend )  return 0;

  transient_out = 0;
  if( *k == TRANSIENT_SUFFIX_SEP ) {
    transient_out = 1;
    k += TRANSIENT_SUFFIX_SIZE + 1;
  }
  if( k >= kend || *k )  return 0;
  k++;

  id_out.length(kend - k);
  memcpy(id_out.NP_data(), k, kend - k);

  return 1;
}

static
void
toIOR(const char* iorstr,IOP::IOR& ior)
{
  size_t s = (iorstr ? strlen(iorstr) : 0);
  if (s<4)
    throw CORBA::MARSHAL(0,CORBA::COMPLETED_NO);
  const char *p = iorstr;
  if (p[0] != 'I' ||
      p[1] != 'O' ||
      p[2] != 'R' ||
      p[3] != ':')
    throw CORBA::MARSHAL(0,CORBA::COMPLETED_NO);

  s = (s-4)/2;  // how many octets are there in the string
  p += 4;

  cdrMemoryStream buf((CORBA::ULong)s,0);

  for (int i=0; i<(int)s; i++) {
    int j = i*2;
    CORBA::Octet v;
    
    if (p[j] >= '0' && p[j] <= '9') {
      v = ((p[j] - '0') << 4);
    }
    else if (p[j] >= 'a' && p[j] <= 'f') {
      v = ((p[j] - 'a' + 10) << 4);
    }
    else if (p[j] >= 'A' && p[j] <= 'F') {
      v = ((p[j] - 'A' + 10) << 4);
    }
    else
      throw CORBA::MARSHAL(0,CORBA::COMPLETED_NO);

    if (p[j+1] >= '0' && p[j+1] <= '9') {
      v += (p[j+1] - '0');
    }
    else if (p[j+1] >= 'a' && p[j+1] <= 'f') {
      v += (p[j+1] - 'a' + 10);
    }
    else if (p[j+1] >= 'A' && p[j+1] <= 'F') {
      v += (p[j+1] - 'A' + 10);
    }
    else
      throw CORBA::MARSHAL(0,CORBA::COMPLETED_NO);
    buf.marshalOctet(v);
  }

  buf.rewindInputPtr();
  CORBA::Boolean b = buf.unmarshalBoolean();
  buf.setByteSwapFlag(b);

  ior.type_id = IOP::IOR::unmarshaltype_id(buf);
  ior.profiles <<= buf;
}

void IORInfo(CONST_STRING_T str_ior, STRING_T & ip_addr, ULONG_T & port)
{
   IOP::IOR ior;
   toIOR(str_ior, ior);
   if (ior.profiles.length() == 0 && strlen(ior.type_id) == 0) {
      // ior is a nil object
      ip_addr = "0";
      port = 0;
      return;
   } else {
      try {
         for (unsigned long count=0; count < ior.profiles.length(); count++) {
            if (ior.profiles[count].tag == IOP::TAG_INTERNET_IOP) {
               IIOP::ProfileBody pBody;
               IIOP::unmarshalProfile(ior.profiles[count],pBody);
               ip_addr = pBody.address.host;
               port = pBody.address.port;
            } else if (ior.profiles[count].tag == IOP::TAG_MULTIPLE_COMPONENTS) {
               IIOP::ProfileBody pBody;
               IIOP::unmarshalMultiComponentProfile(ior.profiles[count], pBody.components);
            } else {
	         }
         }
      } catch (CORBA::MARSHAL& ex) {
         const char* ms = ex.NP_minorString();
         if (ms) {
            printf("invalid ior\nCORBA::MARSHAL: minor = %s\n", ms);
         } else {
            printf("invalid ior\nCORBA::MARSHAL: minor = ?\n");
         }
      } catch (...) {
         printf("Exception while processing stringified IOR\n");
      }
   }
}


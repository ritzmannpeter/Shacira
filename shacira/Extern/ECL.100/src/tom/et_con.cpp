// ===========================================================================
// Definition cTomConClient
// ---------------------------------------------------------------------------
//
// cTomConsole
//    |
//    +--cTomConClient   - Stellt einen Remote-Console-Server als
//                         Tomaten-Console zur Verfuegung.
//
// ---------------------------------------------------------------------------


#ifdef __INTERFACE__

#include "tom/et_tomate.hpp"
#include "tom/et_conser.hpp"

class cTomConServer : public cTomConsole {
   char buffer[1024];
   cConServer con_ser;
public:
   cTomConServer(cString name = NULL) :
      con_ser(name) {}
   virtual ~cTomConServer() {}

   virtual int io_putch(int ch) {
      buffer[0] = ch; buffer[1] = '\0';
      return con_ser.cputs(buffer);
   }
   virtual int io_getch() { return EOF; /*???*/ }
   virtual int io_vprintf(const char *fmt, va_list arg) {
      // Sicherheitsloch: was ist, wenn hier buffer nicht ausreicht ???
      vsprintf( buffer, fmt, arg );
      return con_ser.cputs( buffer );
   }
   virtual int io_kbhit() { return 0; }
   virtual int io_cputs(const char *str) {
      return con_ser.cputs( str );
   }
   virtual char* io_cgets(char *buf) {
      return con_ser.cgets( buf );
   }
};

#endif /*__INTERFACE__*/

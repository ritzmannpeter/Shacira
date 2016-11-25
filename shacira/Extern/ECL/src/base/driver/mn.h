// ===========================================================================
// base/driver/mn.h                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsgNode - Basisklasse zur Realisierung von Meldungs-Knoten
// 
// ===========================================================================

#ifndef __ecl_mn__
#define __ecl_mn__


// Other ECL headers
#include "base/message.h"


namespace ecl {


// ===========================================================================
// Definition cMsgNode
// ---------------------------------------------------------------------------
//
// Basisklasse zur Realisierung von Meldungs-Knoten
//
// cMsgNode
//
// ===========================================================================

class cMsgNode {

public:
   // Konstruktor fuer unbenannten Knoten
   cMsgNode(int send_mode);
   // Konstruktor fuer benannten Knoten
   cMsgNode(const cString &name, int send_mode);
   // Destruktor
   virtual ~cMsgNode();

   //
   virtual bool ping() = 0;

   //
   virtual void createChannel(int msg_count, int msg_size) = 0;
   //
   virtual void closeChannel() = 0;
   //
   virtual void connectToChannel() = 0;
   //
   virtual void disconnectFromChannel() = 0;

   //
   virtual cString getFullName() const = 0;
   //
   virtual void sendMsg(cMsg msg) = 0;
   //
   virtual cMsg callMsg(cMsg msg, int timeout) = 0;
   //
   virtual cMsg receiveMsg() = 0;
   //
   virtual bool mustReplyMsg(const cMsg& msg_to_reply) = 0;
   //
   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg) = 0;

   // Protokollnamen aus 'name' ermitteln ("local" falls nicht angegeben)
   static cString getProtocol(const cString &name);
   // Rechnernamen aus 'name' ermitteln ("." falls nicht angegeben)
   static cString getAddress(const cString &name);
   // Teilnehmernamen aus 'name' ermitteln
   static cString getName(const cString &name);

   // Teilnehmername ermitteln
   cString getName() const
      { return _name; }
   // Adresse (Rechnername) ermitteln
   cString getAddress() const
      { return _address; }
   // Ist der MsgNode unbenannt (anonym)?
   bool isAnonymous() const
      { return _name.isEmpty(); }

   // Warte-Flag setzen
   void setWait(bool wait)
      { _wait = wait; }
   // Warte-Flag erfragen
   bool getWait() const
      { return _wait; }

   // Transportform der Meldung liefern (const)
   cMsg::MSGHDR *getMsg(cMsg& msg) const
      { return msg.getMsg(); }
   // Transportform der Meldung liefern (non-const)
   const cMsg::MSGHDR *getMsg(const cMsg& msg) const
      { return msg.getMsg(); }
   // Laenge (Bytezahl) der Transportform ermitteln
   int getMsgLen(const cMsg& msg) const
      { return msg.getMsgLen(); }
   // Meldungsobjekt aus Rohdaten erzeugen
   cMsg newMsg(void *mem) const
      { return cMsg((cMsg::MSGHDR *)mem); }

   // Protokollspezifische Zusatzdaten 1 ermitteln
   int getPrd1(const cMsg& msg) const
      { return msg.getMsg() ? msg.getMsg()->prd1 : 0; }
   // Protokollspezifische Zusatzdaten 2 ermitteln
   int getPrd2(const cMsg& msg) const
      { return msg.getMsg() ? msg.getMsg()->prd2 : 0; }

   // Protokollspezifische Zusatzdaten 1 setzen
   void setPrd1(cMsg& msg, int value) const
      { if ( msg.getMsg() ) msg.getMsg()->prd1 = value; }
   // Protokollspezifische Zusatzdaten 2 setzen
   void setPrd2(cMsg& msg, int value) const
      { if ( msg.getMsg() ) msg.getMsg()->prd2 = value; }

   // Gewuenschtes 'send'-Verhalten, wenn Empfaenger nicht erreichbar
   int getModeAlive() const
      { return _send_mode & cMsgRecipient::modeAliveMask; }
   // Gewuenschtes 'send'-Verhalten, wenn Puffer voll
   int getModeFull() const
      { return _send_mode & cMsgRecipient::modeFullMask; }

private:

   // Namensteil des Knotennamens
   cString _name;
   // Adressteil des Knotennamens
   cString _address;
   // Wait-Flag fuer Empfangs-Operationen
   bool _wait;
   // Verfahren bei 'send', wenn Empfaenger nicht erreichbar bzw. Puffer voll
   int _send_mode;

};


}; // namespace ecl


#endif // __ecl_mn__


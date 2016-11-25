// ===========================================================================
// base/message.h                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsg                 - Meldung.
//
//    cMsgRecipient        - Adressat (zum Senden von Meldungen).
//     |
//     +-cMsgBox           - Briefkasten (zum Empfangen von Meldungen).
//
//! @class ecl::cMsgBox
//!
//! Das Grundgeruest eines Threads, der diese Klassen benutzt, sieht etwa
//! folgendermassen aus.
//!
//!   @code
//!     cMsgBox msg_box("my_name");
//!
//!     while ( true ) {
//!        cMsg msg = msg_box.receive();
//!
//!        // Meldung bearbeiten:
//!        switch ( msg.getMsgId() ) {
//!           ...
//!        }
//!
//!        // Meldung weiterschicken:
//!        if ( send_it_to_other ) {
//!           cMsgRecipient other("other_name");
//!           other.send(msg);
//!        }
//!
//!        // Meldung beantworten?
//!        if ( msg_box.mustReply(msg) ) {
//!           msg_box.reply(msg, cMsg(MY_MSG_ID, "OK"));
//!        }
//!
//!        // Meldung an sich selbst schicken
//!        msg_box.send(cMsg(MY_MSG_ID, "msg"));
//!     }
//!   @endcode
//!
//! Die Namen der Teilnehmer bestehen aus bis zu 3 Teilen:
//!
//!    -# Art der verwendeten Protokolls
//!    -# Adresse (=Rechnername) des Teilnehmers (nur bei cMsgRecipient)
//!    -# Name des Teilnehmers
//!
//! Moegliche Protokolle sind:
//!
//!   @verbatim
//!     Protokoll  | Beschreibung    | Call | T->T | P->P | Netz | OS/2 | W32
//!    ------------+-----------------+------+------+------+------+------+------
//!     :private:  | Anonyme Queues  |  Ja  |  Ja  | Nein | Nein |  Ja  |  Ja
//!     :local:    | Benannte Queues |  Ja  |  Ja  |  Ja  | Nein |  Ja  |  Ja
//!     :queue:    | Systemqueues    | Nein |  Ja  |  Ja  | Nein |  Ja  | Nein
//!     :mslot:    | Mailslots       | Nein |  Ja  |  Ja  |  Ja  | Nein |  Ja
//!     :npipe:    | Named Pipes     | (Ja) |  Ja  |  Ja  |  Ja  |  Ja  |  Ja
//!                                     |      |      |      |      |      |
//!                  Reply moeglich? <--+      |      |      |      |      |
//!         Intraprozess (Thread zu Thread) <--+      |      |      |      |
//!          Interprozess (von Prozess zu Prozess) <--+      |      |      |
//!                Von Maschine zu Maschine (im Netzwerk) <--+      |      |
//!                                           Laeuft unter OS/2? <--+      |
//!                                                 Laeuft unter Win32? <--+
//!   @endverbatim
//!
//! Beispiele fuer den Teilnehmer "MyName":
//!
//!   @verbatim
//!     Teilnehmername:      | Protokoll:  | Rechner:
//!    ----------------------+-------------+-------------
//!     MyName               | Lokal       | .
//!     :npipe:MyName        | Named Pipes | .
//!     mac42:MyName         | Lokal       | mac42
//!     :mslot:mac42:MyName  | Mail Slots  | mac42
//!   @endverbatim
//!
//! Ausserdem ist es moeglich, anonyme cMsgBox-Objekte anzulegen. Diese
//! koennen jedoch nur zur Intra-Prozesskommunikation verwendet werden.
//
// ===========================================================================

#ifndef __ecl_message__
#define __ecl_message__


// Standard headers
#include <cstdarg>
#include <cstdlib>

// Other ECL headers
#include "base/error.h"
#include "base/string.h"
#include "base/base_ex.h"

       
namespace ecl {


// Forward-Deklarationen
// ===========================================================================

class cMsgNode;


// ===========================================================================
// Definition cErrMsg
// ---------------------------------------------------------------------------
//
//! Exception-Objekte der Messages-Schicht.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrMsg : public cErrBase {

public:
   cErrMsg(int err, const char *name);

   enum ERR_CODE { errBase = ERR_PREFIX('M','S','G'),

      //! Fehler
      errOpenChannel = errBase+errError , //!< Kann nicht Oeffnen zum Senden
      errCreateChannel                  , //!< Kann nicht Erzeugen zum Empfangen
      errSendToChannel                  , //!< Fehler beim Senden
      errReceiveFromChannel             , //!< Fehler beim Empfangen
      errSendEmptyMsg                   , //!< Versuch, leere Meldung zu senden
      errInvalidMsg                     , //!< Ungueltige Meldung empfangen
      errInvalidProtocol                , //!< Ungueltiges Protokoll angegeben
      errUnsupportedProtocol            , //!< Protokoll nicht unterstuetzt
      errMsgTooLong                     , //!< Meldung zu lang
      errNoAnonymousRecipient             //!< Anonymer Adressat nicht zulaessig

   };

};


// ===========================================================================
// Definition cMsg
// ---------------------------------------------------------------------------
//
//! Verwaltungs- und Nutzdaten, die als Meldung verschickt werden koennen.
//!
//! Unterstuetzte Platzhalter im Formatstring (bprintf):
//!
//! @verbatim
//!   %    | Bedeutung                      | Auf Stack | In Meldung
//!  ------+--------------------------------+-----------+------------
//!   %c   | ein Zeichen (oder Byte)        | int       | 1 Byte
//!   %i   | ein short (oder USHORT)        | int       | 2 Byte
//!   %u   | ein Wort (oder WORD)           | int       | 4 Byte
//!   %d   | ein Wort (oder WORD)           | int       | 4 Byte
//!   %l   | ein Langwort                   | long      | 4 Byte
//!   %f   | eine Realzahl (immer double)   | double    | 8 Byte
//!   %s   | Adr. eines nullterm. Strings   | char *s   | *s + '\0'
//!   %t   | Adresse einer Struktur mit     | size_t *s | *s
//!        | vorangehender Groesse (size_t) |           |
//!   %%   | das Zeichen '%'                | -         | '%'
//!   #ddd | dez. Angabe eines Zeichens     | -         | '\ddd'
//!   #xhh | hex. Angabe eines Zeichens     | -         | '\0xhh'
//!   ##   | das Zeichen '#'                | -         | '#'
//! @endverbatim
//!
//! Beispiel fuer %t:
//!
//! @code
//!    struct T {
//!       size_t my_size;
//!       int a, b, c;
//!       // ...
//!    } t;
//!
//!    t.my_size = sizeof t;
//!    cMsg msg(MY_ID, "%t", &t);
//! @endcode
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsg {
   friend class cMsgNode;

public:
   //! Konstruktor fuer leere Meldung (isEmpty liefert true)
   cMsg();
   //! Konstruktor fuer datenfreie Meldung
   cMsg(int msg_id);
   //! Konstruktor ueber Zeiger auf Datenbereich
   cMsg(int msg_id, int size, const void *data);
   //! Konstruktor ueber cString
   cMsg(int msg_id, cString str);
   //! Konstruktor ueber bprintf
   cMsg(int msg_id, const char *fmt, ...);
   //! Konstruktor ueber vprintf
   cMsg(int msg_id, const char *fmt, va_list ap);
   //! Copy-Konstruktor
   cMsg(const cMsg& other);
   ~cMsg();

   //! Zuweisungsoperator
   cMsg& operator=(const cMsg& other);

   //! Ist die Meldung gueltig?
   bool isValid() const;
   //! Ist die Meldung gueltig, aber leer?
   bool isEmpty() const;

   //! Meldungs-ID erfragen
   int getMsgId() const
      { return msg ? msg->id : 0; }

   //! Erfragen der Meldungs-Daten
   void *getData() const
      { return msg ? msg->d : 0; }
   //! Erfragen der Laenge der Meldungs-Daten
   int getDataLen() const
      { return msg ? msg->size : 0; }

private:
   struct MSGHDR {
      int magic;     //!< Identifizierung
      int id;        //!< Meldungs-ID
      int size;      //!< Allokierte Groesse
      ATOMIC_T refc; //!< Referenzzaehler
      int prd1;      //!< Protokollspezifische Zusatzdaten 1
      int prd2;      //!< Protokollspezifische Zusatzdaten 2
      char d[1];     //!< Groesse dynamisch
   } *msg;

   //! Konstruktor ueber interne MSGHDR-Struktur
   cMsg(const MSGHDR *foreign_msg);
   //! Allokieren und vorinitialisieren der internen Struktur
   MSGHDR *alloc(int len);
   //! Referenzzaehler dekrementieren, Struktur evtl. freigeben
   void dealloc(MSGHDR *& msg);
   //! Hilfsfunktion zur Initialisieren der internen Struktur
   bool init(int msg_id, const void *data, int size);

   //! Transportform der Meldung liefern (const)
   const MSGHDR *getMsg() const
      { return msg; }
   //! Transportform der Meldung liefern (non-const)
   MSGHDR *getMsg()
      { return msg; }
   //! Laenge (Bytezahl) der Transportform ermitteln
   int getMsgLen() const
      { return sizeof *msg + getDataLen() - 1; }

};


// ===========================================================================
// Definition cMsgRecipient
// ---------------------------------------------------------------------------
//
//! Meldungsadressat.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsgRecipient {

public:
   //! \brief Verhalten von 'send', wenn Empfaenger nicht bereit oder Puffer
   //! voll Gruppenweise maskierbar, z.B. (modeAliveIgnore | modeFullOverwrite)

   enum SEND_MODE {

                        //! Reaktion von 'send', wenn Empfaenger nicht bereit
      modeAliveError    = 0x0000,   //!< Werfen von cErrMsg::errOpenChannel
      modeAliveIgnore   = 0x0001,   //!< Ignorieren des Aufrufs von 'send'
      modeAliveCreate   = 0x0002,   //!< Standardpuffer anlegen (16 x 128 Bytes)
      modeAliveMask     = 0x000f,   //!< ... zum Ausmaskieren der modeAlive-Gruppe

                        //! Reaktion von 'send', wenn Puffer zum Empfaenger voll
      modeFullBlock     = 0x0000,   //!< Blockieren des aufrufenden Threads
      modeFullError     = 0x0010,   //!< Werfen von cErrBase::errOverflow
      modeFullIgnore    = 0x0020,   //!< Verwerfen der aktuellen Meldung
      modeFullOverwrite = 0x0030,   //!< Ueberschreiben der aeltesten Meldung im Puffer
      modeFullMask      = 0x00f0    //!< ... zum Ausmaskieren der modeFull-Gruppe

   };

   //! Anlegen eines benannten Adressaten
   cMsgRecipient(cString address_name, int send_mode = 0);
   //! Loeschen des Adressaten
   ~cMsgRecipient();

   //! Pruefen, ob Adressat lebt
   bool ping();
   //! Meldung abschicken
   void send(cMsg msg);
   //! Meldung abschicken und auf Antwort warten
   cMsg call(cMsg msg, int timeout = -1);

   //! Name des Adressaten
   cString getName() const;
   //! Adresse (Zielrechner) des Adressaten
   cString getAddress() const;
   //! Protokollspezifischer Name des Adressaten
   cString getFullName() const;

protected:
   //! Anlegen eines anonymen Adressaten (nur zusammen mit MsgBox moeglich!)
   cMsgRecipient(int send_mode);
   //! Anlegen eines benannten oder anonymen Adressaten
   cMsgRecipient(cString address_name, bool maybe_anonymous, int send_mode);
   //! Initialisierung des Adressaten
   void init(cString address_name, bool maybe_anonymous, int send_mode);
   //! Zeiger auf Implementierungsklasse (abhaengig von Meldungs-Protokoll)
   cMsgNode *node;

private:
   // Copying is not allowed!
   cMsgRecipient(const cMsgRecipient &other);
   cMsgRecipient &operator=(const cMsgRecipient &other);
};


// ===========================================================================
// Definition cMsgBox
// ---------------------------------------------------------------------------
//
//! Meldungsempfaenger.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMsgBox : public cMsgRecipient {

public:
   //! Anlegen einer anonymen MsgBox (nur Intra-Prozess-Kommunikation)
   cMsgBox(int msg_count = 16, int msg_size = 128, int send_mode = 0);
   //! Anlegen einer benannten MsgBox (vgl. Modul-Dokumentation)
   cMsgBox(cString name, int msg_count = 16, int msg_size = 128, int send_mode = 0);
   //! Loeschen der MsgBox
   ~cMsgBox();

   //! Empfangen einer Meldung (Warten abhaengig vom Wait-Flag)
   cMsg receive();
   //! Empfangen einer gefilterten Meldnung (NOCH NICHT IMPLEMENTIERT!!!)
   cMsg receiveFiltered(unsigned char msg_low, unsigned char msg_hi);

   //! Wird eine Antwort auf die Meldung erwartet?
   bool mustReply(const cMsg& msg_to_reply) const;
   //! Beantworten der Meldung msg_to_reply mit der Meldung reply_msg
   void reply(const cMsg& msg_to_reply, cMsg reply_msg);

   //! Warte-Flag setzen
   void setWait(bool wait);
   //! Warte-Flag erfragen
   bool getWait() const;

};

}; // namespace ecl


#endif // __ecl_message__


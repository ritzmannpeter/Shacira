// ===========================================================================
// ew_listctls.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwControl
//           |
//           +-cwListCtl   - Basisklasse fuer ECL-Listen-Controls
//
// ===========================================================================

#include "win/ew_listctls.hpp"
#include "win/ew_editctls.hpp"

#include <limits.h>                              /* wg. CHAR_MIN, CHAR_MAX */
#include "base/eb_err.hpp"
#include "store/es_var.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_elo.hpp"
#include "win/ew_controls.hpp"

#endif /*__INTERFACE__*/




// Interne Daten
// ===========================================================================

// Offset fuer Field-Index
#define FIELD_OFF csQuery::fldIconID




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwListElem
// ---------------------------------------------------------------------------
//
// Fuer jedes cwListElem-Objekt werden die folgenden Standardfelder definiert:
//
//  - Schluesselfeld (Key): Enthaelt einen eindeutigen Schluesselwert fuer den
//    zum cwListElem-Objekt gehoerenden Datensatz.
//
//  - Namensfeld (Name): Enthaelt einen als Objektnamen benutzbaren, kurzen
//    Text. Bei einem Mitarbeiter-Datensatz koennte das Namensfeld z.B. aus
//    der Kombination Vorname + Nachname bestehen.
//
//  - Beschreibungsfeld (Descr): Enthaelt einen als Objektbeschreibung benutz-
//    baren, laengeren Text. Bei einem Mitarbeiter-Datensatz koennte das Be-
//    schreibungsfeld z.B. aus der Kombination Vorname + Nachname + Wohnort +
//    Strasse + Telefon bestehen.
//
//  - Sinnbildfeld (Icon): Enthaelt ein den Typ des Datensatzes beschreiben-
//    des Icon.
//
// Das Schluessel- und Namensfeld muss auf jeden Fall geliefert werden.
//
// Aufbau der Elemente im Speicher:
//
//    +------------+----------------+---+------+---+------+-..-+---+------+
//    | Data of    | Derived class  | S . DATA | S . DATA |    | S . DATA |
//    | cwListElem | additional mem | 1 .  1   | 2 .  2   |    | n .  n   |
//    +------------+----------------+---+------+---+------+-..-+---+------+
//
//  - S<i> = Statusbyte von Feld <i>
//  - DATA<i> = Datenbereich von Feld <i>
//
// cBase
//  +--cwListElem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwListElem : public cEloElement {
   ELO_DECLARE(cwListElem,cEloElement)
   friend class cwListCtl;

public:

   // Default-Konstruktor
   cwListElem(const cEloElementDescription *elem_descr = 0) :
      cEloElement(elem_descr) { init(); }
   // Konstruktor ueber Query
   cwListElem(csQuery *query) :
      cEloElement(query->getDescription()) { init(query); }
   // Konstruktor ueber Defaultfelder
   cwListElem(cString key, cString name, cString descr = cString(),
              const cEloElementDescription *elem_descr = 0);
   // Destruktor
   ~cwListElem();


   // Speicherverwaltung
   // ==================

   // new-Operator
   void *operator op_new1(size_t size, cwListCtl *ctl);
   // delete-Operator
   void operator op_delete1(void *ptr, cwListCtl *ctl);
   // delete-Operator (speziell fuer VCPP)
   void operator delete(void *ptr);


   // Element-Flags
   // =============

   // Flags
   enum FLAGS { eflStart = 1,
      eflChildsLoaded   = eflStart << 0,  // Child-Elemente bereits geladen?
      eflChildsPossible = eflStart << 1,  // Child-Elemente moeglich, aber nicht geladen?
      eflChildsAutoView = eflStart << 2,  // Child-Elemente automatisch anzeigen?
      eflPreventSelect  = eflStart << 3,  // Verhindere Rekursion bei Selektion
      eflDisplayBold    = eflStart << 4,  // Schriftart BOLD benutzen
      eflDisplayFgColor = eflStart << 5,  // Abweichende Vordergrundfarbe benutzen (fg_col)
      eflDisplayBgColor = eflStart << 6,  // Abweichende Hintergrundfarbe benutzen (bg_col)
      eflUser           = eflStart << 7   // Benutzerdefinierte Flags
   };

   // Alle aktuellen Element-Flags ermitteln
   inline int getFlags() const
      { return flags; }
   // Bestimmte aktuelle Element-Flags ermitteln
   inline int getFlags(int mask) const
      { return flags & mask; }
   // Bestimmte Element-Flags setzen
   void setFlags(int mask, bool set = true);


   // Allgemeines
   // ===========

   // Zeiger auf zugehoeriges ListCtl ermitteln
   inline cwListCtl *getListCtl() const
      { return ctl; }
   // Zeiger auf zusaetzlichen Speicherbereich ermitteln (oder 0)
   void *getAddDataPtr() const;

   // Benutzerspezifische Zusatzinformationen setzen
   void setUserData(void *buf);
   // Benutzerspezifische Zusatzinformationen erfragen
   void *getUserData(void *buf, int buf_size) const;
   // Laenge der benutzerspezifischen Zusatzinformationen erfragen
   int getUserDataLen() const;
   // Pufferadresse der benutzerspezifischen Zusatzinformationen erfragen
   void *getUserDataBuf();

   // Datensatz aus Query erneut einlesen ('query' muss aktuelle Daten haben)
   void refresh(csQuery *query);

   // Liefert die Abfrage, die das Element erzeugt hat
   csQuery *getQuery() const;
   // Liefert die Abfrage, die Kinder dieses Elementes erzeugt
   csQuery *getSubquery() const;


   // Schriftart, Farben
   // ==================

   // Wird Datensatz mit Schriftattribut BOLD angezeigt?
   bool isBold() const;
   // Schriftattribut BOLD setzen/ruecksetzen
   void setBold(bool bold = true);

   // Aktuelle Vordergrundfarbe erfragen (cdColor::None = Standardfarbe)
   cdColor getFgColor() const;
   // Aktuelle Hintergrundfarbe erfragen (cdColor::None = Standardfarbe)
   cdColor getBgColor() const;
   // Abweichende Vordergrundfarbe setzen (Standardfarbe = cdColor::None)
   void setFgColor(const cdColor& new_fg_col);
   // Abweichende Hintergrundfarbe setzen (Standardfarbe = cdColor::None)
   void setBgColor(const cdColor& new_bg_col);


   // Feldbeschreibung
   // ================

   // Feldzahl (excl. Default-Felder, d.h. bei 0 sind Defaultfelder verfuegbar)
   int getCount() const;

   // Ermittelt den Typ eines Feldes
   csQuery::TYPE getType(int fld) const;
   // Kann das Feld NULL-Werte enthalten?
   bool isNullable(int fld) const;
   // Darf das Feld vom Anwender bearbeitet werden?
   bool isEditable(int fld) const;

   // Ermittelt die maximale Groesse eines Feldes
   int getBufferSize(int fld) const;
   // Maximale Feldbreite [Zeichen]
   int getWidth(int fld) const;
   // Anzahl Nachkommastellen [Zeichen]
   int getPrec(int fld) const;

   // Ermittelt den (Datenbank-)Namen eines Feldes
   cString getFieldName(int fld) const;


   // Feldwerte
   // =========

   // Ermittelt den NULL-Wert des Feldes
   bool isNull(int fld) const;
   // Setzt den NULL-Zustand bei einem Feld
   void setNull(int fld) const;

   // Erzeugt die String-Repraesentation des Feldes
   bool get(int fld, char *buf, int size) const;
   // Erzeugt die cString-Repraesentation des Feldes
   bool get(int fld, cString& buf) const;
   // Schreibt den Inhalt des Feldes in eine Storage
   bool get(int fld, csStorage *buf) const;

   // Wert des Feldes ueber int setzen
   bool put(int fld, int _buf);
   // Wert des Feldes ueber double setzen
   bool put(int fld, double _buf);
   // Wert des Feldes ueber cTime setzen
   bool put(int fld, cTime _buf);
   // Wert des Feldes ueber cDate setzen
   bool put(int fld, cDate _buf);
   // Wert des Feldes ueber cDateTime setzen
   bool put(int fld, cDateTime _buf);
   // Wert des Feldes ueber char setzen
   bool put(int fld, char _buf);
   // Wert des Feldes ueber String setzen
   bool put(int fld, const char *buf);
   // Wert des Feldes eine Storage setzen
   bool put(int fld, const csStorage *buf);

   // Erzeugt (per new) ein mit dem Feld assoziiertes csStorage-Objekt (const)
   const csStorage *makeVar(int fld) const;
   // Erzeugt (per new) ein mit dem Feld assoziiertes csStorage-Objekt (non-const)
   csStorage *makeVar(int fld);
   // Erzeugt (per new) ein mit dem Feld kompatibles (eigenstaendiges) csStorage-Objekt
   csStorage *makeCompatibleVar(int fld) const;


   // Verkettung
   // ==========

   // Zeiger auf Vorgaengerelement ermitteln
   inline cwListElem *getPrev() const
      { return prev; }
   // Zeiger auf Nachfolgeelement ermitteln
   inline cwListElem *getNext() const
      { return next; }
   // Zeiger auf erstes Kindelement ermitteln
   inline cwListElem *getFirstChild() const
      { return head; }
   // Zeiger auf letztes Kindelement ermitteln
   inline cwListElem *getLastChild() const
      { return tail; }
   // Zeiger auf Elternelement ermitteln
   inline cwListElem *getParent() const
      { return parent; }

   // Ist Element in eine Liste eingekettet?
   inline bool isLinked() const
      { return prev || next; }
   // Ist Element ein Kindelement?
   inline bool isChild() const
      { return parent != 0; }
   // Hat Element Kindelemente?
   inline bool hasChilds() const
      { return head || tail; }


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const;
   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const;
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const;
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const;
   // Wird aufgerufen, um die ID oder den Index des assoziierten Symbols zu erfragen
   int onGetBitmapId(BITMAP_STYLE bs) const;


private:

   cwListCtl *ctl;               // ListCtl, in dem das Element angezeigt wird
   cdColor fg_col, bg_col;       // Evtl. abweichende Vorder- oder Hintergrundfarbe
   int flags;                    // Element-Flags

   cwListElem *prev, *next;      // Vorgaenger und Nachfolger in der Liste
   cwListElem *head, *tail;      // Erstes und letztes Kind-Element der Liste
   cwListElem *parent;           // Eltern-Knoten bei hierarchischer Struktur

   // Initialisierung aus Abfrage
   void init(csQuery *query = 0);

};

#endif /*__INTERFACE__*/


// Implementierung cwListElem
// ===========================================================================

cwListElem::~cwListElem()
{
   if ( ctl != 0 )
      ctl->onDeletingElement(this);

   #if __DEBUG_ALLOC__
      head = (cwListElem *)0x89abcdef;
   #endif
}

cwListElem::cwListElem(cString key, cString name, cString descr,
                       const cEloElementDescription *elem_descr) :
   cEloElement(elem_descr)
{
   init();

   put(csQuery::fldKey, key);
   put(csQuery::fldName, name);
   put(csQuery::fldDescr, descr);
}

void cwListElem::init(csQuery *query)
{
   flags = 0;
   prev = next = head = tail = parent = 0;

   if ( query ) {
      refresh(query);
   } else {
      char *from = (char*)this + sizeof(cwListElem);
      int size = ctl->onGetAddByteCount() + ctl->field_data_size;
      memset(from, 0, size);
   }

   if ( ctl != 0 )
      ctl->onCreatingElement(this);
}


// Speicherverwaltung
// ==================

void * cwListElem::operator op_new1(size_t size, cwListCtl *ctl)
{
   size += ctl->onGetAddByteCount() + ctl->field_data_size;
   cwListElem *elem = (cwListElem*)dbg_new(size, file, line);
   elem->ctl = ctl;
   return elem;
}

void cwListElem::operator op_delete1(void *ptr, cwListCtl * /*ctl*/)
{
   dbg_delete(ptr, file, line);
}

void cwListElem::operator delete(void *ptr)
{
   // Speziell fuer VCPP
   dbg_delete(ptr, __FILE__, __LINE__);
}


// Element-Flags
// =============

void cwListElem::setFlags(int mask, bool set)
{
   if ( set ) {
      flags |= mask;
   } else {
      flags &= ~mask;
   }
}


// Allgemeines
// ===========

void * cwListElem::getAddDataPtr() const
{
   int add_bytes = ctl->onGetAddByteCount();
   return add_bytes > 0 ?
      (void*)((char*)this + sizeof(cwListElem))
    : (void*)0;
}

void cwListElem::setUserData(void *buf)
{
   if ( ctl->user_data_size > 0 )
      memcpy((char*)this + ctl->user_data_offset, buf, ctl->user_data_size);
}

void * cwListElem::getUserData(void *buf, int buf_size) const
{
   if ( ctl->user_data_size > 0 ) {
      memcpy(buf, (char*)this + ctl->user_data_offset, buf_size);
      return buf;
   } else {
      return 0;
   }
}

int cwListElem::getUserDataLen() const
{
   return ctl->user_data_size;
}

void * cwListElem::getUserDataBuf()
{
   return (char*)this + ctl->user_data_offset;
}

void cwListElem::refresh(csQuery *query)
{
   // Der folgende Code funktioniert nur, wenn der Container aus 'query'
   // oder einer mit 'query' identischen Abfrage heraus erstellt wurde!

   for ( int fld = FIELD_OFF ; fld < ctl->field_count + FIELD_OFF ; fld++ ) {

      cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
      char *data = (char*)this + fd.offset + 1;

      bool nn = !query->isNull(fld); // nn = not null

      if ( nn ) {
         switch ( fd.type ) {
         case csQuery::tInt:     nn = query->get(fld, *((int*)data)); break;
         case csQuery::tDouble:  nn = query->get(fld, *((double*)data)); break;
         case csQuery::tTime:    nn = query->get(fld, *((cTime*)data)); break;
         case csQuery::tDate:    nn = query->get(fld, *((cDate*)data)); break;
         case csQuery::tWeek:    nn = query->get(fld, *((cDate*)data)); break;
         case csQuery::tChar:    nn = query->get(fld, *((char*)data)); break;
         case csQuery::tString:  nn = query->get(fld, data, fd.buffer_size); break;
         case csQuery::tIcon:    nn = query->get(fld, *((cIcon*)data)); break;
         case csQuery::tBitmap:  nn = query->get(fld, *((cBitmap*)data)); break;
         default:                nn = true; break;
         }
      }

      if ( nn ) {
         data[-1] = 0;
      } else {
         data[-1] = cwListCtl::sbmIsNull;
         switch ( fd.type ) {
         case csQuery::tInt:     *((int*)data)      = 0; break;
         case csQuery::tDouble:  *((double*)data)   = 0.0; break;
         case csQuery::tTime:    *((cTime*)data)    = cTime(); break;
         case csQuery::tDate:    *((cDate*)data)    = cDate(); break;
         case csQuery::tWeek:    *((cDate*)data)    = cDate(); break;
         case csQuery::tChar:    *((char*)data)     = '\0'; break;
         case csQuery::tString:  strxcpy(data, "", fd.buffer_size); break;
         case csQuery::tIcon:    *((cIcon*)data)   = cIcon(); break;
         case csQuery::tBitmap:  *((cBitmap*)data) = cBitmap(); break;
         default:                break;
         }
      }
   }
}

csQuery * cwListElem::getQuery() const
{
   return ctl->getQueryOfElem(this, false);
}

csQuery * cwListElem::getSubquery() const
{
   return ctl->getQueryOfElem(this, true);
}


// Schriftart, Farben
// ==================

bool cwListElem::isBold() const
{
   return !!getFlags(eflDisplayBold);
}

void cwListElem::setBold(bool bold)
{
   setFlags(eflDisplayBold, bold);
   if ( ctl != 0 && isLinked() )
      ctl->onElemAttrChanged(this, cwListCtl::eatFontBold);
}

cdColor cwListElem::getFgColor() const
{
   return getFlags(eflDisplayFgColor) ?
      fg_col
    : cdColor::None;
}

cdColor cwListElem::getBgColor() const
{
   return getFlags(eflDisplayBgColor) ?
      bg_col
    : cdColor::None;
}

void cwListElem::setFgColor(const cdColor& new_fg_col)
{
   fg_col = new_fg_col;
   setFlags(eflDisplayFgColor, cdColor::COLOR(new_fg_col) != cdColor::None);
   if ( ctl != 0 && isLinked() )
      ctl->onElemAttrChanged(this, cwListCtl::eatColorFg);
}

void cwListElem::setBgColor(const cdColor& new_bg_col)
{
   bg_col = new_bg_col;
   setFlags(eflDisplayBgColor, cdColor::COLOR(new_bg_col) != cdColor::None);
   if ( ctl != 0 && isLinked() )
      ctl->onElemAttrChanged(this, cwListCtl::eatColorBg);
}


// Feldbeschreibung
// ================

int cwListElem::getCount() const
{
   return ctl->field_count + FIELD_OFF;
}

csQuery::TYPE cwListElem::getType(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].type;
}

bool cwListElem::isNullable(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].nullable;
}

bool cwListElem::isEditable(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].editable;
}

int cwListElem::getBufferSize(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].buffer_size;
}

int cwListElem::getWidth(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].disp_width;
}

int cwListElem::getPrec(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].disp_prec;
}

cString cwListElem::getFieldName(int fld) const
{
   return ctl->field_descr[fld-FIELD_OFF].name;
}


// Feldwerte
// =========

bool cwListElem::isNull(int fld) const
{
   char *status = (char*)this + ctl->field_descr[fld-FIELD_OFF].offset;
   return !!(*status & cwListCtl::sbmIsNull);
}

void cwListElem::setNull(int fld) const
{
   char *status = (char*)this + ctl->field_descr[fld-FIELD_OFF].offset;
   *status |= cwListCtl::sbmIsNull;
}

bool cwListElem::get(int fld, char *buf, int size) const
{
   if ( !__ECL_ASSERT1__(fld-FIELD_OFF >= 0 && fld-FIELD_OFF < ctl->field_count) )
      return false;

   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   if ( data[-1] & cwListCtl::sbmIsNull ) {
      strxcpy(buf, "", size);
      return false;
   }

   //TYPE type = getType();
   //if ( type == tDate && getFlags(fIsWeek) )
   //   type = tWeek;

   switch ( fd.type ) {

   case csQuery::tInt:
      {
         char temp[128];
         csBaseStorage::formatValue(temp, *((int*)data), fd.disp_width, fd.disp_prec, fd.disp_thsnd_sep, fd.disp_left_pad);
         strxcpy(buf, temp, size);
      }
      break;

   case csQuery::tDouble:
      {
         char temp[128];
         csBaseStorage::formatValue(temp, *((double*)data), fd.disp_width, fd.disp_prec, fd.disp_thsnd_sep, fd.disp_left_pad);
         strxcpy(buf, temp, size);
      }
      break;

   case csQuery::tTime:
      strxcpy(buf, ((cTime *)data)->getStr(), size);
      break;

   case csQuery::tDate:
      strxcpy(buf, ((cDate *)data)->getStr(), size);
      break;

   case csQuery::tWeek:
      strxcpy(buf, ((cDate *)data)->getWeekStr(), size);
      break;

   case csQuery::tChar:
      strxcpy(buf, Str(*data), size);
      break;

   case csQuery::tString:
      strxcpy(buf, (const char *)data, size);
      break;

   default:
      return false;

   }

   return true;
}

bool cwListElem::get(int fld, cString& buf) const
{
   if ( !__ECL_ASSERT1__(fld-FIELD_OFF >= 0 && fld-FIELD_OFF < ctl->field_count) )
      return false;

   char temp[2048];

   if ( get(fld, temp, sizeof temp) ) {
      buf = cString(temp);
      return true;
   } else {
      return false;
   }
}

bool cwListElem::get(int fld, csStorage *buf) const
{
   cString v;

   return buf != 0 && get(fld, v) ?
      buf->put(v)
    : false;
}

bool cwListElem::put(int fld, int buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {

   case csQuery::tInt:
      *((int *)data) = buf;
      break;

   case csQuery::tDouble:
      *((double *)data) = double(buf);
      break;

   case csQuery::tChar:
      if ( buf <= CHAR_MAX && buf >= CHAR_MIN ) {
         *data = char(buf);
      } else {
         rc = false;
      }
      break;

   case csQuery::tString:
      {
         char temp[128];
         csBaseStorage::formatValue(temp, buf, fd.disp_width, fd.disp_prec, fd.disp_thsnd_sep, fd.disp_left_pad);
         strxcpy(data, temp, fd.buffer_size);
      }
      break;

   default:
      rc = false;
      break;

   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, double buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {

   case csQuery::tInt:
      if ( buf <= INT_MAX && buf >= INT_MIN ) {
         *((int *)data) = int(buf);
      } else {
         rc = false;
      }
      break;

   case csQuery::tDouble:
      *((double *)data) = buf;
      break;

   case csQuery::tChar:
      if ( buf <= CHAR_MAX && buf >= CHAR_MIN ) {
         *data = char(buf);
      } else {
         rc = false;
      }
      break;

   case csQuery::tString:
      {
         char temp[128];
         csBaseStorage::formatValue(temp, buf, fd.disp_width, fd.disp_prec, fd.disp_thsnd_sep, fd.disp_left_pad);
         strxcpy(data, temp, fd.buffer_size);
      }
      break;

   default:
      rc = false;
      break;

   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, cTime buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {
   case csQuery::tTime:    *((cTime *)data) = buf; break;
   case csQuery::tString:  strxcpy(data, buf.getStr(), fd.buffer_size); break;
   default:                rc = false; break;
   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, cDate buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {
   case csQuery::tDate:    *((cDate *)data) = buf; break;
   case csQuery::tString:  strxcpy(data, buf.getStr(), fd.buffer_size); break;
   default:                rc = false; break;
   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, cDateTime buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {
   case csQuery::tDateTime:   *((cDateTime *)data) = buf; break;
   case csQuery::tString:     strxcpy(data, buf.getStr(), fd.buffer_size); break;
   default:                   rc = false; break;
   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, char buf)
{
   bool rc = true;
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   switch ( fd.type ) {
   case csQuery::tInt:     *((int *)data) = buf; break;
   case csQuery::tDouble:  *((double *)data) = buf; break;
   case csQuery::tChar:    *data = buf; break;
   case csQuery::tString:  strxcpy(data, Str(buf), fd.buffer_size); break;
   default:                rc = false; break;
   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, const char *buf)
{
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   if ( !buf || !*buf ) {
      data[-1] |= cwListCtl::sbmIsNull;
      return true;
   }

   bool rc = true;
   double temp;

   //TYPE type = getType();
   //if ( type == tDate && getFlags(fIsWeek) )
   //   type = tWeek;

   switch ( fd.type ) {

   case csQuery::tInt:
      if ( cString::convStr2Dbl(buf, temp) ) {
         *((int *)data) = (int)temp;
      } else {
         rc = false;
      }
      break;

   case csQuery::tDouble:
      if ( cString::convStr2Dbl(buf, temp) ) {
         *((double *)data) = temp;
      } else {
         rc = false;
      }
      break;

   case csQuery::tTime:
      *((cTime *)data) = cTime(buf);
      break;

   case csQuery::tDate:
      *((cDate *)data) = cDate(buf);
      break;

   case csQuery::tWeek:
      *((cDate *)data) = cDate(buf, true);
      break;

   case csQuery::tChar:
      *((char *)data) = buf[0];
      break;

   case csQuery::tString:
      strxcpy(data, buf, fd.buffer_size);
      break;

   default:
      rc = false;
      break;

   }

   if ( rc ) {
      data[-1] &= ~cwListCtl::sbmIsNull;
   } else {
      data[-1] |= cwListCtl::sbmIsNull;
   }

   return rc;
}

bool cwListElem::put(int fld, const csStorage *buf)
{
   if ( buf != 0 ) {
      switch ( buf->getType() ) {
      case csStorage::tInt:
         { int v; buf->get(v); return put(fld, v); }
      case csStorage::tDouble:
         { double v; buf->get(v); return put(fld, v); }
      case csStorage::tTime:
         { cTime v; buf->get(v); return put(fld, v); }
      case csStorage::tDate:
      case csStorage::tWeek:
         { cDate v; buf->get(v); return put(fld, v); }
      case csStorage::tDateTime:
         { cDateTime v; buf->get(v); return put(fld, v); }
      case csStorage::tChar:
         { char v; buf->get(v); return put(fld, v); }
      case csStorage::tString:
         { cString v; buf->get(v); return put(fld, v); }
      }
   }

   return false;
}

const csStorage * cwListElem::makeVar(int /*fld*/) const
{
   /*TBD:*/__ECL_ASSERT2__(0, ("cwListElem::makeVar not yet implemented"));
   /*DUMMY*/return new0 csVarInt();
}

csStorage * cwListElem::makeVar(int /*fld*/)
{
   /*TBD:*/__ECL_ASSERT2__(0, ("cwListElem::makeVar not yet implemented"));
   /*DUMMY*/return new0 csVarInt();
}

csStorage * cwListElem::makeCompatibleVar(int fld) const
{
   cwListCtl::FIELD_DESCR& fd = ctl->field_descr[fld-FIELD_OFF];
   char *data = (char*)this + fd.offset + 1;

   csStorage *store = 0;

   switch ( fd.type ) {

   case csQuery::tInt:
      store = new0 csVarInt(*((int*)data), fd.disp_width);
      break;

   case csQuery::tDouble:
      store = new0 csVarDouble(*((double*)data), fd.disp_width, fd.disp_prec);
      break;

   case csQuery::tTime:
      store = new0 csVarTime(*((cTime*)data));
      break;

   case csQuery::tDate:
      store = new0 csVarDate(*((cDate*)data));
      break;

   case csQuery::tDateTime:
      store = new0 csVarDateTime(*((cDateTime*)data));
      break;

   case csQuery::tWeek:
      store = new0 csVarDate(*((cDate*)data), csVarDate::fIsWeek);
      break;

   case csQuery::tChar:
      store = new0 csVarChar(*((char*)data));
      break;

   case csQuery::tString:
      {
         csVarString *var = new0 csVarString(fd.buffer_size);
         *var = (const char*)data;
         store = var;
      }
      break;

   }

   if ( store != 0 ) {
      if ( !fd.nullable )
         store->setFlags(csStorage::fNotNull);
      if ( fd.disp_left_pad )
         store->setFlags(csStorage::fLeftPad);
      if ( fd.disp_thsnd_sep )
         store->setFlags(csStorage::fThousandSep);
      store->setNull(isNull(fld));
   }

   return store;
}


// Ueberschriebene Events
// ======================

cString cwListElem::onGetSignature() const
{
   return ctl->signature_offset >= 0 ?
      (const char *)this + ctl->signature_offset
    : "cwListElem"; // Standard-Signatur, falls 'signature_offset' < 0
}

cString cwListElem::onGetKey() const
{
   const char *data = (const char*)this + ctl->field_descr[csQuery::fldKey-FIELD_OFF].offset + 1;
   return (data[-1] & cwListCtl::sbmIsNull) ? 0 : data;
}

cString cwListElem::onGetName() const
{
   return (const char*)this + ctl->field_descr[csQuery::fldName-FIELD_OFF].offset + 1;
}

cString cwListElem::onGetDescr() const
{
   return (const char*)this + ctl->field_descr[csQuery::fldDescr-FIELD_OFF].offset + 1;
}

int cwListElem::onGetBitmapId(BITMAP_STYLE /*bs*/) const
{
   return *((int*)((char*)this + ctl->field_descr[csQuery::fldIconID-FIELD_OFF].offset + 1));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwListCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwListCtl : public cwControl {
   ELO_DECLARE(cwListCtl,cwControl)
   friend class ccwListCtl;
   friend class cwListElem;

public:

   // Destruktor
   virtual ~cwListCtl();


   // Allgemeines
   // ===========

   // Array-Zugriffsoperator
   inline cwListElem * operator[](int idx) const
      { return onGetElemWithIndex(idx); }

   // Feld 'fld' als Element-Signatur benutzen
   void setSigOffField(int fld = csQuery::fldName);
   // User-Data (ab 'offset') fuer Element-Signatur setzen
   void setSigOffUserData(int offset = 0);

   // Standard-Aktionsbeschreibung einrichten
   void setupDefActionDescr(cEloActionDescription *new_action_descr);
   // Ausloesen des Events 'evtOperationExecuted'
   void callOperationEvent(cwListElem *elem, int event);

   // Versucht den Wert des Schluesselfeldes 'key_name' der zugrunde-
   // liegenden Query zu ermitteln, ohne dass ein Datensatz geladen
   // sein muss (oder 0 falls nicht ermittelbar)
   cString getKeyValue(cString key_name) const;


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwControl::wflUser,
      wflAutoRequery    = wflStart << 0,  // Automatisches Requery bei Refresh?
      wflQueryExecuted  = wflStart << 1,  // Query mindestens einmal ausgefuehrt?
      wflColumnsInit    = wflStart << 2,  // Spalten bereits angelegt?
      wflUserDataInit   = wflStart << 3,  // Benutzerdaten bereits angelegt?
      wflInSelectAll    = wflStart << 4,  // Wird waehrend doSelectAllElems gesetzt
      wflUser           = wflStart << 5   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsAutoRequery     = wsStart << 0,   // Automatisches Requery bei Refresh (Default)
      wsUser            = wsStart << 1    // Benutzerdefinierte Styles
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwControl::evtUser,
     evtSelectionChanging,             // (EVFUNC_P)  Selektion vor Aenderung
     evtSelectionChanged,              // (EVFUNC_P)  Selektion geaendert
     evtListElemSelected,              // (EVFUNC_P)  Listenelement ausgewaehlt
     evtAllListElemsRefreshed,         // (EVFUNC_I)  Refresh der gesamten Liste durchfuehrt
     evtSingleListElemRefreshed,       // (EVFUNC_PI) Refresh eines Einzelelementes durchgefuehrt
     evtNewListElemsInserted,          // (EVFUNC_PI) Einfuegen neuer Elemente durchgefuehrt
     evtBeginDrag,                     // (EVFUNC_PI) Beginn einer Dragoperation
     evtBeginEdit,                     // (EVFUNC_PI) Beginn einer Edit-Operation
     evtStoreEdit,                     // (EVFUNC_PI) Edit-Operation beendet: Speichern
     evtDiscardEdit,                   // (EVFUNC_PI) Edit-Operation beendet: Verwerfen
     evtOperationExecuted,             // (EVFUNC_PI) ELO-Operation ausgefuehrt
     evtUser                           // Benutzerdefinierte Events
   };


   // Anmerkung:
   // ----------
   // Durch insertNewListElems() werden alle durch die angegebene Query gelieferte
   // Elemente in das List-Control eingefuegt. Voraussetzung ist jedoch, dass
   // die Insert-Query die gleiche Spaltenstruktur liefert wie die Original-
   // Query (also sinnvollerweise durch Ableitung daraus entstanden ist) und
   // dass die neuen Elemente nicht bereits im List-Control vorhanden sind.
   // Startet den Refresh aller Elemente

   // Startet den Refresh der gesamten Liste
   bool refreshAllListElems();
   // Startet den Refresh eines einzelnen Elementes
   bool refreshListElem(cwListElem *elem);
   // Startet das nachtraegliche Einfuegen eines bestimmten neuen Elementes
   bool insertNewListElem(csQuery *query, cString key, cwListElem *before, cwListElem *parent = 0);
   // Startet das nachtraegliche Einfuegen neuer Elemente
   bool insertNewListElems(csQuery *query, cwListElem *before, cwListElem *parent = 0);


   // List-Control einrichten
   // =======================

   // Anmerkungen:
   //  - Die manuelle Einrichtung der Felder ist beim Fuellen des List-Controls
   //    ueber eine Query nicht noetig!
   //  - Nachdem das erste Element angefordert wurde (allocElem), darf die Ein-
   //    richtung der Felder nicht mehr geaendert werden!

   enum HALIGN { haDefault = 0, haLeft, haCenter, haRight };
   enum VALIGN { vaDefault = 0, vaTop, vaCenter, vaBottom };

   enum FIELD_INFO_FLAGS {
      fifIsNotNull         = 1 << 0,   // Gesetzt, wenn Feld kann keine Nullwerte enthalten kann
      fifIsReadOnly        = 1 << 1,   // Gesetzt, wenn Feld schreibgeschuetzt sein soll
      fifIsInvisible       = 1 << 2,   // Gesetzt, wenn Feld unsichtbar sein soll
      fifHasSeparator      = 1 << 3    // Gesetzt, wenn nach Feld eine vert. Linie eingef. werden soll
   };

   struct FIELD_INFO {
      cString           name;          // Feldname
      csQuery::TYPE     type;          // Datentyp
      int               flags;         // Flags (vgl. oben)
      int               buffer_size;   // Puffergroesse (nur bei tString relevant)
      int               width;         // Maximale Feldbreite [Zeichen]
      int               prec;          // Anzahl Nachkommastellen [Zeichen]
      HALIGN            halign;        // Horizontale Ausrichtung des Feldinhaltes
      VALIGN            valign;        // Vertikale Ausrichtung des Feldinhaltes
      int               row;           // Anzeigeposition: Zeile (-1 falls gleiche Zeile wie voriges Feld)
      int               col;           // Anzeigeposition: Spalte (-1 falls naechste Spalte)
      int               join_rows;     // Zellenverbindung senkrecht: Anzahl weiterer Felder (0 = Default)
      int               join_cols;     // Zellenverbindung waagrecht: Anzahl weiterer Felder (0 = Default)
      cString           title;         // Titel-Text
      HALIGN            title_halign;  // Horizontale Ausrichtung des Spaltentitels
      VALIGN            title_valign;  // Vertikale Ausrichtung des Spaltentitels
   };

   // 1. List-Control (neu) einrichten, Anzahl Felder und Zeilen pro Datensatz setzen
   void resetListCtl(int field_count, int row_count = 1);
   // 2.1 Feld 'fld' einrichten (Muss fuer jedes Feld einmal aufgerufen werden!)
   void setupField(int fld, const FIELD_INFO& field_info);
   // 2.2 Feld 'fld' als String-Feld einrichten (Alternative zu 2.1)
   void setupField(int fld, cString name, cString title, int flags, int buffer_size, int width = -1);
   // 2.3 Feld 'fld' als Zahlen-Feld einrichten (Alternative zu 2.1)
   void setupField(int fld, cString name, cString title, csQuery::TYPE type, int flags, int width, int prec = 1);
   // 3. Konfiguration des List-Controls uebernehmen
   void setupListConfig(int key_len = 16, int name_len = 64, int descr_len = -1);


   // Spalten
   // =======

   // Anzahl Spalten ermitteln
   int getColumnCount() const;
   // Anzahl Zeilen (pro Datensatz) ermitteln
   int getRowCount() const;
   // Anzahl verbundener Zellen waagrecht ermitteln
   int getJoinColumns(int fld) const;
   // Anzahl verbundener Zellen senkrecht ermitteln
   int getJoinRows(int fld) const;
   // Feld ermitteln, das in Spalte 'col' angezeigt wird
   int getFieldFromColumn(int col, int row = 0) const;
   // Spalte ermitteln, in der Feld 'fld' angezeigt wird (-1 falls nicht angezeigt)
   int getColumnFromField(int fld) const;
   // Zeile ermitteln, in der Feld 'fld' angezeigt wird (-1 falls nicht angezeigt)
   int getRowFromField(int fld) const;


   // Elementverwaltung
   // =================

   // Einfache Erfragefunktionen
   // --------------------------

   // Erstes Element der Liste
   inline cwListElem *getFirstElem() const
      { return anchor_head; }
   // Letztes Element der Liste
   inline cwListElem *getLastElem() const
      { return anchor_tail; }
   // Element vor Referenzelement
   inline cwListElem *getPrevElem(cwListElem *elem) const
      { return elem ? elem->prev : anchor_tail; }
   // Element nach Referenzelement
   inline cwListElem *getNextElem(cwListElem *elem) const
      { return elem ? elem->next : anchor_head; }
   // Erstes Kindelement des Referenzelementes
   inline cwListElem *getFirstChildElem(cwListElem *elem) const
      { return elem ? elem->head : anchor_head; }
   // Letztes Kindelement des Referenzelementes
   inline cwListElem *getLastChildElem(cwListElem *elem) const
      { return elem ? elem->tail : anchor_tail; }
   // Elternelement des Referenzelementes
   inline cwListElem *getParentElem(cwListElem *elem) const
      { return elem ? elem->parent : 0; }

   // Element ueber Index erfragen
   inline cwListElem *getElemWithIndex(int idx) const
      { return onGetElemWithIndex(idx); }

   // Liefert die Abfrage, die das Element erzeugt hat (bzw. die Abfrage,
   // die die Kinder des Elementes erzeugt, wenn sub_query = true)
   inline csQuery *getQueryOfElem(const cwListElem *elem, bool sub_query = false) const
      { return onGetQueryOfElem(elem, sub_query); }


   // Verkettung
   // ----------

   // Ist Element in eine Liste eingekettet?
   inline bool isElemInserted(cwListElem *elem) const
      { return elem->isLinked() || elem->parent || anchor_head == elem; }
   // Ist Element 'elem' ein Kindelement?
   inline bool isElemChild(cwListElem *elem) const
      { return elem->isChild(); }
   // Hat Element 'elem' Kindelemente?
   inline bool hasElemChilds(cwListElem *elem) const
      { return elem->hasChilds(); }


   // Komplexere Erfragefunktionen
   // ----------------------------

   // Anzahl der selektierten Elemente ermitteln
   inline int getSelectedElemCount(bool walk = false) const
      { return onGetSelectedElemCount(walk); }
   // Selektierte Elemente ermitteln
   inline cwListElem *getSelectedElem(cwListElem *elem = 0, bool walk = false) const
      { return onGetSelectedElem(elem, walk); }
   // Element ueber Schluessel ermitteln
   inline cwListElem *getElemWithKey(cString key, cwListElem *parent = 0, bool walk = false) const
      { return onGetElemWithKey(key, parent, walk); }
   // Zaehlt Elemente von vorne her durch
   inline int getElemCountFromBegin(cwListElem *elem) const
      { return onGetElemCountFromBegin(elem); }
   // Zaehlt Elemente von hinten her durch
   inline int getElemCountFromEnd(cwListElem *elem) const
      { return onGetElemCountFromEnd(elem); }


   // Selektion
   // ---------

   // Einzelnes Element selektieren
   bool selectElem(cwListElem *elem, bool sel = true);
   // Einzelnes Element deselektieren
   bool deselectElem(cwListElem *elem);
   // Alle Elemente selektieren
   bool selectAllElems(cwListElem *parent = 0, bool walk = false);
   // Alle Elemente deselektieren
   bool deselectAllElems(cwListElem *parent = 0, bool walk = false);


   // Cursor
   // ------

   // Element mit Cursor erfragen
   inline cwListElem *getCursoredElem() const
      { return onGetCursoredElem(); }
   // Cursor auf Element setzen
   inline bool setCursoredElem(cwListElem *elem)
      { return onSetCursoredElem(elem); }


   // Sichtbarkeit
   // ------------

   // Sicherstellen, dass Element 'elem' (wenigstens teilweise) sichtbar ist
   inline bool ensureElemVisible(cwListElem *elem, bool partial_ok = true)
      { return onEnsureElemVisible(elem, partial_ok); }
   // Sicherstellen, dass Feld 'fld' (wenigstens teilweise) sichtbar ist
   inline bool ensureFieldVisible(int fld, bool partial_ok = true)
      { return onEnsureFieldVisible(fld, partial_ok); }


   // Element erzeugen
   // ----------------

   // Neues Element erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(const cEloElementDescription *elem_descr = 0);
   // Neues Element ueber Query erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(csQuery *query);
   // Neues Element ueber Defaultfelder erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(cString key, cString name, cString descr = cString(),
                         const cEloElementDescription *elem_descr = 0);


   // Einfuegen/Loeschen
   // ------------------

   // Am Anfang der Liste einfuegen
   bool insertElemAtBegin(cwListElem *new_elem, cwListElem *parent = 0, bool invd = false);
   // Am Ende der Liste einfuegen
   bool insertElemAtEnd(cwListElem *new_elem, cwListElem *parent = 0, bool invd = false);
   // Vor Referenzelement einfuegen
   bool insertElemBefore(cwListElem *new_elem, cwListElem *ref_elem = 0, cwListElem *parent = 0, bool invd = false);
   // Nach Referenzelement einfuegen
   bool insertElemAfter(cwListElem *new_elem, cwListElem *ref_elem = 0, cwListElem *parent = 0, bool invd = false);
   // Element aus Liste ausklinken (ohne loeschen)
   bool removeElem(cwListElem *elem, bool invd = false);
   // Alle Elemente unterhalb von 'parent' aus Liste ausklinken (ohne loeschen)
   bool removeAllElems(cwListElem *parent = 0, bool invd = false);
   // Element ausklinken und loeschen
   bool deleteElem(cwListElem *elem, bool invd = false);
   // Alle Elemente unterhalb von 'parent' ausklinken und loeschen
   bool deleteAllElems(cwListElem *parent = 0, bool invd = false);


   // Aufzaehlung
   // -----------

   // Prototyp fuer Callback-Funktionen von doWithAllElems()
   typedef bool (*ENUM_ELEM_FUNC)(cwListCtl *list, cwListElem *elem, void *data);

   // Ruft fuer jedes Element eine Funktion func auf
   bool doWithAllElems(ENUM_ELEM_FUNC func, void *data, cwListElem *parent = 0, bool walk = false);


   // Editieren
   // ---------

   // Edit-Operation fuer Feld 'fld' von Listenelement 'elem' beginnnen
   bool beginEdit(cwListElem *elem, int fld);
   // Edit-Operation beenden (oder abbrechen)
   void endEdit(bool cancel = false);
   // Rechteck des Edit-Controls fuer Feld 'fld' von Element 'elem' ermitteln
   cdRect getEditRect(cwListElem *elem, int fld) const;

   // Aktuelles Control ermitteln, das zur Bearbeitung benutzt wird (oder 0)
   inline cwControl *getEditCtl() const
      { return edit_ctl; }
   // Aktuell von Edit bearbeitetes Listenelement ermitteln (oder 0)
   inline cwListElem *getEditElem() const
      { return edit_elem; }
   // Aktuell von Edit bearbeitetes Listenfeld ermitteln (oder 0)
   inline int getEditField() const
      { return edit_fld; }


protected:

   // Ueberschriebene Events
   // ======================

   // Abbruch mit Speichern erlauben?
   bool onAllowStore();
   // Abbruch ohne Speichern erlauben?
   bool onAllowDiscard();
   // Schliessen des Fensters erlauben?
   bool onAllowClose(cwWindow *notify);

   // Inhalt refreshen (false -> Abbruch)
   bool onRefresh();
   // Wird aufgerufen, wenn sich das gebundene Datenobjekt geaendert hat
   void onEventModified();

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   bool onCommandUI(cwCmdUI& cmd);

   // Wird aufgerufen, um zu erfragen, ob eine ELO-Element-Selektion moeglich ist
   bool onHasWindowElemSelection() const;
   // Wird aufgerufen, um die aktuelle ELO-Element-Selektion zu ermitteln
   bool onUpdateWindowElemSelection(cEloSelection& selection) const;
   // Wird aufgerufen, um den Zeiger auf ein aktuelles ELO-Selektionsobjekt zu ermitteln
   cEloSelection *onGetWindowElemSelection();
   // Wird aufgerufen, um den Zeiger auf die ELO-Aktionsbeschreibung zu ermitteln
   cEloActionDescription *onGetWindowActionDescription(const cEloSelection *selection) const;

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);
   // Abfrage des Controls erneut durchfuehren
   bool onRequeryCtl(csQuery *query);
   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


   // Zusaetzliche Events
   // ===================

   // Wird aufgrufen beim Versuch, das Fenster waehrend der Abfrage zu schliessen
   virtual bool onErrorInQuery();

   // Wird aufgerufen, um den Beginn einer Drag-Operation bekanntzugeben
   virtual void onBeginDrag(cwListElem *elem, int mouse_button);
   // Wird aufgerufen, um den Beginn einer Edit-Operation bekanntzugeben
   virtual bool onBeginEdit(cwListElem *elem, int fld);
   // Wird aufgerufen, um das Ende einer Edit-Operation bekanntzugeben
   virtual bool onEndEdit(cwListElem *elem, int fld, cString text);
   // Wird aufgerufen, um das Rechteck fuer das Edit-Control zu ermitteln
   virtual cdRect onGetEditRect(cwListElem *elem, int fld) const;
   // Wird aufgerufen, um das Edit-Control zu erzeugen
   virtual cwControl *onMakeEditCtl(cwListElem *elem, int fld, const cdRect& rect);

   // Wird aufgerufen, bevor sich die Selektion aendert (true = Aenderung zulassen)
   virtual bool onSelectionChanging(cwListElem *elem);
   // Wird aufgerufen, wenn ein Element selektiert wurde
   virtual void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   virtual void onListElemSelected(cwListElem *elem);

   // Wird aufgerufen, um den Default-Text bei NULL-Werten zu ermitteln
   virtual cString onGetNullText();

   // Wird aufgerufen, um ein Element ueber dessen Schluessel zu ermitteln
   virtual cwListElem *onGetElemWithKey(cString key, cwListElem *parent, bool walk) const;
   // Wird aufgerufen, um ein Element ueber dessen Index zu ermitteln
   virtual cwListElem *onGetElemWithIndex(int idx) const;
   // Wird aufgerufen, um die Elemente von vorne her durchzuzaehlen
   virtual int onGetElemCountFromBegin(cwListElem *elem) const;
   // Wird aufgerufen, um die Elemente von hinten her durchzuzaehlen
   virtual int onGetElemCountFromEnd(cwListElem *elem) const;

   // Wird aufgrufen, um die Anzahl der selektierten Elemente zu ermitteln
   virtual int onGetSelectedElemCount(bool walk) const;
   // Wird aufgerufen, um die selektierten Elemente zu ermitteln
   virtual cwListElem *onGetSelectedElem(cwListElem *elem, bool walk) const = 0;
   // Wird aufgerufen, um die Selektion fuer ein einzelnes Element zu aendern
   virtual bool onSelectElem(cwListElem *elem, bool sel) = 0;
   // Wird aufgerufen, um die Selektion fuer alle Elemente zu aendern
   virtual bool onSelectAllElems(bool sel, cwListElem *parent, bool walk);

   // Wird aufgerufen, um das Element mit Cursor zu erfragen
   virtual cwListElem *onGetCursoredElem() const = 0;
   // Wird aufgerufen, um den Cursor auf ein Element zu setzen
   virtual bool onSetCursoredElem(cwListElem *elem) = 0;

   // Wird aufgerufen, um sicherzustellen, dass Element 'elem' sichtbar ist
   virtual bool onEnsureElemVisible(cwListElem *elem, bool partial_ok);
   // Wird aufgerufen, um sicherzustellen, dass Feld 'fld' sichtbar ist
   virtual bool onEnsureFieldVisible(int fld, bool partial_ok);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   virtual bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd) = 0;
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   virtual bool onRemoveElem(cwListElem *elem, bool invd) = 0;
   // Wird aufgerufen, um alle Elemente unterhalb von 'parent' von der Anzeige zu entfernen
   virtual bool onRemoveAllElems(cwListElem *parent, bool invd) = 0;

   // Wird aufgerufen, bevor die Abfrage gestartet wird
   virtual bool onQueryPreStart(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   virtual bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz verfuegbar ist, um ihn zur Liste hinzuzufuegen
   virtual bool onQueryData(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   virtual bool onQueryEnded(csQuery *query);
   // Wird aufgerufen, nachdem die Abfrage beendet wurde
   virtual void onQueryPostEnd(csQuery *query);

   // Wird aufgerufen, bevor die Einzelabfrage gestartet wird
   virtual bool onQuery1PreStart(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn die Einzelabfrage gestartet wurde
   virtual bool onQuery1Started(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einzelabfrage verfuegbar ist
   virtual bool onQuery1Data(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn die Einzelabfrage beendet ist
   virtual bool onQuery1Ended(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, nachdem die Einzelabfrage beendet wurde
   virtual void onQuery1PostEnd(cwListElem *elem, csQuery *query);

   // Wird aufgerufen, bevor die Einfuegeabfrage gestartet wird
   virtual bool onInsQueryPreStart(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn die Einfuegeabfrage gestartet wurde
   virtual bool onInsQueryStarted(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einfuegeabfrage verfuegbar ist
   virtual bool onInsQueryData(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn die Einfuegeabfrage beendet ist
   virtual bool onInsQueryEnded(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, nachdem die Einfuegeabfrage beendet wurde
   virtual void onInsQueryPostEnd(cwListElem *before, cwListElem *parent, csQuery *query);

   // Wird aufgerufen, wenn ein Element des Controls erzeugt wird
   virtual void onCreatingElement(cwListElem *elem);
   // Wird aufgerufen, wenn ein Element des Controls geloescht wird
   virtual void onDeletingElement(cwListElem *elem);

   // Wird aufgerufen, um die Abfrage zu erfragen, die das Element erzeugt hat
   virtual csQuery *onGetQueryOfElem(const cwListElem *elem, bool sub_query) const;

   struct SETUP_ROWCOL_INFO {
      const csQuery *query;      // Aktuelle Abfrage
      int old_row_count;         // Bisherige Zeilenzahl (pro Datensatz)
      int new_row_count;         // Neue Zeilenzahl (pro Datensatz)
      int old_column_count;      // Bisherige Spaltenzahl
      int new_column_count;      // Neue Spaltenzahl
   };

   struct FIELD_DESCR;
   struct SETUP_FIELD_INFO {
      const csQuery *query;      // Aktuelle Abfrage
      const FIELD_DESCR *descr;  // Beschreibung des aktuellen Feldes
      int disp_row;              // Zeile, in der das Feld angezeigt werden soll
      int disp_col;              // Spalte, in der das Feld angezeigt werden soll
      int join_x;                // Anzahl zu verbindender Zellen waagrecht
      int join_y;                // Anzahl zu verbindender Zellen senkrecht
      bool add;                  // Feld hinzufuegen?
   };

   // Wird aufgerufen, um die Anzahl zusaetzlich benoetigter Bytes im Element zu erfragen
   virtual int onGetAddByteCount() const;
   // Wird aufgerufen, um zu erfragen, ob mehrere Zeilen pro Datensatz unterstuetzt werden
   virtual bool onAllowsMultipleRows() const;
   // Wird aufgerufen, wenn sich die Spalten- oder Zeilenzahl (pro DS) geaendert hat
   virtual void onSetupRowCol(const SETUP_ROWCOL_INFO& info);
   // Wird aufgerufen, um in Spalte das Feld 'fld' zur Anzeige vorzubereiten
   virtual void onSetupField(int fld, const SETUP_FIELD_INFO& info);
   // Wird einmalig nach der Einrichtung der benutzerspezifischen Daten aufgerufen
   virtual void onPostUserDataInit();

   enum ELEM_ATTR {
      eatFontBold,               // Schriftart-Attribut "BOLD" geaendert
      eatColorFg,                // Farb-Attribut "Vordergrundfarbe" geaendert
      eatColorBg                 // Farb-Attribut "Hintergrundfarbe" geaendert
   };

   // Wird aufgerufen, wenn das Schriftart-Attribut eines Elementes aendert
   virtual void onElemAttrChanged(cwListElem *elem, ELEM_ATTR attr);


   // Verzoegerte Ausfuehrung
   // =======================

   enum  { ediStart = cwControl::ediUser,
      ediEndEdit,          // Verzoegerte Ausfuehrung von endEdit()
      ediNavigateEdit,     // Verzoegerte Ausfuehrung von endEdit(true) und Navigation
      ediUse               // ab hier Erweiterungen
   };

   // Verzoegertes Ausfuehren einer Operation
   void onExecDelayed(int id, void *data);


protected:

   // Interner Konstruktor
   cwListCtl(void *wnd);


   // Elementbeschreibung
   // ===================

   enum STATUSBYTE {
      sbmIsNull      = 0x01   // Das Feld hat den NULL-Zustand
   };

   struct FIELD_DESCR {
      int offset;                   // Offset (auf Statusbyte) in cwListElem
      int buffer_size;              // Groesse des Feldes (in Bytes)
      int disp_column;              // Feld wird angezeigt in Spalte 'disp_column'
      int disp_row;                 // Feld wird angezeigt in Zeile 'disp_row'
      int join_x;                   // Die naechsten 'join_x' Spalten verbinden
      int join_y;                   // Die naechsten 'join_y' Zeilen verbinden
      int disp_width;               // Maximale Anzeigebreite
      int disp_prec;                // Maximale Anzahl Nachkommastellen
      bool disp_thsnd_sep;          // Tausender-Separatoren anzeigen?
      bool disp_left_pad;           // Zahlen links mit 0en auffuellen?
      bool nullable;                // Darf das Feld den NULL-Zustand annehmen?
      bool editable;                // Darf das Feld vom Anwender bearbeitet werden?
      csQuery::HALIGN halign;       // Horizontale Ausrichtung des Feldinhaltes
      csQuery::VALIGN valign;       // Vertikale Ausrichtung des Feldinhaltes
      csQuery::HALIGN title_halign; // Horizontale Ausrichtung des Spaltentitels
      csQuery::VALIGN title_valign; // Vertikale Ausrichtung des Spaltentitels
      csQuery::TYPE type;           // Typ des Feldes (vgl. csQuery)
      cString title;                // Titel-Text (vgl. csQuery)
      cString name;                 // Feldname (vgl. csQuery)
   };

   // Alle Elemente freigeben
   void cleanup();
   // Alle Kind-Elemente von 'parent' freigeben
   void cleanup(cwListElem *parent);
   // Ausfuehren von 'onSelectElem'
   bool doSelectElem(cwListElem *elem, bool sel);
   // Ausfuehren von 'onSelectAllElems'
   bool doSelectAllElems(bool sel, cwListElem *parent, bool walk);


private:

   // Abfrage
   // =======

   cwListElem *ins_before;    // insertNewListElems(): Referenz-Element
   cwListElem *ins_parent;    // insertNewListElems(): Eltern-Element
   cwListElem *rfs_elem;      // refreshListElem(): Betroffenes Element

   // Wird von refreshAllListElems() zum Fuellen der Liste aufgerufen
   int onRefreshQuery(void *p1, int p2);
   // Wird von refreshListElem() zum Element-Refresh aufgerufen
   int onRefreshQuery1(void *p1, int p2);
   // Wird zum insertNewListElems() zum Einfuegen eines neuen Elementes aufgerufen
   int onInsertQuery(void *p1, int p2);


   // Elementverkettung
   // =================

   cwListElem *anchor_head;   // Erstes Element der Element-Liste
   cwListElem *anchor_tail;   // Letztes Element der Element-Liste


   // Elementbeschreibung
   // ===================

   int field_count;           // Anzahl Felder (incl. Default-Felder, d.h. mind. 4)
   int field_data_size;       // Gesamtgroesse Datenfelder = field_count * (buffer_size+1)
   FIELD_DESCR *field_descr;  // Array mit 'field_count' Feldbeschreibungen

   int user_data_size;        // Groesse der benutzerspezifischen Zusatzinformationen im Element
   int user_data_offset;      // Offset in die benutzerspezifischen Daten des Elementes
   int signature_offset;      // Offset des Textes, der als Element-Signatur verwendet wird

   int column_count;          // Anzahl Spalten (d.h. sichtbare Spalten)
   int row_count;             // Anzahl Zeilen (pro Datensatz)
   int old_column_count;      // Fuer setupListConfig: Bisherige Spaltenzahl
   int old_row_count;         // Fuer setupListConfig: Bisherige Zeilenzahl pro Datensatz
   int *field_column;         // Zuordnung: Spalte 'idx' zeigt Feld 'fld' an

   char *selected_elems;      // Key-Werte der selektierten Elemente (fuer Requery)
   int selected_count;        // Anzahl selektierter Elemente (fuer Requery)

   // Benutzerspezifische Zusatzinformationen einrichten
   bool setupUserData(int new_user_data_size);
   // Spalteninformationen aus der Query uebernehmen
   void setupColumns(csQuery *query);
   // Aktuelle Selektion speichern (vor Requery)
   void saveSelection();
   // Gespeicherte Selektion wieder herstellen (nach Requery)
   void restoreSelection();


   // Aktionsbeschreibung
   // ===================

   cEloActionDescription *action_descr;   // Default-Aktionsbeschreibung


   // Zellen-Editor
   // =============

   cwControl *edit_ctl;       // Zeiger auf aktuelles Edit-Control
   cwListElem *edit_elem;     // Momentan durch Edit bearbeitetes Element...
   int edit_fld;              // ... und Feld

   // Wird aufgerufen, wenn im Edit-Control die ENTER-Taste gedrueckt wird
   void onEvtEnterKey();
   // Wird aufgerufen, wenn im Edit-Control die ESC-Taste gedrueckt wird
   void onEvtEscKey();
   // Wird aufgerufen, wenn im Edit-Control eine Navigationstaste gedrueckt wird
   void onEvtNavKey(int p1);

};

#endif /*__INTERFACE__*/


// Implementierung cwListCtl
// ===========================================================================

cwListCtl::cwListCtl(void *wnd) :
   cwControl(wnd)
{
   setFlags(wflAutoRequery); // Default: AutoRequery an

   anchor_head = 0;
   anchor_tail = 0;

   ins_before = 0;
   ins_parent = 0;
   rfs_elem = 0;

   field_count = 0;
   field_data_size = 0;
   field_descr = 0;

   user_data_size = 0;
   user_data_offset = 0;
   signature_offset = -1;

   column_count = old_column_count = 0;
   row_count = old_row_count = 0;
   field_column = 0;

   selected_elems = 0;
   selected_count = 0;

   action_descr = 0;

   edit_ctl = 0;
   edit_elem = 0;
   edit_fld = 0;
}

cwListCtl::~cwListCtl()
{
   // Alle Elemente loeschen. Es wird vorausgesetzt, dass die abgeleiteten
   // Klassen ihren Teil der Listenverwaltung selbst im Destruktor durchfuehren
   cleanup();

   delete[] field_descr;
   delete[] field_column;
   delete[] selected_elems;
}

// Allgemeines
// ===========

void cwListCtl::setSigOffField(int fld)
{
   if ( fld >= csQuery::fldDescr && fld < field_count + FIELD_OFF )
      signature_offset = field_descr[fld-FIELD_OFF].offset;
}

void cwListCtl::setSigOffUserData(int offset)
{
   if ( offset > 0 && offset < user_data_size )
      signature_offset = user_data_offset + offset;
}

void cwListCtl::setupDefActionDescr(cEloActionDescription *new_action_descr)
{
   action_descr = new_action_descr;
}

void cwListCtl::callOperationEvent(cwListElem *elem, int event)
{
   callEvent(evtOperationExecuted, elem, event);
}

cString cwListCtl::getKeyValue(cString key_name) const
{
   csQuery *query = getQuery();
   return query != 0 ?
      query->getKeyValue(key_name)
    : 0;
}

void cwListCtl::cleanup()
{
   cwListElem *next, *elem = anchor_head;

   while ( elem ) {
      next = elem->next;
      cleanup(elem);
      delete elem;
      elem = next;
   }

   anchor_head = anchor_tail = 0;
}

void cwListCtl::cleanup(cwListElem *parent)
{
   cwListElem *next, *elem = parent->getFirstChild();

   while ( elem ) {
      next = elem->next;
      cleanup(elem);
      delete elem;
      elem = next;
   }

   parent->head = parent->tail = 0;
}


// Selektion
// ---------

bool cwListCtl::selectElem(cwListElem *elem, bool sel)
{
   bool ok;

   if ( !elem ) {
      ok = sel ? selectAllElems() : deselectAllElems();
   } else {
      ok = doSelectElem(elem, sel);
   }

   if ( ok && hasStorage() && !isStorageReadOnly() ) {
      if ( !sel )
         elem = getSelectedElem();
      if ( elem == 0 ) {
         setStorageNull();
      } else {
         putStorageVal(elem->getKey());
      }
   }

   return ok;
}

bool cwListCtl::deselectElem(cwListElem *elem)
{
   if ( !elem ) {
      return deselectAllElems();
   } else {
      return doSelectElem(elem, false);
   }
}

bool cwListCtl::selectAllElems(cwListElem *parent, bool walk)
{
   return onSelectAllElems(true, parent, walk);
}

bool cwListCtl::deselectAllElems(cwListElem *parent, bool walk)
{
   return onSelectAllElems(false, parent, walk);
}

bool cwListCtl::doSelectElem(cwListElem *elem, bool sel)
{
   // Jeder explizite Aufruf von 'onSelectElem' sollte ueber
   // diese Funktion laufen.

   bool rc = onSelectElem(elem, sel);

   if ( !getFlags(wflInSelectAll) )
      updateWindowElemSelection();

   return rc;
}

bool cwListCtl::doSelectAllElems(bool sel, cwListElem *parent, bool walk)
{
   // Jeder explizite Aufruf von 'onSelectAllElems' sollte ueber
   // diese Funktion laufen.

   setFlags(wflInSelectAll, true);

   bool rc = onSelectAllElems(sel, parent, walk);

   setFlags(wflInSelectAll, false);

   updateWindowElemSelection();

   return rc;
}


// Element erzeugen
// ----------------

cwListElem * cwListCtl::allocElem(const cEloElementDescription *elem_descr)
{
   return new1(this) cwListElem(elem_descr);
}

cwListElem * cwListCtl::allocElem(csQuery *query)
{
   return new1(this) cwListElem(query);
}

cwListElem * cwListCtl::allocElem(cString key, cString name, cString descr, const cEloElementDescription *elem_descr)
{
   return new1(this) cwListElem(key, name, descr, elem_descr);
}


// Einfuegen/Loeschen
// ------------------

bool cwListCtl::insertElemAtBegin(cwListElem *new_elem, cwListElem *parent, bool invd)
{
   if ( !new_elem )
      return false;

   if ( isElemInserted(new_elem) )
      removeElem(new_elem, invd);

   if ( parent ) {
      if ( (new_elem->next = parent->head) != NULL )
         parent->head->prev = new_elem;
      new_elem->prev = NULL;
      parent->head = new_elem;
      if ( !parent->tail )
         parent->tail = new_elem;
   } else {
      if ( (new_elem->next = anchor_head) != NULL )
         anchor_head->prev = new_elem;
      new_elem->prev = NULL;
      anchor_head = new_elem;
      if ( !anchor_tail )
         anchor_tail = new_elem;
   }

   new_elem->parent = parent;
   new_elem->ctl = this;

   return onInsertElemAt(1, 0, new_elem, parent, invd);
}

bool cwListCtl::insertElemAtEnd(cwListElem *new_elem, cwListElem *parent, bool invd)
{
   if ( !new_elem )
      return false;

   if ( isElemInserted(new_elem) )
      removeElem(new_elem, invd);

   if ( parent ) {
      if ( (new_elem->prev = parent->tail) != NULL )
         parent->tail->next = new_elem;
      new_elem->next = NULL;
      parent->tail = new_elem;
      if ( !parent->head )
         parent->head = new_elem;
   } else {
      if ( (new_elem->prev = anchor_tail) != NULL )
         anchor_tail->next = new_elem;
      new_elem->next = NULL;
      anchor_tail = new_elem;
      if ( !anchor_head )
         anchor_head = new_elem;
   }

   new_elem->parent = parent;
   new_elem->ctl = this;

   return onInsertElemAt(-1, 0, new_elem, parent, invd);
}

bool cwListCtl::insertElemBefore(cwListElem *new_elem, cwListElem *ref_elem, cwListElem *parent, bool invd)
{
   if ( !new_elem )
      return false;

   if ( isElemInserted(new_elem) )
      removeElem(new_elem, invd);

   if ( ref_elem ) {
      new_elem->prev = ref_elem->prev;
      new_elem->next = ref_elem;
      ref_elem->prev = new_elem;
      if ( new_elem->prev ) {
         new_elem->prev->next = new_elem;
      } else if ( parent ) {
         parent->head = new_elem;
      } else {
         anchor_head = new_elem;
      }
   } else if ( parent ) {
      if ( (new_elem->prev = parent->tail) != NULL )
         parent->tail->next = new_elem;
      new_elem->next = NULL;
      parent->tail = new_elem;
      if ( !parent->head )
         parent->head = new_elem;
   } else {
      if ( (new_elem->prev = anchor_tail) != NULL )
         anchor_tail->next = new_elem;
      new_elem->next = NULL;
      anchor_tail = new_elem;
      if ( !anchor_head )
         anchor_head = new_elem;
   }

   new_elem->parent = parent;
   new_elem->ctl = this;

   return onInsertElemAt(-1, ref_elem, new_elem, parent, invd);
}

bool cwListCtl::insertElemAfter(cwListElem *new_elem, cwListElem *ref_elem, cwListElem *parent, bool invd)
{
   if ( !new_elem )
      return false;

   if ( isElemInserted(new_elem) )
      removeElem(new_elem, invd);

   if ( ref_elem ) {
      new_elem->prev = ref_elem;
      new_elem->next = ref_elem->next;
      ref_elem->next = new_elem;
      if ( new_elem->next ) {
         new_elem->next->prev = new_elem;
      } else if ( parent ) {
         parent->tail = new_elem;
      } else {
         anchor_tail = new_elem;
      }
   } else if ( parent ) {
      if ( (new_elem->next = parent->head) != NULL )
         parent->head->prev = new_elem;
      new_elem->prev = NULL;
      parent->head = new_elem;
      if ( !parent->tail )
         parent->tail = new_elem;
   } else {
      if ( (new_elem->next = anchor_head) != NULL )
         anchor_head->prev = new_elem;
      new_elem->prev = NULL;
      anchor_head = new_elem;
      if ( !anchor_tail )
         anchor_tail = new_elem;
   }

   new_elem->parent = parent;
   new_elem->ctl = this;

   return onInsertElemAt(1, ref_elem, new_elem, parent, invd);
}

bool cwListCtl::removeElem(cwListElem *elem, bool invd)
{
   if ( !elem )
      return false;

   if ( !isElemInserted(elem) )
      return true;

   bool rc = onRemoveElem(elem, invd);

   if ( elem->prev ) {
      elem->prev->next = elem->next;
   } else if ( elem->parent ) {
      elem->parent->head = elem->next;
   } else {
      anchor_head = elem->next;
   }

   if ( elem->next ) {
      elem->next->prev = elem->prev;
   } else if ( elem->parent ) {
      elem->parent->tail = elem->prev;
   } else {
      anchor_tail = elem->prev;
   }

   elem->parent = elem->prev = elem->next = NULL;
   elem->ctl = 0;

   updateWindowElemSelection();

   return rc;
}

bool cwListCtl::removeAllElems(cwListElem *parent, bool invd)
{
   cwListElem *elem = parent ? parent->head : anchor_head;
   cwListElem *next;

   while ( elem ) {
      next = elem->next;
      elem->next = elem->prev = NULL;
      elem->ctl = 0;
      elem = next;
   }

   if ( parent ) {
      parent->head = parent->tail = NULL;
   } else {
      anchor_head = anchor_tail = NULL;
   }

   bool rc = onRemoveAllElems(parent, invd);

   updateWindowElemSelection();

   return rc;
}

bool cwListCtl::deleteElem(cwListElem *elem, bool invd)
{
   if ( !elem )
      return false;

   // bool rc = onRemoveElem(elem, invd);

   while ( elem->hasChilds() )
      if ( !deleteElem(elem->head, invd) )
         return false;

   if ( !removeElem(elem, invd) )
      return false;

   delete elem;
   return true; //rc;
}

bool cwListCtl::deleteAllElems(cwListElem *parent, bool invd)
{
   cwListElem *elem = parent ? parent->head : anchor_head;
   cwListElem *next;

   #ifdef __DEBUG_ALLOC__
      _heap_check();
   #endif

   bool rc = onRemoveAllElems(parent, invd);

   while ( elem ) {
      next = elem->next;
      #if __DEBUG_ALLOC__
         if ( elem->head == (cwListElem *)0x89abcdef ) {
            DbgError("*** FATAL: DeleteAll wants to delete elem already deleted!");
            break;
         }
      #endif
      cleanup(elem);
      delete elem;
      elem = next;
   }

   if ( parent ) {
      parent->head = parent->tail = NULL;
   } else {
      anchor_head = anchor_tail = NULL;
   }

   updateWindowElemSelection();

   return rc;
}


// Refresh aller Elemente
// ----------------------

// Der Event evtAllListElemsRefreshed wird nach Abschluss des Refreshs
// mit folgenden Parametern aufgerufen:
//
//  - Param1 (int): Ok-Wert der Refresh-Verarbeitung

bool cwListCtl::refreshAllListElems()
{
   if ( inQuery() ) {
      callEvent(evtAllListElemsRefreshed, (int)false);
      return false;
   }

   // Fuellen der Liste nur durchfuehren, wenn Query gesetzt ist.
   // Zusaetzlich kann ein evtl. unerwuenschtes Wieder-Fuellen der
   // Liste bei einem weiteren Refresh verhindert werden, wenn
   // der Style wsAutoRequery-Flag rueckgesetzt wurde.

   if ( hasQuery() && (!getFlags(wflQueryExecuted) || getFlags(wflAutoRequery)) ) {
      bool ok = false;
      onQueryPreStart(getQuery());
      setFlags(wflInQuery, true);

      try {
         ok = getQuery()->start(EVENT(this, (EVFUNC_RPI)onRefreshQuery));
      } catch ( const cErrBase& err ) {
         setFlags(wflInQuery|wflQueryStarted, false);
         callEvent(evtAllListElemsRefreshed, (int)false);
         onQueryPostEnd(getQuery());
         showError(err);
         return false;
      }

      if ( !ok ) {
         setFlags(wflInQuery|wflQueryStarted, false);
         callEvent(evtAllListElemsRefreshed, (int)false);
         onQueryPostEnd(getQuery());
         return false;
      }
   } else {
      // QueryEnded muss jedoch auf jeden Fall aufgerufen werden,
      // damit eine eventuelle Selektion durchgefuehrt werden kann.
      setFlags(wflInQuery, true);
      onQueryEnded(getQuery());
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtAllListElemsRefreshed, (int)true);
      onQueryPostEnd(getQuery());
   }

   return true;
}

int cwListCtl::onRefreshQuery(void *p1, int p2)
{
   csQuery *query = (csQuery *)p1;
   csQuery::STATE state = (csQuery::STATE)p2;
   bool rc = false;

   switch ( state ) {
   case csQuery::qsStart:
      setFlags(wflQueryStarted, true);
      return (int)onQueryStarted(query);
   case csQuery::qsData:
      return (int)onQueryData(query);
   case csQuery::qsEnd:
   default:
      rc = onQueryEnded(query);
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtAllListElemsRefreshed, (int)rc);
      onQueryPostEnd(getQuery());
   }

   return (int)rc;
}


// Refresh eines Elementes
// -----------------------

// Der Event evtSingleListElemRefreshed wird nach Abschluss des Refreshs mit
// folgenden Parametern erzeugt:
//
//  - Param1 (void*): Zeiger auf das aufgefrischte cwListElem-Objekt
//  - Param2 (int): Ok-Wert der Refresh-Verarbeitung

bool cwListCtl::refreshListElem(cwListElem *elem)
{
   if ( inQuery() || !elem ) {
      callEvent(evtSingleListElemRefreshed, (void*)elem, (int)false);
      return false;
   }

   csQuery *query = elem->getQuery() != 0 ? elem->getQuery() : getQuery();

   if ( query != 0 ) {
      bool ok = false;
      onQuery1PreStart(elem, query);
      setFlags(wflInQuery, true);
      rfs_elem = elem;

      try {
         ok = query->start1(EVENT(this, (EVFUNC_RPI)onRefreshQuery1), elem->getKey());
      } catch ( const cErrBase& err ) {
         setFlags(wflInQuery|wflQueryStarted, false);
         callEvent(evtSingleListElemRefreshed, (void*)rfs_elem, (int)false);
         onQuery1PostEnd(elem, query);
         showError(err);
         return false;
      }

      if ( !ok ) {
         setFlags(wflInQuery|wflQueryStarted, false);
         callEvent(evtSingleListElemRefreshed, (void*)rfs_elem, (int)false);
         onQuery1PostEnd(elem, query);
         return false;
      }
   } else {
      // QueryEnded muss jedoch auf jeden Fall aufgerufen werden,
      // damit eine eventuelle Selektion durchgefuehrt werden kann.
      setFlags(wflInQuery, true);
      rfs_elem = elem;
      onQuery1Ended(rfs_elem, getQuery());
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtAllListElemsRefreshed, (int)true);
      onQuery1PostEnd(elem, getQuery());
   }

   return true;
}

int cwListCtl::onRefreshQuery1(void *p1, int p2)
{
   csQuery *query = (csQuery *)p1;
   csQuery::STATE state = (csQuery::STATE)p2;
   bool rc = false;

   switch ( state ) {
   case csQuery::qsStart:
      setFlags(wflQueryStarted, true);
      return (int)onQuery1Started(rfs_elem, query);
   case csQuery::qsData:
      return (int)onQuery1Data(rfs_elem, query);
   case csQuery::qsEnd:
   default:
      rc = onQuery1Ended(rfs_elem, query);
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtSingleListElemRefreshed, (void*)rfs_elem, (int)rc);
      onQuery1PostEnd(rfs_elem, getQuery());
   }

   return (int)rc;
}


// Einfuegen neuer Elemente
// ------------------------

// Der Event evtNewListElemsInserted wird nach Abschluss des Inserts mit
// folgenden Parametern erzeugt:
//
//  - Param1 (void*): Zeiger auf das vorige cwListElem-Objekt (last)
//  - Param2 (int): Ok-Wert der Insert-Verarbeitung

bool cwListCtl::insertNewListElem(csQuery *query, cString key, cwListElem *before, cwListElem *parent)
{
   if ( inQuery() || !query ) {
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      return false;
   }

   bool ok = false;
   setFlags(wflInQuery, true);
   ins_before = before;
   ins_parent = parent;

   try {
      ok = query->start1(EVENT(this, (EVFUNC_RPI)onInsertQuery), key);
   } catch ( const cErrBase& err ) {
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      showError(err);
      return false;
   }

   if ( !ok ) {
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      return false;
   }

   return true;
}

bool cwListCtl::insertNewListElems(csQuery *query, cwListElem *before, cwListElem *parent)
{
   if ( inQuery() || !query ) {
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      return false;
   }

   onInsQueryPreStart(before, parent, getQuery());

   bool ok = false;
   setFlags(wflInQuery, true);
   ins_before = before;
   ins_parent = parent;

   try {
      ok = query->start(EVENT(this, (EVFUNC_RPI)onInsertQuery));
   } catch ( const cErrBase& err ) {
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      onInsQueryPostEnd(before, parent, getQuery());
      showError(err);
      return false;
   }

   if ( !ok ) {
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtNewListElemsInserted, (void*)before, (int)false);
      onInsQueryPostEnd(before, parent, getQuery());
      return false;
   }

   return true;
}

int cwListCtl::onInsertQuery(void *p1, int p2)
{
   csQuery *query = (csQuery *)p1;
   csQuery::STATE state = (csQuery::STATE)p2;
   bool rc = false;

   switch ( state ) {
   case csQuery::qsStart:
      setFlags(wflQueryStarted, true);
      return (int)onInsQueryStarted(ins_before, ins_parent, query);
   case csQuery::qsData:
      return (int)onInsQueryData(ins_before, ins_parent, query);
   case csQuery::qsEnd:
   default:
      rc = onInsQueryEnded(ins_before, ins_parent, query);
      setFlags(wflInQuery|wflQueryStarted, false);
      callEvent(evtNewListElemsInserted, (void*)ins_before, (int)rc);
      onInsQueryPostEnd(ins_before, ins_parent, getQuery());
   }

   return (int)rc;
}


// Elementbeschreibung
// ===================

bool cwListCtl::setupUserData(int new_user_data_size)
{
   // Wenn schon mal eingerichtet, darf sich die Groesse der benutzer-
   // spezifischen Zusatzinformationen nicht mehr aendern!

   if ( __ECL_ASSERT1__(new_user_data_size == user_data_size || !getFlags(wflUserDataInit)) ) {
      user_data_size = new_user_data_size;
      user_data_offset = sizeof(cwListElem) + onGetAddByteCount() - new_user_data_size;
      setFlags(wflUserDataInit);
      onPostUserDataInit();
      return true;
   } else {
      return false;
   }
}

void cwListCtl::setupColumns(csQuery *query)
{
   int fld, col; // Zaehler-Variablen

   // Ohne Abfrage geht gar nix

   if ( query == 0 )
      return;

   // Die Listenspalten werden nur geloescht, wenn das wflColumnsInit-Flag
   // nicht gesetzt ist. Dadurch wird unnoetiges "Flackern" beim Refresh
   // verhindert. Sollen die Spalten bewusst neu aus der Query gelesen werden,
   // kann die onQueryStarted-Methode abgeleitet und wflColumnsInit "von Hand"
   // gesetzt werden

   if ( getFlags(wflColumnsInit) )
      return;

   SETUP_ROWCOL_INFO rc_info = { query, row_count, 0, column_count, 0 };
   SETUP_FIELD_INFO fld_info = { query, 0, 0, 0, 0, false };

   // Lesen der Spalteninformationen aus der Abfrage...

   int offset = sizeof(cwListElem) + onGetAddByteCount();
   int column = 0, row = 0;

   delete[] field_descr;
   delete[] field_column;

   field_count = query->getFieldCount() - FIELD_OFF;
   row_count = 1;
   column_count = 0;

   if ( onAllowsMultipleRows() ) {
      // Auf wievielen Zeilen moechte sich EIN Datensatz ausbreiten?
      for ( fld = FIELD_OFF ; fld < field_count + FIELD_OFF ; fld++ )
         row_count = max(row_count, query->getFieldRow(fld)+1);
   }

   field_descr = new0 FIELD_DESCR[field_count];
   field_column = new0 int[row_count*field_count];

   for ( fld = 0 ; fld < row_count*field_count ; fld++ )
      field_column[fld] = -1;

   for ( fld = FIELD_OFF ; fld < field_count + FIELD_OFF ; fld++ ) {

      FIELD_DESCR& fd = field_descr[fld - FIELD_OFF];

      fd.offset          = offset;
      fd.buffer_size     = query->getFieldBufferSize(fld);
      fd.disp_column     = -1; // Nicht angezeigt
      fd.disp_row        = -1; // Nicht angezeigt
      fd.join_x          = query->getFieldJoinCols(fld);
      fd.join_y          = query->getFieldJoinRows(fld);
      fd.disp_width      = query->getFieldWidth(fld);
      fd.disp_prec       = query->getFieldPrec(fld);
      fd.disp_thsnd_sep  = true;
      fd.disp_left_pad   = false;
      fd.nullable        = query->isFieldNullable(fld);
      fd.editable        = !query->isFieldReadOnly(fld);
      fd.type            = query->getFieldType(fld);
      fd.title           = query->getTitleText(fld);
      fd.name            = query->getFieldName(fld);
      fd.halign          = query->getFieldHAlign(fld);
      fd.valign          = query->getFieldVAlign(fld);
      fd.title_halign    = query->getTitleHAlign(fld);
      fd.title_valign    = query->getTitleVAlign(fld);

      if ( fld <= csQuery::fldKey && fld >= csQuery::fldDescr ) {
         fd.buffer_size  = query->getFieldWidth(fld) + 1; // + 1 wg. '\0'-Byte
         fd.type         = csQuery::tString;
      }

      offset += fd.buffer_size + 1;

      if ( fld != csQuery::fldIconID && query->isFieldVisible(fld) ) {
         if ( onAllowsMultipleRows() ) {
            int new_col = query->getFieldCol(fld);
            int new_row = query->getFieldRow(fld);
            if ( new_col >= 0 ) column = new_col;
            if ( new_row >= 0 ) row = new_row;
         }
         field_column[row*field_count + column] = fld;
         fd.disp_column = column++;
         fd.disp_row = row;
         column_count = max(column_count, column);
      }

      #undef __Debug_Column_Setup__
      #if __ECL_DEBUG__ > 0 && defined __Debug_Column_Setup__
         cBase::DbgOut(0, "Setup column %3d: %16s, off=%4d, size=%4d, disp in col %3d",
            fld, (const char *)fd.name,
            fd.offset, fd.buffer_size, fd.disp_column);
      #endif

   }

   field_data_size = offset;
   setFlags(wflColumnsInit);

   // Die eingerichteten Spalten/Zeilen jetzt auch anzeigen. Dazu dem Control
   // erst mal die Moeglichkeit geben, sich mental auf die evtl. geaenderte
   // Spalten-/Zeilenzahl einzustellen:

   rc_info.new_row_count = row_count;
   rc_info.new_column_count = column_count;
   int change_til = column_count > rc_info.old_column_count ? rc_info.old_column_count : column_count;
   onSetupRowCol(rc_info);

   // Anschliessend Spalten einrichten. Um die noetigen Daten zu
   // erhalten, muss das Control die Query befragen. Ueber das 'add'-Flag
   // wird dem Control mitgeteilt, ob eine neue Spalte hinzugefuegt werden
   // muss oder eine bestehende geaendert werden soll.

   for ( row = 0 ; row < row_count ; row++ ) {
      for ( col = 0 ; col < column_count ; col++ ) {
         fld = field_column[row*field_count + col];
         if ( fld >= 0 ) {
            fld_info.descr = &field_descr[fld - FIELD_OFF];
            fld_info.disp_row = row;
            fld_info.disp_col = col;
            fld_info.add = col >= change_til;
            onSetupField(fld, fld_info);
         }
      }
   }
}


// Selektion
// =========

static bool SelectElements(cwListCtl *list, cwListElem *elem, void *)
   { return list->selectElem(elem); }

static bool DeselectElements(cwListCtl *list, cwListElem *elem, void *)
   { return list->deselectElem(elem); }

int cwListCtl::onGetSelectedElemCount(bool /*walk*/) const
{
   int count = 0;
   cwListElem *elem = getSelectedElem(0, true);

   while ( elem != 0 ) {
      count++;
      elem = getSelectedElem(elem, true);
   }

   return count;
}

bool cwListCtl::onSelectAllElems(bool sel, cwListElem *parent, bool walk)
{
   return doWithAllElems(sel ? SelectElements : DeselectElements, NULL, parent, walk);
}

void cwListCtl::saveSelection()
{
   if ( hasQuery() ) {

      cwListElem *elem;
      int key_size = getQuery()->getFieldWidth(csQuery::fldKey);

      delete[] selected_elems;
      selected_count = getSelectedElemCount();
      selected_elems = new0 char[(selected_count+1) * key_size];

      if ( selected_count > 0 && (elem = getCursoredElem()) != 0 ) {
         elem->get(csQuery::fldKey, selected_elems, key_size);
      } else {
         selected_elems[0] = '\0';
      }

      if ( selected_count > 0 ) {
         elem = 0;
         for ( int i=1 ; i<=selected_count ; i++ ) {
            if ( (elem = getSelectedElem(elem)) != 0 ) {
               elem->get(csQuery::fldKey, selected_elems+i*key_size, key_size);
            } else {
               selected_elems[i*key_size] = '\0';
            }
         }
      }

   }
}

void cwListCtl::restoreSelection()
{
   if ( hasQuery() && selected_elems != 0 && selected_count > 0 ) {

      cwListElem *elem;
      int key_size = getQuery()->getFieldWidth(csQuery::fldKey);

      if ( selected_count > 0 && selected_elems != 0 ) {
         for ( int i=1 ; i<=selected_count ; i++ ) {
            if ( (elem = getElemWithKey(selected_elems+i*key_size)) != 0 ) {
               // Hier doSelectElem benutzen, nicht selectElem, da letzteres
               // die Storage beschreibt (und das muss hier nicht sein!)
               doSelectElem(elem, true);
            }
         }
         if ( *selected_elems != '\0' && (elem = getElemWithKey(selected_elems)) != 0 )
            setCursoredElem(elem);
      }

      delete[] selected_elems;
      selected_elems = 0;
      selected_count = 0;

   }
}


// Sichtbarkeit
// ============

bool cwListCtl::onEnsureElemVisible(cwListElem *elem, bool /*partial_ok*/)
{
   // Wird aufgerufen, um sicherzustellen, dass das Element 'elem'
   // ganz (partial_ok = false) oder wenigstens teilweise (partial_ok = true)
   // sichtbar ist. Dazu muss das Control evtl. vertikal gescrollt werden.

   return elem != 0;
}

bool cwListCtl::onEnsureFieldVisible(int /*fld*/, bool /*partial_ok*/)
{
   // Wird aufgerufen, um sicherzustellen, dass die dem Feld zugeordnete Spalte
   // ganz (partial_ok = false) oder wenigstens teilweise (partial_ok = true)
   // sichtbar ist. Dazu muss das Control evtl. horizontal gescrollt werden.

   return true;
}


// List-Control einrichten
// =======================

void cwListCtl::resetListCtl(int field_count, int row_count)
{
   // 'field_count' muss mindestens 0 sein (damit sind die 4 Standard-
   // spalten eingeschlossen)

   if ( !__ECL_ASSERT1__(field_count >= 0) )
      field_count = 0;

   // 'row_count' muss mindestens 1 sein und darf auch groesser sein,
   // wenn das Control mehrzeilige Datensaetze zulaesst

   if ( !__ECL_ASSERT1__(row_count == 1 || row_count > 1 && onAllowsMultipleRows()) )
      row_count = 1;

   // Alle Elemente loeschen und Strukturen initialisieren

   deleteAllElems();

   field_count -= FIELD_OFF;
   old_column_count = cwListCtl::column_count;
   old_row_count = cwListCtl::row_count;

   cwListCtl::field_count = field_count; //
   cwListCtl::row_count = row_count;
   cwListCtl::column_count = 0; // Wird spaeter gesetzt

   delete[] field_descr;
   delete[] field_column;

   field_descr = new0 FIELD_DESCR[field_count];
   field_column = new0 int[row_count*field_count];
   field_data_size = 0;

   for ( int fld = 0 ; fld < field_count ; fld++ )
      field_descr[fld].offset = field_descr[fld].buffer_size = 0;
   for ( int col = 0 ; col < row_count*field_count ; col++ )
      field_column[col] = -1;
}

void cwListCtl::setupField(int fld, const FIELD_INFO& field_info)
{
   if ( __ECL_ASSERT1__(field_descr != 0)
     && __ECL_ASSERT1__(fld >= FIELD_OFF && fld < field_count + FIELD_OFF)
     && __ECL_ASSERT1__(field_info.width >= 0) ) {

      // Naechsten Wert fuer 'Offset', 'row' und 'column' bestimmen

      int offset = sizeof(cwListElem) + onGetAddByteCount();
      int column = 0, row = 0;

      for ( int i = 0 ; i < field_count ; i++ ) {
         FIELD_DESCR& fd = field_descr[i];
         if ( fd.buffer_size > 0 ) {
            offset = max(offset, fd.offset + fd.buffer_size + 1);
            column = max(column, fd.disp_column + 1);
            row    = max(row, fd.disp_row);
         }
      }

      FIELD_DESCR& fd = field_descr[fld - FIELD_OFF];
      csQuery::TYPE type = field_info.type;
      csQuery::HALIGN def_halign = csQuery::haLeft;
      csQuery::VALIGN def_valign = csQuery::vaCenter;

      switch ( type ) {
      case csQuery::tInt:     fd.buffer_size = sizeof(int); def_halign = csQuery::haRight; break;
      case csQuery::tDouble:  fd.buffer_size = sizeof(double); def_halign = csQuery::haRight; break;
      case csQuery::tTime:    fd.buffer_size = sizeof(cTime); break;
      case csQuery::tDate:    fd.buffer_size = sizeof(cDate); break;
      case csQuery::tWeek:    fd.buffer_size = sizeof(cDate); break;
      case csQuery::tChar:    fd.buffer_size = sizeof(char); break;
      case csQuery::tString:  fd.buffer_size = field_info.buffer_size; break;
      case csQuery::tIcon:    fd.buffer_size = sizeof(cIcon); break;
      case csQuery::tBitmap:  fd.buffer_size = sizeof(cBitmap); break;
      default:                fd.buffer_size = 0;
      }

      fd.offset          = offset;
      fd.disp_column     = -1; // Nicht angezeigt
      fd.disp_row        = -1; // Nicht angezeigt
      fd.join_x          = field_info.join_cols;
      fd.join_y          = field_info.join_rows;
      fd.disp_width      = field_info.width;
      fd.disp_prec       = type == csQuery::tDouble ? field_info.prec : 0;
      fd.disp_thsnd_sep  = type == csQuery::tDouble;
      fd.disp_left_pad   = false;
      fd.nullable        = !(field_info.flags & fifIsNotNull);
      fd.editable        = !(field_info.flags & fifIsReadOnly);
      fd.type            = type;
      fd.title           = field_info.title;
      fd.name            = field_info.name;
      fd.halign          = field_info.halign == haDefault ? def_halign : csQuery::HALIGN(field_info.halign-1);
      fd.valign          = field_info.valign == haDefault ? def_valign : csQuery::VALIGN(field_info.valign-1);
      fd.title_halign    = field_info.title_halign == haDefault ? def_halign : csQuery::HALIGN(field_info.title_halign-1);
      fd.title_valign    = field_info.title_valign == vaDefault ? def_valign : csQuery::VALIGN(field_info.title_valign-1);

      if ( fld <= csQuery::fldKey && fld >= csQuery::fldDescr ) {
         fd.buffer_size  = field_info.width + 1; // + 1 wg. '\0'-Byte
         fd.type         = csQuery::tString;
      }

      offset += fd.buffer_size + 1;

      if ( fld != csQuery::fldIconID && !(field_info.flags & fifIsInvisible) ) {
         if ( onAllowsMultipleRows() ) {
            int new_col = field_info.col;
            int new_row = field_info.row;
            if ( new_col >= 0 ) column = new_col;
            if ( new_row >= 0 ) row = new_row;
         }
         if ( __ECL_ASSERT1__(row < row_count) ) {
            field_column[row*field_count + column] = fld;
            fd.disp_column = column++;
            fd.disp_row = row;
            column_count = max(column_count, column);
         }
      }

      #undef __Debug_Column_Setup__
      #if __ECL_DEBUG__ > 0 && defined __Debug_Column_Setup__
         cBase::DbgOut(0, "Setup column %3d: %16s, off=%4d, size=%4d, disp in col %3d",
            fld, (const char *)fd.name,
            fd.offset, fd.buffer_size, fd.disp_column);
      #endif

      field_data_size = max(field_data_size, offset);

   }
}

void cwListCtl::setupField(int fld, cString name, cString title, int flags, int buffer_size, int width)
{
   FIELD_INFO field_info;
   memset(&field_info, 0, sizeof field_info);

   field_info.name         = name;
   field_info.type         = csQuery::tString;
   field_info.flags        = flags;
   field_info.buffer_size  = buffer_size;
   field_info.width        = width >= 0 ? width : buffer_size;
   field_info.prec         = 0;
   field_info.halign       = haDefault;
   field_info.valign       = vaDefault;
   field_info.row          = -1;
   field_info.col          = -1;
   field_info.join_rows    = 0;
   field_info.join_cols    = 0;
   field_info.title        = title.isEmpty() ? name : title;
   field_info.title_halign = haDefault;
   field_info.title_valign = vaDefault;

   setupField(fld, field_info);
}

void cwListCtl::setupField(int fld, cString name, cString title, csQuery::TYPE type, int flags, int width, int prec)
{
   FIELD_INFO field_info;
   memset(&field_info, 0, sizeof field_info);

   field_info.name         = name;
   field_info.type         = type;
   field_info.flags        = flags;
   field_info.buffer_size  = 0;
   field_info.width        = width;
   field_info.prec         = prec;
   field_info.halign       = haDefault;
   field_info.valign       = vaDefault;
   field_info.row          = -1;
   field_info.col          = -1;
   field_info.join_rows    = 0;
   field_info.join_cols    = 0;
   field_info.title        = title.isEmpty() ? name : title;
   field_info.title_halign = haDefault;
   field_info.title_valign = vaDefault;

   setupField(fld, field_info);
}

void cwListCtl::setupListConfig(int key_len, int name_len, int descr_len)
{
   // Wenn noch nicht initialisiert, 'reset' mit Default-Konfiguration
   // (nur die 4 Standardspalten: Key, Name, Descr, IconID)

   if ( field_descr == 0 )
      resetListCtl(0);

   // Wenn noetig, Standardfelder jetzt einrichten

   if ( field_descr[csQuery::fldIconID - FIELD_OFF].buffer_size <= 0 )
      setupField(csQuery::fldIconID, 0, 0, csQuery::tInt, fifIsInvisible, 0);
   if ( field_descr[csQuery::fldDescr - FIELD_OFF].buffer_size <= 0 )
      setupField(csQuery::fldDescr, 0, 0, fifIsInvisible, max(descr_len, 32));
   if ( field_descr[csQuery::fldName - FIELD_OFF].buffer_size <= 0 )
      setupField(csQuery::fldName, 0, 0, fifIsInvisible, max(name_len, 32));
   if ( field_descr[csQuery::fldKey - FIELD_OFF].buffer_size <= 0 )
      setupField(csQuery::fldKey, 0, 0, fifIsInvisible, max(key_len, 8));

   setFlags(wflColumnsInit);

   // Die eingerichteten Spalten/Zeilen jetzt auch anzeigen. Dazu dem Control
   // erst mal die Moeglichkeit geben, sich mental auf die evtl. geaenderte
   // Spalten-/Zeilenzahl einzustellen:

   SETUP_ROWCOL_INFO rc_info = { 0, old_row_count, 0, old_column_count, 0 };

   rc_info.new_row_count = row_count;
   rc_info.new_column_count = column_count;
   int change_til = column_count > rc_info.old_column_count ? rc_info.old_column_count : column_count;
   onSetupRowCol(rc_info);

   // Anschliessend Spalten einrichten. Um die noetigen Daten zu
   // erhalten, muss das Control die Query befragen. Ueber das 'add'-Flag
   // wird dem Control mitgeteilt, ob eine neue Spalte hinzugefuegt werden
   // muss oder eine bestehende geaendert werden soll.

   SETUP_FIELD_INFO fld_info = { 0, 0, 0, 0, 0, false };

   for ( int row = 0 ; row < row_count ; row++ ) {
      for ( int col = 0 ; col < column_count ; col++ ) {
         int fld = field_column[row*field_count + col];
         if ( fld >= 0 ) {
            fld_info.descr = &field_descr[fld - FIELD_OFF];
            fld_info.disp_row = row;
            fld_info.disp_col = col;
            fld_info.add = col >= change_til;
            onSetupField(fld, fld_info);
         }
      }
   }
}


// Spalten
// =======

int cwListCtl::getColumnCount() const
{
   return column_count;
}

int cwListCtl::getRowCount() const
{
   return row_count;
}

int cwListCtl::getJoinColumns(int fld) const
{
   return fld >= FIELD_OFF && fld < field_count + FIELD_OFF && field_descr ?
      field_descr[fld - FIELD_OFF].join_x : 0;
}

int cwListCtl::getJoinRows(int fld) const
{
   return fld >= FIELD_OFF && fld < field_count + FIELD_OFF && field_descr ?
      field_descr[fld - FIELD_OFF].join_y : 0;
}

int cwListCtl::getFieldFromColumn(int col, int row) const
{
   return row >= 0 && row < row_count && col >= 0 && col < column_count && field_column ?
      field_column[row*field_count + col] : -1;
}

int cwListCtl::getColumnFromField(int fld) const
{
   return fld >= FIELD_OFF && fld < field_count + FIELD_OFF && field_descr ?
      field_descr[fld - FIELD_OFF].disp_column : -1;
}

int cwListCtl::getRowFromField(int fld) const
{
   return fld >= FIELD_OFF && fld < field_count + FIELD_OFF && field_descr ?
      field_descr[fld - FIELD_OFF].disp_row : -1;
}


// Elementverwaltung
// =================

//        Erstes                  Letztes
//        Element                 Element
//  ----------------------------------------->
//
//             +---------+ +---------+
//       +---+-+-+   +---+-+-+   +---+---+
//    +->| X | o |   | o | o |   | o | X |<-+
//    |  +---+---+   +-+-+---+   +-+-+---+  |
//    |      +---------+ +---------+        |
//    |                                     |
//  +-+-+                                 +-+-+
//  | o | anchor_head          anchor_tail| o |
//  +---+                                 +---+

bool cwListCtl::doWithAllElems(ENUM_ELEM_FUNC func, void *data, cwListElem *parent, bool walk)
{
   bool rc = true;
   cwListElem *actual;

   actual = parent ? parent->getFirstChild() : anchor_head;

   while ( rc && actual ) {
      if ( (rc = func(this, actual, data)) == true && walk && actual->hasChilds() )
         rc = doWithAllElems(func, data, actual);
      actual = actual->next;
   }

   return rc;
}


// Zellen-Editor
// =============

bool cwListCtl::beginEdit(cwListElem *elem, int fld)
{
   //cBase::DbgOut(0, "cwListCtl::beginEdit(elem=%08x, fld=%d)", elem, fld);

   // Liefert true, wenn die Edit-Operation durchgefuehrt werden soll
   // Liefert false, wenn die Edit-Operation abgebrochen werden soll

   if ( elem != 0 && (onBeginEdit(elem, fld) || edit_ctl != 0) ) {

      // Moegliche Interessenten vom Beginn der Edit-Operation unterrichten
      callEvent(evtBeginEdit, elem, fld);

      if ( edit_ctl != 0 ) {

         // Schriftart des Edit-Controls an die des Listenfensters angleichen
         #if defined __ECL_W32__
            ((CWnd*)ccwWindow::__getWnd(edit_ctl))->SetFont(((CWnd*)_wnd)->GetFont());
         #else
            // ...
         #endif

         // Events registrieren
         edit_ctl->addEvent(evtEnterKeyPressed, this, (EVFUNC)onEvtEnterKey);
         edit_ctl->addEvent(evtEscKeyPressed, this, (EVFUNC)onEvtEscKey);
         edit_ctl->addEvent(evtNavKeyPressed, this, (EVFUNC_I)onEvtNavKey);

         // Enter, Esc und Navigationstasten ansonsten ignorieren
         edit_ctl->setFlags(wflEatEnterKey | wflEatEscKey | wflEatNavKeys);

         // Und schliesslich das Edit-Control auch anzeigen und aktivieren
         edit_ctl->show();
         edit_ctl->refresh();
         edit_ctl->activate();
         edit_ctl->setFocus();

         // Da wir unsere eigene Edit-Verarbeitung durchfuehren (erkennbar an
         // edit_ctl != 0), jetzt false liefern, um die Default-Verarbeitung
         // zu verhindern!
         return false;

      }

      return true;

   }

   return false;
}

void cwListCtl::endEdit(bool cancel)
{
   if ( edit_ctl != 0 ) {

      //cBase::DbgOut(0, "cwListCtl::endEdit(%s)", cancel ? "cancel" : "");

      if ( !cancel ) {
         // Moegliche Interessenten vom Ende der Edit-Operation unterrichten.
         // An dieser Stelle kann Event-Empfaenger den Text aus dem Edit-Control
         // lesen und bei Bedarf sogar modifizieren
         callEvent(evtStoreEdit, edit_elem, edit_fld);
         cString text = edit_ctl->getText();
         if ( onEndEdit(edit_elem, edit_fld, text) )
            edit_elem->put(edit_fld, text);
      } else {
         // Moegliche Interessenten vom Abbruch der Edit-Operation unterrichten
         callEvent(evtDiscardEdit, edit_elem, edit_fld);
      }

      // Alle Events wieder deregistrieren
      edit_ctl->removeEvent(this);

      // Das Edit-Control hat seine Schuldigkeit getan
      delete edit_ctl;
      edit_ctl = 0;
      edit_elem = 0;
      edit_fld = 0;

   }
}

cdRect cwListCtl::getEditRect(cwListElem *elem, int fld) const
{
   return onGetEditRect(elem, fld);
}

void cwListCtl::onEvtEnterKey()
{
   execDelayed(ediEndEdit, (void*)false);
}

void cwListCtl::onEvtEscKey()
{
   execDelayed(ediEndEdit, (void*)true);
}

struct EDIT_NAV {
   cwListElem *next_elem;
   int next_fld;
};

void cwListCtl::onEvtNavKey(int p1)
{
   if ( edit_ctl != 0 ) {

      cwListElem *elem = edit_elem;
      int fld = edit_fld;
      int col = getColumnFromField(fld);

      do {
         if ( p1 == cwCmdChar::vkTab ) {
            if ( ++col >= getColumnCount() ) {
               elem = elem->getNext();
               col = 0;
            }
         } else if ( p1 == cwCmdChar::vkBackTab ) {
            if ( --col < 0 ) {
               elem = elem->getPrev();
               col = getColumnCount() - 1;
            }
         } else if ( p1 == cwCmdChar::vkUp ) {
            elem = elem->getPrev();
         } else if ( p1 == cwCmdChar::vkDown ) {
            elem = elem->getNext();
         } else if ( p1 == cwCmdChar::vkRight ) {
            if ( ++col >= getColumnCount() )
               col = 0;
         } else if ( p1 == cwCmdChar::vkLeft ) {
            if ( --col < 0 )
               col = getColumnCount() - 1;
         }
         fld = getFieldFromColumn(col);
      } while ( elem != 0 && !elem->isEditable(fld) );

      if ( elem != 0 ) {
         EDIT_NAV *ena = new0 EDIT_NAV;
         ena->next_elem = elem;
         ena->next_fld = fld;
         execDelayed(ediNavigateEdit, (void*)ena);
      } else {
         execDelayed(ediEndEdit, (void*)0);
      }

   }
}


// Ueberschriebene Events
// ======================

bool cwListCtl::onAllowStore()
{
   return cwControl::onAllowStore();
}

bool cwListCtl::onAllowClose(cwWindow *notify)
{
   if ( inQuery() && !onErrorInQuery() )
      return false;

   return cwControl::onAllowClose(notify);
}

bool cwListCtl::onAllowDiscard()
{
   if ( inQuery() && !onErrorInQuery() )
      return false;

   return cwControl::onAllowDiscard();
}

bool cwListCtl::onRefresh()
{
   bool rc = false;

   try {
      if ( getFlags(wflAutoRequery) || !getFlags(wflQueryExecuted) )
         rc = requery(); /* war: refreshAllListElems(); */
      rc = cwControl::onRefresh() || rc;
   } catch ( const cErrBase& err ) {
      showError(err, "Fehler beim Refresh eines Dialogelementes");
   }

   return rc;
}

void cwListCtl::onEventModified()
{
   // Auf gar keinen Fall die cwControl::onEventModified() aufrufen,
   // da diese ein Komplett-Refresh (also inklusive Requery) ausloest

   cString key; getStorageVal(key);
   setCursoredElem(getElemWithKey(key, 0, true));

   // Der evtStorageModified-Event soll aber trotzdem ausgeloest
   // werden, daher:

   if ( hasStorage() )
      callEvent(evtStorageModified, getStorage());
}

//

bool cwListCtl::onCommand(const cwCmdEvt& cmd)
{
   cEloSelection selection;
   cEloSelection *sel = &selection;

   for ( cwWindow *win = this ; win != 0 ; win = win->getActiveChild() ) {
      if ( win->hasWindowElemSelection() ) {
         if ( (sel = win->getWindowElemSelection()) == 0 ) {
            sel = &selection;
            win->updateWindowElemSelection(*sel);
         }
         break;
      }
   }

   cEloActionDescription *ad = getWindowActionDescription(sel);

   // Selektion fuer das aktuelle Fenster ('this') vorbereiten
   cEloSelection this_selection;
   this_selection.addElement(this);

   if ( ad != 0 ) {
      cEloOperation *op = ad->getOperation(cmd.getId(), true);
      if ( op != 0 ) {
         cString sig = op->getSignature();
         int sub_id = ad->getOperationSubId(cmd.getId(), true);
         if ( sel != 0 && sel->supportsOperation(sig) && op->isEnabled(sel) ) {
            sel->execOperation(sig, sub_id, this);
            return true;
         } else if ( this_selection.supportsOperation(sig) && op->isEnabled(&this_selection) ) {
            this_selection.execOperation(sig, sub_id, this);
            return true;
         } else if ( op->isStatic() && op->isEnabled() ) {
            op->execOperation();
            return true;
         }
      }
   }

   return false;
}

bool cwListCtl::onCommandUI(cwCmdUI& cmd)
{
   cEloSelection selection;
   cEloSelection *sel = &selection;

   // Aktuelle Selektion ermitteln
   //    TBD: Kann das nicht "weg"-optimiert werden? Voraussetzung, dass die sowieso vorhandene Selektion
   //    des Views schon up-to-date ist: Diese einfach benutzen!

   for ( cwWindow *win = this ; win != 0 ; win = win->getActiveChild() ) {
      if ( win->hasWindowElemSelection() ) {
         if ( (sel = win->getWindowElemSelection()) == 0 ) {
            sel = &selection;
            win->updateWindowElemSelection(*sel);
         }
         break;
      }
   }

   // Selektion fuer das aktuelle Fenster ('this') vorbereiten
   cEloSelection this_selection;
   this_selection.addElement(this);

   // Operation enabled?

   cEloActionDescription *ad = getWindowActionDescription(sel);

   if ( ad != 0 ) {
      cEloOperation *op = ad->getOperation(cmd.getId(), true);
      if ( op != 0 ) {
         cString sig = op->getSignature();
         if ( op->isStatic() && op->isEnabled()
           || sel->supportsOperation(sig) && op->isEnabled(sel)
           || this_selection.supportsOperation(sig) && op->isEnabled(&this_selection) )
         {
            cmd.setEnable(true);
         } else {
            cmd.setEnable(false);
         }
         if ( op->isCheckable(sel) )
            cmd.setCheck(op->isChecked(sel));
         return true;
      } else {
         #undef __Disable_Cmd_If_Not_Connected_To_Operation__
         #if __Disable_Cmd_If_Not_Connected_To_Operation__
            cmd.setEnable(false);
            return true;
         #endif
      }
   }

   // Keine passende Operation gefunden, Default ausfuehren

   return cwControl::onCommandUI(cmd);
}

//

bool cwListCtl::onHasWindowElemSelection() const
{
   return true;
}

bool cwListCtl::onUpdateWindowElemSelection(cEloSelection& selection) const
{
   selection.clearSelection();
   for ( cwListElem *elem = 0 ; (elem = this->getSelectedElem(elem)) != 0 ; )
      selection.addElement(elem);
   if ( selection.getElementCount() == 0 )
      selection.addElement((cwListCtl*)this);
   return true;
}

cEloSelection * cwListCtl::onGetWindowElemSelection()
{
   // Liefert Selektion des Views, falls dieser existiert

   cwWindow *parent = getParent();
   return parent != 0 && parent->getFlags(wflIsAView) ?
      parent->getWindowElemSelection()
    : 0;
}

cEloActionDescription * cwListCtl::onGetWindowActionDescription(const cEloSelection *selection) const
{
   // Liefert die Default-Aktionsbeschreibung des Controls...

   if ( action_descr != 0 )
      return action_descr;

   // ... oder die des Views, falls dieser existiert

   cwWindow *parent = getParent();
   return parent != 0 && parent->getFlags(wflIsAView) ?
      parent->getWindowActionDescription(selection)
    : 0;
}

//

bool cwListCtl::onRefreshCtl(csStorage *store)
{
   bool rc = cwControl::onRefreshCtl(store);
   return rc;
}

bool cwListCtl::onRequeryCtl(csQuery * /*query*/)
{
   deleteAllElems();
   return isCreated() ?
      refreshAllListElems()
    : true;
}

cwControl::DATAERR cwListCtl::onCheckCtl(csStorage *store)
{
   return cwControl::onCheckCtl(store);
}

cwControl::DATAERR cwListCtl::onStoreCtl(csStorage *store)
{
   cwListElem *elem = getSelectedElem();

   if ( store && elem ) {
      cString key = elem->getKey();
      if ( store->isNullable() && !onGetNullText().isEmpty() ) {
         if ( !store->put(key) )
            return derrWrite;
      } else {
         if ( !key.isEmpty() && !store->put(key) )
            return derrWrite;
      }
   }

   return cwControl::onStoreCtl(store);
}


// Window-Styles
// -------------

int cwListCtl::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      if ( (mask & wsAutoRequery) && getFlags(wflAutoRequery) )
         rc |= wsAutoRequery;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwControl::onGetStyles(mask);
}

void cwListCtl::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsAutoRequery )
         setFlags(wflAutoRequery, true);
      if ( remove & wsAutoRequery )
         setFlags(wflAutoRequery, false);

      cwControl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}


// Zusaetzliche Events
// ===================

bool cwListCtl::onErrorInQuery()
{
   onErrorMark(true);
   // ???
   // onErrorBox("Dieser Dialog kann momentan nicht verlassen werden, "
   //            "da noch eine Datenbank-Abfrage laeuft");
   onErrorMark(false);
   return false;
}

void cwListCtl::onBeginDrag(cwListElem *elem, int mouse_button)
{
   callEvent(evtBeginDrag, elem, mouse_button);
}

bool cwListCtl::onBeginEdit(cwListElem *elem, int fld)
{
   // Liefert true, wenn die Edit-Operation durchgefuehrt werden soll
   // Liefert false, wenn die Edit-Operation abgebrochen werden soll

   if ( fld >= csQuery::fldDescr && fld < field_count + FIELD_OFF
     && elem != 0 && elem->isEditable(fld) )
   {
      ensureElemVisible(elem, false);
      ensureFieldVisible(fld, true);

      cdRect rect = getEditRect(elem, fld);
      if ( !rect.isEmpty() ) {
         edit_ctl = onMakeEditCtl(elem, fld, rect);
         if ( edit_ctl != 0 ) {
            edit_elem = elem;
            edit_fld = fld;
            return true;
         }
      }
   }

   return false;
}

bool cwListCtl::onEndEdit(cwListElem * /*elem*/, int /*fld*/, cString /*text*/)
{
   // Hier kann der vom Benutzer eingegebene Text nochmal geprueft
   // und evtl. modifiziert werden, oder das Zurueckspeichern des
   // geaenderten Wertes verhindert werden (rc = false).

   return true;
}

cdRect cwListCtl::onGetEditRect(cwListElem * /*elem*/, int /*fld*/) const
{
   // Die Basisklasse kennt keine Geometrie. Diese Infor-
   // mation muss von der konkreten Ableitung kommen!

   return cdRect();
}

cwControl * cwListCtl::onMakeEditCtl(cwListElem *elem, int fld, const cdRect& rect)
{
   // Edit-Control unsichtbar anlegen und mit einer Kopie der Storage
   // des Feldes 'fld' verbinden.

   cwEditField *ef = new cwEditField;
   ef->create(this, 42, elem->makeCompatibleVar(fld),
      wsBorder | cwEditField::wsAutoScrollHorz, rect);

   return ef;
}

bool cwListCtl::onSelectionChanging(cwListElem *elem)
{
   // Wird ausgeloest, bevor die Aenderung der Selektion durchgefuehrt wird.
   // Durch Rueckgabe von 'false' kann diese Aenderung verhindert werden.

   try {
      callEvent(evtSelectionChanging, elem);
   } catch ( const cErrBase& err ) {
      showError(err);
   }

   return true;
}

void cwListCtl::onSelectionChanged(cwListElem *elem)
{
   // Wird ausgeloest, nachdem die Aenderung der Selektion durchgefuehrt
   // wurde. Die Auswertung dieses Events sollte der "Normalfall" sein.

   #define __Key_Maybe_Empty__
   #ifdef __Key_Maybe_Empty__
      // 10.10.2001 -TE- 'key' darf auch Leerstring sein, damit z.B. fuer
      // cwComboBox das NULL-Element eingetragen werden kann.
      if ( elem && !isStorageReadOnly() )
         putStorageVal(elem->getKey());
   #else
      cString key;
      if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
         putStorageVal(key);
   #endif

   // Falls vorhanden, aktuelle Selektion aktualisieren

   updateWindowElemSelection();

   // Event weiterverteilen

   try {
      callEvent(evtSelectionChanged, elem);
   } catch ( const cErrBase& err ) {
      showError(err);
   }

   setFlags(wflHasChanged);
}

void cwListCtl::onListElemSelected(cwListElem *elem)
{
   // Wird ausgeloest, wenn ein Element der Liste zweifelsfrei ausgewaehlt
   // wurde (z.B. durch Doppelklick). Nicht bei allen Listenarten moeglich.

   #ifdef __Key_Maybe_Empty__
      // 10.10.2001 -TE- 'key' darf auch Leerstring sein, damit z.B. fuer
      // cwComboBox das NULL-Element eingetragen werden kann.
      if ( elem && !isStorageReadOnly() )
         putStorageVal(elem->getKey());
   #else
      cString key;
      if ( elem && !isStorageReadOnly() && !(key = elem->getKey()).isEmpty() )
         putStorageVal(key);
   #endif

   try {
      callEvent(evtListElemSelected, elem);
   } catch ( const cErrBase& err ) {
      showError(err);
   }

   setFlags(wflHasChanged);
}

cString cwListCtl::onGetNullText()
{
   return cString();
}


// Elementverwaltung
// -----------------

int cwListCtl::onGetElemCountFromBegin(cwListElem *elem) const
{
   int count = -1;

   while ( elem ) {
      count++;
      elem = elem->prev;
   }

   return count;
}

int cwListCtl::onGetElemCountFromEnd(cwListElem *elem) const
{
   int count = -1;

   while ( elem ) {
      count++;
      elem = elem->next;
   }

   return count;
}

cwListElem * cwListCtl::onGetElemWithKey(cString key, cwListElem *parent, bool walk) const
{
   cwListElem *elem = parent ? parent->head : anchor_head;

   if ( key.isEmpty() ) {

      while ( elem && !elem->getKey().isEmpty() ) {
         if ( walk && elem->hasChilds() ) {
            cwListElem *child = getElemWithKey(key, elem, true);
            if ( child )
               return child;
         }
         elem = elem->next;
      }

   } else {

      while ( elem && elem->getKey() != key ) {
         if ( walk && elem->hasChilds() ) {
            cwListElem *child = getElemWithKey(key, elem, true);
            if ( child )
               return child;
         }
         elem = elem->next;
      }

   }

   return elem;
}

cwListElem * cwListCtl::onGetElemWithIndex(int idx) const
{
   cwListElem *elem = anchor_head;

   while ( elem && idx > 0 ) {
      elem = elem->next;
      idx--;
   }

   return elem;
}


// Abfrage
// -------

bool cwListCtl::onQueryPreStart(csQuery * /*query*/)
{
   return true;
}

bool cwListCtl::onQueryStarted(csQuery *query)
{
   // Einrichten der benutzerspezifischen Zusatzinformationen

   if ( !setupUserData(query->getUserDataLen()) )
      return false;

   // Einrichten der Spalten ueber die Query

   setupColumns(query);

   // Wenn keine Storage vorhanden, aktuelle Selektion speichern.
   // Anschliessend evtl. vorhandene Listenelemente loeschen

   if ( !hasStorage() )
      saveSelection();

   return deleteAllElems();
}

bool cwListCtl::onQueryData(csQuery *query)
{
   cwListElem *new_elem = new1(this) cwListElem(query);
   if ( user_data_size > 0 )
      query->getUserData((char*)new_elem + user_data_offset, user_data_size);
   return insertElemAtEnd(new_elem);
}

bool cwListCtl::onQueryEnded(csQuery *query)
{
   // Wenn die Abfrage abgebrochen wurde, keine weitere Verarbeitung

   if ( query == 0 || query->getFlags(csQuery::fStopReq) )
      return true;

   // Wenn keine Storage vorhanden, aktuelle Selektion wiederherstellen.
   // Ansonsten aktuelle Markierung aus Storage-Wert uebernehmen

   if ( !hasStorage() ) {
      restoreSelection();
   } else {
      cString key;
      if ( getStorageVal(key) ) {
         cwListElem *elem = getElemWithKey(key, NULL, true);
         if ( elem ) {
            setCursoredElem(elem);
            // Hier doSelectElem benutzen, nicht selectElem, da letzteres
            // die Storage beschreibt (und das muss hier nicht sein!)
            doSelectElem(elem, true);
         }
      }
   }

   setFlags(wflQueryExecuted, true);

   return true;
}

void cwListCtl::onQueryPostEnd(csQuery * /*query*/)
{
}


// Einzelabfrage
// -------------

bool cwListCtl::onQuery1PreStart(cwListElem * /*elem*/, csQuery * /*query*/)
{
   return true;
}

bool cwListCtl::onQuery1Started(cwListElem * /*elem*/, csQuery *query)
{
   // Einrichten der benutzerspezifischen Zusatzinformationen
   return setupUserData(query->getUserDataLen());
}

bool cwListCtl::onQuery1Data(cwListElem *elem, csQuery *query)
{
   if ( user_data_size > 0 )
      query->getUserData((char*)elem + user_data_offset, user_data_size);
   return true;
}

bool cwListCtl::onQuery1Ended(cwListElem * /*elem*/, csQuery * /*squery*/)
{
   return true;
}

void cwListCtl::onQuery1PostEnd(cwListElem * /*elem*/, csQuery * /*query*/)
{
}


// Einfuegeabfrage
// ---------------

bool cwListCtl::onInsQueryPreStart(cwListElem * /*elem*/, cwListElem * /*parent*/, csQuery * /*query*/)
{
   return true;
}

bool cwListCtl::onInsQueryStarted(cwListElem * /*before*/, cwListElem * /*parent*/, csQuery *query)
{
   // Einrichten der benutzerspezifischen Zusatzinformationen
   return setupUserData(query->getUserDataLen());
}

bool cwListCtl::onInsQueryData(cwListElem * /*before*/, cwListElem * /*parent*/, csQuery * /*query*/)
{
   return true;
}

bool cwListCtl::onInsQueryEnded(cwListElem * /*before*/, cwListElem * /*parent*/, csQuery * /*query*/)
{
   return true;
}

void cwListCtl::onInsQueryPostEnd(cwListElem * /*before*/, cwListElem * /*parent*/, csQuery * /*query*/)
{
}


// Erzeugen/Loeschen von Elementen
// -------------------------------

void cwListCtl::onCreatingElement(cwListElem * /*elem*/)
{
}

void cwListCtl::onDeletingElement(cwListElem * /*elem*/)
{
}


// Abfrage zum Element erfragen
// ----------------------------

csQuery * cwListCtl::onGetQueryOfElem(const cwListElem * /*elem*/, bool /*sub_query*/) const
{
   // Diese Funktion liefert diejenige Abfrage zurueck, die das Element
   // urspruenglich erzeugt hat, bzw. (wenn sub_query = true), diejenige
   // Abfrage, die die Kinder des Elementes erzeugt.

   // Normalerweise ist diese die Standard-Query des Controls:
   return getQuery();
}


// Spalteneinrichtung
// ------------------

int cwListCtl::onGetAddByteCount() const
{
   return user_data_size;
}

bool cwListCtl::onAllowsMultipleRows() const
{
   // Normale Controls erlauben nur eine Anzeigezeile pro Datensatz
   return false;
}

void cwListCtl::onSetupRowCol(const SETUP_ROWCOL_INFO& /*info*/)
{
}

void cwListCtl::onSetupField(int /*fld*/, const SETUP_FIELD_INFO& /*info*/)
{
}

void cwListCtl::onPostUserDataInit()
{
   // Jetzt koennen spezifische Einstellungen vorgenommen werden, die erst
   // *nach* der Einrichtung der benutzerspezifischen Daten moeglich sind.
}

void cwListCtl::onElemAttrChanged(cwListElem * /*elem*/, ELEM_ATTR /*attr*/)
{
}


// Verzoegerte Ausfuehrung
// =======================

void cwListCtl::onExecDelayed(int id, void *data)
{
   switch ( id ) {
   case ediEndEdit:
      {
         endEdit(!!data);
      }
      break;
   case ediNavigateEdit:
      {
         endEdit(false);
         EDIT_NAV *ena = (EDIT_NAV*)data;
         beginEdit(ena->next_elem, ena->next_fld);
         delete ena;
      }
      break;
   }

   cwControl::onExecDelayed(id, data);
}


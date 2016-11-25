// ===========================================================================
// es_filter.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csFilter           - Abstrakte Basisklasse fuer Query-Filter.
//           |
//           +-csFmtFilter     - Einfacher sprintf-Filter.
//           |
//           +-csDecodeFilter  - Decode-Filter.
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "store/es_filter.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csFilter
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csFilter : public csBaseStorage {
   ECL_DECLARE(csFilter,csBaseStorage)
   friend class csQuery;

public:

   // Copy-Konstruktor
   csFilter(const csFilter& other);


   // Filter-Funktionen
   // =================

   // Filtern eines Text-Wertes (liefert Text)
   inline void filter(const csQuery *query, cString& text) const
      { onFilterText(query, text); }
   // Filtern eines Schluesselwertes (liefert ein Icon)
   inline void filter(const csQuery *query, cString key, cIcon& icon) const
      { onFilterIcon(query, key, icon); }
   // Filtern eines Schluesselwertes (liefert eine Bitmap)
   inline void filter(const csQuery *query, cString key, cBitmap& bmp) const
      { onFilterBitmap(query, key, bmp); }

   // Ermittelt die Feldgroesse NACH der Filterung
   inline int calcSize(const csQuery *query, int size) const
      { return onCalcSize(query, size); }


   // Aufzaehlwerte
   // =============
   // Basiert ein Filter auf einer aufzaehlbaren Menge von Werten, koennen
   // diese erfragt werden. Damit kann z.B. eine Drop-Selektion basierend
   // auf den moeglichen Werten des Filters erstellt werden.

   // Anzahl moeglicher Werte liefern (0 falls kein Aufzaehltyp)
   inline int getValueCount() const
      { return onGetValueCount(); }
   // Wertepaar (Schluessel,Text) von Position 'idx' der Liste liefern
   inline bool getValue(int idx, cString& key, cString& text) const
      { return onGetValue(idx, key, text); }
   // Query erzeugen, welche die Aufzaehlwerte liefert (0 falls kein Aufzaehltyp)
   inline csQuery *makeValueQuery() const
      { return onMakeValueQuery(); }


protected:

   // Konstruktor (Protected)
   csFilter(int _flags = 0);


   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um einen Text-Wert zu filtern
   virtual void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um einen Schluesselwert in ein Icon umzuwandeln
   virtual void onFilterIcon(const csQuery *query, cString key, cIcon& icon) const;
   // Wird aufgerufen, um einen Schluesselwert in eine Bitmap umzuwandeln
   virtual void onFilterBitmap(const csQuery *query, cString key, cBitmap& bmp) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   virtual int onCalcSize(const csQuery *query, int size) const;

   // Wird aufgerufen, um die Anzahl moeglicher Aufzaehlwerte zu erfragen
   virtual int onGetValueCount() const;
   // Wird aufgerufen, um ein Wertepaar (Schluessel,Text) zu erfragen
   virtual bool onGetValue(int idx, cString& key, cString& text) const;
   // Wird aufgerufen, um eine Query ueber alle Aufzaehlwerte zu erzeugen
   virtual csQuery *onMakeValueQuery() const;

};

#endif /*__INTERFACE__*/


// Implementierung csFilter
// ===========================================================================

csFilter::csFilter(int _flags) :
   csBaseStorage(_flags)
{
}

csFilter::csFilter(const csFilter& other) :
   csBaseStorage(other)
{
}

void csFilter::onFilterText(const csQuery * /*query*/, cString& /*text*/) const
{
}

void csFilter::onFilterIcon(const csQuery * /*query*/, cString /*key*/, cIcon& icon) const
{
   icon = cIcon();
}

void csFilter::onFilterBitmap(const csQuery * /*query*/, cString /*key*/, cBitmap& bmp) const
{
   bmp = cBitmap();
}

int csFilter::onCalcSize(const csQuery * /*query*/, int size) const
{
   return size;
}

int csFilter::onGetValueCount() const
{
   return 0;
}

bool csFilter::onGetValue(int /*idx*/, cString& /*key*/, cString& /*text*/) const
{
   return false;
}

csQuery * csFilter::onMakeValueQuery() const
{
   class csFilterQuery : public csQuery {
      const csFilter *filter;
      int cur_idx, max_idx;
      cString key, name;
   public:
      csFilterQuery(const csFilter *flt)
         { filter = flt; cur_idx = 0;
           max_idx = flt->getValueCount(); }
   protected:
      bool onRewind()
         { cur_idx = 0;
           return true; }
      bool onFetch()
         { return filter->getValue(cur_idx, key, name); }
      bool onGetString(int fld, cString &buf) const
         { if ( fld == fldKey ) buf = key; else buf = name;
           return true; }
   };

   return getValueCount() > 0 ?
      new0 csFilterQuery(this)
    : 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition csFmtFilter
// ---------------------------------------------------------------------------
//
// Stellt einen einfachen Filter auf der Basis von sprintf zur Verfuegung.
// Der im Konstruktor uebergebene Formatstring muss genau ein '%s' enthalten.
// Beispiele: "%s DM", "(%s)", "x=%s"
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//          +--csFmtFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csFmtFilter : public csFilter {
   ECL_DECLARE(csFmtFilter,csFilter)

public:

   // Konstruktor
   csFmtFilter(cString _fmt, int _flags = 0);
   // Copy-Konstruktor
   csFmtFilter(const csFmtFilter& other);

protected:

   // Wird aufgerufen, um einen Text-Wert zu filtern
   void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   int onCalcSize(const csQuery *query, int size) const;

private:

   cString fmt;

};

#endif /*__INTERFACE__*/


// Implementierung cFmtFilter
// ===========================================================================

csFmtFilter::csFmtFilter(cString _fmt, int _flags) :
   csFilter(_flags)
{
   fmt = _fmt;
}

csFmtFilter::csFmtFilter(const csFmtFilter& other) :
   csFilter(other)
{
   fmt = other.fmt;
}

void csFmtFilter::onFilterText(const csQuery * /*query*/, cString& text) const
{
   if ( fmt.getLength() > 0 )
      text = cStringf(fmt, (const char *)text);
}

int csFmtFilter::onCalcSize(const csQuery * /*query*/, int size) const
{
   return size + fmt.getLength();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition csDecodeFilter
// ---------------------------------------------------------------------------
//
// ACHTUNG: Wird der csDecodeFilter ueber ein Query-Objekt konstruiert, muss
//          letzteres das "Permanent"-Flag gesetzt haben!
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//          +--csDecodeFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csDecodeFilter : public csFilter, public cEventTarget {
   ECL_DECLARE(csDecodeFilter,csFilter)

public:

   // Konstruktion ueber Query-Abfrage
   csDecodeFilter(csQuery *query, int flags = 0);
   // Konstruktion ueber Encoded Keys
   csDecodeFilter(const char *str1, ...);
   // Konstruktion ueber Encoded Keys (+ Flags)
   csDecodeFilter(int flags, const char *str1, ...);
   // Copy-Konstruktor
   csDecodeFilter(const csDecodeFilter& other);
   // Destruktor
   virtual ~csDecodeFilter();


   // Flags
   // =====

   enum FLAGS { fStart = csFilter::fUser,
      fEncodedKeys = fStart << 0,  // Schluessel in Enums kodiert: "key$name"
      fShowKeys    = fStart << 1,  // Schluessel mit anzeigen, Format: "key (name)"
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


protected:

   // Wird aufgerufen, um einen Text-Wert zu filtern
   void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   int onCalcSize(const csQuery *query, int size) const;

   // Wird aufgerufen, um die Anzahl moeglicher Aufzaehlwerte zu erfragen
   int onGetValueCount() const;
   // Wird aufgerufen, um ein Wertepaar (Schluessel,Text) zu erfragen
   bool onGetValue(int idx, cString& key, cString& text) const;


private:

   struct NODE {
      NODE(int _key, const char *_name, bool _encoded_keys);
      NODE(const char *_key, const char *_name);
      char key[12];
      cString name;
      NODE *next;
   };

   NODE *anchor, *last;
   int max_name_size;

   void init(csQuery *query);
   void init(const char *str1, va_list arg_ptr);
   void deleteNodes();

   int onQueryEvent(void *p1, int p2);

};

#endif /*__INTERFACE__*/


// Implementierung csDecodeFilter
// ===========================================================================

csDecodeFilter::csDecodeFilter(csQuery *query, int flags) :
   csFilter(flags)
{
   init(query);
}

csDecodeFilter::csDecodeFilter(const char *str1, ...) :
   csFilter(fEncodedKeys)
{
   va_list arg_ptr;

   va_start(arg_ptr, str1);
   init(str1, arg_ptr);
   va_end(arg_ptr);
}

csDecodeFilter::csDecodeFilter(int flags, const char *str1, ...) :
   csFilter(flags|fEncodedKeys)
{
   va_list arg_ptr;

   va_start(arg_ptr, str1);
   init(str1, arg_ptr);
   va_end(arg_ptr);
}

csDecodeFilter::csDecodeFilter(const csDecodeFilter& other) :
   csFilter(other)
{
   max_name_size = other.max_name_size;

   anchor = last = 0;

   // Kopie der Knoten-Liste von 'other' erstellen
   NODE **node_ptr = &anchor;
   for ( NODE *node = other.anchor ; node ; node = node->next ) {
      *node_ptr = new0 NODE(node->key, node->name);
      node_ptr = &(*node_ptr)->next;
   }
}

csDecodeFilter::~csDecodeFilter()
{
   deleteNodes();
}

void csDecodeFilter::init(csQuery *query)
{
   max_name_size = 0;
   anchor = last = 0;

   if ( query )
      query->start(csQuery::EVENT(this, (EVFUNC_RPI)onQueryEvent));
}

int csDecodeFilter::onQueryEvent(void *p1, int p2)
{
   csQuery *query = (csQuery*)p1;
   cString key, name;
   NODE *act;

   switch ( (csQuery::STATE)p2 ) {

   case csQuery::qsStart:
      deleteNodes();
      max_name_size = 0;
      last = 0;
      break;

   case csQuery::qsData:
      query->get(csQuery::fldKey, key);
      query->get(csQuery::fldName, name);

      act = new0 NODE(key, name);

      if ( act->name.getLength() + 1 > max_name_size )
         max_name_size = act->name.getLength() + 1;
      if ( !anchor )
         anchor = act;
      if ( last )
         last->next = act;

      last = act;
      return true;

   case csQuery::qsEnd:
      break;

   }

   return 0;
}

void csDecodeFilter::init(const char *str1, va_list arg_ptr)
{
   const char *str = str1;
   NODE *act, *last = 0;
   int count = 0;

   max_name_size = 0;
   anchor = 0;

   do {
      act = new0 NODE(count++, str, !!getFlags(fEncodedKeys));

      if ( act->name.getLength() + 1 > max_name_size )
         max_name_size = act->name.getLength() + 1;

      if ( !anchor )
         anchor = act;
      if ( last )
         last->next = act;
      last = act;
   } while ( (str = va_arg(arg_ptr, const char *)) != 0 );
}

csDecodeFilter::NODE::NODE(int _key, const char *_name, bool _encoded_keys)
{
   char *pname;

   if ( _encoded_keys && (pname = strchr(_name, '$')) != 0 ) {
      name = pname + 1;
      strxcpy(key, _name, sizeof key);
      if ( (pname = strchr(key, '$')) != 0 )
         *pname = '\0';
   } else {
      sprintf(key, "%d", _key);
      name = _name;
   }

   next = 0;
}

csDecodeFilter::NODE::NODE(const char *_key, const char *_name)
{
   strxcpy(key, _key, sizeof key);
   name = _name;
   next = 0;
}

void csDecodeFilter::deleteNodes()
{
   NODE *next, *node = anchor;

   while ( node ) {
      next = node->next;
      delete node;
      node = next;
   }

   anchor = 0;
}

void csDecodeFilter::onFilterText(const csQuery * /*query*/, cString& text) const
{
   for ( NODE *node = anchor ; node ; node = node->next ) {
      if ( text.compare(node->key) == 0 ) {
         if ( getFlags(fShowKeys) ) {
            text = cString(node->key) + " (" + node->name + ")";
         } else {
            text = node->name;
         }
         return;
      }
   }
}

int csDecodeFilter::onCalcSize(const csQuery * /*query*/, int /*size*/) const
{
   return max_name_size;
}

int csDecodeFilter::onGetValueCount() const
{
   int count = 0;

   for ( NODE *node = anchor ; node ; node = node->next )
      count++;

   return count;
}

bool csDecodeFilter::onGetValue(int idx, cString& key, cString& text) const
{
   int count = 0;

   for ( NODE *node = anchor ; node ; node = node->next ) {
      if ( count++ == idx ) {
         key = node->key;
         text = node->name;
         return true;
      }
   }

   return false;
}


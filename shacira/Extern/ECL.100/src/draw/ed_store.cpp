// ===========================================================================
// ed_store.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdStorage              - Basisklasse fuer Storage-Klassen
//         |
//         +--cdDeviceStore      - "Gedaechtnis" fuer cdDevice-Operationen
//         |
//         +--cdSpaceStore       - "Gedaechtnis" fuer cdSpace-Operationen
//
// ===========================================================================

#include "draw/ed_store.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "draw/ed_base.hpp"
#include "draw/ed_matrix.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdStorage
// ---------------------------------------------------------------------------
//
// "Gedaechtnis" fuer elementare Grafikoperationen
// TBD: Gemeinsamkeiten besser in Basisklasse integrieren
//
//  cBase
//   +--cdStorage
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdStorage : public cBase {

public:
   inline cdStorage(int max_elems = 50) { init(max_elems); }
   virtual ~cdStorage();

protected:
   int max_elems;   // Max. Anzahl Elemente in einem Chunk
   int act_elem_idx;   // Index des naechsten freien Elements in act_chunk

private:
   void init(int max_elems);

};

#endif /*__INTERFACE__*/


// Implementierung cdStorage
// ===========================================================================

void cdStorage::init(int max_elems)
{
   act_elem_idx = 0;
   cdStorage::max_elems = max_elems;
}

cdStorage::~cdStorage()
{
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdDeviceStore
// ---------------------------------------------------------------------------
//
// "Gedaechtnis" fuer elementare Grafikoperationen
//
//  +----+--------+       +----+--------+       +----+--------+   -+
//  | O1 |        |   +-->|On+1|        |   +-->|Om+1|        |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    |
//  | O2 |        |   |   |On+2|        |   |   |Om+2|        |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    \
//  :    :        :   |   :    :        :   |   :    :        :     + max_elems
//  +----+--------+   |   +----+--------+   |   +----+--------+    /
//  | On |        |   |   |On+m|        |   |   |LAST|  NULL  |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    |
//  |NEXT|   X----+---+   |NEXT|   X----+---+   |  <unused>   |    |
//  +----+--------+       +----+--------+       +----+--------+   -+
//  Chunk 0               Chunk 1               Chunk i
//
//  cBase
//   +--cdStorage
//       +--cdDeviceStore
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdDeviceStore : public cdStorage {

public:
   inline cdDeviceStore(int max_elems = 50) : cdStorage(max_elems) { init(); }
   ~cdDeviceStore();

   enum ELEM_CMDS {
      ecLast = 0,             // Kennzeichnet letztes Element im letzten Chunk
      ecNext,                 // Zeiger auf erstes Element im naechsten Chunk
      ecNop,                  // Keine Operation
      ecMoveTo,               // moveTo
      ecDrawLine,             // drawLine
      ecDrawCircle,           // drawCircle
      ecDrawEllipse,          // drawEllipse
      ecDrawRect,             // drawRect
      ecDrawArcCW,            // drawArcCW
      ecDrawArcCCW,           // drawArcCCW
      ecDrawText,             // drawText
      ecBeginArea,            // beginArea
      ecEndArea,              // endArea
      ecSetRect,              // setRect
      ecSetXRect,             // setXRect
      ecSetColor,             // setColor
      ecSetBackColor,         // setBackColor
      ecSetFillColor,         // setFillColor
      ecSetFillPattern,       // setFillPattern
      ecSetLineStyle,         // setLineStyle
      ecSetLineWidth,         // setLineWidth
      ecSetPattern,           // setPattern
      ecSetForeMix,           // setForeMix
      ecSetBackMix,           // setBackMix
      ecSelectFont,           // selectFont
      ecDeleteFont,           // deletefont
      ecSetTextAlign,         // setTextAlign
      ecSetTextAngle,         // setTextAngle
      ecEnd
   };

   enum ELEM_FLAGS {
      efFreeText  = 1 << 0,   // Param. 1 ist Zeiger auf freizugebenden String
      efBoundary  = 1 << 1    // Kanten der gefuellten Flaeche zeichnen
   };

   struct ELEM {
      short cmd;              // Auszufuehrendes Kommando
      short flags;            // Zusaetzliche Flags
      union {                 // 1. Parameter:
         long x;              //    x-Koordinate
         long val1;           //    Erster Wert
         ELEM *next;          //    Zeiger auf naechsten Chunk
         char *text;          //    Zeiger auf Textstring
      };
      union {                 // 2. Parameter:
         long y;              //    y-Koordinate
         long val2;           //    Zweiter Wert
      };
      union {                 // 3. Parameter:
         long x2;             //    Zweite x-Koordinate
         long val3;           //    Dritter Wert
      };
      union {                 // 4. Parameter:
         long y2;             //    Zweite y-Koordinate
         long val4;           //    Vierter Wert
      };
   };

   ELEM *newElem();
   ELEM *firstElem() const;

private:
   ELEM *first_chunk;   // Erster angelegter Chunk
   ELEM *act_chunk;   // Zuletzt beschriebener Chunk

   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cdDeviceStore
// ===========================================================================

void cdDeviceStore::init()
{
   first_chunk = act_chunk = NULL;
}

cdDeviceStore::~cdDeviceStore()
{
   ELEM *act = first_chunk;

   /*#define _DebugDestructor_*/
   #ifdef _DebugDestructor_
      fprintf(stderr, "----- cdDeviceStore - Dump -----\n");
      for ( ELEM *p = first_chunk ; p ; ) {
         for ( int i=0 ; i<max_elems ; i++ ) {
            fprintf(stderr, "%3d: %04x %04x | %08x | %08x\n",
               i, p[i].cmd, p[i].flags, p[i].x, p[i].y);
         }
         p = p[max_elems-1].cmd == ecNext ? p[max_elems-1].next : NULL;
      }
   #endif

   while ( act ) {
      ELEM *to_delete = act;
      while ( act->cmd > ecNext ) {
         if ( act->flags ) {
            if ( act->flags & efFreeText )
               delete[] act->text;
         }
         act++;
      }

      #ifdef _DebugDestructor_
         if ( act->next && act->next->cmd >= ecEnd )
            DbgError("cdDeviceStore: Fatal error in destructor");
      #endif

      act = act->next;
      delete to_delete;
   }
}

cdDeviceStore::ELEM *cdDeviceStore::newElem()
{
   if ( !act_chunk || act_elem_idx >= max_elems-1 ) {
      // Chunk anlegen und vollstaendig mit Nullen initialisieren.
      // Dadurch ist jedes Element automatisch mit ecLast vorini-
      // tialisiert, Alle Flags sind rueckgesetzt und alle Zeiger
      // NULL.
      ELEM *new_chunk = new0 (ELEM[max_elems]);
      if ( new_chunk )
         memset(new_chunk, 0, max_elems * sizeof(ELEM));

      if ( act_chunk ) {
         act_chunk[max_elems-1].cmd = ecNext;
         act_chunk[max_elems-1].next = new_chunk;
      }

      if ( !first_chunk )
         first_chunk = new_chunk;
      act_chunk = new_chunk;
      act_elem_idx = 0;
   }

   // Loeschen nicht mehr noetig, da beim Anlegen des Chunks dieser
   // bereits mit Nullen vorinitialisiert wird...
   // act_chunk[act_elem_idx].cmd = ecLast;
   // act_chunk[act_elem_idx].next = NULL;
   // act_chunk[act_elem_idx].flags = 0;
   return &act_chunk[act_elem_idx++];
}

cdDeviceStore::ELEM *cdDeviceStore::firstElem() const
{
   return first_chunk;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdSpaceStore
// ---------------------------------------------------------------------------
//
// "Gedaechtnis" fuer elementare Grafikoperationen
//
//  +----+--------+       +----+--------+       +----+--------+   -+
//  | O1 |        |   +-->|On+1|        |   +-->|Om+1|        |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    |
//  | O2 |        |   |   |On+2|        |   |   |Om+2|        |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    \
//  :    :        :   |   :    :        :   |   :    :        :     + max_elems
//  +----+--------+   |   +----+--------+   |   +----+--------+    /
//  | On |        |   |   |On+m|        |   |   |LAST|  NULL  |    |
//  +----+--------+   |   +----+--------+   |   +----+--------+    |
//  |NEXT|   X----+---+   |NEXT|   X----+---+   |  <unused>   |    |
//  +----+--------+       +----+--------+       +----+--------+   -+
//  Chunk 0               Chunk 1               Chunk i
//
//  cBase
//   +--cdStorage
//       +--cdSpaceStore
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdSpaceStore : public cdStorage {

public:
   inline cdSpaceStore(int max_elems = 50) : cdStorage(max_elems) { init(); }
   ~cdSpaceStore();

   enum ELEM_CMDS {
      ecLast = 0,                   // Kennzeichnet letztes Element im letzten Chunk
      ecNext,                       // Zeiger auf erstes Element im naechsten Chunk
      ecNop,                        // Keine Operation
      ecMoveTo,                     // moveTo
      ecDrawLine,                   // drawLine
      ecDrawLineSeg,                // drawLineSeg
      ecDrawCircle,                 // drawCircle
      ecDrawArc,                    // drawArc
      ecDrawBox,                    // drawBox
      ecDrawText,                   // drawText
      ecBeginArea,                  // beginArea
      ecEndArea,                    // endArea
      ecSetColor,                   // setColor
      ecSetBackColor,               // setBackColor
      ecSetFillColor,               // setFillColor
      ecSetFillPattern,             // setFillPattern
      ecSetLineStyle,               // setLineStyle
      ecSetLineWidth,               // setLineWidth
      ecSetPattern,                 // setPattern
      ecSetForeMix,                 // setForeMix
      ecSetBackMix,                 // setBackMix
      ecSelectFont,                 // selectFont
      ecDeleteFont,                 // deletefont
      ecSetTextAlign,               // setTextAlign
      ecSetTextAngle,               // setTextAngle
      ecTransformSet,               // setTransform(cdMatrix)
      ecTransformReset,             // resetTransform()
      ecTransformScale,             // scale(sx,sy)
      ecTransformTransl,            // translate(dx,dy)
      ecTransformRotate,            // rotate(sin,cos)
      ecEnd
   };

   enum ELEM_FLAGS {
      efFreeText  = 1 << 0,         // Param. 1 ist Zeiger auf freizugebenden String
      efFreeDbl   = 1 << 1,         // Param. 1 ist Zeiger auf freizugebendes double-Array
      efFreeTMat  = 1 << 2,         // Param. 1 ist Zeiger auf freizugebendes cdMatrix-Objekt
      efBoundary  = 1 << 3,         // Kanten der gefuellten Flaeche zeichnen
      efArcCW     = 1 << 4          // Kreisbogen CW (Standard: CCW)
   };

   struct ELEM {
      short cmd;                    // Auszufuehrendes Kommando
      short flags;                  // Zusaetzliche Flags
      union {                       // 1. Parameter:
         double x1;                 //    x-Koordinate
         long val1;                 //    Erster Wert
         long col;                  //    Farbwert (os_val)
         cdLineStyle::LINESTYLE ls; //    Linienstil
         cdPattern::PATTERN pat;    //    Pattern
         cdMix::MIX mix;            //    Mix-Wert
         cdAlign::ALIGN align1;     //    Erster Align-Wert
         ELEM *next;                //    Zeiger auf naechsten Chunk
         char *text;                //    Zeiger auf Textstring
         double *dbl;               //    Zeiger auf double-Array
         cdMatrix *tmat;            //    Zeiger auf cdMatrix-Objekt
      };
      union {                       // 2. Parameter:
         double y1;                 //    y-Koordinate
         long val2;                 //    Zweiter Wert
         cdAlign::ALIGN align2;     //    Zweiter Align-Wert
      };
      union {                       // 3. Parameter:
         double x2;                 //    Zweite x-Koordinate
         long val3;                 //    Dritter Wert
      };
      union {                       // 4. Parameter:
         double y2;                 //    Zweite y-Koordinate
         long val4;                 //    Vierter Wert
      };
   };

   ELEM *newElem();
   ELEM *firstElem() const;

private:
   ELEM *first_chunk;   // Erster angelegter Chunk
   ELEM *act_chunk;   // Zuletzt beschriebener Chunk

   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cdSpaceStore
// ===========================================================================

void cdSpaceStore::init()
{
   first_chunk = act_chunk = NULL;
}

cdSpaceStore::~cdSpaceStore()
{
   ELEM *act = first_chunk;

   /*#define _DebugDestructor_*/
   #ifdef _DebugDestructor_
      fprintf(stderr, "----- cdSpaceStore - Dump -----\n");
      for ( ELEM *p = first_chunk ; p ; ) {
         for ( int i=0 ; i<max_elems ; i++ ) {
            fprintf(stderr, "%3d: %04x %04x | %08x | %08x\n",
               i, p[i].cmd, p[i].flags, p[i].x, p[i].y);
         }
         p = p[max_elems-1].cmd == ecNext ? p[max_elems-1].next : NULL;
      }
   #endif

   while ( act ) {
      ELEM *to_delete = act;
      while ( act->cmd > ecNext ) {
         if ( act->flags ) {
            if ( act->flags & efFreeText )
               delete[] act->text;
            if ( act->flags & efFreeDbl )
               delete[] act->dbl;
            if ( act->flags & efFreeTMat )
               delete act->tmat;
         }
         act++;
      }

      #ifdef _DebugDestructor_
         if ( act->next && act->next->cmd >= ecEnd )
            DbgError("cdSpaceStore: Fatal error in destructor");
      #endif

      act = act->next;
      delete to_delete;
   }
}

cdSpaceStore::ELEM *cdSpaceStore::newElem()
{
   if ( !act_chunk || act_elem_idx >= max_elems-1 ) {
      // Chunk anlegen und vollstaendig mit Nullen initialisieren.
      // Dadurch ist jedes Element automatisch mit ecLast vorini-
      // tialisiert, Alle Flags sind rueckgesetzt und alle Zeiger
      // NULL.
      ELEM *new_chunk = new0 (ELEM[max_elems]);
      if ( new_chunk )
         memset(new_chunk, 0, max_elems * sizeof(ELEM));

      if ( act_chunk ) {
         act_chunk[max_elems-1].cmd = ecNext;
         act_chunk[max_elems-1].next = new_chunk;
      }

      if ( !first_chunk )
         first_chunk = new_chunk;
      act_chunk = new_chunk;
      act_elem_idx = 0;
   }

   // Loeschen nicht mehr noetig, da beim Anlegen des Chunks dieser
   // bereits mit Nullen vorinitialisiert wird...
   // act_chunk[act_elem_idx].cmd = ecLast;
   // act_chunk[act_elem_idx].next = NULL;
   // act_chunk[act_elem_idx].flags = 0;
   return &act_chunk[act_elem_idx++];
}

cdSpaceStore::ELEM *cdSpaceStore::firstElem() const
{
   return first_chunk;
}



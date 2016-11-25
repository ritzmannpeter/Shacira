/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [hmap.c]                   Type: Finite Map                              */
/*             Endliche Abbildungen mittels dynamischen Hashing             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "prim.h"

/*!!
   [hmap] implements finite maps based on dynamic hashing.
*/

/*I------------------------- Types and macros ------------------------------ */

#define NOTE(C) bug0(C,"internal error")

AbstractType( HMP_Dom );                   /* Abstract domain type of maps  */
AbstractType( HMP_Rng );                   /* Abstract range type of maps   */

/*DOC_INTERFACE*/
#define MAP(Alpha,Beta)   HMP_Map          /* Polymorphic MAP - Type        */
#define MAPIT             HMP_Itr          /* Polymorphic ITR - Type        */
#define MAPTY             HMP_Typ          /* Polymorphic meta-type of MAPs */

ExternalType( HMP_Typ )                    /* Abstract meta-type of maps    */
/* "Klasse" der Abbildungen */
{
  HMP_Dom (*domcpy)(HMP_Dom a);            /* copies a domain        */
  void    (*domfre)(HMP_Dom a);            /* frees  a domain        */
  bool    (*domequ)(HMP_Dom a, HMP_Dom b); /* equality on domains    */
  long    (*domhsh)(HMP_Dom a);            /* hash value of domain   */
  HMP_Rng (*rngcpy)(HMP_Rng a);            /* copies a range         */
  void    (*rngfre)(HMP_Rng a);            /* frees  a range         */
};

/*INTERFACE*/
ConcreteType( HMP_Ent ) 
/* interner Typ; Kette der Defintionen mit gleichem Hash-Wert */
{
  HMP_Ent /* var */ next;
  long    /* con */ hash;   /* hash == home->T->hash(&elem) */
  HMP_Dom /* con */ key ;
  HMP_Rng /* var */ info;
};

/*INTERFACE*/
typedef HMP_Ent __HUGE *HMP_Tab; /* interner Typ; das hash-array */

ExternalType( HMP_Map )                    /* Abstract type of maps          */
{
  /* constant */
  HMP_Typ T;
  /* variable */
  long    Version;     /* Anzahl der Aenderungen im Hash-Set       */
                       /* modulo 2^(8*sizeof(long))                */
  long    L;           /* 0 <= L <  small_size                     */
                       /* Position fuer die naechste Umspeicherung */
  long    small_size;  /* 2^N; 0 <= N                              */
  HMP_Tab small_table; /* [small_size]                             */
                       /* Belegung: [L .. small_size-1]            */
  long    large_size;  /* 2^(N+1)                                  */
  HMP_Tab large_table; /* [large_size]                             */
                       /* Belegung: [small_size .. small_size+L-1] */
};

/*I------------------------- Meta type of hash maps ------------------------ */

HMP_Typ HMP_newTyp
        (                                          /* function parameter:    */
          HMP_Dom (*domcpy)(HMP_Dom a),            /* copies a domain        */
          void    (*domfre)(HMP_Dom a),            /* frees  a domain        */
          bool    (*domequ)(HMP_Dom a, HMP_Dom b), /* equality on domains    */
          long    (*domhsh)(HMP_Dom a),            /* hash value of domain   */
          HMP_Rng (*rngcpy)(HMP_Rng a),            /* copies a range         */
          void    (*rngfre)(HMP_Rng a)             /* frees  a range         */
        )
#define MAP_newTyp(dc, df, de, dh, rc, rf)                 \
        HMP_newTyp(                                        \
                    (HMP_Dom (*)(HMP_Dom a))           dc, \
                    (void    (*)(HMP_Dom a))           df, \
                    (bool    (*)(HMP_Dom a,HMP_Dom b)) de, \
                    (long    (*)(HMP_Dom a))           dh, \
                    (HMP_Rng (*)(HMP_Rng a))           rc, \
                    (void    (*)(HMP_Rng a))           rf  \
                  )
/** defines a new hash type */
{ HMP_Typ t = New(HMP_Typ);
  t->domcpy = domcpy;
  t->domfre = domfre;
  t->domequ = domequ;
  t->domhsh = domhsh;
  t->rngcpy = rngcpy;
  t->rngfre = rngfre;
  return (HMP_Typ)t;
}

void HMP_freeTyp( HMP_Typ t )
#define MAP_freeTyp HMP_freeTyp
/* frees hash type 't' */
{
  FreeMem( t );
}

/* ------------------------------- accessing ------------------------------ */

HMP_Dom (*HMP_domcpy(HMP_Typ t))(HMP_Dom a)
#define MAP_domcpy(Alpha,t) ((Alpha (*)(Alpha a))          HMP_domcpy(t))
/* get domain copy function of hash type 't' */
{
  return t->domcpy;
}

void (*HMP_domfre(HMP_Typ t))(HMP_Dom a)
#define MAP_domfre(Alpha,t) ((void  (*)(Alpha a))          HMP_domfre(t))
/* get domain free function of hash type 't' */
{
  return t->domfre;
}

bool (*HMP_domequ(HMP_Typ t))(HMP_Dom a, HMP_Dom b)
#define MAP_domequ(Alpha,t) ((bool  (*)(Alpha a, Alpha b)) HMP_domequ(t))
/* get domain equal function of hash type 't' */
{
  return t->domequ;
}

long (*HMP_domhsh(HMP_Typ t))(HMP_Dom a)
#define MAP_domhsh(Alpha,t) ((long  (*)(Alpha a))          HMP_domhsh(t))
/* get domain hash function of hash type 't' */
{
  return t->domhsh;
}

HMP_Rng (*HMP_rngcpy(HMP_Typ t))(HMP_Rng a)
#define MAP_rngcpy(Beta ,t) ((Beta  (*)(Beta  a))          HMP_rngcpy(t))
/* get range copy function of hash type 't' */
{
  return t->rngcpy;
}

void (*HMP_rngfre(HMP_Typ t))(HMP_Rng a)
#define MAP_rngfre(Beta ,t) ((void  (*)(Beta  a))          HMP_rngfre(t))
/* get range free function of hash type 't' */
{
  return t->rngfre;
}

static void initHashTables(HMP_Map m)
{
  /* 0) Version     */
  m->Version        = 0;
  /* 1) pointer     */
  m->L              = 0;
  /* 2) small table */
  m->small_size     = 1;
  m->small_table    = (HMP_Tab) NewHMem(m->small_size * sizeof(HMP_Dom));
  m->small_table[0] = (HMP_Ent) NULL;
  /* 3) large table */
  m->large_size     = m->small_size << 1;
  m->large_table    = (HMP_Tab) NewHMem(m->large_size * sizeof(HMP_Dom));
}

static HMP_Ent *TableSlot(long h, HMP_Map m)
{
  return ((h & (m->small_size - 1)) < m->L)
       ? (HMP_Ent*)(&m->large_table[h & (m->large_size - 1)])
       : (HMP_Ent*)(&m->small_table[h & (m->small_size - 1)]);
}

static HMP_Ent *EntryLoc(HMP_Map m, /* using m->T->equal       */
                         HMP_Dom d, /* for Dom d               */
                         long    h) /* h = (*m->T->domhsh)(e)  */
/* BUG(h == (*m->T->domhsh)(e)) */
{ HMP_Ent *x;
  for ( x = TableSlot(h,m); *x != (HMP_Ent) NULL; x = &(*x)->next )
    /* wird im Mittel weniger als 1.0 mal durchlaufen */
    if ( h == (*x)->hash &&
         /* beachte, dass m->T->domequ nur im unwahrscheinlichen */
         /* Fall einer Kollision des Hash-Wert (1/4.000.000.000) */
         /* aufgerufen wird.                                     */
         (*m->T->domequ)(d, (*x)->key) )
      break;
  return x;
}

/* Quality Monitor: Da Fehler in Hash-Funktionen ebenso aergerlich,       */
/* wie schwer zu bemerken sind, wird an dieser Stelle eine Qualitaets-    */
/* ueberwachung, durchgefuehrt. Nach jeder Operation, die eine Kette      */
/* verlaengert (combineTableSlots und addEntry), wird daher die           */
/* neue Kettenlaenge ermittelt. Wird dabei eine Grenzlaenge erreicht oder */
/* ueberschritten, dann erfolgt eine Warnung und die Grenzlaenge wird     */
/* verdoppelt, um zu verhindern, dass zuviele nachfolgende Warnungen      */
/* produziert werden.                                                     */
/* Die Grenzlaenge betraegt zunaechst 16. Diese Zahl sollte nicht herauf- */
/* gesetzt werden, da ihr Erreichen bei einer korrekten Implementation    */
/* statistisch ausgeschlossen sein sollte.                                */

static long QualityLimit = 16; /* do not modify here, but find the bug!  */

static void QualityMonitor(HMP_Ent e)
{ long Length = 0;
  for ( ; e != NULL; e = e->next )
    /* wird im Mittel 1.5 mal durchlaufen. */
    Length += 1;
  if (Length >= QualityLimit)
  {
    fprintf(STDERR,"\n\n[Hash Set Quality Monitor Diagnose]\n!\n!");
    fprintf(STDERR,"  Eine Hash-Funktion erzeugt keine gleichverteilten");
    fprintf(STDERR," Werte,\n!");
    fprintf(STDERR,"  da eine Kette der Laenge %ld auftrat.\n!\n", Length);
    fprintf(STDERR,"[See file \'%s\', line %d]\n\n",__FILE__,__LINE__);
    QualityLimit *= 2;
  }
}

/* increasing and decreasing table sizes */

static void increaseTableSize(HMP_Map m)
{
  bug0( (m->large_size << 1) > 0,
        "implementationsabhaengiger Maximalwert fuer long ueberschritten");
  FreeHMem( m->small_table );
  m->small_size  = m->large_size;
  m->small_table = m->large_table;
  m->large_size  = m->large_size << 1;
  m->large_table = (HMP_Ent*)NewHMem( sizeof(HMP_Ent)*m->large_size );
  m->L           = 0;
}

static void decreaseTableSize(HMP_Map m)
{
  NOTE( m->small_size > 1 );
  FreeHMem( m->large_table );
  m->large_size  = m->small_size;
  m->large_table = m->small_table;
  m->small_size  = m->small_size >> 1;
  m->small_table = (HMP_Ent*)NewHMem( sizeof(HMP_Ent)*m->small_size );
  m->L           = m->small_size;
}

/* spliting and combining table slots */

static void splitTableSlot(HMP_Map m)
/* distribute m->small_table[m->L]
         into m->large_table[m->L]
          and m->large_table[m->L+m->small_size] */
{ HMP_Ent x = m->small_table[m->L];
  /* init large_table slots */
  m->large_table[m->L]               = NULL;
  m->large_table[m->L+m->small_size] = NULL;
  while (x != NULL)
  /* wird im Mittel 1.25 mal durchlaufen */
  { HMP_Ent  e = x;
    /* beachte, dass die Hash-Werte nicht neu berechnet werden */
    HMP_Ent *p = (HMP_Ent*)(&m->large_table[x->hash & (m->large_size-1)]);
    x = e->next; e->next = *p; *p = e;
  }
}

static void combineTableSlots(HMP_Map m)
/* combine m->large_table[m->L]
       and m->large_table[m->L+m->small_size]
      into m->small_table[m->L] */
{ HMP_Ent *x;
  NOTE( m->L >= 0 );
  m->small_table[m->L] = m->large_table[m->L];
  for (x = (HMP_Ent*)(&m->small_table[m->L]); *x != NULL; x = &(*x)->next)
    /* wird im Mittel 0.75 mal durchlaufen */
    ;
  *x = m->large_table[m->L+m->small_size];
  QualityMonitor(m->small_table[m->L]);
}

static void addTableSlot(HMP_Map m)
{
  splitTableSlot(m);
  NOTE( m->L < m->small_size );
  m->L += 1;
  if (m->L == m->small_size)
    increaseTableSize(m);
}

static void rmvTableSlot(HMP_Map m)
{
  NOTE( m->small_size > 1 );
  if (m->L == 0)
    decreaseTableSize(m);
  NOTE( m->L > 0 );
  m->L -= 1;
  combineTableSlots(m);
}

/* adding and removing entries from a hash set at the correct slot position */

static void addEntry(HMP_Ent  *slot,
                     HMP_Map   home,
                     HMP_Dom   key,
                     long      hash,
                     HMP_Rng   info)
/* */
{
  bug0( *slot == NULL, "attempt to add an element which is already a member");
  *slot = New( HMP_Ent );
  (*slot)->next = NULL;
  (*slot)->key  = (*home->T->domcpy)(key);
  (*slot)->hash = hash;
  (*slot)->info = (*home->T->rngcpy)(info);
  QualityMonitor(*TableSlot(hash,home));
}

static void updEntry(HMP_Map home, HMP_Ent entry, HMP_Rng info)
/* */
{
  (*home->T->rngfre)(entry->info);
  entry->info = (*home->T->rngcpy)(info);
}

static void rmvEntry(HMP_Map home, HMP_Ent *slot)
/* */
{ HMP_Ent entry = *slot;
  NOTE( entry != (HMP_Ent) NULL );
  *slot = entry->next;
  (*home->T->domfre)(entry->key);
  (*home->T->rngfre)(entry->info);
  FreeMem( entry );
}

/* clearing and droping */

static void freeEntryList(HMP_Map m, HMP_Ent *e)
/* */
{
  while(*e != NULL)
    rmvEntry(m,e);
}

static void freeTables(HMP_Map m)
/* frees all HMP_Entries in m; used by "HMP_rmvall" and "HMP_freeMap" */
{ long i;
  for (i = m->L; i < m->small_size; i++)
    freeEntryList(m, &m->small_table[i]);
  FreeHMem(m->small_table);
  for (i = 0; i < m->L; i++)
  {
    freeEntryList(m, &m->large_table[i]);
    freeEntryList(m, &m->large_table[m->small_size+i]);
  }
  FreeHMem(m->large_table);
}

/*I=============================== Hash Maps ============================== */

/*I-------------------------- Creating & Disposing ------------------------ */

HMP_Map HMP_newMap( HMP_Typ t )
#define MAP_newMap  HMP_newMap
/* creates a new empty map */
{ HMP_Map res  = New( HMP_Map );
  res->T       = t;
  res->Version = 0;
  initHashTables(res);
  return (HMP_Map)res;
}

void HMP_freeMap(HMP_Map m)
#define MAP_freeMap HMP_freeMap
/* removes map 'm' from storage
   all references to 'm' are invalidated! 
*/
{
  freeTables(m);
  FreeMem(m);
}

/*I------------------------------- Accessing ------------------------------ */

HMP_Typ HMP_MapTyp(HMP_Map m)
#define MAP_MapTyp HMP_MapTyp
/* get meta-type of map 'm' */
{
  return m->T;
}

long HMP_count(HMP_Map m)
#define MAP_count HMP_count
/* number of domain values on which map 'm' is defined 
   HMP_count(m) == | { d in HMP_Dom | HMP_defined(m,d) } | 
*/
{
  return (m->L + m->small_size) - 1;
}

bool HMP_emptyMap(HMP_Map m)
#define MAP_emptyMap HMP_emptyMap
/* whether map 'm' is empty
   HMP_emptyMap(m) == (HMP_count(m) == 0) 
*/
{
  return m->small_size == 1;
}

bool HMP_defined(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_defined(m,d) HMP_defined(m,(HMP_Dom)(d))
/* whether domain 'd' is defined in map 'm' */
{ 
  return *EntryLoc(m,d,(*m->T->domhsh)(d)) != (HMP_Ent) NULL;
}

HMP_Rng HMP_apply(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_apply(Beta,m,d)       ABS_CAST(Beta,HMP_apply(m,(HMP_Dom)(d)))
#define MAP_apply_small(Beta,m,d) ((Beta)((long)HMP_apply(m,(HMP_Dom)(d))))
#define MAP_apply_short(m,d)      ((short)((long)HMP_apply(m,(HMP_Dom)(d))))
/* get range of domain 'd' in map 'm'
   raises execption if not HMP_defined(m,d) 
*/
{ HMP_Ent *x = EntryLoc(m,d,(*m->T->domhsh)(d));
  bug0( *x != NULL, "attempt to apply on an undefined value");
  return (*m->T->rngcpy)((*x)->info);
}

/*I------------------------------ Modifying ------------------------------- */

void HMP_ovrdom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_ovrdom(m,d,r) HMP_ovrdom(m,ABS_CAST(HMP_Dom,d),ABS_CAST(HMP_Rng,r))
/* defines pair ( 'd', 'r' ) or updates range of domain 'd' in map 'm' 
   m := m \ { (d, r) } 
*/
{ long     h = (*m->T->domhsh)(d);
  HMP_Ent *x = EntryLoc(m,d,h);
  if (*x == (HMP_Ent) NULL)
  {
    addEntry(x,m,d,h,r);
    addTableSlot(m);
  }
  else
    updEntry(m,*x,r);
  m->Version += 1;
}

void HMP_dfndom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_dfndom(m,d,r) HMP_dfndom(m,ABS_CAST(HMP_Dom,d),ABS_CAST(HMP_Rng,r))
#define MAP_define        MAP_dfndom
/* defines pair ( 'd', 'r' ) in map'm'
   m := m U { (d, r) }; raises exception if HMP_defined(m,d) 
*/
{ long     h = (*m->T->domhsh)(d);
  HMP_Ent *x = EntryLoc(m,d,h);
  bug0(*x == (HMP_Ent) NULL,"already defined");
  addEntry(x,m,d,h,r);
  addTableSlot(m);
  m->Version += 1;
}

void HMP_upddom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_upddom(m,d,r) HMP_upddom(m,(HMP_Dom)(d),(HMP_Rng)(r))
#define MAP_update        MAP_upddom
/* updates range of domain 'd' in map 'm'
   m := m \ { (d, r) }; raises exception if not HMP_defined(m,d)
*/
{
  HMP_Ent *x = EntryLoc(m,d,(*m->T->domhsh)(d));
  bug0(*x != (HMP_Ent) NULL, "updating an undefined entry");
  updEntry(m,*x,r);
}

void HMP_rmvdom(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_rmvdom(m,d) HMP_rmvdom(m,(HMP_Dom)(d))
#define MAP_remove      MAP_rmvdom
/* removes domain 'd' from map 'm'
   makes m(d) be undefined; raises exception if not HMP_defined(m,d)
*/
{
  HMP_Ent *x = EntryLoc(m,d,(*m->T->domhsh)(d));
  bug0(*x != (HMP_Ent) NULL, "removing an undefined entry");
  rmvEntry(m,x);
  rmvTableSlot(m);
  m->Version += 1;
}

void HMP_rmvall(/* var */ HMP_Map m)
#define MAP_rmvall HMP_rmvall
/* clears map 'm'
   makes m(d) be undefined for all d
*/
{
  freeTables(m);
  initHashTables(m);
}

/*I--------------------- Basic hash set iterator -------------------------- */

/*!! Do not modify the content of an hash set 
     while using a basic iterator on this set.
*/

/* Diese Iteratoren sind in insofern basal, als sie Aenderungsoperation auf */
/* der gerade iterierten Hash-Menge nicht erlauben. Ein gegen Aenderungen   */
/* invarianter Iterator ist "HMP_Itr" in [hash-lib.h].                      */

/* ACHTUNG! Das Iterator-Konzept ist noch in Arbeit. Geplant ist eine       */
/* abstraktere, "objekt-orientierte" Variante. Die Aenderungen sollten sich */
/* aus Anwendersicht heraus jedoch soweit in Grenzen halten, dass die hier  */
/* angebotenen Iteratoren bedenkenlos verwendet werden koennen.             */

ExternalType( HMP_Itr  )              /* Abstract type of iterators on maps */
{
  HMP_Map m  ; /* the Hash-Set iterated         */
  long    sid; /* the serial number of the slot */
  HMP_Ent e  ; /* the next HMP_Ent to get       */
  long    rem; /* number of remaining elements  */
  long    ver; /* original version              */
};

/*I------------------------- Creating & Disposing ------------------------- */

HMP_Itr HMP_newItr(HMP_Map m)
#define MAP_newItr HMP_newItr
/* creates an iterator on hash set 'm' */
{
  HMP_Itr res = New( HMP_Itr );
  res->m          = m;
  res->sid        = 0;
  res->e          = m->small_table[m->L];
  res->rem        = HMP_count(m);
  res->ver        = m->Version;
  return (HMP_Itr)res;
}

void HMP_freeItr(HMP_Itr i)
#define MAP_freeItr HMP_freeItr
/* removes iterator 'i' */
{
  FreeMem( i );
}

/*I------------------------ Accessing & Modifiying ------------------------ */

bool HMP_emptyItr(HMP_Itr i)
#define MAP_emptyItr HMP_emptyItr
/* whether iterator 'i' is empty */
{
  return i->rem == 0;
}

static HMP_Ent sidEntry(HMP_Map m, long sid)
/* returns the slot of serial # sid */
{
  if (sid < (m->small_size - m->L) )
    return m->small_table[m->L + sid];
  sid -= (m->small_size - m->L);
  if (sid < m->L)
    return m->large_table[sid];
  sid += (m->small_size - m->L);
  return m->large_table[sid];
}

void HMP_getItr(HMP_Itr i, HMP_Dom *d)
#define MAP_getItr(i,d) HMP_getItr(i,(HMP_Dom *) d)
/* get the next domain from iterator 'i' into 'd'
   raises exception if 'HMP_emptyItr(i)'
*/
{
  HMP_Ent res;
  bug0( i->rem > 0, "getItr on empty iterator");
  /* Note that the version test is not completely save, since a program, */
  /* running for years, may produce an identical version number by       */
  /* arithmetical overflow. But not modifying a Hash-Set while a         */
  /* basic iterator is open on it, is a proof obligation anyway.         */
  bug1( i->ver == i->m->Version,
        "HashSet 0x%08lx was modified while iterating",i->m);
  while ( i->e == (HMP_Ent) NULL )
  {
    i->sid += 1;
    i->e    = sidEntry( i->m, i->sid );
  }
  res              = i->e;
  i->e    = i->e->next;
  i->rem -= 1;
  *d               = (*i->m->T->domcpy)(res->key);
}

void HMP_getItrAsg(HMP_Itr i, HMP_Dom *d, HMP_Rng *r)
#define MAP_getItrAsg(i,d,r) HMP_getItrAsg(i,(HMP_Dom *)(d),(HMP_Rng *)(r))
/* get the next pair ( domain, range ) from iterator 'i' into 'd' and 'r'
   raises exception if 'HMP_emptyItr(i)'
*/
{
  HMP_Ent res;
  bug0( i->rem > 0, "getItr on empty iterator");
  /* Note that the version test is not completely save, since a program, */
  /* running for years, may produce an identical version number by       */
  /* arithmetical overflow. But not modifying a Hash-Set while a         */
  /* basic iterator is open on it, is a proof obligation anyway.         */
  bug1( i->ver == i->m->Version,
        "HashSet 0x%08lx was modified while iterating",i->m);
  while ( i->e == (HMP_Ent) NULL )
  {
    i->sid += 1;
    i->e    = sidEntry( i->m, i->sid );
  }
  res              = i->e;
  i->e    = i->e->next;
  i->rem -= 1;
  *d               = (*i->m->T->domcpy)(res->key);
  *r               = (*i->m->T->rngcpy)(res->info);
}

/*I---------------------- Convenient iterator macros ----------------------- */

/*!! For - statement with basic iterators. Make sure to 
     free the iterator if you leave the loop via break. 
*/

/*DOC_INTERFACE_COPY_ON*/
#define MAP_forItr(DomVar,ItrVar,MapExpr)           \
        for (ItrVar = MAP_newItr(MapExpr);          \
             MAP_emptyItr(ItrVar)                   \
             ? (MAP_freeItr(ItrVar),         False) \
             : (MAP_getItr(ItrVar, ((StdCPtr)&DomVar)), True );\
            )

#define MAP_forItrAsg(DomVar,RngVar,ItrVar,MapExpr)             \
        for (ItrVar = MAP_newItr(MapExpr);                      \
             MAP_emptyItr(ItrVar)                               \
             ? (MAP_freeItr(ItrVar),         False)             \
             : (MAP_getItrAsg(ItrVar, ((StdCPtr)&DomVar), ((StdCPtr)&RngVar)), True );\
            )
/*DOC_INTERFACE_COPY_OFF*/

/*I------------------------------- Operations on maps --------------------- */

MAP(_,_) MAP_copy(MAP(_,_) a)
/* copies map 'a';
   The result map references the type of map 'a'.
*/
{ HMP_Dom x; HMP_Rng y; MAPIT it; MAP(_,_) res = MAP_newMap(MAP_MapTyp(a));
  MAP_forItrAsg(x,y,it,a) MAP_dfndom(res,x,y);
  return res;
}

/*I------------------------------- Printing ------------------------------- */

void HMP_fprintMap
     (
       FILE     *f,
       HMP_Map   m,
       int       indent,
       void    (*fprintPair)(FILE *f, HMP_Dom d, HMP_Rng r, int indent)
     )
#define MAP_fprintMap HMP_fprintMap
/* prints map 'm' to file 'f' */
{
  HMP_Itr itr;
  HMP_Dom d;

  fprintf(f,"MAP /* elements: %ld */", HMP_count(m) );
  if (HMP_emptyMap(m))
  {
    fprintf(f," { }");
    return;
  }
  NL;
  fprintf(f,"{"); NL;
  for (itr = HMP_newItr(m);          
       HMP_emptyItr(itr)                   
       ? (HMP_freeItr(itr),    False) 
       : (HMP_getItr(itr, &d), True );
      )
  {
    HMP_Rng r;
    r = HMP_apply(m,d);
    fprintf(f,"  ");
    (*fprintPair)(f, d, r, indent+2);
    (*HMP_domfre(HMP_MapTyp(m)))(d);
    (*HMP_rngfre(HMP_MapTyp(m)))(r);
    if (!HMP_emptyItr(itr))
      fprintf(f,",");
    NL;
  }
  fprintf(f,"}");
}

static void (*tmp_printPair)(HMP_Dom d, HMP_Rng r, int indent);

static void aux_fprintPair(FILE *f, HMP_Dom d, HMP_Rng r, int indent)
{
  (*tmp_printPair)(d, r, indent);
}

void HMP_printMap
     (
       HMP_Map  m,
       int      indent,
       void    (*printPair)(HMP_Dom d, HMP_Rng r, int indent)
     )
#define MAP_printMap HMP_printMap
/* prints map 'm' to 'stdout' */
{
  tmp_printPair = printPair;
  HMP_fprintMap(STDOUT, m, indent, aux_fprintPair);
}

/*I------------------- Debugging & Profiling ------------------------------ */

static void showHashEntries
            (
              HMP_Ent e,
              int     indent,
              void  (*printPair)(HMP_Dom d, HMP_Rng r, int indent)
            )
{
  fprintf(STDOUT,"{"); NLIND;
  for (; e != NULL; e = e->next)
  {
    fprintf(STDOUT,"  HMP_Ent"); NLIND;
    fprintf(STDOUT,"  ["); NLIND;
    fprintf(STDOUT,"    hash: 0x%0*lx,",(int)(2*sizeof(long)),e->hash); NLIND;
    fprintf(STDOUT,"    pair: "); (*printPair)(e->key,e->info,indent+10); NLIND;
    fprintf(STDOUT,"  ]");
    if (e->next != NULL) fprintf(STDOUT,","); NLIND;
  }
  fprintf(STDOUT,"}");
}

void HMP_technicalView
     (
       HMP_Map m,
       int     indent,
       void  (*printPair)(HMP_Dom d, HMP_Rng r, int indent)
     )
/* For visual inspection and debugging purposes */
{ long i;
  fprintf(STDOUT,"HMP_Map[elements:%ld, L:%ld]", HMP_count(m), m->L); 
  NLIND;
  fprintf(STDOUT,"{"); NLIND;
  fprintf(STDOUT,"  /* small_table[size:%ld, slots:%ld] */",
          m->small_size, m->small_size - m->L ); 
  NLIND;
  for (i = m->L; i < m->small_size; i++)
  { fprintf(STDOUT,"  small_table[%ld] :",i); NLIND; fprintf(STDOUT,"  "); 
    showHashEntries(m->small_table[i],indent+2, printPair);
    if (i+1 < m->small_size) fprintf(STDOUT,","); NLIND;
  }
  fprintf(STDOUT,"  /* large_table[size:%ld, slots:%ld] */",
          m->large_size, 2 * m->L ); NLIND;
  for (i = 0; i < m->L; i++)
  { fprintf(STDOUT,"  large_table[%ld] :",i); NLIND; fprintf(STDOUT,"  "); 
    showHashEntries(m->large_table[i],indent+2, printPair);
    fprintf(STDOUT,","); NLIND;
  }
  for 
  ( i = m->small_size; 
    i < m->small_size + m->L; 
    i++
  )
  { fprintf(STDOUT,"  large_table[%ld] :",i); NLIND; fprintf(STDOUT,"  ");
    showHashEntries(m->large_table[i],indent+2, printPair);
    if (i+1 < m->small_size + m->L) fprintf(STDOUT,","); 
      NLIND;
  }
  fprintf(STDOUT,"}");
}

/*I---------------------------- Primitive Maps ---------------------------- */

/*!!
   Primitive maps have an implicit meta-type which treats the
   domain and range values as anonymous pointer. 
   The domain / range copy function return the element itself.
   The domain / range free function do nothing.
   The domain equal function performs a simple '==' operation.
   The domain hash function simply hashes the domain ( pointer ) value.
*/

static MAPTY primMapTy      = (MAPTY)NULL;
static int   initcount_hmap = 0;

void MAP_init(void)
/* inits this module ( create meta-type ) */
{
  if( initcount_hmap == 0 )
  {
    assert0(primMapTy == (MAPTY)NULL, "MAP already initalized");
    primMapTy = MAP_newTyp
                ( 
                  primCopy,primFree,primEqual,primHash,
                  primCopy,primFree
                );
  }
  ++initcount_hmap;
}

void MAP_quit(void)
/* quits this module ( free meta-type ) */
{
  --initcount_hmap;
  if( initcount_hmap == 0 )
  {
    assert0(primMapTy != (MAPTY)NULL, "MAP not initalized");
    MAP_freeTyp(primMapTy); primMapTy = (MAPTY)NULL;
  }
}

MAP(_,_) MAP_newPrimMap(void)
/* creates a primitive map */
{
  return MAP_newMap(primMapTy);
}

bool MAP_prim_equal(MAP(_,_) a, MAP(_,_) b)
/* whether the primitive maps 'a' and 'b' are equal */
{ HMP_Dom x; HMP_Rng y; MAPIT it;
  assert0(MAP_MapTyp(a) == primMapTy, "non-primitive map");
  assert0(MAP_MapTyp(b) == primMapTy, "non-primitive map");
  MAP_forItrAsg(x,y,it,a)
  {
    if (!MAP_defined(b,x) || MAP_apply(HMP_Rng,b,x) != y)
    { MAP_freeItr(it); return False; }
  }
  return True;
}

MAP(_,_) MAP_prim_copy(MAP(_,_) a)
/* copies the primitive map 'a' */
{ HMP_Dom x; HMP_Rng y; MAPIT it; MAP(_,_) res = MAP_newPrimMap();
  assert0(MAP_MapTyp(a) == primMapTy, "non-primitive map");
  MAP_forItrAsg(x,y,it,a) MAP_dfndom(res,x,y);
  return res;
}

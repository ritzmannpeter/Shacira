// ===========================================================================
// base/ring.h                                                  ______ /  ECL
// Autor: Markus wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//! @file  base/ring.h
//! @brief Circular memory management (ring)
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cRingBase                  - Basisklasse zur Implementierung
//      |
//      +-- cRingRaw             - Untypisierter Ring (basierend auf void *)
//      |    |
//      |    +-- cRingRawSafe    -  " dito. mit Mutex-Semaphore abgesichert
//      |
//      +-- cRing<TYPE>          - Typsichere Ringspeicherverwaltung
//           |
//           +-- cRingSafe<TYPE> -  " dito. mit Mutex-Semaphore abgesichert
//
// Besonderheiten:
//
// Schreiben in einen vollen Ring fuehrt wahlweise zu einem Fehler (putError,
// default), dem Verlust der neuen Daten (putIgnore) oder dem Verlust der
// "aeltesten" Daten (putOverwrite).
//
// Serienberingung moeglich: MyRing.put(Elem1).put(Elem2).put(Elem3)
//
// ===========================================================================

#ifndef __ecl_ring__
#define __ecl_ring__


// Standard headers
#include <climits>

// Other ECL headers
#include "base/collect.h"
#include "base/sharedmem.h"
#include "base/error.h"
#include "base/semaphore.h"


              

namespace ecl {


// ===========================================================================
// Deklaration cRingBase
// ---------------------------------------------------------------------------
//
//! @class cRingBase ring.h "base/ring.h"
//! @brief Manages read and write index of a circular memory (ring)
//!
//! Zur Veranschaulichung: Das folgende Bild zeigt einen Ring mit count = 10
//! Elementen und used = 5 Elementen (A..E).
//!
//!@verbatim
//!    +---+---+---+---+---+---+---+---+---+---+
//!    | D | E |   |   |   |   |   | A | B | C |
//!    +---+---+---+---+---+---+---+---+---+---+
//!              ^                   ^
//!              write               read
//!              (Tail)              (Head)
//!@endverbatim
//!
//! Wird beim Konstruktor fuer benannte Ringe count <= 0 oder size <= 0
//! angegeben, wird der Ring im cSharedMem::memOpen-Modus geoeffnet (d.h.
//! er muss bereits erzeugt worden sein).
//
// cRingBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRingBase {

public:
   //! Write behavior in case of a full ring:
   enum PUT_MODE {
      putError = 0,        //!< exception cErrBase::errOverflow is thrown
      putIgnore = 1,       //!< writing is ignored (latest data is lost)
      putOverwrite = 2     //!< overwrite (oldest data is lost)
   };

   // Basis-Ringstruktur
   struct RING {
      int count;           // Maximalzahl Eintraege
      int size;            // Groesse eines Eintrages
      int used;            // Auslastung (Anzahl Eintraege)
      int read;            // Leseindex
      int write;           // Schreibindex
      PUT_MODE put_mode;   // Schreibverhalten
   };

   //! Check whether ring is empty (no elements can be read)
   bool isEmpty() const { return ring->used == 0; }
   //! Check whether ring is full (no elementsentries can be added)
   bool isFull()  const { return ring->used == ring->count; }
   //! Number of free elements in the ring
   int getFree()  const { return ring->count - ring->used; }
   //! Number of currently used elements in the ring
   int getUsed()  const { return ring->used; }
   //! Maximum capacity of the ring (max number of elements)
   int getCount() const { return ring->count; }
   //! Size of a single element in the ring
   int getSize()  const { return ring->size; }

   //! Test whether a certain shared memory already exists
   static bool isAllocated(const cString &name)
      { return cSharedMem::isAllocated(name); }

protected:
   //! Constructor: allocates and initializes cyclic memory
   cRingBase(
      const cString &name, //!< Name of shared memory (optional)
      int elem_count,      //!< maximum number of elements in the cylcic memory
      int elem_size,       //!< size of a single element
      PUT_MODE put_mode    //!< behaviour if there is no space left in the ring
   ); // throws cErrBase::errInvParam

   //! Constructor: initializes cyclic memory
   cRingBase(
      void *mem_ptr,       //!< Pointer to any memory block
      int mem_size,        //!< Length of any memory block
      bool create,         //!< Flag to initialize memory block (true)
      int elem_count,      //!< maximum number of elements in the cylcic memory
      int elem_size,       //!< size of a single element
      PUT_MODE put_mode    //!< behaviour if there is no space left in the ring
   ); // throws cErrBase::errInvParam

   //! Is the deriving class responsible for constructing the elements?
   bool mustConstructElements() const;

   //! Is the deriving class responsible for destroying the elements?
   bool mustDestructElements() const;

   //! Query the write behavior in case of a full ring
   PUT_MODE getPutMode() const
      { return ring->put_mode; }

   //! Index management: increments @a index and checks for overflow,
   //! @a index then is set to the buffer start index.
   void inc( int& index )
      { if ( ++index == ring->count ) index = 0; }
   
   //! Index management: decrements @a index and checks for underflow,
   //! @a index then is set to the buffer end index.
   void dec( int& index )
      { if ( --index < 0 ) index = ring->count - 1; }

   //! Read index management (read from head)
   int getFromRing(); // throws cErrBase(cErrBase::errUnderflow)

   //! Peek into the ring without removing data.
   bool peekRing(int& index) const;
   
   //! Write index management (write at tail)
   int putToRingTail(); // throws cErrBase(cErrBase::errOverflow)
   
   //! Read index management (write at head to undo previous read)
   int putToRingHead(); // throws cErrBase(cErrBase::errOverflow)

protected:
   //! Pointer to structure with ring management information (sizes and indices)
   RING *ring;             

private:
   cSharedMem mem;         // Verwaltung fuer Ring-Speicher

};




// ===========================================================================
// Deklaration cRingRaw
// ---------------------------------------------------------------------------
//
//! @class cRingRaw ring.h "base/ring.h"
//! @brief Generic ring based on memory blocks with void* and size.
//
// cRingBase
//  +--cRingRaw
//
// ===========================================================================

class __ECL_DLLEXPORT__ cRingRaw : public cRingBase {

public:
   //! Construct ring in local memory
   cRingRaw(int elem_count, int elem_size, PUT_MODE put_mode = putError) :
      cRingBase(0, elem_count, elem_size, put_mode) { }
   //! Construct ring in allocated, local memory
   cRingRaw(int elem_count, int elem_size, void *mem_ptr, int mem_size, bool create, PUT_MODE put_mode = putError) :
      cRingBase(mem_ptr, mem_size, create, elem_count, elem_size, put_mode) { }
   //! Construct ring in shared memory
   cRingRaw(int elem_count, int elem_size, const cString &shmem_name, PUT_MODE put_mode = putError) :
      cRingBase(shmem_name, elem_count, elem_size, put_mode) { }
   //! Destruct ring
   ~cRingRaw()
      { }

   //! Get element from ring head.
   void *get(void *buf, int size);
   //! Put element to ring tail.
   cRingRaw& put(const void *buf, int size);
   //! Put element to ring head
   cRingRaw& unget(const void *buf, int size);
   //! Peek element from position relative to ring head
   bool peek(int index, void *buf, int size) const;

};


// ===========================================================================
// Deklaration cRingRawSafe
// ---------------------------------------------------------------------------
//
// cRingBase
//  +--cRingRaw
//      +--cRingRawSafe
//
// ===========================================================================

class cRingRawSafe : public cRingRaw {
private:
   cMutexSem mutex;

public:
   cRingRawSafe(int elem_count, int elem_size, PUT_MODE put_mode = putError) :
      cRingRaw(elem_count, elem_size, put_mode),
      mutex() { }
   cRingRawSafe(int elem_count, int elem_size, void *mem_ptr, int mem_size, bool create, PUT_MODE put_mode = putError) :
      cRingRaw(elem_count, elem_size, mem_ptr, mem_size, create, put_mode),
      mutex() { }
   cRingRawSafe(int elem_count, int elem_size, const cString &shmem_name, PUT_MODE put_mode = putError) :
      cRingRaw(elem_count, elem_size, shmem_name, put_mode),
      mutex(shmem_name, cMutexSem::semOpenOrCreate) { }

   void *get(void *buf, int size)
   {
      mutex.request();
      void *result = cRingRaw::get(buf, size);
      mutex.release();
      return result;
   }

   bool peek(int index, void *buf, int size)
   {
      mutex.request();
      bool result = cRingRaw::peek(index, buf, size);
      mutex.release();
      return result;
   }

   cRingRawSafe& put(const void *buf, int size)
   {
      mutex.request();
      cRingRaw::put(buf, size);
      mutex.release();
      return *this;
   }

   cRingRawSafe& unget(const void *buf, int size)
   {
      mutex.request();
      cRingRaw::unget(buf, size);
      mutex.release();
      return *this;
   }

};


// ===========================================================================
// Deklaration cRing<TYPE>
// ---------------------------------------------------------------------------
//
// cRingBase
//  +--cRing<TYPE>
//
// ===========================================================================

template<class TYPE>
class __ECL_DLLEXPORT__ cRing : public cRingBase {

public:
   cRing( int elem_count, PUT_MODE put_mode = putError );
   cRing( int elem_count, void *mem_ptr, int mem_size, bool create, PUT_MODE put_mode = putError );
   cRing( int elem_count, const cString &shmem_name, PUT_MODE put_mode = putError );
   ~cRing();

   // Elementweiser Zugriff, nur hier koennen Fehler geschehen
   TYPE get();
   cRing<TYPE>& put( const TYPE& value );
   cRing<TYPE>& unget( const TYPE& value);
   bool peek(int index,TYPE& value) const;

   // Blockweise schreiben, liefert Zahl der bearbeiteten Elemente
   int writeBlock( const TYPE *buffer, int count );
   // Blockweise bzw. den gesamten Ring lesen, liefert Elementzahl
   int readBlock( TYPE *buffer, int count = INT_MAX );

};


// Implementierung cRing<TYPE>
// ===========================================================================

template<class TYPE>
cRing<TYPE>::cRing( int elem_count, PUT_MODE put_mode ) :
   cRingBase( 0, elem_count, sizeof(TYPE), put_mode )
{
   if ( mustConstructElements() )
      EclConstructElements( (TYPE*)(ring+1), elem_count );
}

template<class TYPE>
cRing<TYPE>::cRing( int elem_count, void *mem_ptr, int mem_size, bool create, PUT_MODE put_mode ) :
   cRingBase( mem_ptr, mem_size, create, elem_count, sizeof(TYPE), put_mode )
{
   if ( mustConstructElements() )
      EclConstructElements( (TYPE*)(ring+1), elem_count );
}

template<class TYPE>
cRing<TYPE>::cRing( int elem_count, const cString &shmem_name, PUT_MODE put_mode ) :
   cRingBase( shmem_name, elem_count, sizeof(TYPE), put_mode )
{
   if ( mustConstructElements() )
      EclConstructElements( (TYPE*)(ring+1), elem_count );
}

template<class TYPE>
cRing<TYPE>::~cRing()
{
   if ( mustDestructElements() )
      EclDestructElements( (TYPE*)(ring+1), ring->count );
}


//
// Elementfunktionen
//

template<class TYPE>
TYPE cRing<TYPE>::get()
{
   int index = getFromRing();
   return ((TYPE*)(ring+1))[index];
}

template<class TYPE>
bool cRing<TYPE>::peek(int index,TYPE& value) const
{
   if ( !peekRing(index) )
      return false;
   value = ((TYPE*)(ring+1))[index];
   return true;
}

template<class TYPE>
cRing<TYPE>& cRing<TYPE>::put( const TYPE& value )
{
   int index = putToRingTail();
   if ( index >= 0 )
      ((TYPE*)(ring+1))[index] = value;
   return *this;
}

template<class TYPE>
cRing<TYPE>& cRing<TYPE>::unget( const TYPE& value )
{
   int index = putToRingHead();
   if ( index >= 0 )
      ((TYPE*)(ring+1))[index] = value;
   return *this;
}


//
// Blockfunktionen
//
template<class TYPE>
int cRing<TYPE>::readBlock( TYPE *buffer, int count )
{
   int done = 0;

   while ( count > 0 && !isEmpty() ) {
      *buffer++ = get();
      count--; done++;
   };

   return done;
}

template<class TYPE>
int cRing<TYPE>::writeBlock( const TYPE *buffer, int count )
{
   int done = 0;

   // Je nach Schreibverhalten gehen Daten verloren !!!
   while ( count > 0 && (!isFull() || getPutMode() != putError) ) {
      put( *buffer++ );
      count--; done++;
   };

   return done;
}


// ===========================================================================
// Deklaration cRingSafe<TYPE>
// ---------------------------------------------------------------------------
//
// cRingBase
//  +--cRing<TYPE>
//      +--cRingSafe<TYPE>
//
// ===========================================================================

template<class TYPE>
class cRingSafe : public cRing<TYPE> {
private:
   cMutexSem mutex;

public:
// PR GNUC
//   cRingSafe( int elem_count, cRingBase::PUT_MODE put_mode = putError ) :
   cRingSafe( int elem_count, cRingBase::PUT_MODE put_mode = cRingBase::putError ) :
      cRing<TYPE>( elem_count, put_mode ),
      mutex() { }
// PR GNUC
//   cRingSafe( int elem_count, void *mem_ptr, int mem_size, bool create, cRingBase::PUT_MODE put_mode = putError ) :
      cRingSafe( int elem_count, void *mem_ptr, int mem_size, bool create, cRingBase::PUT_MODE put_mode = cRingBase::putError ) :
      cRing<TYPE>( elem_count, mem_ptr, mem_size, create, put_mode ),
      mutex() { }
// PR GNUC
//   cRingSafe( int elem_count, const cString &shmem_name, cRingBase::PUT_MODE put_mode = putError ) :
   cRingSafe( int elem_count, const cString &shmem_name, cRingBase::PUT_MODE put_mode = cRingBase::putError ) :
      cRing<TYPE>( elem_count, shmem_name, put_mode ),
      mutex( shmem_name, cMutexSem::semOpenOrCreate ) { }

   TYPE get()
   {
      mutex.request();
      TYPE result = cRing<TYPE>::get();
      mutex.release();
      return result;
   }

   bool peek( int index, TYPE& value)
   {
      mutex.request();
      bool result = cRing<TYPE>::peek( index, value );
      mutex.release();
      return result;
   }

   cRingSafe<TYPE>& put( const TYPE& value )
   {
      mutex.request();
      cRing<TYPE>::put( value );
      mutex.release();
      return *this;
   }

   cRingSafe<TYPE>& unget( const TYPE& value)
   {
      mutex.request();
      cRing<TYPE>::unget( value );
      mutex.release();
      return *this;
   }

   int writeBlock( const TYPE *buffer, int count )
   {
      mutex.request();
      int result = cRing<TYPE>::writeBlock( buffer, count );
      mutex.release();
      return result;
   }

   int readBlock( TYPE *buffer, int count = INT_MAX )
   {
      mutex.request();
      int result = cRing<TYPE>::readBlock( buffer, count );
      mutex.release();
      return result;
   }
};


}; // namespace ecl


#endif // __ecl_ring__



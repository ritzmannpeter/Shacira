// ===========================================================================
// base/ring.cpp                                                ______ /  ECL
// Autor: Markus wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/ring.h"




namespace ecl {




// Implementierung cRingBase
// ===========================================================================

/**
 * 
 */
// Initialisierung von mem: es scheint mit Absicht erlaubt zu sein, dass ueber
// count<=0 bzw. size<=0 der open_mode implizit gesteuert werden kann. Allerdings
// wurde dann der size Parameter von cSharedMem falsch gesetzt, abgesehen davon,
// dass cSharedMem bisher size<=0 nicht akzeptiert hat!
cRingBase::cRingBase(const cString &mem_name, int elem_count, int elem_size, PUT_MODE put_mode) :
   mem(mem_name,
       (elem_count > 0 && elem_size > 0) ? cSharedMem::memOpenOrCreate : cSharedMem::memOpen,
       (elem_count > 0 && elem_size > 0) ? sizeof(RING) + elem_count * elem_size : -1)
{
   ring = (RING *)mem.getAdr();
   ring->put_mode = put_mode;

   switch ( mem.getCreationMode() ) {
      case cSharedMem::cmSharedCreated:
      case cSharedMem::cmLocalCreated:
         if ( elem_count <= 0 || elem_size <= 0 )
            throw cErrBase(cErrBase::errInvParam, "cRingBase");
         ring->size = elem_size;
         ring->count = elem_count;
         ring->used = 0;
         ring->read = 0;
         ring->write = 0;
         break;
      case cSharedMem::cmSharedOpened:
         if ( (elem_count > 0 && ring->count != elem_count) || (elem_size > 0 && ring->size != elem_size) )
            throw cErrBase(cErrBase::errInvParam, "cRingBase");
         break;
      default:
         throw cErrBase(cErrBase::errInvParam, "cRingBase");
   }
}


cRingBase::cRingBase(void *mem_ptr, int mem_size, bool create, int elem_count, int elem_size, PUT_MODE put_mode) :
   mem(create ? cSharedMem::memCreate : cSharedMem::memOpen, mem_ptr, mem_size)
{
   if ( elem_count <= 0 || elem_size <= 0 || mem.getSize() < (int)sizeof(RING) + elem_count * elem_size )
      throw cErrBase(cErrBase::errInvParam, "cRingBase");
   
   ring = (RING *)mem.getAdr();
   ring->put_mode = put_mode;

   switch ( mem.getCreationMode() ) {
      case cSharedMem::cmStaticCreated:
         ring->size = elem_size;
         ring->count = elem_count;
         ring->used = 0;
         ring->read = 0;
         ring->write = 0;
         break;
      case cSharedMem::cmStaticOpened:
         if ( ring->count != elem_count || ring->size != elem_size )
            throw cErrBase(cErrBase::errInvParam, "cRingBase");
         break;
      default:
         throw cErrBase(cErrBase::errInvParam, "cRingBase");
   }

}


/**
 * If the cyclic memory is opened on an existing data structure in
 * the shared memory (cmSharedOpened), the elements of the ring must
 * not be initially constructed. This is done by the instance of the
 * ring class that created the shared or local memory.
 */
bool cRingBase::mustConstructElements() const
{ 
   return mem.getCreationMode() != cSharedMem::cmSharedOpened &&
          mem.getCreationMode() != cSharedMem::cmStaticOpened;
}

/**
 * Similar to mustConstructElements() only the creating instance is
 * allowed and obliged to destruct the elements of the ring.
 */
 bool cRingBase::mustDestructElements() const
 { 
    return mem.getCreationMode() != cSharedMem::cmSharedOpened && 
           mem.getCreationMode() != cSharedMem::cmStaticOpened;
}


/**
 * Returns index of the next element at the head of the ring and changes the
 * read index to remove this element from the ring. Throws an exception if
 * the ring is empty.
 */
int cRingBase::getFromRing()
{
   if ( isEmpty() )
      throw cErrBase( cErrBase::errUnderflow, "cRingBase" );

   int index = ring->read;
   inc( ring->read ); ring->used--;
   return index;
}

/**
 * Converts an index relative to the read pointer to an absolute index
 * of the ring data area. Returns true if the converstion was successful
 * and such an element is within the currently valid head and tail.
 * Returns false and @a index == -1 if no such element exists.
 */
bool cRingBase::peekRing(int& index) const
{
   if (index < 0 || index >= ring->used) {
      index = -1;
      return false;
   }
   index = (index + ring->read) % ring->count;
   return true;
}

/**
 * Changes the write index to add an element at the tail of the ring and
 * returns that index. If the ring is full, throws an execption @a cErrBase
 * or returns index -1 (depending on putMode during construction)
 */
int cRingBase::putToRingTail()
{
   int index;

   if ( isFull() ) {
      switch ( getPutMode() ) {
      case putIgnore: 
         return -1;
      case putOverwrite:
         index = ring->write;
         inc( ring->write ); inc( ring->read );
         return index;
      case putError:
      default:
         throw cErrBase( cErrBase::errOverflow, "cRingBase" );
      }
   }
   index = ring->write;
   inc( ring->write ); ring->used++;
   return index;
}

/**
 * Changes the read index to ad an element at
 * the head of the ring and returns that index. If the ring is full, throws
 * an execption @a cErrBase or returns index -1 (depending on putMode during
 * construction). Usually this is used to put an element previously read
 * back into the ring so it will be read the next time again.
 */
int cRingBase::putToRingHead()
{
   if ( isFull() ) {
      switch ( getPutMode() ) {
      case putIgnore: 
         return -1;
      case putOverwrite:
         dec( ring->write ); dec( ring->read );
         return ring->write;
      case putError:
      default:
         throw cErrBase( cErrBase::errOverflow, "cRingBase" );
      }
   }
   // -MW- 2004-07-29 war 2x ring->write (uuuaaahhh!!!)
   dec( ring->read ); ring->used++;
   return ring->read;
}




// Implementierung cRingRaw
// ===========================================================================

/**
 * If @a size is greater than the element size defined during construction, only
 * the available element bytes are copied (see getSize()). That applys to peek(),
 * put() and unget(), too. Return value is @a buf.
 */
void *cRingRaw::get(void *buf, int size)
{
   void *src_buf = ((char*)(ring+1)) + getFromRing() * ring->size;
   return memcpy(buf, src_buf, min(size, ring->size));
}

/**
 * Get an element from the ring without removing it. If the offset from the
 * ring head @a index exeeds the currently stored number of element, false is
 * returned and no data is copied.
 */
bool cRingRaw::peek(int index, void *buf, int size) const
{
   if ( !peekRing(index) )
      return false;
   void *src_buf = ((char*)(ring+1)) + index * ring->size;
   memcpy(buf, src_buf, min(size, ring->size));
   return true;
}

/**
 * Since a the ring object is returned, you can write several elements with
 * a single statement:
 * @code
 * myring.put(data1,size1).put(data2,size2)
 * @endcode
 */
cRingRaw& cRingRaw::put(const void *buf, int size)
{
   int index = putToRingTail();
   if ( index >= 0 ) {
      void *dest_buf = ((char*)(ring+1)) + index * ring->size;
      memcpy(dest_buf, buf, min(size, ring->size));
   }
   return *this;
}

/**
 * Exactly the same as put(), but the element is added to the head of the
 * ring instead of the tail.
 */
cRingRaw& cRingRaw::unget(const void *buf, int size)
{
   int index = putToRingHead();
   if ( index >= 0 ) {
      void *dest_buf = ((char*)(ring+1)) + index * ring->size;
      memcpy(dest_buf, buf, min(size, ring->size));
   }
   return *this;
}


}; // namespace ecl


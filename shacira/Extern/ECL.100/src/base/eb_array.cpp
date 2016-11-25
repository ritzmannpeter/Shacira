// ===========================================================================
// eb_array.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cArray                  - Array collection class.
//
// ===========================================================================

#include "base/eb_array.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_collect.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cArray<TYPE,ARG_TYPE>
// ---------------------------------------------------------------------------
//
// Groesse eines leeren cArray-Objektes unter:
//
//   - OS/2 (IBM CSet ++)        = 16 Bytes
//   - Windows (MS Visual C++)   = 16 Bytes
//
//  cArray<TYPE,ARG_TYPE>
//
// ===========================================================================

template<class TYPE, class ARG_TYPE>
   class cArray {

   public:
      cArray();
      ~cArray();

      // Attributes
      int getSize() const
         { return act_size; }
      int getUpperBound() const
         { return act_size - 1; }
      void setSize(int new_size, int grow_by = -1);

      // Operations
      // Clean up
      void freeExtra();
      void removeAll()
         { setSize(0, -1); }

      // Accessing elements
      TYPE getAt(int idx) const
         { __ECL_ASSERT1__(idx >= 0 && idx < act_size);
           return data[idx]; }
      void setAt(int idx, ARG_TYPE new_element)
         { __ECL_ASSERT1__(idx >= 0 && idx < act_size);
           data[idx] = new_element; }
      TYPE& getElementAt(int idx)
         { __ECL_ASSERT1__(idx >= 0 && idx < act_size);
           return data[idx]; }

      // Direct Access to the element data (may return NULL)
      const TYPE* getData() const
         { return (const TYPE*)data; }
      TYPE* getData()
         { return (TYPE*)data; }

      // Potentially growing the array
      void setAtGrow(int idx, ARG_TYPE new_element);
      int add(ARG_TYPE new_element)
         { int idx = act_size;
           setAtGrow(idx, new_element);
           return idx; }
      int append(const cArray<TYPE, ARG_TYPE>& src);
      void copy(const cArray<TYPE, ARG_TYPE>& src);

      // overloaded operator helpers
      TYPE operator[](int idx) const
         { return getAt(idx); }
      TYPE& operator[](int idx)
         { return getElementAt(idx); }

      // Operations that move elements around
      void insertAt(int idx, ARG_TYPE new_element, int count = 1);
      void removeAt(int idx, int count = 1);
      void insertAt(int nStartIndex, cArray<TYPE, ARG_TYPE>* pNewArray);

   protected:
      TYPE* data;       // the actual array of data
      int act_size;     // # of elements (upperBound - 1)
      int max_size;     // max allocated
      int grow_amount;  // grow amount

   };


// Implementierung cArray<TYPE,ARG_TYPE>
// ===========================================================================

template<class TYPE, class ARG_TYPE>
   cArray<TYPE, ARG_TYPE>::cArray()
   {
      data = NULL;
      act_size = max_size = grow_amount = 0;
   }

template<class TYPE, class ARG_TYPE>
   cArray<TYPE, ARG_TYPE>::~cArray()
   {
      if (data != NULL)
      {
         EclDestructElements(data, act_size);
         delete[] (char*)data;
      }
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::setSize(int new_size, int grow_by)
   {
      __ECL_ASSERT1__(new_size >= 0);

      if (grow_by != -1)
         grow_amount = grow_by;  // set new size

      if (new_size == 0)
      {
         // shrink to nothing
         if (data != NULL)
         {
            EclDestructElements(data, act_size);
            delete[] (char*)data;
            data = NULL;
         }
         act_size = max_size = 0;
      }
      else if (data == NULL)
      {
         // create one with exact size
   #ifdef SIZE_T_MAX
         __ECL_ASSERT1__(new_size <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
   #endif
         data = (TYPE*) new char[new_size * sizeof(TYPE)];
         EclConstructElements(data, new_size);
         act_size = max_size = new_size;
      }
      else if (new_size <= max_size)
      {
         // it fits
         if (new_size > act_size)
         {
            // initialize the new elements
            EclConstructElements(&data[act_size], new_size-act_size);
         }
         else if (act_size > new_size)
         {
            // destroy the old elements
            EclDestructElements(&data[new_size], act_size-new_size);
         }
         act_size = new_size;
      }
      else
      {
         // otherwise, grow array
         int grow_by = grow_amount;
         if (grow_by == 0)
         {
            // heuristically determine growth when grow_by == 0
            //  (this avoids heap fragmentation in many situations)
            grow_by = act_size / 8;
            grow_by = (grow_by < 4) ? 4 : ((grow_by > 1024) ? 1024 : grow_by);
         }
         int nNewMax;
         if (new_size < max_size + grow_by)
            nNewMax = max_size + grow_by;  // granularity
         else
            nNewMax = new_size;  // no slush

         __ECL_ASSERT1__(nNewMax >= max_size);  // no wrap around
   #ifdef SIZE_T_MAX
         __ECL_ASSERT1__(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
   #endif
         TYPE* pNewData = (TYPE*) new char[nNewMax * sizeof(TYPE)];

         // copy new data from old
         memcpy(pNewData, data, act_size * sizeof(TYPE));

         // construct remaining elements
         __ECL_ASSERT1__(new_size > act_size);
         EclConstructElements(&pNewData[act_size], new_size-act_size);

         // get rid of old stuff (note: no destructors called)
         delete[] (char*)data;
         data = pNewData;
         act_size = new_size;
         max_size = nNewMax;
      }
   }

template<class TYPE, class ARG_TYPE>
   int cArray<TYPE, ARG_TYPE>::append(const cArray<TYPE, ARG_TYPE>& src)
   {
      __ECL_ASSERT1__(this != &src);   // cannot append to itself

      int nOldSize = act_size;
      setSize(act_size + src.act_size);
      EclCopyElements(data + nOldSize, src.data, src.act_size);
      return nOldSize;
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::copy(const cArray<TYPE, ARG_TYPE>& src)
   {
      __ECL_ASSERT1__(this != &src);   // cannot append to itself

      setSize(src.act_size);
      EclCopyElements(data, src.data, src.act_size);
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::freeExtra()
   {
      if (act_size != max_size)
      {
         // shrink to desired size
   #ifdef SIZE_T_MAX
         __ECL_ASSERT1__(act_size <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
   #endif
         TYPE* pNewData = NULL;
         if (act_size != 0)
         {
            pNewData = (TYPE*) new char[act_size * sizeof(TYPE)];
            // copy new data from old
            memcpy(pNewData, data, act_size * sizeof(TYPE));
         }

         // get rid of old stuff (note: no destructors called)
         delete[] (char*)data;
         data = pNewData;
         max_size = act_size;
      }
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::setAtGrow(int idx, ARG_TYPE new_element)
   {
      __ECL_ASSERT1__(idx >= 0);

      if (idx >= act_size)
         setSize(idx+1, -1);
      data[idx] = new_element;
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::insertAt(int idx, ARG_TYPE new_element, int count /*=1*/)
   {
      __ECL_ASSERT1__(idx >= 0);    // will expand to meet need
      __ECL_ASSERT1__(count > 0);     // zero or negative size not allowed

      if (idx >= act_size)
      {
         // adding after the end of the array
         setSize(idx + count, -1);   // grow so idx is valid
      }
      else
      {
         // inserting in the middle of the array
         int nOldSize = act_size;
         setSize(act_size + count, -1);  // grow it to new size
         // destroy intial data before copying over it
         EclDestructElements(&data[nOldSize], count);
         // shift old data up to fill gap
         memmove(&data[idx+count], &data[idx],
            (nOldSize-idx) * sizeof(TYPE));

         // re-init slots we copied from
         EclConstructElements(&data[idx], count);
      }

      // insert new value in the gap
      __ECL_ASSERT1__(idx + count <= act_size);
      while (count--)
         data[idx++] = new_element;
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::removeAt(int idx, int count)
   {
      __ECL_ASSERT1__(idx >= 0);
      __ECL_ASSERT1__(count >= 0);
      __ECL_ASSERT1__(idx + count <= act_size);

      // just remove a range
      int nMoveCount = act_size - (idx + count);
      EclDestructElements(&data[idx], count);
      if (nMoveCount)
         memmove(&data[idx], &data[idx + count],
            nMoveCount * sizeof(TYPE));
      act_size -= count;
   }

template<class TYPE, class ARG_TYPE>
   void cArray<TYPE, ARG_TYPE>::insertAt(int nStartIndex, cArray<TYPE, ARG_TYPE>* pNewArray)
   {
      __ECL_ASSERT1__(pNewArray != NULL);
      __ECL_ASSERT1__(nStartIndex >= 0);

      if (pNewArray->getSize() > 0)
      {
         insertAt(nStartIndex, pNewArray->getAt(0), pNewArray->getSize());
         for (int i = 0; i < pNewArray->getSize(); i++)
            setAt(nStartIndex + i, pNewArray->getAt(i));
      }
   }

#endif /*__INTERFACE__*/


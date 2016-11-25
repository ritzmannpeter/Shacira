// ===========================================================================
// base/singleton.h                                             ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    tSingleton<TYPE> - Singleton Design Pattern
//
//! @file  base/singleton.h
//! @brief Singleton Design Pattern
// ===========================================================================

#ifndef __singleton_template__
#define __singleton_template__


// Other ECL headers
//-threadsafe- #include "base/semaphore.h"


namespace ecl {


// ===========================================================================
// Definition tSingleton<TYPE>
// ---------------------------------------------------------------------------
//
//! @class tSingleton singleton.h "base/singleton.h"
//! @brief Singleton Design Pattern
//! @ingroup creational
//!
//! Ensures that there is exactly one instance of a class. To achieve this,
//! derive the class you want to be a singleton from tSingleton<TYPE> like this:
//!
//! @code
//! // Class declaration
//! class cExample : public ecl::tSingleton<cExample>
//! {
//! private:
//!    // Use private or protected default constructor and friend declaration
//!    // of internal helper class to prevent unintentional instantiation
//!    // without using getInstance()
//!    friend cExample::cManager;
//!    cExample() {
//!       // empty or your code
//!    }
//!
//! public: 
//!    void someMethod() {
//!       // your code
//!    };
//! };
//! 
//! // Access to the instance:
//! cExample::getInstance()->someMethod();
//! @endcode
//!
//! It is recommended (and comfortable) to use a global access function:
//!
//! @code
//! class cMain : public ecl::tSingleton<cMain>
//! {
//!    // your stuff
//! };
//!
//! inline cMain &MAIN() { return *cMain::getInstance(); }
//! @endcode
//!
//! @note 
//! The construction of the instance is <b>not thread safe</b>. If used in a
//! multi-threading environment, enforce the construction already in the main
//! thread by a call of getInstance() before the other threads are started.
//!
//! @note
//! If thread-safety is needed, this header may become dependant of 
//! "base/semaphore.h", but the scheme tSingleton<TYPE> is guaranted. Either:
//! - Mutex is completely hidden (the modifications to get this variant are
//!   comment out with "//-threadsafe-", additional overhead concerns only
//!   the very first call of getInstance()).
//! - Mutex become an optional template parameter: tSingleton<TYPE,MUTX=cMutexNull>
//! - A completely new class is introduced: tSingletonSafe<TYPE>
//!
//! @note
//! Thread safety inside TYPE itself is the responsibility of the user
//! of tSingleton<TYPE>. 
//!
//! @note
//! The class takes care of the "phoenix effect", that means if a singleton 
//! has already been destroyed during program termination, it is not created
//! again if it is referenced e.g. by another, later destroyed singleton. A
//! zero pointer is returned in this case.
//!
//! @note
//! There is no defined destruction order of singletons! If this is needed,
//! a destruction manager or something like that has to be implemented. (A
//! lightwight methods requires only the possiblity to explicit delete a
//! concrete singleton. The modifications to get this variants are comment
//! out with "//-delete-")
//! 
// ===========================================================================

template <class TYPE>
class tSingleton
{
protected:
   //! Constructor is protected to prevent unintentional direct instantiation.
   tSingleton() {};

public:
   // Internal helper class that controls construction and destruction
   // of TYPE with new and delete.
   class cManager  {
   public:
      cManager() : _instance(0),_deleted(false) { }
      ~cManager() { delete _instance; _instance = 0; _deleted = true; }
      TYPE *getInstance() {
         //-threadsafe- if (_instance == 0) {
         //-threadsafe-    cMutexGuard g(_construction_mutex);
            if (_instance == 0 && _deleted == false) _instance = new TYPE;
         //-threadsafe- }
         return _instance;
      }
      //-delete- void delInstance() { delete _instance; _instance = 0; _deleted = true; }
   private:
      //-threadsafe- cMutexSem _construction_mutex;
      bool _deleted;
      TYPE *_instance;
   };

public:
   //! Access to the instance of TYPE. The first call causes
   //! the creation of the object. Returns 0 if the object has
   //! been destroyed during program termination.
   static TYPE *getInstance() {
      return _manager.getInstance();
   }

   // Delete explicit the instance of TYPE. All further calls of
   // getInstance() return 0.
   //-delete- static void delInstance() {
   //-delete-    _manager.delInstance();
   //-delete- }

private:
   static cManager _manager;

}; // tSingleton


template<class TYPE>
typename tSingleton<TYPE>::cManager tSingleton<TYPE>::_manager;


}; // namespace ecl


#endif //__singleton_template__

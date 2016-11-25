// ===========================================================================
// base/singleton.h                                             ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cSingleton<TYPE> - Singleton Design Pattern
//
//! @file  base/singleton.h
//! @brief Singleton Design Pattern
// ===========================================================================

#ifndef __singleton_template__
#define __singleton_template__


// ===========================================================================
// Definition cSingleton<TYPE>
// ---------------------------------------------------------------------------
//
//! @class cSingleton singleton.h "base/singleton.h"
//! @brief Singleton Design Pattern
//! @ingroup creational
//!
//! Ensures that there is exactly one instance of a class. To achieve this,
//! derive the class you want to be a singleton from cSingleton<TYPE> like this:
//!
//! @code
//! // Class declaration
//! class cExample : public cSingleton<cExample>
//! {
//!    void someMethod();
//! };
//! 
//! // Access to the instance:
//! cExample::getInstance()->someMethod();
//! @endcode
//!
//! @note 
//! The construction of the instance is <b>not thread safe</b>. If used in a
//! multi-threading environment, enforce the construction already in the main
//! thread by a call of getInstance() before the other threads are started.
//!
//! @note
//! If thread-safety is needed, this header may become dependant of 
//! "base/semaphore.h", but the scheme cSingleton<TYPE> is guaranted. Either:
//! - Mutex is completely hidden (preferred).
//! - Mutex become an optional template parameter: cSingleton<TYPE,MUTX=cMutexNull>
//! - A completely new class is introduced: cSingletonSafe<TYPE>
//!
//! Thread safety inside TYPE itself is the responsibility of the user
//! of cSingleton<TYPE>. 
// ===========================================================================

template <class TYPE>
class cSingleton
{
protected:
   //! Constructor is protected to prevent unintentional direct instantiation.
   cSingleton() {};

public:
   // Internal helper class that controls construction and destruction
   // of TYPE with new and delete.
   class cManager  {
   public:
      cManager() : _instance(0) { }
      ~cManager() { delete _instance; _instance = 0; }
      TYPE *getInstance() {
         // lock mutex here if thread safety is required
         if (_instance == 0) _instance = new TYPE;
         // unlock mutex
         return _instance;
      }
   private:
      TYPE *_instance;
   };

public:
   //! Access to the instance of TYPE. The first call causes
   //! the creation of the object.
   static TYPE *getInstance() {
      return _manager.getInstance();
   }

private:
   static cManager _manager;

}; // cSingleton


template<class TYPE>
cSingleton<TYPE>::cManager cSingleton<TYPE>::_manager;


#endif //__singleton_template__

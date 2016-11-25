// ===========================================================================
// eb_except.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cException           - Basisklasse fuer systemspezifische Exceptions.
//     |
//     +-cExceptionHandler    - Exception-Handler fuer Threads
//
// ===========================================================================

#include "base/eb_thread.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>                              /* wg. offsetof()         */

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_DOSEXCEPTIONS    /* Exception handling */
   #include <os2.h>
#elif defined __ECL_W32__
   // ...
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

#endif /* __INTERFACE__ */




#ifdef __INTERFACE__

// ===========================================================================
// cExceptionHandler
// ---------------------------------------------------------------------------
//
// cBase
//  +--cExceptionHandler
//
// ===========================================================================

class cThread;

class __ECL_DLLEXPORT__ cExceptionHandler : public cBase {
   friend class cThread;

public:
   cExceptionHandler(cThread *thread_to_register);
   ~cExceptionHandler();

   void raiseAsyncTerminate();

private:
   cThread *thread;
   void *registration_record;
   static void deregisterAllHandlersFor(cThread *thread_to_deregister);

};

#endif /* __INTERFACE__ */


// Implementierung cExceptionHandler
// ---------------------------------------------------------------------------

#if defined __ECL_OS2__

   // Maximalzahl von moeglichen Exception-Handlern
   #define MAX_THREADS 50

   static struct REGISTERED_THREADS {
      PEXCEPTIONREGISTRATIONRECORD x_mark;
      cThread *thread;
      int tid;
   } RegisteredThreadTab[MAX_THREADS];

   class cOS2Exception : public cException {
   public:
      PEXCEPTIONREPORTRECORD x_record;
      PEXCEPTIONREGISTRATIONRECORD x_mark;
      PCONTEXTRECORD x_context;
      PVOID x_pointer;
   public:
      cOS2Exception(PEXCEPTIONREPORTRECORD x_record,
                    PEXCEPTIONREGISTRATIONRECORD x_mark,
                    PCONTEXTRECORD x_context,
                    PVOID x_pointer)
      {
         cOS2Exception::x_record = x_record;
         cOS2Exception::x_mark = x_mark;
         cOS2Exception::x_context = x_context;
         cOS2Exception::x_pointer = x_pointer;
      }
      EXCEPTION getId() const
      {
         switch ( x_record->ExceptionNum ) {
            case XCPT_GUARD_PAGE_VIOLATION:     return xGuardPageViolation;
            case XCPT_UNABLE_TO_GROW_STACK:     return xUnableToGrowStack;
            case XCPT_DATATYPE_MISALIGNMENT:    return xDatatypeMisalignment;
            case XCPT_BREAKPOINT:               return xBreakpoint;
            case XCPT_SINGLE_STEP:              return xSingleStep;
            case XCPT_ACCESS_VIOLATION:         return xAccessViolation;
            case XCPT_ILLEGAL_INSTRUCTION:      return xIllegalInstruction;
            case XCPT_FLOAT_DENORMAL_OPERAND:   return xFloatDenormalOperand;
            case XCPT_FLOAT_DIVIDE_BY_ZERO:     return xFloatDivideByZero;
            case XCPT_FLOAT_INEXACT_RESULT:     return xFloatInexactResult;
            case XCPT_FLOAT_INVALID_OPERATION:  return xFloatInvalidOperation;
            case XCPT_FLOAT_OVERFLOW:           return xFloatOverflow;
            case XCPT_FLOAT_STACK_CHECK:        return xFloatStackCheck;
            case XCPT_FLOAT_UNDERFLOW:          return xFloatUnderflow;
            case XCPT_INTEGER_DIVIDE_BY_ZERO:   return xIntegerDivideByZero;
            case XCPT_INTEGER_OVERFLOW:         return xIntegerOverflow;
            case XCPT_PRIVILEGED_INSTRUCTION:   return xPriviledgedInstruction;
            case XCPT_IN_PAGE_ERROR:            return xInPageError;
            case XCPT_PROCESS_TERMINATE:        return xProcessTerminate;
            case XCPT_ASYNC_PROCESS_TERMINATE:  return xAsyncProcessTerminate;
            case XCPT_NONCONTINUABLE_EXCEPTION: return xNoncontinuableException;
            case XCPT_INVALID_DISPOSITION:      return xInvalidDisposition;
            case XCPT_UNWIND:                   return xUnwind;
            case XCPT_BAD_STACK:                return xBadStack;
            case XCPT_INVALID_UNWIND_TARGET:    return xInvalidUnwindTarget;
            case XCPT_SIGNAL:                   return xSignal;
            default:                            return xUndefined;
         }
      }
   };

   // Thread suchen und Exception-Behandlung aufrufen
   static ULONG CallThreadException(cOS2Exception *exception)
   {
      for ( int i = 0 ; i < MAX_THREADS ; i++ ) {
         if ( RegisteredThreadTab[i].x_mark == exception->x_mark ) {
            if ( RegisteredThreadTab[i].thread->isRunning() ) {
               return RegisteredThreadTab[i].thread->onException(exception) ?
                  XCPT_CONTINUE_EXECUTION
                : XCPT_CONTINUE_SEARCH;
            } else {
               break;
            }
         }
      }

      return XCPT_CONTINUE_SEARCH;
   }

   // ExceptionHandler - Ruft die Exceptionroutine des betroffenen Threads auf
   ULONG APIENTRY ExceptionHandler( PEXCEPTIONREPORTRECORD       x_record,
                                    PEXCEPTIONREGISTRATIONRECORD x_mark,
                                    PCONTEXTRECORD               x_context,
                                    PVOID                        x_pointer  )
   {
      if ( x_record->fHandlerFlags & EH_EXIT_UNWIND )    // process is exiting
         return XCPT_CONTINUE_SEARCH;

      if ( x_record->fHandlerFlags & EH_UNWINDING )      // unwinding exc handlers
         return XCPT_CONTINUE_SEARCH;

      if ( x_record->fHandlerFlags & EH_NESTED_CALL )    // nested exceptions
         return XCPT_CONTINUE_SEARCH;

      if ( x_record->fHandlerFlags & EH_STACK_INVALID )  // stack overflow
         return XCPT_CONTINUE_SEARCH;

      if ( x_record->fHandlerFlags & EH_NONCONTINUABLE )  // stack overflow
         return XCPT_CONTINUE_SEARCH;

      cOS2Exception exception(x_record, x_mark, x_context, x_pointer);
      return CallThreadException(&exception);
   }

   // Registriere neuen Exceptionhandler fuer Thread
   static void *RegisterThread(cThread *thread)
   {
      int i;
      PEXCEPTIONREGISTRATIONRECORD x_mark = new0 EXCEPTIONREGISTRATIONRECORD;

      x_mark->prev_structure = NULL;
      x_mark->ExceptionHandler = ExceptionHandler;

      for ( i = 0 ; i < MAX_THREADS ; i++ ) {
         if ( RegisteredThreadTab[i].thread == NULL ) {
            RegisteredThreadTab[i].thread = thread;
            RegisteredThreadTab[i].x_mark = x_mark;
            RegisteredThreadTab[i].tid    = thread->getThreadId();
            cBase::DbgInfo("OS/2: Thread %d registered", RegisteredThreadTab[i].tid);
            DosSetExceptionHandler(x_mark);
            return x_mark;
         } else if ( RegisteredThreadTab[i].thread == thread || RegisteredThreadTab[i].x_mark == x_mark ) {
            cBase::DbgError("OS/2: Thread %d already registered");
            break;
         }
      }

      if ( i == MAX_THREADS )
         cBase::DbgError("OS/2: Thread table overflow");

      delete x_mark;
      return NULL;
   }

   // Deregistriere Exceptionhandler von Thread (ueber registration_record)
   static void DeregisterThread(void *registration_record)
   {
      PEXCEPTIONREGISTRATIONRECORD x_mark = (PEXCEPTIONREGISTRATIONRECORD)registration_record;

      for ( int i = 0 ; i < MAX_THREADS ; i++ ) {
         if ( RegisteredThreadTab[i].x_mark == x_mark ) {
            RegisteredThreadTab[i].thread = NULL;
            RegisteredThreadTab[i].x_mark = NULL;
            cBase::DbgInfo("OS/2: Thread %d deregistered", RegisteredThreadTab[i].tid);
            DosUnsetExceptionHandler(x_mark);
            return;
         }
      }

      cBase::DbgInfo("OS/2: Could not find registration entry to deregister");
   }

   // Deregistriere alle Exceptionhandler fuer Thread
   static void DeregisterThread(cThread *thread)
   {
      for ( int i = 0 ; i < MAX_THREADS ; i++ ) {
         if ( RegisteredThreadTab[i].thread == thread ) {
            cBase::DbgInfo("OS/2: Thread %d deregistered", RegisteredThreadTab[i].tid);
            DosUnsetExceptionHandler(RegisteredThreadTab[i].x_mark);
            RegisteredThreadTab[i].thread = NULL;
            RegisteredThreadTab[i].x_mark = NULL;
         }
      }
   }

   void cExceptionHandler::raiseAsyncTerminate()
   {
      if ( thread ) {
         EXCEPTIONREPORTRECORD x_record = { 0 };
         EXCEPTIONREGISTRATIONRECORD x_mark = { 0 };
         CONTEXTRECORD x_context = { 0 };
         PVOID x_pointer = NULL;
         x_record.ExceptionNum = XCPT_ASYNC_PROCESS_TERMINATE;
         cOS2Exception exception(&x_record, &x_mark, &x_context, x_pointer);
         thread->onException(&exception);
      }
   }

#elif defined __ECL_W32__

   static void *RegisterThread(cThread *)
      { return (void *)1; }
   static void DeregisterThread(void *)
      { }
   static void DeregisterThread(cThread *)
      { }

   class cW32Exception : public cException {
      EXCEPTION id;
   public:
      cW32Exception(EXCEPTION id)
         { cW32Exception::id = id; }
      EXCEPTION getId() const
         { return id; }
   };

   void cExceptionHandler::raiseAsyncTerminate()
   {
      if ( thread ) {
         cW32Exception exception(cException::xAsyncProcessTerminate);
         thread->onException(&exception);
      }
   }

#else

   // ...

#endif

cExceptionHandler::cExceptionHandler(cThread *thread_to_register)
{
   thread = thread_to_register;
   registration_record = RegisterThread(thread_to_register);
   if ( registration_record == NULL )
      DbgError("cExceptionHandler: Could not register exception handler");
}

cExceptionHandler::~cExceptionHandler()
{
   DeregisterThread(registration_record);
}

void cExceptionHandler::deregisterAllHandlersFor(cThread *thread_to_deregister)
{
   DeregisterThread(thread_to_deregister);
}




#ifdef __INTERFACE__

// ===========================================================================
// cException
// ---------------------------------------------------------------------------
//
// cBase
//  +--cException
//
// ===========================================================================

class __ECL_DLLEXPORT__ cException : public cBase {

public:
   enum EXCEPTION {
      xUndefined,
      xGuardPageViolation,
      xUnableToGrowStack,
      xDatatypeMisalignment,
      xBreakpoint,
      xSingleStep,
      xAccessViolation,
      xIllegalInstruction,
      xFloatDenormalOperand,
      xFloatDivideByZero,
      xFloatInexactResult,
      xFloatInvalidOperation,
      xFloatOverflow,
      xFloatStackCheck,
      xFloatUnderflow,
      xIntegerDivideByZero,
      xIntegerOverflow,
      xPriviledgedInstruction,
      xInPageError,
      xProcessTerminate,
      xAsyncProcessTerminate,
      xNoncontinuableException,
      xInvalidDisposition,
      xUnwind,
      xBadStack,
      xInvalidUnwindTarget,
      xSignal
   };

   virtual EXCEPTION getId() const = 0;

};

#endif /* __INTERFACE__ */


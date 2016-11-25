// ===========================================================================
// base/cppunit/template_tester.cpp                             ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// CPPUNIT Testsuite fuer
//
//    cDebugLog -> cDebugLogTester
//
// ===========================================================================

// Include fuer Testobjekt
#include "debug_log.h"

#include "base/string.h"
#include "base/file.h"
using namespace ecl;

// CppUnit Helper Macros
#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/cppunitmain.h"




// ===========================================================================
// Deklaration cDebugLogTester
// ===========================================================================

class cDebugLogTester : public CppUnit::TestFixture
{

   // ------------------------------------------------------------------------
   // Test Suite
   // ------------------------------------------------------------------------
private:

   // Deklaration der Test Suite (private)
   CPPUNIT_TEST_SUITE( cDebugLogTester );

   // Deklaration der Test Cases in der Test Suite
   CPPUNIT_TEST( BaseSettings );
   CPPUNIT_TEST( TestCase2 );

   // Deklarationsende der Test Suite
   CPPUNIT_TEST_SUITE_END();


   // ------------------------------------------------------------------------
   // Intialisierung / Deinitialisierung
   // ------------------------------------------------------------------------
public:

   // Intitalisierung (vor jedem einzelnen Test Case)
   void setUp() 
   {
   }
   
   // Deinitialisierung (nach jedem einzelnen Test Case)
   void tearDown()
   { 
   }
  

   // ------------------------------------------------------------------------
   // Test Cases
   // ------------------------------------------------------------------------

   void BaseSettings()
   {
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxMessageLength() == 1024 );
      
      CPPUNIT_ASSERT( DEBUG_LOG()->getFile(0) == 0 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxGen(0) == -1 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxSize(0) == -1 );
      
      DEBUG_LOG()->assignIdToFile(0,"test.log");
      
      CPPUNIT_ASSERT( strcmp(DEBUG_LOG()->getFile(0), "test.log") == 0 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxGen(0) == 3 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxSize(0) == 512*1024 );

      DEBUG_LOG()->setLimits(0, 5, 555);

      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxGen(0) == 5 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxSize(0) == 1024 );

      DEBUG_LOG()->assignIdToFile(0,0);

      CPPUNIT_ASSERT( DEBUG_LOG()->getFile(0) == 0 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxGen(0) == -1 );
      CPPUNIT_ASSERT( DEBUG_LOG()->getMaxSize(0) == -1 );
   }

   void TestCase2()
   {
      cFile::Remove("test.log");
      DEBUG_LOG()->assignIdToFile(0,"test.log");
      CPPUNIT_ASSERT( cFile::Exists("test.log") == false );
      
      DEBUG_LOG_TEXT(0,"Erste Zeile");
      CPPUNIT_ASSERT( cFile::Exists("test.log") == true );

      int value = 0xAFFE;
      DEBUG_LOG_PRINTF(0, ("Printf-style: hex value is 0x%04X", value));

      DEBUG_LOG()->setLimits(0,2,1024);
      for (int i=0; i<100; i++) {
         DEBUG_LOG_PRINTF(0, ("Wait for next generation (counter = %d)", i));
      }

      CPPUNIT_ASSERT( cFile::Exists("test.001.log") == true );
      CPPUNIT_ASSERT( cFile::Exists("test.002.log") == true );
      CPPUNIT_ASSERT( cFile::Exists("test.003.log") == false );

      //DEBUG_LOG()->assignIdToFile(0,0);
   }


   // ------------------------------------------------------------------------
   // Test Objekte [in setUp() initialisieren, in tearDown() deinitialisieren]
   // ------------------------------------------------------------------------
private:
   
}; // class cDebugLogTester




// ---------------------------------------------------------------------------
// Test Suite registrieren
// ---------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( cDebugLogTester );



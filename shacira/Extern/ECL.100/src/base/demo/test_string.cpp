
#include "base/eb_str.hpp"

#include <stddef.h>


static void SchnippSchnapp( void )
{
   cString sl, sr, sm;
   cString s = "Das ist ein l„nglicher";

   s += " String";
   sl = s.getLeft(7); /* das ist */
   sr = s.getRight(6);
   sm = s.getMid(12,10);
   cout << "s=" << s << endl;
   cout << "sl=" << sl << endl;
   cout << "sm=" << sm << endl;
   cout << "sr=" << sr << endl;
   s = s.getLeft(12) + "d„mlicher" + s.getRight(7);
   cout << s << endl;
   s[1] = 'e';
   cout << s << endl;
}

static void TrimDich( void )
{
   cString s = "     Blanks am Anfang und am Ende      ";
   cout << '*' << s << "*\n";
   cout << '*' << s.trimLeft() << "*\n";
   cout << '*' << s.trimRight() << "*\n";
}

static void KonverTier( void )
{
   cString s = "3.14159";

   cout << "pi=" << s << " oder " << s.getDouble() << endl;
}

static cString Cat3( cString& s1, cString& s2, cString& s3 )
{
   return s1+s2+s3;
}

static void coutstring( cString s )
{
   cout << s;
}

static cString cStringByPointer( cString *sp )
{
   cString test = *sp;
   *sp << "---";
   test << "***";
   cout << "test = "; coutstring(test);
   cout << "\n*sp = "; coutstring(*sp); cout << endl;
   return test;
}

void ConDestructPtr( void )
{
   cString s = "Der String";
   cString *ps  = &s;
   cString *ps2 = ps;
   cString result =  cStringByPointer( ps );
   cout << "s=" << s << endl;
   cout << "result=" << result << endl;
   cout << "ps2=" << *ps2 << endl;
}

void test( void )
{
   cString s1("Hallo");
   cString s2 = "Udo";
   cString s11 = s1;
   cString *s3;
   cString big(200);
   big.showDebugInfo();
   big = "Bigstring: ";

   s3 = new cString("Welt");
   s1.showDebugInfo();
   s2.showDebugInfo();
   s3->showDebugInfo();
   big.showDebugInfo();

   cout << "s1=" << s1 << endl;
   cout << "s2=" << s2 << endl;
   cout << "s3=" << *s3 << endl;
   cout << "s1+s2=" << s1+s2 << endl;

   cout << Cat3( s11, *s3, s2 ) << endl;

   big += s1;
   big += *s3;
   cout << "big=" << big;
   delete s3;
}

void assert_test()
{
   cString test("HUND");
   cString null;

   int chr;
   cString str;

   cout << "*** test = '" << test << "'" << endl
        << "*** null.isNull() == true" << endl;

   chr = test[-1]; // bad -> 0
   cout << "*** Assertion: test[-1] = " << chr << endl;

   chr = test[4]; // ok -> 0
   cout << "*** Ok: test[4] = " << chr << endl;

   chr = test[5];       // bad -> 0
   cout << "*** Assertion: test[4] = " << chr << endl;

   str = null.getMid(0);     // bad -> cString()
   cout << "*** Assertion: null.getMid(0) = '" << str << "'" << endl;

   str = test.getMid(-1);    // bad -> "HUND"
   cout << "*** Assertion: test.getMid(-1) = '" << str << "'" << endl;

   str = test.getMid(4);     // ok -> ""
   cout << "*** Ok: test.getMid(4) = '" << str << "'" << endl;
   
   str = test.getMid(5);     // bad -> ""
   cout << "*** Assertion: test.getMid(5) = '" << str << "'" << endl;

   str = test.trim();
   cout << "*** Ok: test.trim() = '" << str << "'" << endl;

   test = "   <3SPACE>   ";
   cout << "*** test = '" << test << "'" << endl;

   str = test.trimLeft();
   cout << "*** Ok: test.trimLeft() = '" << str << "'" << endl;

   str = test.trimRight();
   cout << "*** Ok: test.trimRight() = '" << str << "'" << endl;

   str = test.trim();
   cout << "*** Ok: test.trim() = '" << str << "'" << endl;

}


#include "stdio.h"

void buffer_test()
{
   cout << endl << endl << "--- buffer --- buffer --- buffer --- buffer --- buffer ---" << endl;
   cout << "### Konstruktor & Zuweisung" << endl;
   cString buf = "Alter Inhalt";
   buf.showDebugInfo();

   cout << "### Kopie old = buf" << endl;
   cString old = buf;
   buf.showDebugInfo();
   old.showDebugInfo();

   cout << "### lockBuffer" << endl;
   char *ptr = buf.lockBuffer(100);
   buf.showDebugInfo();
   old.showDebugInfo();

   cout << "### sprintf" << endl;
   sprintf(ptr, "Das ist das haus vom nikolaus");
   buf.showDebugInfo();
   old.showDebugInfo();

   cout << "### unlockBuffer" << endl;
   buf.unlockBuffer();
   buf.showDebugInfo();
   old.showDebugInfo();

   cout << "### Kopie zurueck buf = old" << endl;
   buf = old;
   buf.showDebugInfo();
   old.showDebugInfo();

   cout << "### Testende" << endl;
}

class cDemo : public cString {
public:
   cDemo() {
      setDebug(1);
      cBase::setDebugMask("Error Info");

      showDiagnostic();
      ConDestructPtr();
      showDiagnostic();
      test();
      showDiagnostic();
      SchnippSchnapp();
      showDiagnostic();
      TrimDich();
      showDiagnostic();
      KonverTier();
      showDiagnostic();
   
      cout << endl << endl << "--- neu --- neu --- neu --- neu --- neu ---" << endl;
      assert_test();
      showDiagnostic();

      {
         cString a("Hund Katze Maus");
         cString b = a;
         cString c = a.replace("Katze","Oger");
      
         cout << "Vorher: " << a << endl 
              << "Danach: " << a << " Katze -> Oger: " << c << endl;
         if (a != b) {
            cout << "***** SEITENEFFEKT *****" << endl;
         }
      }
      showDiagnostic();

      buffer_test();
      showDiagnostic();
   }
};

void main( void )
{
   cDemo();
}

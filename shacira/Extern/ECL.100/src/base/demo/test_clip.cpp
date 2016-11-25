//
// test_clip.cpp
//

#include "base/eb_clip.hpp"

static cClipboardFormat my_cbf("Hollaroedullioeh");
static cClipboardFormat fmt_text = cClipboardFormat::getFmtText();
static cClipboardFormat fmt_bitmap = cClipboardFormat::getFmtBitmap();

void ShowHelp()
{
   cout << "clipview [-o] [-t] [-e]" << endl
        << "purpose: ECL clipboard viewer application" << endl
        << "options: -o = Write sample object data" << endl
        << "         -t = Write sample text data" << endl
        << "         -e = Empty clipboard" << endl;
}

void EmptyClipboard()
{
   cClipboard cb;
   cb.empty();
}

void WriteTestObjData()
{
   cClipboardData wcbd(my_cbf, cClipboardData::cbiCopy);
   wcbd.addObject("P5", "Bauer",        "Grossknecht, gibst mer mein Loeffel");
   wcbd.addObject("P2", "Grossknecht",  "Loeffel Hollaroedullioeh");
   wcbd.addObject("P3", "Gaildalerin",  "Aufi muesch, Bueb");
   wcbd.addObject("P3", "Bueb",         "Aufi mues i");

   cClipboardData wcbt(fmt_text, cClipboardData::cbiMove);
   wcbt.addObject(0, 0, "Bauer: Grossknecht, gibst mer mein Loeffel\n"
                        "Grossknecht: Loeffel Hollaroedullioeh\n"
                        "Gaildalerin: Aufi muesch, Bueb\n"
                        "Bueb: Aufi mues i\n");

   cClipboard cb;
   cb.setData(wcbd, true);
   cb.setData(wcbt, false);
}

void WriteTestTextData()
{
   cClipboardData wcbd(cClipboardFormat::getFmtText());
   wcbd.addObject(0, 0, "Aufi auf des Berges Hoeh'n! Aufi mues i auf'n Berg!");

   cClipboard cb;
   cb.setData(wcbd);
}

void ShowClipboardData(const cClipboardData& cbd)
{
   cClipboardFormat cbf = cbd.getFormat();
   static const char *insert_types[] =
      { "Undef", "NoChange", "DRAG", "COPY", "MOVE" };

   cout << "Clipboard Format is '" << cbf.getFormat() << "'"
        << ", Version " << cbf.getVersion()
        << ", inserted by " << insert_types[cbd.getInsertType()]
        << endl;

   for ( int i = 0 ; i < cbd.getObjectCount() ; i++ ) {
      cout << "obj " << i << ": "
           << "sig=" << cbd.getObjectSignature(i) << ", "
           << "name=" << cbd.getObjectName(i) << ", "
           << "data='" << cbd.getObjectDataStr(i) << "'" << endl;
   }
}

void ShowClipboard()
{
   cClipboard cb;
   cClipboardFormat cbf;
   cClipboardData cbd;

   if ( cb.isEmpty() ) {
      cout << "Clipboard is empty." << endl;
   } else {
      if ( cb.isAvailable(fmt_text) && cb.getData(cbd, fmt_text) )
         ShowClipboardData(cbd);
      if ( cb.isAvailable(fmt_bitmap) && cb.getData(cbd, fmt_bitmap) )
         ShowClipboardData(cbd);
      if ( cb.getData(cbd) )
         ShowClipboardData(cbd);
   }
}

int main(int argc, char *argv[])
{
   if ( argc > 1 && stricmp(argv[1], "-o") == 0 ) {
      WriteTestObjData();
   } else if ( argc > 1 && stricmp(argv[1], "-t") == 0 ) {
      WriteTestTextData();
   } else if ( argc > 1 && stricmp(argv[1], "-e") == 0 ) {
      EmptyClipboard();
   } else if ( argc > 1 ) {
      ShowHelp();
   }

   ShowClipboard();

   return 0;
}


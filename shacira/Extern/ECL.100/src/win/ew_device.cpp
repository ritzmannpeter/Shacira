// ===========================================================================
// ew_device.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdDevice
//         |
//         +--cwDevice           - Ausgabegeraet fuer Bildschirmoperationen
//
// ===========================================================================

#include "win/ew_device.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "draw/ed_device.hpp"
#include "win/ew_context.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDevice
// ---------------------------------------------------------------------------
//
// Geraet fuer Bildschirmausgaben. Solange kein konkreter Kontext an das
// Ausgabegeraet gebunden ist, wird ein Anfrage-Kontext zur Verfuegung
// gestellt.
//
//  cBase
//   +--cdDevice
//       +--cwDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDevice : public cdDevice {

public:

   // Konstruktor
   inline cwDevice() { init(); }
   // Destruktor
   ~cwDevice();

   // Kontext an Ausgabegeraet binden
   void bindContext(cdContext *ctxt);


private:

   // Intern: Initialisierung der Klasse
   void init();
   // Anfrage-Kontext fuer Bildschirmoperationen
   cwInfoContext info_ctxt;

};

#endif /*__INTERFACE__*/


// Implementierung cwDevice
// ===========================================================================

void cwDevice::init()
{
   cdDevice::bindContext(&info_ctxt);
   reset();
}

cwDevice::~cwDevice()
{
}

void cwDevice::bindContext(cdContext *ctxt)
{
   cdDevice::bindContext(ctxt == 0 ? &info_ctxt : ctxt);
}



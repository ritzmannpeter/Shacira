// ==========================================================================
// property_interface.h
//
// Deklaration iProperty
//
// Abstrakte Interfaceklasse die einen allgemeinen Property-Mechanismus
// beschreibt. Zugegeben ... die Klasse ist nicht wirklich abstrakt, da alle
// virtuellen Methoden pragmatischerweise eine Defaultimplementierung haben,
// aber das ist nur ein formaler Schoenheitsfehler. 
//
// iProperty
//
// ==========================================================================

#ifndef property_interface_h_included
#define property_interface_h_included


class iProperty
{
public:
   // Fuer alle set/getProperty-Methoden gilt: Wenn die Eigenschaft nicht
   // gesetzt oder gelesen werden kann, wird false zurueckgeliefert:
   //
   // - der Datentyp wird grundsaetzlich nicht unterstuetzt oder
   // - die Eigenschaft gibt es nicht (prop_name ist unbekannt) oder
   // - die Eigenschaft hat einen anderen Datentyp
   // - es gibt zwar grundsaetzlich die Eigenschaft und der Datentyp stimmt,
   //   aber z.Zt. ist kein Zugriff darauf moeglich.

   virtual bool SetProperty(const char *prop_name, int value) { return false; }
   virtual bool GetProperty(const char *prop_name, int &value) { return false; }

   virtual bool SetProperty(const char *prop_name, unsigned int value) { return false; }
   virtual bool GetProperty(const char *prop_name, unsigned int &value) { return false; }

   virtual bool SetProperty(const char *prop_name, bool value) { return false; }
   virtual bool GetProperty(const char *prop_name, bool &value) { return false; }

   virtual bool SetProperty(const char *prop_name, double value) { return false; }
   virtual bool GetProperty(const char *prop_name, double &value) { return false; }

   //virtual bool SetProperty(const char *prop_name, const char *value) { return false; }
   //virtual bool GetProperty(const char *prop_name, char *value, size_t size) { return false; }
};


#endif // property_interface_h_included

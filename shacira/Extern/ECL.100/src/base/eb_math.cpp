// ===========================================================================
// eb_math.cpp                                   ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cX                      - ?
//
// ===========================================================================

#include "base/eb_math.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include <math.h>
#include "base/eb_base.hpp"


// Utility Macros
// ===========================================================================

#define ZDELTA 0.000001
#define PI 3.14159265358979393846264338


// Utility Macros / Templates
// ===========================================================================

#if defined sqr
   #undef sqr
#endif

#if defined __ECL_ICC__
   #define sqr(a) ((a) * (a))
#else
   template<class T> inline T sqr(T a)
      { return a * a; }
#endif


// Utility Functions
// ===========================================================================

// Umwandlung Gradmass -> Bogenmass
inline double rad(double a)
   { return a * PI/180.0; }

// Umwandlung Bogenmass -> Gradmass
inline double deg(double a)
   { return a * 180.0/PI; }

// Vorzeichenermittlung
inline int sign_of(int x)
   { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
inline int sign_of(double x)
   { return fabs(x) < ZDELTA ? 0 : (x < 0 ? -1 : 1); }

// Umwandlung Bogenmass -> Gradmass (long)
inline long ldeg(double angle)
   { return (long)(deg(angle) * 1e5 + sign_of(angle) * 0.5); }

// Pruefen auf 0.0
inline bool is_zero(double x)
   { return fabs(x) < ZDELTA; }

// Pruefen auf Gleichheit
inline bool is_equal(double x, double y)
   { return fabs(x - y) < ZDELTA; }

// Runden auf Genauigkeit 'prec'
inline double round(double x, int prec)
   { double pwr = pow(10.0, prec);
     return floor(x*pwr + 0.5) / pwr; }

// Wert in Intervall einpassen
#if defined __ECL_ICC__
   #define min_max(val,min,max) ((val) < (min) ? (min) : (val) > (max) ? (max) : (val))
#else
   template<class T> inline T min_max(T val, T min, T max)
      { return (val) < (min) ? (min) : (val) > (max) ? (max) : (val); }
#endif

#endif /*__INTERFACE__*/


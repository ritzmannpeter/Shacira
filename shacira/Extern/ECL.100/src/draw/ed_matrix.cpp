// ===========================================================================
// ed_matrix.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cdMatrix             - Basisklasse (inkl. Matrixmultiplikation)
//     |
//     +--cdMatrixScale    - Konstruktion von Matrizen zur Skalierung
//     |
//     +--cdMatrixRot      - Konstruktion von Matrizen zur Rotation
//     |
//     +--cdMatrixTransl   - Konstruktion von Matrizen zur Translation
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>

#include "draw/ed_matrix.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_geo2d.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMatrix
// ---------------------------------------------------------------------------
//
// Definiert eine Transformationsmatrix M sowie Operationen darauf.
//
//        | M11 M12  0 |
//    M = | M21 M22  0 |
//        | Dx  Dy   1 |
//
//  cdMatrix
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMatrix {

public:

   // Transformationsmatrix
   double M11, M12;
   double M21, M22;
   double Dx,  Dy;


   // Default-Konstruktor (Einheitsmatrix)
   cdMatrix();
   // Copy-Konstruktor
   cdMatrix(const cdMatrix& other);
   // Konstruktor ueber Einzelkomponenten
   cdMatrix(double m11, double m12, double m21, double m22, double dx, double dy);

   // Multiplikation (Ma * Mb => Mc)
   friend cdMatrix operator*(const cdMatrix& ma, const cdMatrix& mb);
   // Multiplikation und Zuweisung
   cdMatrix& operator*=(const cdMatrix& other);

   // Einheitsmatrix herstellen
   void makeIdent();

   // Transformation von Koordinaten
   void trans(double& x, double& y) const
      { x = M11*x + M21*y + Dx;
        y = M12*x + M22*y + Dy; }
   // Transformation eines Vektors
   c2dVector trans(const c2dVector& v) const
      { return c2dVector(M11*v.x + M21*v.y + Dx, M12*v.x + M22*v.y + Dy); }
   // Transformation eines Punktes
   c2dPoint trans(const c2dPoint& p) const
      { return c2dVector(M11*p.x + M21*p.y + Dx, M12*p.x + M22*p.y + Dy); }

};

#endif /*__INTERFACE__*/


// Implementierung cdMatrix
// ===========================================================================

cdMatrix::cdMatrix()
{
   makeIdent();
}

cdMatrix::cdMatrix(const cdMatrix& other)
{
   M11 = other.M11; M12 = other.M12;
   M21 = other.M21; M22 = other.M22;
   Dx  = other.Dx;  Dy  = other.Dy;
}

cdMatrix::cdMatrix(double m11, double m12, double m21, double m22, double dx, double dy)
{
   M11 = m11; M12 = m12;
   M21 = m21; M22 = m22;
   Dx  = dx;  Dy  = dy;
}

void cdMatrix::makeIdent()
{
   M11 = M22 = 1.0;
   M21 = M12 = 0.0;
   Dx  = Dy  = 0.0;
}

cdMatrix operator*(const cdMatrix& ma, const cdMatrix& mb)
{
   return cdMatrix(
      /*M11*/ ma.M11*mb.M11 + ma.M12*mb.M21,
      /*M12*/ ma.M11*mb.M12 + ma.M12*mb.M22,
      /*M21*/ ma.M21*mb.M11 + ma.M22*mb.M21,
      /*M22*/ ma.M21*mb.M12 + ma.M22*mb.M22,
      /*Dx */ ma.Dx*mb.M11 + ma.Dy*mb.M21 + mb.Dx,
      /*Dy */ ma.Dx*mb.M12 + ma.Dy*mb.M22 + mb.Dy
   );
}

cdMatrix& cdMatrix::operator*=(const cdMatrix& other)
{
   return *this = cdMatrix(
      /*M11*/ M11*other.M11 + M12*other.M21,
      /*M12*/ M11*other.M12 + M12*other.M22,
      /*M21*/ M21*other.M11 + M22*other.M21,
      /*M22*/ M21*other.M12 + M22*other.M22,
      /*Dx */ Dx*other.M11 + Dy*other.M21 + other.Dx,
      /*Dy */ Dx*other.M12 + Dy*other.M22 + other.Dy
   );
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMatrixScale
// ---------------------------------------------------------------------------
//
// Konstruktion von Matrizen zur Skalierung
//
//        | sx  0   0 |
//    M = | 0   sy  0 |
//        | 0   0   1 |
//
//  cdMatrix
//   +--cdMatrixScale
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMatrixScale : public cdMatrix {

public:

   // Gleiche Skalierung in x und y
   cdMatrixScale(double scale) :
      cdMatrix(scale, 0.0  ,
               0.0  , scale,
               0.0  , 0.0  ) { }

   // Unabhaengige Skalierung in x und y
   cdMatrixScale(double scale_x, double scale_y) :
      cdMatrix(scale_x, 0.0    ,
               0.0    , scale_y,
               0.0    , 0.0    ) { }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMatrixRot
// ---------------------------------------------------------------------------
//
// Konstruktion von Matrizen zur Rotation
//
//        | cos_a -sin_a  0 |
//    M = | sin_a  cos_a  0 |
//        | 0      0      1 |
//
//  cdMatrix
//   +--cdMatrixRot
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMatrixRot : public cdMatrix {

public:

   // Rotation um Winkel 'angle' (Bogenmass)
   cdMatrixRot(double angle)
   {
      double sin_angle = sin(angle);
      double cos_angle = cos(angle);

      M11 = cos_angle; M12 = -sin_angle;
      M21 = sin_angle; M22 = cos_angle;
   }

   // Rotation um Winkel 'angle' (gegeben sin_angle, cos_angle)
   cdMatrixRot(double sin_angle, double cos_angle) :
      cdMatrix(cos_angle, -sin_angle,
               sin_angle,  cos_angle,
               0.0      ,  0.0      ) { }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMatrixTransl
// ---------------------------------------------------------------------------
//
// Konstruktion von Matrizen zur Translation
//
//        | 1   0   0 |
//    M = | 0   1   0 |
//        | dx  dy  1 |
//
//  cdMatrix
//   +--cdMatrixTransl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMatrixTransl : public cdMatrix {

public:

   // Translation um dx, dy
   cdMatrixTransl(double dx, double dy) :
      cdMatrix(1.0, 0.0,
               0.0, 1.0,
               dx , dy ) { }

   // Translation um Vektor
   cdMatrixTransl(const c2dVector& v) :
      cdMatrix(1.0, 0.0,
               0.0, 1.0,
               v.x, v.y) { }

};

#endif /*__INTERFACE__*/




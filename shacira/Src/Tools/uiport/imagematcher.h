
#ifndef _imagematcher_h_
#define _imagematcher_h_

#include <qimage.h>

class PixelEvaluation
{
public:
   int pixelCount;
   int redMatchCount;
   int greenMatchCount;
   int blueMatchCount;
   int alphaMatchCount;
   double redMatchDeviation;
   double greenMatchDeviation;
   double blueMatchDeviation;
   double alphaMatchDeviation;
};

class ImageMatcher
{
public:
   bool match(const QImage & image1, const QImage & image2) const;
   void collectPixelData(const QImage & image1, const QImage & image2, int scanLines, PixelEvaluation & pixelEvaluation) const;
};

#endif // _imagematcher_h_

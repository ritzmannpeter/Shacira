
#include "imagematcher.h"

bool ImageMatcher::match(const QImage & image1, const QImage & image2) const
{
#define SCAN_LINES            6
#define DEVIATION_THRESHHOLD  0.95

   int srcWidth = image1.width();
   int dstWidth = image2.width();
   int srcHeight = image1.height();
   int dstHeight = image2.height();
   int srcSize = srcWidth * srcHeight;
   int dstSize = dstWidth * dstHeight;
   int srcByteCount = image1.byteCount();
   int dstByteCount = image2.byteCount();
   unsigned char * srcBits = (unsigned char*)image1.bits();
   unsigned char * dstBits = (unsigned char*)image2.bits();
   if (srcByteCount == 0) {
      return false;
   }
   if (dstByteCount == 0) {
      return false;
   }
   if (srcBits == NULL) {
      return false;
   }
   if (dstBits == NULL) {
      return false;
   }
   if (srcByteCount == dstByteCount) {
      if (memcmp(srcBits, dstBits, srcByteCount) == 0) {
         return true;
      }
   }
   if (srcWidth == dstWidth &&
       srcHeight == dstHeight) {
      PixelEvaluation pixelEvaluation;
      collectPixelData(image1, image2, SCAN_LINES, pixelEvaluation);
      bool matched = false;
      if (pixelEvaluation.redMatchDeviation < DEVIATION_THRESHHOLD) {
         matched = false;
      } else if (pixelEvaluation.greenMatchDeviation < DEVIATION_THRESHHOLD) {
         matched = false;
      } else if (pixelEvaluation.blueMatchDeviation < DEVIATION_THRESHHOLD) {
         matched = false;
      } else if (pixelEvaluation.alphaMatchDeviation < 1) {
         matched = false;
      } else {
         matched = true;
      }
      if (!matched) {
         // resolves matching problem with general pixmaps in mosaicframe
         if (pixelEvaluation.redMatchDeviation == pixelEvaluation.greenMatchDeviation &&
             pixelEvaluation.greenMatchDeviation == pixelEvaluation.blueMatchDeviation &&
             pixelEvaluation.alphaMatchDeviation == 1) {
            if (srcWidth == 27 && dstWidth == 27 &&
                srcHeight == 27 && dstHeight == 27) {
               // works around matching problem with light_green.png, light_grey.png, light_red.png and light_orange.png
               // (mosaic)
               int dummy = 0;
            } else {
               matched = true;
            }
         }
      }
      return matched;
   }
   return false;
}

void ImageMatcher::collectPixelData(const QImage & image1, const QImage & image2, int scanLines, PixelEvaluation & pixelEvaluation) const
{
#define PIXEL_DISTANCE_TRESHHOLD    32
   int width = image1.width();
   int height = image1.height();
   int redMatchCount = 0;
   int greenMatchCount = 0;
   int blueMatchCount = 0;
   int alphaMatchCount = 0;
   int colOffset = (width / scanLines) / 2;
   int col = 0;
   int rowOffset = (height / scanLines) / 2;
   int row = 0;
   int r = 0;
   int c = 0;
   int pixelCount = 0;
   for (row=rowOffset; row<height; row+=rowOffset) {
      for (c=0; c<width; c++) {
         QRgb srcPixel = image1.pixel(c, row);
         QRgb dstPixel = image2.pixel(c, row);
         if (srcPixel == 0 &&
             dstPixel == 16777215) {
            redMatchCount++;
            greenMatchCount++;
            blueMatchCount++;
            alphaMatchCount++;
         } else if (dstPixel == 0 &&
                    srcPixel == 16777215) {
            redMatchCount++;
            greenMatchCount++;
            blueMatchCount++;
            alphaMatchCount++;
         } else {
            if (qAbs(qRed(srcPixel) - qRed(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               redMatchCount++;
            }
            if (qAbs(qGreen(srcPixel) - qGreen(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               greenMatchCount++;
            }
            if (qAbs(qBlue(srcPixel) - qBlue(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               blueMatchCount++;
            }
            if (qAbs(qAlpha(srcPixel) - qAlpha(dstPixel)) < 1) {
               alphaMatchCount++;
            }
         }
         pixelCount++;
      }
   }
   for (col=colOffset; col<width; col+=colOffset) {
      for (r=0; r<height; r++) {
         QRgb srcPixel = image1.pixel(col, r);
         QRgb dstPixel = image2.pixel(col, r);
         if (srcPixel == 0 &&
             dstPixel == 16777215) {
            redMatchCount++;
            greenMatchCount++;
            blueMatchCount++;
            alphaMatchCount++;
         } else if (dstPixel == 0 &&
                    srcPixel == 16777215) {
            redMatchCount++;
            greenMatchCount++;
            blueMatchCount++;
            alphaMatchCount++;
         } else {
            if (qAbs(qRed(srcPixel) - qRed(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               redMatchCount++;
            }
            if (qAbs(qGreen(srcPixel) - qGreen(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               greenMatchCount++;
            }
            if (qAbs(qBlue(srcPixel) - qBlue(dstPixel)) < PIXEL_DISTANCE_TRESHHOLD) {
               blueMatchCount++;
            }
            if (qAbs(qAlpha(srcPixel) - qAlpha(dstPixel)) < 1) {
               alphaMatchCount++;
            }
         }
         pixelCount++;
      }
   }
   int pointMatchCount = 0;
   int pointPixelCount = 0;
   for (row=rowOffset; row<height; row+=rowOffset) {
      for (col=colOffset; col<width; col+=colOffset) {
         QRgb srcPixel = image1.pixel(col, row);
         QRgb dstPixel = image2.pixel(col, row);
         if (qRed(srcPixel) == qRed(dstPixel) &&
             qGreen(srcPixel) == qGreen(dstPixel) &&
             qBlue(srcPixel) == qBlue(dstPixel) &&
             qAlpha(srcPixel) == qAlpha(dstPixel)) {
            pointMatchCount++;
         }
         pointPixelCount++;
      }
   }
   pixelEvaluation.redMatchCount = redMatchCount;
   pixelEvaluation.greenMatchCount = greenMatchCount;
   pixelEvaluation.blueMatchCount = blueMatchCount;
   pixelEvaluation.alphaMatchCount = alphaMatchCount;
   pixelEvaluation.pixelCount = pixelCount;
   pixelEvaluation.redMatchDeviation = (double)(redMatchCount) / (double)(pixelCount);
   pixelEvaluation.greenMatchDeviation = (double)(greenMatchCount) / (double)(pixelCount);
   pixelEvaluation.blueMatchDeviation = (double)(blueMatchCount) / (double)(pixelCount);
   pixelEvaluation.alphaMatchDeviation = (double)(alphaMatchCount) / (double)(pixelCount);
}


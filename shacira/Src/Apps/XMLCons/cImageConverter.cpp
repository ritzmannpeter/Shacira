
#include "FirstHeader.h"
#include "cImageConverter.h"
#include "cAlloc.h"
#include <qimage.h>
#include <qbuffer.h>

static const QRgb _GrayTable[] = 
{
   0xff000000,0xff010101,0xff020202,0xff030303,0xff040404,0xff050505,0xff060606,0xff070707,0xff080808,0xff090909,0xff0a0a0a,0xff0b0b0b,0xff0c0c0c,0xff0d0d0d,0xff0e0e0e,0xff0f0f0f,
	0xff101010,0xff111111,0xff121212,0xff131313,0xff141414,0xff151515,0xff161616,0xff171717,0xff181818,0xff191919,0xff1a1a1a,0xff1b1b1b,0xff1c1c1c,0xff1d1d1d,0xff1e1e1e,0xff1f1f1f,
	0xff202020,0xff212121,0xff222222,0xff232323,0xff242424,0xff252525,0xff262626,0xff272727,0xff282828,0xff292929,0xff2a2a2a,0xff2b2b2b,0xff2c2c2c,0xff2d2d2d,0xff2e2e2e,0xff2f2f2f,
	0xff303030,0xff313131,0xff323232,0xff333333,0xff343434,0xff353535,0xff363636,0xff373737,0xff383838,0xff393939,0xff3a3a3a,0xff3b3b3b,0xff3c3c3c,0xff3d3d3d,0xff3e3e3e,0xff3f3f3f,
	0xff404040,0xff414141,0xff424242,0xff434343,0xff444444,0xff454545,0xff464646,0xff474747,0xff484848,0xff494949,0xff4a4a4a,0xff4b4b4b,0xff4c4c4c,0xff4d4d4d,0xff4e4e4e,0xff4f4f4f,
	0xff505050,0xff515151,0xff525252,0xff535353,0xff545454,0xff555555,0xff565656,0xff575757,0xff585858,0xff595959,0xff5a5a5a,0xff5b5b5b,0xff5c5c5c,0xff5d5d5d,0xff5e5e5e,0xff5f5f5f,
	0xff606060,0xff616161,0xff626262,0xff636363,0xff646464,0xff656565,0xff666666,0xff676767,0xff686868,0xff696969,0xff6a6a6a,0xff6b6b6b,0xff6c6c6c,0xff6d6d6d,0xff6e6e6e,0xff6f6f6f,
	0xff707070,0xff717171,0xff727272,0xff737373,0xff747474,0xff757575,0xff767676,0xff777777,0xff787878,0xff797979,0xff7a7a7a,0xff7b7b7b,0xff7c7c7c,0xff7d7d7d,0xff7e7e7e,0xff7f7f7f,
	0xff808080,0xff818181,0xff828282,0xff838383,0xff848484,0xff858585,0xff868686,0xff878787,0xff888888,0xff898989,0xff8a8a8a,0xff8b8b8b,0xff8c8c8c,0xff8d8d8d,0xff8e8e8e,0xff8f8f8f,
	0xff909090,0xff919191,0xff929292,0xff939393,0xff949494,0xff959595,0xff969696,0xff979797,0xff989898,0xff999999,0xff9a9a9a,0xff9b9b9b,0xff9c9c9c,0xff9d9d9d,0xff9e9e9e,0xff9f9f9f,
	0xffa0a0a0,0xffa1a1a1,0xffa2a2a2,0xffa3a3a3,0xffa4a4a4,0xffa5a5a5,0xffa6a6a6,0xffa7a7a7,0xffa8a8a8,0xffa9a9a9,0xffaaaaaa,0xffababab,0xffacacac,0xffadadad,0xffaeaeae,0xffafafaf,
	0xffb0b0b0,0xffb1b1b1,0xffb2b2b2,0xffb3b3b3,0xffb4b4b4,0xffb5b5b5,0xffb6b6b6,0xffb7b7b7,0xffb8b8b8,0xffb9b9b9,0xffbababa,0xffbbbbbb,0xffbcbcbc,0xffbdbdbd,0xffbebebe,0xffbfbfbf,
	0xffc0c0c0,0xffc1c1c1,0xffc2c2c2,0xffc3c3c3,0xffc4c4c4,0xffc5c5c5,0xffc6c6c6,0xffc7c7c7,0xffc8c8c8,0xffc9c9c9,0xffcacaca,0xffcbcbcb,0xffcccccc,0xffcdcdcd,0xffcecece,0xffcfcfcf,
	0xffd0d0d0,0xffd1d1d1,0xffd2d2d2,0xffd3d3d3,0xffd4d4d4,0xffd5d5d5,0xffd6d6d6,0xffd7d7d7,0xffd8d8d8,0xffd9d9d9,0xffdadada,0xffdbdbdb,0xffdcdcdc,0xffdddddd,0xffdedede,0xffdfdfdf,
	0xffe0e0e0,0xffe1e1e1,0xffe2e2e2,0xffe3e3e3,0xffe4e4e4,0xffe5e5e5,0xffe6e6e6,0xffe7e7e7,0xffe8e8e8,0xffe9e9e9,0xffeaeaea,0xffebebeb,0xffececec,0xffededed,0xffeeeeee,0xffefefef,
	0xfff0f0f0,0xfff1f1f1,0xfff2f2f2,0xfff3f3f3,0xfff4f4f4,0xfff5f5f5,0xfff6f6f6,0xfff7f7f7,0xfff8f8f8,0xfff9f9f9,0xfffafafa,0xfffbfbfb,0xfffcfcfc,0xfffdfdfd,0xfffefefe,0xffffffff
};

static int ColorCount(int pixel_size)
{
   switch (pixel_size) {
   case 8: return 0xff;
   case 16: return 0xffff;
   case 32: return 0xffffffff;
   }
   return 0xff;
}

#include <stdio.h>
bool cImageConverter::ConvertToJpeg(int pixel_size, int width, int height, unsigned char * image_data,
                                    unsigned char * & buf, int & buf_size)
{
   QImage image = QImage(image_data,
                         width,
                         height,
	                      pixel_size,
                         (unsigned int *)_GrayTable,
                         ColorCount(pixel_size),
                         QImage::BigEndian);
   QByteArray ba;
   QBuffer buffer(ba);
   buffer.open(IO_WriteOnly);
   int quality = -1;
//   image.save("xxx.png", "PNG", quality);
   image.save(&buffer, "PNG", quality);
   if (!ba.isNull()) {
      int conv_size = ba.size();
      unsigned char * conv_data = (unsigned char *)ba.data();
      buf = (unsigned char *)cAlloc::Alloc(conv_size);
      memcpy(buf, conv_data, conv_size);
      buf_size = conv_size;
      FILE * stream = fopen("image.png", "wb+");
      if (stream != NULL) {
         fwrite(buf, 1, buf_size, stream);
         fclose(stream);
      }
      return true;
   } else {
      return false;
   }
}



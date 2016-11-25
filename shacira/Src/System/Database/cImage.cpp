//## begin module%40306E69033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40306E69033C.cm

//## begin module%40306E69033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40306E69033C.cp

//## Module: cImage%40306E69033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cImage.cpp

//## begin module%40306E69033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40306E69033C.additionalIncludes

//## begin module%40306E69033C.includes preserve=yes
//## end module%40306E69033C.includes

// cImage
#include "System/Database/cImage.h"
//## begin module%40306E69033C.additionalDeclarations preserve=yes
//## end module%40306E69033C.additionalDeclarations


// Class cImage 





cImage::cImage()
  //## begin cImage::cImage%.hasinit preserve=no
      : _Data(NULL), _ImageData(NULL), _ImageHeader(NULL), _BufferAllocated(false)
  //## end cImage::cImage%.hasinit
  //## begin cImage::cImage%.initialization preserve=yes
  //## end cImage::cImage%.initialization
{
  //## begin cImage::cImage%.body preserve=yes
//_ASSERT_UNCOND
  //## end cImage::cImage%.body
}

cImage::cImage(const cImage &right)
  //## begin cImage::cImage%copy.hasinit preserve=no
      : _Data(NULL), _ImageData(NULL), _ImageHeader(NULL), _BufferAllocated(false)
  //## end cImage::cImage%copy.hasinit
  //## begin cImage::cImage%copy.initialization preserve=yes
  //## end cImage::cImage%copy.initialization
{
  //## begin cImage::cImage%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cImage::cImage%copy.body
}

cImage::cImage (ULONG_T x_size, ULONG_T y_size, UCHAR_T pix_size, ULONG_T color_count)
  //## begin cImage::cImage%1079377737.hasinit preserve=no
      : _Data(NULL), _ImageData(NULL), _ImageHeader(NULL), _BufferAllocated(false)
  //## end cImage::cImage%1079377737.hasinit
  //## begin cImage::cImage%1079377737.initialization preserve=yes
  //## end cImage::cImage%1079377737.initialization
{
  //## begin cImage::cImage%1079377737.body preserve=yes
   ULONG_T image_size = BYTE_SIZE(pix_size) * x_size * y_size;
   _Data = (BUF_T)cSystemUtils::Alloc(image_size + sizeof(IMAGE_HEADER_T));
   _BufferAllocated = true;
   _ImageHeader = (IMAGE_HEADER_T*)_Data;
   _ImageHeader->header_size = sizeof(*_ImageHeader);
   _ImageHeader->image.x_size = x_size;
   _ImageHeader->image.y_size = y_size;
   _ImageHeader->image.pix_size = pix_size;
   _ImageHeader->image.color_count = color_count;
   _ImageHeader->image.image_size = image_size;
   _ImageData = _Data + sizeof(*_ImageHeader);
   _ImageHeader->image_frame.x_size = x_size;
   _ImageHeader->image_frame.y_size = y_size;
  //## end cImage::cImage%1079377737.body
}

cImage::cImage (ULONG_T x_size, ULONG_T y_size, UCHAR_T pix_size, ULONG_T color_count, BUF_T data, ULONG_T data_size)
  //## begin cImage::cImage%1076915515.hasinit preserve=no
      : _Data(NULL), _ImageData(NULL), _ImageHeader(NULL), _BufferAllocated(false)
  //## end cImage::cImage%1076915515.hasinit
  //## begin cImage::cImage%1076915515.initialization preserve=yes
  //## end cImage::cImage%1076915515.initialization
{
  //## begin cImage::cImage%1076915515.body preserve=yes
   ULONG_T image_size = BYTE_SIZE(pix_size) * x_size * y_size;
   if (data == NULL) {
      _Data = (BUF_T)cSystemUtils::Alloc(image_size + sizeof(IMAGE_HEADER_T));
   } else {
      _Data = data;
      if (image_size > data_size) {
         throw cError(IMAGE_BUFFER_TOO_SMALL, 0,
                      cConvUtils::StringValue(image_size + sizeof(IMAGE_HEADER_T)).c_str(),
                      cConvUtils::StringValue(data_size).c_str());
      }
   }
   _ImageHeader = (IMAGE_HEADER_T*)_Data;
   _ImageHeader->header_size = sizeof(*_ImageHeader);
   _ImageHeader->image.x_size = x_size;
   _ImageHeader->image.y_size = y_size;
   _ImageHeader->image.pix_size = pix_size;
   _ImageHeader->image.color_count = color_count;
   _ImageHeader->image.image_size = image_size;
   _ImageData = _Data + sizeof(*_ImageHeader);
   _ImageHeader->image_frame.x_size = x_size;
   _ImageHeader->image_frame.y_size = y_size;
  //## end cImage::cImage%1076915515.body
}

cImage::cImage (BUF_T data)
  //## begin cImage::cImage%1076915523.hasinit preserve=no
      : _Data(NULL), _ImageData(NULL), _ImageHeader(NULL), _BufferAllocated(false)
  //## end cImage::cImage%1076915523.hasinit
  //## begin cImage::cImage%1076915523.initialization preserve=yes
  //## end cImage::cImage%1076915523.initialization
{
  //## begin cImage::cImage%1076915523.body preserve=yes
   _Data = data;
   _ImageHeader = (IMAGE_HEADER_T*)_Data;
   _ImageHeader = (IMAGE_HEADER_T*)_Data;
   _ImageData = _Data + _ImageHeader->header_size;
  //## end cImage::cImage%1076915523.body
}


cImage::~cImage()
{
  //## begin cImage::~cImage%.body preserve=yes
   if (_BufferAllocated && _Data != NULL) {
      cSystemUtils::Free(_Data);
   }
  //## end cImage::~cImage%.body
}



//## Other Operations (implementation)
ULONG_T cImage::GetXSize ()
{
  //## begin cImage::GetXSize%1076915516.body preserve=yes
   return _ImageHeader->image.x_size;
  //## end cImage::GetXSize%1076915516.body
}

ULONG_T cImage::GetYSize ()
{
  //## begin cImage::GetYSize%1076915517.body preserve=yes
   return _ImageHeader->image.y_size;
  //## end cImage::GetYSize%1076915517.body
}

UCHAR_T cImage::GetPixSize ()
{
  //## begin cImage::GetPixSize%1076915518.body preserve=yes
   return _ImageHeader->image.pix_size;
  //## end cImage::GetPixSize%1076915518.body
}

ULONG_T cImage::GetColorCount ()
{
  //## begin cImage::GetColorCount%1076915524.body preserve=yes
   return _ImageHeader->image.color_count;
  //## end cImage::GetColorCount%1076915524.body
}

ULONG_T cImage::GetSize ()
{
  //## begin cImage::GetSize%1076915519.body preserve=yes
   return _ImageHeader->header_size + _ImageHeader->image.image_size;
  //## end cImage::GetSize%1076915519.body
}

ULONG_T cImage::GetImageSize ()
{
  //## begin cImage::GetImageSize%1076915520.body preserve=yes
   return _ImageHeader->image.image_size;
  //## end cImage::GetImageSize%1076915520.body
}

BUF_T cImage::GetData ()
{
  //## begin cImage::GetData%1076915521.body preserve=yes
   return _Data;
  //## end cImage::GetData%1076915521.body
}

BUF_T cImage::GetImageData ()
{
  //## begin cImage::GetImageData%1076915522.body preserve=yes
   return _ImageData;
  //## end cImage::GetImageData%1076915522.body
}

void cImage::SetFrame (ULONG_T x0, ULONG_T y0, ULONG_T x_size, ULONG_T y_size)
{
  //## begin cImage::SetFrame%1077297891.body preserve=yes
   _ImageHeader->image_frame.x0 = x0;
   _ImageHeader->image_frame.y0 = y0;
   _ImageHeader->image_frame.x_size = x_size;
   _ImageHeader->image_frame.y_size = y_size;
  //## end cImage::SetFrame%1077297891.body
}

ULONG_T cImage::GetFrameX0 ()
{
  //## begin cImage::GetFrameX0%1077297894.body preserve=yes
   return _ImageHeader->image_frame.x0;
  //## end cImage::GetFrameX0%1077297894.body
}

ULONG_T cImage::GetFrameY0 ()
{
  //## begin cImage::GetFrameY0%1077297895.body preserve=yes
   return _ImageHeader->image_frame.y0;
  //## end cImage::GetFrameY0%1077297895.body
}

ULONG_T cImage::GetFrameXSize ()
{
  //## begin cImage::GetFrameXSize%1077297892.body preserve=yes
   return _ImageHeader->image_frame.x_size;
  //## end cImage::GetFrameXSize%1077297892.body
}

ULONG_T cImage::GetFrameYSize ()
{
  //## begin cImage::GetFrameYSize%1077297893.body preserve=yes
   return _ImageHeader->image_frame.y_size;
  //## end cImage::GetFrameYSize%1077297893.body
}

BOOL_T cImage::IsEmpty ()
{
  //## begin cImage::IsEmpty%1076931338.body preserve=yes
   if (GetImageSize() == 0) {
      return true;
   } else {
      return false;
   }
  //## end cImage::IsEmpty%1076931338.body
}

ULONG_T cImage::ColorNo (UCHAR_T pix_size)
{
  //## begin cImage::ColorNo%1076915528.body preserve=yes
   switch (pix_size) {
   case 8: return 0xff;
   case 16: return 0xffff;
   case 32: return 0xffffffff;
   }
   return 0xff;
  //## end cImage::ColorNo%1076915528.body
}

// Additional Declarations
  //## begin cImage%40306E69033C.declarations preserve=yes
  //## end cImage%40306E69033C.declarations

//## begin module%40306E69033C.epilog preserve=yes
//## end module%40306E69033C.epilog

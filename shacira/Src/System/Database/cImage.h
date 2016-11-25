//## begin module%40306E69033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40306E69033C.cm

//## begin module%40306E69033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40306E69033C.cp

//## Module: cImage%40306E69033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cImage.h

#ifndef cImage_h
#define cImage_h 1

//## begin module%40306E69033C.includes preserve=yes
//## end module%40306E69033C.includes

//## begin module%40306E69033C.additionalDeclarations preserve=yes

#define IMAGE_HEADER_SIZE     0x200

typedef struct image_frame {
   ULONG_T x0;
   ULONG_T y0;
   ULONG_T x_size;
   ULONG_T y_size;
}  IMAGE_FRAME_T;

typedef struct image {
   UCHAR_T pix_size;
   ULONG_T color_count;
   ULONG_T image_size;
   ULONG_T x_size;
   ULONG_T y_size;
}  IMAGE_T;

typedef struct image_header {
   ULONG_T header_size;
   IMAGE_FRAME_T image_frame;
   IMAGE_T image;
   char reserved[IMAGE_HEADER_SIZE - sizeof(ULONG_T) - sizeof(IMAGE_FRAME_T) - sizeof(IMAGE_T)];
}  IMAGE_HEADER_T;

#define BYTE_SIZE(psize)   (psize / 8)

//## end module%40306E69033C.additionalDeclarations


//## begin cImage%40306E69033C.preface preserve=yes
//## end cImage%40306E69033C.preface

//## Class: cImage%40306E69033C
//	This class covers flat image layouts.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cImage 
{
  //## begin cImage%40306E69033C.initialDeclarations preserve=yes
public:
  //## end cImage%40306E69033C.initialDeclarations

    //## Constructors (generated)
      cImage();

      cImage(const cImage &right);

    //## Constructors (specified)
      //## Operation: cImage%1079377737
      cImage (ULONG_T x_size, ULONG_T y_size, UCHAR_T pix_size, ULONG_T color_count);

      //## Operation: cImage%1076915515
      cImage (ULONG_T x_size, ULONG_T y_size, UCHAR_T pix_size, ULONG_T color_count, BUF_T data, ULONG_T data_size);

      //## Operation: cImage%1076915523
      cImage (BUF_T data);

    //## Destructor (generated)
      virtual ~cImage();


    //## Other Operations (specified)
      //## Operation: GetXSize%1076915516
      virtual ULONG_T GetXSize ();

      //## Operation: GetYSize%1076915517
      ULONG_T GetYSize ();

      //## Operation: GetPixSize%1076915518
      UCHAR_T GetPixSize ();

      //## Operation: GetColorCount%1076915524
      virtual ULONG_T GetColorCount ();

      //## Operation: GetSize%1076915519
      virtual ULONG_T GetSize ();

      //## Operation: GetImageSize%1076915520
      virtual ULONG_T GetImageSize ();

      //## Operation: GetData%1076915521
      virtual BUF_T GetData ();

      //## Operation: GetImageData%1076915522
      virtual BUF_T GetImageData ();

      //## Operation: SetFrame%1077297891
      void SetFrame (ULONG_T x0, ULONG_T y0, ULONG_T x_size, ULONG_T y_size);

      //## Operation: GetFrameX0%1077297894
      virtual ULONG_T GetFrameX0 ();

      //## Operation: GetFrameY0%1077297895
      virtual ULONG_T GetFrameY0 ();

      //## Operation: GetFrameXSize%1077297892
      virtual ULONG_T GetFrameXSize ();

      //## Operation: GetFrameYSize%1077297893
      virtual ULONG_T GetFrameYSize ();

      //## Operation: IsEmpty%1076931338
      virtual BOOL_T IsEmpty ();

  public:
    // Additional Public Declarations
      //## begin cImage%40306E69033C.public preserve=yes
      //## end cImage%40306E69033C.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: Data%403071260157
      //## begin cImage::Data%403071260157.attr preserve=no  protected: BUF_T {U} NULL
      BUF_T _Data;
      //## end cImage::Data%403071260157.attr

      //## Attribute: ImageData%403073EF02EE
      //## begin cImage::ImageData%403073EF02EE.attr preserve=no  protected: BUF_T {U} NULL
      BUF_T _ImageData;
      //## end cImage::ImageData%403073EF02EE.attr

      //## Attribute: ImageHeader%4030753802AF
      //## begin cImage::ImageHeader%4030753802AF.attr preserve=no  protected: IMAGE_HEADER_T * {U} NULL
      IMAGE_HEADER_T *_ImageHeader;
      //## end cImage::ImageHeader%4030753802AF.attr

      //## Attribute: BufferAllocated%4055FFC80261
      //## begin cImage::BufferAllocated%4055FFC80261.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _BufferAllocated;
      //## end cImage::BufferAllocated%4055FFC80261.attr

    // Additional Protected Declarations
      //## begin cImage%40306E69033C.protected preserve=yes
      //## end cImage%40306E69033C.protected

  private:
    // Additional Private Declarations
      //## begin cImage%40306E69033C.private preserve=yes
      //## end cImage%40306E69033C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ColorNo%1076915528
      ULONG_T ColorNo (UCHAR_T pix_size);

    // Additional Implementation Declarations
      //## begin cImage%40306E69033C.implementation preserve=yes
      //## end cImage%40306E69033C.implementation

};

//## begin cImage%40306E69033C.postscript preserve=yes
//## end cImage%40306E69033C.postscript

// Class cImage 

//## begin module%40306E69033C.epilog preserve=yes
//## end module%40306E69033C.epilog


#endif

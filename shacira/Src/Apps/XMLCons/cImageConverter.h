
#ifndef _cImageConverter_h
#define _cImageConverter_h

class cSHClientProcess;
class cContext;

class cImageConverter
{
public:
   static bool ConvertToJpeg(int pixel_size, int width, int height, unsigned char * image_data, unsigned char * & buf, int & buf_size);
};

#endif

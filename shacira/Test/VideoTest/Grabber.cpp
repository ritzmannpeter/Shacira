
#include "Video.h"
#include "Grabber.h"
#include "System/Objects/cObjectLock.h"
#include "System/Database/cImage.h"

Grabber::Grabber(cMutexSem * sync, int idle_time)
   : _Active(false), _Sync(NULL)
{
   for (int i=0; i<IMAGE_COUNT; i++) {
      _Devices[i] = NULL;
   }
   for (i=0; i<IMAGE_COUNT; i++) {
      _Buffers[i] = (BUF_T)cSystemUtils::Alloc(IMAGE_SIZE);
   }
   _Sync = sync;
   _IdleTime = idle_time;
   cControlThread::Start();
};

BUF_T Grabber::Buffer(int index)
{
   if (index < IMAGE_COUNT) {
      return _Buffers[index];
   } else {
      return NULL;
   }
};

void Grabber::Start()
{
   _Active = true;
}

void Grabber::Stop()
{
   _Active = false;
}

void Grabber::SetDevice(cDevice * device, int index)
{
   if (index < IMAGE_COUNT) {
      _Devices[index] = device;
   }
}

int Grabber::ControlFunc ()
{
   if (_Active) {
      Grab();
   }
   return 0;
}

static int no = 0;
static void SaveImage(BUF_T buf)
{
   cImage image(buf);
   ULONG_T size = image.GetImageSize();
   BUF_T data = image.GetImageData();
   char file_name[256] = {0};
   sprintf(file_name, "image%d.raw", no);
   FILE * stream = fopen(file_name, "wb");
   if (stream != NULL) {
      fwrite(data, 1, size, stream);
      fclose(stream);
   }
   no++;
}

void Grabber::Grab()
{
   ULONG_T t = GetTickCount();
   for (int i=0; i<IMAGE_COUNT; i++) {
      cObjectLock __lock__(_Sync);
      if (_Devices[i] != NULL) {
         int retries = 1;
         for (int j=0; j<retries; j++) {
            _Devices[i]->Read("channel1", "Image", IMAGE_SIZE, _Buffers[i], IMAGE_SIZE);
         }
         cSystemUtils::Suspend(_IdleTime);
      }
   }
   printf("Cycle: %d\n", GetTickCount() - t);
};

void Grabber::Save(int index)
{
   cObjectLock __lock__(_Sync);
   if (_Devices[index] != NULL && _Buffers[index] != NULL) {
      _Devices[index]->Read("channel0", "image", IMAGE_SIZE, _Buffers[index], IMAGE_SIZE);
      SaveImage(_Buffers[index]);
   }
};


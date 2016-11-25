#if !defined(__GENTHUNK_H) && !defined(__WIN32__)
#define __GENTHUNK_H


DECLARE_HANDLE32 (HPROC32);
DECLARE_HANDLE32 (HINSTANCE32);

class TGenericThunk
{
    public:
        ~TGenericThunk ();

        bool    IsOK () const { return mInst32 != 0; }

    protected:
        TGenericThunk (const char * fileName);

        DWORD __cdecl CallProc32    (HPROC32, DWORD fAddrCvt, DWORD nArgs, ...);
        void          FreeVdmPtr32  (void far *);
        HPROC32       GetProcAddr32 (const char * procName);
        DWORD         GetVdmPtr16   (void far *buffer, unsigned cbSize);
        void far *    GetVdmPtr32   (DWORD dwAddr32, DWORD cbSize);
        HINSTANCE32   GetInstance   () const { return mInst32; }

    private:
        HINSTANCE32     mInst32;

        static HINSTANCE32 (WINAPI *LoadLibraryEx32W) (LPCSTR, DWORD, DWORD);
        static BOOL        (WINAPI *FreeLibrary32W)   (HINSTANCE32);
        static HPROC32     (WINAPI *GetProcAddress32W)(HINSTANCE32, LPCSTR);
        static DWORD       (WINAPI *GetVDMPointer32W) (LPVOID, UINT);
        static DWORD       (WINAPI *CallProc32W)      (HPROC32, DWORD, DWORD);
};

#endif  // __GENTHUNK_H || __WIN32__


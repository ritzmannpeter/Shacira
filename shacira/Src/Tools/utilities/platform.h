
#ifndef sh_platform_h
#define sh_platform_h 1

/* this header file resolves global platform specific dependencies
*/

#if _MSC_VER >= 1300
#define __WIN32__
#define __MSCPP__
#define __MSCPP_700__
#define __PLATFORM_DEFINED__
#elif _MSC_VER >= 1100
#define __WIN32__
#define __MSCPP__
#define __MSCPP_600__
#define __PLATFORM_DEFINED__
#elif defined(__BORLANDC__)
#if __BCPLUSPLUS__ >= 0x0550
#define __WIN32__
#define __BLCPP__
#define __BLCPP_550__
#define __PLATFORM_DEFINED__
#elif __BCPLUSPLUS__ >= 0x0540
#define __WIN32__
#define __BLCPP__
#define __BLCPP_540__
#define __PLATFORM_DEFINED__
#endif
#elif __GNUC__ >= 3
#define __GCC__
#define __GCC3__
#define __PLATFORM_DEFINED__
#endif

// temporarily while porting
#ifdef __GCC__
typedef void * _EXCEPTION_POINTERS;
typedef const char * LPWSTR;
#endif

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#endif // sh_platform_h


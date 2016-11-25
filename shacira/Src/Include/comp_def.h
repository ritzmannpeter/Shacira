
#ifndef comp_def_h
#define comp_def_h 1

#if defined(_WIN32)
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#if _MSC_VER >= 1100
#pragma warning(disable:4067) /* unexpected tokens following preprocessor directive - expected a newline */
#pragma warning(disable:4101) /* Unreferenzierte lokale Variable */
#pragma warning(disable:4786) /* identifier was truncated to '255' characters in the debug information */
#pragma warning(disable:4503) /* decorated name length exceeded, name was truncated */
#pragma warning(disable:4800) /* Variable wird auf booleschen Wert ('True' oder 'False') gesetzt (Auswirkungen auf Leistungsverhalten moeglich) */
#pragma warning(disable:4996) /* The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strlwr. See online help for details. */
#define PACKED
#ifdef _USRDLL
#define __SH_DLL_EXPORT__ __declspec(dllexport)
#else
#define __SH_DLL_EXPORT__
#endif
#pragma warning(disable:4514)
#pragma warning(disable:4251)
#endif
#elif defined(__linux)
#endif

/// no structured exception handling
#define __TRY__ try
#define __EXCEPT__(args) catch(...)

#endif



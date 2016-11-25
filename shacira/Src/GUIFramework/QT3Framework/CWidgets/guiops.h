

#ifndef GUIOPS_H
#define GUIOPS_H

/// visible state values to be returned by blanking functions

#define elementFree        0x00000000  // element (widget) is visible
                                       // no input restrictions in the case
                                       // of input widgets
#define elementDisabled    0x00000001  // element is visible
                                       // input is disabled on input widgets
#define elementInvisible   0x00000002  // element is unvisible
#define elementUnspecified 0x00000003  // ignore dark function

#define OP_SET_XPOS           0x00000004
#define OP_SET_YPOS           0x00000008
#define OP_SET_COLOR          0x00000010
#define OP_RESET_COLOR        0x00000020
#define OP_RESFUNC1           0x00000040
#define OP_RESFUNC2           0x00000080
#define OP_RESFUNC3           0x000000C0

#define WXPOS(xpos)         ((xpos & 0x00003FFF) << 8)
#define WYPOS(ypos)         ((ypos & 0x00003FFF) << 20)

#define R(r)               ((r & 0x000000FF) << 8)
#define G(g)               ((g & 0x000000FF) << 16)
#define B(b)               ((b & 0x000000FF) << 24)

#define SET_XPOS(xpos)     (WXPOS(xpos) | OP_SET_XPOS)
#define SET_YPOS(ypos)     (WYPOS(ypos) | OP_SET_YPOS)
#define SET_COLOR(r,g,b)   (R((ULONG_T)r) | G((ULONG_T)g) | B((ULONG_T)b) | OP_SET_COLOR)
#define RESET_COLOR(r,g,b) (OP_RESET_COLOR)

#define OP_SET(v, op)      (v & op)

#define GET_STATE(v)       (UCHAR_T)(v & 0x00000007)
#define GET_XPOS(v)        ((v >> 8) & 0x00003FFF)
#define GET_YPOS(v)        ((v >> 20) & 0x00003FFF)
#define GET_R(v)           ((v >> 8) & 0x000000FF)
#define GET_G(v)           ((v >> 16) & 0x000000FF)
#define GET_B(v)           ((v >> 24) & 0x000000FF)

/// action values to be returned by input or init functions

#define actionProceed                     0x00000000     // proceed processing
#define actionReject                      0x00000001     // reject action
#define actionIgnore                      0x00000002     // reserved
#define actionRes2                        0x00000003     // reserved
#define actionRes3                        0x00000004     // reserved
#define actionRes4                        0x00000005     // reserved
#define actionRes5                        0x00000006     // reserved
#define actionRes6                        0x00000007     // reserved
#define actionRes7                        0x00000008     // reserved
#define actionRes8                        0x00000009     // reserved
#define actionRes9                        0x0000000A     // reserved
#define actionRes10                       0x0000000B     // reserved
#define actionRes11                       0x0000000C     // reserved
#define actionRes12                       0x0000000D     // reserved
#define actionRes13                       0x0000000E     // reserved
#define actionRes14                       0x0000000F     // reserved
#define actionDisableDarkFunction         0x10000000     // dark function will be disabled

/// value function flags

#define FFLAG_TARGET    0x00000001


#endif



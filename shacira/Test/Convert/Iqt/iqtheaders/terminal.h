
#ifndef __terminal__
#define __terminal__

#define MAX_TERMINALS                           2
#define MAX_COLS                                                160
#define MAX_ROWS                                                53

/* stream interface types
 */
#define QNX_INTERFACE                           0
#define IQT_INTERFACE                           1

/* screen interface types
 */
#define QNX_ASCII_INTERFACE             0
#define QNX_GRAPHIC_INTERFACE           1
#define IQT_GRAPHIC_INTERFACE           2

typedef UWORD OPTIONS;
typedef UWORD ATTRIBUTES;

typedef struct params
{  UWORD baudrate;
        BYTE charlength;
        BYTE stopbits;
        BYTE parity;
}       PARAMS;

typedef struct stream_interface
{       int type;
        UWORD flags;
        int handle;
        char tty[10];
        FILE * stream;
        OPTIONS options;
        ATTRIBUTES attributes;
        PARAMS params;
}       STREAM_INTERFACE;

typedef struct screen_interface
{       int type;
        UWORD flags;
        int handle;
        int window;
        char tty[10];
        FILE * stream;
        OPTIONS options;
        ATTRIBUTES attributes;
        PARAMS params;
        int cols;
        int rows;
        int font;
        int color;
        int bgcolor;
        int x_origin;
        int y_origin;
}       SCREEN_INTERFACE;

GLOBAL int TERM_Create(int terminal, SCREEN_INTERFACE * screen,
                                                          STREAM_INTERFACE * input);
GLOBAL int TERM_Remove(int terminal);
GLOBAL int TERM_Login(int terminal, STREAM_INTERFACE * keyboard,
                                                          STREAM_INTERFACE * output);
GLOBAL int TERM_Logoff(int terminal);
GLOBAL int TERM_View(int terminal, SCREEN_INTERFACE * screen,
                                                        STREAM_INTERFACE * input);
GLOBAL int TERM_Hide(int terminal);

#define TERM_MISSING_INPUT_DRIVER                               -1
#define TERM_MISSING_OUTPUT_DRIVER                              -2
#define TERM_INPUT_DRIVER_DIED                                  -3
#define TERM_OUTPUT_DRIVER_DIED                                 -4
#define TERM_PARAM_SYNTAX                                                       -5
#define TERM_UNKNOWN_SEQUENCE                                           -6
#define TERM_BUFFER_OVERFLOW                                            -7
#define TERM_INVALID_NOOF_PARAMS                                        -8
#define TERM_UNKNOWN_DESIGNATOR                                 -9
#define TERM_INVALID_ERASE_LINE_PARAM                   -10
#define TERM_INVALID_ERASE_IN_DISPLAY_PARAM     -11

#define TERM_UNABLE_TO_OPEN_INPUT                               -20
#define TERM_UNABLE_TO_GET_INPUT_OPTIONS        -21
#define TERM_UNABLE_TO_SET_INPUT_OPTIONS        -22
#define TERM_UNABLE_TO_GET_INPUT_ATTRIBUTES     -23
#define TERM_UNABLE_TO_SET_INPUT_ATTRIBUTES     -24
#define TERM_UNABLE_TO_GET_INPUT_PARAMS         -25
#define TERM_UNABLE_TO_SET_INPUT_PARAMS         -26
#define TERM_UNKNOWN_MSG_ID                                             -27
#define TERM_ALLOC_MEMORY                                                       -28
#define TERM_UNABLE_TO_OPEN_WINDOW                              -29
#define TERM_NO_WINDOW                                                          -30

#define isnumeric(c)            ((c>47) && (c<58))

/* control codes
 */
#define NUL_                                    0
#define SOH                                             1
#define STX                                             2
#define ETX                                             3
#define EOT                                             4
#define ENQ                                             5
#define ACK                                             6
#define BEL                                             7
#define BS                                              8
#define HT                                              9
#define LF                                              10
#define VT                                              11
#define FF                                              12
#define CR                                              13
#define SO                                              14
#define SI                                              15
#define DLE                                             16
#define DC1                                             17
#define XON                                             17
#define DC2                                             18
#define DC3                                             19
#define XOFF                                    19
#define DC4                                             20
#define NAK                                             21
#define SYN                                             22
#define ETB                                             23
#define CAN                                             24
#define EM                                              25
#define SUB                                             26
#define ESC                                             27
#define FS                                              28
#define GS                                              29
#define RS                                              30
#define US                                              31
#define SP                                              32
#define DEL                                             127

#define IND                                             132
#define NEL                                             133
#define SSA                                             134
#define ESA                                             135
#define HTS                                             136
#define HTJ                                             137
#define VTS                                             138
#define PLD                                             139
#define PLU                                             140
#define RI                                              141
#define SS2                                             142
#define SS3                                             143
#define DSC                                             144
#define PU1                                             145
#define PU2                                             146
#define STS                                             147
#define CCH                                             148
#define MW                                              149
#define SPA                                             150
#define EPA                                             151

#define CSI                                             155
#define ST                                              156
#define OSC                                             157
#define PM                                              158
#define APC                                             159

#define F1                                              0x81
#define F2                                              0x82
#define F3                                              0x83
#define F4                                              0x84
#define F5                                              0x85

#define CHARSET_SIZE                                            (DEL - SP)
#define CHARSET_START                                   SP
typedef char CHARSET[CHARSET_SIZE];
#define ASCII_8Bit(c)                                   (c & 0x0080)
#define CONV_TO_ASCII_7Bit(c)                   c = ((c & 0x007F) - CHARSET_START);
#define CONTROL_CODE(c)                                 (c < SP || (c >= DEL && c < EPA))

#define OPEN_DEVICE                     0x0001
#define USE_DEFAULTS                    0x0002

#endif /* __terminal__ */


#ifndef __program__
#define __program__

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

#define MAX_MARX                                        5
#define UN_MARKED                                       -1
#define ALL_MARKED                              -2

typedef int (*MARKFUNC)(int cursor, int previous_cursor, long context);

typedef struct mark
{       int value;
        MARKFUNC event_func;
        long context;
}       MARK;

typedef struct program
{       int lines, line_len, fill, cursor;
        void * buffer;
        MARK mark[MAX_MARX];
}       PROGRAM;

#define PROG_CURSOR_UP                  1
#define PROG_CURSOR_DOWN                2
#define PROG_CURSOR_SET                 3
#define PROG_CURSOR_START               4
#define PROG_CURSOR_END                 5
#define PROG_CURSOR_ENDMARK     6

GLOBAL PROGRAM * PROG_Create(int line_len, int lines);
GLOBAL int PROG_Delete(PROGRAM * program);
GLOBAL int PROG_Lines(PROGRAM * program);
GLOBAL int PROG_LineLen(PROGRAM * program);
GLOBAL int PROG_Fill(PROGRAM * program);
GLOBAL int PROG_Cursor(PROGRAM * program);
GLOBAL int PROG_LinePosUpdate(PROGRAM * program, int line, void * data);
GLOBAL int PROG_LineUpdate(PROGRAM * program, void * data);
GLOBAL int PROG_LinePosInsert(PROGRAM * program, int line, void * data);
GLOBAL int PROG_LineInsert(PROGRAM * program, void * data);
GLOBAL int PROG_LineAppend(PROGRAM * program, void * data);
GLOBAL int PROG_LinePosPeek(PROGRAM * program, int line, void * data);
GLOBAL int PROG_LinePeek(PROGRAM * program, void * data);
GLOBAL int PROG_LinePosDelete(PROGRAM * program, int line);
GLOBAL int PROG_LineDelete(PROGRAM * program);
GLOBAL int PROG_CursorMove(PROGRAM * program, int direction, int distance);
GLOBAL int PROG_SetMark(PROGRAM * program, int mark, int value, long context);
GLOBAL int PROG_RegisterMarkEvent(PROGRAM * program, int mark, MARKFUNC event_func);

#define NO_MEMORY                                       -1
#define INVALID_LINE                            -2
#define LINE_BUFFER_FULL                -3
#define INVALID_DIRECTION               -4
#define INVALID_MARK                            -5

#endif /* __program__ */





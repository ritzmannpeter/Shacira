**** Error Message file for DPipe / PP
****
**** If there's no APP_MSG_FILE environment variable pointing to this file,
**** it will be searched in the current directory.
****

CLASS#0 information
CLASS#1 warning
CLASS#2 error
CLASS#3 fatal error
CLASS#4 system error

DEFAULT No corresponding message found

MODULE#0 General

I#000 No error
W#000 Module${ $} terminated with active handles
E#000 Initialization error
E#001 Out of memory
E#002 Illegal handle${ in call of function $}
E#003 Illegal parameter${ in call of function $}
E#004 Access to function${ $} denied

MODULE#2 MemPool

E#000 Illegal pool mode
F#000 Corrupted pool list detected by Pool_Exit

MODULE#3 SymTab

E#000 Redeclaration of symbol${ '$'}
E#001 Undefined symbol${ '$'}
E#002 Symbol${ '$'} too long

MODULE#5 CmdArg

E#000 No command line set
E#001 Illegal State
E#002 Cannot open argument file${ '$'}
F#000 INTERNAL: Illegal state

MODULE#7 Stack

E#000 Stack is full
E#001 Stack is empty

MODULE#8 Fifo

E#000 Fifo is full
E#001 Fifo is empty
E#002 Illegal element number in call of Fifo_Peek

MODULE#9 List

I#000 Element already exists

MODULE#10 File

I#000 Tried to read beyond end of file
I#001 No more matching files

E#000 Cannot open file${ '$'}
E#001 Path${ '$'} does not exist
E#002 File${ '$'} exists
E#003 Illegal file specification${ '$'}
E#004 Illegal device${ '$'}
E#005 CLib/Illegal parameter${ using '$'}
E#006 Access to file${ '$'} denied
E#007 Permission denied${ using '$'}
E#008 General I/O error${ in '$'}
E#009 Device${ containing '$'} is full
E#010 Device${ containing '$'} is write protected
E#011 Seek error${ in '$'}
E#012 unget buffer${ of '$'} is full
E#013 Sharing violation${ using '$'}
E#014 Device${ containing '$'} in use
E#015 Device${ containing '$'} is locked
E#016 Pipe${ '$'} is busy
E#017 Device${ containing '$'} is not ready
E#018 Sorry, not yet implemented

F#000 CLib/Illegal file handle
F#001 CLib/Handle table overflow
F#002 CLib/Too many open files
F#003 CLib/Error number${ $}

MODULE#11 PreProc

- Informations
I#000 Unused
I#001 Text constant $ declared but never used
I#002 Redefinition of text constant $ ignored
I#003 Tried to read beyond end of file${ $}
I#004 Call of state $ ignored
- Warnings
W#000 Undefined text constant $ ignored
W#001 Backslash at end of line ignored
W#002 State $ declared but never used
W#003 Function $ declared but never used
W#004 Parameter $1 is never used in $2
W#005 Wildcard $ declared but never used
W#006 Variable $ declared but never used
W#007 Useless EOF-rule in function $
W#008 No system call available
- Errors
E#000 User error $
E#001 Syntax error $
E#002 Redeclaration of variable $
E#003 Undefined variable $1$2{ in call of function $2}
E#004 Unknown option${ '$'}
E#005 Function call in illegal state
E#006 State $ called with wrong number of parameters
E#007 Function $ called with wrong number of parameters
E#008 No corresponding source part for $$$
E#009 Call of state $ inside a parameter
E#010 Illegal wildcard definition
E#011 Redeclaration of builtin function $
E#012 Function$1{ $1} called with illegal parameter$2{ '$2'}
E#013 Unterminated string constant
E#014 Redeclaration of wildcard $
E#015 Undefined wildcard $1
E#016 Duplicate range for wildcard $1
E#017 No range allowed for wildcard $1
E#018 First state may not have parameters
E#019 Illegal number $ following backslash
E#020 Redefinition of internal text constant $
E#021 Empty source part
E#022 "#case" not allowed here
E#023 Rule expected
E#024 Illegal include directive
E#025 Redeclaration of internal variable $
E#026 Internal variable $ may not be changed
E#027 Unexpected character${ '$'}
E#028 Only one init rule allowed
E#029 Only one start rule allowed
E#030 Illegal conditional construct
E#031 Nested branch not allowed
E#032 Illegal branch construct
E#033 Branch not allowed here
E#034 Illegal class description${ '$'}
E#035 Empty branch construct
E#036 Illegal identifier${ '$'}
E#037 Expected '$'
E#038 Unexpected end of file
E#039 Case directive needs 'on' or 'off'
E#040 Illegal debug mask${ '$'}
- Fatal errors
F#000 INTERNAL: Scanner stack overflow
F#001 INTERNAL: Unexpected syntax tree
F#002 INTERNAL: Source stack overflow
F#003 INTERNAL: Limit for source parts exceeded
F#004 Illegal commandline (use option -h for help)
F#005 IO-Error occurred in file${ '$'}
F#006 Cannot open file${ '$'}
F#007 Error(s) ${in file '$' }prevented me from doing my work
F#008 No state defined
F#009 Include filename ${'$' }too long
F#010 Too many nested includes
F#011 Environment variable $ has illegal contents
F#012 Overflow in conversion of real number
F#013 Illegal argument $1{'$1' }in call of function $2
F#014 Cannot create output file${ '$'}
F#015 Cannot create error file${ '$'}
F#016 Illegal argument $1{'$1' }in call of arithmetic function $2

MODULE#12 WinLiB

F#000 No anchor block available
F#001 Cannot create window message queue

MODULE#13 TermWin

I#000 Line not found
E#000 Illegal terminal mode
E#001 Sorry, not yet implemented
E#002 Window is not open
E#003 Window is open
E#004 No popup menu set for this terminal
F#000 Unable to start load thread
F#001 Unable to register window class

MODULE#14 Pipe

I#000 Pipe${ '$'} not connected
I#001 More data available
W#000 End of pipe${ '$'} reached
E#000 General pipe error
E#001 Pipe${ '$'} is busy
E#002 Pipe${ '$'} is broken
E#003 Out of internal memory
E#004 Illegal parameter
E#005 Pipe call interrupted
E#006 Access to pipe${ '$'} denied
E#007 Pipe call not allowed for clients
E#008 Illegal Pipe name${ '$'}
E#009 Sorry, not yet implemented

MODULE#15 Semaphore

E#000 General semaphore error
E#001 Semaphore${ '$'} already exists
E#002 Semaphore${ '$'} is busy

* The End

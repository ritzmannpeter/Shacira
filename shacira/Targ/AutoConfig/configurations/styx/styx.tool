
.name styxw
.description Wrapper for parser generator styx
.command_line styxw $< -makeC -o$@
.target %s_lim.h
.target %s_pim.h
.target %s_int.h
.target %s_lim.c
.target %s_pim.c
.target %s_int.c


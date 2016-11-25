
.name mdlc
.description 2i data model compiler
.command_line mdlc class=gui outputdir=$(intermediate_dir) input=$<
.target %s.h
.target %s.tab.cpp
.target %s.txt


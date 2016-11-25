

.command_line cl -nologo -c -TP $(c_options) $(definitions) -I. $(include_dirs) $< -Fo$@
.target %s.o

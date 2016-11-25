

.command_line cl -nologo -c -TC $(c_options) $(definitions) -I. $(include_dirs) $< -Fo$@
.target %s.o

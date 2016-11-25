
.command_line gcc -mno-cygwin -c $(c_options) $(definitions) -I. $(include_dirs) $< -o$@
.target %s.o

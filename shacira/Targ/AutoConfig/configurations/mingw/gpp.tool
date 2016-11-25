
.command_line g++ -enable-exceptions -mno-cygwin -Wno-deprecated -c $(c_options) $(definitions) -I. $(include_dirs) $< -o$@
.target %s.o

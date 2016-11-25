
.command_line g++ -shared -o$@ $(objects) $(library_dirs) $(libraries) -mthreads -Wl,--enable-runtime-pseudo-reloc -Wl,--allow-multiple-definition

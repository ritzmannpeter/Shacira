
.name omniidl
.description Omniorb CORBA IDL Compiler
.command_line omniidl $(include_dirs) -C$(intermediate_dir) -bcxx -WbBOA -Wba $<
.target %s.hh
.target %sSK.cc
.target %sDynSK.cc

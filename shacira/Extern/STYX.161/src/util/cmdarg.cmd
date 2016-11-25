# [cmdarg.cmd] command description for [cmdarg.c]

Program cmdarg -- Program context translator

# NOTE: This only purpose of this source is the documentation of [cmdarg.c].
# The corresponding [.cim] file will never be read in order to be able to
# translate this program independant from all binary files.
# (allthough the format of the [.cim] files is not machine dependant.)

# >>>>>>> All changes in this source has to be done in      <<<<<<<
# >>>>>>> the function 'CTX_init_cmdarg' [cmda_cim.c], too. <<<<<<<

doc
  <p>'cmdarg' translates a command description file [$CMDENV/Program.cmd] into 
  either a binary image file [$CIMENV/Program.cim] or a C-source module 
  [$CMDGEN/Program_cim.c]. 
  <p>A command description contains all the arguments and environment variables
  necessary for program executes, and, moreover, the options known by the program.
  <br>
  <p>The program accesses this information throuh the module [ctx_app]. 
  <p>The loading, verification and unloading of the current program context 
  can be achieved by the functions 'CTX_init' and 'CTX_quit' within the 
  module [ctx] or the corresponding functions of the generated C-module. 
  <br>In the case of an error program execution stops with a usage message.
  <br>
  <p>[cmd.sty] defines the syntax of a command description file [.cmd].
cod

Arguments

  Command  : name         -- name of the command i.e. program 

Options

  version   : flag = false -- entertainment
  makeC     : flag = false -- generates C-source instead of binary image [.cim]
  shortform : flag = false -- use short form of language name

Environment

  CMDENV   : path = "."   -- [.cmd] source directory 
  CIMENV   : path = "."   -- [.cim] target directory
  CMDGEN   : path = "."   -- [.c] target directory

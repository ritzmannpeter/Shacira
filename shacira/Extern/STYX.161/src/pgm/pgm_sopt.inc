  charset  : string = ""    -- source file character set ( UTF-8, UCS4, ... )
  skipset  : string = ""    -- ( ascii ) characters to be skipped
#ifndef EXCLUDE_OPTION_BINMODE
  binmode  : flag   = false -- scan source file in binary mode ( not with charset-option )
#end
  wprint   : flag   = false -- unicode output ( on non-default character set )
  prepar   : string = ""    -- standard preprocessing: yes or list index~value , ...
  premac   : string = ""    -- standard preprocessing:  pre-defined macro , ...
  prefun   : string = ""    -- user-defined preprocessing: Function@Library ( not with prepar-option )

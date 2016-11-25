  charset   : string = ""    -- source file character set ( UTF-8, UCS4, ... )
  skipset   : string = ""    -- ( ascii ) characters to be skipped
  lookahead : flag   = false -- enable n character lookahead
#ifndef EXCLUDE_OPTION_BINMODE
  binmode   : flag   = false -- scan source file in binary mode ( not with charset-option )
#end
  wprint    : flag   = false -- unicode / UTF-8 output ( on non-default character set )
  prepar    : string = ""    -- standard preprocessing: yes or list index~value , ...
  premac    : string = ""    -- standard preprocessing:  pre-defined macro , ...
  prefun    : string = ""    -- user-defined preprocessing: Function@Library ( not with prepar-option )

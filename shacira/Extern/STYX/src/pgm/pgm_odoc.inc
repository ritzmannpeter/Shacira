
doc
  <p>The options 'prepar' and 'premac' are only useful with styx-like preprocessing. 
  <p>If your language uses the same preprocessing directives as specified in [styx.sty], 
  but differnt macro token identifiers and keywords, the option 'prepar' can be used to 
  enable preprocessing and specify the differences as a comma separated list:
  </p>
  <ol>
  <li><b>0~name of identifier token</b>
  <li><b>1~name of macro definition token</b>
  <li><b>2~name of argument separator token</b>
  <li><b>3~name of include token</b>
  <li><b>4~name of conditional token</b>
  <li><b>5~name of undefine token</b>
  <li><b>6~#macro keyword</b>
  <li><b>7~#end keyword</b>
  <li><b>8~#ifdef keyword</b>
  <li><b>9~#ifndef keyword</b>
  <li><b>10~#else keyword</b>
  <li><b>11~#include keyword</b>
  <li><b>12~#undefine keyword</b>
  <li><b>13~environment variable or path list as search path for include files</b>
  <li><b>14~include file character set ( default: charset-option )</b>
  </ol>
  <p>The option 'premac' supports pre-defined macros in connection with 
  styx-like preprocessing.
  <p>Dynamic library support is a prerequisite for the user-defined callback handler.
cod

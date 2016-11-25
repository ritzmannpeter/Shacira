# [ctoh.cmd] command description for [ctoh.c]

Program ctoh -- C header file generation

doc
  <h3>Overview</h3>

    <p>'ctoh' creates the corresponding header files for all given c source files 
    which represent modules, i.e. don't contain the function 'main'. 
    The lines below show the general structure of the generated header files: 
    <br>
    <pre>
               | Header ...
               | #ifndef <FILE>_INCL
               | #define <FILE>_INCL
               | Includes ...
               | #ifdef __cplusplus
               | extern "C" {
               | #endif
               | Signature ...
               | #ifdef __cplusplus
               | }
               | #endif
               | #endif
    </pre>
    <br>
    <p>The header file will only be produced if there are differences to the previous one.

  <h3>Rules</h3>

    <p>Within each c modul there may be certain groups of lines, called blocks, 
    which belong to the interface. If nothing else is mentioned each interface block starts
    with a word and is followed either by an empty line or the curly bracket '{' at line position 0
    which both marks the end of the block. In the interface copy the curly bracket '{' is replaced 
    by a semicolon ';'. The body within the curly brackets and the curly bracket '}' will be skipped.
    <br>
    <br>
    <p><b>Function definition block</b><br>
    <p>The basic idea is that a function definition block starts with a word that 
    is not marked as non-function or non-interface related, i.e. the result type name. 
    <p>The header definition ends with the first empty line or the curly bracket '{' at 
    line position 0. The latter will be replaced with a semicolon ';' in the copy for the interface. 
    The function body will be skipped.
    <br>
    <br>
    <p><b>Non-interface related block</b><br>
    <p>Blocks whose first Line start with on of the following words don't belong to the interface
    and will be skipped:
    <p>'static', 'ConcreteType', 'ConcreteImp', 'struct', 'union' und 'typedef', 'inline', 
    'class', 'template'
    <p>Beside that a member function definition block, recognized by the pattern 'name::name'
    will be skipped.
    <br>
    <br>
    <p><b>C source file header block</b><br>
    <p>The first block will allways be copied. Within this block the suffix of the file name
    will be patched from '.c' to '.h'.
    <br>
    <br>
    <p><b>Include block</b><br>
    <p> The first block whose lines starts with an #include-directive will be copied. In order 
    to copy the necessary #include-directives they must be places first in the c source file,
    separated by an empty line from the rest. 
    <br>
    <br>
    <p><b>Comment block</b><br>
    <p>Comment lines starting with '/*I-' or '/*I=' are interface-related and thus copied. The
    Character 'I' will be replaced with a space character. Further comment blocks starting with '/*!' 
    will be copied.
    <br>
    <br>
    <p><b>Explicit interface block ( 1 )</b><br>
    In order to force the copy of certain c source lines to the interface the first line of such 
    a block must only contain the comment '/*INTERFACE*/'. This line will be skipped and not copied.
    <p>'/*DOC_INTERFACE*/' is a second variant which in addition copies the block to the [.htm] 
    documentation file if the option 'DPATH' is given.
    <br>
    <br>
    <p><b>Explicit interface block ( 2 )</b><br>
    In addition to the previous method the following uses an explicit start and end tag to provide 
    more flexibility.
    <br>
    <pre>
                | /*INTERFACE_COPY_ON*/
                | ...
                | /*INTERFACE_COPY_OFF*/
    </pre>
    <br>
    The first and last line won't be copied.
    <p>Alternative '/*DOC_INTERFACE_COPY_ON*/' and '/*DOC_INTERFACE_COPY_OFF*/' can be used for 
    additional documentation purposes.
    <br>
    <br>
    <p><b>Explicit interface-only block</b><br>
    The following mechanismn applies to text which should be placed in the interface but is not 
    visible in the c source file for the c/c++ compiler. This is done via the below mentioned
    conditional preprocessor directive. As a consequence the macro name 'INTERFACE' can't be 
    defined. 
    <br>
    <pre>
                | #ifdef INTERFACE
                | ...
                | #endif
    </pre>
    <br>
    The first and last line won't be copied.
    <br>
    <br>
    <p><b>Documentation block</b><br>
    <p>A documentation block is non-interface related and will be skipped. 
    Therefore the macro name
    can't be defined in another context.
    <br>
    <pre>
                | #ifdef DOCUMENT
                | ...
                | #endif
    </pre>
    <br>
    <br>
    <p><b>Interface layout</b><br>
    <p>Blocks where the first line starts with a letter and ends with ')' 
    and the second line starts with '/*' or '{' will be recognized as function
    definitions and layouted in one line.
    <br>
    <p>The comment line '/*INTERFACE_GROUP*/' produces an empty line.
    <br>
    <br>
    <p><b>Starting point of the Signature</b><br>
    <p>Generall the signature starts after the first include-block or before 
    the first function definition. The comment line '/*INTERFACE_LINKAGE_ON*/
    forces the creation of the opening linkage block.
    <br>
cod

Arguments

Options

  CPATH    : path   = "."   -- [DLL basename~]C source directory ; ... [*.c]
  HPATH    : path   = "."   -- H target directory                      [*.h]
  PRJ      : path   = "."   -- directory for project image file        [ctoh.cth]

  force    : flag   = false -- force the creation of the header files
  ct       : flag   = false -- prefix type identifier string,bool,byte,word with 'c_'
  exp      : flag   = false -- generate ms linker export directives / modul 
  DPATH    : path   = ""    -- document target directory             [*.htm]
  DROOT    : path   = "index.html" -- root document file                    
  api      : string = ""    
    -- DLL basename for ms DLL-based ex/import directives, applied to functions prefixed with '_DLL_EXPORT_'

doc
  <p> The options '-exp' and '-api' are not used in a linux environment.
cod

Environment

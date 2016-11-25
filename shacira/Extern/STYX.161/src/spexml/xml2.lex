; [xml2.lex] Token definitions for [.xml]-Files

#include xml1.lex

; Extensible Markup Language ( base tokens 2 )

tok Nmtoken   = ( NameChar - ( Letter | '_' | ':' ) ) { NameChar }

let EQ        = {Space} '=' {Space} 
tok XMLDecl   = "<?" KXML 
                [ Space+ KVERSION EQ '\'\"' ( HexChar | '.:-_' )+ '\'\"' ]
                [ Space+ KENCODING EQ '\'\"' ( HexChar | '-_' )+ '\'\"' ]
                [ Space+ KSTANDALONE EQ '\'\"' ( KYES | KNO ) '\'\"' ]
                {Space} "?>"
tok PI        = ( "<?" Ide ({Char} - ({Char} "?>" {Char})) "?>" ) - XMLDecl

tok CDSect    = "<![" KCDATA "[" ({Char} - ({Char} "]]>" {Char})) "]]>"

tok ElmStart  = "<" | "</" | "<!"
tok TagEnd    = ">" | "/>"
tok XMLOpr    = '=,*?+|()[]%#' | "<![" | "]]>" | "?>" | ")*" 

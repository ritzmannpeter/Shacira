
   Aenderungen ab 09.07.04

   Widgets:

     1. Widgets Header-Dateien <widget>.h werden durch den Praeprozessor
     pp erzeugt.
     Als Eingabedateien dienen die Praeprozessor-Dateien <widget>.pp.
     Die Eigenschaften aller Widgets werden 

     2. Die Widget-Methoden wurden aufgrund der Qt-Anforderungen an
     das Threading teilweise geaendert und erweitert.    

     3. Alle Widgets wurden um die Funktionsreferenzen GUISlotFuncRef
     und GUISignalFilterFuncRef sowie um die Eigenschaften QualifiedName,
     Listening und ListenTo erweitert.
     Mit diesen Eigenschaften und der entsprechenden Funktionalitaet,
     koennen Widgets untereinander ohne direkte Kopllung kommunizieren.

     4. Die Standardparametersaetze aller User-Funktionen haben sich 
     geaendert sowohl fuer die Modell-basierten User-Funktionen, als
     auch fuer die GUI-basierten User-Funktionen.

     Modell:
       type ConvFunc(context, value, i1, i2, i3, i4, ...)
       type FilterFunc(context, value, i1, i2, i3, i4, ...)
       type Limit(context, i1, i2, i3, i4, ...) (neu fuer Min- und Max-Funktionen s. u., ...)
     GUI:
       ulong DarkFunc(context,widget, ...)
       ulong PlausFunc(context,widget,input, ...)
       ulong UserFunc(context,widget,input, ...)
       ulong ButtonFunc(context,widget, ...)
       ulong GUISignalFilterFunc(context,widget,signal, ...)
       ulong GUISlotFunc(context,widget,signal,widget, ...) das zweite widget ist der Sender
       string LstFltFunc(context,widget,index, ...) (neu fuer ComboBoxen)
     Frei:
       type EmbeddedFunc(context, ...)
       type FreeFunc(...)

     5. Alle Eingabewidgets
       CReqValue
       CCheckBox
       CRadioButton
       CComboBox
       CStateButton
     sind mit Plaus- und Userfunktion ausgestattet

     6. Bei der textuellen Eingabe (CReqValue) werden Validatoren
     verwendet, die sich nach Datentyp, Praezision, Minimum und
     Maximum der zugrundeliegenden Variable-Referenz richten.

     7. Es gibt ein neues numerisches und ein zusaetzliches
     alphanumerisches Keypad (noch nicht aktiviert!).
     Das numerische Keypad verwendet denselben Validator wie das
     Eingabewidget. Es behandelt Eingabefehler Keypad-intern.

   Datenmodell:
     FÅr jede Variable koennen Minimum und Maximum festgelegt werden.
       minimum=spec
       maximum=spec
     Min- und Max-Werte koennen uber drei verschiedene Mechanismen werden:
       1. Konstante:
         minimum=55.3
       2. Variablenreferenz:
         maximum=ToolParamTab[3]
       3. Funktionsreferenz
         minimum=PressureMin()

        deklaration: limit ushort PressureMin()


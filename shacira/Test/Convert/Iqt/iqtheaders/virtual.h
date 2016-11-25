#ifndef __virtual__
#define __virtual__

// Flags zum Einschalten verschiedener Test- und Demo-Optionen. Die Flags werden
// mittels Kommandozeilenparameter eingeschaltet. Standardmäßig sind alle Flags
// ausgeschaltet.

extern GLOBAL int FlagTextWindow;       // 1 = Textwindow benutzen statt VGA
extern GLOBAL int FlagWindowBoarder;    // 1 = IQT-Fenster mit Rahmen
extern GLOBAL int FlagVirtualFMEM;      // 1 = Virtuellen Flatmem-Treiber benutzen
extern GLOBAL int FlagVirtualCAN;       // 1 = Virtuellen Canbus-Treiber benutzen
extern GLOBAL int FlagVirtualPPC;       // 1 = Virtuellen PPCCom-Treiber benutzen
extern GLOBAL int FlagKbdSimulation;    // 1 = Tastatursimulation zulassen
extern GLOBAL int FlagAnalyzeStructure; // 1 = Hosttabelle analysieren
extern GLOBAL int FlagPrintPages;       // 1 = Seitentexte in Dateien ausgeben
extern GLOBAL int FlagNoVersionCheck;   // 1 = Kein Versionscheck beim Aufstarten
extern GLOBAL int FlagDebug;            // 1 = IQT läuft unter Debuggerkontrolle
extern GLOBAL int ReadOnlyFileSystem;   // 1 = Man darf nicht auf Festplatte schreiben

// Variable zur Definition der benutzten Hardwareplattform; solange keine
// praktikable Hardwareerkennung möglich ist, wird dies als Kommandozeilenparameter
// beim Aufstarten des IQT definiert.

#define STANDARD_PC     0
#define PROVIT2000      1
#define PROVIT2001      2
#define PROVIT5000      3

extern GLOBAL int HardwarePlatform;


// Funktion zum Initialisieren obiger Flags und Variablen
GLOBAL void InitIqtArgs(int argc, char ** argv);

#endif /* __virtual__ */

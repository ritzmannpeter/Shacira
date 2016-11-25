/*.SH.*/

/*
 *  Headerfile for module ew_commands
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ew_commands.cpp on Tuesday April 09 2002  22:01:08
 */

#ifndef __ew_commands__
#define __ew_commands__


// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"
#include "base/eb_clip.hpp"
#include "win/ew_base.hpp"


// ===========================================================================
// Definition cwCmd
// ---------------------------------------------------------------------------
//
//    cwCmd
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmd {
   friend class ccwCmd;

public:
   inline cwCmd(const cwCmd& cmd)
      { *this = cmd; }

protected:
   #if defined __ECL_W32__

      inline cwCmd()
         { l1 = l2 = msg = 0; }

      struct SHORTS {
         union { short s1; unsigned short us1; };
         union { short s2; unsigned short us2; };
      };

      unsigned int msg;       // Meldungscode
      union {
         unsigned long  ul1;  //  - ULONG (allgemein)
         long           l1;   //  - LONG (allgemein)
         SHORTS         v1;   //  - 2xSHORT (allgemein)
      };
      union {
         unsigned long  ul2;  //  - ULONG (allgemein)
         long           l2;   //  - LONG (allgemein)
         SHORTS         v2;   //  - 2xSHORT (allgemein)
      };

   #elif defined __ECL_OS2__

      cwCmd()
         { hwnd = msg = ul1 = ul2 = 0; }

      struct SHORTS {
         union { short s1; unsigned short us1; };
         union { short s2; unsigned short us2; };
      };

      unsigned long hwnd;     // Window-Handle
      unsigned long msg;      // Meldungscode
      union {
         unsigned long  ul1;  //  - ULONG (allgemein)
         long           l1;   //  - LONG (allgemein)
         SHORTS         v1;   //  - 2xSHORT (allgemein)
      };
      union {
         unsigned long  ul2;  //  - ULONG (allgemein)
         long           l2;   //  - LONG (allgemein)
         SHORTS         v2;   //  - 2xSHORT (allgemein)
      };

   #endif

};


// ===========================================================================
// Definition cwCmdPosition
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdPosition : public cwCmd {

public:
   cwCmdPosition(const cwCmd& cmd) :
      cwCmd(cmd) { }

   // Position des Events (in Window-Koordinaten)
   cdPoint getPos() const;

   int getPosX() const;
   int getPosY() const;

   // Screen- oder Window-Koordinaten?
   bool isRelativeToScreen() const;
   bool isRelativeToWindow() const;

   // Anforderung via Tastatur oder Maus?
   bool fromMouse() const;
   bool fromKeyboard() const;

};


// ===========================================================================
// Definition cwCmdMouse
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdMouse
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdMouse : public cwCmdPosition {

public:
   cwCmdMouse(const cwCmd& cmd) :
      cwCmdPosition(cmd) { }

   // SHIFT, CTRL oder ALT momentan gedrueckt?
   bool holdsShift() const;
   bool holdsCtrl() const;
   bool holdsAlt() const;

   // Welche Mausknoepfe sind momentan gedrueckt?
   bool holdsLeftButton() const;
   bool holdsRightButton() const;
   bool holdsMiddleButton() const;

   // Event von Mausknopf (0=None, 1=Left, 2=Right, 3=Middle)
   int getButtonNo() const;

   bool wasClickLeftButton() const;
   bool wasClickRightButton() const;
   bool wasClickMiddleButton() const;

   // Art des Mausklicks (0=None, 1=Down, 2=Up, 3=DblClick)
   int getClickStyle() const;

   bool wasClickDown() const;
   bool wasClickUp() const;
   bool wasClickDbl() const;

};


// ===========================================================================
// Definition cwCmdDragDrop
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDragDrop : public cwCmdPosition {

public:
   cwCmdDragDrop(const cwCmd& cmd) :
      cwCmdPosition(cmd) { }

   // SHIFT, CTRL oder ALT momentan gedrueckt?
   bool holdsShift() const;
   bool holdsCtrl() const;
   bool holdsAlt() const;

   // Welche Mausknoepfe sind momentan gedrueckt?
   bool holdsLeftButton() const;
   bool holdsRightButton() const;
   bool holdsMiddleButton() const;

   // Ist ein bestimmtes Format vorhanden?
   bool isAvailable(const cClipboardFormat& format) const;
   // Daten im ECL-Format erfragen
   bool getData(cClipboardData& data) const;
   // Daten in bestimmtem Format 'format' erfragen
   bool getData(cClipboardData& data, const cClipboardFormat& format) const;

protected:
   // Menge der erlaubten Operationen setzen
   void setAllowedOps(int allowed_ops);
   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setSourceOps(int source_ops);
   // Ausgewaehlte Operation setzen
   void setDropOp(int drop_op);

   // Menge der erlaubten Operationen erfragen
   int getAllowedOps() const;
   // Menge der von der DragSource unterstuetzten Operationen erfragen
   int getSourceOps() const;
   // Ausgewaehlte Operation erfragen
   int getDropOp() const;

};


// ===========================================================================
// Definition cwCmdDrag
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//             +--cwCmdDrag
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDrag : public cwCmdDragDrop {

public:
   cwCmdDrag(const cwCmd& cmd) :
      cwCmdDragDrop(cmd) { }

   // Erlaubte Operationen
   enum ALLOWED_OPS {
      allowNone   = 0x00,  // DropTarget erlaubt keine Operation
      allowCopy   = 0x01,  // DropTarget erlaubt "Objekt kopieren"
      allowMove   = 0x02,  // DropTarget erlaubt "Objekt bewegen"
      allowLink   = 0x04   // DropTarget erlaubt "Verknuefpung erstellen"
   };

   // Menge der erlaubten Operationen setzen
   void setAllowedOps(int allowed_ops);
   // Menge der erlaubten Operationen erfragen
   int getAllowedOps() const;

   // Umwandlung vom systemspezifischen Format: Erlaubte Operationen
   static int convSysToAllowedOps(int sys);
   // Umwandlung ins systemspezifische Format: Erlaubte Operationen
   static int convAllowedOpsToSys(int allowed_ops);

};


// ===========================================================================
// Definition cwCmdDrop
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdPosition
//         +--cwCmdDragDrop
//             +--cwCmdDrop
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdDrop : public cwCmdDragDrop {

public:
   cwCmdDrop(const cwCmd& cmd) :
      cwCmdDragDrop(cmd) { }

   // Von der DragSource unterstuetzte Operationen
   enum SOURCE_OPS {
      mayCopy     = 0x01,  // DragSource unterstuetzt "Objekt kopieren"
      mayMove     = 0x02,  // DragSource unterstuetzt "Objekt bewegen"
      mayLink     = 0x04,  // DragSource unterstuetzt "Verknuefpung erstellen"
      mayBeAny    = 0x07   // DragSource unterstuetzt alle Operationen
   };

   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setSourceOps(int source_ops);
   // Menge der erlaubten Operationen erfragen
   int getSourceOps() const;

   // Umwandlung vom systemspezifischen Format: Von DragSource unterstuetzte Operationen
   static int convSysToSourceOps(int sys);
   // Umwandlung ins systemspezifische Format: Von DragSource unterstuetzte Operationen
   static int convSourceOpsToSys(int source_ops);


   // Auszufuehrende Operation
   enum DROP_OP {
      opNone      = 0x00,  // Keine Drop-Operation ausfuehren (Dummy)
      opCopy      = 0x01,  // Drop-Operation "Objekt kopieren"
      opMove      = 0x02,  // Drop-Operation "Objekt bewegen"
      opLink      = 0x04   // Drop-Operation "Verknuefpung erstellen"
   };

   // Menge der von der DragSource unterstuetzten Operationen setzen
   void setDropOp(DROP_OP drop_op);
   // Menge der erlaubten Operationen erfragen
   DROP_OP getDropOp() const;

   // Umwandlung vom systemspezifischen Format: Ausgewaehlte Operation
   static DROP_OP convSysToDropOp(int sys);
   // Umwandlung ins systemspezifischen Format: Ausgewaehlte Operation
   static int convDropOpToSys(DROP_OP drop_op);

};


// ===========================================================================
// Definition cwCmdChar
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdChar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdChar : public cwCmd {

public:
   cwCmdChar(const cwCmd& cmd) :
      cwCmd(cmd) { }

   enum VIRTUALKEYS {
      vkUndef,                // Nicht definiert, normale Taste

      vkF1, vkF2, vkF3,       // Funktionstasten F1..F3
      vkF4, vkF5, vkF6,       // Funktionstasten F4..F6
      vkF7, vkF8, vkF9,       // Funktionstasten F7..F9
      vkF10, vkF11, vkF12,    // Funktionstasten F10..F12

      vkBreak,                // Break
      vkShift,                // Shift (links oder rechts)
      vkControl,              // Strg (links oder rechts)
      vkAlt,                  // Alt (links)
      vkAltGraf,              // AltGr (rechts)
      vkEsc,                  // ESC
      vkBackspace,            // BACKSPACE
      vkReturn,               // RETURN (Alpha-Block)
      vkTab,                  // TAB
      vkBackTab,              // BACKTAB
      vkPause,                // PAUSE
      vkSpace,                // Leertaste

      vkPgUp,                 // Cursor "Bild Auf"
      vkPgDown,               // Cursor "Bild Ab"
      vkEnd,                  // Cursor "Ende"
      vkHome,                 // Cursor "Pos1"
      vkLeft,                 // Cursor "Links"
      vkRight,                // Cursor "Rechts"
      vkUp,                   // Cursor "Auf"
      vkDown,                 // Cursor "Ab"

      vkPrintScrn,            // Druck
      vkInsert,               // Einfg
      vkDelete,               // Entf
      vkScrlLock,             // Rollen
      vkCapsLock,             // Caps

      vkNumLock,              // NumPad "Num" (Num-Lock)
      vkNumDiv,               // NumPad "/" (Divide)
      vkNumMul,               // NumPad "x" (Multiply)
      vkNumSub,               // NumPad "-" (Subtract)
      vkNumAdd,               // NumPad "+" (Add)
      vkNumEnter,             // NumPad "Enter"
      vkNumDec,               // NumPad "," (Decimal-Point)
      vkNum0,                 // NumPad "0"
      vkNum1,                 // NumPad "1"
      vkNum2,                 // NumPad "2"
      vkNum3,                 // NumPad "3"
      vkNum4,                 // NumPad "4"
      vkNum5,                 // NumPad "5"
      vkNum6,                 // NumPad "6"
      vkNum7,                 // NumPad "7"
      vkNum8,                 // NumPad "8"
      vkNum9,                 // NumPad "9"

      // Alte Bezeichner, nicht mehr benutzen:
      //
      vkEnter = vkNumEnter,   // ENTER (Ziffern-Block)
      vkPageUp = vkPgUp,      // Bild Auf
      vkPageDown = vkPgDown,  // Bild Ab
   };

   // Taste gedrueckt?
   bool isKeyDown() const;
   // Taste losgelassen?
   bool isKeyUp() const;

   // Code fuer Sondertaste verfuegbar?
   bool isVirt() const;
   // Code fuer normale Taste verfuegbar?
   bool isChar() const;

   // Abfrage der Codes fuer Sondertaste
   VIRTUALKEYS getVirt() const;
   // Abfrage der Codes fuer normale Taste
   int getChar() const;

   // Meldung nicht weiterleiten
   void killMsg();

   // Tastencode modifizieren (nur bei normaler Taste)
   void setChar(int ch_code);
   // Tastencode aus Puffer entfernen (nur bei normaler Taste)
   void killChar();

   // SHIFT gedrueckt?
   bool holdsShift() const;
   // CTRL gedrueckt?
   bool holdsCtrl() const;
   // ALT gedrueckt?
   bool holdsAlt() const;

};


// ===========================================================================
// Definition cwCmdCmds
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdCmds : public cwCmd {

public:
   // Konstruktor
   cwCmdCmds(const cwCmd& cmd) :
      cwCmd(cmd) { }

   enum CMDSRC {
      csSystem,               // Systemereignis
      csProgram,              // Programmiertes Ereignis
      csControl,              // Quelle: Dialog-Control
      csMenu,                 // Quelle: Menueauswahl
      csAccel                 // Quelle: Accelerator
   };

   enum STDCMDS {
      cmdStandardFirst = -1000,

      cmdSysClose,
      cmdSysHotkey,
      cmdSysHScroll,
      cmdSysKeyMenu,
      cmdSysMaximize,
      cmdSysMinimize,
      cmdSysMouseMenu,
      cmdSysMove,
      cmdSysNextWindow,
      cmdSysPrevWindow,
      cmdSysRestore,
      cmdSysScreenSave,
      cmdSysSize,
      cmdSysTaskList,
      cmdSysVScroll,

      cmdFileNew,                         // Datei->Neu...
      cmdFileOpen,                        // Datei->�ffnen...
      cmdFileClose,                       // Datei->Schliessen
      cmdFileSave,                        // Datei->Speichern
      cmdFileSaveAs,                      // Datei->Speichern unter...
      cmdFilePageSetup,                   // Datei->Seite einrichten...
      cmdFilePrintSetup,                  // Datei->Druckereinrichtung...
      cmdFilePrint,                       // Datei->Drucken...
      cmdFilePrintDirect,                 // ?
      cmdFilePrintPreview,                // Datei->Druckvorschau...
      cmdFileUpdate,                      // ?
      cmdFileSaveCopyAs,                  // Datei->Speichern als Kopie...
      cmdFileSendMail,                    // Datei->Senden...

      cmdFileMruFirst,                    // (erster Eintrag der Liste)
      cmdFileMru01 = cmdFileMruFirst,     // (Datei 01 oeffnen)
      cmdFileMru02,                       // (Datei 02 oeffnen)
      cmdFileMru03,                       // (Datei 03 oeffnen)
      cmdFileMru04,                       // (Datei 04 oeffnen)
      cmdFileMru05,                       // (Datei 05 oeffnen)
      cmdFileMru06,                       // (Datei 06 oeffnen)
      cmdFileMru07,                       // (Datei 07 oeffnen)
      cmdFileMru08,                       // (Datei 08 oeffnen)
      cmdFileMru09,                       // (Datei 09 oeffnen)
      cmdFileMru10,                       // (Datei 10 oeffnen)
      cmdFileMru11,                       // (Datei 11 oeffnen)
      cmdFileMru12,                       // (Datei 12 oeffnen)
      cmdFileMru13,                       // (Datei 13 oeffnen)
      cmdFileMru14,                       // (Datei 14 oeffnen)
      cmdFileMru15,                       // (Datei 15 oeffnen)
      cmdFileMru16,                       // (Datei 16 oeffnen)
      cmdFileMruLast = cmdFileMru16,      // (letzter Eintrag der Liste)

      cmdEditClear,
      cmdEditClearAll,
      cmdEditCopy,
      cmdEditCut,
      cmdEditFind,
      cmdEditPaste,
      cmdEditPasteLink,
      cmdEditPasteSpecial,
      cmdEditRepeat,
      cmdEditReplace,
      cmdEditSelectAll,
      cmdEditUndo,
      cmdEditRedo,

      cmdWindowNew,
      cmdWindowArrange,
      cmdWindowCascade,
      cmdWindowTileHorz,
      cmdWindowTileVert,
      cmdWindowSplit,

      cmdWindowFirst,
      cmdWindow01 = cmdWindowFirst,
      cmdWindow02,
      cmdWindow03,
      cmdWindow04,
      cmdWindow05,
      cmdWindow06,
      cmdWindow07,
      cmdWindow08,
      cmdWindow09,
      cmdWindow10,
      cmdWindow11,
      cmdWindow12,
      cmdWindow13,
      cmdWindow14,
      cmdWindow15,
      cmdWindow16,
      cmdWindowLast = cmdWindow16,

      cmdAppAbout,
      cmdAppExit,

      cmdHelpIndex,
      cmdHelpFinder,
      cmdHelpUsing,
      cmdHelpContext,
      cmdHelp,
      cmdDefaultHelp,

      cmdPaneNext,
      cmdPanePrev,

      cmdFormatFont,

      cmdPreviewClose,
      cmdPreviewNumpage,
      cmdPreviewNext,
      cmdPreviewPrev,
      cmdPreviewPrint,
      cmdPreviewZoomin,
      cmdPreviewZoomout,

      cmdViewToolbar,
      cmdViewStatusbar,
      cmdViewRebar,
      cmdViewAutoarrange,
      cmdViewSmallIcon,
      cmdViewLargeIcon,
      cmdViewList,
      cmdViewDetails,
      cmdViewLineup,
      cmdViewByname,

      cmdRecordFirst,
      cmdRecordLast,
      cmdRecordNext,
      cmdRecordPrev,

      cmdStandardLast
   };


   // Ermitteln der System-ID zu einer ECL-Ereignis-ID
   static int convID(STDCMDS ecl_id);
   // Ermitteln der ECL-Ereignis-ID zu einer System-ID
   static int convID(int sys_id, bool from_sysmenu);

protected:
   cwCmdCmds()
      { }

};


// ===========================================================================
// Definition cwCmdEvt
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//         +--cwCmdEvt
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdEvt : public cwCmdCmds {

public:
   // Konstruktor
   cwCmdEvt(const cwCmd& cmd) :
      cwCmdCmds(cmd) { }
   // Konstruktor ueber ID
   cwCmdEvt(int id);
   // Konstruktor ueber ECL-Ereignis-ID
   cwCmdEvt(STDCMDS id);

   // Ereignis ausgeloest ueber Tastatur?
   bool fromKeyboard() const;
   // Ereignis ausgeloest ueber Maus?
   bool fromMouse() const;
   // Ermitteln der Quelle des Ereignisses
   CMDSRC getSource() const;
   // Ermitteln der ID des Ereignisses
   int getId() const;

};


// ===========================================================================
// Definition cwCmdUI
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdCmds
//         +--cwCmdUI
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdUI : public cwCmdCmds {

public:
   cwCmdUI(const cwCmd& cmd) :
      cwCmdCmds(cmd) { }

   // ID des betroffenen Menu-Items, Toolbar-Buttons, o.a. erfragen
   int getId() const;
   // Index des betroffenen Menu-Items, Toolbar-Buttons, o.a. erfragen
   int getIndex() const;

   // Enable-Flag manipulieren (true = freigeben; false = sperren)
   void setEnable(bool enable = true);
   // Enable-Status manipulieren (0 = chkUnchecked, 1 = chkChecked, 2 = chkIndeter)
   void setCheck(int check);
   // Text setzen
   void setText(const cString& text);

};


// ===========================================================================
// Definition cwCmdScroll
// ---------------------------------------------------------------------------
//
//    cwCmd
//     +--cwCmdScroll
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCmdScroll : public cwCmd {

public:

   enum BAR {
      barHorz  = 0x0001,   // Kennzeichnet den horizontalen Standard-Scrollbalken
      barVert  = 0x0002    // Kennzeichnet den vertikalen Standard-Scrollbalken
   };

   enum ACTION {
      scrlLeft,            // An den linken Rand scrollen
      scrlLeftLine,        // Um eine "Zeile" nach links scrollen
      scrlLeftPage,        // Um eine "Seite" nach links scrollen
      scrlRight,           // An der rechten Rand scrollen
      scrlRightLine,       // Um eine "Zeile" nach rechts scrollen
      scrlRightPage,       // Um eine "Seite" nach rechts scrollen
      // ---
      scrlTop,             // An den oberen Rand scrollen
      scrlUpLine,          // Um eine "Zeile" nach oben scrollen
      scrlupPage,          // Um eine "Seite" nach oben scrollen
      scrlBottom,          // An den unteren Rand scrollen
      scrlDownLine,        // Um eine "Zeile" nach unten scrollen
      scrlDownPage,        // Um eine "Seite" nach unten scrollen
      // ---
      scrlEnd,             // MouseUp nach wiederholter Scrollbewegung
      // ---
      scrlBoxTracking,     // Scrollbox wird bewegt (Position vgl. getScrollTrackPos)
      scrlBoxReleased,     // Scrollbox wieder losgelassen (Position vgl. getScrollTrackPos)
   };

   // Konstruktor ueber cwCmd-Objekt
   cwCmdScroll(const cwCmd& cmd) :
      cwCmd(cmd) { }
   // Konstruktor ueber spezifische Parameter
   cwCmdScroll(BAR bar, ACTION action);

   // Scroll-Aktion von horizontalem Standard-Scrollbar?
   bool fromHorzScrollBar() const;
   // Scroll-Aktion von vertikalem Standard-Scrollbar?
   bool fromVertScrollBar() const;

   // Scroll-Aktion ermitteln
   ACTION getAction() const;

};


#endif

/*.EH.*/

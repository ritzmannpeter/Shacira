// ===========================================================================
// eb_elo.cpp                                                   ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//     |
//     +--cEloBase
//     |   |
//     |   +--cEloElement
//     |   |
//     |   +--cEloOperation
//     |   |
//     |   +--cEloAction
//     |   |   |
//     |   |   +--cEloActionStatic
//     |   |   |
//     |   |   +--cEloActionDynamic
//     |   |
//     |   +--cEloDescription
//     |   |   |
//     |   |   +--cEloElementDescription
//     |   |   |
//     |   |   +--cEloActionDescription
//     |   |
//     |   +--cEloManager
//     |       |
//     |       +--cEloOperationManager
//     |       |
//     |       +--cEloActionManager
//     |       |
//     |       +--cEloDescriptionManager
//     |
//     +--cEloSelection
//
// ===========================================================================

#include "base/eb_elo.hpp"

#include "base/eb_array.hpp"
#include "base/eb_list.hpp"
#include "base/eb_map.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_object.hpp"
#include "base/eb_str.hpp"


// Forward-Deklarationen
// ===========================================================================

class cEloElementDescription;
class cEloActionDescription;
class cEloSelection;
class cEloOperation;
class cEloOperationManager;
class cEloDescriptionManager;


// Runtime-Type-Information (light)
// ===========================================================================

// Veraltete Namen (aus Kompatibilitaetsgruenden):
#define ELO_DECLARE(CLASS,BASECLASS) ECL_DECLARE(CLASS,BASECLASS)
#define ELO_CAST(CLASS,PTREXPR)      ECL_CAST(CLASS,PTREXPR)
#define ELO_ISKINDOF(CLASS)          ECL_ISKINDOF(CLASS)

#endif /*__INTERFACE__*/




// Lokale Deklarationen
// ===========================================================================

// ELO_INIT_WHEN - Mit diesem Makro wird die Initialisierung eines Manager-
// oder Beschreibungsobjektes "bei Bedarf" angestossen, selbst wenn der Bedarf
// in einer 'const'-Funktion entsteht. Der verwendete Mechanismus zur
// Initialisierung laeuft ueber die onInitialize-Memberfunktion.
#define ELO_INIT_WHEN(CLASS,COND) \
   if ( COND ) ((CLASS*)this)->onInitialize();

// ELO_INIT_OP_WHEN - Spezialform fuer cEloOperation: Setzt zusaetzlich noch
// das 'was_initialized'-Flag auf 'true'.
#define ELO_INIT_OP_WHEN(CLASS,COND) \
if ( COND ) { \
      ((CLASS*)this)->onInitialize(); \
      ((CLASS*)this)->was_initialized = true; \
   }




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloBase
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Elemente, Operationen und Aktionen sowie fuer
// Beschreibungsobjekte.
//
// Mit getSignature() kann die eindeutige Signatur des ELO-Objektes
// (technisch ein einfacher cString) ermittelt werden. Die Signatur kann
// fuer verschiedene Zwecke eingesetzt werden, zum Beispiel:
//
//  - Bestimmen des Typs eines Elementes, einer Operation oder Aktion
//    UNABHAENGIG von der zur Implementierung verwendeten Klasse
//
//  - Indizieren in ein Online-Hilfesystem
//
// Weitere definierte Eigenschaften sind: (Nicht alle der folgenden Eigen-
// schaften sind bei jedem Objekttyp sinnvoll!)
//
//  - getType(): Ermittelt den primaeren Typ des ELO-Objektes (die in diesem
//    Modul definierten Klassen).
//
//  - getKey(): Ermittelt den eindeutigen (textuellen) Schluesselwert des
//    ELO-Objektes. Dieser kann zum Wiederauffinden des Objektes benutzt
//    werden. Der Schluesselwert kann auch aus mehreren Teilschluesseln
//    zusammengesetzt sein; die einzelnen Teilschluessel sind dann durch
//    Komma voneinander abgetrennt.
//
//  - getName(): Ermittelt einen als Objektnamen benutzbaren, kurzen Text.
//    Bei einem Mitarbeiter-Datensatz koennte das Objektname z.B. aus der
//    Kombination Vorname + Nachname bestehen.
//
//  - getDescr(): Ermittelt einen als Objektbeschreibung benutzbaren,
//    moeglicherweise laengeren Text. Bei einem Mitarbeiter-Datensatz koennte
//    die Objektbeschreibung z.B. aus der Kombination Vorname + Nachname +
//    Wohnort + Strasse + Telefon bestehen.
//
//  - getBitmapId(): Ermittelt die ID oder den Index eines Sinnbildes (Icon
//    oder Bitmap), das den Datensatz beschreibt.
//
// cEclObject
//  +--cEloBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloBase : public cEclObject {
   ECL_DECLARE(cEloBase,cEclObject)

public:

   // Virtueller Destruktor (Wichtig bei Mehrfachvererbung!)
   virtual ~cEloBase();


   // ELO-Signatur
   // ============

   // Eindeutige Signatur des ELO-Objektes erfragen
   cString getSignature() const;


   // ELO-Objekttypen
   // ===============

   enum ELO_TYPE {
      etElement,              // Selektierbares Element
      etOperation,            // Operation
      etAction,               // Aktionsobjekt
      etElementDescription,   // Beschreibung von Elementen
      etActionDescription,    // Beschreibung von Aktionen
      etOperationManager,     // Manager von Operationen
      etActionManager,        // Manager von Aktionen
      etDescriptionManager    // Manager von Beschreibungen
   };

   // Typ des ELO-Objektes erfragen
   ELO_TYPE getType() const;

   // Ist das ELO-Objekt ein selektierbares Element?
   inline bool isElement() const
      { return getType() == etElement; }
   // Ist das ELO-Objekt eine Operation?
   inline bool isOperation() const
      { return getType() == etOperation; }
   // Ist das ELO-Objekt eine Aktion?
   inline bool isAction() const
      { return getType() == etAction; }
   // Ist das ELO-Objekt eine Elementbeschreibung?
   inline bool isElementDescription() const
      { return getType() == etElementDescription; }
   // Ist das ELO-Objekt eine Aktionsbeschreibung?
   inline bool isActionDescription() const
      { return getType() == etActionDescription; }
   // Ist das ELO-Objekt ein Manager von Operationen?
   inline bool isOperationManager() const
      { return getType() == etOperationManager; }
   // Ist das ELO-Objekt ein Manager von Aktionen?
   inline bool isActionManager() const
      { return getType() == etActionManager; }
   // Ist das ELO-Objekt ein Manager von Beschreibungen?
   inline bool isDescriptionManager() const
      { return getType() == etDescriptionManager; }


   // Allgemeine Eigenschaften
   // ========================

   enum BITMAP_STYLE {
      bsDefault,              // Default-Bitmap
      bsActive,               // Bitmap fuer "Objekt aktiv"
      bsLink                  // Bitmap fuer "Objekt ist Link"
   };

   // Eindeutigen (textuellen) Schluessel des ELO-Objektes erfragen
   cString getKey() const;
   // Teilschluessel erfragen (als String)
   cString getKeyPart(int part) const;
   // Teilschluessel erfragen (als int)
   int getKeyPartInt(int part) const;

   // Name des ELO-Objektes erfragen
   cString getName() const;
   // Textuelle Beschreibung des ELO-Objektes erfragen
   cString getDescr() const;
   // ID oder Index des assoziierten Symbols erfragen (-1 = kein Symbol)
   int getBitmapId(BITMAP_STYLE bs = bsDefault) const;


protected:

   // Events
   // ======

   // Wird aufgerufen, um das ELO-Objekt zu initialisieren
   virtual void onInitialize() = 0;

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   virtual cString onGetSignature() const = 0;
   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   virtual ELO_TYPE onGetType() const = 0;

   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   virtual cString onGetKey() const = 0;
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   virtual cString onGetName() const = 0;
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   virtual cString onGetDescr() const = 0;
   // Wird aufgerufen, um die ID oder den Index des assoziierten Symbols zu erfragen
   virtual int onGetBitmapId(BITMAP_STYLE bs) const;

};

#endif /*__INTERFACE__*/


// Implementierung cEloBase
// ===========================================================================

cEloBase::~cEloBase()
{
}


// ELO-Signatur
// ============

cString cEloBase::getSignature() const
{
   return onGetSignature();
}


// ELO-Objekttypen
// ===============

cEloBase::ELO_TYPE cEloBase::getType() const
{
   return onGetType();
}


// Allgemeine Eigenschaften
// ========================

cString cEloBase::getKey() const
{
   return onGetKey();
}

cString cEloBase::getKeyPart(int part) const
{
   // Bei zusammengesetzten Schluesseln sind die Komponenten durch
   // Komma getrennt im Schluessel gespeichert, z.B. "42,BLA,99".
   // Ist die Komponente nicht vorhanden, wird ein Leerstring geliefert.

   return getKey().getPart(part);
}

int cEloBase::getKeyPartInt(int part) const
{
   // Wie getKeyPart(), wandelt das Ergebnis jedoch in 'int'.
   // Ist die Komponente nicht vorhanden, wird der Wert 0 geliefert.

   return getKeyPart(part).getLong();
}

cString cEloBase::getName() const
{
   return onGetName();
}

cString cEloBase::getDescr() const
{
   return onGetDescr();
}

int cEloBase::getBitmapId(BITMAP_STYLE bs) const
{
   return onGetBitmapId(bs);
}


// Events
// ======

int cEloBase::onGetBitmapId(BITMAP_STYLE /*bs*/) const
{
   // Eine Bitmap-ID ist nicht zwingend noetig
   return -1;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloElement
// ---------------------------------------------------------------------------
//
// Basisklasse fuer selektierbare Elemente. Elemente sind in der Regel fuer
// den Anwender einer Anwendung identifizierbare Objekte, d.h. er kann sie
// zum Beispiel mit der Maus anklicken. Jedem solchen Element kann eine Menge
// von Operationen zugeordnet werden, die ueber eine Aktion (des Anwenders)
// ausgeloest werden.
//
// cEclObject
//  +--cEloBase
//      +--cEloElement
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloElement : public cEloBase {
   ECL_DECLARE(cEloElement,cEloBase)

public:

   // Konstruktor ueber Elementbeschreibung (direkt)
   cEloElement(const cEloElementDescription *elem_descr = 0);
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cEloElement(const cEloDescriptionManager *descr_manager, cString descr_sig);


   // Operationen
   // ===========

   // Unterstuetzt das Element die Operation mit Signatur 'sig_op'?
   bool supportsOperation(cString op_sig, cEloElement *target = 0) const;
   // Zeiger auf Operation mit Signatur 'sig_op' ermitteln
   cEloOperation *getOperation(cString op_sig) const;


   // Elementbeschreibung
   // ===================

   // Aktuelle Elementbeschreibung erfragen
   const cEloElementDescription *getElemDescr() const;


protected:

   // Elementbeschreibung
   // ===================

   // Nachtraegliches Setzen oder Ueberschreiben der Elementbeschreibung (direkt)
   void setElemDescr(const cEloElementDescription *elem_descr);
   // Nachtraegliches Setzen oder Ueberschreiben der Elementbeschreibung (indirekt)
   void setElemDescr(const cEloDescriptionManager *descr_manager, cString descr_sig);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um das ELO-Objekt zu initialisieren
   void onInitialize();

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const;
   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const;

   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const;
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const;
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const;


private:

   // Assoziierte Elementbeschreibung
   const cEloElementDescription *elem_descr;

};

#endif /*__INTERFACE__*/


// Implementierung cEloElement
// ===========================================================================

cEloElement::cEloElement(const cEloElementDescription *elem_descr)
{
   setElemDescr(elem_descr);
}

cEloElement::cEloElement(const cEloDescriptionManager *descr_manager, cString descr_sig)
{
   setElemDescr(descr_manager, descr_sig);
}


// Operationen
// ===========

bool cEloElement::supportsOperation(cString op_sig, cEloElement *target) const
{
   ELO_INIT_WHEN(cEloElement, elem_descr == 0);

   if ( target != 0 ) {
      cEloOperation *op = elem_descr->getOperation(op_sig);
      return op ? op->supportsTarget(this, target) : false;
   }

   return elem_descr->supportsOperation(op_sig);
}

cEloOperation * cEloElement::getOperation(cString op_sig) const
{
   ELO_INIT_WHEN(cEloElement, elem_descr == 0);
   return elem_descr->getOperation(op_sig);
}


// Elementbeschreibung
// ===================

void cEloElement::setElemDescr(const cEloElementDescription *elem_descr)
{
   static class cEloDummyElementDescription : public cEloElementDescription {
      ECL_DECLARE(cEloDummyElementDescription,cEloElementDescription)
   protected:
      void onInitialize() { }
      cString onGetSignature() const { return "cEloDummyElementDescription"; }
   } dummy_description;

   cEloElement::elem_descr = elem_descr == 0 ?
      &dummy_description
    : elem_descr;
}

void cEloElement::setElemDescr(const cEloDescriptionManager *descr_manager, cString descr_sig)
{
   if ( __ECL_ASSERT1__(descr_manager != 0) ) {
      const cEloDescription *descr = descr_manager->getDescription(descr_sig);
      if ( __ECL_ASSERT1__(descr != 0 && descr->isElementDescription() ) ) {
         elem_descr = (const cEloElementDescription*)descr;
      } else {
         elem_descr = 0;
      }
   }
}

const cEloElementDescription * cEloElement::getElemDescr() const
{
   return elem_descr;
}


// Ueberschriebene Events
// ======================

void cEloElement::onInitialize()
{
   // Default-Implementierung leer. ELO-Elemente brauchen aus historischen
   // Gruenden nicht zwingend ein onInitialize-Member.
}

cString cEloElement::onGetSignature() const
{
   return __getClassName();
}

cEloBase::ELO_TYPE cEloElement::onGetType() const
{
   return etElement;
}

cString cEloElement::onGetKey() const
{
   return cString();
}

cString cEloElement::onGetName() const
{
   return getKey();
}

cString cEloElement::onGetDescr() const
{
   return getName();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloAction
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Aktionsobjekte. Aktionen kapseln alle Arten von Eingaben
// durch den Benutzer: Menues und Toolbars sowie Tastatur- und Mauseingaben.
// Jede moegliche Aktion wird mit einem cEloActionDescription-Objekt be-
// schrieben, welches auch die Verbindung zu den Operationen herstellt.
//
// Wenn der Benutzer eine Aktion initiiert (z.B. durch Aufklappen eines Menus
// oder Anzeigen eines Toolbars), werden die fuer die aktuelle Selektion
// gueltigen Operationen anhand deren Signaturen ermittelt und dem Benutzer
// zur Auswahl angeboten.
//
// cEclObject
//  +--cEloBase
//      +--cEloAction
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloAction : public cEloBase {
   ECL_DECLARE(cEloAction,cEloBase)

public:

   // Konstruktor ueber Aktionsbeschreibung (direkt)
   cEloAction(const cEloActionDescription *action_descr);
   // Konstruktor ueber Aktionsbeschreibung (indirekt ueber Signatur)
   cEloAction(const cEloDescriptionManager *descr_manager, cString descr_sig);

   // Ist das Objekt mit ID 'id' ein cEloOperation-Objekt?
   bool isOperation(int id) const;
   // Ist die Operation mit ID 'id' enabled?
   bool isOperationEnabled(int id, cEloSelection *selection = 0, int sub_op = -1) const;
   // Assoziierte Operation mit ID 'id' ermitteln (0 bei Fehler)
   cEloOperation *getOperation(int id) const;

   // Zugeordnete Aktionsbeschreibung ermitteln
   inline const cEloActionDescription *getActionDescription() const
      { return action_descr; }

   // Anzeigen der Aenderung der Selektion
   void reflectSelectionChange(cEloSelection *selection);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, wenn sich die aktuelle Selektion geaendert hat
   virtual void onSelectionChanged(cEloSelection *selection) = 0;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etAction; }
   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const
      { return cString(); }
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const
      { return cString(); }
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const
      { return cString(); }
   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return __getClassName(); }


private:

   // Assoziierte Aktionsbeschreibung
   const cEloActionDescription *action_descr;

};

#endif /*__INTERFACE__*/


// Implementierung cEloAction
// ===========================================================================

cEloAction::cEloAction(const cEloActionDescription *action_descr)
{
   __ECL_ASSERT1__(action_descr != 0);
   cEloAction::action_descr = action_descr;
}

cEloAction::cEloAction(const cEloDescriptionManager *descr_manager, cString descr_sig)
{
   if ( __ECL_ASSERT1__(descr_manager != 0) ) {
      const cEloDescription *descr = descr_manager->getDescription(descr_sig);
      if ( __ECL_ASSERT1__(descr != 0 && descr->getType() == etActionDescription ) ) {
         action_descr = (const cEloActionDescription*)descr;
      } else {
         action_descr = 0;
      }
   }
}

bool cEloAction::isOperation(int id) const
{
   return __ECL_ASSERT1__(action_descr != 0) ?
      action_descr->isOperation(id, true)
    : false;
}

bool cEloAction::isOperationEnabled(int id, cEloSelection *selection, int sub_op) const
{
   cEloOperation *op = getOperation(id);
   return op != 0 ?
      selection->supportsOperation(op->getSignature()) && op->isEnabled(selection, sub_op)
    : false;
}

cEloOperation * cEloAction::getOperation(int id) const
{
   return __ECL_ASSERT1__(action_descr != 0) ?
      action_descr->getOperation(id, true)
    : 0;
}

void cEloAction::reflectSelectionChange(cEloSelection *selection)
{
   if ( __ECL_ASSERT1__(selection != 0) )
      onSelectionChanged(selection);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloActionStatic
// ---------------------------------------------------------------------------
//
// Statische Aktionen sind in der Regel sichtbaren Bildschirmelementen
// zugeordnet (z.B. Frame-Menues oder Toolbars), die - ganz oder teilweise -
// fuer eine laengere Zeit sichtbar sind. Statische Aktionen werden normaler-
// weise von cEloActionManager-Objekten erzeugt und verwaltet.
//
// cEclObject
//  +--cEloBase
//      +--cEloAction
//          +--cEloActionStatic
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloActionStatic : public cEloAction {
   ECL_DECLARE(cEloActionStatic,cEloAction)

public:

   // Konstruktor ueber Aktionsbeschreibung (direkt)
   cEloActionStatic(const cEloActionDescription *action_descr);
   // Konstruktor ueber Aktionsbeschreibung (indirekt ueber Signatur)
   cEloActionStatic(const cEloDescriptionManager *descr_manager, cString descr_sig);

};

#endif /*__INTERFACE__*/


// Implementierung cEloActionStatic
// ===========================================================================

cEloActionStatic::cEloActionStatic(const cEloActionDescription *action_descr) :
   cEloAction(action_descr)
{
}

cEloActionStatic::cEloActionStatic(const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cEloAction(descr_manager, descr_sig)
{
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloActionDynamic
// ---------------------------------------------------------------------------
//
// Dynamische Aktionen sind entweder keinen sichtbaren Bildschirmelementen
// zugeordnet oder diese sind nur fuer die Dauer einer Benutzerinteraktion
// sichtbar (z.B. Kontextmenues). Das dynamische Aktionsobjekt wird erzeugt,
// mit dem Bildschirmelement verknuepft und geloescht, wenn die Operation
// ausgewaehlt wurde.
//
// cEclObject
//  +--cEloBase
//      +--cEloAction
//          +--cEloActionDynamic
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloActionDynamic : public cEloAction {
   ECL_DECLARE(cEloActionDynamic,cEloAction)

public:

   // Konstruktor ueber Aktionsbeschreibung (direkt)
   cEloActionDynamic(const cEloActionDescription *action_descr);
   // Konstruktor ueber Aktionsbeschreibung (indirekt ueber Signatur)
   cEloActionDynamic(const cEloDescriptionManager *descr_manager, cString descr_sig);

};

#endif /*__INTERFACE__*/


// Implementierung cEloActionDynamic
// ===========================================================================

cEloActionDynamic::cEloActionDynamic(const cEloActionDescription *action_descr) :
   cEloAction(action_descr)
{
}

cEloActionDynamic::cEloActionDynamic(const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cEloAction(descr_manager, descr_sig)
{
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloOperation
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Operationen, die auf Elementen arbeiten. Wenn ein Element
// selektiert wird, werden die diesem Element zugeordneten Operationen
// aktiviert (d.h. sichtbar oder aktiv in einem Menu oder einem Toolbar).
// Werden mehrere Elemente selektiert, wird die Menge der aktiven Operationen
// auf die von allen selektierten Elementen unterstuetzte Operationsmenge
// beschraenkt.
//
// Operationen werden von Operationsmanagern (cEloOperationManager) erzeugt
// und verwaltet, die als zentrale Instanzen innerhalb eines logischen
// (Sub-)systems fuer eine zusammengehoerende Menge von Operationen
// zustaendig sind.
//
// Eine Operation besteht aus n Teil-Operationen, die dynamisch erzeugt
// werden koennen (typischerweise ist n = 1). Beispiele:
//
//    n = 1                        | n >= 0
//   ------------------------------+------------------------------
//    File->Open                   | File->(RecentFileList)
//    Edit->Copy                   | Create->(CurrentTypeList)
//    Window->Cascade              | Window->(CurrentWindowList)
//
// Bei allen Funktionen, die ein 'sub_operation'-Parameter erhalten, gilt:
//
//  - Wenn sub_operation < 0, ist der Haupteintrag gemeint
//  - Wenn sub_operation >= 0, ist der spezifizierte Untereintrag gemeint
//
// Flags zur Steuerung der Operation:
//
//  - isStatic()
//    Ist dieses Flag gesetzt, wird die Operation unabhaengig von der
//    aktuellen Auswahl angeboten. Statische Operation werden ueber eine
//    spezielle exec-Methode ausgefuehrt.
//
//  - isVisible()
//    Dieses Flag steuert die Sichtbarkeit der Operation: Unsichtbare Opera-
//    tionen werden in keinem Menu oder Toolbar angezeigt, koennen aber
//    dennoch (intern) verwendet werden. Sichtbare Operationen werden auf die
//    folgende Art angezeigt:
//
//     * Frame Menus: Die Operation wird stets angezeigt. Kann sie aufgrund
//       der aktuellen Selektionsmenge nicht ausgefuehrt werden, wird sie
//       "grau" dargestellt.
//
//     * Context Menus: Die Operation wird nur angezeigt, wenn sie aufgrund
//       der aktuellen Selektionsmenge auch ausgefuehrt werden kann.
//
//  - isEnabled()
//    Ueber dieses Flag kann festgelegt werden, ob die Operation aktuell zu-
//    gaengig (enabled) ist oder nicht (disabled). Nicht zugaengige Opera-
//    tionen werden (abhaengig von isVisible) zwar angezeigt, koennen aber
//    nicht ausgewaehlt werden (sind in Menues z.B. "ausgegraut").
//
//  - isChecked()
//    Ueber das isChecked()-Flag kann festgelegt werden, ob die Operation
//    aktuell ein Checkmark anzeigt oder nicht. In Menues wird der "Checked"-
//    Zustand z.B. ueber einen speziellen "Haken" angezeigt.
//
//  - isCheckable()
//    Ob eine Operation prinzipiell "Checkable" ist, wird ueber dieses Flag
//    gesteuert. Sollte es geliefert werden, ist das Flag unabhaengig von der
//    aktuellen Selektion fuer die Operation gueltig.
//
// Zum Ausfuehren von der Operation wird die virtuelle Methode onExecOperation
// aufgerufen. Die ableitende Klasse muss die Operation fuer alle Elemente der
// Selektion ausfuehren. Alternativ kann onExecOperation auch fuer einzelne
// Elemente benutzt werden (zweite Variante).
//
// cEclObject
//  +--cEloBase
//      +--cEloElement
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloOperation : public cEloBase {
   ECL_DECLARE(cEloOperation,cEloBase)

public:

   // Konstruktor
   cEloOperation();


   // Allgemeines
   // ===========

   // Erlaubt die Operation Teil-Operationen? (Default: false)
   bool hasSubOperations(const cEloSelection *selection = 0) const;
   // Aktuelle Anzahl Teil-Operationen erfragen (Default: 1)
   int getSubOperationCount(const cEloSelection *selection = 0) const;
   // Unterstuetzt die Operation ein spezifisches 'target' auf 'selected_elem'?
   bool supportsTarget(const cEloElement *selected_elem, cEloElement *target) const;

   // Statische Operation ausfuehren
   void execOperation(cEloElement *target = 0);
   // (Teil-)Operation auf eine Elementmenge anwenden
   void execOperation(cEloSelection *selection, int sub_operation = -1, cEloElement *target = 0);


   // Attribute
   // =========

   // Default Objekt-ID der Operation ermitteln
   int getDefaultObjectId() const;
   // Text fuer Menueeintraege (Shortcut-Praefix "&")
   cString getMenuText(const cEloSelection *selection = 0, int sub_operation = -1) const;
   // Hilfetext fuer Statuszeile oder Bubble-Help
   cString getHelpText(const cEloSelection *selection = 0, int sub_operation = -1) const;
   // Index in Online-Hilfesystem (-1 = Keine Hilfe)
   int getHelpId(const cEloSelection *selection = 0, int sub_operation = -1) const;


   // Steuerflags
   // ===========

   // Ist die Operation statisch?
   bool isStatic() const;
   // Wird die (Teil-)Operation angezeigt?
   bool isVisible(const cEloSelection *sel = 0, int sub_op = -1, cEloElement *target = 0) const;
   // Ist die (Teil-)Operation "enabled" (zugaengig fuer Benutzer)?
   bool isEnabled(const cEloSelection *sel = 0, int sub_op = -1, cEloElement *target = 0) const;
   // Ist die (Teil-)Operation "checked" (speziell markiert)?
   bool isChecked(const cEloSelection *sel = 0, int sub_op = -1, cEloElement *target = 0) const;
   // Erlaubt die (Teil-)Operation spezielle Markierungen?
   bool isCheckable(const cEloSelection *sel = 0, int sub_op = -1, cEloElement *target = 0) const;


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um eine statische Operation auszufuehren
   virtual void onExecOperation(cEloElement *target);
   // Wird aufgerufen, um die Operation auf alle Elemente der Selektion auszufuehren
   virtual void onExecOperation(cEloSelection *selection, int sub_operation, cEloElement *target);
   // Wird aufgerufen, um die Operation auf ein einzelnes Element auszufuehren
   virtual void onExecOperation(cEloElement *elem, int sub_operation, cEloElement *target);

   // Wird aufgerufen, um zu bestimmen, ob die Operationen Teil-Operationen erlaubt
   virtual bool onGetSubOperations(const cEloSelection *selection) const;
   // Wird aufgerufen, um die aktuelle Anzahl Teil-Operationen zu erfragen
   virtual int onGetSubOperationCount(const cEloSelection *selection) const;
   // Wird aufgerufen, um zu pruefen, ob die Operation ein spezifisches Target Unterstuetzt
   virtual bool onSupportsTarget(const cEloElement *selected_elem, cEloElement *target) const;

   // Wird aufgerufen, um die default Objekt-ID der Operation ermitteln
   virtual int onGetDefaultObjectId() const;
   // Wird aufgerufen, um den Text fuer Menueeintraege zu erfragen
   virtual cString onGetMenuText(const cEloSelection *selection, int sub_operation) const = 0;
   // Wird aufgerufen, um den Hilfetext fuer die Statuszeile zu erfragen
   virtual cString onGetHelpText(const cEloSelection *selection, int sub_operation) const = 0;
   // Wird aufgerufen, um den Index in das Online-Hilfesystem zu erfragen
   virtual int onGetHelpId(const cEloSelection *selection, int sub_operation) const;

   // Wird aufgerufen, um zu pruefen, ob die Operation statisch ist
   virtual bool onGetStaticFlag() const;
   // Wird aufgerufen, um zu pruefen, ob die (Teil-)Operation angezeigt wird
   virtual bool onGetVisibleFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const;
   // Wird aufgerufen, um zu pruefen, ob die (Teil-)Operation "enabled" (zugaengig fuer Benutzer) ist
   virtual bool onGetEnabledFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const;
   // Wird aufgerufen, um zu pruefen, ob die (Teil-)Operation "checked" (speziell markiert) ist
   virtual bool onGetCheckedFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const;
   // Wird aufgerufen, um zu pruefen ob die (Teil-)Operation spezielle Markierungen erlaubt
   virtual bool onGetCheckableFlag(const cEloSelection *sel, int sub_op, cEloElement *target) const;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um das ELO-Objekt zu initialisieren
   void onInitialize();

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const;
   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const;
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const;
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const;


protected:

   // Operation bereits initialisiert?
   bool was_initialized;


public:

   // ALTER BEZEICHNER! NICHT MEHR VERWENDEN! (Flags der Operation erfragen)
   int getFlags(const cEloSelection *selection = 0, int sub_operation = 0) const;

protected:

   enum FLAGS {                     // ALTE BEZEICHNER! NICHT MEHR VERWENDEN!
      ofStatic       = 0x00000001,  // Operation statisch (stets verfuegbar)?
      ofVisible      = 0x00000002,  // Operation angezeigt (sichtbar im Menue)?
      ofEnabled      = 0x00000004,  // Operation "enabled" (zugaengig fuer Benutzer)?
      ofChecked      = 0x00000008,  // Operation "checked" (speziell markiert)?
      ofCheckable    = 0x00000100,  // Spezielle Markierung ("Checkmark") moeglich?
      ofUser         = 0x00010000
   };

   // ALTER BEZEICHNER! NICHT MEHR VERWENDEN! Wird aufgerufen, um die Flags der Operation zu erfragen
   virtual int onGetFlags(const cEloSelection *selection, int sub_operation) const;

};

#endif /*__INTERFACE__*/


// Implementierung cEloOperation
// ===========================================================================

cEloOperation::cEloOperation()
{
   was_initialized = false;
}


// Allgemeines
// ===========

bool cEloOperation::hasSubOperations(const cEloSelection *selection) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetSubOperations(selection);
}

int cEloOperation::getSubOperationCount(const cEloSelection *selection) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetSubOperationCount(selection);
}

bool cEloOperation::supportsTarget(const cEloElement *selected_elem, cEloElement *target) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onSupportsTarget(selected_elem, target);
}

void cEloOperation::execOperation(cEloElement *target)
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);

   // Ausfuehren einer statischen Operation
   // -------------------------------------
   // 'target' ist das (optionale) Zielelement der Operation. Dieses kann bei
   // gerichteten Aktivierungsarten (wie Drag-and-Drop) eine wesentliche
   // Rolle fuer die Semantik der Operation spielen.

   onExecOperation(target);
}

void cEloOperation::execOperation(cEloSelection *selection, int sub_operation, cEloElement *target)
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);

   // Ausfuehren einer Operation auf einer Elementmenge (Selektion)
   // -------------------------------------------------------------
   // 'target' ist das (optionale) Zielelement der Operation. Dieses kann bei
   // gerichteten Aktivierungsarten (wie Drag-and-Drop) eine wesentliche
   // Rolle fuer die Semantik der Operation spielen.

   if ( __ECL_ASSERT1__(selection != 0) ) {
      if ( selection->getElementCount() > 0 )
         onExecOperation(selection, sub_operation, target);
   }
}


// Attribute
// =========

int cEloOperation::getDefaultObjectId() const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetDefaultObjectId();
}

cString cEloOperation::getMenuText(const cEloSelection *selection, int sub_operation) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetMenuText(selection, sub_operation);
}

cString cEloOperation::getHelpText(const cEloSelection *selection, int sub_operation) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetHelpText(selection, sub_operation);
}

int cEloOperation::getHelpId(const cEloSelection *selection, int sub_operation) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetHelpId(selection, sub_operation);
}


// Steuerflags
// ===========

int cEloOperation::getFlags(const cEloSelection *selection, int sub_operation) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetFlags(selection, sub_operation);
}

bool cEloOperation::isStatic() const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetStaticFlag();
}

bool cEloOperation::isVisible(const cEloSelection *sel, int sub_op, cEloElement *target) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetVisibleFlag(sel, sub_op, target);
}

bool cEloOperation::isEnabled(const cEloSelection *sel, int sub_op, cEloElement *target) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetEnabledFlag(sel, sub_op, target);
}

bool cEloOperation::isChecked(const cEloSelection *sel, int sub_op, cEloElement *target) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetCheckedFlag(sel, sub_op, target);
}

bool cEloOperation::isCheckable(const cEloSelection *sel, int sub_op, cEloElement *target) const
{
   ELO_INIT_OP_WHEN(cEloOperation, !was_initialized);
   return onGetCheckableFlag(sel, sub_op, target);
}


// Hinzugefuegte Events
// ====================

void cEloOperation::onExecOperation(cEloElement * /*target*/)
{
   // Wird zum Ausfuehren einer statischen Operation aufgerufen
}

void cEloOperation::onExecOperation(cEloSelection *selection, int sub_operation, cEloElement *target)
{
   // Variante 1: Default-Implementierung ruft Variante 2 fuer
   // alle Elemente der Selektion auf.

   cEloSelection temp_selection = *selection;

   for ( int i = 0 ; i < temp_selection.getElementCount() ; i++ )
      onExecOperation(temp_selection.getElement(i), sub_operation, target);
}

void cEloOperation::onExecOperation(cEloElement * /*elem*/, int /*sub_operation*/, cEloElement * /*target*/)
{
   // Variante 2: Default-Implementierung wirft Assertion, d.h. es
   // muss entweder Variante 1 ODER Variante 2 implementiert werden.

   __ECL_ASSERT2__(0, ("Operation '%s' (class %s) not implemented",
      (const char *)getSignature(),
      (const char *)getClassName()));
}

bool cEloOperation::onGetSubOperations(const cEloSelection * /*selection*/) const
{
   return false;
}

int cEloOperation::onGetSubOperationCount(const cEloSelection *selection) const
{
   // Normalerweise sind Sub-Operationen nur bei Selektion von
   // exakt einem Element moeglich.

   return hasSubOperations() && selection->getElementCount() == 1 ? 1 : 0;
}

bool cEloOperation::onSupportsTarget(const cEloElement *, cEloElement *) const
{
   // Hier kann geprueft werden, ob die Operation in einem bestimmten
   // Kontext laeuft. Dabei gibt der erste Parameter das Element an, auf
   // das die Operation angewendet werden soll. Der zweite Parameter gibt
   // einen Hinweis auf das Ziel der Operation.

   // Normalerweise ist der Wert fuer 'target' ohne Bedeutung, daher:

   return true;
}

int cEloOperation::onGetDefaultObjectId() const
{
   // Defaultwert ist -1, was als "Kein Objekt-ID" interpretiert
   // wird

   return -1;
}

int cEloOperation::onGetHelpId(const cEloSelection * /*selection*/, int /*sub_operation*/) const
{
   return -1;
}

int cEloOperation::onGetFlags(const cEloSelection * /*selection*/, int /*sub_operation*/) const
{
   return ofVisible | ofEnabled;
}

bool cEloOperation::onGetStaticFlag() const
{
   // Basisklasse ruft aus Kompatibilitatesgruenden getFlags() auf!
   return !!(getFlags() & ofStatic);
}

bool cEloOperation::onGetVisibleFlag(const cEloSelection *sel, int sub_op, cEloElement *) const
{
   // Basisklasse ruft aus Kompatibilitatesgruenden getFlags() auf!
   return !!(getFlags(sel, sub_op) & ofVisible);
}

bool cEloOperation::onGetEnabledFlag(const cEloSelection *sel, int sub_op, cEloElement *) const
{
   // Basisklasse ruft aus Kompatibilitatesgruenden getFlags() auf!
   return !!(getFlags(sel, sub_op) & ofEnabled);
}

bool cEloOperation::onGetCheckedFlag(const cEloSelection *sel, int sub_op, cEloElement *) const
{
   // Basisklasse ruft aus Kompatibilitatesgruenden getFlags() auf!
   return !!(getFlags(sel, sub_op) & ofChecked);
}

bool cEloOperation::onGetCheckableFlag(const cEloSelection *sel, int sub_op, cEloElement *) const
{
   // Basisklasse ruft aus Kompatibilitatesgruenden getFlags() auf!
   return !!(getFlags(sel, sub_op) & ofCheckable);
}


// Ueberschriebene Events
// ======================

void cEloOperation::onInitialize()
{
   // Default-Implementierung. ELO-Operationen brauchen aus historischen
   // Gruenden nicht zwingend ein onInitialize-Member.
}

cEloBase::ELO_TYPE cEloOperation::onGetType() const
{
   return etOperation;
}

cString cEloOperation::onGetKey() const
{
   return getSignature();
}

cString cEloOperation::onGetName() const
{
   return getMenuText();
}

cString cEloOperation::onGetDescr() const
{
   return getHelpText();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloDescription
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Beschreibungsobjekte von Elementen und Aktionen.
//
// cEclObject
//  +--cEloBase
//      +--cEloDescription
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloDescription : public cEloBase {
   ECL_DECLARE(cEloDescription,cEloBase)

public:

   // Konstruktor
   cEloDescription();
   // Destruktor
   ~cEloDescription();


protected:

   // Assoziierte Beschreibungen
   // ==========================

   // Anzahl assoziierter Beschreibungen ermitteln
   int getDescriptionCount() const;
   // Assoziierte Beschreibung mit Index 'index' ermitteln
   cEloDescription *getDescription(int index) const;
   // Assoziierte Beschreibung hinzufuegen
   void addDescription(cEloDescription *descr);
   // Assoziierte Beschreibung entfernen
   void removeDescription(cEloDescription *descr);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const
      { return getSignature(); }
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const
      { return getKey(); }
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const
      { return getName(); }
   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return __getClassName(); }


private:

   // Zeiger auf die geordnete Liste assoziierter Beschreibungen (oder 0)
   struct ASSOCIATED_DESCRIPTIONS;
   ASSOCIATED_DESCRIPTIONS *descriptions;

};

#endif /*__INTERFACE__*/


// Implementierung cEloDescription
// ===========================================================================

struct cEloDescription::ASSOCIATED_DESCRIPTIONS {
   cList<cEloDescription*,cEloDescription*> list;
};

cEloDescription::cEloDescription()
{
   descriptions = 0;
}

cEloDescription::~cEloDescription()
{
   delete descriptions;
}


// Assoziierte Beschreibungen
// ==========================

int cEloDescription::getDescriptionCount() const
{
   // hier nicht: ELO_INIT_WHEN(cEloDescription, descriptions==0);

   return descriptions != 0 ?
      descriptions->list.getCount()
    : 0;
}

cEloDescription * cEloDescription::getDescription(int index) const
{
   // hier nicht: ELO_INIT_WHEN(cEloDescription, descriptions==0);

   if ( __ECL_ASSERT1__(descriptions != 0) ) {
      IPOSITION descr_pos = descriptions->list.findIndex(index);
      if ( __ECL_ASSERT1__(descr_pos != 0) )
         return descriptions->list.getAt(descr_pos);
   }

   return 0;
}

void cEloDescription::addDescription(cEloDescription *descr)
{
   if ( __ECL_ASSERT1__(descr != 0) ) {
      if ( descriptions == 0 )
         descriptions = new0 ASSOCIATED_DESCRIPTIONS;
      descriptions->list.addTail(descr);
   }
}

void cEloDescription::removeDescription(cEloDescription *descr)
{
   if ( __ECL_ASSERT1__(descr != 0 && descriptions != 0) ) {
      IPOSITION descr_pos = descriptions->list.find(descr);
      if ( __ECL_ASSERT1__(descr_pos != 0) )
         descriptions->list.removeAt(descr_pos);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloElementDescription
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Beschreibungsobjekte von Elementen, Operationen und
// Aktionen.
//
// cEclObject
//  +--cEloBase
//      +--cEloDescription
//          +--cEloElementDescription
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloElementDescription : public cEloDescription {
   ECL_DECLARE(cEloElementDescription,cEloDescription)

public:

   // Konstruktor
   cEloElementDescription();
   // Destruktor
   ~cEloElementDescription();


   // Registrierte Operationen
   // ========================

   // Unterstuetzt das Element die Operation mit Signatur 'sig_op'?
   bool supportsOperation(cString op_sig) const;
   // Zeiger auf Operation mit Signatur 'sig_op' ermitteln
   cEloOperation *getOperation(cString op_sig) const;


protected:

   // Deklaration der Verwandschaft: this erbt alles von 'elem_descr'
   void inheritFrom(cEloElementDescription *elem_descr);
   // Registrieren einer Operation
   void registerOperation(cEloOperation *op);
   // Registrieren einer Operation ueber Operation-Manager
   void registerOperation(cEloOperationManager *op_manager, cString op_sig);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etElementDescription; }


private:

   // Zeiger auf die assoziative Liste registrierter Operationen (oder 0)
   struct REGISTERED_OPERATIONS;
   REGISTERED_OPERATIONS *operations;

};

#endif /*__INTERFACE__*/


// Implementierung cEloElementDescription
// ===========================================================================

struct cEloElementDescription::REGISTERED_OPERATIONS {
   cMap<cString,cString,cEloOperation*,cEloOperation*> map;
};

cEloElementDescription::cEloElementDescription()
{
   operations = 0;
}

cEloElementDescription::~cEloElementDescription()
{
   delete operations;
}


// Verwandschaften
// ===============

void cEloElementDescription::inheritFrom(cEloElementDescription *elem_descr)
{
   addDescription(elem_descr);
}


// Registrierte Operationen
// ========================

void cEloElementDescription::registerOperation(cEloOperation *op)
{
   if ( __ECL_ASSERT1__(op != 0) ) {
      if ( operations == 0 )
         operations = new0 REGISTERED_OPERATIONS;
      cEloOperation *existing_op;
      if ( operations->map.lookup(op->getSignature(), existing_op) ) {
         __ECL_ASSERT1__(op == existing_op);
      } else {
         operations->map[op->getSignature()] = op;
      }
   }
}

void cEloElementDescription::registerOperation(cEloOperationManager *op_manager, cString op_sig)
{
   if ( __ECL_ASSERT1__(op_manager != 0) ) {
      if ( operations == 0 )
         operations = new0 REGISTERED_OPERATIONS;
      cEloOperation *op = op_manager->getOperation(op_sig);
      if ( __ECL_ASSERT1__(op != 0) ) {
         cEloOperation *existing_op;
         if ( operations->map.lookup(op_sig, existing_op) ) {
            __ECL_ASSERT1__(op == existing_op);
         } else {
            operations->map[op_sig] = op;
         }
      }
   }
}

bool cEloElementDescription::supportsOperation(cString op_sig) const
{
   return getOperation(op_sig) != 0;
}

cEloOperation * cEloElementDescription::getOperation(cString op_sig) const
{
   ELO_INIT_WHEN(cEloElementDescription, operations==0);

   cEloOperation *op_found;

   if ( operations != 0 ) {
      if ( operations->map.lookup(op_sig, op_found) )
         return op_found;
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      if ( (op_found = ((cEloElementDescription*)getDescription(i))->getOperation(op_sig)) != 0 )
         return op_found;
   }

   return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloActionDescription
// ---------------------------------------------------------------------------
//
// ...
//
// Jedem zur Aktionsbeschreibung assozierten Objekt kann eine benutzer-
// spezifische Kennung gegeben werden, z.B. die Resource-ID im Menusystem.
//
// cEclObject
//  +--cEloBase
//      +--cEloDescription
//          +--cEloActionDescription
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloActionDescription : public cEloDescription {
   ECL_DECLARE(cEloActionDescription,cEloDescription)

public:

   // Konstruktor
   cEloActionDescription();
   // Destruktor
   ~cEloActionDescription();


   // Assoziierte Objekte
   // ===================

   // Anzahl assoziierter Objekte ermitteln
   int getObjectCount() const;
   // User-ID des Objektes an Position 'index' ermitteln
   int getObjectID(int index) const;

   // Ist das Objekt an Position (oder mit ID) 'index_or_id' ein cEloOperation-Objekt?
   bool isOperation(int index_or_id, bool by_id = false) const;
   // Ist das Objekt an Position (oder mit ID) 'index_or_id' ein cEloActionDescription-Objekt?
   bool isSubDescription(int index_or_id, bool by_id = false) const;
   // Soll das Objekt an Position (oder mit ID) 'index_or_id' als Defaultobjekt markiert werden?
   bool isDefault(int index_or_id, bool by_id = false) const;
   // Soll dem Objekt an Position (oder mit ID) 'index_or_id' eine Trennlinie vorangestellt werden?
   bool hasBreakBefore(int index_or_id, bool by_id = false) const;
   // Soll dem Objekt an Position (oder mit ID) 'index_or_id' eine Trennlinie folgen?
   bool hasBreakAfter(int index_or_id, bool by_id = false) const;

   // Assoziierte Operation mit Index (oder ID) 'index_or_id' ermitteln
   // (Liefert 0, falls bei 'index' kein cEloOperation-Objekt!)
   cEloOperation *getOperation(int index_or_id, bool by_id = false) const;
   // Sub-ID der Operation mit Index (oder ID) 'index_or_id' ermitteln
   // (Liefert -1, falls bei 'index' kein cEloOperation-Objekt!)
   int getOperationSubId(int index_or_id, bool by_id = false) const;
   // Untergeordnete Beschreibung mit Index (oder ID) 'index_or_id' ermitteln
   // (Liefert 0, falls bei 'index' kein cEloActionDescription-Objekte!)
   cEloActionDescription *getSubDescription(int index_or_id, bool by_id = false) const;


protected:

   // Stile assoziierter Objekte
   // ==========================

   enum OBJECT_STYLES {
      osBreakBefore     = 1 << 0,      // Trennlinie VOR dem Objekt (wenn moeglich)
      osBreakAfter      = 1 << 1,      // Trennlinie NACH dem Objekt (wenn moeglich)
      osDefault         = 1 << 2       // Der Wert wird als Defaultwert gekennzeichnet
   };


   // Assoziierte Objekte
   // ===================

   // Deklaration der Verwandschaft: this erbt alles von 'action_descr'
   void inheritFrom(cEloActionDescription *action_descr);
   // Assoziiertes Objekt hinzufuegen, Einfuegen vor 'insert_before'
   void addObject(cEloBase *obj, int obj_id = -1, int obj_id_count = 1, cEloBase *insert_before = 0, int obj_style = 0);
   // Assoziiertes Objekt von 'index' einfuegen
   void addObjectBefore(cEloBase *obj, int obj_id = -1, int obj_id_count = 1, int index = 0, int obj_style = 0);
   // Assoziiertes Objekt entfernen
   void removeObject(cEloBase *obj);
   // Assoziiertes Objekt ueber dessen User-ID entfernen
   void removeObject(int obj_id);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etActionDescription; }


private:

   // Zeiger auf die geordnete Liste assoziierter Operationen (oder 0)
   struct ASSOCIATED_OBJECTS;
   ASSOCIATED_OBJECTS *objects;

   // Intern: Objekt suchen (auch durch alle 'ererbten' Beschreibungen)
   cEloBase *findObject(int index_or_id, bool by_id) const;
   // Intern: Objekt ueber ID suchen (auch durch alle 'ererbten' Beschreibungen)
   cEloBase *findObjectById(int id) const;
   // Intern: Objekt ueber Index suchen (auch durch alle 'ererbten' Beschreibungen)
   cEloBase *findObjectByIndex(int index) const;

   // Intern: Objektstil suchen (auch durch alle 'ererbten' Beschreibungen)
   int findObjectStyle(int index_or_id, bool by_id) const;
   // Intern: Objektstil ueber ID suchen (auch durch alle 'ererbten' Beschreibungen)
   int findObjectStyleById(int id) const;
   // Intern: Objektstil ueber Index suchen (auch durch alle 'ererbten' Beschreibungen)
   int findObjectStyleByIndex(int index) const;

};

#endif /*__INTERFACE__*/


// Implementierung cEloActionDescription
// ===========================================================================

struct OBJECT_INFO {
   OBJECT_INFO();
   OBJECT_INFO(cEloBase *obj, int id, int id_count, int style);
   cEloBase *obj_ptr;
   int obj_id, obj_id_count;
   int obj_style;
};

struct cEloActionDescription::ASSOCIATED_OBJECTS {
   cList<OBJECT_INFO,const OBJECT_INFO&> list;
   IPOSITION findObject(cEloBase *obj, IPOSITION pos = 0);
   IPOSITION findObjectId(int id, IPOSITION pos = 0);
};

cEloActionDescription::cEloActionDescription()
{
   objects = 0;
}

cEloActionDescription::~cEloActionDescription()
{
   delete objects;
}

OBJECT_INFO::OBJECT_INFO()
{
   obj_ptr = 0; obj_id = obj_id_count = obj_style = 0;
}

OBJECT_INFO::OBJECT_INFO(cEloBase *obj, int id, int id_count, int style)
{
   obj_ptr = obj; obj_id = id; obj_id_count = id_count; obj_style = style;
}

IPOSITION cEloActionDescription::ASSOCIATED_OBJECTS::findObject(cEloBase *obj, IPOSITION pos)
{
   if ( pos == 0 ) {
      pos = list.getHeadPosition();
   } else {
      list.getNext(pos);
   }

   while ( pos != 0 ) {
      IPOSITION cur_pos = pos;
      if ( list.getNext(pos).obj_ptr == obj )
         return cur_pos;
   }

   return 0;
}

IPOSITION cEloActionDescription::ASSOCIATED_OBJECTS::findObjectId(int id, IPOSITION pos)
{
   if ( pos == 0 ) {
      pos = list.getHeadPosition();
   } else {
      list.getNext(pos);
   }

   while ( pos != 0 ) {
      IPOSITION cur_pos = pos;
      OBJECT_INFO& oi = list.getNext(pos);
      if ( id >= oi.obj_id && id < oi.obj_id + oi.obj_id_count )
         return cur_pos;
   }

   return 0;
}

cEloBase * cEloActionDescription::findObject(int index_or_id, bool by_id) const
{
   return by_id ?
      findObjectById(index_or_id)
    : findObjectByIndex(index_or_id);
}

cEloBase * cEloActionDescription::findObjectById(int id) const
{
   if ( objects != 0 ) {
      IPOSITION obj_pos = objects->findObjectId(id);
      if ( obj_pos != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_ptr;
      }
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      cEloActionDescription *ad = ECL_CAST(cEloActionDescription, getDescription(i));
      if ( __ECL_ASSERT1__(ad != 0) ) {
         cEloBase *obj_found = ad->findObjectById(id);
         if ( obj_found != 0 )
            return obj_found;
      }
   }

   return 0;
}

cEloBase * cEloActionDescription::findObjectByIndex(int index) const
{
   int offset = 0;

   if ( objects != 0 ) {
      IPOSITION obj_pos = objects->list.findIndex(index);
      if ( obj_pos != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_ptr;
      } else {
         offset = objects->list.getCount();
      }
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      cEloActionDescription *ad = ECL_CAST(cEloActionDescription, getDescription(i));
      if ( __ECL_ASSERT1__(ad != 0) ) {
         cEloBase *obj_found = ad->findObjectByIndex(index - offset);
         if ( obj_found != 0 )
            return obj_found;
         offset += ad->getObjectCount();
      }
   }

   return 0;
}

int cEloActionDescription::findObjectStyle(int index_or_id, bool by_id) const
{
   return by_id ?
      findObjectStyleById(index_or_id)
    : findObjectStyleByIndex(index_or_id);
}

int cEloActionDescription::findObjectStyleById(int id) const
{
   if ( objects != 0 ) {
      IPOSITION obj_pos = objects->findObjectId(id);
      if ( obj_pos != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_style;
      }
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      cEloActionDescription *ad = ECL_CAST(cEloActionDescription, getDescription(i));
      if ( __ECL_ASSERT1__(ad != 0) ) {
         if ( ad->findObjectById(id) != 0 )
            return ad->findObjectStyleById(id);
      }
   }

   return 0;
}

int cEloActionDescription::findObjectStyleByIndex(int index) const
{
   int offset = 0;

   if ( objects != 0 ) {
      IPOSITION obj_pos = objects->list.findIndex(index);
      if ( obj_pos != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_style;
      } else {
         offset = objects->list.getCount();
      }
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      cEloActionDescription *ad = ECL_CAST(cEloActionDescription, getDescription(i));
      if ( __ECL_ASSERT1__(ad != 0) ) {
         if ( ad->findObjectByIndex(index - offset) != 0 )
            return ad->findObjectStyleByIndex(index - offset);
         offset += ad->getObjectCount();
      }
   }

   return 0;
}


// Assoziierte Operationen
// =======================

int cEloActionDescription::getObjectCount() const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   int object_count = 0;

   if ( objects != 0 )
      object_count = objects->list.getCount();

   for ( int i = 0 ; i < getDescriptionCount() ; i++ )
      object_count += ((cEloActionDescription*)getDescription(i))->getObjectCount();

   return object_count;
}

int cEloActionDescription::getObjectID(int index) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   int offset = 0;

   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = objects->list.findIndex(index);
      if ( __ECL_ASSERT1__(obj_pos != 0) ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_id;
      }
      offset = objects->list.getCount();
   }

   for ( int i = 0 ; i < getDescriptionCount() ; i++ ) {
      cEloActionDescription *ad = ((cEloActionDescription*)getDescription(i));
      if ( __ECL_ASSERT1__(ad != 0) ) {
         int id_found = ad->getObjectID(index - offset);
         if ( id_found >= 0 )
            return id_found;
         offset += ad->getObjectCount();
      }
   }

   return -1;
}

bool cEloActionDescription::isOperation(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   cEloBase *obj_ptr = findObject(index_or_id, by_id);
   return obj_ptr != 0 ?
      obj_ptr->isOperation()
    : false;

/* OLD:
   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = by_id ?
         objects->findObjectId(index_or_id)
       : objects->list.findIndex(index_or_id);
      if ( __ECL_ASSERT1__(obj_pos != 0) ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_ptr->isOperation();
      }
   }

   return false;
*/
}

bool cEloActionDescription::isSubDescription(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   cEloBase *obj_ptr = findObject(index_or_id, by_id);
   return obj_ptr != 0 ?
      obj_ptr->isActionDescription()
    : false;

/* OLD:
   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = by_id ?
         objects->findObjectId(index_or_id)
       : objects->list.findIndex(index_or_id);
      if ( __ECL_ASSERT1__(obj_pos != 0) ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return oi.obj_ptr->isActionDescription();
      }
   }

   return false;
*/
}

bool cEloActionDescription::isDefault(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);
   return !!(findObjectStyle(index_or_id, by_id) & osDefault);
}

bool cEloActionDescription::hasBreakBefore(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);
   return !!(findObjectStyle(index_or_id, by_id) & osBreakBefore);
}

bool cEloActionDescription::hasBreakAfter(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);
   return !!(findObjectStyle(index_or_id, by_id) & osBreakAfter);
}

cEloOperation * cEloActionDescription::getOperation(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   cEloBase *obj_ptr = findObject(index_or_id, by_id);
   return obj_ptr != 0 ?
      ECL_CAST(cEloOperation, obj_ptr)
    : 0;

/* OLD:
   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = by_id ?
         objects->findObjectId(index_or_id)
       : objects->list.findIndex(index_or_id);
      if ( obj_pos != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return ECL_CAST(cEloOperation, oi.obj_ptr);
      } else {
         // Operation nicht gefunden (kein Fehler!)
         return 0;
      }
   }

   return 0;
*/
}

int cEloActionDescription::getOperationSubId(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   // Ermittelt die SUB_ID der Operation an 'index_or_id' durch Bestimmen der
   // Differenz zwischen der ID der durch 'index_or_id' gegebenen Operation 'op'
   // und der kleinsten ID mit der gleichen Operation 'op'.

   cEloOperation *op = getOperation(index_or_id, by_id);

   if ( op != 0 && objects != 0 ) {

      IPOSITION pos = 0;
      int min_id = 65536;

      while ( (pos = objects->findObject(op, pos)) != 0 ) {
         OBJECT_INFO &oi = objects->list.getAt(pos);
         min_id = min(oi.obj_id, min_id);
      }

      if ( by_id ) {
         return index_or_id - min_id - 1;
      } else {
         pos = objects->list.findIndex(index_or_id);
         if ( pos != 0 ) {
            OBJECT_INFO &oi = objects->list.getAt(pos);
            return oi.obj_id - min_id - 1;
         }
      }
   }

   return -1;
}

cEloActionDescription * cEloActionDescription::getSubDescription(int index_or_id, bool by_id) const
{
   ELO_INIT_WHEN(cEloActionDescription, objects==0);

   cEloBase *obj_ptr = findObject(index_or_id, by_id);
   return obj_ptr != 0 ?
      ECL_CAST(cEloActionDescription, obj_ptr)
    : 0;

/* OLD:
   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = by_id ?
         objects->findObjectId(index_or_id)
       : objects->list.findIndex(index_or_id);
      if ( __ECL_ASSERT1__(obj_pos != 0) ) {
         OBJECT_INFO &oi = objects->list.getAt(obj_pos);
         return ECL_CAST(cEloActionDescription, oi.obj_ptr);
      }
   }

   return 0;
*/
}

void cEloActionDescription::inheritFrom(cEloActionDescription *action_descr)
{
   addDescription(action_descr);
}

void cEloActionDescription::addObject(cEloBase *obj, int obj_id, int obj_id_count, cEloBase *insert_before, int obj_style)
{
   if ( __ECL_ASSERT1__(obj != 0 && (obj->isOperation() || obj->isActionDescription())) ) {
      if ( obj_id == -1 && obj->isOperation() )
         obj_id = ELO_CAST(cEloOperation,obj)->getDefaultObjectId();
      __ECL_ASSERT1__(obj_id != -1);
      if ( objects == 0 )
         objects = new0 ASSOCIATED_OBJECTS;
      IPOSITION insert_pos = insert_before != 0 ? objects->findObject(insert_before) : 0;
      if ( insert_pos == 0 ) {
         objects->list.addTail(OBJECT_INFO(obj,obj_id,obj_id_count,obj_style));
      } else {
         objects->list.insertBefore(insert_pos, OBJECT_INFO(obj,obj_id,obj_id_count,obj_style));
      }
   }
}

void cEloActionDescription::addObjectBefore(cEloBase *obj, int obj_id, int obj_id_count, int index, int obj_style)
{
   if ( __ECL_ASSERT1__(obj != 0 && (obj->isOperation() || obj->isActionDescription())) ) {
      if ( obj_id == -1 && obj->isOperation() )
         obj_id = ELO_CAST(cEloOperation,obj)->getDefaultObjectId();
      __ECL_ASSERT1__(obj_id != -1);
      if ( objects == 0 )
         objects = new0 ASSOCIATED_OBJECTS;
      IPOSITION insert_pos = objects->list.findIndex(index);
      if ( insert_pos == 0 ) {
         objects->list.addTail(OBJECT_INFO(obj,obj_id,obj_id_count,obj_style));
      } else {
         objects->list.insertBefore(insert_pos, OBJECT_INFO(obj,obj_id,obj_id_count,obj_style));
      }
   }
}

void cEloActionDescription::removeObject(cEloBase *obj)
{
   if ( __ECL_ASSERT1__(obj != 0 && objects != 0) ) {
      IPOSITION obj_pos = objects->findObject(obj);
      if ( __ECL_ASSERT1__(obj_pos != 0) )
         objects->list.removeAt(obj_pos);
   }
}

void cEloActionDescription::removeObject(int obj_id)
{
   if ( __ECL_ASSERT1__(objects != 0) ) {
      IPOSITION obj_pos = objects->findObjectId(obj_id);
      if ( __ECL_ASSERT1__(obj_pos != 0) )
         objects->list.removeAt(obj_pos);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloManager
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Manager-Objekte, die einen logisch zusammengehoerenden
// Satz von identischen ELO-Objekten Operationen verwalten. Eine Manager-
// Instanz erzeugt waehrend onInitialize(), eine Menge von ELO-Objekten
// (via new) und fuegt sie mit addObject() zum Manager hinzu. Die Basisklasse
// sorgt spaeter fuer die korrekte Freigabe der ELO-Objekte.
//
// || ACHTUNG! OBACHT!
// ||
// || ECL/win benutzt einen anderen Heap als ECL/base. Deshalb duerfen
// || Operationen, die aus ECL/win stammen, NICHT (N-I-C-H-T) auf dem
// || Heap angelegt werden, sofern die Gefahr besteht, dass sie von der
// || ELO-Manager-Klasse via 'delete' wieder freigegeben werden. Statt dessen
// || muss aus ECL/win das 'destroy_objects'-Flag UNBEDINGT auf false gesetzt
// || werden! (Fuer eine ECL-Anwendung besteht diese Einschraenkung nicht!)
//
// cEclObject
//  +--cEloBase
//      +--cEloManager
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloManager : public cEloBase {
   ECL_DECLARE(cEloManager,cEloBase)

public:

   // Loescht der Manager seine verwalteten Objekte mit 'delete'?
   inline bool isDestroyingObjects() const
      { return destroy_objects; }


protected:

   // Konstruktor
   cEloManager(bool destroy_objects);
   // Destruktor
   ~cEloManager();

   // Objekt ueber Signatur ermitteln
   cEloBase *getObject(cString sig) const;
   // Objekt hinzufuegen
   void addObject(cEloBase *obj);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const
      { return getSignature(); }
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const
      { return cString(); }
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const
      { return cString(); }
   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return __getClassName(); }

   // Zeiger auf Liste verwalteter Objekte (oder 0)
   struct MANAGED_OBJECTS;
   MANAGED_OBJECTS *objects;


private:

   // Verwaltete Objekte automatisch loeschen?
   bool destroy_objects;

};

#endif /*__INTERFACE__*/


// Implementierung cEloManager
// ===========================================================================

struct cEloManager::MANAGED_OBJECTS {
   MANAGED_OBJECTS(bool destroy_objects);
   ~MANAGED_OBJECTS();
   cMap<cString,cString,cEloBase*,cEloBase*> map;
   bool destroy_objects;
};

cEloManager::cEloManager(bool destroy_objects)
{
   cEloManager::destroy_objects = destroy_objects;
   objects = 0;
}

cEloManager::~cEloManager()
{
   delete objects;
}

cEloManager::MANAGED_OBJECTS::MANAGED_OBJECTS(bool destroy_objects)
{
   MANAGED_OBJECTS::destroy_objects = destroy_objects;
}

cEloManager::MANAGED_OBJECTS::~MANAGED_OBJECTS()
{
   if ( destroy_objects ) {
      for ( IPOSITION pos = map.getStartPosition() ; pos != 0 ; ) {
         cString sig; cEloBase *obj;
         map.getNextAssoc(pos, sig, obj);
         delete obj;
      }
   }
}

void cEloManager::addObject(cEloBase *obj)
{
   if ( __ECL_ASSERT1__(obj != 0) ) {
      if ( objects == 0 )
         objects = new0 MANAGED_OBJECTS(destroy_objects);
      cEloBase *existing_obj;
      if ( objects->map.lookup(obj->getSignature(), existing_obj) ) {
         __ECL_ASSERT1__(obj == existing_obj);
      } else {
         objects->map[obj->getSignature()] = obj;
      }
   }
}

cEloBase * cEloManager::getObject(cString sig) const
{
   ELO_INIT_WHEN(cEloManager, objects==0);

   cEloBase *obj_found;

   if ( objects != 0 ) {
      if ( objects->map.lookup(sig, obj_found) )
         return obj_found;
   }

   return 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloOperationManager
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Manager-Objekte, die einen logisch zusammengehoerenden
// Satz von Operationen verwalten. Eine Manager-Instanz erzeugt waehrend
// onInitialize() in ihrem Konstruktor, eine Menge von Operationen (via new)
// und fuegt sie mit addOperation() zum Manager hinzu. Die Basisklasse sorgt
// spaeter fuer die korrekte Freigabe der Operations-Objekte.
//
// cEclObject
//  +--cEloBase
//      +--cEloManager
//          +--cEloOperationManager
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloOperationManager : public cEloManager {
   ECL_DECLARE(cEloOperationManager,cEloManager)

public:

   // Konstruktor
   inline cEloOperationManager(bool destroy_objects = true) :
      cEloManager(destroy_objects) { }

   // Operation ueber Signatur ermitteln
   cEloOperation *getOperation(cString op_sig) const;


protected:

   // Operation hinzufuegen
   void addOperation(cEloOperation *op);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etOperationManager; }

};

#endif /*__INTERFACE__*/


// Implementierung cEloOperationManager
// ===========================================================================

void cEloOperationManager::addOperation(cEloOperation *op)
{
   addObject(op);
}

cEloOperation * cEloOperationManager::getOperation(cString op_sig) const
{
   return (cEloOperation*)getObject(op_sig);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloActionManager
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Manager-Objekte, die einen logisch zusammengehoerenden
// Satz von (statischen) Aktionen verwalten. Eine Manager-Instanz erzeugt
// waehrend onInitialize() eine Menge von Operationen (via new) und fuegt
// sie mit addOperation() zum Manager hinzu. Die Basisklasse sorgt spaeter
// fuer die korrekte Freigabe der Operations-Objekte.
//
// cEclObject
//  +--cEloBase
//      +--cEloManager
//          +--cEloActionManager
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloActionManager : public cEloManager {
   ECL_DECLARE(cEloActionManager,cEloManager)

public:

   // Konstruktor
   inline cEloActionManager(bool destroy_objects = true) :
      cEloManager(destroy_objects) { }

   // Anzeigen der Aenderung der Selektion
   void reflectSelectionChange(cEloSelection *selection);
   // Aktion ueber Signatur ermitteln
   cEloActionStatic *getAction(cString action_sig) const;


protected:

   // Aktion hinzufuegen
   void addAction(cEloActionStatic *action);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etActionManager; }

};

#endif /*__INTERFACE__*/


// Implementierung cEloActionManager
// ===========================================================================

void cEloActionManager::reflectSelectionChange(cEloSelection *selection)
{
   ELO_INIT_WHEN(cEloActionManager, objects==0);

   if ( objects != 0 ) {
      for ( IPOSITION pos = objects->map.getStartPosition() ; pos != 0 ; ) {
         cString sig; cEloBase *obj;
         objects->map.getNextAssoc(pos, sig, obj);
         ((cEloActionStatic*)obj)->reflectSelectionChange(selection);
      }
   }
}

void cEloActionManager::addAction(cEloActionStatic *action)
{
   addObject(action);
}

cEloActionStatic * cEloActionManager::getAction(cString action_sig) const
{
   return (cEloActionStatic*)getObject(action_sig);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloDescriptionManager
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Manager-Objekte, die einen logisch zusammengehoerenden
// Satz von Beschreibungsobjekten verwalten. Eine Manager-Instanz erzeugt
// waehrend onInitialize() eine Menge von Beschreibungsobjekten (via new)
// und fuegt sie mit addDescription() zum Manager hinzu. Die Basisklasse
// sorgt spaeter fuer die korrekte Freigabe der Beschreibungsobjekte.
//
// cEclObject
//  +--cEloBase
//      +--cEloManager
//          +--cEloDescriptionManager
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloDescriptionManager : public cEloManager {
   ECL_DECLARE(cEloDescriptionManager,cEloManager)

public:

   // Konstruktor
   inline cEloDescriptionManager(bool destroy_objects = true) :
      cEloManager(destroy_objects) { }

   // Beschreibungsobjekt ueber Signatur ermitteln
   cEloDescription *getDescription(cString descr_sig) const;


protected:

   // Beschreibungsobjekt hinzufuegen
   void addDescription(cEloDescription *descr);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Typ des ELO-Objektes zu erfragen
   ELO_TYPE onGetType() const
      { return etDescriptionManager; }

};

#endif /*__INTERFACE__*/


// Implementierung cEloDescriptionManager
// ===========================================================================

void cEloDescriptionManager::addDescription(cEloDescription *descr)
{
   addObject(descr);
}

cEloDescription * cEloDescriptionManager::getDescription(cString descr_sig) const
{
   return (cEloDescription*)getObject(descr_sig);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEloSelection
// ---------------------------------------------------------------------------
//
// cEclObject
//  +--cEloSelection
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEloSelection : public cEclObject {
   ECL_DECLARE(cEloSelection,cEclObject)

public:

   // Konstruktor
   cEloSelection();
   // Copy-Konstruktor
   cEloSelection(const cEloSelection& other);
   // Destruktor
   ~cEloSelection();

   // Zuweisungsoperator
   cEloSelection& operator=(const cEloSelection& other);


   // Selektion
   // =========

   // Selektion loeschen
   void clearSelection();
   // Element zur Selektion hinzufuegen
   void addElement(cEloElement *elem, int from = -1, int to = -1);
   // Element aus der Selektion entfernen
   void removeElement(cEloElement *elem, int from = -1, int to = -1);

   // Anzahl selektierter Elemente erfragen
   int getElementCount() const;
   // Zugriff auf ein Element der Selektion
   cEloElement *getElement(int index) const;
   // Ist zum Element 'index' ein (Unter-)Bereich definiert?
   bool hasElementRange(int index) const;
   // Unterbereich von Element 'index' erfragen
   void getElementRange(int index, int& from, int& to) const;

   // Ist 'elem' (ggf. mit Unterbereich) in der Selektion enthalten?
   bool isSelected(const cEloElement *elem, int fromto = -1) const;
   bool isSelected(const cEloElement *elem, int from, int to) const;


   // Operationen
   // ===========

   // Unterstuetzten ALLE Elemente der Elementmenge die Operation mit Signatur 'sig_op'?
   bool supportsOperation(cString op_sig, cEloElement *target = 0) const;
   // Operation 'op_sig' auf die aktuelle Elementmenge anwenden
   void execOperation(cString op_sig, int sub_operation = 0, cEloElement *target = 0);


private:

   // Zeiger auf Liste selektierter Elemente (oder 0)
   struct SELECTED_ELEMENTS;
   SELECTED_ELEMENTS *elements;

   // Aktuelle Anzahl Element in der Selektion
   int elem_count;

};

#endif /*__INTERFACE__*/


// Implementierung cEloSelection
// ===========================================================================

struct cEloSelection::SELECTED_ELEMENTS {
   enum { INCREMENT = 11 };
   struct RANGE {
      RANGE();
      RANGE(cEloElement *elem, int from, int to);
      cEloElement *elem_ptr;
      int from_pos, to_pos;
   };
   cArray<RANGE,const RANGE&> array;
};

cEloSelection::cEloSelection()
{
   elements = 0;
   elem_count = 0;
}

cEloSelection::cEloSelection(const cEloSelection& other)
{
   elements = 0;
   elem_count = other.elem_count;

   if ( other.elements != 0 ) {
      elements = new0 SELECTED_ELEMENTS;
      elements->array.setSize(elem_count);
      for ( int i = 0 ; i < elem_count ; i++ )
         elements->array[i] = other.elements->array[i];
   }
}

cEloSelection::~cEloSelection()
{
   delete elements;
}

cEloSelection& cEloSelection::operator=(const cEloSelection& other)
{
   delete elements; elements = 0;
   elem_count = other.elem_count;

   if ( other.elements != 0 ) {
      elements = new0 SELECTED_ELEMENTS;
      elements->array.setSize(elem_count);
      for ( int i = 0 ; i < elem_count ; i++ )
         elements->array[i] = other.elements->array[i];
   }

   return *this;
}

cEloSelection::SELECTED_ELEMENTS::RANGE::RANGE()
{
   elem_ptr = 0;
   from_pos = to_pos = -1;
}

cEloSelection::SELECTED_ELEMENTS::RANGE::RANGE(cEloElement *elem, int from, int to)
{
   elem_ptr = elem;
   from_pos = from;
   to_pos = to;
}


// Selektion
// =========

void cEloSelection::clearSelection()
{
   // Aus Performancegruenden das cArray-Objekt NICHT verkleinern!!
   elem_count = 0;
}

void cEloSelection::addElement(cEloElement *elem, int from, int to)
{
   if ( elements == 0 )
      elements = new0 SELECTED_ELEMENTS;
   if ( elem_count + 1 > elements->array.getSize() )
      elements->array.setSize(elem_count + SELECTED_ELEMENTS::INCREMENT);
   elements->array[elem_count++] = SELECTED_ELEMENTS::RANGE(elem, from, to);
}

void cEloSelection::removeElement(cEloElement *elem, int from, int to)
{
   if ( __ECL_ASSERT1__(elements != 0) ) {

      for ( int i = 0 ; i < elem_count ; i++ ) {
         SELECTED_ELEMENTS::RANGE& range = elements->array[i];
         if ( range.elem_ptr == elem ) {

            if ( from == -1 && to == -1
              || from <= range.from_pos && to >= range.to_pos ) {

               // Element komplett aus Selektion nehmen
               elements->array.removeAt(i);
               elem_count--; i--;

            } else if ( from <= range.from_pos && to < range.to_pos ) {

               // Bereich von vorne her einschraenken
               range.from_pos = to + 1;

            } else if ( from > range.from_pos && to >= range.to_pos ) {

               // Bereich von hinten her einschraenken
               range.to_pos = from - 1;

            } else if ( from > range.from_pos && to < range.to_pos ) {

               // Bereich heraustrennen (neues Element noetig)
               int old_to = range.to_pos;
               range.to_pos = from - 1;
               elements->array.insertAt(i+1, SELECTED_ELEMENTS::RANGE(elem, to+1, old_to));
               elem_count++;

            }

         }
      }

   }
}

int cEloSelection::getElementCount() const
{
   return elem_count;
}

cEloElement * cEloSelection::getElement(int index) const
{
   return __ECL_ASSERT1__(index >= 0 && index < elem_count) ?
      elements->array[index].elem_ptr
    : 0;
}

bool cEloSelection::hasElementRange(int index) const
{
   return __ECL_ASSERT1__(index >= 0 && index < elem_count) ?
      elements->array[index].from_pos >= 0 || elements->array[index].to_pos >= 0
    : false;
}

void cEloSelection::getElementRange(int index, int& from, int& to) const
{
   if ( __ECL_ASSERT1__(index >= 0 && index < elem_count) ) {
      from = elements->array[index].from_pos;
      to = elements->array[index].to_pos;
   } else {
      from = to = -1;
   }
}

bool cEloSelection::isSelected(const cEloElement *elem, int fromto) const
{
   for ( int i = 0 ; i < elem_count ; i++ ) {
      if ( elements->array[i].elem_ptr == elem ) {
         if ( fromto == -1 ||
              ( elements->array[i].from_pos >= 0 &&
                elements->array[i].to_pos >= 0 &&
                elements->array[i].from_pos <= fromto &&
                elements->array[i].to_pos >= fromto ) ) return true;
      }
   }

   return false;
}

bool cEloSelection::isSelected(const cEloElement *elem, int from, int to) const
{
   for ( int i = from ; i <= to ; i++ ) {
      if ( isSelected(elem,i) == false ) return false;
   }

   return true;
}


// Operationen
// ===========

bool cEloSelection::supportsOperation(cString op_sig, cEloElement *target) const
{
   if ( elem_count == 0 )
      return false;

   for ( int i = 0 ; i < elem_count ; i++ ) {
      if ( !elements->array[i].elem_ptr->supportsOperation(op_sig, target) )
         return false;
   }

   return true;
}

void cEloSelection::execOperation(cString op_sig, int sub_operation, cEloElement *target)
{
   int elem_idx;

   // Bilde eine Liste mit Zeigern auf unterschiedliche Operations-Objekte
   // (Dies ist noetig, wenn die Elemente der Selektion mit Operationen
   // registriert wurden, die zwar die gleiche Signatur haben, aber unter-
   // schiedliche Realisierungen)

   cList<cEloOperation*,cEloOperation*> list;
   for ( elem_idx = 0 ; elem_idx < elem_count ; elem_idx++ ) {
      cEloOperation *op = elements->array[elem_idx].elem_ptr->getOperation(op_sig);
      if ( op != 0 && list.find(op) == 0 )
         list.addTail(op);
   }

   if ( list.getCount() > 1 ) {

      // Die Operation 'op_sig' ist bei den Elementen in der Selektionsmenge
      // unterschiedlich realisiert. Bilde entsprechende Selektionsgruppen.

      IPOSITION pos = list.getHeadPosition();
      while ( pos != 0 ) {
         cEloOperation *cur_op = list.getNext(pos);
         cEloSelection sel_grp;

         for ( elem_idx = 0 ; elem_idx < elem_count ; elem_idx++ ) {
            SELECTED_ELEMENTS::RANGE& range = elements->array[elem_idx];
            if ( range.elem_ptr->getOperation(op_sig) == cur_op )
               sel_grp.addElement(range.elem_ptr, range.from_pos, range.to_pos);
         }

         cur_op->execOperation(&sel_grp, sub_operation, target);
      }

   } else if ( list.getCount() == 1 ) {

      // Die Operation 'op_sig' ist bei allen Elementen in der Selektionsmenge
      // gleich realisiert. Ein einzelner Aufruf genuegt.

      list.getHead()->execOperation(this, sub_operation, target);

   }
}


#ifndef QT_KEYBOARD_INPUT_H
#define QT_KEYBOARD_INPUT_H


#include <qobject.h>
#include <qfont.h>

class cQtKeyboardLayout;
class cQtKeyboardButton;
class QLineEdit;
class QTextEdit;
class QValidator;


// ------------------------------------------------------------------------
// Interface-Klasse die den finalen Validator spezifiziert
class iFinalValidator {
public:
   // Liefert true wenn input akzeptiert wird. Ansonsten false und
   // ein error eine Fehlermeldung, die als Signal verschickt wird.
   virtual bool check(const QString &input, QString &error) const = 0;
};


class cQtKeyboardInput : public QObject
{
   Q_OBJECT

public:
   cQtKeyboardInput(QWidget *parent = 0);
   virtual ~cQtKeyboardInput();

   void initialize();

public:
   // ------------------------------------------------------------------------
   // Dialog mit eingebettetem cQtKeyboardLayout, liefert false wenn dieses
   // nicht gefunden wurde.
   //bool setDialog(QDialog *dialog);
   bool setWidget(QWidget *widget);
   cQtKeyboardLayout *getLayout() const;

   // ------------------------------------------------------------------------
   // Im cQtKeyboardLayout die Fonts setzen/lesen
   void setBigFont(const QFont &font);
   QFont getBigFont() const;
   void setSmallFont(const QFont &font);
   QFont getSmallFont() const;

   // ------------------------------------------------------------------------
   // Syntaktischen Validator waehrend der Eingabe festlegen. Mit 0 wird nix
   // validiert.
   void setSyntaxValidator(QValidator *v);
   QValidator *getSyntaxValidator() { return _syntax_validator; }

   // Finalen Validator setzen, der zusaetzlich zum syntaktischen
   // Validator aufgerufen wird, bevor die Eingabe abgeschlossen werden
   // kann. Mit 0 wird nix validiert. (Aufrufer bleibt Eigentuemer.)
   void setFinalValidator(iFinalValidator *fv) { _final_validator = fv; }
   iFinalValidator *getFinalValidator() const { return _final_validator; }

   // ------------------------------------------------------------------------
   // Eingabe-Vorinitialisierung, liefert false wenn diese vom Syntax
   // Validator als INVALID abgelehnt wird und nicht uebernommen wurde!
   bool setInput(const QString &input);
   // Eingabe Rueckgabewert
   QString getInput() const;

   // Dialog anzeigen und Eingabe durchfuehren
   enum EXEC_CODE {
      execAccepted = 0, // OK, Enter
      execRejected = 1, // Esc, Cancel
      execError = -1    // kein Dialog oder Layout definiert
   };
   int exec();

   // ------------------------------------------------------------------------
   // Widget mit dem die Eingabe stattfinden soll. Möglich sind:
   // 0 - kein Widget, es wird mit einer internen Variable gearbeitet, die bei
   //     jeder Veränderung das Signal cQtKeyboardLayout::inputChanged()
   //     auslöst. Einzige Korrekturmöglichkeit ist Backspace.
   // QLineEdit* - QLineEdit dient als Eingabevariable
   // QTextEdit* - QTextEdit dient als Eingabevariable
   void setEchoWidget(QWidget *widget);

   // ------------------------------------------------------------------------
signals:
   // Finale Validierung fehlgeschlagen
   void finalValidationFailed(const QString &error);
   // Eingabe wurde (nach Fehlersignal) ohne Fehler fortgesetzt
   void clearValidationError();
   // Action-Button gedrueckt
   void actionButtonClicked(cQtKeyboardButton *button);
   void actionButtonToggled(cQtKeyboardButton *button, bool on);

   // -----------------------
   // Intern: Hilfsklassen
   // -----------------------
private:
   // Interface-Klasse zur Verknüpfung mit Eingabe-Widget
   class iEcho {
   public:
      // Text am Anfang der Eingabe initialisieren
      virtual void setText(const QString &text) = 0;
      // Text auslesen (zur Validierung und am Ende der Eingabe)
      virtual QString getText() const = 0;
      // Nächstes Zeichen einfügen (typeNormal)
      virtual void insert(const QString &key) = 0;
      // Validator festlegen
      virtual void setValidator(QValidator *v) { };

      // Vorzeichenwechsel
      virtual void changeSign() { }
      // Zeichen links vom Cursor löschen
      virtual void delLeft() { }
      // Zeichen rechts/unter Cursor löschen
      virtual void delRight() { }
      // Gesamte Eingabe löschen
      virtual void delAll() { }
      // Cursor: Zeichen nach links
      virtual void moveLeft() { }
      // Cursor: Zeichen nach rechts
      virtual void moveRight() { }
      // Cursor: Zeile nach oben
      virtual void moveUp() { }
      // Cursor: Zeile nach unten
      virtual void moveDown() { }
      // Cursor: Zeilenanfang
      virtual void moveLineStart() { }
      // Cursor: Zeilenende
      virtual void moveLineEnd() { }
      // Cursor: Seite nach oben
      virtual void movePgUp() { }
      // Cursor: Seite nach unten
      virtual void movePgDown() { }

      // Markierung: Anfang
      virtual void markStart() { }
      // Markierung: Ende
      virtual void markEnd() { }
      // Alles markieren (fuer QuickOverwrite ein)
      virtual void markAll() { }
      // Nix markieren (fuer QuickOverwrite aus)
      virtual void markNothing() { }

      // letzte Änderung rückgängig machen
      virtual void undo() { }
   };

   class cEchoNoWidget : public iEcho 
   {
   public:
      virtual void setText(const QString &text);
      virtual QString getText() const;
      virtual void insert(const QString &key);
      virtual void changeSign();
      virtual void delLeft();
      virtual void delAll();
      virtual void undo();
   private:
      QString _line;
      QString _undo_line;
   };

   class cEchoLineEdit : public iEcho
   {
   public:
      cEchoLineEdit(QLineEdit *widget) : _widget(widget), _mark(false) { }
      virtual void setText(const QString &text);
      virtual QString getText() const;
      virtual void insert(const QString &key);
      virtual void setValidator(QValidator *v);
      virtual void changeSign();
      virtual void delLeft();
      virtual void delRight();
      virtual void delAll();
      virtual void moveLeft();
      virtual void moveRight();
      virtual void undo();
      virtual void markStart();
      virtual void markEnd();
      virtual void markAll();
      virtual void markNothing();

   private:
      QLineEdit *_widget;
      bool _mark;
   };

   class cEchoTextEdit : public iEcho
   {
   public:
      cEchoTextEdit(QTextEdit *widget) : _widget(widget), _paraFrom(0), _indexFrom(0) { }
      virtual void setText(const QString &text);
      virtual QString getText() const;
      virtual void insert(const QString &key);
      virtual void delLeft();
      virtual void delRight();
      virtual void delAll();
      virtual void moveLeft();
      virtual void moveRight();
      virtual void moveUp();
      virtual void moveDown();
      virtual void moveLineStart();
      virtual void moveLineEnd();
      virtual void movePgUp();
      virtual void movePgDown();
      virtual void undo();
      virtual void markStart();
      virtual void markEnd();
      virtual void markAll();
      virtual void markNothing();

   private:
      QTextEdit *_widget;
      int _paraFrom,_indexFrom;
   };


   // -----------------------
   // Intern: Hilfsfunktionen
   // -----------------------
private:   
   // Validator aufrufen
   int callSyntaxValidator(const QString &line) const;
   bool callFinalValidator(const QString &line, QString &error) const;
   // Signal für geänderte Eingabe in cQtKeyboardLayout auslösen
   void inputChanged(const QString &input);

private slots:
   // Slots fuer die Signale aus cQtKeyboardLayout
   void slotClicked(cQtKeyboardButton *button);
   void slotToggled(cQtKeyboardButton *button, bool on);

   // -----------------------
   // Intern: Attribute
   // -----------------------
private:
   // Qt Dialog mit eingebettetem cQtKeyboardLayout
   QWidget *_parent_widget;
   // Lokalisiertes Keyboard-Layout
   cQtKeyboardLayout *_keyboard_layout;

   // Syntax Validator um die Eingabe zu pruefen (oder 0)
   QValidator *_syntax_validator;

   // Finaler Validator (oder 0)
   iFinalValidator *_final_validator;

   // Widget für Handling der Eingabe
   iEcho *_echo_widget;

   // erste Eingabeaktion (fuer quickOverwrite)
   bool _first_button;
   // Fehler signalisiert (fuer clearValidationError)
   bool _error_emitted;
   // Text wird gerade markiert
   bool _mark_text;

   // Umschalttasten
   enum SHIFT_STATE {
      shiftNone  = 0,
      shiftUpper = 1,
      shiftAlt   = 2
   } _shift_state;
   bool _shift_lock;
   bool _caps_lock;
   cQtKeyboardButton *_shift_button;
   bool _multi_line;

};


#endif // QT_KEYBOARD_INPUT_H


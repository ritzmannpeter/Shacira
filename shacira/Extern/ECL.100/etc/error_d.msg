#
# EB_ERR
#
ERR-I-01 Funktion nicht implementiert
ERR-I-02 Fehlercode falsch formatiert
ERR-E-01 Allgemeiner Fehler$1{, $1}$2{, $2}
ERR-E-02 Ungültiger Zeiger$1{: $1}
ERR-E-03 Ungültiges Handle$1{: $1}
ERR-E-04 Ungültiger Parameter$1{ $1}$2{: $2}
ERR-E-05 Fehler bei Initialisierung
ERR-E-06 Zeitüberschreitung$1{ bei $1}
ERR-E-07 Interner Überlauf$1{ in Modul $1}
ERR-E-08 Interner Unterlauf$1{ in Modul $1}
ERR-F-01 Kein freier Speicher mehr
ERR-F-02 Keine freien Handles mehr

#
# EB_MSG
#
MSG-E-01 Kann $1 nicht Öffnen zum Senden
MSG-E-02 Kann $1 nicht Erzeugen zum Empfangen
MSG-E-03 Fehler beim Senden zu $1
MSG-E-04 Fehler beim Empfangen von $1
MSG-E-05 Versuch, leere Meldung zu $1 zu senden
MSG-E-06 Ungültige Meldung von $1 empfangen
MSG-E-07 Ungültiges Protokoll in $1 angegeben
MSG-E-08 Protokoll in $1 nicht unterstützt
MSG-E-09 Meldung fuer $1 zu lang
MSG-E-10 Anonymer Adressat nicht zulässig

#
# EB_FILE
#
FIL-I-01 errEOF$1{: $1}
FIL-I-02 errNoMatch$1{: $1}
FIL-E-01 errIllSpec$1{: $1}
FIL-E-02 errIllDevice$1{: $1}
FIL-E-03 errIllParam$1{: $1}
FIL-E-04 errIllAccess$1{: $1}
FIL-E-05 errFileNotFound$1{: $1}
FIL-E-06 errPathNotFound$1{: $1}
FIL-E-07 errExists$1{: $1}
FIL-E-08 errPermDenied$1{: $1}
FIL-E-09 errGeneralIO$1{: $1}
FIL-E-10 errDeviceFull$1{: $1}
FIL-E-11 errWriteProt$1{: $1}
FIL-E-12 errSeek$1{: $1}
FIL-E-13 errUnget$1{: $1}
FIL-E-14 errShare$1{: $1}
FIL-E-15 errDeviceInUse$1{: $1}
FIL-E-16 errDeviceLocked$1{: $1}
FIL-E-17 errPipeBusy$1{: $1}
FIL-E-18 errDeviceNotReady$1{: $1}
FIL-E-19 errSorry$1{: $1}
FIL-F-01 errIllHandle$1{: $1}
FIL-F-02 errTableOverflow$1{: $1}
FIL-F-03 errTooManyFiles$1{: $1}
FIL-F-04 errLib$1{: $1}

#
# EDB_DATABASE
#
DBI-E-01 Allgemeiner Datenbankfehler$1{, $1}$2{, $2}
DBI-E-02 Datenbanktyp nicht unterstützt$1{, $1}$2{, $2}
DBI-E-03 Fehler beim LOGIN an Datenbank$1{, $1}$2{, $2}
DBI-E-04 Timeout beim Zugriff auf eine Resource$1{, $1}$2{, $2}
#
DBI-E-06 Fehler beim Öffnen einer Tabelle (RECORD)$1{, $1}$2{, $2}
DBI-E-07 Resource momentan nicht bereit (RECORD)$1{, $1}$2{, $2}
DBI-E-08 Datensatz seit letztem Zugriff geändert (RECORD)$1{, $1}$2{, $2}
#
DBI-E-11 Anforderung einer Umgebung fehlgeschlagen (SQL)$1{, $1}$2{, $2}
DBI-E-12 Anforderung einer Verbindung fehlgeschlagen (SQL)$1{, $1}$2{, $2}
DBI-E-13 Anforderung eines Cursors fehlgeschlagen (SQL)$1{, $1}$2{, $2}
#
DBI-E-21 Fehler beim Definieren von Ergebnisspalten$1{, $1}$2{, $2}
DBI-E-22 Fehler beim Binden von Parametervariablen$1{, $1}$2{, $2}
DBI-E-23 Benötigte Parametervariable nicht gebunden$1{, $1}$2{, $2}
DBI-E-24 Fehler beim Binden einer statischen Parametervariable$1{, $1}$2{, $2}
DBI-E-25 Fehler beim Setzen des Zugriffsmodes$1{, $1}$2{, $2}
DBI-E-26 Fehler bei der Analyse einer SQL-Anweisung$1{, $1}$2{, $2}
DBI-E-27 Fehler beim Ausführen einer SQL-Anweisung$1{, $1}$2{, $2}
DBI-E-28 Fehler beim Lesen von der Datenbank$1{, $1}$2{, $2}
#
DBI-E-31 Keine Daten gefunden$1{, $1}$2{, $2}
#
DBI-E-41 errDuplicateKey
DBI-E-42 errBindType
DBI-E-43 errFetchOutOfSeq
DBI-E-44 errVarNotInList
DBI-E-45 errColumnNull
DBI-E-46 errColumnTooLarge
DBI-E-47 errNullFetched
DBI-E-48 errColumnTrunc
DBI-E-49 errColumnUpdNull
DBI-E-50 errRowidInvalid
DBI-E-51 errValueTooLarge
DBI-E-52 errRowidUnavail
DBI-E-53 errRowidUnavail2
DBI-E-54 errRealOverflow
DBI-E-55 errCheckConstraint
DBI-E-56 errNoParentRecord
DBI-E-57 errChildRecords
DBI-E-58 errNoTrunc
DBI-E-59 errNoRetcValue
DBI-E-60 errAutoCommitFailed

#
# FBSON
#
FON-E-01 Header not Found$1{: $1}
FON-E-02 Unexpected EOF$1{: $1}
FON-E-03 Illegal Part$1{: $1}
FON-E-04 Template Expected (File $1 line $2)
FON-E-05 Multiple Template$1 (File $1 line $2)
FON-E-06 Unknown Option$1{: $1}

FON-F-01 Unknown Exception
FON-F-02 Display $1 not available$2{ ($2)}
FON-F-03 Machine $1 not available$2{ ($2)}

#
# CSERIAL
#
SER-F-01 Open failed$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-02 Bad Parameters$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-03 Read Data$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-04 Write Data$1{: $1}$2{: $2}$3{: $3}$4{: $4}

TST-E-01 Testfehlermeldung #1
TST-E-02 Testfehlermeldung #2 <$1{xx$1}>


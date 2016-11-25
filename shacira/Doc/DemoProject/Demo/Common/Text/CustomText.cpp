#include "FirstHeader.h"
#include "CustomText.h"
#include <qobject.h>

// PR 9.2.05 >>

#include "System/Text/cTextTable.h"
static cTextTable * _TextTable = NULL;

// PR 23.03.05 _GetCustomText must be a C-Style function

extern "C" {

CONST_STRING_T _GetCustomText(ULONG_T text_id)
{
   if (_TextTable == NULL) {
      _TextTable = new cTextTable((TEXT_ENTRY_T*)_CustomText);
   }
   return _TextTable->GetText(text_id);
}

}

// PR 9.2.05 <<

const TEXT_ENTRY_T _CustomText[] = {
   {GUIMSG_VALUE_TO_LOW,           QT_TRANSLATE_NOOP("custom", "Wert zu klein - Min = #1")},
   {GUIMSG_VALUE_TO_LARGE,         QT_TRANSLATE_NOOP("custom", "Wert zu groß - Max = #1")},
   {GUIMSG_NO_SETTING_MODE,        QT_TRANSLATE_NOOP("custom", "Einrichten betätigen")},
   {GUIMSG_NO_VARREF,              QT_TRANSLATE_NOOP("custom", "Variablenreferenz #1 kann nicht aufgelößt werden")},
   {GUIMSG_MOLDHEIGHT_STILL_ACTIV, QT_TRANSLATE_NOOP("custom", "Werkzeughöhenabgleich der SPS noch aktiv")},
   {PRGMSG_SHOT_COUNTER_ZERO,      QT_TRANSLATE_NOOP("custom", "Sub. Schußzähler = 0")},
   {DEVMSG_NOTHING_TEXT,           QT_TRANSLATE_NOOP("custom", "???")},
   {DEVMSG_HEAT_CONTROLLER_DESC,   QT_TRANSLATE_NOOP("custom", "Regler #1")},
   {DEVMSG_FREE1,                  QT_TRANSLATE_NOOP("custom", "")},
   {DEVMSG_FREE2,                  QT_TRANSLATE_NOOP("custom", "")},
   {DEVMSG_BARREL_TOLERR_UP_WIDE_NOAGG,    QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Zylinderheizung Zone #1")},
   {DEVMSG_BARREL_TOLERR_UP_WIDE_AGG,      QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Zylinderheizung Aggregat #2 Zone #1")},
   {DEVMSG_BARREL_TOLERR_UP_NARROW_NOAGG,  QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Zylinderheizung Zone #1")},
   {DEVMSG_BARREL_TOLERR_UP_NARROW_AGG,    QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Zylinderheizung Aggregat #2 Zone #1")},
   {DEVMSG_BARREL_TOLERR_LOW_WIDE_NOAGG,   QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Zylinderheizung Zone #1")},
   {DEVMSG_BARREL_TOLERR_LOW_WIDE_AGG,     QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Zylinderheizung Aggregat #2 Zone #1")},
   {DEVMSG_BARREL_TOLERR_LOW_NARROW_NOAGG, QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Zylinderheizung Zone #1")},
   {DEVMSG_BARREL_TOLERR_LOW_NARROW_AGG,   QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Zylinderheizung Aggregat #2 Zone #1")},
   {DEVMSG_BARREL_TOLERR_SENSOR_BROKEN_NOAGG,QT_TRANSLATE_NOOP("custom", "Fühlerbruch Zylinderheizung Zone #1")},
   {DEVMSG_BARREL_TOLERR_SENSOR_BROKEN_AGG,QT_TRANSLATE_NOOP("custom", "Fühlerbruch Zylinderheizung Aggregat #2 Zone #1")},
   {DEVMSG_TOOL_TOLERR_UP_WIDE_NOAGG,      QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Werkzeugheizung Zone #1")},
   {DEVMSG_TOOL_TOLERR_UP_WIDE_AGG,        QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Werkzeugheizung Aggregat #2 Zone #1")},
   {DEVMSG_TOOL_TOLERR_UP_NARROW_NOAGG,    QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Werkzeugheizung Zone #1")},
   {DEVMSG_TOOL_TOLERR_UP_NARROW_AGG,      QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Werkzeugheizung Aggregat #2 Zone #1")},
   {DEVMSG_TOOL_TOLERR_LOW_WIDE_NOAGG,     QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Werkzeugheizung Zone #1")},
   {DEVMSG_TOOL_TOLERR_LOW_WIDE_AGG,       QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Werkzeugheizung Aggregat #2 Zone #1")},
   {DEVMSG_TOOL_TOLERR_LOW_NARROW_NOAGG,   QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Werkzeugheizung Zone #1")},
   {DEVMSG_TOOL_TOLERR_LOW_NARROW_AGG,     QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Werkzeugheizung Aggregat #2 Zone #1")},
   {DEVMSG_TOOL_TOLERR_SENSOR_BROKEN_NOAGG,QT_TRANSLATE_NOOP("custom", "Fühlerbruch Werkzeugheizung Zone #1")},
   {DEVMSG_TOOL_TOLERR_SENSOR_BROKEN_AGG,  QT_TRANSLATE_NOOP("custom", "Fühlerbruch Werkzeugheizung Aggregat #2 Zone #1")},
   {DEVMSG_TEMP_TOLERR_UP_WIDE_NOAGG,      QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Temperiergeräte Zone #1")},
   {DEVMSG_TEMP_TOLERR_UP_WIDE_AGG,        QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Temperiergeräte Aggregat #2 Zone #1")},
   {DEVMSG_TEMP_TOLERR_UP_NARROW_NOAGG,    QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Temperiergeräte Zone #1")},
   {DEVMSG_TEMP_TOLERR_UP_NARROW_AGG,      QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Temperiergeräte Aggregat #2 Zone #1")},
   {DEVMSG_TEMP_TOLERR_LOW_WIDE_NOAGG,     QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Temperiergeräte Zone #1")},
   {DEVMSG_TEMP_TOLERR_LOW_WIDE_AGG,       QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Temperiergeräte Aggregat #2 Zone #1")},
   {DEVMSG_TEMP_TOLERR_LOW_NARROW_NOAGG,   QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Temperiergeräte Zone #1")},
   {DEVMSG_TEMP_TOLERR_LOW_NARROW_AGG,     QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Temperiergeräte Aggregat #2 Zone #1")},
   {DEVMSG_TEMP_TOLERR_SENSOR_BROKEN_NOAGG,QT_TRANSLATE_NOOP("custom", "Fühlerbruch Temperiergeräte Zone #1")},
   {DEVMSG_TEMP_TOLERR_SENSOR_BROKEN_AGG,  QT_TRANSLATE_NOOP("custom", "Fühlerbruch Temperiergeräte Aggregat #2 Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_UP_WIDE_NOAGG,   QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Reserveheizung Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_UP_WIDE_AGG,     QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Reserveheizung Aggregat #2 Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_UP_NARROW_NOAGG, QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Reserveheizung Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_UP_NARROW_AGG,   QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Reserveheizung Aggregat #2 Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_LOW_WIDE_NOAGG,  QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Reserveheizung Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_LOW_WIDE_AGG,    QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Reserveheizung Aggregat #2 Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_LOW_NARROW_NOAGG,QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Reserveheizung Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_LOW_NARROW_AGG,  QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Reserveheizung Aggregat #2 Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_SENSOR_BROKEN_NOAGG,QT_TRANSLATE_NOOP("custom", "Fühlerbruch Reserveheizung Zone #1")},
   {DEVMSG_RESHEAT_TOLERR_SENSOR_BROKEN_AGG,  QT_TRANSLATE_NOOP("custom", "Fühlerbruch Reserveheizung Aggregat #2 Zone #1")},
   {DEVMSG_OIL_TOLERR_UP_WIDE_NOAGG,       QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Ölheizung")},
   {DEVMSG_OIL_TOLERR_UP_WIDE_AGG,         QT_TRANSLATE_NOOP("custom", "Außer weiter oberen Toleranz Ölheizung Aggregat #2")},
   {DEVMSG_OIL_TOLERR_UP_NARROW_NOAGG,     QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Ölheizung")},
   {DEVMSG_OIL_TOLERR_UP_NARROW_AGG,       QT_TRANSLATE_NOOP("custom", "Außer enger oberen Toleranz Ölheizung Aggregat #2")},
   {DEVMSG_OIL_TOLERR_LOW_WIDE_NOAGG,      QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Ölheizung")},
   {DEVMSG_OIL_TOLERR_LOW_WIDE_AGG,        QT_TRANSLATE_NOOP("custom", "Außer weiter untere Toleranz Ölheizung Aggregat #2")},
   {DEVMSG_OIL_TOLERR_LOW_NARROW_NOAGG,    QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Ölheizung")},
   {DEVMSG_OIL_TOLERR_LOW_NARROW_AGG,      QT_TRANSLATE_NOOP("custom", "Außer enger unteren Toleranz Ölheizung Aggregat #2")},
   {DEVMSG_OIL_TOLERR_SENSOR_BROKEN_NOAGG, QT_TRANSLATE_NOOP("custom", "Fühlerbruch Ölheizung")},
   {DEVMSG_OIL_TOLERR_SENSOR_BROKEN_AGG,   QT_TRANSLATE_NOOP("custom", "Fühlerbruch Ölheizung Aggregat #2")},
    // displaytxt for proc pages
   {GUIPROC_DIM_MM,                 QT_TRANSLATE_NOOP("custom", "mm")}, 
   {GUIPROC_DIM_BAR,                QT_TRANSLATE_NOOP("custom", "bar")},  
   {GUIPROC_DIM_SEC,                QT_TRANSLATE_NOOP("custom", "s")},  
   {GUIPROC_INJ_SINGLE_AGG_NAME,    QT_TRANSLATE_NOOP("custom", "Spritzeinheit")},
   {GUIPROC_INJ_SINGLE_AGG_PRSBACK, QT_TRANSLATE_NOOP("custom", "spec. Staudruck")},  
   {GUIPROC_INJ_SINGLE_AGG_SRCPOS,  QT_TRANSLATE_NOOP("custom", "Schneckenposition")},  
   {GUIPROC_INJ_SINGLE_AGG_BRSNOZZLE, QT_TRANSLATE_NOOP("custom", "Düsenanpresskraft")},  
   {GUIPROC_INJ_SINGLE_STEP_PRS,    QT_TRANSLATE_NOOP("custom", "Stufe #1 Einspritzdruck")},  
   {GUIPROC_INJ_SINGLE_STEP_TIM,    QT_TRANSLATE_NOOP("custom", "Stufe #1 Einspritzzeit")},  
   {GUIPROC_INJ_SINGLE_STEP_STR,    QT_TRANSLATE_NOOP("custom", "Stufe #1 Einspritzweg")},  
   {GUIPROC_INJ_PLSTCOOL,           QT_TRANSLATE_NOOP("custom", "Abkühlzeit")},  
   {GUIPROC_INJ_SINGLE_STEP_CUS,     QT_TRANSLATE_NOOP("custom", "Polster")},
   {PRGMSG_EMPTY_TEXT,               QT_TRANSLATE_NOOP("custom", "")},
   {PRGMSG_OPMODE_SETTING,           QT_TRANSLATE_NOOP("custom", "Einrichten")},  
   {PRGMSG_OPMODE_MANUAL,            QT_TRANSLATE_NOOP("custom", "Handbetr.")},
   {PRGMSG_OPMODE_SEMI_AUTO,         QT_TRANSLATE_NOOP("custom", "Halb-Auto.")},
   {PRGMSG_OPMODE_AUTO,              QT_TRANSLATE_NOOP("custom", "Automatik")},
   {PRGMSG_INFO1,                    QT_TRANSLATE_NOOP("custom", "RAM-Modul erzeugt")},
   {PRGMSG_INFO2,                    QT_TRANSLATE_NOOP("custom", "EPROM-Modul erzeugt")},
   {PRGMSG_INFO3,                    QT_TRANSLATE_NOOP("custom", "Force-Mode nicht möglich")},
   {PRGMSG_INFO4,                    QT_TRANSLATE_NOOP("custom", "SPS-Init nicht erlaubt")},
   {PRGMSG_INFO5,                    QT_TRANSLATE_NOOP("custom", "SPS Text 5")},
   {PRGMSG_INFO6,                    QT_TRANSLATE_NOOP("custom", "Werkzeughöhenabgleich")},
   {PRGMSG_INFO7,                    QT_TRANSLATE_NOOP("custom", "Einfahrschmierintervall eingeschaltet")},
   {PRGMSG_INFO8,                    QT_TRANSLATE_NOOP("custom", "SPS Text 8")},
   {PRGMSG_INFO9,                    QT_TRANSLATE_NOOP("custom", "SPS Text 9")},
   {PRGMSG_INFO10,                   QT_TRANSLATE_NOOP("custom", "Optimierung läuft")},
   {PRGMSG_INFO11,                   QT_TRANSLATE_NOOP("custom", "Optimierung beendet - Werte übernehmen")},
   {PRGMSG_INFO12,                   QT_TRANSLATE_NOOP("custom", "Heizung für die Optimierung einschalten")},
   {PRGMSG_INFO13,                   QT_TRANSLATE_NOOP("custom", "Sollwert zu klein für Optimierung")},
   {PRGMSG_INFO14,                   QT_TRANSLATE_NOOP("custom", "Optimierung abgebrochen")},
   {GUIPROC_INJ_SINGLE_AGG_PLASTPOS, QT_TRANSLATE_NOOP("custom", "Plastifizierweg")},  
   {GUIMSG_MACHINEDATA_READ,         QT_TRANSLATE_NOOP("custom", "Maschinendatensatz wurde in den #1 eingelesen")},
   {GUIMSG_MACHINEDATA_WRITE,        QT_TRANSLATE_NOOP("custom", "Maschinendatensatz aus dem #1 wurde erstellt")},
   {GUIPROC_CYCLE_TIME_ACTUAL,       QT_TRANSLATE_NOOP("custom", "Aktuelle Zykluszeit")},
   {GUIPROC_SHOT_COUNTER,            QT_TRANSLATE_NOOP("custom", "Schußzähler")},
   {GUIPROC_DIM_PARTS ,              QT_TRANSLATE_NOOP("custom", "Stück")},
   {GUIPROC_SETCFGINJSTAGES,         QT_TRANSLATE_NOOP("custom", "Einspritzstufen")},
   {GUIPROG_SETPRSINJ,               QT_TRANSLATE_NOOP("custom", "Einspritzdruck Einheit #1 Stufe #2")},
   {GUIPROG_SETTIMEINJ,              QT_TRANSLATE_NOOP("custom", "Einspritzzeit Einheit #1 Stufe #2")},
   {GUIPROC_SETSTRINJ,               QT_TRANSLATE_NOOP("custom", "Einspritzweg Einheit #1 Stufe #2")},
   {GUIMSG_RESTART_MACHINE,          QT_TRANSLATE_NOOP("custom", "Bitte Maschine neu aufstarten !")},
   {GUIMSG_SWITCH_MOTORS_OFF,        QT_TRANSLATE_NOOP("custom", "Bitte Motoren ausschalten !")},
   {GUIMSG_SWITCH_BARRELHEATING_OFF, QT_TRANSLATE_NOOP("custom", "Bitte Zylinderheizung ausschalten !")},
   {GUIMSG_DATASET_FG_TO_BG,         QT_TRANSLATE_NOOP("custom", "Daten wurden in den Hintergrund übertragen")},
   {GUIMSG_DATASET_CHANGE_FG_BG,     QT_TRANSLATE_NOOP("custom", "Alle Daten wurden ausgetauscht")},
    // display text for pasword
   {GUIMSG_USER_SUCCESSFUL_LOGON,    QT_TRANSLATE_NOOP("custom", "erfolgreich angemeldet")},
   {GUIMSG_USER_LOGOFF,              QT_TRANSLATE_NOOP("custom", "wurde abgemeldet")},
   {GUIMSG_AUTOLOGOFF_ACTIV,         QT_TRANSLATE_NOOP("custom", "Auto logoff ist aktiv")},
   {GUIMSG_AUTOLOGOFF_INACTIV,       QT_TRANSLATE_NOOP("custom", "Auto logoff nicht aktiv")},

   {GUIMSG_MACHINEDATA_REMOVED,      QT_TRANSLATE_NOOP("custom", "Maschinendatensatz wurde gelöscht")},
   {GUIMSG_MACHINEDATA_NOT_REMOVED,  QT_TRANSLATE_NOOP("custom", "Maschinendatensatz konnte nicht gelöscht werden")},

   {GUIMSG_MLD_HEIGHT_ACTIV,         QT_TRANSLATE_NOOP("custom", "Werkzeughöhenabgleich der SPS noch aktiv")},
   {GUIMSG_MLD_NOT_IN_OPEN_STROKE,   QT_TRANSLATE_NOOP("custom", "Werkzeug nicht in Öffnungsweite")},

   {GUIMSG_NO_ZONE_TO_TUNE,          QT_TRANSLATE_NOOP("custom", "Keine Zone für Ableich ausgewählt")},
   
   {GUIMSG_BRLNOZ_ADJ_NOTPOSSIBLE,   QT_TRANSLATE_NOOP("custom", "Bitte Taste Aggregat vor betätigen")},

   {GUIMSG_TEXT_BG,                  QT_TRANSLATE_NOOP("custom", "Hintergrund")},
   {GUIMSG_TEXT_FG,                  QT_TRANSLATE_NOOP("custom", "Vordergrund")},

   {GUIMSG_PRINTER_EXPORT,           QT_TRANSLATE_NOOP("custom", "Druckausgabe wurde exportiert auf #1")},
   {GUIMSG_PRINTER_OUTPUT,           QT_TRANSLATE_NOOP("custom", "Druckausgabe erfolgt auf Standard Drucker")},
   {GUIMSG_NO_SCRDUMP_EXPORT_FOUND,  QT_TRANSLATE_NOOP("custom", "Keine Druck-Verzeichnisse vorhanden")},

   {GUIMSG_NO_VALID_DIRECTORY,       QT_TRANSLATE_NOOP("custom", "Bitte geben Sie ein gültiges Verzeichnis an, z.B: D:\\Mosaic.\n")},
      
   {GUIMSG_CONF_DIGITAL_OUT_STAGE,   QT_TRANSLATE_NOOP("custom", "Stufe")},
   {GUIMSG_CONF_DIGITAL_OUT_COUNT,   QT_TRANSLATE_NOOP("custom", "Anzahl")},
   {GUIMSG_CONF_AO_DIM_SCREW_POS,    QT_TRANSLATE_NOOP("custom", "10 V =  500 mm")},
   {GUIMSG_CONF_AO_DIM_CLAMP_POS,    QT_TRANSLATE_NOOP("custom", "10 V = 1000 mm")},
   {GUIMSG_CONF_AO_DIM_EJECTOR_POS,  QT_TRANSLATE_NOOP("custom", "10 V =  500 mm")},
   {GUIMSG_CONF_AO_DIM_LOCKING_PRES, QT_TRANSLATE_NOOP("custom", "10 V =  400 bar")},
   {GUIMSG_CONF_AO_DIM_SYSTEM_PRES,  QT_TRANSLATE_NOOP("custom", "10 V =  400 bar")},
   {GUIMSG_CONF_AO_DIM_CAVITY_PRES,  QT_TRANSLATE_NOOP("custom", "10 V = 5000 bar")},
   {GUIMSG_CONF_AO_DIM_INJ_VELOCITY, QT_TRANSLATE_NOOP("custom", "10 V =  500 mm/s")},
   {GUIMSG_CONF_AO_DIM_CLAMP_VELOCITY, QT_TRANSLATE_NOOP("custom", "10 V = 1000 mm/s")},
   {GUIMSG_CONF_AO_DIM_EJECTOR_VELOCITY, QT_TRANSLATE_NOOP("custom", "10 V =  500 mm/s")},
   {GUIMSG_CONF_AO_DIM_PLAST_SPEED,  QT_TRANSLATE_NOOP("custom", "10 V =  500 U/min")},
   {GUIMSG_CONF_AO_DIM_NOZZLE_TEMP,  QT_TRANSLATE_NOOP("custom", "10 V =  500 `C")},

   {GUIMSG_DIFF_SYMBOL_NR,           QT_TRANSLATE_NOOP("custom", "SPS-Versionnummer falsch")},
   {GUIMSG_NO_FILE_CREATED,          QT_TRANSLATE_NOOP("custom", "Maschinendaten-Datei konnte nicht erstellt werden")},

   {PRGMSG_GRAPHIC_OUT_OF_TOLERANCE, QT_TRANSLATE_NOOP("custom", "Graphik: Toleranzband verlassen")},
    //Toleranz control
   {PROCMSG_TOL_CNRL,                QT_TRANSLATE_NOOP("custom", "Toleranzbandüberschreitung")},  
   {PROCMSG_TOL_CNRL_INJ_PRS,        QT_TRANSLATE_NOOP("custom", "Toleranzbandüberschreitung des Einspritzdruck der Einheit #1 und Stufe #2.")},
   {PROCMSG_TOL_CNRL_INJ_TIM,        QT_TRANSLATE_NOOP("custom", "Toleranzbandüberschreitung der Einspritzzeit der Einheit #1 und Stufe #2.")},
   {PROCMSG_TOL_CNRL_INJ_STR,        QT_TRANSLATE_NOOP("custom", "Toleranzbandüberschreitung des Einspritzwegs der Einheit #1 und Stufe #2.")},
   {PROCMSG_TOL_CNRL_PLAST_STR,      QT_TRANSLATE_NOOP("custom", "Toleranzbandüberschreitung des Plastifizierwegs der Einheit #1")},
   {PROCMSG_TOL_CNRL_CSN,            QT_TRANSLATE_NOOP("custom", "Toleranzüberschreitung des Polsters der Einheit #1.")},

   {GUIMSG_DIM_MIN,                  QT_TRANSLATE_NOOP("custom", "min")}, 
   {GUIMSG_DIM_HOUR,                 QT_TRANSLATE_NOOP("custom", "h")},  
   {GUIMSG_DIM_DAY,                  QT_TRANSLATE_NOOP("custom", "d")},

   {GUIMSG_WRONG_PASSWORD,           QT_TRANSLATE_NOOP("custom", "Falsches Passwort")},
   {GUIMSG_USER_DOES_NOT_EXIST,      QT_TRANSLATE_NOOP("custom", "Benutzer nicht vorhanden")},
   {GUIMSG_USER_ALREADY_EXISTS,      QT_TRANSLATE_NOOP("custom", "Benutzer existiert bereits")},
   {GUIMSG_THIS_USER_CANNOT_BE_DELETED, QT_TRANSLATE_NOOP("custom", "Dieser Benutzer kann nicht gelöscht werden")},
   {GUIMSG_COULD_NOT_CREATE_NEW_USER,QT_TRANSLATE_NOOP("custom", "Benutzer konnte nicht angelegt werden")},
   {GUIMSG_DELETE_USER,              QT_TRANSLATE_NOOP("custom", "Benutzer löschen")},
   {GUIMSG_SURE_YOU_WANT_DELETE,     QT_TRANSLATE_NOOP("custom", "Benutzer wirklich löschen")},
   {GUIMSG_YES,                      QT_TRANSLATE_NOOP("custom", "Ja")},
   {GUIMSG_NO,                       QT_TRANSLATE_NOOP("custom", "Nein")},
   {GUIMSG_MAX_USER_ACCOUNTS_REACHED,QT_TRANSLATE_NOOP("custom", "Max. Anzahl Benutzer erreicht")},
   {GUIMSG_EJECTORADJUST_NOTSET,     QT_TRANSLATE_NOOP("custom", "Auswerfernullpunkt wurde nicht korrekt beendet")},
   {GUIMSG_BRLNOZZLEADJUST_NOTSET,   QT_TRANSLATE_NOOP("custom", "Spritzeinheitabgleich wurde nicht korrekt beendet")},

   {GUIMSG_FILE_NOT_FOUND,           QT_TRANSLATE_NOOP("custom", "Datei #1 fehlt")},
  
   {GUIMSG_SELECTMOLDCAVITY_NOTSET,  QT_TRANSLATE_NOOP("custom", "Werkzeuginnendruck Einspritzstufenauswahl wurde nicht korrekt beendet")},
   {0, NULL}                                                                   
};

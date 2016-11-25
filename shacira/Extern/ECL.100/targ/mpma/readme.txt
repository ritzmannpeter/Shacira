
  Multiple Platform Make Architecture (MPMA)                    ______ /
-------------------------------------------------------------- /__ ___/  -----
                                                              /___/  /_____
                                                                 /_____
1. Voraussetzungen
------------------

Umgebungsvariable PROJECT_TOP zeigt auf folgende Verzeichnisstruktur:

 $(PROJECT_TOP)
  |
  +--bin
  |   |
  |   +--win32
  |
  +--lib
  |   |
  |   +--$(PLATFORM>
  |
  +--make
  |
  +--mods
      |
      +--lib_base
      |
      +--lib_dbi
      |
      +--lib_store
      |
      +--lib_tom


2. Wichtige Dateien
-------------------

make/env.mk
make/general.mk
make/$(PLATFORM).mk

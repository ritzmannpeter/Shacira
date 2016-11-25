/****************************************************************************
*
*
*         IQTBIT.H
*
*  HISTORY:
*     05.12.89 -SF-     Neue Struktur der Include-Files eingebaut
*     20.03.90 -TSchw-  HOST_BG_SWITCH eingefuehrt
*     17.12.90 -TSchw-  XERR_ROB_DOWNLOAD eingefuehrt
*     28.02.91 -TSchw-  HEATOPT - Bits eingefuehrt
*     18.07.91 -SF-     XERR_HOST_MSG_SEND eingebaut
*     19.11.91 -PR-     Ergaenzungen fuer das 10-Stufen-Spritzverfahren
*                       eingebaut: Bit XDEXPL
*     19.11.91 -SF-     XERR_HOST_xxx (Index 2417-2419) eingebaut
*     03.12.91 -TSchw-  XERR_POWER_FAIL (Index 2408) eingebaut
*     03.12.91 -TSchw-  Die Iqtbits WCLOCK_EXT1_SWITCH und WCLOCK_EXT2_
*                       SWITCH entfernt, da sie ab sofort Iqtregister
*                       sind
*     21.02.92 -PR-     HEATCHAN_ACTIVE (EWIKON) eingebaut
*     17.03.92 -PR-     HEATCHAN_ERR (EWIKON) eingebaut
*     14.10.92 -TSchw-  XERR_POWER_FAIL entfernt, MIQT 294
*     03.12.92 -TSchw-  WCLOCK_MOTOR_SWITCH und WCLOCK_HEAT_SWITCH
*                       entfernt, da nun als Register ausgefuehrt
*                       wegen Datentraeger und Hintergrund
*     17.02.94 -MBa-    Bit HOST_SSZ_MONITOR u. XMSTILL eingefuegt
*		11.09.96 -TSchw-  Bit TWO_PAGES neu erstellt
*		03.06.97 -TSchw-	IQT_SONBIT01 bis 20 eingefuegt zum Gebrauch
*                       durch Sonderprogramme
*     08.09.98 -HAns-   STATUS_PROC_STEP1 bis PROC_ERR_STATUS fuer
*                       Toleranzueberwachugn: Auswahl der Prozessschritte eingefuegt.
*     14.03.00 -HAns-   STATUS_PROC_STEP5,6 eingefuegt.
*	   03.05.00 -HAns-	BTCOUNTER_SET eingefuegt.
*     30.03.01 -TSchw-  Einige Bits für Kartenlesen angelegt, siehe MCARD_FOT.
*     26.03.02 -HA-     ICHG_CELCIUS_KELVIN und ICHG_BAR_PSI eingefuegt.
*     06.03.03 -HA-     ICHGHYDR_SPEZ eingefuegt.
*
****************************************************************************/

#ifndef _iqtbit
#define _iqtbit

/* ------------------------------------------------------------------------- *
 |  Definitons fuer die Register(Bit-)nummern der IQT-Bits                    |
 |  IQT-Bitnummern bewegen sich im Bereich zwischen 2000 und 2999            |
 |                                                                           |
 |  Wenn _USE_NOT_KLOECK_IQTBIT gesetzt ist, werden die von Kloeckner         |
 |  definierten Iqtbits nicht eingebunden.                                   |
 * ------------------------------------------------------------------------- */


#define  XQB500      2000
#define  XQB501      2001
#define  XQBKSA      2002
#define  XQB503      2003
#define  XQB504      2004
#define  XQBCARS     2005
#define  XQBCARL     2006
#define  XQB507      2007
#define  XQB508      2008
#define  XQB509      2009
#define  XQBCARN     2010
#define  XQB50B      2011
#define  XQBSPN1     2012
#define  XQBSPN2     2013
#define  XQBSPN3     2014
#define  XQBSPN4     2015
#define  XQBSPN5     2016
#define  XQBSPN6     2017
#define  XQBUMS1     2018
#define  XQBUMS2     2019
#define  XQBUMS3     2020
#define  XQBUMS4     2021
#define  XQBUMS5     2022
#define  XQBUMS6     2023
#define  XQB51F      2024
#define  XQB51C      2025
#define  XQB51D      2026
#define  XQB51E      2027
#define  XQBTX01     2028
#define  XQBTX02     2029
#define  XQBTX03     2030
#define  XQBTX04     2031
#define  XQBTX05     2032
#define  XQBTX06     2033
#define  XQBTX07     2034
#define  XQBTX08     2035
#define  XQBTX09     2036
#define  XQBTX10     2037
#define  XQBTX11     2038
#define  XQBTX12     2039
#define  XQBTX13     2040
#define  XQBTX14     2041
#define  XQBTX15     2042
#define  XQBTX16     2043
#define  XQBTX17     2044
#define  XQBTX18     2045
#define  XQBTX19     2046
#define  XQBTX20     2047
#define  XQBSTF3     2048
#define  XQBSTF4     2049
#define  XQBSTF5     2050
#define  XQBSTF6     2051
#define  XQBALRM     2052
#define  XQBT0SW     2053
#define  XQBSCSW     2054
#define  XQBMASW     2055
#define  XQBABSW     2056
#define  XBHZG1A     2057
#define  XBHZG2A     2058
#define  XBHZG3A     2059
#define  XBHZG4A     2060
#define  XBHZG5A     2061
#define  XBHZG6A     2062
#define  XBHZMAS     2063
#define  XQBASWF     2064
#define  XBHZGAS     2065
#define  XBHZ32A     2066
#define  XBHZ34A     2067
#define  XB35NR1     2068
#define  XB35NR2     2069
#define  XB35NR3     2070
#define  XB35NR4     2071
#define  XB35NR5     2072
#define  XB35NR6     2073
#define  XB35NR7     2074
#define  XB35NR8     2075
#define  XB35NR9     2076
#define  XB35NRA     2077
#define  XB35NRB     2078
#define  XB35NRC     2079
#define  XB35NRD     2080
#define  XB35NRE     2081
#define  XB35NRF     2082
#define  XB35NRG     2083
#define  XB35ST1     2084
#define  XB35ST2     2085
#define  XB35ST3     2086
#define  XB35ST4     2087
#define  XB35ST5     2088
#define  XB35ST6     2089
#define  XB35ST7     2090
#define  XB35ST8     2091
#define  XB35ST9     2092
#define  XB35STA     2093
#define  XB35STB     2094
#define  XB35STC     2095
#define  XB35STD     2096
#define  XB35STE     2097
#define  XB35STF     2098
#define  XB35STG     2099
#define  XBHZHT0     2100
#define  XBHZHT1     2101
#define  XBHZHT2     2102
#define  XBHZHT3     2103
#define  XBHZHT4     2104
#define  XBHZHT5     2105
#define  XBHZHT6     2106
#define  XBHZHT7     2107
#define  XBHZG1B     2108
#define  XBHZG2B     2109
#define  XBHZG3B     2110
#define  XBHZG4B     2111
#define  XBHZG5B     2112
#define  XBHZG6B     2113
#define  XBHZG7B     2114
#define  XBHZG8B     2115
#define  XBHZG8A     2116
#define  XBHZG7A     2117
#define  XBHZFTS     2118
#define  XBHZHTS     2119
#define  XBHZSNE     2120
#define  XBHZ32B     2121
#define  XBHZ32C     2122
#define  XBHZ32D     2123
#define  XBHZ32E     2124
#define  XBHZ32F     2125
#define  XBHZ32G     2126
#define  XBHZ32H     2127
#define  XBHZFT0     2128
#define  XBHZFT1     2129
#define  XBHZFT2     2130
#define  XBHZFT3     2131
#define  XBHZFT4     2132
#define  XBHZFT5     2133
#define  XBHZFT6     2134
#define  XBHZFT7     2135
#define  XBHZ34B     2136
#define  XBHZ34C     2137
#define  XBHZ34D     2138
#define  XBHZTRI     2139
#define  XQSTELR     2140
#define  XCDFSSW     2141
#define  XQBBDER     2142
#define  XQBSTO1     2143
#define  XQBSTO2     2144
#define  XQBSTO3     2145
#define  XQBSTO4     2146
#define  XQBSTO5     2147
#define  XQBSTO6     2148
#define  XQBSTO7     2149
#define  XQBSTO8     2150
#define  XQBSTO9     2151
#define  XQBSTOA     2152
#define  XQBL230     2153
#define  XQBL231     2154
#define  XQBL232     2155
#define  XQBL233     2156
#define  XQBL234     2157
#define  XQBL235     2158
#define  XQBL236     2159
#define  XQBL237     2160
#define  XQBL238     2161
#define  XQBL239     2162
#define  XQBL240     2163
#define  XQBL241     2164
#define  XQBL242     2165
#define  XQBL243     2166
#define  XQBL244     2167
#define  XQBSAM1     2168
#define  XQBSAM2     2169
#define  XQBSAM3     2170
#define  XQBSAM4     2171
#define  XQBSAM5     2172
#define  XQBST11     2173
#define  XQBST12     2174
#define  XQBST13     2175
#define  XQBST14     2176
#define  XQBST15     2177
#define  XQBST16     2178
#define  XQBST17     2179
#define  XQBST18     2180
#define  XQBST19     2181
#define  XQBST1A     2182
#define  XQBUM11     2183
#define  XQBUM12     2184
#define  XQBUM13     2185
#define  XQBUM14     2186
#define  XQBUM15     2187
#define  XQBWECO     2188
#define  XQBCAR1     2189
#define  XQBCAR2     2190
#define  XQBCAR3     2191
#define  XQBCAR4     2192
#define  XQBCAR5     2193
#define  XQBCAR6     2194
#define  XQBCAR7     2195
#define  XQBCAR8     2196
#define  XQBCAR9     2197
#define  XQBCARA     2198
#define  XQBCARB     2199
#define  XQBCARC     2200
#define  XQBZON1     2201
#define  XQBZON2     2202
#define  XQBZON3     2203
#define  XQBZON4     2204
#define  XQBZON5     2205
#define  XQBZON6     2206
#define  XQBZON7     2207
#define  XQBHOST     2208
#define  XQBGRAF     2209
#define  XQGRF0      2210
#define  XQGRF1      2211
#define  XQGRF2      2212
#define  XQGRF3      2213
#define  XQGRF4      2214
#define  XQGRF5      2215
#define  XQGRF6      2216
#define  XQGRF7      2217
#define  XQGRF8      2218
#define  XQGRF9      2219
#define  XQGRFA      2220
#define  XQGRFB      2221
#define  XQGRFC      2222
#define  XQGRFD      2223
#define  XQGRFE      2224
#define  XQGRFF      2225
#define  XQBGRAR     2226
#define  XQBN555     2227
#define  XQBN549     2228
#define  XQBN542     2229
#define  XQB476      2230
#define  XQB549      2231
#define  XQBDTCA     2232
#define  XQ1DTCA     2233
#define  XQ2DTCA     2234
#define  XQ3DTCA     2235
#define  XQBDTCE     2236
#define  XQ1DTCE     2237
#define  XQ2DTCE     2238
#define  XQ3DTCE     2239
#define  XQBIPF      2240
#define  XQ1BIPF     2241
#define  XQ2BIPF     2242
#define  XQ3BIPF     2243
#define  XQBIPE      2244
#define  XQ1BIPE     2245
#define  XQ2BIPE     2246
#define  XQ3BIPE     2247
#define  XQBIHT      2248
#define  XQ1BIHT     2249
#define  XQ2BIHT     2250
#define  XQ3BIHT     2251
#define  XQBIFW      2252
#define  XQ1BIFW     2253
#define  XQ2BIFW     2254
#define  XQ3BIFW     2255
#define  XBX618      2256
#define  XBX619      2257
#define  XBX61A      2258
#define  XBX61B      2259
#define  XBX61C      2260
#define  XBX61D      2261
#define  XBX61E      2262
#define  XBX61F      2263
#define  XFSTOL2     2264
#define  XFTTOL2     2265
#define  XFPTOL2     2266
#define  XFKTOL2     2267
#define  XFSTOL1     2268
#define  XFTTOL1     2269
#define  XFPTOL1     2270
#define  XFKTOL1     2271
#define  XFXTOLU     2272
#define  XFXTOLO     2273
#define  XFTOL11     2274
#define  XFTOL12     2275
#define  XFTOL13     2276
#define  XFTOL14     2277
#define  XFTOL15     2278
#define  XFTOL16     2279

#define STATUS_PROC_STEP1     2300     /* Ausschu~status, Proze~schritt 1 */
#define STATUS_PROC_STEP2     2301     /* Ausschu~status, Proze~schritt 2 */
#define STATUS_PROC_STEP3     2302     /* Ausschu~status, Proze~schritt 3 */
#define STATUS_PROC_STEP4     2303     /* Ausschu~status, Proze~schritt 4 */
#define PROC_ERR_STATUS       2304     /* Ausschu~status, Proze~auswertung */
#define STATUS_PROC_STEP5     2305     /* Ausschu~status, Proze~schritt 5 */
#define STATUS_PROC_STEP6     2306     /* Ausschu~status, Proze~schritt 6 */
#define BTCOUNTER_SET         2307     /* Betriebsstundenzaehler setzen */
#define ICHG_BAR_PSI          2308     /* Darstellung bar/psi */
#define ICHG_CELCIUS_KELVIN   2309     /* Darstellung Celcius/Kelvin */

/* Von 2i kreierte IQT-Bits */
#define XERR_NOTINTOL         2400     /* Fehlermeldung Toleranzueberwachung  */
#define XERR_GRAPH_NOTINTOL   2401     /* Fehlermeldung Toleranzueberwachung  */
#define XERR_WORK_NOTINTOL    2402     /* Fehlermeldung Toleranzueberwachung  */
#define HEAT_TOL_BIT          2403     /* S.30: Toleranzanzeige switchen     */
#define FGBG_BIT              2404     /* Vergleich Vorder-/Hintergrunddaten */
#define XERR_HOST_INIT        2405     /* Fehlermeldung Host-Initialisierung */

#define PG_CURSOR_SELECT      2406     /* 0=Cursor1 links, 1=Cursor2 rechts  */
#define XERR_HOST_MSG_SEND    2407     /* Meldung wurde von Host gesendet    */

#define WCLOCK_SWITCH         2410     /* Wochentagsschaltuhr ein/ausschalten*/

#define XERR_HOST_UD_START    2417     /* Upload von HOST angefordert */
#define XERR_HOST_DD_START    2418     /* Download von HOST angefordert */
#define XERR_HOST_TRANSM_ERR  2419     /* Fehler bei der Datenuebertragung */
#define HOST_BG_SWITCH        2420     /* 0: Host schreibt auf Vordergrund   */
                                       /* 1: Host schreibt auf Hintergrund   */
#define SN_CHANGE             2421     /* Schneckenwechsel aus=0, ein=1      */
#define PRINT_CYC_TIME        2422     /* Zykluszeit unterdr. nein=0, ja=1   */
#define XERR_XNSUB_ZERO       2423     /* Fehlermeldung: Sub.Schusszaehler=0 */
#define IQT_DUMMY_BIT         2424     /* Dummybit fuer alle Gelegenheiten   */
#define XERR_ROB_DOWNLOAD     2425     /* Fehlermeldung: Roboter-Download    */
#define HEATOPT_SWITCH        2426     /* Schaltet Optimierung ein/aus       */
#define HEATOPT_REGLER_ONOFF  2427     /* Schaltet aktuellen Regler ein/aus  */
#define NUL_BIT               2428     /* Dummy-Bit, wird nie gelesen        */


#define HEATCHAN_ACTIVE       2430     /* EWIKON-Heisskanaele aktiv */
#define HEATCHAN_ERR          2431     /* Fehler EWIKON Heisskanaele */
#define  HOST_SSZ_MONITOR     2432	   /* subt. Schussz. ueberwachen  */ 
#define  XMSTILL              2433	   /* 0= Stillstand 1= Produktion */ 
#define  TWO_PAGES				2434		/* 1= zwei Iqtseiten pro Druckseite */

/*BEGIN_MODE_10*/
#define  XDEXPL               2504
/*END_MODE_10*/

/* START MCARD_FOT */
#define  CARD_STORE_FOTPAGE1  2510     /* Frei konfigurierbare Seite 1, 2, 3 */
#define  CARD_STORE_FOTPAGE2  2511     /* auf Chipkarte speichern, wenn True */
#define  CARD_STORE_FOTPAGE3  2512
#define  CARD_READ_FOTPAGE1   2513     /* Frei konfigurierbare Seite 1, 2, 3 */
#define  CARD_READ_FOTPAGE2   2514     /* wurde von Chipkarte gelesen, wenn  */
#define  CARD_READ_FOTPAGE3   2515     /* True.                              */
/* END MCARD_FOT */

#define ICHGHYDR_SPEZ         2516     /* Darstellung Hydr./Spez. */

/* Sonderbits fuer Sonderprogramme: */
#define IQT_SONBIT01          2600
#define IQT_SONBIT02          2601
#define IQT_SONBIT03          2602
#define IQT_SONBIT04          2603
#define IQT_SONBIT05          2604
#define IQT_SONBIT06          2605
#define IQT_SONBIT07          2606
#define IQT_SONBIT08          2607
#define IQT_SONBIT09          2608
#define IQT_SONBIT10          2609
#define IQT_SONBIT11          2610
#define IQT_SONBIT12          2611
#define IQT_SONBIT13          2612
#define IQT_SONBIT14          2613
#define IQT_SONBIT15          2614
#define IQT_SONBIT16          2615
#define IQT_SONBIT17          2616
#define IQT_SONBIT18          2617
#define IQT_SONBIT19          2618
#define IQT_SONBIT20          2619

#endif      /* _iqtbit */

# gazefis_display
The display part of the GAZEFIS project, open source EFIS for homebuilt aircrafts (initial version for GAZAILE).

Partie display du projet GAZEFIS D'EFIS open source, basé sur écran industrial 4D Systems.

The display is based on 4D Systems [70D-SB](https://4dsystems.com.au/products/4d-intelligent-hmi-display-modules/gen4-ulcd-70d-sb) (super bright) from [4D Systems](https://4dsystems.com.au).

## Inputs

The display reads frames from the COM0 / COM1 ports. Trames sur COM0 / COM1.

###Frame format (ASCII 8bits, 38400bps):
```
:SPEED,ALTITUDE_1013,QNH,PITCH,ROLL,GMETER,SLIP,HEADING,HEADING_BUG,TRIMV,TRUMH,FLAPS,AP,CHRONO,EDITZONE,EDITFLAG,RPM,OIL P,WATER_OR_CHT,OIL_T,EGT,FUEL P,FUEL,AMPS,VOLTS,EFIS_VOLTS,TEMP_EXT,CRLF
```

Separator SPACE , ; TAB
Multiple separators are allowed (e.g./ SPACE & ,), only one will be taken into account. Use 999 for EGT/CHT not used. WARNING: no decimal sign!
Si plusieurs séparateurs, seul 1 est utilisé (les valeurs non utilisées doivent être remplies). Attention pas de séparateur décimal!

Where:
```
    // SSSS Speed in 1/10 kts or Km/h
    // AAAAA Altitude = feets
    // QNH mbar
    // PPP Pich in 1/10 Deg
    // RRRR Roll in 1/10 Deg
    // GGG G=meter in 1/100 G
    // LLL Slip in 1/10 G
    // HHH Heading in Deg
    // BUG Heading bug in Deg
    // TRIMV +- 50
    // TRIMH +- 50
    // FLAPS +50 -5
    // AP (0: OFF, 1: LEVEL, 2: Heading, 3:Altitude hold)
    // CHRONO (0:OFF, 1:START, 2:FLYBACK, 3:STOP
    // EDITZONE Edit zone: ZONEDI 1 , ZONEAP 2 , ZONEBUG 3 , ZONEQNH 4 , ZONETIME 5  , ZONENONE 0
    // EDITFLAG 0/1 (1 if in edit mide / zone blinking)
    // RPM Engine rpm /10 (400 for 4000)
    // OIL P in mbar  /10 (400 for 4 Bars)
    // WAT Temp water in deg (or CHT Rotax)
    // TOI Oil temp in Deg
    // EGT EGT in °C /10
    // FUEP Fuelpressure in mbar
    // FUE Fuel in liter
    // AAA Amprs in 1/10 Amp
    // VVV Volts in 1/10 volts
    // BAK Backup voltage 1/10 volts
    // EXT Ext temp in 1/10 Deg

    // EG2, EG3, EG4 EGT 2/3/4 in Deg/10 (optional, use 999 if nor used)
    // CH1 CH2 CH3 CH4 CHTs in deg/10 (optional, use 999 if not used)

```

Example
```
:1404,10000,1028,40,-100,11,1,300,342,-10,5,-4,2,0,1,0,550,400,90,98,49,310,70,100,137,72,120CRLF

140,4 Knots
10000ft / 1013
QNH 1028
PITCH 4° UP
ROLL 10° LEFT
GMeter 1,1G
0,1G Right Slip
Heading 300
Heading bug 342
TRIM V -10°
TRIM H 5° R
FLAPS -4°
AP HDG
CHRONO OFF
EDITZONE DI (Recalage Heading)
EDITFLAG OFF (Pas en édition, ne clignote pas)
RPM 5500
Oil pressure 4000 mbars
WATER 90°C
OIL TEMP 98°C
EGT 490°C
Fuel Pressure 310 mbars
Fuel 70 liters
Amp 10.0 A load
Volts 13.8V
Volts backup battery EFIS 7.2V
Ext temperateure 12°C


## Outputs
There is no output.

# gazefis_display
The display part of the GAZEFIS project, open source EFIS for homebuilt aircrafts (initial version for GAZAILE).

Partie display du projet GAZEFIS D'EFIS open source, basé sur écran industrial 4D Systems.

The display is based on 4D Systems [70D-SB](https://4dsystems.com.au/products/4d-intelligent-hmi-display-modules/gen4-ulcd-70d-sb) (super bright) from [4D Systems](https://4dsystems.com.au).

## Inputs

The display reads frames from the COM0 / COM1 ports. Trames sur COM0 / COM1.

###Frame format (fixed lenght, ASCII 8bits, 38400bps):
```
:SPEED,ALTITUDE_1013,QNH,PITCH,ROLL,GMETER,SLIP,HEADING,RPM,EGT,
WATER,TURBO,OILTEMP,OILPRESSURE,FUEL,AMPS,VOLTS,BAK,TEXT,CRLF
```

Separator SPACE , ; TAB
Multiple separators are allowed (e.g./ SPACE & ,), only one will be taken into account. Use 999 for EGT/CHT not used.
Si plusisurs séparateurs, seul 1 est utilisé (les valeurs non utilisées doivent être remplies)

Where:
```
    // SPEED Speed in 1/10 kts or Km/h
    // ALTITUDE_1013 Flight level in feets (.;g.: 9500)
    // FLIGHT_LEVEL Flight level = feets (1013)
    // QNH QNH mbar
    // PITCH Pitch in 1/10 Deg (positive climbing). 
    // RRRR Roll in 1/10 Deg (positive turn right)
    // GMETER G=meter in 1/100 G
    // SLIP Slip in 1/10 G
    // HEADING Heading in Deg
    // RPM Engine rpm /10 (400 for 4000)
    // EGT in Deg / 10 (70 for 700)
    // WATER Temp water in deg
    // TURBO Turbo pressure in mbar / 10 (180 for 1800 mbar)
    // OILTEMP Oil temp in Deg
    // OILPRESSURE Oil pressure in mbar / 10
    // FUEL Fuel in liter
    // AMPS Amprs in 1/10 Amp
    // VOLTS Volts in 1/10 volts
    // BAK Backup voltage 1/10 volts
    // TEXT Ext temp in 1/10 Deg
    // CR Carriage return
    // LF Line feed
```

Example
```
:125,10000,1028,40,-200,110,1,300,432,70,93,180,110,200,35,100,138,72,12CRLF

125 Knots
10000ft / 1013
QNH 1028
PITCH 4° UP
ROLL 10° LEFT
GMeter 1,1G
0,1G Right Slip
Heading 300°C
RPM 4320
EGT 700°C
Temp Eau 93°C
Turbo 1800 mbars
Oil Temp 110°C
Oil pressure 2000 mbars
Fuel 35 Liters
Amp 10.0 A load
Volts 13.8V
Volts backup battery EFIS 7.2V
Ext temperateure 12°C


## Outputs
There is no output. Future versions will return Heading, QNH and 

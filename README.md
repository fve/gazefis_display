# gazefis_display
The display part of the GAZEFIS project, open source EFIS for homebuilt aircrafts (initial version for GAZAILE)

The display is based on 4D Systems [70D-SB](https://4dsystems.com.au/products/4d-intelligent-hmi-display-modules/gen4-ulcd-70d-sb) (super bright) from [4D Systems](https://4dsystems.com.au).

## Inputs

The display reads frames from the COM0 / COM1 ports

###Frame format (fixed lenght, ASCII 8bits, 38400bps):

:SSSSAAAAAPPPRRRRGGGLLLHHHRPMEGTWATTURTOIPOIFUEAAAVVVBAKEXTEG2EG3EG4CH1CH2CH3CH4CRLF

Where:
```
    // SSSS Speed in 1/10 kts or Km/h
    // AAAAA Altitude = feets
    // PPP Pitch in 1/10 Deg
    // RRRR Roll in 1/10 Deg
    // GGG G=meter in 1/100 G
    // LLL Slip in 1/10 G
    // HHH Headinf in Deg
    // RPM Engine rpm /10 (400 for 4000)
    // EGT in Deg / 10 (70 for 700)
    // WAT Temp water in deg
    // TUR Turbo pressure in mbar / 10 (180 for 1800 mbar)
    // TOI Oil temp in Deg
    // POI Oil pressure in mbar / 10
    // FUE Fuel in liter
    // AAA Amprs in 1/10 Amp
    // VVV Volts in 1/10 volts
    // BAK Backup voltage 1/10 volts
    // EXT Ext temp in 1/10 Deg
    // EG2, EG3, EG4 EGT 2/3/4 in Deg/10 (optional, use 999 if nor used)
    // CH1 CH2 CH3 CH4 CHTs in deg/10 (optional, use 999 if not used)
    // CR Carriage return
    // LF Line feed
```

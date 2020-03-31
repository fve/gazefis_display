
var comBuffer0[1024] ;
var comBuffer1[1024] ;


// var line0[101] ;
var lineCpt0, lineCpt1 ;
var line1[101] ;
var currentLine ;
var *lineCpt ;  // Points to the last retrieved line Buffer
var *line ;     // Last counter when readOneSerialLine returns OK
var strBuff0[20];
var strPtr0 ;
var isEmpty0 ;
var lineFieldCpt ;


func initSerial()
    setbaud(BAUD_38400) ;
    cleanReadBuffer() ;
    initLine() ;
endfunc

func initLine()
     com_Init(comBuffer0,300,':');
     lineFieldCpt := 0 ;
endfunc

func cleanReadBuffer()
    lineCpt0 := 0;
    mem_Set(strBuff0, 0, 40);
    strPtr0 := str_Ptr(strBuff0);
    isEmpty0 := TRUE ;
endfunc

//Reads one line from serial 0
// Returns 1 if line is ready
// Line is stored in line0[] buffer
func readLine0()

var char; // last char read from line
var ok; // > 1 if somethong to display
var value; // value parsed
var cpt ; // rank of value in the message
var initRequested ; // call for line reinit

ok := 2 ;

    while ( ok == 2 )
        initRequested := FALSE ;
        char := serin() ;

        switch (char)
            case -1: // Nothing to read
                if ( com_Full() )
                    // putchXY(0,360, 'F') ;
                    cleanReadBuffer() ;
                    com_Init(comBuffer0,200,':');
                endif
                ok := 0 ; // Nothing to read
            break ;

            case -2: // Framing / Overrun
            putchXY(0,360, 'O') ;
            case -3: // Break
                // putchXY(0,360, 'E') ;
                cleanReadBuffer() ;
                com_Init(comBuffer0,200,':');
                ok := 0 ; // Nothing to read
            break ;

            case 0x0A: // LF Ignored
                ok := 0 ;
            break ;

            case 0x0D: // CR: validate message
                initRequested := TRUE ;
                // putchXY(0,360, 'C') ;
                if ( !isEmpty0 )
                    ok := 1 ;
                endif

            case ',' : // Separator
            case ' ' : // Separator
            case ';' : // Separator
            case ':' : // Initial separator
            case 0x09: // Tab separator
                if ( !isEmpty0 )
                    // putchXY(0,360, ',') ;

                    // Put end of string at end of work string
                    // char := 0;
                    str_PutByte(strPtr0 + lineCpt0++, ' ');
                    str_PutByte(strPtr0 + lineCpt0++, 0);
                    // Parse content as Integer
                    if ( str_GetW(&strPtr0, &value) )
                        // Feed the appropriate display variable
                        dispatch(lineFieldCpt, value) ;
                    endif
                    lineFieldCpt++ ;
                    // Clean string for next pass
                    cleanReadBuffer() ;
                endif
            break ;

            default:
                // putchXY(0,360, char) ;
                isEmpty0 := FALSE ;
                str_PutByte(strPtr0 + lineCpt0++, char);


                if ( lineCpt0 > 190 )
                    // Buffer full before LF, remove the line
                    lineCpt0 := 0 ;
                endif
                ok := 0 ;
            break; // optional break endswitch
        endswitch
    wend

    if ( initRequested )
        cleanReadBuffer();
        // com_Init(comBuffer0,300,':');
        initLine() ;
    endif

    return ok ;

endfunc



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


func dispatch(var cpt, var value)
    switch (cpt)
        case 0: speed := value;  break ;
        case 1: altitude := value;  break ;
        case 2: qnh := value;  break ;
        case 3: pitch := value;  break ;
        case 4: roll := value;  break ;
        case 5: gMeter := value;  break ;
        case 6: slip := value;  break ;
        case 7: heading := value;  break ;
        case 8: bug := value;  break ;
        case 9: trimV := value;  break ;
        case 10: trimH := value;  break ;
        case 11: flaps := value;  break ;
        case 12: apMode := value;  break ;
        case 13: chrono := value;  break ;
        case 14: editZone := value;  break ;
        case 15: editFlag := value;  break ;


        default:
            if ( cpt > 15 && cpt < 27 )
                 gaugesValues[cpt-16] := value;
            endif
        break ;
    endswitch

endfunc

//Reads one line from serial 1
// Returns 1 if line is ready
// Line is stored in line1[] buffer
func readLine1()

var char;
var ok ;

ok := 2 ;

    while ( ok == 2 )
        char := serin1() ;
        switch (char)
            case -1: // Nothing to read
                if ( com1_Full() )
                    com1_Init(comBuffer1,1024,0x00);
                endif
                ok := 0 ; // Nothing to read
            break ;

            case -2: // Framing / Overrun
            case -3: // Break
                lineCpt1 := 0 ;
                com1_Init(comBuffer1,1024,0x00);
                ok := 0  ; // Nothing to read
            break ;

            case 0x0D: // CR Ignored
                 ok := 2 ;
            break;

            case 0x0A: // LF: end of line
                  line1[lineCpt1] := 0x00 ;
                  ok := 1 ; // We have a line
            break;

            default:
                line1[lineCpt1] := char ;
                lineCpt1++ ;
                if ( lineCpt1 > 100 )
                    // Buffer full before LF, remove the line
                    lineCpt1 := 0 ;
                endif
                ok := 0 ;
            break; // optional break endswitch
        endswitch
    wend

    return ok ;

endfunc

func initComs()
    currentLine := 1 ;
    lineCpt0 := 0 ;
    lineCpt1 := 0 ;

    com_Init(comBuffer0,1024,0x00);
    com1_Init(comBuffer1,1024,0x00);
endfunc

func readOneSerialLine()

    var ok ;

    // currentLine := (currentLine + 1) % 2 ;
    currentLine := 0 ;

    switch ( currentLine )
        case 0:
            ok := readLine0() ;
            break ;
        case 1:
            ok := readLine1() ;
            break ;
        default:
            ok := 0 ;
    endswitch

    if ( ok > 0 )
        // putstrXY(0,460, line) ;  // line
        return 1 ;
    else
        return 0 ;
    endif
endfunc


func displayGaugeFrames()
    var i;
    // _*+/-[]
    // gfx_CircleFilled(X+67, Y+67, 65, LIME);
    for ( i := 0; i < 6 ; i++ )
        gfx_PieSlice(gaugeX[i], gaugeY[i], 0, 65, 1, 90, 315, 0, gaugeThirdColor[i]);
        gfx_PieSlice(gaugeX[i], gaugeY[i], 0, 65, 1, 90, gaugeSecondColorLastValue[i], 0, gaugeSecondColor[i]);
        gfx_PieSlice(gaugeX[i], gaugeY[i], 0, 65, 1, 90, gaugeFirstColorLastValue[i] , 0, gaugeFirstColor[i]) ; // AZURE);

        // gfx_PieSlice(X+67, Y+67, 0, 65, 1, 270, 315, 0, RED);
        gfx_CircleFilled(gaugeX[i], gaugeY[i], 59, BLACK);


        if ( addZero[i] > 0 )
            displayGaugeDigit( gaugeX[i]+28, gaugeY[i]-22, 0) ;
        endif
        if ( addDot[i] > 0 )
            gfx_RectangleFilled(gaugeX[i]+26, gaugeY[i]-2, gaugeX[i]+28, gaugeY[i],WHITE) ;
        endif
    next

    // FUEL
    // gfx_Rectangle(gaugeX[6],gaugeY[6]-3,gaugeX[6]+15,gaugeY[6]-326,LIGHTSTEELBLUE) ;
    gfx_Gradient(GRAD_DOWN, gaugeX[6], gaugeY[6]-326+164, gaugeX[6], gaugeY[6]-3, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  gaugeX[6], gaugeY[6]-326, gaugeX[6], gaugeY[6]-326+164, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_DOWN, gaugeX[6]+15, gaugeY[6]-326+164, gaugeX[6]+15, gaugeY[6]-3, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  gaugeX[6]+15, gaugeY[6]-326, gaugeX[6]+15, gaugeY[6]-326+164, GRADIENTHIGH, GRADIENTLOW);


    for ( i := 0; i < gaugeFirstColorLastValue[6] ; i++ )
        displayFuelSegment(6, i, 0) ;
    next

    // Digital gauges
    // gfx_Rectangle(504,430,800,480,LIGHTSTEELBLUE) ;  // 504
    for ( i := 7; i < 10 ; i++ )
        if ( addDot[i] )
            gfx_RectangleFilled(gaugeX[i]+32, gaugeY[i]+20, gaugeX[i]+34, gaugeY[i]+18,WHITE) ;
        endif
    next

    gaugeTexts() ;
    // Decimal point of voltage
    // gfx_RectangleFilled(gaugeX[8]+15, gaugeY[8]+126, gaugeX[8]+16,  gaugeY[8]+127, WHITE) ;
    // DSet & display initial state
    for ( i := 0; i < 11 ; i++ )
         gaugesValues[i] := (gaugeMin[i] + gaugeMax[i]) / 2 ;
         // gaugesValues[i] := gaugeMin[i] ;
    next
    // gfx_Rectangle(740,0,740,479,WHITESMOKE) ;
    displayGauges() ;
endfunc

func displayGauges()
    var i ;

    for ( i := 0; i < 6 ; i++ )
        // Display numbers and round gauges
        if ( addZero[i] > 0 )
            displayRoundGauge(i, gaugesValues[i]) ;
            displayGaugeNumbers(gaugeX[i]-23, gaugeY[i]-22, i, gaugesValues[i]) ;
        else
            displayRoundGauge(i, gaugesValues[i]) ;
            displayGaugeNumbers(gaugeX[i]-6, gaugeY[i]-22, i, gaugesValues[i]) ;
        endif
        displayAlert(gaugeX[i]+22, gaugeY[i]+54, i) ;
    next

    displayFuelBarGauge(gaugesValues[6]) ;
    displayAlert(gaugeX[6]+7, gaugeY[6]+83, 6) ;

    for ( i := 7; i < 10 ; i++ )
        // Display numbers and round gauges
        displayGaugeNumbers(gaugeX[i], gaugeY[i], i, gaugesValues[i]) ;
    next
    displayAlert(gaugeX[8]-33, gaugeY[8]+11, 8) ;


endfunc

func displayRoundGauge(var gaugeIndex, var value)
    var digits[3] ;
    var angleTmpMul[2] ;
    var angleTmpDiv[2] ;
    var maxMinusMin[2] ;
    var angle ;

    maxMinusMin[1] := 0 ;


    // Calculate angle
    umul_1616(angleTmpMul,gaugesValues[gaugeIndex]-gaugeMin[gaugeIndex], GAUGEANGLE);
    maxMinusMin[0] := gaugeMax[gaugeIndex]-gaugeMin[gaugeIndex] ;
    udiv_3232(angleTmpDiv, angleTmpMul, maxMinusMin);
    angle :=  angleTmpDiv[0] + 90 ;
    if ( angle != prevValues[prevDigit3[gaugeIndex]] )
        // Remove indicator
        if ( prevValues[prevDigit3[gaugeIndex]] >= 0 )
            gfx_PieSlice(gaugeX[gaugeIndex], gaugeY[gaugeIndex], 41, 18, 1, prevValues[prevDigit3[gaugeIndex]], prevValues[prevDigit3[gaugeIndex]], 0, BLACK);
        endif
        // Display indicator
        gfx_PieSlice(gaugeX[gaugeIndex], gaugeY[gaugeIndex], 41, 18, 1, angle, angle, 0, AQUA);
        prevValues[prevDigit3[gaugeIndex]] := angle ;
    endif

endfunc

func displaySmallGaugeNumbers(var X, var Y, var gaugeIndex, var value, var format)
     if ( value != prevValues[prevDigit0[gaugeIndex]] )
        txt_Set(FONT_ID,7) ;
        txt_Set(TEXT_COLOUR, WHITE) ;
        putnumXY(X,Y,format,value) ;
        prevValues[prevDigit0[gaugeIndex]] := value ;
    endif

endfunc

func displayGaugeNumbers(var X, var Y, var gaugeIndex, var value)
     var digits[3] ;

     digits[0] := value % 10 ;
    digits[1] := (value / 10) % 10 ;
    digits[2] := (value / 100) ;

    if ( digits[2] == 0 )
        digits[2] := -1 ;
    endif

    if ( digits[2] != prevValues[prevDigit2[gaugeIndex]] )
        displayGaugeDigit( X, Y, digits[2]) ;
        prevValues[prevDigit2[gaugeIndex]] := digits[2] ;
    endif

    if ( digits[1] != prevValues[prevDigit1[gaugeIndex]] )
        displayGaugeDigit( X+17, Y, digits[1]) ;
        prevValues[prevDigit1[gaugeIndex]] := digits[1] ;
    endif

    if ( digits[0] != prevValues[prevDigit0[gaugeIndex]] )
        displayGaugeDigit( X+34, Y, digits[0]) ;
        prevValues[prevDigit0[gaugeIndex]] := digits[0] ;
    endif

endfunc


func displayFuelSegment(var gaugeIndex, var value, var isOn)
    var offsetY ;
    var color ;

    if ( value < gaugeSecondColorLastValue[gaugeIndex] )
        if ( isOn == 1 )
            color := gaugeFirstColor[gaugeIndex] ;
        else
             color := gaugeSecondColor[gaugeIndex] ;
        endif
    else
        if ( isOn == 1 )
            color := gaugeThirdColor[gaugeIndex] ;
        else
             color := BLACK ;
        endif
    endif
    offsetY :=  gaugeY[gaugeIndex]-5-((3+1)*value) ;
    gfx_RectangleFilled(gaugeX[gaugeIndex]+2,offsetY,gaugeX[gaugeIndex]+13,offsetY-3+1,color) ;
endfunc

func displayFuelBarGauge(var value)
    var gaugeIndex ;
    var i ;

    gaugeIndex := 6 ; // Fixed position of Fuel Bar Gauge
    if ( prevValues[PREVFUEL] < 0  )
         prevValues[PREVFUEL] := 0 ;
    endif
    if ( value != prevValues[PREVFUEL] )
        if ( value > prevValues[PREVFUEL] )
            for ( i := prevValues[PREVFUEL]; i < value ; i++ )
                // Light ON new segments
                displayFuelSegment(gaugeIndex, i, 1) ;
            next
        else
             for ( i := value; i < prevValues[PREVFUEL] ; i++ )
                // Light OFF new segments
                displayFuelSegment(gaugeIndex, i, 0) ;
            next
        endif

        displayGaugeNumbers(gaugeX[gaugeIndex]-25, gaugeY[gaugeIndex]+7,gaugeIndex, value) ;
        prevValues[PREVFUEL] := value ;
    endif

endfunc



func displayAlert(var X, var Y, var gaugeIndex)
    var alert ;

    if ( gaugeAlert[gaugeIndex] == 0 )
        // putstrXY(700,360+(16*gaugeIndex),"no index") ;
        // No alert to manage
        return ;
    endif

    if ( gaugeAlert[gaugeIndex] > 0 )
        alert := gaugesValues[gaugeIndex] - gaugeAlert[gaugeIndex] ;
    else
        alert := ABS(gaugeAlert[gaugeIndex]) - gaugesValues[gaugeIndex] ;
    endif


    if ( alert != prevValues[prevAlert[gaugeIndex]] )
        prevValues[prevAlert[gaugeIndex]] := alert ;
        if ( alert > 0 )
            // gfx_CircleFilled(X, Y, 9, RED);
        else
            gfx_CircleFilled(X, Y, 9, DARKSLATEGRAY);
            // Stop flashing
            return ;
        endif
    else
        // gfx_RectangleFilled(X, Y, X+19, Y+9,VIOLET) ;
    endif

    if ( (prevValues[prevAlert[gaugeIndex]] > 0) && (onOffState != alertStates[gaugeIndex]) )
        // Flash when alert is on
        if ( onOffState > 0 )
            gfx_CircleFilled(X, Y, 9, RED);
        else
            gfx_CircleFilled(X, Y, 9, DARKSLATEGRAY);
            // gfx_CircleFilled(X, Y, 9, BLACK);
        endif
        alertStates[gaugeIndex] := onOffState ;
    endif

endfunc

func displayGaugeDigit(var X, var Y, var value)
     displayDigit(X,Y,value) ;
endfunc

func gaugeTexts()
    txt_Set(FONT_ID,4) ;
    txt_Set(TEXT_COLOUR, LIGHTSTEELBLUE) ;
    putstrXY(gaugeX[0]+7,gaugeY[0]+9,"RPM") ;
    putstrXY(gaugeX[1]-17,gaugeY[1]+9,"OIL P") ;
    putstrXY(gaugeX[2]+7,gaugeY[2]+9,"WAT") ;
    putstrXY(gaugeX[3]-17,gaugeY[3]+9,"OIL T") ;
    putstrXY(gaugeX[4]+7,gaugeY[4]+9,"EGT") ;
    putstrXY(gaugeX[5]-29,gaugeY[5]+9,"FUEL P") ;

    putstrXY(gaugeX[6]-17,gaugeY[6]+38,"FUEL") ;

    putstrXY(gaugeX[7]+70,gaugeY[7]+26,"BUS") ;
    // putstrXY(gaugeX[7]-42,gaugeY[7]+3,"BAT.") ;


    txt_Set(FONT_ID,7) ;
    putstrXY(gaugeX[0]+11,gaugeY[0]+25,"min-1") ;
    putstrXY(gaugeX[1]+10,gaugeY[1]+25,"mbar") ;
    putstrXY(gaugeX[2]+2,gaugeY[2]+25,"deg. C") ;
    putstrXY(gaugeX[3]+0,gaugeY[3]+25,"deg. C") ;
    putstrXY(gaugeX[4]+0,gaugeY[4]+25,"deg. C") ;
    putstrXY(gaugeX[5]+10,gaugeY[5]+25,"mbar") ;

    putstrXY(gaugeX[6]-10,gaugeY[6]+54,"liters") ;

    putstrXY(gaugeX[7]+20,gaugeY[7]+24,"amp.") ;
    putstrXY(gaugeX[8]+15,gaugeY[8]+24,"volts") ;
    putstrXY(gaugeX[9]+2,gaugeY[9]+24,"backup") ;

endfunc

func sanitizeGauges()
    var i ;
     for ( i := 0; i <= 10 ; i++ )
        // Display numbers
        if ( gaugesValues[i] > gaugeMax[i] )
            gaugesValues[i] := gaugeMax[i] ;
        else
            if ( gaugesValues[i] < gaugeMin[i] )
                gaugesValues[i] := gaugeMin[i] ;
            endif
        endif
    next
endfunc

func displayNumericGaugesFrames()
    txt_Set(FONT_ID,4) ;
    txt_Set(TEXT_COLOUR, LIGHTSTEELBLUE) ;
    putstrXY(375,255,"QNH") ;
    putstrXY(8,255,"TIME") ;

    putstrXY(30,145,"KTS") ;
    gfx_RectangleFilled(330,145,380,169,BLACK) ;
    putstrXY(334,145,"FEET") ;

    gfx_Rectangle(372,273,438,297,LIGHTSTEELBLUE) ;

    displayGaugeDigit( 373, 275, 1) ;
    displayGaugeDigit( 390, 275, 0) ;
    displayGaugeDigit( 405, 275, 1) ;
    displayGaugeDigit( 420, 275, 3) ;

    // gfx_Rectangle(372,328,472,352,LIGHTSTEELBLUE) ;
    gfx_Rectangle(5,273,105,297,LIGHTSTEELBLUE) ;
    gfx_RectangleFilled(36,279,40,281,WHITE) ; gfx_RectangleFilled(36,289,40,291,WHITE) ;
    gfx_RectangleFilled(69,279,73,281,WHITE) ; gfx_RectangleFilled(69,289,73,291,WHITE) ;

    hours := -1 ; minutes := -1 ; seconds := -1 ;
endfunc



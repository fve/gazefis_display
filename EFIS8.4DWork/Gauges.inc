func displayGaugeFrames()
    var i;
    // _*+/-[]
    // gfx_CircleFilled(X+67, Y+67, 65, LIME);
    for ( i := 0; i < 4 ; i++ )
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
    for ( i := 4; i < 9 ; i++ )
        gfx_RectangleFilled(gaugeX[i]+0, gaugeY[i]+16, gaugeX[i]+5, gaugeY[i]+116, gaugeThirdColor[i]);
        gfx_RectangleFilled(gaugeX[i]+0, gaugeY[i]+16+gaugeSecondColorLastValue[i], gaugeX[i]+5, gaugeY[i]+116, gaugeSecondColor[i]);
        gfx_RectangleFilled(gaugeX[i]+0, gaugeY[i]+16+gaugeFirstColorLastValue[i], gaugeX[i]+5,  gaugeY[i]+116, gaugeFirstColor[i]) ;
    next
    gaugeTexts() ;
    // Decimal point of voltage
    gfx_RectangleFilled(gaugeX[8]+31, gaugeY[8]+133, gaugeX[8]+32,  gaugeY[8]+134, WHITE) ;
endfunc

func displayGauges()
    var i ;

    for ( i := 0; i < 4 ; i++ )
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

    for ( i := 4; i < 9 ; i++ )
        // Display numbers and linear gauges
        displayLinearGauge(i, gaugesValues[i]) ;
        displayAlert(gaugeX[i]+3, gaugeY[i]+131, i) ;
    next
    displaySmallGaugeNumbers(gaugeX[6]+16, gaugeY[6]+122, i, gaugesValues[6], DEC2Z) ;
    displaySmallGaugeNumbers(gaugeX[8]+16, gaugeY[8]+122, i, gaugesValues[8]/10, DEC2Z) ;
    displaySmallGaugeNumbers(gaugeX[8]+33, gaugeY[8]+122, i, gaugesValues[8]%10, DEC1Z) ;
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

func displayLinearGauge(var gaugeIndex, var value)
    var offsetTmpMul[2] ;
    var offsetTmpDiv[2] ;
    var maxMinusMin[2] ;
    var offset ;

    maxMinusMin[1] := 0 ;


    // Calculate indicator offset
    umul_1616(offsetTmpMul,gaugesValues[gaugeIndex]-gaugeMin[gaugeIndex], GAUGELEN);
    maxMinusMin[0] := gaugeMax[gaugeIndex]-gaugeMin[gaugeIndex] ;
    udiv_3232(offsetTmpDiv, offsetTmpMul, maxMinusMin);
    offset :=  16 + 100 - offsetTmpDiv[0] ;
    if ( offset != prevValues[prevDigit3[gaugeIndex]] )
        // Remove indicator
        if ( prevValues[prevDigit3[gaugeIndex]] >= 0 )
            gfx_RectangleFilled(gaugeX[gaugeIndex]+6, gaugeY[gaugeIndex]+prevValues[prevDigit3[gaugeIndex]] , gaugeX[gaugeIndex]+22, gaugeY[gaugeIndex]+prevValues[prevDigit3[gaugeIndex]], AQUA);
        endif
        // Display indicator
        gfx_RectangleFilled(gaugeX[gaugeIndex]+6, gaugeY[gaugeIndex]+offset , gaugeX[gaugeIndex]+22, gaugeY[gaugeIndex]+offset, AQUA);
        prevValues[prevDigit3[gaugeIndex]] := offset ;
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
            gfx_CircleFilled(X, Y, 9, DARKRED);
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
            gfx_CircleFilled(X, Y, 9, DARKRED);
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
    putstrXY(gaugeX[1]+8,gaugeY[1]+9,"EGT") ;
    putstrXY(gaugeX[2]-17,gaugeY[2]+9,"WATER") ;
    putstrXY(gaugeX[3]-17,gaugeY[3]+9,"TURBO") ;

    txt_Set(FONT_ID,7) ;
    putstrXY(gaugeX[0]+11,gaugeY[0]+25,"min-1") ;
    putstrXY(gaugeX[1]+0,gaugeY[1]+25,"deg. C") ;
    putstrXY(gaugeX[2]+2,gaugeY[2]+25,"deg. C") ;
    putstrXY(gaugeX[3]+10,gaugeY[3]+25,"mbar") ;

    putstrXY(gaugeX[4]-10,gaugeY[4]-5," T.") ;
    putstrXY(gaugeX[4]+15,gaugeY[4]-5,"OIL") ;
    putstrXY(gaugeX[5]-7,gaugeY[4]-5," P.") ;
    putstrXY(gaugeX[6]-10,gaugeY[6]-5,"Fuel") ;
    putstrXY(gaugeX[7]-10,gaugeY[7]-5,"Amp.") ;
    putstrXY(gaugeX[8]-10,gaugeY[8]-5,"Volts") ;
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



func displayTrimAndFlapsFrames()
    var i;
    var baseX,  baseY, baseXL, baseYL, baseXF, baseYF ;

    baseX := 462 ; baseY := 297 ;    // 462
    baseXL := baseX - 38 ; baseYL := baseY + 150 ;
    baseXF := 25 ; baseYF:= 302 ;

    gfx_Gradient(GRAD_DOWN, baseX, baseY-2+50, baseX, baseY+102, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  baseX, baseY-2, baseX, baseY-2+50, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_DOWN, baseX+13, baseY-2+50, baseX+13, baseY+102, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  baseX+13, baseY-2, baseX+13, baseY-2+50,GRADIENTHIGH, GRADIENTLOW);

    txt_Set(FONT_ID,7) ;
    txt_Set(TEXT_COLOUR, LIGHTSTEELBLUE) ;
    putstrXY(baseX-13,baseY-21,"DOWN") ;
    putstrXY(baseX-0,baseY+108,"UP") ;

    gfx_Gradient(GRAD_RIGHT, baseXL-6+50, baseYL, baseXL+98, baseYL, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_LEFT,  baseXL-6, baseYL, baseXL-6+50, baseYL, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_RIGHT, baseXL-6+50, baseYL+13, baseXL+98, baseYL+13, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_LEFT,  baseXL-6, baseYL+13, baseXL-6+50, baseYL+13, GRADIENTHIGH, GRADIENTLOW);

    putstrXY(baseXL-6,baseYL-18,"L") ;
    putstrXY(baseXL+89,baseYL-18,"R") ;

    txt_Set(FONT_ID,7) ;
    txt_Set(TEXT_COLOUR, LIGHTSTEELBLUE) ;
    putstrXY(baseX-12,baseYL+14,"TRIM") ; // =20

    gfx_Gradient(GRAD_DOWN, baseXF-1, baseYF+51, baseXF-1, baseY+101, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  baseXF-1, baseYF, baseXF-1, baseYF+50, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_DOWN, baseXF+13, baseYF+51, baseXF+13, baseY+101, GRADIENTHIGH, GRADIENTLOW);
    gfx_Gradient(GRAD_UP,  baseXF+13, baseYF, baseXF+13, baseYF+50, GRADIENTHIGH, GRADIENTLOW);

    txt_Set(FONT_ID,7) ;
    putstrXY(baseXF+14,baseYF-4, " cruise") ;
    putstrXY(baseXF+14,baseYF+27," 10°") ;
    putstrXY(baseXF-27,baseYF+36," 15°") ;
    putstrXY(baseXF+14,baseYF+53," 25°") ;
    putstrXY(baseXF-27,baseYF+71," 35°") ;
    putstrXY(baseXF+14,baseYF+85," 45") ;
    putstrXY(baseXF-12,baseYF-20,"FLAPS") ;
    txt_Set(TEXT_COLOUR, WHITE) ;
    putstrXY(baseXF+14,baseYF+10," neutral") ;



endfunc

func displayTrim()
    var baseY, baseXL, baseYL ;
    // trimH, trimV, flaps  ;
    baseY := 297 ;    // 462
    baseXL := 424 ; baseYL := baseY + 150 ;

    if ( prevTrimV != trimV )
        // Display new position
        gfx_Line(463, baseY+50+trimV, 474, baseY+50+trimV,AQUA) ;
        // Erase previous position
        if ( prevTrimV > -10000 )
            gfx_Line(463, baseY+50+prevTrimV, 474, baseY+50+prevTrimV,BLACK) ;
        endif
        prevTrimV := trimV ;
    endif

    if ( prevTrimH != trimH )
        // Display new position
        gfx_Line(baseXL-4+50+trimH, baseYL+1, baseXL-4+50+trimH, baseYL+12,AQUA) ;
        // Erase previous position
        if ( prevTrimH > -10000 )
            gfx_Line(baseXL-4+50+prevTrimH, baseYL+1, baseXL-4+50+prevTrimH, baseYL+12,BLACK) ;
        endif
        prevTrimH := trimH ;
    endif


endfunc

func displayFlaps()
    if ( prevFlaps != flaps )
        // Display new position
        displayFlapLine( flaps, AQUA) ;
        // Erase previous position
        if ( prevFlaps > -10000 )
            displayFlapLine(prevFlaps, BLACK) ;
        endif
        prevFlaps := flaps ;
    endif
endfunc


func displayFlapLine(var value, var color)
    var actualY ;

    if ( value < 0 )
        // Augment scale for negative flaps so that indicator is in front of "cruise"
        value := value * 2 ;
    endif
    actualY := 304+((value+10)*10/6 ) ;
    gfx_Line(25, actualY, 37, actualY,color) ;

endfunc



func sanitizeTrim()
    var i ;
    if ( trimH > 50 )
        trimH  := 50 ;
    endif
    if ( trimH < -50 )
        trimH  := -50 ;
    endif
    if ( trimV > 50 )
        trimV  := 50 ;
    endif
    if ( trimV < -50 )
        trimV  := -50 ;
    endif
    f ( flaps < -4 )
        flaps  := -4 ;
    endif
    if ( flaps > 50 )
        flaps  := 50 ;
    endif
endfunc


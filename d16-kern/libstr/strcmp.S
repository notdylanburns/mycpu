    !ifndef _LIBSTR_STRCMP_S_
    !define _LIBSTR_STRCMP_S_

strcmp_w: ; compares strings pointed to by %0 and %1, and sets the Z flag if they are equal
    
strcmp_w.loop:
    cmp *0 #0
    jsz strcmp.end

    cmp *1 #0
    jsz strcmp.end

    sbc *0 *1
    jnz strcmp.end

    inc %0
    inc %1

    jmp strcmp.loop

strcmp_w.end:
    ret

    !endif
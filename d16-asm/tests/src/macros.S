    !ifndef LIBRARY_INCLUDED
    !define LIBRARY_INCLUDED

    !org $0000

    !dw $4865                   ; H e
    !dw '0110110001101100       ; l l
    !dw 28416                   ; o

    !word $2c20                 ; ,  
    !word '0111011101101111     ; w o
    !word 29292                 ; r l

    !ddw $64210000              ; d !

    !str "hello"

    !define __SYMBOL
    !ifndef __SYMBOL

    !embed "/home/mk41/mycpu/d16-asm/test.S"

    !endif

    !bstr "\n\n\n"

    !endif
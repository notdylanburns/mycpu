    !org $0000

    !dw $4865                   ; H e
    !dw '0110110001101100       ; l l
    !dw 28416                   ; o

    !word $2c20                 ; ,  
    !word '0111011101101111     ; w o
    !word 29292                 ; r l

    !ddw $64210000              ; d !

redfine_me:
    !str "hello"
    
    !inc "/home/mk41/mycpu/d16-asm/test.S"
    !bstr "/home/mk41/mycpu/d16-asm/test.d16 hello balls fart deez"
start:
    mov %0 #0           ; program pointer
    mov %1 &program     ; instruction pointer

decode:
    cmp *1 #$00
    jsz end

    cmp *1 #$2B     ; +
    jsz plus 

    cmp *1 #$2C     ; ,
    jsz in 

    cmp *1 #$2D     ; -
    jsz minus 

    cmp *1 #$2B     ; .
    jsz out 

    cmp *1 #$3C     ; <
    jsz left 

    cmp *1 #$3E     ; >
    jsz right 

    cmp *1 #$5B     ; [
    jsz open_sq 

    cmp *1 #$5D     ; ]
    jsz close_sq

next:
    inc %1

plus:
    

in:

minus:

out:

left:

right:

open_sq:

close_sq:

end:
    hlt

program: !wstr "++>"
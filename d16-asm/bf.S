start:
    mov %0 &cells       ; program pointer
    mov %1 &program     ; instruction pointer
    mov %2 &stack       ; stack pointer

decode:
    cmp *1 #0
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
    jmp decode

plus:
    inc *0              ; increment the value at *0
    jmp next

in:
    ; TODO implement
    jmp next

minus:
    dec *0              ; decrement the value at *0
    jmp next

out:
    ; TODO implement
    jmp next

left:
    cmp %0 &cells       ; if at the start of cells
    jsz next            ; jump to next instruction

    dec %0              ; else, decrement the program pointer
    jmp next            ; jump to next instruction

right:
    inc %0              ; increment program pointer
    cmp %0 &end_cells   ; if not past the end of cells
    jnz next            ; jump to next instruction

    dec %0              ; else, decrement program pointer
    jmp next            ; jump to next instruction

open_sq:
    cmp *0 #0
    jsz open_sq.skip
    
    jsr push_stack
    jmp next

open_sq.skip:
    jsr find_close_sq
    jmp next

find_close_sq:
    inc %1

find_close_sq.loop:
    cmp *1 #$5B
    jsz find_close_sq.inc

    cmp *1 #$5D
    jnz find_close_sq.next

    cmp sq_counter #0
    jnz find_close_sq.dec

    inc %1
    ret

find_close_sq.next:
    inc %1
    jmp find_close_sq.loop

find_close_sq.inc:
    inc sq_counter
    jmp find_close_sq.next

find_close_sq.dec:
    dec sq_counter
    jmp find_close_sq.next
    
close_sq:
    cmp *0 #0
    jsz close_sq.skip

    jsr pop_stack

close_sq.skip:
    jmp next

error:
end:
    hlt

check_stack:
    cmp *2 &end_stack
    jsz error           ; stack overflow

    cmp *2 &sq_counter
    jsz error           ; stack underflow

    ret

push_stack:
    jsr check_stack

    mov *2 %0
    inc %2

    ret

pop_stack:
    dec %2

    jsr check_stack

    mov %0 *2

    ret

program: !wstr "++>"

cells: !array 1024 0    ; 1024 zeros
end_cells:

sq_counter:
    !dw 0               ; pre stack word
stack: !array 1024 0 
end_stack:
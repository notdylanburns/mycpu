start:
    mov %0 #10
    adc %0 #12

    mov %1 %0
    sbc %1 #10

    jmp init

post_init:
    jsr my_routine

loop:
    hlt

my_routine:
    phf
    mov %0 #$ffff
    mov %1 %0
    ppf

    ret

init:
    jmp post_init
; Interrupt Handlers

irq0:
irq1:
irq2:
irq3:
irq4:
irq5:
irq6:
irq7:
irq8:
irq9:
irqA:
irqB:
irqC:
irqD:
irqE:
irqF:

    !org $fff0

irq_vector_table:
    !dw irq0
    !dw irq1
    !dw irq2
    !dw irq3
    !dw irq4
    !dw irq5
    !dw irq6
    !dw irq7
    !dw irq8
    !dw irq9
    !dw irqA
    !dw irqB
    !dw irqC
    !dw irqD
    !dw irqE
    !dw irqF 
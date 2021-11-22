start:
    mov %f #$1234           ; stores 0x1234 in %f
    mov %0 #1234            ; stores 1234 in %0
    mov $9a7d #'1101        ; stores 0b1101 at memory location 0x9a7d
    mov $ffff0003 #10       ; stores 10 at memory location 0xffff0003
    mov data %f

data:
    !dw 0
    !ddw $deadbeef

redfine_me:
    !ddw irq_vector_table

my_str:
    !str "deez nutz"

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
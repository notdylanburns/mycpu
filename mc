0000: nop
    8000000a

001r: ldr %r imm
    0000000a
    00402r80
    8000000a

002r: psh %r
    42401r80
    8000002a

003r: pop %r
    00000020
    02402r80
    8000000a

004r: adc %r imm
    00085r8a
    00504000
    00206r80
    8000000a

005r: sbc %r imm

006r: and %r imm

007r: or %r imm

008r: xor %r imm

009r: not %r

00ar: inc %r

00br: dec %r

00cr: lsh %r 

00dr: rsh %r 

00er: rol %r 

00fr: ror %r
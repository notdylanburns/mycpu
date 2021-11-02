0000: hlt
    

001r: mov %r imm   (%r is destination)
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
    00085r8a
    00504000
    0020er80
    8000000a

006r: and %r imm
    00085r8a
    00504000
    00216r80
    8000000a

007r: or %r imm
    00085r8a
    00504000
    0021er80
    8000000a

008r: xor %r imm
    00085r8a
    00504000
    00226r80
    8000000a

009r: not %r
    00085r8a
    0022er80
    8000000a

00ar: inc %r
    00085r8a
    00236r80
    8000000a

00br: dec %r
    00085r8a
    0023er80
    8000000a

00cr: lsh %r
    00085r8a
    00246r80
    8000000a

00dr: rsh %r 
    00085r8a
    0024er80
    8000000a

00er: rol %r
    00085r8a
    00256r80
    8000000a

00fr: ror %r
    00085r8a
    0025er80
    8000000a

0100:

011r: mov %r m16

012r: mov m16 %r

013r: tst %r

014r: adc %r m16

015r: sub %r m16

016r: and %r m16

017r: or %r m16

018r: xor %r m16

019r: 

01ar: 

01br: 

01cr: 

01dr: 

01er: 

01fr:

4000: rti
    02400014
    00000020
    0240000c
    00000020
    80000000

8000: int (used internally only)
    43400000
    00000022
    42c00000
    00000022
    03c0000c
    80000001

f000: nop
    8000000a

ff00: jmp a16
    0000000a
    0040000c
    80000000
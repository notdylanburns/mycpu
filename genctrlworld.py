"""
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|MCR|   |   |   |   |   |   |   |   |   |   |   |IRE|PRE|SPE|PCE|
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
|CI1|CI0|RS3|RS2|RS1|RS0|GEN|AI3|AI2|AI1|AI0|AEN|ARW|LRW|SRW|HLT|
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

CTRL LINES:
// CPU halt
 0: HLT

// RW FLAGS
 1: SYSRW // External RW
 2: REGRW // CIR, REGISTERS
 3: ADDRW // PR, PC
 4: ALURW // FLAGS, A, B

// ALU enable
 5: ALUEN

 6: ALUF // ALU Flag register
 7: ALUA // ALU A register
 8: ALUB // ALU B register

// ALU instructions
 9: ALUI0
10: ALUI1
11: ALUI2
12: ALUI3

// general purpose register select bits
13: GPREN
14: GPRS0
15: GPRS1
16: GPRS2
17: GPRS3

// counter bits
18: CTRI0
19: CTRI1
20: PCENA  // program counter enable
21: SPENA  // stack pointer enable 

22: PRENA  // Page register enable
23: IRENA  // Instruction register enable

// addressing stuff
24: DHIGHA // Output data to HI addr register
25: DLOWA  // Output data to LO addr register

26: SAHIGH // Set hi half of address
27: SALOW  // set lo half of address
...

31: MCR    // Microcode counter reset

"""

def main():
    prompts = [
        "(HLT) Halt CPU: ", 
        "(SRW) RW Pin: ", 
        "(RRW) Register RW (GPR and IR): ",
        "(MRW) Memory Address Register WE: ",
        "(ARW) ALU Registers RW: ",
        "(AEN) ALU Enable: ",
        "(AFE) ALU Flags Enable: ",
        "(AAE) ALU A Register Enable: ",
        "(ABE) ALU B Register Enable: ",
        "(AI0) ALU Instruction Bit 0: ",
        "(AI1) ALU Instruction Bit 1: ",
        "(AI2) ALU Instruction Bit 2: ",
        "(AI3) ALU Instruction Bit 3: ",
        "(REN) General Purpose Register Enable: ",
        "(RS0) Register Select Bit 0: ",
        "(RS1) Register Select Bit 1: ",
        "(RS2) Register Select Bit 2: ",
        "(RS3) Register Select Bit 3: ",
        "(CI0) Counter Instruction Bit 0 (PC, SP): ",
        "(CI1) Counter Instruction Bit 1 (PC, SP): ",
        "(PCE) Program Counter Enable: ",
        "(SPE) Stack Pointer Enable: ",
        "(PRE) Page Register Enable: ",
        "(IRE) Instruction Register Enable: ",
        "(DLA) Set Data To Lower Half Of MAR: ",
        "(DHA) Set Data To Upper Half Of MAR: ",
        "(LAE) Enable Low Half Of MAR: ",
        "(HAE) Enable High Half of MAR: ",
        "(UN0) Unused: ",
        "(UN1) Unused: ",
        "(PCI) Increment Program Counter at the start of this cycle: ",
        "(MCR) Microcode Counter Reset: "
    ]

    for words in range(16):
        ctrlword = 0

        i = 0
        bit = 0
        while i < len(prompts):
            try:
                bit = int(input(prompts[i]))
                if bit != 0 and bit != 1:
                    pass
                else:
                    ctrlword += bit * (1 << i)
                    i += 1
            except ValueError as e:
                pass

        print("{:032b}\n{:08x}".format(ctrlword, ctrlword))

        if bit == 1: #MCR is 1
            break


if __name__ == "__main__":
    main()
import sys

output = [0x80000000] * (2 ** 20)

def lines(f):
    with open(f, "r") as src:
        for l in src:
            yield l.strip()

def main(f):
    gen = lines(f)
    while True:
        try:
            l = next(gen)
        except StopIteration:
            break

        if ":" in l:
            op = l.split(":")[0]
            mc = ["00400044"]
            while True:
                try:
                    nl = next(gen)
                except StopIteration:
                    break

                if nl == "":
                    break
                else:
                    mc.append(nl)
        
            nop = 0
            if "r" in op:
                for i in range(16):
                    nop = int(op.replace("r", f"{i:x}"), 16)
                    count = 0
                    for m in mc:
                        output[(nop << 4) + count] = int(m.replace("r", f"{i:x}"), 16)
                        count += 1

            else:
                nop = int(op, 16)
                count = 0
                for m in mc:
                    output[(nop << 4) + count] = int(m, 16)
                    count += 1
    
    with open("microcode.bin", "wb") as out:
        for s in output:
            out.write(bytearray([
                (s & 0xff000000) >> 24,
                (s & 0xff0000) >> 16,
                (s & 0xff00) >> 8, 
                (s & 0xff)
            ]))

    return

if __name__ == "__main__":
    main(sys.argv[1])
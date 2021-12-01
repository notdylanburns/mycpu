import csv
import sys

def main(file: str, out: str):
    words: list[int] = [0x80000000] * (2 ** 20)
    output: bytearray = bytearray([0] * (2 ** 22))

    with open(file, "r") as f:
        f.readline()
        for l in csv.reader(f):
            if l[0] != "":
                if "R" in l[0]:
                    for r in range(16):
                        base = int(l[0].replace("R", f"{r:x}"), 16) << 4
                        i: int = 0
                        for w in l[5:]:
                            try:
                                words[base + i] = int(w.replace("R", f"{r:x}"), 16)
                            except ValueError:
                                print(f"Error parsing microcode for {l[0]}")
                            i += 1

                elif "X" in l[0] and "Y" in l[0]:
                    for x in range(16):
                        for y in range(16):
                            base = int(l[0].replace("X", f"{x:x}").replace("Y", f"{y:x}"), 16) << 4
                            i: int = 0
                            for w in l[5:]:
                                try:
                                    words[base + i] = int(w.replace("X", f"{x:x}").replace("Y", f"{y:x}"), 16)
                                except ValueError:
                                    print(f"Error parsing microcode for {l[0]}")
                                i += 1

                else:
                    base = int(l[0], 16) << 4
                    i: int = 0
                    for w in l[5:]:
                        words[base + i] = int(w, 16)
                        i += 1

    i = 0
    for w in words:
        output[4 * i + 0] = (w & 0xff000000) >> 24
        output[4 * i + 1] = (w & 0x00ff0000) >> 16
        output[4 * i + 2] = (w & 0x0000ff00) >> 8
        output[4 * i + 3] = (w & 0x000000ff)
        i += 1
    
    with open(out, "wb") as f:
        f.write(output)

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])

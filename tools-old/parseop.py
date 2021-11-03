import json
import sys
from typing import Generator, Tuple, Union

def main(file: str) -> int:
    try:
        content = None
        with open(file, "r") as f:
            content = list(map(
                lambda s: s.rstrip("\n").split("  "), 
                f.readlines()
            ))
        
        lines = []
        for line in content:
            tabcount = 0
            for v in line:
                if v == "":
                    tabcount += 1
                elif v.strip() == "":
                    #error, invalid indent
                    pass
                else:
                    lines.append({"indent": tabcount, "value": v, "opcode": None})
                    break
        
        print(lines)
    except FileNotFoundError:
        print(f"No such file '{file}'")
        return 1

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0].split('/')[:-1]} file")
        exit(1)
    exit(main(sys.argv[1]))
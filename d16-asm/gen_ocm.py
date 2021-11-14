import csv
import sys

template = """#include "matrix.h"\nconst int MATRIX_LEN = {};\n\nconst struct Opcode MATRIX[] = """

ocm = {}
NUM_MODES = 36

def get_am(o1, o2):
    ams = {
        "-": 0,
        "imm": 1,
        "a16": 2,
        "a32": 3,
        "%R": 4,
        "%X": 4,
        "%Y": 4,
        "*R": 5,
    }

    try:
        return (ams[o1] * 6) + ams[o2]
    except KeyError:
        return -1


def main(file: str):
    with open(file, "r") as f:
        f.readline()
        for l in csv.reader(f):
            if l[1] != "":
                if l[1] not in ocm:
                    ocm[l[1]] = []
                    for i in range(NUM_MODES):
                        ocm[l[1]].append({"X": "----", "V": False})

                if (am := get_am(l[3], l[4])) >= 0:
                    ocm[l[1]][am]["X"] = l[0]
                    ocm[l[1]][am]["V"] = True

    string = "{\n"
    for o in ocm:
        string += f"    {{.N=\"{o.lower()}\", .M={{"
        for m in ocm[o]:
            string += f"{{.V={'true ' if m['V'] else 'false'},.X=\"{m['X']}\"}},"
        string += "}},\n"
    string += "};"

    print(template.format(len(ocm)) + string)

if __name__ == "__main__":
    main(sys.argv[1])
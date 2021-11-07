import csv
import sys

template = """#include "matrix.h"\n\nconst struct Opcode MATRIX[] = """

ocm = {}

def get_am(o1, o2):
    ams = {
        "-": {
            "-": 0,
        },
        "imm": {
            "-": 1,
        },
        "a16": {
            "-": 2,
            "imm": 5,
            "%R": 6
        },
        "a32": {
            "-": 3,
            "imm": 7,
            "%R": 8,
        },
        "%R": {
            "-": 4,
            "imm": 9,
            "a16": 10,
            "a32": 11
        },
        "%X": {
            "%Y": 12
        },
    }

    try:
        return ams[o1][o2]
    except KeyError:
        return -1


def main(file: str):
    with open(file, "r") as f:
        f.readline()
        for l in csv.reader(f):
            if l[1] != "":
                if l[1] not in ocm:
                    ocm[l[1]] = [{"X": 0, "V": False}] * 16

                if (am := get_am(l[3], l[4])) > 0:
                    ocm[l[1]][am]["X"] = l[0]
                    ocm[l[1]][am]["V"] = True

    string = "{ "
    for o in ocm:
        string += f"{{.N=\"{o}\", .M={{"
        for m in ocm[o]:
            string += f"{{.V={'true' if m['V'] else 'false'},.X=\"{m['X']}\"}},"
        string += "}}"
    string += "}"

    print(template + string)

if __name__ == "__main__":
    main(sys.argv[1])
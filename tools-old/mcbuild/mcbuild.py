import json

def join(*args) -> dict:
    word: list(str) = "--------------------------------".split()
    incompatible: list[int] = []
    for w in args:
        for i in range(32):
            if word[i] == w[i]:
                pass
            elif word[i] == "-":
                word[i] = w[i]
            else:
                incompatible.append(31 - i)

    return {
        "word": "".join(word),
        "valid": len(incompatible) == 0,
        "incompatible": list(map(incompatible))
    }



def main(macros: dict[str, str]):
    while True:
        cmd = input("$ ").split("|")
        ops: list = None
        try:
            ops = [macros[o.strip()] for o in cmd]
        except KeyError as e:
            print(f"{e.args[0]} is not a macro")
            continue

        print(ops)
        new = join(ops)
        if new["valid"]:
            name = input("Name of new opcode: ")
            while name in macros:
                print(f"{name} already exists.")
                name = input("Name of new opcode: ")
            macros["name"] = new["word"]
        else:
            print(f"Conflicting bits present: {', '.join(new['incompatible'])}")

if __name__ == "__main__":
    obj = None
    with open("macros.json", "r") as f:
        obj = json.load(f)
    
    with open("macros.json", "w") as f:
        try:
            main(obj)
        except KeyboardInterrupt:
            json.dump(obj, f, indent=2)
        except EOFError:
            json.dump(obj, f, indent=2)
        except Exception as e:
            print(e.with_traceback())
            json.dump(obj, f, indent=2)

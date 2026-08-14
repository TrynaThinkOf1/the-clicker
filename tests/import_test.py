"""
August 11, 2026.

This test requires a specific version of main.py such that the program only does the following:
  ```c
    if (argc < 2) return 1;

    char* error;
    Macro* mac;
    if (!importMacro(argv[1], &mac, &error)) {
      printf("error: %s\n", error);
      return 1;
    }

    printf("name: %s\n", mac->name);

    macro_part* p = mac->first;
    while (p != NULL) {
      printf("{{\t%s(%d, %d)\t}}\n", getFuncName(p->func), p->x, p->y);
      p = p->next;
    }

    freeMacro(mac);

    return 0;
  ```
  
That example requires a certain version of the macro API, change code to meet any current specifications such that it
still outputs properly and can be tested with this file. Otherwise, edit this test file code.

This test also requires that binary exist at the path `~/the-clicker/clicker` (`/Users/<name>/the-clicker/clicker`)
"""

import subprocess
import typing
from pathlib import Path


def fprint(n: int, msg: str, scs: bool):
  if not scs:
    print(f"\033[0;31m[[ TEST #{n}  ->  {msg} ]]\033[0m")
  else:
    print(f"\033[0;32m[[ TEST #{n}  ->  SUCCESS ]]\033[0m")


def create(name: str, steps: dict[str, tuple[int, int]]) -> None:
  with open(Path.home() / ".clicker_macros" / name, "w") as file:
    file.write(f"\"{name}\": {{ \n")

    for func, (x, y) in steps.items():
      file.write(f"\t{name}({x}, {y})\n")

    file.write("}\n")


def verify(name: str, steps: dict[str, tuple[int, int]], n: int) -> bool:
  result = subprocess.run([Path.home() / "the-clicker" / "clicker", name], stdout=subprocess.PIPE)
  if result.returncode != 0:
    raise Exception(f"clicker returned error code {result.returncode}")

  op: str = result.stdout.decode()

  if op.startswith("error: "):
    fprint(n, '"' + op[:len(op) - 1] + '"', False)
    return False
  
  for line, (func, (x, y)) in zip(op.splitlines(), steps.items()):
    if line.startswith("name: "):
      if line[6:] != name:
        fprint(n, "NAME FAILED TO COPY", False)
        return False
      else:
        continue

    if line != f"{{{{\t{func}({x}, {y})\t}}}}":
      fprint(n, f"line \"{line}\" != \"{{{{\t{func}({x}, {y})\t}}}}\"", False)
      return False

  fprint(n, "", True)
  return True;


def main():
  create("testingTest", {"leftClick": (2, 4)})
  verify("testingTest", {"leftClick": (2, 4)}, 0)


if __name__ == "__main__":
  main()

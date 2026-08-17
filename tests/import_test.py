"""
August 11, 2026.

This test requires a specific version of main.c such that the program only does the following:
  ```c
    if (argc < 2) return 1;

    char* error;
    Macro* mac;
    if (!importMacro(argv[1], &mac, &error)) {
      printf("error: %s\n", error);
      freeMacro(mac);
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

import standardized
from pathlib import Path
from os import remove

# [===================== SEPARATOR =====================]

def createTestFile(name: str, steps: dict[str, tuple[int, int]]) -> None:
  with open(Path.home() / ".clicker_macros" / name, "w") as file:
    file.write(f"\"{name}\": {{ \n")

    for func, (x, y) in steps.items():
      file.write(f"\t{func}({x}, {y})\n")

    file.write("}\n")

# [===================== SEPARATOR =====================]

class Test:
  def __init__(self, std_desc: str, steps: dict[str, tuple[int, int]], desired: list[str], modifier):
    self.desc = std_desc
    self.steps = steps
    self.desired = ["name: test"] + [modifier(val) for val in desired]

# [===================== SEPARATOR =====================]

TESTS: list[Test] = [
  Test("VALID MACRO : NO NAME ERRORS : NO NUMBER ERRORS : NO FORMAT ERRORS",
    {
      "leftClick": (-1, -1),
      "moveCursor": (4, 5),
      "rightClick": (800, 250),
      "sleep_m": (500, 0),
      "rightDoubleClick": (-1, -1)
    }, [
      "leftClick(-1, -1)",
      "moveCursor(4, 5)",
      "rightClick(800, 250)",
      "sleep_m(500, 0)",
      "rightDoubleClick(-1, -1)"
    ],
    lambda s : f"{{{{\t{s}\t}}}}"
  ),
  Test("HALF MACRO : ONE NAME ERROR : ONE NUMBER ERROR : NO FORMAT ERRORS",
    {
      "fakeFunc": (400, 200),
      "sleep_m": (1000, 0),
      "moveCursor": (2000, 1800),
      "rightClick": (-2, -400)
    },
    [
      "sleep_m(1000, 0)",
      "moveCursor(2000, 1800)",
    ],
    lambda s : f"{{{{\t{s}\t}}}}"
  ),
  Test("BAD MACRO : ALL NAME ERRORS : NO NUMBER ERRORS : NO FORMAT ERRORS",
    {
      "fakeFunc": (0, 0),
      "badFunc": (-1, -1),
      "lfetClick": (356, 112)
    },
    [],
    lambda s : f"{{{{\t{s}\t}}}}"
  ),
  Test("BAD MACRO : NO NAME ERRORS : ALL NUMBER ERRORS : NO FORMAT ERRORS",
    {
      "rightClick": (-400, -1000),
      "sleep_m": (-2, -3),
      "moveCursor": (-645, -350)
    },
    [],
    lambda s : f"{{{{\t{s}\t}}}}"
  ),
  Test("HALF MACRO : NO NAME ERROS : NO NUMBER ERRORS : FIVE FORMAT ERROS",
    {
      "  leftClick": (12, 30),
      "sleep_m(": (500, 0),
      "rightClick": (-1, -1),
      "": (-1, -1),
      "": ("", ""), # this should still work to just have an empty function
      "\nleftDoubleClick": ("--1", -1),
    },
    [
      "rightClick(-1, -1)"
    ],
    lambda s : f"{{{{\t{s}\t}}}}"
  )
]

def main():
  for test in TESTS:
    print(f"| {test.desc} |")
    createTestFile("test", test.steps)
    standardized.fullTest([Path.home() / "the-clicker" / "clicker", "test"], test.desired)
    remove(Path.home() / ".clicker_macros" / "test")

# [===================== SEPARATOR =====================]

if __name__ == "__main__":
  main()
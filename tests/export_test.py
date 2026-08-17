"""
August 15, 2026.

This test requires a specific version of main.c such that the program only does the following:
  ```c
  if (argc < 2) return 1;
  
  char* copied_name = malloc(sizeof(char) * (strlen(argv[1]) + 1));
  if (copied_name == NULL) {
    printf("error: failed to allocate name\n");
    return 0;
  }
  strlcpy(copied_name, argv[1], sizeof(char) * (strlen(argv[1]) + 1));
  
  Macro* mac = initializeMacro();
  mac->name = copied_name;

  for (int i = 2; i < argc; i++) {
    char func_name[17] = {0}; // longest possible name is rightDoubleClick @ 16 chars
    int x, y;
    if (sscanf(argv[i], " %16[^(](%d, %d)", func_name, &x, &y) != 3) continue; // just skip the line

    addMacroStep(mac, getNameFunc(func_name), x, y);
  }

  char* error;
  if (!exportMacro(mac, &error)) {
    printf("error: %s\n", error);
  }

  freeMacro(mac);
  
  return 0;
  ```
  
That example requires a certain version of the macro API, change code to meet any current specifications such that it
still outputs properly, will create properly formatted files, and can be tested with this file. Otherwise, edit this test file code.

This test also requires that binary exist at the path `~/the-clicker/clicker` (`/Users/<name>/the-clicker/clicker`)

All of these tests use valid macros because the program assumes that the macros created within the app are valid, because
it should not be possible to create invalid ones.
"""

from standardized import fullTest, fullTestFile
from pathlib import Path
from os import remove

# [===================== SEPARATOR =====================]

class Test:
  def __init__(self, std_desc: str, name: str, steps: list[str]):
    self.desc = std_desc
    self.name = name
    self.steps = steps

# [===================== SEPARATOR =====================]

TESTS: list[Test] = [
  Test("VALID MACRO : CLEAN NAME",
    "validMacro",
    [
      "leftClick(-1, -1)",
      "moveCursor(4, 5)",
      "rightClick(800, 250)",
      "sleep_m(500, 0)",
      "rightDoubleClick(-1, -1)"
    ]
  ),
  Test("VALID MACRO : EMOJI NAME",
    "🤮🔥🫁",
    [
      "leftDoubleClick(545, 200)",
    ]
  ),
  Test("VALID MACRO : SPECIAL CHAR NAME",
    "$_&\tw0*()",
    [
      "rightClick(-1, -1)",
      "sleep_m(200, 0)",
      "moveCursor(1750, 0)"
    ]
  )
]

def main():
  for test in TESTS:
    print(f"| {test.desc} |")
    print("creating file.")
    fullTest([Path.home() / "the-clicker" / "clicker", test.name] + test.steps, []) # ask clicker to create the file
    print("file created.")
    fullTestFile(Path.home() / ".clicker_macros" / test.name, [f"\"{test.name}\": {{"] + [f"\t{step}" for step in test.steps] + ["}"])
    remove(Path.home() / ".clicker_macros" / test.name)

# [===================== SEPARATOR =====================]

if __name__ == "__main__":
  main()
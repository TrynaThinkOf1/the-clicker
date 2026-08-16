import subprocess

RED     = "\033[0;31m"
GREEN   = "\033[0;32m"
YELLOW  = "\033[0;33m"
BLUE    = "\033[0;34m"
BLANK   = ""
RESET   = "\033[0m"

"""
Print a list of messages in a list of colors
"""
def formatPrintList(msgs: list[str], colors: list[str]) -> None:
  if len(msgs) != len(colors):
    raise ValueError("Length of messages and length of colors do NOT match up!")

  for msg, color in zip(msgs, colors):
    print(color + msg + RESET, end="")

  print() # final newline

# [===================== SEPARATOR =====================]

"""
Test read a file
"""
def fullTestFile(abs_path: str, desired: list[str]):
  with open(abs_path, "r") as file:
    buffer = file.read()

  fullTest(["echo", buffer], desired + [""])

# [===================== SEPARATOR =====================]

"""
Test a command
"""
def fullTest(command: list[str], desired: list[str]) -> None:
  formatPrintList(["RUNNING TEST"], [BLUE])
  
  result = subprocess.run(command, stdout=subprocess.PIPE)
  outputs = result.stdout.decode().splitlines()

  scs = True

  if len(outputs) != len(desired):
    scs = False
    seen: list[str] = []
    
    formatPrintList(["[[ DIFF OUTPUT THAN EXPECTED, ", (str(-diff) + " EXTRA LINES") if ((diff := len(desired) - len(outputs)) < 0) else (str(diff) + " LINES MISSING"), "]]"], [YELLOW, YELLOW, YELLOW])
    # because we dont have a direct-direct match, we have to check every output line against every desired line
    for op_line in outputs:
      if op_line not in desired:
        formatPrintList(["UNEXPECTED LINE: ", op_line], [RED, BLANK])
        scs = False
      else:
        seen.append(op_line)

    not_seen = set(desired) - set(seen)
    if len(not_seen) > 0:
      formatPrintList([f"[[ LINES NOT SEEN ]]\n"] + [f"\t{line}\n" for line in list(not_seen)] + ["[[ ]]"], [YELLOW] + [BLANK for _ in range(len(not_seen))] + [YELLOW])
  else:
    nt, nf = 0, 0
    for op_line, de_line in zip(outputs, desired):
      if op_line != de_line:
        formatPrintList(["LINE MISMATCH: ", de_line, "\t->\t", op_line], [RED, BLANK, RED, BLANK])
        scs = False
        nf += 1
      else:
        nt += 1
  
  if scs:
    formatPrintList(["[[ TEST PASSED ]]"], [GREEN])
  else:
    formatPrintList(["[[ TEST FAILED ]]"], [RED])

  formatPrintList(["END TEST\n"], [BLUE])
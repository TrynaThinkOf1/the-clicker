RED     = "\033[0;31m"
GREEN   = "\033[0;32m"
YELLOW  = "\033[0;33m"
BLUE    = "\033[0;34m"
RESET   = "\033[0m"

"""
Print a list of messages in a list of colors
"""
def format_print_list(msgs: list[str], colors: list[str]) -> None:
  if len(msgs) != len(colors):
    raise ValueError("Length of messages and length of colors do NOT match up!")

  for msg, color in zip(msgs, colors):
    print(color + msg + RESET, end="")

  print() # final newline

if __name__ == "__main__":
  format_print_list(["this is red", "\tthis is yellow\n", "how about blue\t", "maybe some green?"], [RED, YELLOW, BLUE, GREEN])
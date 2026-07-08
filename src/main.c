#include <stdio.h>

#include <ApplicationServices/ApplicationServices.h>

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/screen/screen.h"
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/screen/screen.h"
  #include "linux/mouse/mouse.h"
#else
  #error "Unknown Operating System"
#endif

#include "parse_int.h"
#include "builtins.h"
#include "macros.h"


int main(int argc, char** argv) {
  Macro* mac = initializeMacro();
  addMacroStep(mac, leftClick, 500, 500);
  runMacro(mac);

  return 0;
}

#include <stdio.h>

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/screen/screen.h"
  #include "macos/mouse/mouse.h"
  #include "linux/export_macros.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/screen/screen.h"
  #include "linux/mouse/mouse.h"
  #include "linux/export_macros.h"
#elif defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
  #include "windows/screen/screen.h"
  #include "windows/mouse/mouse.h"
#else
  #error "Unknown Operating System"
#endif

#include "parse_int.h"
#include "builtins.h"
#include "macros.h"


int main(int argc, char** argv) {
  if (!initializeMouse()) { // this is only necessary for linux, but macos has a dummy version for API uniformity
    printf("Failed to initialize mouse!\n");
    return 1;
  }
  destroyMouse(); // same as the initializer function above

  Macro* mac = initializeMacro();
  if (mac == NULL) {
    printf("Failed to initialize macro!\n");
    return 1;
  }

  addMacroStep(mac, moveCursor, 100, 200);
  addMacroStep(mac, leftClick, 0, 0);

  exportMacro(mac, "test macro name");
  exportMacro(mac, "anotherMacro");
  exportMacro(mac, "macro_3");

  freeMacro(mac);

  return 0;
}

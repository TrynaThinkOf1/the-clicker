#ifndef BUILTINS_H
#define BUILTINS_H

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
  #include <unistd.h>
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
  #include <unistd.h>
#elif defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
  #include "windows/mouse/mouse.h"
  #include <windows.h>
#endif


extern void moveCursor(int x, int y);

/// built-in function for left clicking at a certain position
/// set x and y to -1 for the current position
static void leftClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(LEFT, true);
#if !defined(__WINDOWS__) && !defined(_WIN32) && !defined(__WIN64__)
  clickMouse(LEFT, false);
#endif
}

/// built-in function for right clicking at a certain position
/// set x and y to -1 for the current position
static void rightClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(RIGHT, true);
#if !defined(__WINDOWS__) && !defined(_WIN32) && !defined(__WIN64__)
  clickMouse(RIGHT, false);
#endif
}

//

/// built-in function for double left clicking at a certain position
/// set x and y to -1 for the current position
static void leftDoubleClick(int x, int y) {
  leftClick(x, y);
  leftClick(x, y);
}

/// built-in function for double right clicking at a certain position
/// set x and y to -1 for the current position
static void rightDoubleClick(int x, int y) {
  rightClick(x, y);
  rightClick(x, y);
}

//

/// THIS IS THE FUNCTION TO CALL FOR SLEEP.
/// IT IS SET UP IN THIS WAY SO THAT I CAN ADD
/// A UNIFORM FUNCTION POINTER TO THE MACRO SYSTEM.
/// SET X TO A # > 0 AND THAT AMOUNT OF TIME
/// WILL BE SLEPT. SET Y TO 0.
static void sleep_m(int x, int y) {
  #if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
    Sleep(x);
  #else
    usleep(x * 1000); // convert to milliseconds
  #endif
}

#endif /* BUILTINS_H */

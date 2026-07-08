#ifndef BUILTINS_H
#define BUILTINS_H

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
#endif


/// built-in function for left clicking at a certain position
/// set x and y to -1 for the current position
static void leftClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(LEFT, LEFT_DOWN);
  clickMouse(LEFT, LEFT_UP);
}

/// built-in function for right clicking at a certain position
/// set x and y to -1 for the current position
static void rightClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(RIGHT, RIGHT_DOWN);
  clickMouse(RIGHT, RIGHT_UP);
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
  sleep(x);
}

#endif /* BUILTINS_H */

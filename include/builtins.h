#ifndef BUILTINS_H
#define BUILTINS_H

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
#endif


/// built-in function for left clicking at a certain position
static void leftClick(int x = -1, int y = -1) {
  if (x >= 0 && y >= 0) move(x, y);

  clickMouse(LEFT, LEFT_DOWN);
  clickMouse(LEFT, LEFT_UP);
}

/// built-in function for right clicking at a certain position
static void rightClick(int x = -1, int y = -1) {
  if (x >= 0 && y >= 0) move(x, y);

  clickMouse(RIGHT, RIGHT_DOWN);
  clickMouse(RIGHT, RIGHT_UP);
}

//

/// built-in function for double left clicking at a certain position
static void leftDoubleClick(int x = -1, int y = -1) {
  leftClick(x, y);
  leftClick(x, y);
}

/// built-in function for double right clicking at a certain position
static void rightDoubleClick(int x = -1, int y = -1) {
  rightClick(x, y);
  rightClick(x, y);
}

#endif /* BUILTINS_H */

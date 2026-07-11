#include "builtins.h"

#include <stdbool.h>

void leftClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(LEFT, true);
  #if !defined(__WINDOWS__) && !defined(_WIN32) && !defined(__WIN64__)
    clickMouse(LEFT, false);
  #endif
}

void rightClick(int x, int y) {
  if (x >= 0 && y >= 0) moveCursor(x, y);

  clickMouse(RIGHT, true);
  #if !defined(__WINDOWS__) && !defined(_WIN32) && !defined(__WIN64__)
    clickMouse(RIGHT, false);
  #endif
}

void leftDoubleClick(int x, int y) {
  leftClick(x, y);
  leftClick(x, y);
}

void rightDoubleClick(int x, int y) {
  rightClick(x, y);
  rightClick(x, y);
}

void sleep_m(int x, int y) {
  #if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
    Sleep(x);
  #else
    struct timespec ts;
    ts.tv_sec = x / 1000;
    ts.tv_nsec = (x % 1000) * 1000000;
    nanosleep(&ts, NULL);
  #endif
}

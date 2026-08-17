#include "builtins.h"


char* getFuncName(void (*func)(int x, int y)) {
  if (func == moveCursor) return (char*)"moveCursor";
  else if (func == leftClick) return (char*)"leftClick";
  else if (func == rightClick) return (char*)"rightClick";
  else if (func == leftDoubleClick) return (char*)"leftDoubleClick";
  else if (func == rightDoubleClick) return (char*)"rightDoubleClick";
  else if (func == sleep_m) return (char*)"sleep_m";

  return NULL;
}

void (*getNameFunc(const char* name))(int x, int y) {
  if (strcmp(name, "moveCursor") == 0) return moveCursor;
  else if (strcmp(name, "leftClick") == 0) return leftClick;
  else if (strcmp(name, "rightClick") == 0) return rightClick;
  else if (strcmp(name, "leftDoubleClick") == 0) return leftDoubleClick;
  else if (strcmp(name, "rightDoubleClick") == 0) return rightDoubleClick;
  else if (strcmp(name, "sleep_m") == 0) return sleep_m;

  return NULL;
}

//

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
  sleep_m(2, 0);
  leftClick(x, y);
}

void rightDoubleClick(int x, int y) {
  rightClick(x, y);
  sleep_m(2, 0);
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

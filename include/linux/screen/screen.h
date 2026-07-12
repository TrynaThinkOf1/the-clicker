#ifndef LINUX_SCREEN_H
#define LINUX_SCREEN_H

#if defined(__LINUX__) || defined(__unix__)

  #include <X11/Xlib.h>

  #include "linux/mouse/mouse.h" // for display

  /// Get the width and height of the display unit
  static void getScreenSize(int* width, int* height) {
    Display* display;
    if (!(display = XOpenDisplay(NULL))) {
      *width = -1;
      *height = -1;
      return;
    }

    int snum = DefaultScreen(display);
    *width = DisplayWidth(display, snum);
    *height = DisplayHeight(display, snum);
  }

#endif

#endif /* LINUX_SCREEN_H */

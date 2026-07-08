#ifndef LINUX_SCREEN_H
#define LINUX_SCREEN_H

#if defined(__LINUX__) || defined(__unix__)

  #include <X11/Xlib.h>

  /// Get the width and height of the display unit
  static void getScreenSize(int* width, int* height) {
    char* window_id;
    Display* dpy;
    Window w;

    if (!(dpy = XOpenDisplay(0))) {
      *width = 0;
      *height = 0;
    }

    int snum = DefaultScreen(dpy);
    *width = DisplayWidth(dpy, snum);
    *height = DisplayHeight(dpy, snum);
  }

#endif

#endif /* LINUX_SCREEN_H */

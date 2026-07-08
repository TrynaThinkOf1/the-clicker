#ifndef LINUX_SCREEN_H
#define LINUX_SCREEN_H

#if defined(__LINUX__) || defined(__unix__)

  /// Get the width and height of the display unit
  static void getScreenSize(int* width, int* height) {
    *width = 0;
    *height = 0;
  }

#endif

#endif /* LINUX_SCREEN_H */

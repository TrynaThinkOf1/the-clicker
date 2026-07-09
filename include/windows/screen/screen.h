#ifndef WINDOWS_SCREEN_H
#define WINDOWS_SCREEN_H

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)

  #include <Windows.h>

  /// Get the width and height of the display unit
  static void getScreenSize(int* width, int* height) {
    *width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    *height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
  }

#endif

#endif /* WINDOWS_SCREEN_H */

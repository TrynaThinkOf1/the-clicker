#ifndef MACOS_SCREEN_H
#define MACOS_SCREEN_H

#include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Display Services

/// Get the width and height of the display unit
static void getScreenSize(int* width, int* height) {
  CGDirectDisplayID main_id = CGMainDisplayID();

  *width = CGDisplayPixelsWide(main_id);
  *height = CGDisplayPixelsHigh(main_id);
}

#endif /* MACOS_SCREEN_H */
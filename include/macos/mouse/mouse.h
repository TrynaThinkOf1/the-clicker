#ifndef MACOS_MOUSE_H
#define MACOS_MOUSE_H

#include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services


typedef enum ClickType {
  RIGHT = kCGMouseButtonRight,
  CENTER = kCGMouseButtonCenter,
  LEFT = kCGMouseButtonLeft
} ClickType;

/// Move the mouse cursor to a position on the screen
void moveCursor(int x, int y);

/// Get current location of cursor
CGPoint getCursorLocation();

/// Click the mouse in a certain way
void clickMouseDown(ClickType type);
void clickMouseUp(ClickType type);

#endif /* MACOS_MOUSE_H */
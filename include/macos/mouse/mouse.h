#ifndef MACOS_MOUSE_H
#define MACOS_MOUSE_H

#include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services


typedef enum ClickType {
  RIGHT = kCGMouseButtonRight,
  LEFT = kCGMouseButtonLeft
} ClickType;

typedef enum ClickDirection {
  RIGHT_DOWN = kCGEventRightMouseDown,
  RIGHT_UP = kCGEventRightMouseUp,
  LEFT_DOWN = kCGEventLeftMouseDown,
  LEFT_UP = kCGEventLeftMouseUp,
} ClickDirection;

/// Move the mouse cursor to a position on the screen
void moveCursor(int x, int y);

/// Get current location of cursor
CGPoint getCursorLocation();

/// Click the mouse in a certain way
void clickMouse(ClickType type, ClickDirection dir);

#endif /* MACOS_MOUSE_H */
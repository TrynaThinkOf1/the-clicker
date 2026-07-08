#ifndef MACOS_MOUSE_H
#define MACOS_MOUSE_H

#if defined(__APPLE__) || defined(__MACH__)

  #include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services
  
  
  typedef enum ClickType {
    RIGHT = kCGMouseButtonRight,
    LEFT = kCGMouseButtonLeft
  } ClickType;
  
  /// dummy functions
  static bool initializeMouse() {
    return true;
  }
  static void destroyMouse() {
    ;
  }
  
  /// Move the mouse cursor to a position on the screen
  void moveCursor(int x, int y);
  
  /// Get current location of cursor
  CGPoint getCursorLocation();
  
  /// Click the mouse in a certain way
  void clickMouse(ClickType type, bool click_down);
#endif

#endif /* MACOS_MOUSE_H */

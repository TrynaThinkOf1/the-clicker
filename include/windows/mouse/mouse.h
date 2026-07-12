#ifndef WINDOWS_MOUSE_H
#define WINDOWS_MOUSE_H

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)

  #include <Windows.h>

  
  typedef struct CursorPoint {
    int x;
    int y;
  } CursorPoint;

  /// for windows these dont actually represent values, the API is different
  typedef enum ClickType {
    RIGHT,
    LEFT
  } ClickType;

  /// dummy functions
  static bool initializeMouse() {
    return true;
  }
  static void destroyMouse() {
    ;
  }

  CursorPoint getCursorLocation();

  /// Move the mouse cursor to a position on the screen
  void moveCursor(int x, int y);

  /// This does a FULL CLICK OPERATION
  void clickMouse(ClickType type, bool click_down);

#endif

#endif /* WINDOWS_MOUSE_H */

#ifndef LINUX_MOUSE_H
#define LINUX_MOUSE_H

#if defined(__LINUX__) || defined(__unix__)

  #include <stdio.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <string.h>
  #include <stdbool.h>
  #include <linux/uinput.h>
  #include <linux/input-event-codes.h>

  #include <X11/Xlib.h>
  
  
  typedef struct CursorPoint {
    int x;
    int y;
  } CursorPoint;

  typedef enum ClickType {
    RIGHT = BTN_RIGHT,
    LEFT = BTN_LEFT
  } ClickType;

  extern volatile int fd;
  extern volatile Display* display;

  /// helper function to actually send the event to the kernel
  void emit(int fd_, int type, int code, int val);

  bool initializeMouse();
  void destroyMouse();

  CursorPoint getCursorLocation();

  void moveCursor(int x, int y);

  void clickMouse(ClickType type, bool click_down);

#endif

#endif /* LINUX_MOUSE_H */

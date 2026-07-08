#ifndef LINUX_MOUSE_H
#define LINUX_MOUSE_H

#if defined(__LINUX__) || defined(__unix__)

  #include <stdio.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <linux/uinput.h>
  #include <sys/ioctl.h>
  #include <string.h>
  #include <stdbool.h>

  typedef enum ClickType {
    RIGHT = BTN_RIGHT,
    LEFT = BTN_LEFT
  } ClickType;

  /// much simpler than the Quartz stuff
  typedef enum ClickDirection {
    RIGHT_DOWN = 1,
    RIGHT_UP = 0,
    LEFT_DOWN = 1,
    LEFT_UP = 0
  } ClickDirection;

  extern volatile int fd;

  /// helper function to actually send the event to the kernel
  void emit(int fd_, int type, int code, int val);

  bool initializeMouse();
  void destroyMouse();

  void moveCursor(int x, int y);

  void clickMouse(ClickType type, ClickDirection dir);

#endif

#endif /* LINUX_MOUSE_H */

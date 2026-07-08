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

  volatile int fd;

  void emit(int fd, int type, int code, int val);

  bool initializeMouse();
  void destroyMouse();

#endif

#endif /* LINUX_MOUSE_H */

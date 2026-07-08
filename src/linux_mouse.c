#include "linux/mouse/mouse.h"

#if defined(__LINUX__) || defined(__unix__)

  volatile int fd = -1;

  #include <stdio.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <string.h>
  #include <stdbool.h>
  #include <linux/uinput.h>
  #include <linux/input-event-codes.h>

  void emit(int fd_, int type, int code, int val) {
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;

    write(fd_, &ie, sizeof(ie));
  }
  

  bool initializeMouse() {
    /*
    * All of this code is inspired by / taken from the kernel docs:
    * https://www.kernel.org/doc/html/latest/input/uinput.html
    */
    struct uinput_setup usetup = {0};

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
      fd = open("/dev/input/uinput", O_WRONLY | O_NONBLOCK);
    }
    if (fd < 0) {
      return false;
    }

    if (ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0) return false;
    if (ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) < 0) return false;
    if (ioctl(fd, UI_SET_EVBIT, EV_REL) < 0) return false;
    if (ioctl(fd, UI_SET_RELBIT, REL_X) < 0) return false;
    if (ioctl(fd, UI_SET_RELBIT, REL_Y) < 0) return false;

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x0001; /* virtual vendor - not defined */
    usetup.id.product = 0x0001; /* virtual product - not defined */
    strcpy(usetup.name, "Virtual device");

    if (ioctl(fd, UI_DEV_SETUP, &usetup) < 0) return false;
    if (ioctl(fd, UI_DEV_CREATE) < 0) return false;

    return true;
  }

  void destroyMouse() {
    ioctl(fd, UI_DEV_DESTROY);
    if (fd >= 0) close(fd);
  }

  //

  void moveCursor(int x, int y) {
    emit(fd, EV_REL, REL_X, x); // move x
    emit(fd, EV_REL, REL_Y, y); // move y
    
    emit(fd, EV_SYN, SYN_REPORT, 0); // synchronize the event with the actual display
  }


  void clickMouse(ClickType type, bool click_down) {
    emit(fd, EV_KEY, type, (int)click_down);
    emit(fd, EV_SYN, SYN_REPORT, 0);
  }

#endif

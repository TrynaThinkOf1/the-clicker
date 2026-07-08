#include "linux/mouse/mouse.h"

#if defined(__LINUX__) || defined(__unix__)

  #include <stdio.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <linux/uinput.h>
  #include <sys/ioctl.h>
  #include <string.h>
  #include <stdbool.h>

  void emit(int fd_, int type, int code, int val) {
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd_, &ie, sizeof(ie));
  }

  bool initializeMouse() {
    /*
    * All of this code is inspired by / taken from the kernel docs:
    * https://www.kernel.org/doc/html/latest/input/uinput.html
    */
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
      fd = open("/dev/input/uinput", O_WRONLY | O_NONBLOCK);
    }
    if (fd < 0) {
      return false;
    }

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_RELBIT, REL_X);
    ioctl(fd, UI_SET_RELBIT, REL_Y);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x0001; /* virtual vendor - not defined */
    usetup.id.product = 0x0001; /* virtual product - not defined */
    strcpy(usetup.name, "Virtual device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);
  }

  void destroyMouse() {
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
  }

#endif

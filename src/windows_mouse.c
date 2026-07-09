#include "windows/mouse/mouse.h"

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)

  #include <Windows.h>

  #include "windows/screen/screen.h"


  void moveCursor(int x, int y) {
    INPUT event = {0};
    int width, height;
    getScreenSize(&width, &height);

    event.type = INPUT_MOUSE;
    event.mi.dx = (x * 65535) / width; // normalization
    event.mi.dy = (y * 65535) / height; // normalization
    event.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK; // absolute move

    SendInput(1, &event, sizeof(INPUT));
  }


  void clickMouse(ClickType type, bool click_down) {
    INPUT events[] = {0, 0};

    // click down without moving the mluse
    events[0].type = INPUT_MOUSE;
    events[0].mi.dx = 0;
    events[0].mi.dy = 0;
    events[0].mi.dwFlags = (type == LEFT ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN) | MOUSEEVENTF_VIRTUALDESK;

    // click up, these values will be cached, not calculated every time
    events[1].type = INPUT_MOUSE;
    events[1].mi.dx = 0;
    events[1].mi.dy = 0;
    events[1].mi.dwFlags = (type == LEFT ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP) | MOUSEEVENTF_VIRTUALDESK;

    SendInput(2, &events, sizeof(INPUT));
  }

#endif

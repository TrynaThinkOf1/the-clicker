#include "macos/mouse/mouse.h"

#if defined(__APPLE__) || defined(__MACH__)

  #include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services


  void moveCursor(int x, int y) {
    // create the event, does nothing yet
    CGEventRef event = CGEventCreateMouseEvent(
      NULL, // nullable source of event
      kCGEventMouseMoved, // type of event
      CGPointMake(x, y), // where to move the mouse
      kCGMouseButtonLeft // ignored
    );

    // post the event to the queue
    CGEventPost(kCGHIDEventTap, event);

    CFRelease(event); // free the event
  }


  CursorPoint getCursorLocation() {
    CGEventRef event = CGEventCreate(NULL); // create an event representing the current state
    CGPoint location = CGEventGetLocation(event); // get the location of said event

    CFRelease(event); // free the event

    CursorPoint loc = { (int)location.x, (int)location.y };
    return loc;
  }


  void clickMouse(ClickType type, bool click_down) {
    if (CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, type)) return; // button already down

    CursorPoint point = getCursorLocation();
    CGPoint loc = { (double)point.x, (double)point.y };

    CGEventRef event = CGEventCreateMouseEvent(
      NULL, // nullable source of event
      (type == RIGHT
        ? (click_down ? kCGEventRightMouseDown : kCGEventRightMouseUp)
        : (click_down ? kCGEventLeftMouseDown : kCGEventLeftMouseUp)
      ), // type of event
      loc, // click in the current position
      type // type of click
    );

    // post the event to the queue
    CGEventPost(kCGHIDEventTap, event);

    CFRelease(event); // free the event
  }

#endif

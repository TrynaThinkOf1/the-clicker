#ifndef MACOS_MOUSE_H
#define MACOS_MOUSE_H

#include <ApplicationServices/ApplicationServices.h> // MacOS Quartz Event Services

/// Move the mouse cursor to a position on the screen
static void move(int x, int y) {
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

#endif /* MACOS_MOUSE_H */
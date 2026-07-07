#include "macos/mouse/mouse.h"

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


CGPoint getCursorLocation() {
  CGEventRef event = CGEventCreate(NULL); // create an event representing the current state
  CGPoint location = CGEventGetUnflippedLocation(event); // get the location of said event

  CFRelease(event); // free the event

  return location;
}


void clickMouseDown(ClickType type) {
  if (CGEventSourceButtonState(kCGEventSourceStateHIDSystemState, type)) return; // button already down
  
  CGEventRef event = CGEventCreateMouseEvent(
    NULL, // nullable source of event
    kCGEventLeftMouseDown, // type of event // TODO: Fix this
    getCursorLocation(), // click in the current position
    kCGMouseButtonLeft // type of click
  );
}

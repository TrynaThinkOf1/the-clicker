#include <stdio.h>
#include "parse_int.h"

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
#else
  #error "Unknown Operating System"
#endif



int main(int argc, char** argv) {
    /*
    // Left button down at 250x250
    CGEventRef click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown,
        CGPointMake(250, 250),
        kCGMouseButtonLeft
    );
    // Left button up at 250x250
    CGEventRef click1_up = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseUp,
        CGPointMake(250, 250),
        kCGMouseButtonLeft
    );
    // Now, execute these events with an interval to make them noticeable
    CGEventPost(kCGHIDEventTap, move1);
    sleep(1);
    CGEventPost(kCGHIDEventTap, move2);
    sleep(1);
    CGEventPost(kCGHIDEventTap, click1_down);
    CGEventPost(kCGHIDEventTap, click1_up);
    // Release the events
    CFRelease(click1_up);
    CFRelease(click1_down);
    CFRelease(move2);
    CFRelease(move1);
        return 0;*/

  //move(0, 0);
  printf("str: '%s'\tint: %i\n", argv[1], parse_int(argv[1]));

  return 0;
}

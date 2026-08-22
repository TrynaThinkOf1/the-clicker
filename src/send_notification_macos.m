#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "graphics/sendNotification.h"

// Define the Delegate Class
// We need a class to handle the "shouldPresent" logic.
@interface NotificationDelegate : NSObject <NSUserNotificationCenterDelegate>
@end

@implementation NotificationDelegate
// This method is called by the system to ask: "Should I show this notification?"
// We return YES to force it to show, even if our app is active.
- (BOOL)userNotificationCenter:(NSUserNotificationCenter *)center 
       shouldPresentNotification:(NSUserNotification *)notification {
    return YES;
}
@end

void send_notification(const char *title, const char *body, void *user_data) {

    // 1. Create the notification object
    NSUserNotification *notification = [[NSUserNotification alloc] init];
    notification.title = [NSString stringWithUTF8String:title];
    notification.informativeText = [NSString stringWithUTF8String:body];
    notification.soundName = NSUserNotificationDefaultSoundName;

    // 2. CRITICAL FIX: Use a STATIC delegate.
    // If we make this a local variable, it gets destroyed when this function ends.
    // The system needs the delegate to exist LONGER than this function call.
    static NotificationDelegate *delegate = nil;
    
    // Only create it once, then reuse it forever.
    if (!delegate) {
        delegate = [NotificationDelegate new];
    }

    // 3. Assign the delegate to the center
    NSUserNotificationCenter *center = [NSUserNotificationCenter defaultUserNotificationCenter];
    [center setDelegate:delegate];

    // 4. Deliver the notification
    [center deliverNotification:notification];
}   
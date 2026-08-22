/*
 * define macros to check the os and if its not macos then include sendNotification.h and define the function
 */

#if !defined(__APPLE__) && !defined(__MACH__)

  #include <string.h>

  #include <gtk/gtk.h>

  #include "graphics/state.h"
  #include "graphics/sendNotification.h"

  void send_notification(const char *title, const char *body, void* user_data) {
    GtkApplication* app = (GtkApplication*)user_data;
    
    GNotification* noti = g_notification_new(title);
    g_notification_set_body(noti, body);
    g_notification_set_priority(noti, G_NOTIFICATION_PRIORITY_HIGH);

    const int tlen = strlen(title);
    const int blen = strlen(body);

    char id[(tlen / 2) + (blen / 2) + 2]; // + 1 for '-' + 1 for NUL
    strlcat(id, title, tlen / 2);
    id[tlen / 2] = '-';
    strlcat(id, body, blen / 2);
    id[(tlen / 2) + (blen / 2) + 2] = 0;
    
    g_application_send_notification(app, id, noti);

    g_object_unref(noti);
  }

#endif
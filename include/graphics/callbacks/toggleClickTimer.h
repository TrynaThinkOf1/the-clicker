#ifndef TOGGLECLICKTIMER_H
#define TOGGLECLICKTIMER_H

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/sendNotification.h"
#include "linux/macro_storage.h"
#include "debug_tests.h"


static void toggleClickTimer(GtkWidget* button, gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;

  long wait_in_ms =
    (gtk_spin_button_get_value_as_int(state->mins_spinbtn) * 60 * 1000)
    + (gtk_spin_button_get_value_as_int(state->secs_spinbtn) * 1000)
    + gtk_spin_button_get_value_as_int(state->ms_spinbtn);

  if (wait_in_ms <= 0) {
    // GtkAlertDialog* dialog = gtk_alert_dialog_new("Invalid Wait Time");
    // gtk_alert_dialog_set_detail(dialog, "Timer must be more than 0ms between clicks.");
    // gtk_alert_dialog_show(dialog, state->main_window);

    // GNotification* noti = g_notification_new("Invalid Wait Time");
    // g_notification_set_body(noti, "Timer must be for more than 0ms between clicks.");
    // g_notification_set_priority(noti, G_NOTIFICATION_PRIORITY_HIGH);
    
    // g_application_send_notification(G_APPLICATION(state->app), "click-timer-invalid-wait-time", noti);

    // g_object_unref(noti);

    send_notification("Invalid Wait Time", "Timer must be for more than 0ms between clicks", state->app);
  }

  CLICKER_ASSERT(wait_in_ms > 0, "Click Timer Wait is less than or equal to 0ms!");

  // TODO: Implement the thread adder
}

#endif /* TOGGLECLICKTIMER_H */
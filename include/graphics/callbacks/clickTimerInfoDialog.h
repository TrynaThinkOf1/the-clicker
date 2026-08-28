#ifndef CLICKTIMERINFODIALOG_H
#define CLICKTIMERINFODIALOG_H

#include <gtk/gtk.h>

#include "graphics/state.h"

static void clickTimerInfoDialog(GtkWidget* button, gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;
  
  GtkAlertDialog* dialog = gtk_alert_dialog_new("\nThe Click Timer");
  gtk_alert_dialog_set_detail(dialog,
    "The Click Timer serves very basic autoclicker functionality.\n"
    "Load the timer with Minutes/Seconds/Milliseconds, then select\n"
    "a click-type from the drop down menu. Once you click Start, a\n"
    "new thread will constantly execute that type of click every period\n"
    "of time set in the timer until you click the Stop button."
  );

  const char* buttons[] = {"Ok", NULL};
  gtk_alert_dialog_set_buttons (dialog, buttons);
  gtk_alert_dialog_set_cancel_button (dialog, 0); // make the cancel button an Ok button instead
  
  gtk_alert_dialog_show(dialog, GTK_WINDOW(state->main_window));
}

#endif /* CLICKTIMERINFODIALOG_H */
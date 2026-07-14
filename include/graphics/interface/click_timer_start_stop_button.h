#ifndef INTERFACE_CLICK_TIMER_START_BUTTON_H
#define INTERFACE_CLICK_TIMER_START_BUTTON_H

#include <gtk/gtk.h>

#include "graphics/callbacks/startStopClickTimer.h"


static void interface_createStartStopButton(GtkWidget* grid) {
  // create the button
  GtkWidget* button = gtk_button_new_with_label("Start");
  //

  // create the signal handlers for when input is added
  g_signal_connect(button, "clicked", G_CALLBACK(callback_startStopClickTimer), NULL);
  //

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 6, 1);
  //

  // add style classes for all labels and entries
  gtk_widget_add_css_class(button, "click-timer-start-stop-button");
  //
}

#endif /* INTERFACE_CLICK_TIMER_START_BUTTON_H */
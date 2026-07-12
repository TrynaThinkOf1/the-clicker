#ifndef INTERFACE_CLICK_TIMER_FUNC_SELECTOR_H
#define INTERFACE_CLICK_TIMER_FUNC_SELECTOR_H

#include <gtk/gtk.h>

#include "graphics/callbacks/loadGlobalFunc.h"


static void interface_createFunctionSelector(GtkWidget* grid) {
  // create the drop down menu
  const char* items[] = {
    "Left Click",
    "Right Click",
    "Left Double-Click",
    "Right Double-Click",
    NULL
  }; // items to be displayed on the drop down
  GtkWidget* selector = gtk_drop_down_new_from_strings(items);
  gtk_drop_down_set_selected(selector, 0); // default to Left Click
  //

  // create the signal handlers for when input is added
  g_signal_connect(selector, "activate", G_CALLBACK(callback_loadGlobalFunc), NULL);
  //

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), selector, 0, 2, 3, 1);
  //

  // add style classes for all labels and entries
  //gtk_widget_add_css_class(mins_label, "click-timer-label");
  //
}

#endif /* INTERFACE_CLICK_TIMER_FUNC_SELECTOR_H */
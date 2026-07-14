#ifndef INTERFACE_CLICK_TIMER_COORDS_H
#define INTERFACE_CLICK_TIMER_COORDS_H

#include <gtk/gtk.h>

#include "graphics/callbacks/loadGlobalCoords.h"
#include "graphics/callbacks/preventNonDigitInput.h"
#include "graphics/globals.h"


static void interface_createCoordEntries(GtkWidget* grid) {
  // create the actual entries for coords
  GtkWidget* x_entry = gtk_entry_new();
  GtkWidget* y_entry = gtk_entry_new();

   // load them into the global state coord holder
  coords.xentry = x_entry;
  coords.yentry = y_entry;
  //

  // only allow a certain # of digits
  gtk_entry_set_max_length(x_entry, 4); // maximum of 9999 for x axis
  gtk_entry_set_max_length(y_entry, 4); // maximum of 9999 for y axis
  //

  // placeholder text
  gtk_entry_set_placeholder_text(x_entry, "");
  gtk_entry_set_placeholder_text(y_entry, "");
  //

  // add labels for the units of time for each
  GtkWidget* label = gtk_label_new("(x,y) for click | blank for current position");
  //

  // create the signal handlers for when input is added
  g_signal_connect(G_OBJECT(x_entry), "changed", G_CALLBACK(callback_loadGlobalCoords), NULL);
  g_signal_connect(G_OBJECT(y_entry), "changed", G_CALLBACK(callback_loadGlobalCoords), NULL);

  GtkEditable *x_delegate = gtk_editable_get_delegate(GTK_EDITABLE(x_entry));
  g_signal_connect(x_delegate, "insert-text", G_CALLBACK(callback_preventNonDigitInput), NULL);
  GtkEditable *y_delegate = gtk_editable_get_delegate(GTK_EDITABLE(y_entry));
  g_signal_connect(y_delegate, "insert-text", G_CALLBACK(callback_preventNonDigitInput), NULL);
  //

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 4, 1); // 0 0 2 1

  gtk_grid_attach(GTK_GRID(grid), x_entry, 0, 3, 2, 1); // 0 1 2 1
  gtk_grid_attach(GTK_GRID(grid), y_entry, 2, 3, 2, 1); // 3 1 2 1
  //

  // add style classes for all labels and entries
  gtk_widget_add_css_class(label, "click-timer-label");

  gtk_widget_add_css_class(x_entry, "click-timer-entry");
  gtk_widget_add_css_class(y_entry, "click-timer-entry");

  gtk_editable_set_max_width_chars(GTK_EDITABLE(x_entry), 12);
  gtk_editable_set_max_width_chars(GTK_EDITABLE(y_entry), 12);
  //
}

#endif /* INTERFACE_CLICK_TIMER_COORDS_H */

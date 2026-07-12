#ifndef INTERFACE_CLICK_TIMER_ENTRIES_H
#define INTERFACE_CLICK_TIMER_ENTRIES_H

#include <gtk/gtk.h>

#include "graphics/callbacks/loadGlobalSleepMS.h"
#include "graphics/callbacks/preventNonDigitInput.h"


static void interface_createTimeEntries(GtkWidget* grid) {
  // create the actual entries for times
  GtkWidget* mins_entry = gtk_entry_new();
  GtkWidget* secs_entry = gtk_entry_new();
  GtkWidget* ms_entry = gtk_entry_new();

   // load them into the global state holder
  holder.e1 = mins_entry;
  holder.e2 = secs_entry;
  holder.e3 = ms_entry;
  //

  // only allow a certain # of digits
  gtk_entry_set_max_length(mins_entry, 3); // maximum of 999 minutes
  gtk_entry_set_max_length(secs_entry, 2); // maximum of 99 seconds, then it will overflow into minutes
  gtk_entry_set_max_length(ms_entry, 3); // maximum of 999 ms, then it overflows into seconds
  //

  // placeholder text
  gtk_entry_set_placeholder_text(mins_entry, "0");
  gtk_entry_set_placeholder_text(secs_entry, "0");
  gtk_entry_set_placeholder_text(ms_entry, "0");
  //

  // add labels for the units of time for each
  GtkWidget* mins_label = gtk_label_new("Minutes");
  GtkWidget* secs_label = gtk_label_new("Seconds");
  GtkWidget* ms_label = gtk_label_new("Milliseconds");
  //

  // create the signal handlers for when input is added
  g_signal_connect(G_OBJECT(mins_entry), "changed", G_CALLBACK(callback_loadGlobalSleepMS), NULL);
  g_signal_connect(G_OBJECT(secs_entry), "changed", G_CALLBACK(callback_loadGlobalSleepMS), NULL);
  g_signal_connect(G_OBJECT(ms_entry), "changed", G_CALLBACK(callback_loadGlobalSleepMS), NULL);

  GtkEditable *mins_delegate = gtk_editable_get_delegate(GTK_EDITABLE(mins_entry));
  g_signal_connect(mins_delegate, "insert-text", G_CALLBACK(callback_preventNonDigitInput), NULL);
  GtkEditable *secs_delegate = gtk_editable_get_delegate(GTK_EDITABLE(secs_entry));
  g_signal_connect(secs_delegate, "insert-text", G_CALLBACK(callback_preventNonDigitInput), NULL);
  GtkEditable *ms_delegate = gtk_editable_get_delegate(GTK_EDITABLE(ms_entry));
  g_signal_connect(ms_delegate, "insert-text", G_CALLBACK(callback_preventNonDigitInput), NULL);
  //

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), mins_label, 0, 0, 2, 1); // 0 0 2 1
  gtk_grid_attach(GTK_GRID(grid), secs_label, 2, 0, 2, 1); // 3 0 2 1
  gtk_grid_attach(GTK_GRID(grid), ms_label, 4, 0, 2, 1); // 6 0 2 1

  gtk_grid_attach(GTK_GRID(grid), mins_entry, 0, 1, 2, 1); // 0 1 2 1
  gtk_grid_attach(GTK_GRID(grid), secs_entry, 2, 1, 2, 1); // 3 1 2 1
  gtk_grid_attach(GTK_GRID(grid), ms_entry, 4, 1, 2, 1); // 6 1 2 1
  //

  // add style classes for all labels and entries
  gtk_widget_add_css_class(mins_label, "click-timer-label");
  gtk_widget_add_css_class(secs_label, "click-timer-label");
  gtk_widget_add_css_class(ms_label, "click-timer-label");

  gtk_widget_add_css_class(mins_entry, "click-timer-entry");
  gtk_widget_add_css_class(secs_entry, "click-timer-entry");
  gtk_widget_add_css_class(ms_entry, "click-timer-entry");

  gtk_editable_set_max_width_chars(GTK_EDITABLE(mins_entry), 12);
  gtk_editable_set_max_width_chars(GTK_EDITABLE(secs_entry), 12);
  gtk_editable_set_max_width_chars(GTK_EDITABLE(ms_entry), 12);
  //
}

#endif /* INTERFACE_CLICK_TIMER_ENTRIES_H */

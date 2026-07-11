#ifndef INTERFACE_TIME_ENTRIES_H
#define INTERFACE_TIME_ENTRIES_H

#include <string.h>

#include <gtk/gtk.h>

#include "graphics/globals.h"
#include "parse_int.h"


struct entry_holder {
  GtkWidget* e1;
  GtkWidget* e2;
  GtkWidget* e3;
};

struct entry_holder holder = {0};

/// function to ensure that the global sleep timer for basic click timer is active
static void load_global_sleep_ms(GtkWidget* widget, gpointer user_data) {
  char* mins_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e1));
  int mins = parse_int(mins_text, strlen(mins_text) - 1);
  char* secs_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e2));
  int secs = parse_int(secs_text, strlen(secs_text) - 1);
  char* ms_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e3));
  int ms = parse_int(ms_text, strlen(ms_text) - 1);

  SLEEP_MS = (mins * 60 * 1000) + (secs * 1000) + ms;
}

/// disallow all non-digit characters in the buffer
/// IMMA BE SO FR, I HAVE NO IDEA HOW THIS FUNCTION WORKS
static void prevent_nd_chars(GtkEditable* editable, const char* text, int length, int* position, gpointer user_data) {
  bool nd;
  for (int i = 0; i < length; i++) {
    if (text[i] < 48 || text[i] > 57) {
      nd = true;
      break;
    }
  }

  if (nd) {
    GString *filtered = g_string_new(NULL);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 48 && text[i] <= 57) {
            g_string_append_c(filtered, text[i]);
        }
    }

    g_signal_stop_emission_by_name(editable, "insert-text"); // stop the original signal

    g_signal_handlers_block_by_func(editable, prevent_nd_chars, user_data); // block the signal to prevent recursion while inserting manually
    gtk_editable_insert_text(editable, filtered->str, filtered->len, position); // insert the clean text at the current position
    g_signal_handlers_unblock_by_func(editable, prevent_nd_chars, user_data); // unblock the signal
  }
}


static void interface_createTimeEntries(GtkWidget* grid) {
  // create the actual entries for times
  GtkWidget* mins_entry = gtk_entry_new();
  GtkWidget* secs_entry = gtk_entry_new();
  GtkWidget* ms_entry = gtk_entry_new();

  // TODO: This could be a potential stack issue for below
  holder.e1 = mins_entry;
  holder.e2 = secs_entry;
  holder.e3 = ms_entry;

  // only allow a certain # of digits
  gtk_entry_set_max_length(mins_entry, 3); // maximum of 999 minutes
  gtk_entry_set_max_length(secs_entry, 2); // maximum of 99 seconds, then it will overflow into minutes
  gtk_entry_set_max_length(ms_entry, 3); // maximum of 999 ms, then it overflows into seconds

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
  g_signal_connect(G_OBJECT(mins_entry), "changed", G_CALLBACK(load_global_sleep_ms), NULL);
  g_signal_connect(G_OBJECT(secs_entry), "changed", G_CALLBACK(load_global_sleep_ms), NULL);
  g_signal_connect(G_OBJECT(ms_entry), "changed", G_CALLBACK(load_global_sleep_ms), NULL);

  GtkEditable *mins_delegate = gtk_editable_get_delegate(GTK_EDITABLE(mins_entry));
  g_signal_connect(mins_delegate, "insert-text", G_CALLBACK(prevent_nd_chars), NULL);
  GtkEditable *secs_delegate = gtk_editable_get_delegate(GTK_EDITABLE(secs_entry));
  g_signal_connect(secs_delegate, "insert-text", G_CALLBACK(prevent_nd_chars), NULL);
  GtkEditable *ms_delegate = gtk_editable_get_delegate(GTK_EDITABLE(ms_entry));
  g_signal_connect(ms_delegate, "insert-text", G_CALLBACK(prevent_nd_chars), NULL);
  //

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), mins_label, 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), secs_label, 3, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), ms_label, 6, 0, 2, 1);

  gtk_grid_attach(GTK_GRID(grid), mins_entry, 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), secs_entry, 3, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), ms_entry, 6, 1, 2, 1);
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

#endif /* INTERFACE_TIME_ENTRIES_H */

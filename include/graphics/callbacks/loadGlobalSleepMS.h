#ifndef CALLBACKS_LOADGLOBALSLEEPMS_H
#define CALLBACKS_LOADGLOBALSLEEPMS_H

#include <string.h>

#include <gtk/gtk.h>

#include "graphics/globals.h"
#include "parse_int.h"

/// function to ensure that the global sleep timer for basic click timer is active
static void callback_loadGlobalSleepMS(GtkWidget* widget, gpointer user_data) {
  char* mins_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e1));
  int mins = parse_int(mins_text, strlen(mins_text) - 1);
  char* secs_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e2));
  int secs = parse_int(secs_text, strlen(secs_text) - 1);
  char* ms_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(holder.e3));
  int ms = parse_int(ms_text, strlen(ms_text) - 1);

  SLEEP_MS = (mins * 60 * 1000) + (secs * 1000) + ms;
}

#endif /* CALLBACKS_LOADGLOBALSLEEPMS_H */
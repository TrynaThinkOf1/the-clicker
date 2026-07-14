#ifndef CALLBACKS_LOADGLOBALCOORDS_H
#define CALLBACKS_LOADGLOBALCOORDS_H

#include <string.h>

#include <gtk/gtk.h>

#include "graphics/globals.h"
#include "parse_int.h"

/// function to ensure that the global coordinates for basic click timer is active
static void callback_loadGlobalCoords(GtkWidget* widget, gpointer user_data) {
  char* x_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(coords.xentry));
  CLICK_X = (strlen(x_text) > 0 ? parse_int(x_text, strlen(x_text) - 1) : -1);
  
  char* y_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(coords.yentry));
  CLICK_Y = (strlen(y_text) > 0 ? parse_int(y_text, strlen(y_text) - 1) : -1);
}

#endif /* CALLBACKS_LOADGLOBALCOORDS_H */
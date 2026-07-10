#ifndef INTERFACE_GRID_BUTTONS_H
#define INTERFACE_GRID_BUTTONS_H

#include <gtk/gtk.h>

#include "graphics/callbacks/mover.h"


static void layer(GtkWidget* widget, gpointer user_data) {
  GtkWidget* entry = (GtkWidget*)user_data;
  GtkEntryBuffer* buffer = gtk_entry_get_buffer(entry);
  const char* buf = gtk_entry_buffer_get_text(buffer);
  g_print("buffer: `%s`\n", buf);
  callback_mover(widget, (gpointer)buf);
}

static void add_grid_buttons(GtkWidget* window) {
  GtkWidget* grid = gtk_grid_new(); // create a grid object

  gtk_window_set_child(GTK_WINDOW(window), grid); // add the grid to the window

  GtkWidget* entry = gtk_entry_new();
  gtk_entry_set_max_length(entry, 9);

  gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 5, 1);

  GtkWidget* moveButton = gtk_button_new_with_label("Move Cursor");
  g_signal_connect(moveButton, "clicked", G_CALLBACK(layer), (gpointer)entry);

  gtk_grid_attach(GTK_GRID(grid), moveButton, 6, 0, 2, 1);
}

#endif /* INTERFACE_GRID_BUTTONS_H */
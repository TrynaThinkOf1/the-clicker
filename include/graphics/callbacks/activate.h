#ifndef CALLBACKS_ACTIVATE_H
#define CALLBACKS_ACTIVATE_H

#include <gtk/gtk.h>

#include "graphics/interface/grid_buttons.h"

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget* window;
  
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "The Clicker");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

  add_grid_buttons(window);
  
  gtk_window_present(GTK_WINDOW(window));
}

#endif /* CALLBACKS_ACTIVATE_H */
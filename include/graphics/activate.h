#ifndef ACTIVATE_H
#define ACTIVATE_H

#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget* window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "The Clicker");

  gtk_window_present(GTK_WINDOW(window));
}

#endif /* ACTIVATE_H */
#ifndef CLOSE_REQUEST_H
#define CLOSE_REQUEST_H

#include <gtk/gtk.h>

static void close_request(GtkApplicationWindow* window, gpointer user_data) {
  g_application_quit(G_APPLICATION(user_data));
}
#endif /* CLOSE_REQUEST_H */
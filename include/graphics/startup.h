#ifndef STARTUP_H
#define STARTUP_H

#include <gtk/gtk.h>

#include "graphics/helpMenu.h"

static void startup(GtkApplication* app, gpointer user_data) {
  createHelpMenu(app);
}

#endif /* STARTUP_H */
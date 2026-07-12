#ifndef CALLBACKS_LOADGLOBALFUNC_H
#define CALLBACKS_LOADGLOBALFUNC_H

#include <gtk/gtk.h>

#include "builtins.h"
#include "graphics/globals.h"

static void callback_loadGlobalFunc(GtkWidget* widget, gpointer user_data) {
  guint pos = gtk_drop_down_get_selected(widget);

  switch (pos) {
    case 0:
      CLICK_FUNC = leftClick;
      break;
    case 1:
      CLICK_FUNC = rightClick;
      break;
    case 2:
      CLICK_FUNC = leftDoubleClick;
      break;
    case 3:
      CLICK_FUNC = rightDoubleClick;
      break;
    case GTK_INVALID_LIST_POSITION:
      break;
  }
}

#endif /* CALLBACKS_LOADGLOBALFUNC_H */
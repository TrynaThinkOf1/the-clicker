#ifndef LOADCLICKTIMERFUNC_H
#define LOADCLICKTIMERFUNC_H

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "builtins.h"

static void loadClickTimerFunc(GtkWidget* dropdown, gpointer user_data) {
  ClickTimerState* state = (ClickTimerState*)user_data;

  guint pos = gtk_drop_down_get_selected(dropdown);

  switch (pos) {
    case 0:
      state->click_func = leftClick;
      break;
    case 1:
      state->click_func = rightClick;
      break;
    case 2:
      state->click_func = leftDoubleClick;
      break;
    case 3:
      state->click_func = rightDoubleClick;
      break;
    case GTK_INVALID_LIST_POSITION:
      break;
  }
}

#endif /* LOADCLICKTIMERFUNC_H */
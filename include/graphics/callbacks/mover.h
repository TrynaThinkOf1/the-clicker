#ifndef CALLBACKS_MOVER_H
#define CALLBACKS_MOVER_H

#include <string.h>

#include <gtk/gtk.h>

#include "builtins.h"
#include "parse_int.h"

static void callback_mover(GtkWidget* widget, gpointer user_data) {
  const char* data = (const char*)user_data;
  int len = strlen(data);
  
  int len_first, len_second, middex = 0;

  while (data[middex] != ',' && middex < len) {
    middex++;
    len_first++;
  }

  len_second = len - len_first - 1;

  int x = parse_int(data, len_first - 1);
  int y = parse_int(&data[middex + 1], len_second - 1);

  g_print("User Data: `%s`\n", data);
  g_print("(%i, %i)\n", x, y);

  moveCursor(x, y);
}

#endif /* CALLBACKS_MOVER_H */
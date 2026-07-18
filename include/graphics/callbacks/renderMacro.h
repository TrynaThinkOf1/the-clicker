#ifndef CALLBACKS_RENDERMACRO_H
#define CALLBACKS_RENDERMACRO_H

#include <string.h>

#include <gtk/gtk.h>

#include "graphics/globals.h"
#include "macros.h"
#include "builtins.h"

static void renderGlobalMacro(GtkWidget* macro_grid) {
  macro_part* part = current_macro->first;
  while (part != NULL) {
    char buffer[100];

    if (part->func == moveCursor) {
      strcpy(buffer, "moveCursor");
    } else if (part->func == leftClick) {
      strcpy(buffer, "leftClick");
    } else if (part->func == rightClick) {
      strcpy(buffer, "rightClick");
    } else if (part->func == leftDoubleClick) {
      strcpy(buffer, "leftDoubleClick");
    } else if (part->func == rightDoubleClick) {
      strcpy(buffer, "rightDoubleClick");
    } else if (part->func == sleep_m) {
      strcpy(buffer, "sleep_m");
    }

    if (part->func != sleep_m) {
      sprintf(&buffer[strlen(buffer)], "(%i, %i)", part->x, part->y);
    } else {
      sprintf(&buffer[strlen(buffer)], "(%i)", part->x);
    }
    
    GtkWidget* label = gtk_label_new(buffer);

    gtk_grid_attach(GTK_GRID(macro_grid), label, 0, NEXT_Y_POSITION, 3, 1);
    NEXT_Y_POSITION++;
    
    gtk_widget_add_css_class(label, "macro-label");
    
    part = part->next;
  }
}

#endif /* CALLBACKS_RENDERMACRO_H */
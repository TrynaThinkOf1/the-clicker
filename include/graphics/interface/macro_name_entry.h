#ifndef INTERFACE_MACRO_NAME_ENTRY_H
#define INTERFACE_MACRO_NAME_ENTRY_H

#include <gtk/gtk.h>

#include "graphics/globals.h"


static void interface_createNameEntry(GtkWidget* grid) {
  // define the global name entry
  macro_name_entry = gtk_entry_new();
  //

  // only allow a certain # of digits
  gtk_entry_set_max_length(macro_name_entry, 20); // maximum of 20 characters for a macro name
  //

  // placeholder text
  gtk_entry_set_placeholder_text(macro_name_entry, "Name of Macro");
  //

  // no signal handlers necessary

  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), macro_name_entry, 0, 0, 3, 1);
  //

  // add style classes for all labels and entries
  gtk_widget_add_css_class(macro_name_entry, "macro-box-entry");

  gtk_editable_set_max_width_chars(GTK_EDITABLE(macro_name_entry), 29);
  //
}

#endif /* INTERFACE_MACRO_NAME_ENTRY_H */
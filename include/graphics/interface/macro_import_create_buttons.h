#ifndef INTERFACE_MACRO_IMPORT_CREATE_BUTTONS_H
#define INTERFACE_MACRO_IMPORT_CREATE_BUTTONS_H

#include <gtk/gtk.h>

#include "graphics/callbacks/importGlobalMacro.h"


static void interface_createImportCreateButtons(GtkWidget* grid) {
  // create the button
  GtkWidget* create_button = gtk_button_new();
  GtkWidget* import_button = gtk_button_new();

  GtkWidget* plus_icon = gtk_image_new_from_resource("/assets/include/graphics/assets/plus_icon.png");
  GtkWidget* import_icon = gtk_image_new_from_resource("/assets/include/graphics/assets/import_icon.png");
  gtk_image_set_pixel_size(GTK_IMAGE(plus_icon), 32); // forces render at 32x32
  gtk_image_set_pixel_size(GTK_IMAGE(import_icon), 32);
  gtk_button_set_child(GTK_BUTTON(create_button), plus_icon); // add the icon to the button
  gtk_button_set_child(GTK_BUTTON(import_button), import_icon);
  //

  // create the signal handlers for when input is added
  //g_signal_connect(create_button, "clicked", G_CALLBACK(callback_createGlobalMacro), NULL);
  g_signal_connect(import_button, "clicked", G_CALLBACK(callback_importGlobalMacro), NULL);
  //

  // add tooltips
  gtk_widget_set_tooltip_text(create_button, "Create a new Macro");
  gtk_widget_set_tooltip_text(import_button, "Import a saved Macro");
  
  // render the entries and labels
  gtk_grid_attach(GTK_GRID(grid), create_button, 4, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), import_button, 5, 0, 1, 1);
  //

  // add style classes for all labels and entries
  gtk_widget_add_css_class(create_button, "macro-button");
  gtk_widget_add_css_class(import_button, "macro-button");
  //
}

#endif /* INTERFACE_MACRO_IMPORT_CREATE_BUTTONS_H */
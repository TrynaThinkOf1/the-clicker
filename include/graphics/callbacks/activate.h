#ifndef CALLBACKS_ACTIVATE_H
#define CALLBACKS_ACTIVATE_H

#include <gtk/gtk.h>
#include "resources.h"

#include "graphics/styling/css_provider.h"
//
#include "graphics/interface/click_timer_entries.h"
#include "graphics/interface/click_timer_coords.h"
#include "graphics/interface/click_timer_func_selector.h"
#include "graphics/interface/click_timer_start_stop_button.h"
//
#include "graphics/interface/macro_name_entry.h"
#include "graphics/interface/macro_import_create_buttons.h"


void init_resources() {
  GResource *resource = resources_get_resource(); // generated in resources.c during build process
  g_resources_register(resource);
}

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget* window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "The Clicker");
  gtk_window_set_default_size(GTK_WINDOW(window), 405, 750);

  gtk_widget_add_css_class(window, "window"); // create root window styles class

  GtkWidget* root_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  // create click-timer box
  GtkWidget* click_timer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(click_timer_box, GTK_ALIGN_START);
  gtk_widget_set_valign(click_timer_box, GTK_ALIGN_START);

   // grid for storing elements
  GtkWidget* timer_entry_grid = gtk_grid_new();

  interface_createTimeEntries(timer_entry_grid); // add the inputs for mins, secs, ms
  interface_createCoordEntries(timer_entry_grid); // entries for the coordinates of the click
  interface_createFunctionSelector(timer_entry_grid); // add the dropdown menu for selecting click function
  interface_createStartStopButton(timer_entry_grid);

   // styling
  gtk_widget_add_css_class(click_timer_box, "click-timer-box"); // add a class to style the click timer box
  gtk_widget_set_overflow(click_timer_box, GTK_OVERFLOW_HIDDEN); // prevent corner clipping, hard to explain
  
  gtk_box_append(GTK_BOX(click_timer_box), timer_entry_grid);
  //

  // create macro handling box
  GtkWidget* macro_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(macro_box, GTK_ALIGN_START);
  gtk_widget_set_valign(macro_box, GTK_ALIGN_START);

   // grid for storing elements
  GtkWidget* macro_box_grid = gtk_grid_new();

  interface_createNameEntry(macro_box_grid);
  interface_createImportCreateButtons(macro_box_grid);
  
   // styling
  gtk_widget_add_css_class(macro_box, "macro-box"); // add a class to style the click timer box
  gtk_widget_set_overflow(macro_box, GTK_OVERFLOW_HIDDEN); // prevent corner clipping, hard to explain

  gtk_box_append(GTK_BOX(macro_box), macro_box_grid);
  // 

  gtk_box_append(GTK_BOX(root_box), click_timer_box);
  gtk_box_append(GTK_BOX(root_box), macro_box);
  gtk_window_set_child(GTK_WINDOW(window), root_box);
  

  // global styling
  styling_createCSS(); // create the styles
  //

  // about dialoge
   // TODO: Implement
  //

  gtk_window_present(GTK_WINDOW(window));
}

#endif /* CALLBACKS_ACTIVATE_H */

#ifndef CALLBACKS_ACTIVATE_H
#define CALLBACKS_ACTIVATE_H

#include <gtk/gtk.h>

#include "graphics/styling/css_provider.h"
#include "graphics/interface/click_timer_entries.h"
#include "graphics/interface/click_timer_func_selector.h"
#include "graphics/interface/click_timer_start_button.h"

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget* window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "The Clicker");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

  gtk_widget_add_css_class(window, "window"); // create root window styles class

  // create click-timer box
  GtkWidget* click_timer_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_halign(click_timer_box, GTK_ALIGN_START);
  gtk_widget_set_valign(click_timer_box, GTK_ALIGN_START);

   // grid for storing elements
  GtkWidget* timer_entry_grid = gtk_grid_new();
  GtkWidget* selector_and_start_grid = gtk_grid_new();

  interface_createTimeEntries(timer_entry_grid); // add the inputs for mins, secs, ms
  interface_createFunctionSelector(selector_and_start_grid); // add the dropdown menu for selecting click function
  interface_createStartButton(selector_and_start_grid);
  
  gtk_box_append(GTK_BOX(click_timer_box), timer_entry_grid);
  gtk_box_append(GTK_BOX(click_timer_box), selector_and_start_grid);
  gtk_window_set_child(GTK_WINDOW(window), click_timer_box);

   // styling
  gtk_widget_add_css_class(click_timer_box, "click-timer-box"); // add a class to style the click timer box
  gtk_widget_set_overflow(click_timer_box, GTK_OVERFLOW_HIDDEN); // prevent corner clipping, hard to explain
  //

  styling_createCSS(); // create the styles

  gtk_window_present(GTK_WINDOW(window));
}

#endif /* CALLBACKS_ACTIVATE_H */

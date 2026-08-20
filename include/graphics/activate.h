#ifndef ACTIVATE_H
#define ACTIVATE_H

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "gtk/gtkshortcut.h"

static void activate(GtkApplication* app, gpointer user_data) {
  // GtkWidget* main_window;

  // main_window = gtk_application_window_new(app);
  // gtk_window_set_title(GTK_WINDOW(main_window), "The Clicker");

  /*
   * Set up the click timer.
   * [HOURS ENTRY] [MINS ENTRY] [SECS ENTRY]
   * [X ENTRY][Y ENTRY][CLICK TYPE DROPDOWN]
   * [          START/STOP BUTTON          ]
   * Relies on a global state struct for everything
   */
  ClickTimerState* CT_STATE = g_new0(ClickTimerState, 1); // deliberatly leaked, actual pattern for GTK+

  /*GtkBuilder *builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/click_timer.ui");
  GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "main_grid"));
  CT_STATE->mins_spinbtn = GTK_WIDGET(gtk_builder_get_object(builder, "mins_entry"));
  CT_STATE->secs_spinbtn = GTK_WIDGET(gtk_builder_get_object(builder, "secs_entry"));
  CT_STATE->ms_spinbtn = GTK_WIDGET(gtk_builder_get_object(builder, "ms_entry"));
  CT_STATE->start_stop_button = GTK_WIDGET(gtk_builder_get_object(builder, "start_stop_button"));*/

  /*
   * GtkCssProvider *provider = gtk_css_provider_new();
   gtk_css_provider_load_from_resource(provider, "/com/yourapp/graphics/style.css");
   gtk_style_context_add_provider_for_display(
       gdk_display_get_default(),
       GTK_STYLE_PROVIDER(provider),
       GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
   g_object_unref(provider);
   */

  GtkBuilder* main_window_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/main_window.ui");
  GtkApplicationWindow* window = GTK_APPLICATION_WINDOW(gtk_builder_get_object(main_window_builder, "main_window"));
  gtk_window_set_application(GTK_WINDOW(window), app);

  GtkBuilder* click_timer_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/click_timer.ui");
  GtkWidget* click_timer_grid = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_timer_grid"));

  gtk_window_set_child(GTK_WINDOW(window), GTK_GRID(click_timer_grid));
  
  gtk_window_present(GTK_WINDOW(window));
  
  g_object_unref(main_window_builder); // were done with builders, its been loaded into GTK's heap
  g_object_unref(click_timer_builder);
}

#endif /* ACTIVATE_H */
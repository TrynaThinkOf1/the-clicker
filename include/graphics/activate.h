#ifndef ACTIVATE_H
#define ACTIVATE_H

#include <stdbool.h>

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/close_request.h"
#include "graphics/callbacks/createClickTimer.h"
#include "graphics/callbacks/createMacroLoader.h"
#include "graphics/callbacks/macroLoaderInfoDialog.h"
#include "graphics/callbacks/clickTimerInfoDialog.h"
#include "graphics/callbacks/toggleClickTimer.h"
#include "graphics/callbacks/numberOnlyEntry.h"

static void activate(GtkApplication* app, gpointer user_data) {
  /* MAIN WINDOW */
  GtkBuilder* main_window_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/main_window.ui");
  GtkApplicationWindow* window = GTK_APPLICATION_WINDOW(gtk_builder_get_object(main_window_builder, "main_window"));
  g_signal_connect(window, "close-request", G_CALLBACK(close_request), app);
  gtk_window_set_application(GTK_WINDOW(window), app);

  GtkWidget* container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  /* */

  createClickTimer(app, window, container);

  createMacroLoader(app, window, container);

  /* STYLE */
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_resource(provider, "/com/the-clicker/graphics/styles/style.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
  /* */
  
  gtk_window_set_child(GTK_WINDOW(window), container);
  gtk_window_present(GTK_WINDOW(window));
  //gtk_window_present_with_time(GTK_WINDOW(window), GDK_CURRENT_TIME); // draw focus immediately

  // we're done with builders, its been loaded into GTK's heap
  g_object_unref(main_window_builder);
}

#endif /* ACTIVATE_H */
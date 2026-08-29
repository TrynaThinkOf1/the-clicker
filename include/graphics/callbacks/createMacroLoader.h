#ifndef CREATEMACROLOADER_H
#define CREATEMACROLOADER_H

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/callbacks/macroLoaderInfoDialog.h"

/* 
 *    Macro Editor (i)
 * [     MACRO NAME    ]
 * [ IMPORT ] [ CREATE ]
 * 
 * relies on global state struct
 */
static void createMacroLoader(GtkApplication* app, GtkWidget* window, GtkWidget* container) {
  GtkWidget* macro_loader_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(macro_loader_container, "click-timer-box");
  gtk_widget_set_overflow(macro_loader_container, GTK_OVERFLOW_HIDDEN); // make corners round

  GtkBuilder* macro_loader_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/macro_loader.ui");
  MacroEditorState* state = g_new0(MacroEditorState, 1); // deliberatly leaked, actual pattern for GTK+
  state->app = app;
  state->main_window = window;

  /*
   * Label and info button grid
   */
   GtkWidget* label_and_info_grid = GTK_WIDGET(gtk_builder_get_object(macro_loader_builder, "label_and_info_grid"));
   
   GtkWidget* macro_loader_info_button = GTK_WIDGET(gtk_builder_get_object(macro_loader_builder, "macro_loader_info_button"));
   g_signal_connect(macro_loader_info_button, "clicked", G_CALLBACK(macroLoaderInfoDialog), state);
   gtk_widget_set_cursor_from_name(macro_loader_info_button, "pointer"); // make the cursor a pointer on hover
 
   gtk_box_append(GTK_BOX(macro_loader_container), label_and_info_grid);

  GtkWidget* macro_loader_grid = gtk_builder_get_object(macro_loader_builder, "macro_loader_grid");
   
  gtk_box_append(macro_loader_container, macro_loader_grid);
  gtk_box_append(GTK_BOX(container), macro_loader_container);

  g_object_unref(macro_loader_builder);
}

#endif /* CREATEMACROLOADER_H */
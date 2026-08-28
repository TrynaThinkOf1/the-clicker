#ifndef ACTIVATE_H
#define ACTIVATE_H

#include <gtk/gtk.h>
#include <stdbool.h>

#include "graphics/state.h"
#include "graphics/callbacks/macroLoaderInfoDialog.h"
#include "graphics/callbacks/clickTimerInfoDialog.h"
#include "graphics/callbacks/toggleClickTimer.h"
#include "graphics/callbacks/numberOnlyEntry.h"
#include "gtk/gtkshortcut.h"

static void activate(GtkApplication* app, gpointer user_data) {

  /* MAIN WINDOW */
  GtkBuilder* main_window_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/main_window.ui");
  GtkApplicationWindow* window = GTK_APPLICATION_WINDOW(gtk_builder_get_object(main_window_builder, "main_window"));
  gtk_window_set_application(GTK_WINDOW(window), app);

  GtkWidget* container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  /* */

  /* CLICK TIMER
   *             Click Timer (i)
   * [HOURS ENTRY] [MINS ENTRY] [SECS ENTRY]
   * [X ENTRY][Y ENTRY][CLICK TYPE DROPDOWN]
   * [          START/STOP BUTTON          ]
   * Relies on a global state struct for everything
   */
  GtkWidget* click_timer_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(click_timer_container, "click-timer-box");
  gtk_widget_set_overflow(click_timer_container, GTK_OVERFLOW_HIDDEN); // make corners round
  
  GtkBuilder* click_timer_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/click_timer.ui");
  ClickTimerState* CT_STATE = g_new0(ClickTimerState, 1); // deliberatly leaked, actual pattern for GTK+
  CT_STATE->app = app;
  CT_STATE->main_window = window;
  CT_STATE->timer_active = false;
  CT_STATE->click_func = leftClick;

   /*
    * Label and info button grid
    */
    GtkWidget* label_and_info_grid = gtk_grid_new();
    gtk_widget_set_halign(label_and_info_grid, GTK_ALIGN_CENTER); // set the grid in the center of the box
    gtk_widget_set_valign(label_and_info_grid, GTK_ALIGN_CENTER); // set the grid in the center of the box
    
    GtkWidget* click_timer_label = gtk_label_new("Click Timer");
    gtk_widget_add_css_class(click_timer_label, "click-timer-label");
    
    GtkWidget* click_timer_info_button = gtk_button_new();
    g_signal_connect(click_timer_info_button, "clicked", G_CALLBACK(clickTimerInfoDialog), CT_STATE);
    gtk_widget_add_css_class(click_timer_info_button, "click-timer-info-button");
    gtk_widget_set_cursor_from_name(click_timer_info_button, "pointer"); // make the cursor a pointer on hover
    
    GtkWidget* info_icon = gtk_image_new_from_resource("/com/the-clicker/graphics/assets/info_icon.png");
    gtk_image_set_pixel_size(GTK_IMAGE(info_icon), 18);
    gtk_button_set_child(GTK_BUTTON(click_timer_info_button), info_icon); // add the icon to the button
  
    gtk_grid_attach(GTK_GRID(label_and_info_grid), click_timer_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(label_and_info_grid), gtk_label_new(" "), 1, 0, 1, 1); // spacer
    gtk_grid_attach(GTK_GRID(label_and_info_grid), click_timer_info_button, 2, 0, 1, 1);
    gtk_box_append(GTK_BOX(click_timer_container), label_and_info_grid);

  GtkWidget* click_timer_grid = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_timer_grid"));
  
  CT_STATE->mins_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "mins_spinbtn"));
  CT_STATE->secs_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "secs_spinbtn"));
  CT_STATE->ms_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "ms_spinbtn"));
  
  CT_STATE->x_coord_entry = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "x_coord_entry"));
  g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(CT_STATE->x_coord_entry)), "insert-text", G_CALLBACK(numberOnlyEntry), NULL);
  CT_STATE->y_coord_entry = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "y_coord_entry"));
  g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(CT_STATE->y_coord_entry)), "insert-text", G_CALLBACK(numberOnlyEntry), NULL);

  CT_STATE->click_func_dropdown = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_func_dropdown"));

  //

  CT_STATE->start_stop_button = gtk_button_new_with_label("START");
  gtk_widget_add_css_class(GTK_WIDGET(CT_STATE->start_stop_button), "start-stop-button");
  gtk_widget_set_cursor_from_name(CT_STATE->start_stop_button, "pointer"); // make the cursor a pointer on hover
  g_signal_connect(CT_STATE->start_stop_button, "clicked", G_CALLBACK(toggleClickTimer), CT_STATE);
  gtk_grid_attach(GTK_GRID(click_timer_grid), CT_STATE->start_stop_button, 0, 2, 3, 1);

  gtk_box_append(GTK_BOX(click_timer_container), click_timer_grid);
  gtk_box_append(GTK_BOX(container), click_timer_container);
  /*  */

  /* MACRO LOADER
   * 
   *    Macro Editor (i)
   * [     MACRO NAME    ]
   * [ IMPORT ] [ CREATE ]
   * 
   */
  GtkWidget* macro_loader_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(macro_loader_container, "macro-loader-box");
  gtk_widget_set_overflow(macro_loader_container, GTK_OVERFLOW_HIDDEN); // make corners round

  GtkBuilder* macro_loader_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/macro_loader.ui");
  MacroEditorState* ME_STATE = g_new0(MacroEditorState, 1); // deliberatly leaked, actual pattern for GTK+
  ME_STATE->app = app;
  ME_STATE->main_window = window;

  /*
   * Label and info button grid
   */
   GtkWidget* macro_loader_label_and_info_grid = gtk_grid_new();
   gtk_widget_set_halign(macro_loader_label_and_info_grid, GTK_ALIGN_CENTER); // set the grid in the center of the box
   gtk_widget_set_valign(macro_loader_label_and_info_grid, GTK_ALIGN_CENTER); // set the grid in the center of the box
   
   GtkWidget* macro_loader_label = gtk_label_new("Macro Editor");
   gtk_widget_add_css_class(macro_loader_label, "click-timer-label"); // reuse CSS
   
   GtkWidget* macro_loader_info_button = gtk_button_new();
   
   g_signal_connect(macro_loader_info_button, "clicked", G_CALLBACK(macroLoaderInfoDialog), ME_STATE);
   gtk_widget_add_css_class(macro_loader_info_button, "click-timer-info-button"); // reuse CSS
   gtk_widget_set_cursor_from_name(macro_loader_info_button, "pointer"); // make the cursor a pointer on hover

   /*
    * This doesn't actually dupe memory in any meaningful way or cause
    * perfomance bottlenecks, its just a GTK refcounting issue about double-childing
    */
   GtkWidget* info_icon2 = gtk_image_new_from_resource("/com/the-clicker/graphics/assets/info_icon.png");
   gtk_image_set_pixel_size(GTK_IMAGE(info_icon2), 18);
   gtk_button_set_child(GTK_BUTTON(macro_loader_info_button), info_icon2); // add the icon to the button
 
   gtk_grid_attach(GTK_GRID(macro_loader_label_and_info_grid), macro_loader_label, 0, 0, 1, 1);
   gtk_grid_attach(GTK_GRID(macro_loader_label_and_info_grid), gtk_label_new(" "), 1, 0, 1, 1); // spacer
   gtk_grid_attach(GTK_GRID(macro_loader_label_and_info_grid), macro_loader_info_button, 2, 0, 1, 1);
   gtk_box_append(GTK_BOX(macro_loader_container), macro_loader_label_and_info_grid);
  
  //gtk_box_append(macro_loader_container, macro_loader_grid);
  gtk_box_append(GTK_BOX(container), macro_loader_container);
  /*  */

  /* STYLE */
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_resource(provider, "/com/the-clicker/graphics/styles/style.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
  /* */
  
  gtk_window_set_child(GTK_WINDOW(window), container);
  gtk_window_present(GTK_WINDOW(window));
  
  g_object_unref(main_window_builder); // were done with builders, its been loaded into GTK's heap
  g_object_unref(click_timer_builder);
}

#endif /* ACTIVATE_H */
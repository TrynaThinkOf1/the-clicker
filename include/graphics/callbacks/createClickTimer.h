#ifndef CREATECLICKTIMER_H
#define CREATECLICKTIMER_H

#include <stdbool.h>

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/callbacks/clickTimerInfoDialog.h"
#include "graphics/callbacks/toggleClickTimer.h"
#include "graphics/callbacks/numberOnlyEntry.h"

/*
 *             Click Timer (i)
 * [HOURS ENTRY] [MINS ENTRY] [SECS ENTRY]
 * [X ENTRY][Y ENTRY][CLICK TYPE DROPDOWN]
 * [          START/STOP BUTTON          ]
 * 
 * Relies on a global state struct for everything
*/
static void createClickTimer(GtkApplication* app, GtkWidget* window, GtkWidget* container) {
  GtkWidget* click_timer_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_add_css_class(click_timer_container, "click-timer-box");
  gtk_widget_set_overflow(click_timer_container, GTK_OVERFLOW_HIDDEN); // make corners round
  
  GtkBuilder* click_timer_builder = gtk_builder_new_from_resource("/com/the-clicker/graphics/ui/click_timer.ui");
  ClickTimerState* state = g_new0(ClickTimerState, 1); // deliberatly leaked, actual pattern for GTK+
  state->app = app;
  state->main_window = window;
  state->timer_active = false;
  state->click_func = leftClick;

   /*
    * Label and info button grid
    */
    GtkWidget* label_and_info_grid = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "label_and_info_grid"));
    
    GtkWidget* click_timer_info_button = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_timer_info_button"));
    g_signal_connect(click_timer_info_button, "clicked", G_CALLBACK(clickTimerInfoDialog), state);
    gtk_widget_set_cursor_from_name(click_timer_info_button, "pointer"); // make the cursor a pointer on hover
  
    gtk_box_append(GTK_BOX(click_timer_container), label_and_info_grid);

  GtkWidget* click_timer_grid = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_timer_grid"));
  
  state->mins_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "mins_spinbtn"));
  state->secs_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "secs_spinbtn"));
  state->ms_spinbtn = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "ms_spinbtn"));
  
  state->x_coord_entry = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "x_coord_entry"));
  g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(state->x_coord_entry)), "insert-text", G_CALLBACK(numberOnlyEntry), NULL);
  state->y_coord_entry = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "y_coord_entry"));
  g_signal_connect(gtk_editable_get_delegate(GTK_EDITABLE(state->y_coord_entry)), "insert-text", G_CALLBACK(numberOnlyEntry), NULL);

  state->click_func_dropdown = GTK_WIDGET(gtk_builder_get_object(click_timer_builder, "click_func_dropdown"));

  //

  state->start_stop_button = gtk_button_new_with_label("START");
  gtk_widget_add_css_class(GTK_WIDGET(state->start_stop_button), "start-stop-button");
  gtk_widget_set_cursor_from_name(state->start_stop_button, "pointer"); // make the cursor a pointer on hover
  g_signal_connect(state->start_stop_button, "clicked", G_CALLBACK(toggleClickTimer), state);
  gtk_grid_attach(GTK_GRID(click_timer_grid), state->start_stop_button, 0, 2, 3, 1);

  gtk_box_append(GTK_BOX(click_timer_container), click_timer_grid);
  gtk_box_append(GTK_BOX(container), click_timer_container);
  /*  */
  
  g_object_unref(click_timer_builder);
}

#endif /* CREATECLICKTIMER_H */
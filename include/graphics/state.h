#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>


typedef struct ClickTimerState_t {
  GtkWindow* main_window;
  
  GtkWidget* mins_spinbtn;
  GtkWidget* secs_spinbtn;
  GtkWidget* ms_spinbtn;
  
  GtkWidget* x_coord_entry;
  GtkWidget* y_coord_entry;
  
  GtkWidget* click_func_dropdown;
  
  GtkWidget* start_stop_button;

  // now to the actual functionality

  void (*click_func)(int, int);
  int x_coord;
  int y_coord;

  // instead of having a pthread like earlier, we just push the function to the GTK main loop
} ClickTimerState;

#endif /* STATE_H */
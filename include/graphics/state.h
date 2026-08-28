#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

#include <gtk/gtk.h>

#include "macros.h"


typedef struct ClickTimerState_t {
  GtkApplication* app;
  GtkApplicationWindow* main_window;
  
  GtkWidget* mins_spinbtn;
  GtkWidget* secs_spinbtn;
  GtkWidget* ms_spinbtn;
  guint64 sleep_ms;
  
  GtkWidget* x_coord_entry;
  GtkWidget* y_coord_entry;
  
  GtkWidget* click_func_dropdown;
  
  GtkWidget* start_stop_button;

  // now to the actual functionality

  void (*click_func)(int, int);
  int x;
  int y;

  volatile gint timer_active;
  GThread* timer_thread;
} ClickTimerState;

/* */

typedef struct MacroEditorState_t {
  GtkApplication* app;
  GtkApplicationWindow* main_window;
  GtkWindow* editor_window;

  GtkWidget* macro_name_entry;
  char* macro_name_easy;

  Macro* mac;
} MacroEditorState;

#endif /* STATE_H */

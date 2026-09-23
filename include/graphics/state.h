#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>

#include "macros.h"


typedef struct {
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

typedef struct {
  GtkApplication* app;
  GtkApplicationWindow* main_window;
  GtkWindow* editor_window;

  GtkWindow* warning_window;
  gboolean warning_up;
  guint close_editor_window_with_unsaved_work; // if 0: user has not confirmed anything, if 1: cancel, if 2: delete unsaved work

  GtkWidget* macro_name_entry;
  char* macro_name_easy;

  Macro* mac;
} MacroEditorState;

#endif /* STATE_H */

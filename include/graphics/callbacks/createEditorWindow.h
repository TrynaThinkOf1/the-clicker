#ifndef CREATE_EDITOR_WINDOW_H
#define CREATE_EDITOR_WINDOW_H

#include <gtk/gtk.h>

#include "graphics/callbacks/unsavedWorkWarning.h"
#include "graphics/state.h"
#include "macros.h"

static gboolean editor_window_close_request(GtkWindow* self, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;

  if (!state->mac->saved) {
    if (state->warning_up) return true;
    else {
      switch (state->close_editor_window_with_unsaved_work) {
        case 0: unsavedWorkWarning(state); break;
        case 1:
          state->close_editor_window_with_unsaved_work = 0;
          return true; // they do not want to delete unsaved work
        case 2:
          gtk_window_destroy(state->editor_window);
          freeMacro(state->mac);
          state->close_editor_window_with_unsaved_work = 0;
          break; // they want to delete unsaved work
      }
    }
  } else {
    // simply free the macro, its already been exported
    freeMacro(state->mac);
    // no need to deal with state->macro_name_easy because it pointed to state->mac->name, which was just freed
    
    gtk_window_destroy(state->editor_window);
  }

  return true;
}

static void createEditorWindow(MacroEditorState* state) {
  GtkWindow* window = gtk_window_new();

  g_signal_connect(GTK_WINDOW(window), "close-request", G_CALLBACK(editor_window_close_request), state);

  state->editor_window = window;
  
  gtk_window_present(window);
}

#endif /* CREATE_EDITOR_WINDOW_H */
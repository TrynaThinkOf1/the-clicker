#ifndef IMPORTMACRO_H
#define IMPORTMACRO_H

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/sendNotification.h"
#include "macros.h"

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)
  #include "linux/macro_storage.h"
#endif

static void importMacroCallback(GtkWidget* widget, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;

  state->macro_name_easy = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(state->macro_name_entry)));

  const int len = strlen(state->macro_name_easy); // between 0 and 50
  
  if (len == 0) {
    send_notification("Invalid Macro Name", "Cannot load a macro with an empty name", state->app);
    return;
  }

  Macro* mac;
  char* err;
  if (!importMacro(state->macro_name_easy, &mac, &err)) {
    send_notification("Failed to import macro", err, state->app);
    return;
  }

  state->mac = mac;

  /*
   * TODO: Create editor window
   */
}

#endif /* IMPORTMACRO_H */
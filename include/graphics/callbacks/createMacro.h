#ifndef CREATEMACRO_H
#define CREATEMACRO_H

#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>

#include "graphics/state.h"
#include "graphics/sendNotification.h"
#include "macros.h"

#if defined(__APPLE__) || defined(__MACH__) || defined(__LINUX__) || defined(__unix__)
  #include "linux/macro_storage.h"
#endif

static void createMacro(GtkWidget* widget, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;

  state->macro_name_easy = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(state->macro_name_entry)));

  const int len = strlen(state->macro_name_easy); // between 0 and 50
  
  if (len == 0) {
    send_notification("Invalid Macro Name", "Cannot create a macro with an empty name", state->app);
    return;
  }

  Macro* mac = initializeMacro();
  if (mac == NULL) {
    send_notification("Failed to create macro", "Memory allocation for the new macro failed", state->app);
    return;
  }

  char new_name[len + 1];
  strlcpy(new_name, state->macro_name_easy, len + 1);
  // new_name[len] = '\0'; // the size'th character gets the null terminator
  mac->name = new_name;

  char* err;
  if (!exportMacro(mac, &err)) {
    send_notification("Failed to create macro", err, state->app);
    return;
  }

  char body[6 + len + 1 + 9 + 11 + 1]; // "Name: " + name + '\t' + "Address: " + mac + '\0'
  snprintf(body, 6 + len + 1 + 9 + 11 + 1, "Name: %s\tAddress: %p", mac->name, mac);
  send_notification("Successfully created macro", body, state->app);

  state->mac = mac;

  /*
   * TODO: Create the editor window and load in the brand new blank macro.
   */
}

#endif /* CREATEMACRO_H */
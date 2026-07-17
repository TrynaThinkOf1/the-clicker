#ifndef CALLBACKS_IMPORTGLOBALMACRO_H
#define CALLBACKS_IMPORTGLOBALMACRO_H

#include <gtk/gtk.h>

#include "graphics/globals.h"
#include "macros.h"
/* VERY TEMPORARY - FOR TESTING PURPOSES */
#include "linux/macro_storage.h"
/*  */

static void callback_importGlobalMacro(GtkWidget* widget, gpointer user_data) {
  char* macro_name = gtk_entry_buffer_get_text(gtk_entry_get_buffer(macro_name_entry)); // get content from global buffer

  if (current_macro != NULL) {
    // TODO: Prompt for saving changes if changes exist
    freeMacro(current_macro);
    // TODO: Derender it, etc.
  }

  if (nameExists(macro_name)) {
    current_macro = importMacro(macro_name);
    if (current_macro != NULL) {
      // TODO: Render it, etc.
      g_print("Name: %s | Saved: %b | First: %p | Last: %p\n", current_macro->name, current_macro->saved, current_macro->first, current_macro->last);
    }
  }
}

#endif /* CALLBACKS_IMPORTGLOBALMACRO_H */

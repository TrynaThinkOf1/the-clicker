#ifndef NUMBERONLYENTRY_H
#define NUMBERONLYENTRY_H

#include <gtk/gtk.h>

/*
 * Just a reimplementation of the insert-text handler for my own purposes
 */
static void numberOnlyEntry(GtkEditable* editable, const char* text, int length, int* position, gpointer data) {
  char* string = g_utf8_strup(text, length); // create a string

  g_signal_handlers_block_by_func(editable, (gpointer)numberOnlyEntry, data); // block an infinite recursion loop

  int idx = 0;
  char processed[length]; // to add the digit characters
  
  for (int i = 0; i < length; i++) {
    if (string[i] - '0' < 10) {
      processed[idx] = string[i];
      idx++;
    }
  }
  processed[idx + 1] = '\0';
  
  gtk_editable_insert_text (editable, processed, length, position); // add the digit-only string to the editable

  g_signal_handlers_unblock_by_func(editable, (gpointer)numberOnlyEntry, data); // unblock the function so that it can be called again

  g_signal_stop_emission_by_name(editable, "insert_text"); // prevent this function from emitting the same signal again

  g_free(string);
}

#endif /* NUMBERONLYENTRY_H */

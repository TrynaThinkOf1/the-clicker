#ifndef CALLBACKS_PREVENTNONDIGITINPUT_H
#define CALLBACKS_PREVENTNONDIGITINPUT_H

#include <gtk/gtk.h>


/// disallow all non-digit characters in the buffer
/// IMMA BE SO FR, I HAVE NO IDEA HOW THIS FUNCTION WORKS
static void callback_preventNonDigitInput(GtkEditable* editable, const char* text, int length, int* position, gpointer user_data) {
  bool nd = false;
  for (int i = 0; i < length; i++) {
    if (text[i] < 48 || text[i] > 57) {
      nd = true;
      break;
    }
  }

  if (nd) {
    GString *filtered = g_string_new(NULL);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 48 && text[i] <= 57) {
            g_string_append_c(filtered, text[i]);
        }
    }

    g_signal_stop_emission_by_name(editable, "insert-text"); // stop the original signal

    g_signal_handlers_block_by_func(editable, callback_preventNonDigitInput, user_data); // block the signal to prevent recursion while inserting manually
    gtk_editable_insert_text(editable, filtered->str, filtered->len, position); // insert the clean text at the current position
    g_signal_handlers_unblock_by_func(editable, callback_preventNonDigitInput, user_data); // unblock the signal
  }
}

#endif /* CALLBACKS_PREVENTNONDIGITINPUT_H */
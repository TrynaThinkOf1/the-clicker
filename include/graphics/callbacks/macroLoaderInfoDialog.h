#ifndef MACROLOADERINFODIALOG_H
#define MACROLOADERINFODIALOG_H

#include <gtk/gtk.h>

#include "graphics/state.h"

static void macroLoaderInfoDialog(GtkWidget* button, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;
  
  GtkAlertDialog* dialog = gtk_alert_dialog_new("\nThe Macro Editor");
  gtk_alert_dialog_set_detail(dialog,
    "The Macro Editor is the biggest offer from The Clicker. Macros\n"
    "are simplistic instruction lists for the program to execute. They\n"
    "are stored in the folder `~/.clicker_macros/` and take on a JSON-like\n"
    "format. Users have a variety of available instructions for their macros:\n"
    "moveCursor, sleep_m, leftClick, rightClick, leftDoubleClick,\n"
    "rightDoubleClick. There are more options coming soon, if you want to add\n"
    "functionality yourself, create a pull request on the GitHub page."
  );

  const char* buttons[] = {"Ok", NULL};
  gtk_alert_dialog_set_buttons (dialog, buttons);
  gtk_alert_dialog_set_cancel_button (dialog, 0); // make the cancel button an Ok button instead
  
  gtk_alert_dialog_show(dialog, GTK_WINDOW(state->main_window));
}

#endif /* MACROLOADERINFODIALOG_H */
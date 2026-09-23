#ifndef UNSAVEDWORKWARNING_H
#define UNSAVEDWORKWARNING_H

#include <gtk/gtk.h>

#include "graphics/state.h"

static void cancelTheCloseRequest(GtkWidget* widget, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;

  gtk_window_destroy(state->warning_window);
  state->warning_up = false;
  state->close_editor_window_with_unsaved_work = 1;
}
static void deleteUnsavedWork(GtkWidget* widget, gpointer user_data) {
  MacroEditorState* state = (MacroEditorState*)user_data;

  gtk_window_destroy(state->warning_window);
  gtk_window_destroy(state->editor_window);
  state->warning_up = false;
  state->close_editor_window_with_unsaved_work = 2;
}

static void unsavedWorkWarning(MacroEditorState* state) {
  GtkWindow* warning = gtk_window_new();
  gtk_window_set_modal(warning, true); // makes it the force focus and force primary interaction
  gtk_window_set_deletable(warning, FALSE); // disallow closing
  gtk_window_set_transient_for(GTK_WINDOW(warning), GTK_WINDOW(state->editor_window));
  
  state->warning_window = warning;
  state->warning_up = true;
  
  gtk_window_set_title(warning, "!! WARNING !!");
  gtk_window_set_resizable(warning, false);

  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  /* title */
  GtkWidget* title = gtk_label_new("");
  gtk_label_set_justify(title, GTK_JUSTIFY_CENTER);
  gtk_label_set_use_markup(title, true);
  gtk_widget_set_margin_top(title, 10);
  gtk_widget_set_margin_bottom(title, 10);
  gtk_label_set_markup(GTK_LABEL(title),
    "<span size=\"large\" weight=\"bold\" color=\"red\">You Have Unsaved Work</span>"
  );

  /* buttons */
  GtkBox* buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  GtkButton* cancel_button = gtk_button_new_with_label("Cancel");
  g_signal_connect(GTK_WIDGET(cancel_button), "clicked", G_CALLBACK(cancelTheCloseRequest), state);
  gtk_box_append(buttons, cancel_button);
  
  GtkButton* delete_work_button = gtk_button_new_with_label("Delete Work (this cannot be undone)");
  g_signal_connect(GTK_WIDGET(delete_work_button), "clicked", G_CALLBACK(deleteUnsavedWork), state);
  gtk_box_append(buttons, delete_work_button);
  
  gtk_box_append(GTK_BOX(box), title);
  gtk_box_append(GTK_BOX(box), buttons);

  gtk_window_set_child(warning, GTK_BOX(box));

  gtk_window_set_application(warning, state->app);
  gtk_window_present(warning);
}

#endif /* UNSAVEDWORKWARNING_H */
#ifndef HELPMENU_H
#define HELPMENU_H

#include <gtk/gtk.h>

static void default(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
}

static void createHelpMenu(GtkApplication* app) {
  GMenu* menubar = g_menu_new();

  /* ABOUT PAGE */
  GMenu* about_submenu = g_menu_new();
  g_menu_append(about_submenu, "About the Program", "app.about");
  g_menu_append(about_submenu, "Technical Information", "app.about");
  g_menu_append(about_submenu, "About the Authors", "app.about");
  g_menu_append_submenu(menubar, "About", G_MENU_MODEL(about_submenu));
  /*  */

  gtk_application_set_menubar(app, G_MENU_MODEL(menubar));
}

#endif /* HELPMENU_H */
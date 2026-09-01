#ifndef HELPMENU_H
#define HELPMENU_H

#include <gtk/gtk.h>

struct temp_data_holder {
  int option;
  GtkApplication* app;
};

static void about_window_loader(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
  const struct temp_data_holder* data = (struct temp_data_holder*)user_data;
}
// static void createHelpMenu(GtkApplication* app) {
//   GMenu* menubar = g_menu_new();
  
//   GMenu* program_help_submenu = g_menu_new();
//   g_menu_append(program_help_submenu, "Program Help", "app.help");
//   GSimpleAction* program_help_action = g_simple_action_new("help", NULL);
//   g_signal_connect(program_help_action, "activate", G_CALLBACK(on_program_help_activate), app);
//   g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(program_help_action));
//   g_menu_append_submenu(menubar, "Help", G_MENU_MODEL(program_help_submenu));

//   GMenu* error_help_submenu = g_menu_new();
//   g_menu_append(error_help_submenu, "Error Help", "app.help");
//   GSimpleAction* error_help_action = g_simple_action_new("help", NULL);
//   g_signal_connect(error_help_submenu, "activate", G_CALLBACK(on_error_help_activate), app);
//   g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(error_help_action));
//   g_menu_append_submenu(program_help_submenu, "Error Help", G_MENU_MODEL(error_help_submenu));
  
//   gtk_application_set_menubar(app, G_MENU_MODEL(menubar));
// }

static void createHelpMenu(GtkApplication* app) {
  GMenu* menubar = g_menu_new();

  /* ABOUT PAGE */
  GMenu* about_submenu = g_menu_new();
  
  g_menu_append(about_submenu, "About the Program", "app.about-program");
  GSimpleAction* about_prog = g_simple_action_new("about-program", NULL);
  struct temp_data_holder* about_prog_struct = g_new0(struct temp_data_holder, 1);
  about_prog_struct->option = 0;
  about_prog_struct->app = app;
  g_signal_connect(about_prog, "activate", G_CALLBACK(about_window_loader), about_prog_struct);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_prog));

  g_menu_append(about_submenu, "Technical Information", "app.about-technical");
  GSimpleAction* about_tech = g_simple_action_new("about-technical", NULL);
  struct temp_data_holder* about_tech_struct = g_new0(struct temp_data_holder, 1);
  about_tech_struct->option = 1;
  about_tech_struct->app = app;
  g_signal_connect(about_tech, "activate", G_CALLBACK(about_window_loader), about_tech_struct);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_tech));
  
  g_menu_append(about_submenu, "About the Authors", "app.about-authors");
  GSimpleAction* about_auth = g_simple_action_new("about-authors", NULL);
  struct temp_data_holder* about_auth_struct = g_new0(struct temp_data_holder, 1);
  about_auth_struct->option = 2;
  about_auth_struct->app = app;
  g_signal_connect(about_auth, "activate", G_CALLBACK(about_window_loader), about_auth_struct);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_auth));
  
  g_menu_append_submenu(menubar, "About", G_MENU_MODEL(about_submenu));
  /*  */

  gtk_application_set_menubar(app, G_MENU_MODEL(menubar));
}

#endif /* HELPMENU_H */
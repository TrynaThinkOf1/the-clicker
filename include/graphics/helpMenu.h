#ifndef HELPMENU_H
#define HELPMENU_H

#include <stdbool.h>

#include <gtk/gtk.h>

struct temp_data_holder {
  int option;
  GtkApplication* app;
};

static void about_window_loader(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
  const struct temp_data_holder* data = (struct temp_data_holder*)user_data;

  GtkWindow* window = gtk_window_new();
  //gtk_window_set_default_size(window, 500, 300); // commented out so the window sets its own size
  gtk_window_set_resizable(window, false);

  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  GtkWidget* title = gtk_label_new("");
  gtk_label_set_justify(title, GTK_JUSTIFY_CENTER);
  gtk_label_set_use_markup(title, true);
  gtk_widget_set_margin_top(title, 10);
  gtk_widget_set_margin_bottom(title, 10);
  
  GtkWidget* content = gtk_label_new("");
  gtk_label_set_max_width_chars(GTK_LABEL(content), 70);
  gtk_label_set_wrap(GTK_LABEL(content), true);
  gtk_label_set_wrap_mode(GTK_LABEL(content), PANGO_WRAP_WORD_CHAR);
  gtk_label_set_justify(GTK_LABEL(content), GTK_JUSTIFY_LEFT);
  gtk_label_set_use_markup(content, true);
  gtk_widget_set_margin_start(content, 10);
  gtk_widget_set_margin_end(content, 10);
  gtk_widget_set_margin_bottom(content, 10);
  gtk_label_set_markup(GTK_LABEL(title),
    "<span size=\"large\" weight=\"bold\">The Clicker</span>"
  );

  switch (data->option) {
    case 0:
      gtk_window_set_title(window, "About the Program");
      gtk_label_set_markup(GTK_LABEL(content),
        "It is a relatively simple-to-use autoclicker application "
        "for MacOS, Linux, and Windows. "
        "It comes with two main features: the click timer, and the macro runner. "
        "The click timer is literally just an autoclicker.\n\n"
        "<big>How to use the click timer</big>\n"
        "<b>1.</b> Select how much time should happen in between clicks (min, sec, ms)\n"
        "\t<small>minimum is 1ms, maximum is 120 mins, 59 secs, and 999 ms</small>\n\n"
        "<b>2.</b> Select your click type from the drop-down menu below the timer input\n"
        "\t<small>the options are a single Left Click, a double Left Click, a single Right Click, and a double Right click.</small>\n\n"
        "<b>3.</b> Fill in the coordinates for where the clicks should happen on your screen, these numbers typically range "
        "from 0 to 1920 in the X axis and 0 to 1080 in the Y axis\n"
        "\t<small>your computer may vary, check your resolution in your settings or preferences application)\n"
        "\tleave both inputs blank to simply have the clicks happen at your cursor at the moment of click execution.</small>\n\n"
        "<b>4.</b> Once all options are set and validated <i>(the app will let you know if you have "
        "any invalid options)</i>, click the <u>START</u> button and the clicks will begin happening "
        "at regular intervals executing your "
        "selected click type at the desired location until the <u>STOP</u> button is clicked.\n"
      );
      break;
    case 1:
      gtk_window_set_title(window, "Technical Information");
      gtk_label_set_markup(GTK_LABEL(content),
        "<b>Written in</b>:\t\tC\t\t\t\t\t<small>standard C17</small>\n"
        "<b>Compiled with</b>:\t"
        #if defined(__clang__) && defined(__APPLE__) // first check because clang also defines __GNUC__
          "Apple clang"
        #elif defined(__clang__)
          "clang"
        #elif defined(__GNUC__) && !defined(__INTEL_COMPILER)
          "GCC"
        #elif defined(_MSC_VER)
          "MSVC"
        #elif defined(__INTEL_COMPILER)
          "Intel"
        #elif defined(__TINYC__)
          "TinyCC"
        #elif defined(__EMSCRIPTEN__)
          "Emscripten"
        #elif defined(__ARMCC_VERSION)
          "ARM"
        #else
          #error "Unknown Compiler"
        #endif
        
        "\t<small>" __VERSION__ "</small>\n"
        "<b>Compiled for</b>:\t"
      #if defined(__APPLE__) || defined(__MACH__)
        "MacOS "
      #elif defined(__LINUX__) || defined(__unix__)
        "Linux "
      #elif defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
        "Windows "
      #else
        #error "Unknown Operating System"
      #endif

      #if defined(__x86_64__) || defined(_M_X64)
        "x86_64"
      #elif defined(__i386__) || defined(_M_IX86)
        "x86"
      #elif defined(__aarch64__) || defined(_M_ARM64)
        "arm64"
      #elif defined(__arm__) || defined(_M_ARM)
        "arm"
      #else
        #error "Unknown Architecture"
      #endif
        "\n"
        "<b>Built with</b>:\t\tGNU Make\t\t\t<small>version 3.81</small>\n"
        "<b>Libraries</b>:\n"
        "\tgtk 4.0"
        "\tgdk 2.0"
        "\tgio 2.0"
        "\t\tglib 2.0\n"
        "\tpango"
        "\tcairo"
        "\tgraphene"
        "\tgettext\n"
        "\n"
        "<b>Editor</b>:\tZed\t<small>version 1.17.2</small>\n"
        "<b>Offical Repo</b>:\t<a href=\"https://www.github.com/trynathinkof1/the-clicker/\">"
        "https://www.github.com/trynathinkof1/the-clicker/</a>\n"
      );
      break;
    case 2:
      gtk_window_set_title(window, "About the Authors");
      gtk_label_set_markup(GTK_LABEL(content),
        ""
      );
      break;
    default:
      break;
  };

  gtk_box_append(GTK_BOX(box), title);
  gtk_box_append(GTK_BOX(box), content);

  gtk_window_set_child(window, GTK_BOX(box));

  gtk_window_set_application(window, data->app);
  gtk_window_present(window);
}

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
/*
 * The Clicker
 * Open source GUI autoclicker
 * Copyright Zevi Berlin 2026 - license in LICENSE file
 */

#include <stdio.h>

#include <gtk/gtk.h>

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/screen/screen.h"
  #include "macos/mouse/mouse.h"
  #include "linux/macro_storage.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/screen/screen.h"
  #include "linux/mouse/mouse.h"
  #include "linux/macro_storage.h"
#elif defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
  #include "windows/screen/screen.h"
  #include "windows/mouse/mouse.h"
#else
  #error "Unknown Operating System"
#endif

#include "parse_int.h"
#include "builtins.h"
#include "macros.h"
#include "graphics/callbacks/activate.h"


int main(int argc, char** argv) {
  if (!initializeMouse()) { // this is only necessary for linux, but macos has a dummy version for API uniformity
    printf("Failed to initialize mouse!\n");
    return 1;
  }

  //

  GtkApplication *app;
  int status;

  app = gtk_application_new("trynathinkof1.the-clicker", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  
  g_object_unref(app);

  //

  destroyMouse(); // same as the initializer function above
  
  return status;
}
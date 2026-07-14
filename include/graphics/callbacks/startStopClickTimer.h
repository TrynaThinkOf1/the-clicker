#ifndef CALLBACKS_STARTCLICKTIMER_H
#define CALLBACKS_STARTCLICKTIMER_H

#include <stdbool.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include "graphics/globals.h"

#if defined(__APPLE__) || defined(__MACH__)
  #include "macos/mouse/mouse.h"
#elif defined(__LINUX__) || defined(__unix__)
  #include "linux/mouse/mouse.h"
#elif defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN64__)
  #include "windows/mouse/mouse.h"
#endif


static void* clickTimerLoop(void* data) {
  g_print("{\n\tSLEEP_MS: %i\n\tCLICK_X: %i\n\tCLICK_Y: %i\n\tCLICK_FUNC: %p\n}\n", SLEEP_MS, CLICK_X, CLICK_Y, CLICK_FUNC);

  while (!click_timer_should_stop) {
    sleep_m(SLEEP_MS, 0);
    if (click_timer_should_stop) break;

    CLICK_FUNC(CLICK_X, CLICK_Y);
  }

  return NULL;
}

static void callback_startStopClickTimer(GtkWidget* widget, gpointer user_data) {
  if (SLEEP_MS > 0 && CLICK_FUNC != NULL && !click_timer_is_active) {
    click_timer_should_stop = false;
    pthread_create(&click_timer_thread, NULL, clickTimerLoop, NULL);

    click_timer_is_active = true;
    gtk_button_set_label(GTK_BUTTON(widget), "Stop");

    gtk_widget_set_sensitive(FUNC_SELECTOR, false); // disallow new click functions
  } else if (click_timer_is_active) {
    click_timer_should_stop = true;
    pthread_join(click_timer_thread, NULL);

    click_timer_is_active = false;
    gtk_button_set_label(GTK_BUTTON(widget), "Start");

    gtk_widget_set_sensitive(FUNC_SELECTOR, true); // allow new click functions to be selected
  }
}

#endif /* CALLBACKS_STARTCLICKTIMER_H */
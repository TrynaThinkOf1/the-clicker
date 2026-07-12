#ifndef STYLING_CSS_PROVIDER_H
#define STYLING_CSS_PROVIDER_H

#include <gtk/gtk.h>

static void styling_createCSS() {
  GtkCssProvider* provider = gtk_css_provider_new(); // create the CSS provider

  // create the actual CSS classes
  const char* CSS_DATA =
    ".window { "
    "  background-color: #37123c; "
    "}"
    ".click-timer-box { "
    "  background-color: #71677c; "
    "  padding: 1em; "
    "  border-style: solid; "
    "  border-width: 1px; "
    "  border-color: #ffffff; "
    "  border-radius: 20px; "
    "  margin: 1em; "
    "}"
    ".click-timer-label { "
    "  font-size: 1em; "
    "  color: #ffffff; "
    "}"
    ".click-timer-entry { "
    "  border-color: #945D5E; "
    "  color: #945D5E; "
    "  margin: 2px; "
    "  font-weight: bold; "
    "}"
    ".click-timer-func-selector { " // advanced CSS ts
    "  font-size: 1em; "
    "  color: #945D5E; "
    "  border-color: #945D5E; "
    "  margin: 2px; "
    "}"
    //".click-timer-func-selector > popover.menu > contents > box > button { "
    //"  background-image: none; "
    //"  background-color: #D8D1CA; "
    //"}"
    ".click-timer-start-stop-button { "
    "  border-color: #945D5E; "
    "  color: #945D5E; "
    "  font-weight: bold; "
    "  margin: 2px; "
    "}";

  gtk_css_provider_load_from_string(provider, CSS_DATA); // load the data into the provider

  // set the CSS for the default dispaly
  gtk_style_context_add_provider_for_display(
      gdk_display_get_default(),
      GTK_STYLE_PROVIDER(provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
  );
}

#endif /* STYLING_CSS_PROVIDER_H */
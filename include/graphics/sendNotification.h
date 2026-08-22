/*
 * Sends a system notification.
 * 
 * @param title     The bold title of the notification.
 * @param body      The main text content.
 * @param user_data Only for the non-macos callers to include the GTK Application
 */
void send_notification(const char *title, const char *body, void* user_data);

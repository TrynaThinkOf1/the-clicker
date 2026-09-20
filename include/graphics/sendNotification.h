/*
 * Sends a system notification.
 * 
 * @param title     The bold title of the notification.
 * @param body      The main text content.
 * @param user_data Only for the non-macos callers to include the GTK Application
 */
void send_notification(const char* title, const char* body, void* user_data);

/*
 * Sends a system notification with buttons
 * 
 * @param button1   The text in the first button - if this is clicked the function returns TRUE
 * @param button2   The text in the second button - if this is clicked the function returns FALSE
 */
void send_notification_with_buttons(const char* title, const char* body, const char* button1, const char* button2, void* user_data);
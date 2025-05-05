#ifndef UI_H
#define UI_H

char get_user_confirmation(const char *message);
void display_summary(int changes, const char *operation);
void display_error(const char *error_message);

#endif


#ifndef WREPLACE_H
#define WREPLACE_H

int replace_case_sensitive(char *buffer, const char *word);
int replace_ignore_case(char *buffer, const char *word);
int unremove_keep_case(char *buffer, const char *word);
int unremove_match_case(char *buffer, const char *word);

#endif

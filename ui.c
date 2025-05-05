#include <stdio.h>
#include "ui.h"

// Prompt user for confirmation
char get_user_confirmation(const char *message) {
    char response;
    printf("%s Confirm(Yes/No/All/Quit): ", message);
    scanf(" %c", &response);
    return response;
}

// Display summary of changes
void display_summary(int changes, const char *operation) {
    if (changes > 0) {
        printf("%d occurrences modified using %s.\n", changes, operation);
    } else {
        printf("No occurrences found for %s.\n", operation);
    }
}

// Display an error message
void display_error(const char *error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
}


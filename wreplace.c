#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wreplace.h"


char *replace_word(const char *buffer, const char *word, int case_sensitive) {
    printf("DEBUG: replace_word() called with word: %s\n", word);

    int word_len = strlen(word);
    int buffer_len = strlen(buffer);

    char *modified_buffer = malloc(buffer_len + 1);
    if (!modified_buffer) {
        perror("Memory allocation failed");
        return NULL;
    }
    strcpy(modified_buffer, buffer);

    char *pos = modified_buffer;
    while ((pos = strstr(pos, word)) != NULL) {
        printf("DEBUG: Checking substring: '%.10s' at position: %ld\n", pos, pos - modified_buffer);
        printf("DEBUG: Found '%s' at position: %ld\n", word, pos - modified_buffer);
        memset(pos, '*', word_len);
        pos += word_len; // Move past the replaced word
    }

    return modified_buffer;

}
// Replace word case-sensitive
int replace_case_sensitive(char *buffer, const char *word) {
    int word_len = strlen(word);
    int count = 0;
    char *pos = buffer;
    
    while ((pos = strstr(pos, word)) != NULL) {
        memset(pos, '*', word_len);
        pos += word_len;
        count++;
    }
    return count;
}

// Replace word case-insensitive
int replace_ignore_case(char *buffer, const char *word) {
    int word_len = strlen(word);
    int count = 0;
    char *pos = buffer;
    char *lower_buffer = strdup(buffer);
    char *lower_word = strdup(word);
    if (!lower_buffer || !lower_word) return -1;

    for (int i = 0; lower_buffer[i]; i++) lower_buffer[i] = tolower(lower_buffer[i]);
    for (int i = 0; lower_word[i]; i++) lower_word[i] = tolower(lower_word[i]);

    char *search_pos = lower_buffer;
    while ((search_pos = strstr(search_pos, lower_word)) != NULL) {
        int offset = search_pos - lower_buffer;
        memset(buffer + offset, '*', word_len);
        search_pos += word_len;
        count++;
    }
    free(lower_buffer);
    free(lower_word);
    return count;
}

// Restore word with caese
int unremove_keep_case(char *buffer, const char *word) {
    int word_len = strlen(word);
    int count = 0;
    char *pos = buffer;
    char response;

    while ((pos = strstr(pos, "*****")) != NULL && strlen(pos) >= word_len) {
        if (strncmp(pos, "*****", word_len) == 0) {
            printf("Restore '%s' at position %ld? (y/n): ", word, pos - buffer);
            scanf(" %c", &response);
            if (response == 'y' || response == 'Y') {
                memcpy(pos, word, word_len);
                count++;
            }
        }
        pos += word_len;
    }
    return count;
}

// Restore word
int unremove_match_case(char *buffer, const char *word) {
    int word_len = strlen(word);
    int count = 0;
    char *pos = buffer;
    char response;

    while ((pos = strstr(pos, "*****")) != NULL && strlen(pos) >= word_len) {
        if (strncmp(pos, "*****", word_len) == 0) {
            char before = (pos > buffer) ? *(pos - 1) : ' ';
            char after = *(pos + word_len);
            char transformed_word[word_len + 1];
            strcpy(transformed_word, word);

            if (isupper(before) || isupper(after)) {
                for (int i = 0; i < word_len; i++) transformed_word[i] = toupper(transformed_word[i]);
            } else {
                for (int i = 0; i < word_len; i++) transformed_word[i] = tolower(transformed_word[i]);
            }

            printf("Restore '%s' at position %ld? (y/n): ", transformed_word, pos - buffer);
            scanf(" %c", &response);
            if (response == 'y' || response == 'Y') {
                memcpy(pos, transformed_word, word_len);
                count++;
            }
        }
        pos += word_len;
    }
    return count;
}


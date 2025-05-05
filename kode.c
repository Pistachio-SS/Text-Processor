#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileread.h"
#include "wreplace.h"
#include "ui.h"

void print_usage() {
    fprintf(stderr, "Usage: kode <command> <word> <file>\n");
    fprintf(stderr, "Commands:\n");
    fprintf(stderr, "  RC <word> <file>  - Remove Case Sensitive\n");
    fprintf(stderr, "  RI <word> <file>  - Remove Ignore Case\n");
    fprintf(stderr, "  UK <word> <file>  - Un-remove Keep Case\n");
    fprintf(stderr, "  UM <word> <file>  - Un-remove Match Case\n");

}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage();
        return 1;
    }

    char *command = argv[1];
    char *word = argv[2];
    char *filename = argv[3];

    if (strlen(word) == 0) {
        fprintf(stderr, "Error: Word cannot be empty.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'.\n", filename);
        return 3;
    }
    fclose(file);

    int changes = 0, apply_all = 0;
    if (strcmp(command, "RC") == 0 || strcmp(command, "RI") == 0 || strcmp(command, "UK") == 0 || strcmp(command, "UM") == 0) {
        long file_size;
        char *buffer = read_file(filename, &file_size);
        if (!buffer) {
            fprintf(stderr, "Error: Failed to read file '%s'.\n", filename);
            return 3;
        }

        char *pos = buffer;
        int line_no = 1;
        while (*pos) {
            char *line_start = pos;
            while (*pos && *pos != '\n') pos++;
            *pos = '\0';

            char modified_line[1024];
            strcpy(modified_line, line_start);
            int line_changed = 0;

            if (strcmp(command, "RC") == 0) {
                line_changed = replace_case_sensitive(modified_line, word);
            } else if (strcmp(command, "RI") == 0) {
                line_changed = replace_ignore_case(modified_line, word);
            } else if (strcmp(command, "UK") == 0) {
                line_changed = unremove_keep_case(modified_line, word);
            } else if (strcmp(command, "UM") == 0) {
                line_changed = unremove_match_case(modified_line, word);
            }

            *pos = '\n';
            pos++;
            line_no++;
        }

        if (changes > 0) {
            if (write_file(filename, buffer, file_size) == 0) {
                printf("Changes applied successfully.\n");
            } else {
                fprintf(stderr, "Error: Failed to write changes to file '%s'.\n", filename);
                free(buffer);
                return 3;
            }
        } else {
            printf("No changes were made.\n");
        }

        free(buffer);
    } else {
        fprintf(stderr, "Error: Invalid command '%s'.\n", command);
        print_usage();
        return 1;
    }
    return 0;
}


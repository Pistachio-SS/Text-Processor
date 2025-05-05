#include <stdio.h>
#include <stdlib.h>
#include "fileread.h"

char *read_file(const char *filename, long *file_size) {
    printf("Attempting to open file: %s\n", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    printf("File opened successfully.\n");

    fseek(file, 0, SEEK_END);  // Move to end of file
    *file_size = ftell(file);
    if (*file_size == -1) {
        perror("Error determining file size");
        fclose(file);
        return NULL;
    }
    rewind(file);  // Move back to the beginning

    printf("File size: %ld bytes\n", *file_size);

    char *buffer = (char *)malloc(*file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, *file_size, file);
    if (read_size != *file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[*file_size] = '\0';
    fclose(file);

    printf("File read successfully.\n");
    return buffer;
}

// Writes a buffer back to a file
int write_file(const char *filename, const char *buffer, long file_size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    fwrite(buffer, 1, file_size, file);
    fclose(file);
    return 0;
}


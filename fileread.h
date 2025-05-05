#ifndef FILEREAD_H
#define FILEREAD_H

char *read_file(const char *filename, long *file_size);
int write_file(const char *filename, const char *buffer, long file_size);

#endif


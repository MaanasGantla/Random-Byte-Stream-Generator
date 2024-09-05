#ifndef OUTPUT_H
#define OUTPUT_H

#include "options.h"
#include <stdbool.h>
#include <stddef.h>




void writeOutput(char *buffer, size_t buffer_pos, int blocksize);
bool writeStdio(unsigned long long x, int nbytes);
bool writeBytes(unsigned long long x, int nbytes, int blocksize, char **buffer, size_t *buffer_size, size_t *buffer_pos);




#endif
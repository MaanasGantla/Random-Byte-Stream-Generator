#include "output.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "options.h"



void writeOutput(char *buffer, size_t positionOfBuffer, int blocksize) {
  size_t writtenNumberOfBytes = 0;
  while (writtenNumberOfBytes < positionOfBuffer) {
        ssize_t writeBytes = (positionOfBuffer - writtenNumberOfBytes < (size_t)blocksize) ?
        (ssize_t)(positionOfBuffer - writtenNumberOfBytes) : (ssize_t)blocksize;
    ssize_t written = write(STDOUT_FILENO, buffer + writtenNumberOfBytes, writeBytes);
    if (written == -1) {
      perror("Was unable to write");
      exit(1);
    }
    writtenNumberOfBytes += written;
  }
  free(buffer);
}


bool writeStdio(unsigned long long inputLength, int numberOfBytes)
{
  do
    {
      if (putchar (inputLength) < 0)
        return false;
      inputLength = inputLength >> CHAR_BIT;
      numberOfBytes--;
    }
  while (0 < numberOfBytes);

  return true;
}	


bool writeBytes(unsigned long long inputLength, int numberOfBytes, int blocksize, char **buffer, size_t *sizeOfBuffer, size_t *positionOfBuffer) {
    do {
        int writeBytes = (numberOfBytes < blocksize) ? numberOfBytes : blocksize;

        if (*positionOfBuffer + writeBytes > *sizeOfBuffer) 
        {
            *sizeOfBuffer += blocksize;
            *buffer = realloc(*buffer, *sizeOfBuffer);
            if (*buffer == NULL) {
                perror("issue with reallocation");
                return false;
            }
        }

        for (int i = 0; i < writeBytes; i++) {
            (*buffer)[(*positionOfBuffer)++] = inputLength;
            inputLength >>= CHAR_BIT;
        }

        numberOfBytes -= writeBytes;
    } while (numberOfBytes > 0);

    return true;   
}



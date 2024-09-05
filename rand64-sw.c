#include "rand64-sw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "options.h"
#include "lrand48.h"


int LRAND48_R = 0;
static FILE *randomStream = NULL;

void software_rand64_init (struct options *options)
{
  if (options->inputType == INPUT_LRAND48_R) {
	software_lrand48_init();
        LRAND48_R = 1;
  } else if (options->inputType == INPUT_FILE) {
    randomStream = fopen(options->inputFile, "r");
    if (!randomStream) {
      perror("Error: failed to open file \n printed by perror");
      exit(1);
    }
  } else {
    randomStream = fopen("/dev/random", "r");
    if (!randomStream) {
      perror("Error: failed to open file \n printed by perror");
      exit(1);
    }
  }
}

unsigned long long software_rand64 (void)
{
  if(LRAND48_R) {
	return software_lrand48();
  } else {
    unsigned long long int x;
    if (fread (&x, sizeof x, 1, randomStream) != 1)
      abort ();
    return x;
  }
}

void software_rand64_fini (void)
{
  if(!LRAND48_R)
    fclose (randomStream);
  else
    software_lrand48_fini();
}

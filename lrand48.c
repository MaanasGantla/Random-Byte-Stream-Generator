#include "lrand48.h"
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

struct drand48_data byteSpace; //byteSpace created for the lrand command
void software_lrand48_init(void) {
	srand48_r((unsigned int)time(NULL), &byteSpace); //start the byteSpace at null
}

unsigned long long software_lrand48(void) {
	long int higherBits;
	mrand48_r(&byteSpace, &higherBits);

	long int lowerBits;
	mrand48_r(&byteSpace, &lowerBits);

	return ((unsigned long long)higherBits << 32) | (unsigned long long)lowerBits; //shift so that the or bitwise operation is done with the lower bits of high
}

void software_lrand48_fini(void) {}


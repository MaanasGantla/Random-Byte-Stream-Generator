#ifndef RAND64_SW_H
#define RAND64_SW_H
#include "options.h"


void software_rand64_init(struct options *options);
unsigned long long software_rand64(void);
void software_rand64_fini(void);


#endif
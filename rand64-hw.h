#ifndef RAND64_HW_H
#define RAND64_HW_H
#include <stdbool.h>
#include "options.h"


bool rdrand_supported(void);
void hardware_rand64_init(struct options *options);
unsigned long long hardware_rand64(void);
void hardware_rand64_fini(void);



#endif
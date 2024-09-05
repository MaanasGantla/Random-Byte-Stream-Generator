#include "rand64-hw.h"
#include <cpuid.h>
#include <stdio.h>
#include <immintrin.h>
#include <stdbool.h>
#include "options.h"

struct cpuid { unsigned eax, ebx, ecx, edx; };

static struct cpuid
cpuid (unsigned int leaf, unsigned int subleaf)
{
  struct cpuid result;
  asm ("cpuid"
       : "=a" (result.eax), "=b" (result.ebx),
         "=c" (result.ecx), "=d" (result.edx)
       : "a" (leaf), "c" (subleaf));
  return result;
}

bool rdrand_supported (void)
{
  struct cpuid extended = cpuid (1, 0);
  return (extended.ecx & bit_RDRND) != 0;
}

void hardware_rand64_init (struct options *options)
{
  if (options->inputType == INPUT_RDRAND && !rdrand_supported()) { //this is the case where rdrand is passed as an option but it doesn't actually exist on the machine
    fprintf(stderr, "RDRAND instruction doesn't exist on this machine!\n");
    exit(1);
  }
}

unsigned long long hardware_rand64 (void)
{
  unsigned long long int x;


  x = 0;

  while (! _rdrand64_step (&x))
    continue;
  return x;
}

void hardware_rand64_fini (void) {}


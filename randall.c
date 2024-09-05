#include <errno.h>
#include <stdio.h>
#include "output.h"
#include "options.h"
#include "rand64-sw.h"
#include "rand64-hw.h"

/* Main program, which outputs N bytes of random data.  */
int main(int argc, char ** argv) {
  /* Check arguments.  */
  struct options options; //a struct of potential options
  optionsScanner(argc, argv, &options);
  
  /* Now that we know we have work to do, arrange to use the appropriate library.  */
  void( * init)(struct options *);
  unsigned long long( * rand64)(void);
  void( * finalize)(void);

  switch (options.inputType) {
  case DEFAULT:

     if (rdrand_supported()) { //if rdrand is supported then we do the same functionality as the original main
        init = hardware_rand64_init;
        rand64 = hardware_rand64;
        finalize = hardware_rand64_fini;
      } else {
        init = software_rand64_init;
        rand64 = software_rand64;
        finalize = software_rand64_fini;
      }
    break;
    //initalize properly if specified RDRAND
  case INPUT_RDRAND:
    init = hardware_rand64_init;
    rand64 = hardware_rand64;
    finalize = hardware_rand64_fini;
    break;
  case INPUT_LRAND48_R:
  case INPUT_FILE: //LRAND would fall into this case as well
    init = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
    break;
  default:
    fprintf(stderr, "Invalid input type\n");
    return 1;
  }

  init (&options);

  int sizeOfBytes = sizeof rand64();
  int nbytes = options.numberOfBytes;
  int output_errno = 0;
  char *buffer = NULL;
  size_t buffer_size = 0;
  size_t buffer_pos = 0;

  do
    {
      unsigned long long x = rand64 (); // randomization
      int outbytes = nbytes < sizeOfBytes ? nbytes : sizeOfBytes;
      if (options.outputType == STDIO) {
        if (!writeStdio(x, outbytes)) {
	  output_errno = errno;
	  break;
	}
      } else {
        if(!writeBytes(x, outbytes, options.outputSize, &buffer,
				&buffer_size, &buffer_pos)) {
	  output_errno = errno;
	  break;
        }
      }
      nbytes -= outbytes;
    } 
  while (nbytes > 0); 
  
  if (options.outputType == WRITE)
    writeOutput(buffer, buffer_pos, options.outputSize);
  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output error");
    }

  finalize ();
  return !!output_errno;
}

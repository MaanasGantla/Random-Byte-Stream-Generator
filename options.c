#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "options.h"



void optionsScanner(int argc, char *argv[], struct options *optionsStruct) {
    optionsStruct->outputSize = 0;
    optionsStruct->inputFile = NULL;
    optionsStruct->outputType = STDIO;
    optionsStruct->inputType = DEFAULT;
    bool isValid = false;
    int option;
    char *pointerToEndOfBuffer;


    while ((option = getopt(argc, argv, "i:o:")) != -1) 
    {
        switch (option) {
            //test for the type of input
            case 'i':
                if (strcmp(optarg, "lrand48_r") == 0) 
                {
                    optionsStruct->inputType = INPUT_LRAND48_R;
                } else if (strcmp(optarg, "rdrand") == 0) 
                {
                    optionsStruct->inputType = INPUT_RDRAND;
                } else if (optarg[0] == '/') 
                {
                    optionsStruct->inputFile = optarg;
		            optionsStruct->inputType = INPUT_FILE;
                } else 
                {
                    fprintf(stderr, "The input was invalid: %s\n", optarg);
                    exit(1);
                }
                break;
            //test for the type of output
            case 'o': 
                if (strcmp(optarg, "stdio") == 0) 
                {
                    optionsStruct->outputType = STDIO;
                } else 
                {
                    optionsStruct->outputType = WRITE;
                    optionsStruct->outputSize = atoi(optarg);
                    if (optionsStruct->outputSize <= 0) 
                    {
                        fprintf(stderr, "Invalid block size for output: %s\n", optarg);
                        exit(1);
                    }
                }
                break;
            default:
                fprintf(stderr, "The usage of this command is: %s [-i input] [-o output] numberOfBytes\n", argv[0]);
                exit(1);
        }
    }

    //otherwise, no bytes were passed to the function
    if (optind >= argc) 
    {
        fprintf(stderr, "There weren't any bytes passed into the function \n");
        exit(1);
    }

  
    errno = 0;
    optionsStruct->numberOfBytes = strtoll(argv[optind], &pointerToEndOfBuffer, 10);
    if (errno) 
    {
        perror (argv[optind]);
    }
    else 
	isValid = !*pointerToEndOfBuffer && (optionsStruct->numberOfBytes >= 0);
    

    optionsStruct->errnoGlobal = errno;
    if (!isValid) 
    {
        fprintf(stderr, "Invalid numberOfBytes: %s\n", argv[optind]);
        exit(1);
    }
    if (optionsStruct->numberOfBytes == 0)
	exit(0);
}


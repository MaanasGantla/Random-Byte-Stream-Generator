#ifndef OPTIONS_H
#define OPTIONS_H




enum inputType
{
    INPUT_LRAND48_R,
    INPUT_FILE,
    INPUT_RDRAND,
    DEFAULT
};

enum outputType
{
    WRITE,
    STDIO
};

struct options
{
    enum inputType inputType;
    enum outputType outputType;
    long long int numberOfBytes; //we need a long long since this will guarantee an 8 byte quantity regardless of machine
    int errnoGlobal;
    int outputSize;
    const char* inputFile;
};

void optionsScanner(int argc, char **argv, struct options *options); //parses the number of options and the contents of the options themselves


#endif




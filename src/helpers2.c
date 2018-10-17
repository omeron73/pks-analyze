#include "headers/helpers2.h"

int read_two_bytes_to_int(const unsigned char * start){

    unsigned char value[4] = {0};

    value[1] = start[0];
    value[0] = start[1];
    unsigned int * result = (int*)value;

    return *result;

}
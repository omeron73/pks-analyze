#include <stdio.h>
#include "config_parser.h"
#include "tcp.h"

int analyze_packet(const unsigned char * data, const int filter, FILE * file);
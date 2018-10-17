#include <stdio.h>
#include "tcp.h"
#include "icmp.h"

int analyze_packet(const unsigned char * data, const int filter, FILE * file);
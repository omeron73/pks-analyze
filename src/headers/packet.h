#include <stdio.h>
#include "tcp.h"
#include "icmp.h"
#include "udp.h"

int analyze_packet(const unsigned char * data, const int filter, FILE * file);
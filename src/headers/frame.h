#include <stdio.h>
#include <pcap.h>
#include "packet.h"

int analyze_frame(const unsigned char * data, const int filter, const int counter, struct pcap_pkthdr * header);

#include "headers/usage.h"

void print_usage(void){

    printf("Usage: ./analyze [--file FILENAME][OPTIONS]\n\n");
    printf("Available options: \n");

    printf("none            Running without specified option: Program reads data file and writes output to stdout\n\n");
    printf("-f [FILTER]     Filter option. Implemented filters: http, https, telnet, ssh, ftp-control, ftp-data, tftp, icmp, arp.\n\n");

    printf("Example :\n     ./analyze --file eth-1.pcap -f http\n\n");

    return;

}
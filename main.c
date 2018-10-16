#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include "src/headers/config_parser.h"
#include "src/headers/usage.h"
#include "src/headers/frame.h"
#include "src/headers/helpers.h"

void analyze(const int filter_id, const char * filename);

int main(int argc, char const *argv[])
{
    
    switch (argc){
        case 3:
                analyze(0, argv[3]);
                break;
        case 5:
                analyze(get_filter_id(argv[4]), argv[3]);
                break;
        default:
                print_usage();
                break;
    }
    return 0;
}

void analyze(const int filter_id, const char * filename){

    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t * file = pcap_open_offline(filename, errbuff);
    
    struct pcap_pkthdr * header;
    const unsigned char * data;

    int frame_number = 0;

    //main loop
    while ( pcap_next_ex(file, &header, &data) == 1 ){

        //print frame number
        
    }

    return;
}
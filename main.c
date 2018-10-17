#include <stdio.h>
#include "src/headers/usage.h"
#include "src/headers/analyze_all.h"
#include "src/headers/frame.h"

void analyze_with_filter(const char * filename, const char * filter);

int main(int argc, char const *argv[]){
    
    switch (argc){
        case 3:
                analyze_all(argv[2]);
                print_file(".temp/all.tmp");
                break;
        case 5:
                analyze_with_filter(argv[2], argv[4]);
                break;
        default:
                print_usage();
                break;
    }

    return 0;
}

void analyze_with_filter(const char * filename, const char * filter){

    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t * file = pcap_open_offline(filename, errbuff);
    
    struct pcap_pkthdr * header;
    const unsigned char * data;

    int frame_counter = 0;

    //main loop
    while ( pcap_next_ex(file, &header, &data) == 1 ){

        frame_counter++;
        
        if (analyze_frame(data, get_filter_id(filter), frame_counter, header) == 0){
            print_file(".temp/frame.tmp");
        }

    } // end of main loop

    return;
}
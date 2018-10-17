#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include "src/headers/config_parser.h"
#include "src/headers/usage.h"
#include "src/headers/frame.h"
#include "src/headers/helpers.h"

void analyze_all(const char * filename);

int main(int argc, char const *argv[])
{
    
    switch (argc){
        case 3:
                analyze_all(argv[2]);
                print_file("temp/all.tmp");
                break;
        case 5:
                // analyze_all(argv[2]);            //deep analyze
                //decision mechanism, what to print
                break;
        default:
                print_usage();
                break;
    }

    return 0;
}

void analyze_all(const char * filename){

    FILE * all = fopen("temp/all.tmp", "w");

    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t * file = pcap_open_offline(filename, errbuff);
    
    struct pcap_pkthdr * header;
    const unsigned char * data;

    int frame_number = 1;

    //main loop
    while ( pcap_next_ex(file, &header, &data) == 1 ){

        //print frame number
        fprintf(all, "ramec %d\n", frame_number++);

        //dlzka ramca pcap api
        fprintf(all, "dlzka ramca poskytnuta pcap API - %d B\n", header->len);

        //dlzka prenasana po mediu
        int real_size;
        if (header->len < 60){
            real_size = 64;
        }
        else{
            real_size = header->len + 4;
        }
        fprintf(all, "dlzka ramca prenasana po mediu - %d B\n", real_size);

        //type
        int type;
        memcpy(&type, &data[12], 1);
        
        if (type > 0x05){
            fprintf(all, "Ethernet II\n");
        }
        else{
            type = data[14];
            memcpy(&type, &data[14], 1);
            if (type == 0xFF){
                fprintf(all, "IEEE 802.3 - Raw\n");
            }
            else if (type == 0xAA){
                fprintf(all, "IEEE 802.3 - LLC + SNAP\n");
            }
            else{
                fprintf(all, "IEEE 802.3 - LLC\n");
            }

        }

        //source MAC
        fprintf(all, "Zdrojova MAC adresa: ");
        for (int i = 6; i < 12; i++){
            fprintf(all, "%.2X ", data[i]);
        }  
        fprintf(all, "\n");

        //destination address
        fprintf(all, "Cielova MAC adresa: ");
        for (int i = 0; i < 6; i++){
            fprintf(all, "%.2X ", data[i]);
        }  
        fprintf(all, "\n");

        //print data
        for (int i = 0; i < header->len; i++){
            fprintf(all, "%.2X ", data[i]);
            if (( i + 1 )%16 == 0){
                fprintf(all, "\n");
            }
            else if (( i + 1 )%8 == 0){
                fprintf(all, " ");
            }
        }
        fprintf(all, "\n\n");


    }

    return;
}
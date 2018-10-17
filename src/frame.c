#include "headers/frame.h"

int analyze_frame(const unsigned char * data, const int filter, const int counter, struct pcap_pkthdr * header){

    FILE * file = fopen(".temp/frame.tmp", "w");

    fprintf(file, "Ramec %d\n", counter);
    fprintf(file, "dlzka ramca poskytnuta pcap API - %d B\n", header->len);

    //dlzka prenasana po mediu
    int real_size;
    if (header->len < 60){
        real_size = 64;
    }
    else{
        real_size = header->len + 4;
    }
    fprintf(file, "dlzka ramca prenasana po mediu - %d B\n", real_size);

    //type
    if (data[12] > 0x05){
        fprintf(file, "Ethernet II\n");
    }
    else{
        if (data[14] == 0xFF){
            fprintf(file, "IEEE 802.3 - Raw\n");
        }
        else if (data[14] == 0xAA){
            fprintf(file, "IEEE 802.3 - LLC + SNAP\n");
        }
        else{
            fprintf(file, "IEEE 802.3 - LLC\n");
        }

    }

    //source MAC
    fprintf(file, "Zdrojova MAC adresa: ");
    for (int i = 6; i < 12; i++){
        fprintf(file, "%.2X ", data[i]);
    }  
    fprintf(file, "\n");

    //destination address
    fprintf(file, "Cielova MAC adresa: ");
    for (int i = 0; i < 6; i++){
        fprintf(file, "%.2X ", data[i]);
    }  
    fprintf(file, "\n");

    //check if should be written to output
    if (analyze_packet(data, filter) != 0){
        return 1;
    }

    //print data
    for (int i = 0; i < header->len; i++){
        fprintf(file, "%.2X ", data[i]);
        if (( i + 1 )%16 == 0){
            fprintf(file, "\n");
        }
        else if (( i + 1 )%8 == 0){
            fprintf(file, " ");
        }
    }
    fprintf(file, "\n\n");

    return 0;
}
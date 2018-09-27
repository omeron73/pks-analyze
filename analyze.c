#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("Usage: ./analyze [path to .pcap file]\n");
    }

    pcap_t * file;
    char errbuff[PCAP_ERRBUF_SIZE];

    file = pcap_open_offline(argv[1], errbuff);
    struct pcap_pkthdr * header;
    const unsigned char * data;
    int i = 0, status, lenght;

    while ((status = pcap_next_ex(file, &header, &data)) == 1){
        i++;
        printf("Ramec %d\n", i);
        printf("dlzka ramca poskytnuta pcap API - %d B\n", header->len);
        if (header->len <= 60){
            lenght = 64;
        }
        else{
            lenght = header->len + 4;
        }
        printf("dlzka ramca prenasaneho po mediu - %d B\n", lenght);
        
        int type;
        memcpy(&type, &data[12], 2);
        if (type > 0x05DC){
            printf("Ethernet II");
        }
        else{
            memcpy(&type, &data[13], 1);
            if (type == 0xFF){
                printf("IEEE 802.3 - Raw");
            }
            else if (type == 0xAA){
                printf("IEEE 802.3 - LLC - SNAP");
            }
            else{
                printf("IEEE 802.3 - LLC");
            }
        }
        printf("\n");
    
        printf("Zdrojova MAC adresa: ");
        for(int y = 6; y < 12; y++){
            printf("%.2X", data[y]);
            if (y < 11){
                printf(":");
            }
        }
        printf("\n");

        printf("Cielova MAC adresa: ");
        for(int y = 0; y < 6; y++){
            printf("%.2X", data[y]);
            if (y < 5){
                printf(":");
            }
        }
        printf("\n");

        //print frame dump 
        for (int y = 0; y < header->len; y++){
            printf("%.2X", data[y]);
            printf(" ");
            if ((y + 1 )%16 == 0){
                printf("\n");
            }
            else if ((y + 1 )%8 == 0){
                printf(" ");
            }
        }
        printf("\n\n");


    }

    return 0;
}

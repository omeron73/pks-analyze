#include "headers/analyze_all.h"

void analyze_all(const char * filename){

    FILE * all = fopen(".temp/all.tmp", "w");
    FILE * ips = fopen(".temp/ips.tmp", "w");

    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t * file = pcap_open_offline(filename, errbuff);
    
    struct pcap_pkthdr * header;
    const unsigned char * data;

    int frame_number = 1;

    ip_addr * ip = (ip_addr*)malloc(sizeof(ip_addr));
    ip_addr * head = ip;
    ip->bytes = 0;
    ip->next = NULL;

    char * ip_a = (char*)malloc(20);

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
        
        
        if (read_2_bytes_to_int(&data[12]) > 0x05DC){
            fprintf(all, "Ethernet II\n");
        }
        else{
            if (data[14] == 0xFF){
                fprintf(all, "IEEE 802.3 - Raw\n");
            }
            else if (data[14] == 0xAA){
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

        //ip address fun
        if (data[12] > 0x05){

            sprintf(ip_a, "%d.%d.%d.%d", data[26], data[27], data[28], data[29]);
            add_ip(head, ip_a, real_size);

        }
        
    }

    int max = write_ips(ips, head), x;

    //ip printout
    fclose(ips);
    
    ips = fopen(".temp/ips.tmp", "r");
    char * temp = malloc(20);
    fprintf(all, "IP adresy vysielajucich uzlov:\n");
    while (fscanf(ips, "%s%d", ip_a, &x) != EOF){

        fprintf(all, "%s\n", ip_a);
        if (x == max) memcpy(temp, ip_a, 20);

    }
    fprintf(all, "\nAdresa uzla s najvyzsim poctom odvysielanych bajtov:\n");
    fprintf(all, "%s\t%d bajtov\n", temp, max);

    fclose(ips);
    fclose(all);

    return;
}
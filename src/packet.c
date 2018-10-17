#include "headers/packet.h"

int analyze_packet(const unsigned char * data, const int filter, FILE * file){
    
    ini_list * ethertype = parse_ini("tables/ethertype.ini", 0);

    char * type = lookup(read_two_bytes_to_int(&data[12]), ethertype);
    fprintf(file, "%s\n", type);

    fprintf(file, "Zdrojova IP adresa: %d.%d.%d.%d\n", data[26], data[27], data[28], data[29]);
    fprintf(file, "Cielova IP adresa: %d.%d.%d.%d\n", data[30], data[31], data[32], data[33]);

    ini_list * ipv4 = parse_ini("tables/IPv4.ini", 1);

    char * protocol = lookup(data[23], ipv4);
    fprintf(file, "%s\n", protocol);

    int length = data[14] & 0x0F;

    if (read_two_bytes_to_int(&data[12]) == 2054){
        return 1;           //arp, should not be here
    }

    if (data[23] == 6){
        if (analyze_segment(&data[14+(4*length)], filter, file) != 0){
            return 1;
        }
    }
    else if (data[23] == 17){
        if (analyze_datagram(&data[14+(4*length)], filter, file) != 0){
            return 1;
        }
    }
    else if (data[23] == 1){
        if (analyze_ICMP(&data[14+(4*length)], filter, file) != 0){
            return 1;
        }
    }

    return 0;
}
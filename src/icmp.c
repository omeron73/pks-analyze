#include "headers/icmp.h"

int analyze_ICMP(const unsigned char * data, const int filter, FILE * file){

    int type = *data;

    ini_list * icmp = parse_ini("tables/icmp.ini", 0);

    fprintf(file, "%d - %s\n", type, lookup(type, icmp));

    if ( filter == 8){
        return 0;
    }
    if ( (filter == 12) && (type == 3) ){
        return 0;
    }

    return 1;
}
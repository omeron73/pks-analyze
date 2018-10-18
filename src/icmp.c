#include "headers/icmp.h"

int analyze_ICMP(const unsigned char * data, const int filter, FILE * file){

    int type = *data;
    static int pocet = 0;
    FILE * pocet_file = fopen(".temp/pocet.tmp", "w");
    ini_list * icmp = parse_ini("tables/icmp.ini", 0);

    fprintf(file, "%d - %s\n", type, lookup(type, icmp));

    if ( filter == 8){
        return 0;
    }
    if ( (filter == 12) && (type == 3) ){
        pocet++;
        fprintf(pocet_file, "%d\n", pocet);
        fclose(pocet_file);
        return 0;
        
    }

    return 1;
}
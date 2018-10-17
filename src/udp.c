#include "headers/udp.h"

int analyze_datagram(const unsigned char * data, const int filter, FILE * file){

    int source_p = read_bytes_to_int(data);
    fprintf(file, "zdrojovy port: %d\n", source_p);

    int dest_p = read_bytes_to_int(&data[2]);
    fprintf(file, "cielovy port: %d\n", dest_p);

    static int port = 0;
    if (source_p == 69){
        port = dest_p;
    }
    else if (dest_p == 69){
        port = source_p;
    }

    if ( (filter == 7) && ( (source_p == 69) || (dest_p == 69) ) ){
        return 0;          //tftp
    }
    if ( (filter == 7) && (port != 0) && ( (source_p == port) || (dest_p == port) ) ){
        return 0;          //tftp with random port
    }

    return 1;

}
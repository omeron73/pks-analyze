#include "headers/tcp.h"

int analyze_segment(const unsigned char * data, const int filter, FILE * file){

    int source_p = read_two_bytes_to_int(data);
    fprintf(file, "zdrojovy port: %d\n", source_p);

    int dest_p = read_two_bytes_to_int(&data[2]);
    fprintf(file, "cielovy port: %d\n", dest_p);
    
    if ( (filter == 1) && ( (source_p == 80) || (dest_p == 80) ) ){
        return 0;          //http
    }
    else if ( filter == 10 ){
        return 0;          //tcp all protocols
    }
    else if ( (filter == 2) && ( (source_p == 443) || (dest_p == 443) ) ){
        return 0;          //https
    }
    else if ( (filter == 3) && ( (source_p == 23) || (dest_p == 23) ) ){
        return 0;          //telnet
    }
    else if ( (filter == 4) && ( (source_p == 22) || (dest_p == 22) ) ){
        return 0;          //ssh
    }
    else if ( (filter == 5) && ( (source_p == 21) || (dest_p == 21) ) ){
        return 0;          //ftp-control
    }
    else if ( (filter == 6) && ( (source_p == 20) || (dest_p == 20) ) ){
        return 0;          //ftp-data
    }

    return 1;
}
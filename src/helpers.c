#include "headers/helpers.h"

int get_filter_id(const char * filter){

    if (strcmp("http", filter) == 0){
        return 1;
    }
    else if (strcmp("https", filter) == 0){
        return 2;
    }
    else if (strcmp("telnet", filter) == 0){
        return 3;
    }
    else if (strcmp("ssh", filter) == 0){
        return 4;
    }
    else if (strcmp("ftp-control", filter) == 0){
        return 5;
    }
    else if (strcmp("ftp-data", filter) == 0){
        return 6;
    }
    else if (strcmp("tftp", filter) == 0){
        return 7;
    }
    else if (strcmp("icmp", filter) == 0){
        return 8;
    }
    else if (strcmp("arp", filter) == 0){
        return 9;
    }

    return 0;
}

void print_file(const char * filename){

    FILE * fd = fopen(filename, "r");

    char c;
    while ( (c = fgetc(fd)) != EOF ){
        printf("%c", c);
    }

    return;
}

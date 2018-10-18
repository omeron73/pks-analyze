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
    else if (strcmp("tcp", filter) == 0){
        return 10;
    }
    else if (strcmp("udp", filter) == 0){
        return 11;
    }
    else if (strcmp("icmp-dest_unreach", filter) == 0){
        return 12;
    }

    return 0;
}

void print_file(const char * filename){

    FILE * fd = fopen(filename, "r");

    char c;
    while ( (c = fgetc(fd)) != EOF ){
        printf("%c", c);
    }

    fclose(fd);
    return;
}

void add_ip(ip_addr * head, const char * ip_a, int size){

    while (head != NULL){

        if (head->bytes == 0){
            head->bytes = size;
            memcpy(head->addr, ip_a, 20);
            return;
        }
        else if (strcmp(head->addr, ip_a) == 0){
            head->bytes += size;
            return;
        }
        else if (head->next != NULL){
            head = head->next;
            continue;
        }
        else{
            head->next = malloc(sizeof(ip_addr));
            head = head->next;
            memcpy(head->addr, ip_a, 20);
            head->bytes = size;
            head->next = NULL;
            return;
        }

    }

}

int write_ips(FILE * file, ip_addr * head){

    int max = 0;
    while (head != NULL){
        fprintf(file, "%s %d\n", head->addr, head->bytes);
        if (max < head->bytes) max = head->bytes;

        head = head->next;
    }

    return max;

}

int read_2_bytes_to_int(const unsigned char * start){

    unsigned char value[4] = {0};

    value[1] = start[0];
    value[0] = start[1];
    unsigned int * result = (int*)value;

    return *result;

}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ip_addr{
    char addr[20];
    int bytes;
    struct ip_addr * next;
}ip_addr;

int get_filter_id(const char * filter);
void print_file(const char * filename);
void add_ip(ip_addr * head, const char * ip_a, int size);
int write_ips(FILE * file, ip_addr * head);

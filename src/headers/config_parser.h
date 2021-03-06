#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ini_list{
    char name[50];
    int value;
    struct ini_list * next_entry;
}ini_list;

ini_list * parse_ini(char * destination, int section);
void print_ini_list(ini_list * head);
char * lookup(int value, ini_list* head);

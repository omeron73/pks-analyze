#include "headers/config_parser.h"

ini_list * parse_ini(char * destination, int section){

    FILE * fd = fopen(destination, "r");
    
    char c;
    
    //iterate through file to desired section

        fgetc(fd);  //consume first [
            
        for (int i = 0; i < section; i++){

            while( (c = fgetc(fd)) != '[' ){
                ;
            }

        }
    
    //iterate through section name

        while ( (c = fgetc(fd)) != ']' ){
            ;       //consume section name
        }
        fgetc(fd);  //consume newline

    //create root

        ini_list * head = NULL;

    //add all name=value pairs to the list

        ini_list * node = malloc(sizeof(ini_list));
        head = node;
        int i;
        while ( (c = fgetc(fd)) != EOF ){
            
            if ( c == '\n') break;

            i = 0;
            node->name[i++] = c;
            while ( (c = fgetc(fd)) != '=' ){
                node->name[i++] = c;
            }
            node->name[i] = '\0';

            //scan value
            fscanf(fd, "%d", &node->value);

            fgetc(fd); //newline 

            node->next_entry = malloc(sizeof(ini_list));
            node = node->next_entry;

        }

        node->next_entry = NULL;

    //return head *

    return head;

}

char * lookup(int value, ini_list* head){

    char * key = (char*)malloc(50);

    do{
        if (head->value == value){
            memcpy(key, head->name, sizeof(head->name));
            break;
        }
        head = head->next_entry;
    }while (head->next_entry != NULL);

    return key;

}

void print_ini_list(ini_list * head){

    while (head->next_entry != NULL){

        printf("%s = %d\n", head->name, head->value);
        head = head->next_entry;

    }

    return;
}
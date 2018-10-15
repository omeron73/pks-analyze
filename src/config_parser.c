#include "headers/config_parser.h"

ini_list * parse_ini(char * destination, int section){

    FILE * fd = fopen(*destination, "r");

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

        while (1);

    //return head *

}
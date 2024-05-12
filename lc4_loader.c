    /************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"
#include "lc4_hash.h"
#include <string.h>

/* declarations of functions that must defined in lc4_loader.c */

/**
 * opens up name of the file passed in, returns a pointer
 * to the open file
 *
 * returns the FILE pointer upon success, else NULL.
 */
FILE* open_file(char* file_name)
{
	/* checking if the filename is null */
    if( file_name == NULL )
    {
        return NULL;
    }
    /* length of the filename */
    int len = strlen(file_name);

    /* Check if the file name ends with ".obj" (case insensitive) */
    if (len >= 4 && strcasecmp(file_name + len - 4, ".obj") == 0) {
        return fopen(file_name, "rb");    /* Open in read-binary mode if file name ends with ".obj" */
    }
    return fopen(file_name, "w");        // opening other type of files in write mode 
    return NULL ;
}

/**
 * parses the given input file into hashtable
 *
 * returns 0 upon successs, non-zero if an error occurs.
 */
int parse_file (FILE* my_obj_file, lc4_memory_segmented* memory)
{
	unsigned short int *data = (unsigned short int *)malloc(sizeof(unsigned short int));
    int ret = -1;
    int loopCount = 1;
    while(1)
    {
        ret = fread(data, 2, 1, my_obj_file);
        if( ret != 1 ) {
            // Reached end of file 
            break;
        }
        
        // data read 
        unsigned short int header, address, n;
        row_of_memory* rom;
        header = *data;
        header = (header << 8) | (header >> 8);

        char str[100000];
        char digit[2];

        switch(header)
        {
        case 0xDADA: // Data: 3-word header (0xDADA, <address>, <n>), n-word body comprising the initial data values
            fread(data, 2, 1, my_obj_file);
            address = *data;                                  // fetching address 
            address = (address << 8) | (address >> 8);
            fread(data, 2, 1, my_obj_file);
            n = *data;                                        // fetching n 
            n = (n << 8) | (n >> 8);

            for( int i = 0; i < n; ++i )
            {
                fread(data, 2, 1, my_obj_file);
                unsigned short int temp = *data;              // fetching data 
                temp = (temp << 8) | (temp >> 8);

                rom = (search_tbl_by_address(memory, address+i));
                /* variations are also handled */
                if( rom == NULL ) {
                    add_entry_to_tbl(memory, address + i, temp);  // adding new data into table
                }
                if( rom != NULL){
                    rom->address = address;
                    rom->contents = temp;
                }
            }
            break;
        case 0xCADE: // Code: 3-word header (0xCADE, <address>, <n>), n-word body comprising the instructions
            fread(data, 2, 1, my_obj_file);
            address = *data;                                  // fetching address 
            address = (address << 8) | (address >> 8);
            fread(data, 2, 1, my_obj_file);
            n = *data;                                        // fetching n 
            n = (n << 8) | (n >> 8);

            for( int i = 0; i < n; ++i )
            {
                fread(data, 2, 1, my_obj_file);
                unsigned short int temp = *data;              // fetching instructions 
                temp = (temp << 8) | (temp >> 8);
                
                rom = (search_tbl_by_address(memory, address+i));
                /* variations are also handled */
                if( rom == NULL ) {
                    add_entry_to_tbl(memory, address + i, temp);  // adding new instructions into table
                }
                if( rom != NULL){
                    rom->address = address;
                    rom->contents = temp;
                }
            }
            break;
        case 0xC3B7: // Symbol: 3-word header (0xC3B7, <address>, <n>), n-character body of the symbol string
            fread(data, 2, 1, my_obj_file);
            address = *data;
            address = (address << 8) | (address >> 8);
            fread(data, 2, 1, my_obj_file);
            n = *data;
            n = (n << 8) | (n >> 8);

            strcpy(str, "");
            for( int i = 0; i < n; ++i )
            {
                fread(data, 1, 1, my_obj_file);
                char ch = *data;
                digit[0] = ch;
                digit[1] = '\0';
                strcat(str, digit);
            }
            rom = (search_tbl_by_address(memory, address));
            /* variations are also handled */
            if( rom == NULL ) {
                add_entry_to_tbl(memory, address, 0);
                rom = (search_tbl_by_address(memory, address));
            }
            if( rom != NULL){
                rom->label = (char*)malloc(10000 * sizeof(char));
                strcpy(rom->label, "");
                strcpy(rom->label, str);
            }  // updating label into table 
            break;
        case 0xF17E: // File name: 2-word header (0xF17E, <n>), n-character body comprising the file name string 
            fread(data, 2, 1, my_obj_file);
            n = *data;
            n = (n << 8) | (n >> 8);

            for( int i = 0; i < n; ++i )
            {
                fread(data, 1, 1, my_obj_file);
                // don't need to populate memory with this data 
            }
            break;
        case 0x715E: // Line number: 4-word header (0x715E, <address>, <line>, <file-index>), no body
            fread(data, 2, 1, my_obj_file);
            fread(data, 2, 1, my_obj_file);
            fread(data, 2, 1, my_obj_file);
            break;
        default:
            // printf("Unrecognized data. Hitting default case from switch. (lc4_loader.c->parse_file())");
            // return -1;
            // free(data);
            break;
        }
    }
    free(data);
    return 0;
}

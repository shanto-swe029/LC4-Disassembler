/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"
#include "lc4_hash.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

int my_hash_function(void* table, void *key);

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {

	/**
	 * main() holds the hashtable &
	 * only calls functions in other files
	 */
    
    /*
    * If no file is passed in, error1: usage: ./lc4 <output_filename.asm> <object_file.obj>
    */
    if( argc < 3 ) {
        printf("error1: usage: ./lc4 <output_filename.asm> <object_file.obj>\n");
        return 1;
    }

	/* step 1: create a pointer to the hashtable: memory 	*/
	lc4_memory_segmented* memory = NULL ;

	/* step 2: call create_hash_table() and create 4 buckets 	*/
    memory = create_hash_table(4, &my_hash_function);

	
	/* step 5: repeat steps 3 and 4 for each .OBJ file in argv[] 	*/
    for( int i = 2; i < argc; ++i )
    {
        /* step 3: determine filename, then open it		*/
        char* filename = argv[i];                    // extract filename from argv
        FILE* file = open_file(filename);            // pass it to open_file()

        /* step 4: call function: parse_file() in lc4_loader.c 	*/
        /*   call function & check for errors		*/
        int ret = parse_file(file, memory);
        fclose(file);
    }

	/* step 6: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
    int ret = reverse_assemble(memory);

    if( ret != 0 )
    {
        printf("error2: could not parse the complete file.\n");
        return 1;
    }

	/* step 7: call function: print out the hashtable to output file */
    char* output_filename = argv[1];
    FILE* output_file = open_file(output_filename);
    print_table(memory, output_file);
    fclose(output_file);

	/* step 8: call function: delete_table() in lc4_hash.c */
    delete_table(memory);

	/* only return 0 if everything works properly */
	return 0 ;
}

int my_hash_function(void* table, void *key)
{
    // Cast the key back to the expected type (unsigned short int)
    unsigned short int address = *(unsigned short int*)key;

    // Access the hash table structure to find the number of buckets
    lc4_memory_segmented* hash_table = (lc4_memory_segmented*)table;
    int num_buckets = hash_table->num_of_buckets;

    // Compute the hash value
    int hash_value = -1;
    if( address < 0x2000 ) {
        hash_value = 0;
    }
    else if( address < 0x8000 ) {
        hash_value = 1;
    }
    else if ( address < 0xA000 ) {
        hash_value = 2;
    }
    else {
        hash_value = 3;
    }
    return hash_value;
}

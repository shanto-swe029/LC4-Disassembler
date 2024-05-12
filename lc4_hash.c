/************************************************************************/
/* File Name : lc4_hash.c		 										*/
/* Purpose   : This file contains the definitions for the hash table  	*/
/*																		*/
/* Author(s) : tjf 														*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_hash.h"

/*
 * creates a new hash table with num_of_buckets requested
 */
lc4_memory_segmented* create_hash_table (int num_of_buckets, 
             					         int (*hash_function)(void* table, void *key) ) 
{
	// allocate a single hash table struct
    lc4_memory_segmented* table = (lc4_memory_segmented*) malloc(sizeof(lc4_memory_segmented));
    if (table == NULL) {
        return NULL;        // Memory allocation failed
    }
	// allocate memory for the buckets (head pointers)
    table->buckets = (row_of_memory**) malloc(num_of_buckets * sizeof(row_of_memory*));
    if (table->buckets == NULL) {
        free(table);        // Memory allocation failed, clean up previously allocated memory
        return NULL;
    }
    // Initialize all bucket head pointers to NULL
    for (int i = 0; i < num_of_buckets; i++) {
        table->buckets[i] = NULL;
    }
    table->num_of_buckets = num_of_buckets;        // Assign the number of buckets
	// assign function pointer to call back hashing function
    table->hash_function = hash_function;

	return table;
}


/*
 * adds a new entry to the table
 */
int add_entry_to_tbl (lc4_memory_segmented* table, 
					  unsigned short int address,
			    	  unsigned short int contents) 
{
	if (table == NULL) {
        return -1;        // Error if table pointer is NULL
    }
    // apply hashing function to determine proper bucket #
    int bucket = table->hash_function(table, /*(void*)(uintptr_t)*/ &address);
    if (bucket < 0 || bucket >= table->num_of_buckets) {
        return -1;        // Error if bucket number is out of range
    }
	// add to bucket's linked list using linked list add_to_list() helper function
    if (add_to_list(&(table->buckets[bucket]), address, contents) != 0) {
        return -1;        // Return -1 if adding to the list fails
    }
	return 0 ;
}

/*
 * search for an address in the hash table
 */
row_of_memory* search_tbl_by_address 	(lc4_memory_segmented* table,
			                   			 unsigned short int address ) 
{
	if (table == NULL) {
        return NULL;        // Return NULL if the table is not initialized
    }
    /* apply hashing function to determine bucket # item must be located in */
    int bucket = table->hash_function(table, &address);
    if (bucket < 0 || bucket >= table->num_of_buckets) {
        return NULL;        // Return NULL if the bucket number is out of range
    }
	// invoked linked_lists helper function, search_by_address() to return return proper node
	return search_address(table->buckets[bucket], address);
}

/*
 * prints the linked list in a particular bucket
 */
void print_bucket (lc4_memory_segmented* table, 
				   int bucket_number,
				   FILE* output_file ) 
{
	if (table == NULL || output_file == NULL) {
        return;        // Return if table or output file is not initialized
    }
    // Check if the bucket number is valid
    if (bucket_number < 0 || bucket_number >= table->num_of_buckets) {
        fprintf(output_file, "Invalid bucket number.\n");
        return;
    }
    // call the linked list helper function to print linked list
    print_list(table->buckets[bucket_number], output_file);
	return ;
}

/*
 * print the entire table (all buckets)
 */
void print_table (lc4_memory_segmented* table, 
				  FILE* output_file ) 
{
	if (table == NULL || output_file == NULL) {
        return;        // Return if table or output file is not initialized
    }
    // Iterate through each bucket of the hash table
    for (int i = 0; i < table->num_of_buckets; i++) {
        // call the linked list helper function to print linked list to output file for each bucket
        print_bucket(table, i, output_file);
        fprintf(output_file, "\n");
    }
	return ;
}

/*
 * delete the entire table and underlying linked lists
 */
void delete_table (lc4_memory_segmented* table ) 
{
	if (table == NULL) {
        return; // Return if table is not initialized
    }
    // call linked list delete_list() on each bucket in hash table
    for (int i = 0; i < table->num_of_buckets; i++) {
        delete_list(&(table->buckets[i]));
    }
	// then delete the table itself
    free(table->buckets);
    free(table);
}

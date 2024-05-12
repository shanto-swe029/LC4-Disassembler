/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"


/*
 * adds a new node to linked list pointed to by head
 * return 0 for success, -1 if malloc fails
 */
int add_to_list (row_of_memory** head,
		 		 unsigned short int address,
		 		 unsigned short int contents)
{

	/* allocate memory for a single node */
    row_of_memory* new_node = (row_of_memory*)malloc(sizeof(row_of_memory));

    /* checking if malloc fails */
    if (new_node == NULL) {
        return -1;
    }

	/* populate fields in newly allocated node with arguments: address/contents */
    new_node->address = address;
    new_node->contents = contents;

    /* make certain to set other fields in structure to NULL */
    new_node->label = NULL;
    new_node->assembly = NULL;
    new_node->next = NULL;

	/* if head==NULL, node created is the new head of the list! */
    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

	/* otherwise, insert the node into the linked list keeping it in order of ascending addresses */
    row_of_memory* current = *head;
    row_of_memory* prev = NULL;

    /* searching for the location where the new node is to be stored */
    while (current != NULL && current->address < address) {
        prev = current;
        current = current->next;
    }

    /* inserting the new node */
    if (prev == NULL) {
        new_node->next = *head;
        *head = new_node;
    } else {
        prev->next = new_node;
        new_node->next = current;
    }

	/* return 0 for success, -1 if malloc fails */
	return 0 ;
}


/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			        		   unsigned short int address )
{
	/* traverse linked list, searching each node for "address"  */
    while( head != NULL )
    {
        if( head->address == address )
        {
            /* return pointer to node in the list if item is found */
            return head;
        }
        head = head->next;
    }

	/* return NULL if list is empty or if "address" isn't found */
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode (row_of_memory* head,
				      		  unsigned short int opcode  )
{
	/* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is empty */
    while( head != NULL )
    {
        if( head->contents == opcode && head->assembly == NULL )
        {
            /* return pointer to node in the list if item is found */
            return head;
        }
        head = head->next;
    }

	/* return NULL if list is empty or if no matching nodes */
	return NULL ;
}

/*
 * delete the node from the linked list with matching address
 */
int delete_from_list (row_of_memory** head,
			          unsigned short int address ) 
{
	if (*head == NULL) {
        return -1;
    }
    /* if head isn't NULL, traverse linked list until node is found with matching address */
    row_of_memory* current = *head;
    row_of_memory* prev = NULL;
    while (current != NULL && current->address != address) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return -1; // Return -1 if the node wasn't found
    }

	/* delete the matching node, re-link the list */

	/* make certain to update the head pointer - if original was deleted */
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    // Free the memory allocated for the deleted node
    free(current);

	/* return 0 if successfully deleted the node from list, -1 if node wasn't found */

	return 0 ;

}

void print_list_console(row_of_memory* head, 
				 FILE* output_file )
{
    /* make sure head isn't NULL */
    if (head == NULL) {
        // fprintf(output_file, "Linked list is empty.\n");
        return;
    }

	/* print out a header to output_file */
    fprintf(output_file, "<label> <address> <contents> <assembly>\n");

	/* traverse linked list, print contents of each node to output_file */
    row_of_memory* current = head;
    while (current != NULL) {
        fprintf(output_file, "%s %04X %04X %s\n",
            (current->label != NULL) ? current->label : "\t",
            current->address, 
            current->contents, 
            (current->assembly != NULL) ? current->assembly : "");
        current = current->next;
    }

	return ;
}

void print_list (row_of_memory* head, 
				 FILE* output_file )
{
	/* make sure head isn't NULL */
    if (head == NULL) {
        // fprintf(output_file, "Linked list is empty.\n");
        return;
    }

    print_list_console(head, output_file);
    return;

	row_of_memory* curr = head;
    row_of_memory* prev = NULL;

    while( curr != NULL )
    {
        if( curr->address < 0x2000 || (curr->address > 0x7FFF && curr->address < 0xA000) ) {
            // Code
            if( prev == NULL ) { 
                if(curr->address < 0x2000) fprintf(".CODE\n.ADDR %d\n", curr->address); 
                else fprintf(".CODE\n.ADDR x%04X\n", curr->address); 
            }
            if(curr->label != NULL) {
                fprintf("%s:\n", curr->label);
            }
            fprintf("%s\n", curr->assembly);
        }
        else {
            // Data 
            if( prev == NULL ) {
                if(curr->address < 0x2000) fprintf(".DATA\n.ADDR %d\n", curr->address);
                else fprintf(".DATA\n.ADDR x%04X\n", curr->address);
            }
            if(curr->label != NULL) {
                fprintf("%s: \n", curr->label);
            }
            fprintf("%s\n", curr->assembly);
        }
        // if curr->next->address != curr->address + 1 : prev = null 
    }

	return ;
}

/*
 * delete entire linked list
 */
void delete_list (row_of_memory** head )
{
	// Pointer to store the next node temporarily
    row_of_memory* next_node;
    /* delete entire list node by node */
    while (*head != NULL) {
        next_node = (*head)->next; // Save the next node
        free((*head)->label);      // Free memory allocated to the label if any
        free((*head)->assembly);   // Free memory allocated to the assembly if any
        free(*head);               // Free the current node
        *head = next_node;         // Move head to the next node
    }
	/* set head = NULL upon deletion */
    *head = NULL;
	return ;
}

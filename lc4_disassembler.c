/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_hash.h"
#include "lc4_memory.h"

char* convert_int_to_string(int n) {
    // Determine the length of the string
    int length = snprintf(NULL, 0, "%d", n);
    
    // Allocate memory for the string (+1 for null terminator)
    char* str = (char*)malloc(length + 1);
    
    // Convert the integer to a string
    snprintf(str, length + 1, "%d", n);
    
    return str;
}

void handle_arith_op(lc4_memory_segmented* memory, row_of_memory* rom)
{
    unsigned short int instr, subop, rd, rs, rt, imm5;
    char assembly[1000];
    char digit[2]; // Temporary array to hold a single character and null terminator
    strcpy(assembly, "");
    instr = rom->contents;
    subop = (instr >> 3) & 0x0007;
    rt = instr & 0x0007;
    rs = (instr >> 6) & 0x0007;
    rd = (instr >> 9) & 0x0007;
    imm5 = instr & 0x001F;

    printf("handle_arith_op()->instr = %04x\t subop = %04x\n", instr, subop);

    switch(subop)
    {
        case 0:
            strcat(assembly, "ADD R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 1:
            strcat(assembly, "MUL R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 2:
            strcat(assembly, "SUB R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 3:
            strcat(assembly, "DIV R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        default:
            strcat(assembly, "ADD R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", #");
            strcat(assembly, convert_int_to_string(imm5));
            break;
    }
    rom->assembly = strdup(assembly);
}

void handle_logical_op(lc4_memory_segmented* memory, row_of_memory* rom)
{
    unsigned short int instr, subop, rd, rs, rt, imm5;
    char assembly[1000];
    char digit[2]; // Temporary array to hold a single character and null terminator
    strcpy(assembly, "");
    instr = rom->contents;
    subop = (instr >> 3) & 0x0007;
    rt = instr & 0x0007;
    rs = (instr >> 6) & 0x0007;
    rd = (instr >> 9) & 0x0007;
    imm5 = instr & 0x001F;

    switch(subop)
    {
        case 0:
            strcat(assembly, "AND R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 1:
            strcat(assembly, "NOT R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 2:
            strcat(assembly, "OR R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 3:
            strcat(assembly, "XOR R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rt;
            digit[1] = '\0';
            strcat(assembly, digit);
            break;
        case 4:
            strcat(assembly, "AND R");
            digit[0] = '0' + rd;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", R");
            digit[0] = '0' + rs;
            digit[1] = '\0';
            strcat(assembly, digit);
            strcat(assembly, ", #");
            strcat(assembly, convert_int_to_string(imm5));
            break;
        default:
            break;
    }
    rom->assembly = strdup(assembly);
}

void handle_branch_op(lc4_memory_segmented* memory, row_of_memory* rom)
{
    unsigned short int instr, subop, imm9;
    unsigned short int label_address;
    char assembly[1000];
    row_of_memory* label_row;
    strcpy(assembly, "");
    instr = rom->contents;
    subop = (instr >> 9) & 0x0007;
    imm9 = instr & 0x01FF;

    // Sign extend imm9 from 9-bit to a 16-bit signed
    int16_t signed_imm9 = (int16_t)(imm9 << 7) >> 7;

    switch (subop) {
        case 0: // NOP
            strcat(assembly, "NOP");
            break;
        case 1: // BRp
            strcat(assembly, "BRp ");
            break;
        case 2: // BRz
            strcat(assembly, "BRz ");
            break;
        case 3: // BRzp
            strcat(assembly, "BRzp ");
            break;
        case 4: // BRn
            strcat(assembly, "BRn ");
            break;
        case 5: // BRnp
            strcat(assembly, "BRnp ");
            break;
        case 6: // BRnz
            strcat(assembly, "BRnz ");
            break;
        case 7: // BRnzp
            strcat(assembly, "BRnzp ");
            break;
        default:
            // Add handling for unexpected subop values if necessary
            strcat(assembly, "<invalid branch>");
            break;
    }

    if( subop == 0 || subop > 7 ) {rom->assembly = strdup(assembly); return;}

    // calculate label address considering PC + 1 (next instruction) + offset
    label_address = rom->address + 1 + signed_imm9;

    // Attempt to find the label at the calculated address
    label_row = search_tbl_by_address(memory, label_address);
    if (label_row && label_row->label) {
        strcat(assembly, label_row->label);
    } else {
        // Handle cases where no label is found
        strcat(assembly, "<unknown>");
    }
    rom->assembly = strdup(assembly);
}

void handle_compare_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    unsigned short int instr, opcode, rs, rt, imm7, uimm7, is_unsigned, is_immediate;
    char assembly[1000];

    instr = rom->contents;
    opcode = (instr >> 12) & 0xF;
    rs = (instr >> 9) & 0x7;
    is_immediate = (instr >> 8) & 0x1;
    is_unsigned = (instr >> 7) & 0x1;

    strcpy(assembly, "");  // Initialize the assembly instruction string

    if (!is_immediate) {
        rt = instr & 0x7; // Target register Rt is in bits 0-2
        if (!is_unsigned) {
            sprintf(assembly, "CMP R%d, R%d", rs, rt);
        } else {
            sprintf(assembly, "CMPU R%d, R%d", rs, rt);
        }
    } 
    else {
        imm7 = instr & 0x7F; // Immediate value IMM7/UIMM7 is in bits 0-6
        if (!is_unsigned) {
            sprintf(assembly, "CMPI R%d, #%d", rs, (int16_t)(imm7 << 9) >> 9); // Sign extend IMM7
        } else {
            sprintf(assembly, "CMPIU R%d, #%d", rs, imm7);
        }
    }

    rom->assembly = strdup(assembly); // Store the assembled instruction string in the memory row
}

void handle_jsr_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    unsigned short int instr, opcode, rs, imm11;
    unsigned short int label_address;
    char assembly[1000];
    row_of_memory* label_row;

    instr = rom->contents;
    opcode = (instr >> 12) & 0xF;

    strcpy(assembly, "");  // Initialize the assembly instruction string

    if ((opcode & 0xF) == 0x4) { // JSRR Rs 0100 0xxs ssxx xxxx (R7 = PC + 1; PC = Rs)
        rs = (instr >> 6) & 0x7; // Extract the source register Rs
        strcat(assembly, "JSRR R");
        strcat(assembly, convert_int_to_string(rs)); // Append the source register to the assembly string
    } 
    else if ((opcode & 0xF) == 0x4 || (opcode & 0xF) == 0xC) { // JSR <Label> 0100 1iii iiii iiii (R7 = PC + 1; PC = (PC & 0x8000) | ((IMM11 offset to <Label>) << 4))
        imm11 = instr & 0x7FF; // Extract the 11-bit immediate offset
        label_address = (rom->address + 1 + ((imm11 & 0x400) ? imm11 | 0xF800 : imm11) << 1); // Calculate the label address
        strcat(assembly, "JSR ");
        strcat(assembly, search_tbl_by_address(memory, label_address)->label); // Append the label to the assembly string
    } else {
        strcat(assembly, "<unknown>");
    }

    rom->assembly = strdup(assembly); // Store the assembly instruction in the ROM
}

void handle_load_store_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    unsigned short int instr, opcode, rd, rs, imm6;
    unsigned short int address;
    char assembly[1000];

    instr = rom->contents; // Fetch the instruction from memory
    opcode = (instr >> 12) & 0xF; // Opcode is encoded in bits 12-15

    strcpy(assembly, ""); // Initialize the assembly instruction string

    switch (opcode) {
        case 0x6: // LDR Rd Rs IMM6 (Rd = dmem[Rs + sext(IMM6)])
            rd = (instr >> 9) & 0x7; // Extract destination register Rd
            rs = (instr >> 6) & 0x7; // Extract source register Rs
            imm6 = instr & 0x3F; // Extract 6-bit immediate offset
            strcat(assembly, "LDR R");
            strcat(assembly, convert_int_to_string(rd)); // Append destination register to assembly string
            strcat(assembly, ", R");
            strcat(assembly, convert_int_to_string(rs)); // Append source register to assembly string
            strcat(assembly, ", #");
            strcat(assembly, convert_int_to_string(imm6)); // Append immediate offset to assembly string
            break;
        case 0x7: // STR Rt Rs IMM6 (dmem[Rs + sext(IMM6)] = Rt)
            rd = (instr >> 9) & 0x7; // Extract destination register Rd
            rs = (instr >> 6) & 0x7; // Extract source register Rs
            imm6 = instr & 0x3F; // Extract 6-bit immediate offset
            strcat(assembly, "STR R");
            strcat(assembly, convert_int_to_string(rd)); // Append destination register to assembly string
            strcat(assembly, ", R");
            strcat(assembly, convert_int_to_string(rs)); // Append source register to assembly string
            strcat(assembly, ", #");
            strcat(assembly, convert_int_to_string(imm6)); // Append immediate offset to assembly string
            break;
        default:
            strcat(assembly, "<unknown>");
            break;
    }

    rom->assembly = strdup(assembly); // Store the assembly instruction in the ROM
}

void handle_rti_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    // Build the assembly string
    char assembly[1000];
    strcpy(assembly, "RTI");

    // Set the assembly string in the row of memory
    rom->assembly = strdup(assembly);
}

void handle_const_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    // Extract fields from the instruction
    unsigned short int instr = rom->contents;
    unsigned short int rd = (instr >> 9) & 0x7; // Extract destination register Rd
    unsigned short int imm9 = instr & 0x01FF; // Extract 9-bit immediate value

    // Build the assembly string
    char assembly[1000];
    sprintf(assembly, "CONST R%d, #%d", rd, imm9);

    // Set the assembly string in the row of memory
    rom->assembly = strdup(assembly);
}

void handle_shift_mod_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    // Extract fields from the instruction
    unsigned short int instr = rom->contents;
    unsigned short int op = (instr >> 3) & 0x3; // Extract sub-operation
    unsigned short int rd = (instr >> 9) & 0x7; // Extract destination register Rd
    unsigned short int rs = (instr >> 6) & 0x7; // Extract source register Rs
    unsigned short int rt = instr & 0x7;        // Extract target register Rt or immediate value for MOD operation
    unsigned short int uimm4 = instr & 0xf;

    // Build the assembly string
    char assembly[1000];
    switch (op) {
        case 0: // SLL
            strcat(assembly, "SLL");
            break;
        case 1: // SRA
            strcat(assembly, "SRA");
            break;
        case 2: // SRL
            strcat(assembly, "SRL");
            break;
        case 3: // MOD
            strcat(assembly, "MOD");
            break;
    }
    if (op != 3) { // If not MOD 
        sprintf(assembly + strlen(assembly), " R%d, R%d, #%d", rd, rs, uimm4);
    } else { // If MOD 
        sprintf(assembly + strlen(assembly), " R%d, R%d, R%d", rd, rs, rt);
    }

    // Set the assembly string in the row of memory
    rom->assembly = strdup(assembly);
}

void handle_jump_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    // Extract fields from the instruction
    unsigned short int instr = rom->contents;
    unsigned short int op = (instr >> 11) & 0x1; // Extract sub-operation
    unsigned short int rs = (instr >> 6) & 0x7; // Extract source register Rs or label offset for JMP operation
    unsigned short int imm11 = instr & 0x07ff;

    // Build the assembly string
    char assembly[1000];
    switch (op) {
        case 0: // JMPR
            strcat(assembly, "JMPR R");
            sprintf(assembly + strlen(assembly), "%d", rs);
            break;
        case 1: // JMP
            strcat(assembly, "JMP ");
            // Calculate the target address
            unsigned short int target_address = rom->address + 1 + imm11;
            // Attempt to find the label at the calculated address
            row_of_memory* label_row = search_tbl_by_address(memory, target_address);
            if (label_row && label_row->label) {
                strcat(assembly, label_row->label);
            } 
            else {
                // If label not found, append "<unknown>"
                strcat(assembly, "<unknown>");
            }
            break;
    }

    // Set the assembly string in the row of memory
    rom->assembly = strdup(assembly);
}

void handle_hiconst_trap_op(lc4_memory_segmented* memory, row_of_memory* rom) {
    // Extract fields from the instruction
    unsigned short int instr = rom->contents;
    unsigned short int op = (instr >> 12) & 0xF; // Extract operation code
    unsigned short int rd = (instr >> 9) & 0x7; // Extract destination register Rd or trap vector for TRAP operation
    unsigned short int imm8 = instr & 0xFF; // Extract 8-bit immediate value

    // Build the assembly string
    char assembly[1000];
    switch (op) {
        case 0xD: // HICONST
            strcat(assembly, "HICONST R");
            sprintf(assembly + strlen(assembly), "%d", rd);
            strcat(assembly, ", #");
            strcat(assembly, convert_int_to_string(imm8)); // Convert immediate value to string
            break;
        case 0xF: // TRAP
            strcat(assembly, "TRAP ");
            strcat(assembly, "x");
            strcat(assembly, convert_int_to_string(imm8)); // Convert trap vector to string
            break;
    }

    // Set the assembly string in the row of memory
    rom->assembly = strdup(assembly);
}


int reverse_assemble (lc4_memory_segmented* memory) 
{
    row_of_memory* user_prog_mem = memory->buckets[0];
    row_of_memory* current = user_prog_mem;
    while( current != NULL )
    {
        unsigned short int instruction = current->contents;
        unsigned short int opcode = instruction >> 12;
        switch(opcode)
        {
            case 0: // Branch Operatins 
                handle_branch_op(memory, current);
                break;
            case 1: // Arithmatic Operations
                handle_arith_op(memory, current);
                break;
            case 2: // Compare Operations 
                handle_compare_op(memory, current);
                break;
            case 4: // JSR Operations 
                handle_jsr_op(memory, current);
                break;
            case 5: // Logical Operations
                handle_logical_op(memory, current);
                break;
            case 6: // Load Operation 
            case 7: // Store Operation 
                handle_load_store_op(memory, current);
                break;
            case 8: // RTI Operation 
                handle_rti_op(memory, current);
                break;
            case 9: // CONST Operation 
                handle_const_op(memory, current);
                break;
            case 10: // SHIFT-MOD Operation 
                handle_shift_mod_op(memory, current);
                break;
            case 12: // Jump Operation 
                handle_jump_op(memory, current);
                break;
            case 13: // HICONST
            case 15: // TRAP 
                handle_hiconst_trap_op(memory, current);
                break;
            default:
                printf("hitting default\n");
                // printf("Hola! Inside reverse_assemble!\n");
                break;
        }
        current = current->next;
    }
    row_of_memory* os_prog_mem = memory->buckets[2];
    current = os_prog_mem;
    while( current != NULL )
    {
        unsigned short int instruction = current->contents;
        unsigned short int opcode = instruction >> 12;
        switch(opcode)
        {
            case 0: // Branch Operatins 
                handle_branch_op(memory, current);
                break;
            case 1: // Arithmatic Operations
                handle_arith_op(memory, current);
                break;
            case 2: // Compare Operations 
                handle_compare_op(memory, current);
                break;
            case 4: // JSR Operations 
                handle_jsr_op(memory, current);
                break;
            case 5: // Logical Operations
                handle_logical_op(memory, current);
                break;
            case 6: // Load Operation 
            case 7: // Store Operation 
                handle_load_store_op(memory, current);
                break;
            case 8: // RTI Operation 
                handle_rti_op(memory, current);
                break;
            case 9: // CONST Operation 
                handle_const_op(memory, current);
                break;
            case 10: // SHIFT-MOD Operation 
                handle_shift_mod_op(memory, current);
                break;
            case 12: // Jump Operation 
                handle_jump_op(memory, current);
                break;
            case 13: // HICONST
            case 15: // TRAP 
                handle_hiconst_trap_op(memory, current);
                break;
            default:
                printf("hitting default\n");
                // printf("Hola! Inside reverse_assemble!\n");
                break;
        }
        current = current->next;
    }
	return 0 ;
}

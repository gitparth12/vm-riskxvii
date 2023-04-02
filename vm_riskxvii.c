#include "helper_functions.h"
#include "vm_functions.h"
#include "heap.h"
#include "linked_list.h"
#include <string.h>

int main(int argc, char *argv[]) {

    // Initialising the struct
    blob vm = {
        .inst_mem = {0},
        .data_mem = {0},
        .registers = {0},
        .PC = 0,
        .heap_memory = {
            .total_banks_taken = 0,
            .head = NULL
        }
    };
    blob* p_vm = &vm;

    // Creating a file pointer for the binary input
    FILE* pbinary;
    if(argc == 2) {
        pbinary = fopen(argv[1],"rb");
    }
    else {
        printf("Wrong number of command line arguments.");
        exit(1);
    }

    // Reading binary file into both arrays in our struct
    fread(p_vm->inst_mem, sizeof(uint32_t), INST_MEM_SIZE, pbinary);
    fread(p_vm->data_mem, sizeof(uint8_t), DATA_MEM_SIZE, pbinary);
    
    while (1) {
        execute_inst(p_vm, p_vm->inst_mem[p_vm->PC / 4]);

        if (p_vm->PC > 1024) {
            printf("PC got too big, exiting.\n");
            list_free(&p_vm->heap_memory.head);
            exit(1);
        }
    }

    return 0;
}
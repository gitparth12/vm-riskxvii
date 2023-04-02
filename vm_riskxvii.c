#include "helper_functions.h"
#include "vm_functions.h"
#include "heap.h"
#include "linked_list.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // // Instruction Memory
    // uint32_t inst_mem[INST_MEM_SIZE];
    // // Data memory
    // uint8_t data_mem[DATA_MEM_SIZE];
    // // Registers for the vm
    // int32_t registers[REGISTER_COUNT];
    // // Program counter
    // uint32_t PC;
    // // Linked list of malloc requests
    // Heap heap_memory;

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
    // memset(p_vm->registers, 0, sizeof(p_vm->registers));
    // p_vm->PC = 0;

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
        // register_dump(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
        // printf("PC: %d\n", p_vm->PC);
        // printf("\n");
        if (p_vm->PC > 1024) {
            printf("PC got too big, exiting.\n");
            list_free(&p_vm->heap_memory.head);
            exit(1);
        }
    }

    // while (1) {
    //     uint32_t inst = p_vm->inst_mem[p_vm->PC / 4];
    //     print_inst(p_vm, inst);
    //     printf("Instruction Binary: ");
    //     print_bits(4, &inst);
    //     execute_inst(p_vm, inst);
    //     register_dump(p_vm, inst);
    //     printf("\n-------------------------------------\n");
    // }

    // while (1) {
    //     printf("PC: %x    |    ", p_vm->PC);
    //     uint32_t inst = p_vm->inst_mem[p_vm->PC / 4];
    //     printf("Instruction Binary: ");
    //     print_bits(4, &inst);
    //     register_dump(p_vm, inst);
    //     execute_inst(p_vm, inst);
    //     register_dump(p_vm, inst);
    //     printf("\n---------------------------------\n");
    // }
    // uint32_t inst = p_vm->inst_mem[p_vm->PC / 4];
    // print_bits(4, &inst);
    // register_dump(p_vm, inst);
    // execute_inst(p_vm, inst);
    // register_dump(p_vm, inst);
    // uint32_t add_inst = 0b00000000100100111000000100110011;
    // add(p_vm, add_inst);

    return 0;
}
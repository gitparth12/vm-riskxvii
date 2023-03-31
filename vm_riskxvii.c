#include "helper_functions.h"
#include "vm_functions.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // Initialising the struct
    blob vm;
    blob* p_vm = &vm;
    memset(p_vm->registers, 0, sizeof(p_vm->registers));
    p_vm->PC = 0;

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
    
    // while (1) {
    //     execute_inst(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
    //     // register_dump(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
    //     // printf("PC: %d\n", p_vm->PC);
    //     // printf("\n");
    //     if (p_vm->PC > 1024) {
    //         printf("PC got too big, exiting.\n");
    //         exit(1);
    //     }
    // }

    for (int i = 0; i < 256; i++) {
        print_inst(p_vm, p_vm->inst_mem[i]);
        execute_inst(p_vm, p_vm->inst_mem[i]);
    }

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

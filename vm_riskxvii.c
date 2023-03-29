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
    fread(p_vm->data_mem, sizeof(unsigned char), DATA_MEM_SIZE, pbinary);
    
    for (size_t i = 0; i < INST_MEM_SIZE; i++) {
        execute_inst(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
        // register_dump(p_vm, p_vm->inst_mem[i]);
        //printf("\n");
    }
    // uint32_t add_inst = 0b00000000100100111000000100110011;
    // add(p_vm, add_inst);

    return 0;
}

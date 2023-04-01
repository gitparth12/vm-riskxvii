#ifndef VM_RISKXVII
#define VM_RISKXVII

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INST_MEM_SIZE (256)
#define DATA_MEM_SIZE (1024)
#define INST_BYTES (4)
#define OPCODE_LENGTH (7)
#define FUNC3_START (12)
#define FUNC7_START (25)

typedef struct blob {
    // Instruction Memory
    uint32_t inst_mem[INST_MEM_SIZE];
    // Data memory
    uint8_t data_mem[DATA_MEM_SIZE];
    // Registers for the vm
    int32_t registers[32];
    // Program counter
    uint32_t PC;
} blob;

#endif
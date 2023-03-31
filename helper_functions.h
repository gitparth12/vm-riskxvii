#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

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
    unsigned char data_mem[DATA_MEM_SIZE];
    // Registers for the vm
    int32_t registers[32];
    // Program counter
    uint32_t PC;
} blob;

typedef struct memory_bank {
    char* data;
    uint16_t start_adress;
    bool allocated;
    uint8_t n_bytes;
} memory_bank;

extern void print_bits(size_t const size, void* ptr);
extern int32_t get_number(uint32_t instruction, int start_pos, int n_bits);
// https://stackoverflow.com/questions/8011700/how-do-i-extract-specific-n-bits-of-a-32-bit-unsigned-integer-in-c
extern bool compare_bits(uint32_t instruction, int start_pos, int n_bits, uint32_t bin_number);
extern void execute_inst(blob* p_vm, uint32_t instruction);
extern void call_illegal_op(blob* p_vm, uint32_t instruction);
extern void register_dump(blob* p_vm, uint32_t instruction);
extern void print_inst(blob* p_vm, uint32_t instruction);

#endif
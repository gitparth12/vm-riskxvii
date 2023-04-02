#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include "vm_riskxvii.h"
#include "heap.h"

extern void print_bits(size_t const size, void* ptr);
extern int32_t get_number(uint32_t instruction, int start_pos, int n_bits);
extern bool compare_bits(uint32_t instruction, int start_pos, int n_bits, uint32_t bin_number);
extern void execute_inst(blob* p_vm, uint32_t instruction);
extern void call_illegal_op(blob* p_vm, uint32_t instruction);
extern void register_dump(blob* p_vm, uint32_t instruction);
extern void print_inst(blob* p_vm, uint32_t instruction);

#endif
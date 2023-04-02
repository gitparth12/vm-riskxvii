#ifndef HEAP
#define HEAP

#include <stdint.h>
#include <stdbool.h>
#include "vm_riskxvii.h"

#define INST_MEM_SIZE (256)
#define DATA_MEM_SIZE (1024)
#define REGISTER_COUNT (32)
#define INST_BYTES (4)
#define OPCODE_LENGTH (7)
#define FUNC3_START (12)
#define FUNC7_START (25)
#define HEAP_SIZE (128)
#define HEAP_BANK_SIZE (64)

typedef struct Node { // represents malloc requests
    int8_t* p_data;
    uint8_t size;
    uint32_t num_banks;
    uint32_t start_address;
    struct Node* next;
} Node;

typedef struct Heap {
    Node* head; // Linked list of nodes
    uint8_t total_banks_taken;
} Heap;

typedef struct blob {
    // Instruction Memory
    uint32_t inst_mem[INST_MEM_SIZE];
    // Data memory
    uint8_t data_mem[DATA_MEM_SIZE];
    // Registers for the vm
    int32_t registers[REGISTER_COUNT];
    // Program counter
    uint32_t PC;
    // Linked list of malloc requests
    Heap heap_memory;
} blob;

extern uint32_t get_num_banks(uint32_t malloc_size);
extern uint32_t my_malloc(blob* p_vm, uint32_t malloc_size);
extern void my_free(blob* p_vm, uint32_t address);
extern void sb_h(blob* p_vm, uint32_t* value, uint32_t address);
extern void sh_h(blob* p_vm, uint32_t* value, uint32_t address);
extern void sw_h(blob* p_vm, uint32_t* value, uint32_t address);
extern void lb_h(blob* p_vm, uint32_t reg_index, uint32_t address);
extern void lh_h(blob* p_vm, uint32_t reg_index, uint32_t address);
extern void lw_h(blob* p_vm, uint32_t reg_index, uint32_t address);
extern void lbu_h(blob* p_vm, uint32_t reg_index, uint32_t address);
extern void lhu_h(blob* p_vm, uint32_t reg_index, uint32_t address);


#endif
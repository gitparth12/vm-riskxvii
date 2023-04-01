#ifndef VM_FUNCTIONS
#define VM_FUNCTIONS

#include "helper_functions.h"
#include "vm_riskxvii.h"

extern void add(blob* p_vm, uint32_t instruction);
extern void addi(blob* p_vm, uint32_t instruction);
extern void sub(blob* p_vm, uint32_t instruction);
extern void lui(blob* p_vm, uint32_t instruction);
extern void xor(blob* p_vm, uint32_t instruction);
extern void xori(blob* p_vm, uint32_t instruction);
extern void or(blob* p_vm, uint32_t instruction);
extern void ori(blob* p_vm, uint32_t instruction);
extern void and(blob* p_vm, uint32_t instruction);
extern void andi(blob* p_vm, uint32_t instruction);
extern void sll(blob* p_vm, uint32_t instruction);
extern void srl(blob* p_vm, uint32_t instruction);
extern void sra(blob* p_vm, uint32_t instruction);
extern void lb(blob* p_vm, uint32_t instruction);
extern void lh(blob* p_vm, uint32_t instruction);
extern void lw(blob* p_vm, uint32_t instruction);
extern void lbu(blob* p_vm, uint32_t instruction);
extern void lhu(blob* p_vm, uint32_t instruction);
extern void sb(blob* p_vm, uint32_t instruction);
extern void sh(blob* p_vm, uint32_t instruction);
extern void sw(blob* p_vm, uint32_t instruction);
extern void slt(blob* p_vm, uint32_t instruction);
extern void slti(blob* p_vm, uint32_t instruction);
extern void sltu(blob* p_vm, uint32_t instruction);
extern void sltiu(blob* p_vm, uint32_t instruction);
extern void beq(blob* p_vm, uint32_t instruction);
extern void bne(blob* p_vm, uint32_t instruction);
extern void blt(blob* p_vm, uint32_t instruction);
extern void bltu(blob* p_vm, uint32_t instruction);
extern void bge(blob* p_vm, uint32_t instruction);
extern void bgeu(blob* p_vm, uint32_t instruction);
extern void jal(blob* p_vm, uint32_t instruction);
extern void jalr(blob* p_vm, uint32_t instruction);

#endif
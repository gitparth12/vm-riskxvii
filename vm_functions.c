#include "vm_functions.h"

// bool compare_bits(uint32_t value, int start_bit, int n_bits, uint32_t bin_number) {
//     uint32_t mask;
//     mask = ((1 << n_bits) - 1) << start_bit;
//     uint32_t isolated_bits = value & mask;
//     // Putting given binary number at the correct position in 32 bits
//     bin_number = bin_number << start_bit;
//     if ((isolated_bits ^ bin_number) == 0)
//         return true;
//     return false;
// }

void add(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] + p_vm->registers[rs2];
    printf("add: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void addi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    // https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] + imm;
    printf("addi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sub(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] - p_vm->registers[rs2];
    printf("sub: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lui(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 12, 20) << 12;
    p_vm->registers[rd] = imm;
    printf("lui: rd: %d, imm: %d\n", p_vm->registers[rd], imm);
}

void xor(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] ^ p_vm->registers[rs2];
    printf("xor: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void xori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] ^ imm;
    printf("xori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void or(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] | p_vm->registers[rs2];
    printf("or: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void ori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] | imm;
    printf("ori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void and(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] & p_vm->registers[rs2];
    printf("and: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void andi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] & imm;
    printf("andi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sll(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] << p_vm->registers[rs2];
    printf("sll: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void srl(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] >> p_vm->registers[rs2];
    printf("srl: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void sra(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t shifted = p_vm->registers[rs1] >> p_vm->registers[rs2];
    int32_t rot_bits = p_vm->registers[rs1] << (32 - p_vm->registers[rs2]);
    int32_t combined = shifted | rot_bits;
    p_vm->registers[rd] = combined;
    printf("sra: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lb(blob* p_vm, uint32_t instruction) {

}

void lw(blob* p_vm, uint32_t instruction) {

}

void lbu(blob* p_vm, uint32_t instruction) {

}

void lhu(blob* p_vm, uint32_t instruction) {

}

void sb(blob* p_vm, uint32_t instruction) {

}

void sh(blob* p_vm, uint32_t instruction) {

}

void sw(blob* p_vm, uint32_t instruction) {

}

void slt(blob* p_vm, uint32_t instruction) {

}

void slti(blob* p_vm, uint32_t instruction) {

}

void sltu(blob* p_vm, uint32_t instruction) {

}

void sltiu(blob* p_vm, uint32_t instruction) {

}

void beq(blob* p_vm, uint32_t instruction) {

}

void bne(blob* p_vm, uint32_t instruction) {

}

void blt(blob* p_vm, uint32_t instruction) {

}

void bltu(blob* p_vm, uint32_t instruction) {

}

void bge(blob* p_vm, uint32_t instruction) {

}

void bgeu(blob* p_vm, uint32_t instruction) {

}

void jal(blob* p_vm, uint32_t instruction) {

}

void jalr(blob* p_vm, uint32_t instruction) {

}
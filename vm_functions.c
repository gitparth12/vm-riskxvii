#include "vm_functions.h"
#include <string.h>

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
    // printf("add: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void addi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    // https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] + imm;
    // printf("addi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sub(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] - p_vm->registers[rs2];
    // printf("sub: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lui(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 12, 20) << 12;
    p_vm->registers[rd] = imm;
    // printf("lui: rd: %d, imm: %d\n", p_vm->registers[rd], imm);
}

void xor(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] ^ p_vm->registers[rs2];
    // printf("xor: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void xori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] ^ imm;
    // printf("xori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void or(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] | p_vm->registers[rs2];
    // printf("or: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void ori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] | imm;
    // printf("ori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void and(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] & p_vm->registers[rs2];
    // printf("and: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void andi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->registers[rs1] & imm;
    // printf("andi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sll(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] << p_vm->registers[rs2];
    // printf("sll: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void srl(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    p_vm->registers[rd] = p_vm->registers[rs1] >> p_vm->registers[rs2];
    // printf("srl: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void sra(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t shifted = p_vm->registers[rs1] >> p_vm->registers[rs2];
    int32_t rot_bits = p_vm->registers[rs1] << (32 - p_vm->registers[rs2]);
    int32_t combined = shifted | rot_bits;
    p_vm->registers[rd] = combined;
    // printf("sra: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lb(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;
    if (memory_addr <= 0x3ff) { // Instruction memory or negative address
        call_illegal_op(p_vm, instruction);
    }
    else if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        p_vm->registers[rd] = (p_vm->data_mem[memory_addr] << 24) >> 24;
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        memory_addr -= 0xb700;
        // Assign value to heap memory (to be implemented)
    }
}

void lh(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;
    if (memory_addr <= 0x3ff) { // Instruction memory or negative address
        call_illegal_op(p_vm, instruction);
    }
    else if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        int8_t first = p_vm->data_mem[memory_addr]; // Read right 8 bits
        int16_t second = p_vm->data_mem[memory_addr+1] << 8; // Read left 8 bits
        int32_t combined = ((first | second) << 16) >> 16;
        p_vm->registers[rd] = combined; // Sign extend and store
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        memory_addr -= 0xb700;
        // Assign value to heap memory (to be implemented)
    }
}

void lw(blob* p_vm, uint32_t instruction) {

}

void lbu(blob* p_vm, uint32_t instruction) {

}

void lhu(blob* p_vm, uint32_t instruction) {

}

void sb(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = ((get_number(instruction, 7, 5) | (get_number(instruction, 25, 7) << 5)));
    imm = (imm << 20) >> 20; // Sign extend
    uint32_t memory_addr = p_vm->registers[rs1] + imm;
    if (memory_addr <= 0x3ff) { // Instruction memory or negative address
        call_illegal_op(p_vm, instruction);
    }
    else if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        memcpy(&p_vm->data_mem[memory_addr], &p_vm->registers[rs2], 1);
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        memory_addr -= 0xb700;
        // Assign value to heap memory (to be implemented)
    }
    switch (memory_addr) {
        case 0x800:
            printf("%c\n", p_vm->registers[rs2]);
            break;
        case 0x804:
            printf("%d\n", p_vm->registers[rs2]);
            break;
        case 0x808:
            printf("%d\n", (uint32_t) p_vm->registers[rs2]);
            break;
        case 0x80c:
            printf("CPU Halt Requested\n");
            exit(0);
            break;
    }
    // printf("sb: rs1: %d, rs2: %d, imm: %d, memory_addr: %d\n", p_vm->registers[rs1], p_vm->registers[rs2], imm, memory_addr);
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
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 21, 10);
    imm = (imm | (get_number(instruction, 20, 1) << 11));
    imm = (imm | (get_number(instruction, 12, 8) << 12));
    imm = (imm | (get_number(instruction, 31, 1) << 31));
    // print_inst(4, &imm);
    p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC += (imm << 1);
    // printf("jal: rd: %d, imm: %d, PC: %d\n", rd, imm, p_vm->PC);
}

void jalr(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC = p_vm->registers[rs1] + imm;
    // printf("jalr: rd: %d, rs1: %d, imm: %d\n", rd, rs1, imm);
}
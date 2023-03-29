#include "helper_functions.h"
#include "vm_functions.h"

void execute_inst(blob* p_vm, uint32_t instruction) {
    // TYPE R -> Same opcode
    if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b0110011)) { // 51
        // Comparing func3
        if (compare_bits(instruction, FUNC3_START, 3, 0b0)) {
            // Comparing func7
            if (compare_bits(instruction, FUNC7_START, 7, 0b0)) {
                add(p_vm, instruction);
                // printff("add\n");
            }
            else {
                sub(p_vm, instruction);
                // printff("sub\n");
            }
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b101)) { // 5
            // Comparing func7
            if (compare_bits(instruction, FUNC7_START, 7, 0b0)) {
                srl(p_vm, instruction);
                // printff("srl\n");
            }
            else {
                sra(p_vm, instruction);
                // printff("sra\n");
            }
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b100)) { // 4
            xor(p_vm, instruction);
            // printff("xor\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b110)) { // 6
            or(p_vm, instruction);
            // printff("or\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b111)) { // 7
            and(p_vm, instruction);
            // printff("and\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b001)) { // 1
            sll(p_vm, instruction);
            // printff("sll\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b010)) { // 2
            slt(p_vm, instruction);
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b011)) { // 3
            sltu(p_vm, instruction);
            // printff("sltu\n");
        }
    }
    // TYPE I -> Multiple opcodes
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b0010011)) { // 19
        // Comparing func3
        if (compare_bits(instruction, FUNC3_START, 3, 0b0)) {
            addi(p_vm, instruction);
            // printff("addi\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b100)) { // 4
            xori(p_vm, instruction);
            // printff("xori\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b110)) { // 6
            ori(p_vm, instruction);
            // printff("ori\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b111)) { // 7
            andi(p_vm, instruction);
            // printff("andi\n");
        }
    }
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b0000011)) { // 3
        // Comparing func3
        if (compare_bits(instruction, FUNC3_START, 3, 0b0)) {
            lb(p_vm, instruction);
            // printff("lb\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b001)) { // 1
            lh(p_vm, instruction);
            // printff("lh\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b010)) { // 2
            lw(p_vm, instruction);
            // printff("lw\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b100)) { // 4
            lbu(p_vm, instruction);
            // printff("lbu\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b101)) { // 5
            lhu(p_vm, instruction);
            // printff("lhu\n");
        }
    }
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b1100111)) { // 103
        jalr(p_vm, instruction);
        // printff("jalr\n");
    }
    // TYPE U -> Unique opcode, one instruction only
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b0110111)) { // 55
        lui(p_vm, instruction);
        // printff("lui\n");
    }
    // TYPE UJ -> Unique opcode, one instruction only
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b1101111)) { // 111
        jal(p_vm, instruction);
        // printff("jal\n");
    }
    // TYPE S -> Same opcode
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b0100011)) { // 35
        // Comparing func3
        if (compare_bits(instruction, FUNC3_START, 3, 0b0)) {
            sb(p_vm, instruction);
            // printff("sb\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b001)) { // 1
            sh(p_vm, instruction);
            // printff("sh\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b010)) { // 2
            sw(p_vm, instruction);
            // printff("sw\n");
        }
    }
    // TYPE SB -> Same opcode
    else if (compare_bits(instruction, 0, OPCODE_LENGTH, 0b1100011)) { // 99
        // Comparing func3
        if (compare_bits(instruction, FUNC3_START, 3, 0b0)) {
            beq(p_vm, instruction);
            // printff("beq\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b001)) { // 1
            bne(p_vm, instruction);
            // printff("bne\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b100)) { // 4
            blt(p_vm, instruction);
            // printff("blt\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b110)) { // 6
            bltu(p_vm, instruction);
            // printff("bltu\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b101)) { // 5
            bge(p_vm, instruction);
            // printff("bge\n");
        }
        else if (compare_bits(instruction, FUNC3_START, 3, 0b111)) { // 7
            bgeu(p_vm, instruction);
            // printff("bgeu\n");
        }
    }
}

uint32_t get_number(uint32_t instruction, int start_pos, int n_bits) {
    uint32_t mask;
    mask = ((1 << n_bits) - 1) << start_pos;
    uint32_t isolated_bits = instruction & mask;
    return (isolated_bits >> start_pos);
}

bool compare_bits(uint32_t instruction, int start_pos, int n_bits, uint32_t bin_number) {
    uint32_t mask;
    mask = ((1 << n_bits) - 1) << start_pos;
    uint32_t isolated_bits = instruction & mask;
    // Putting given binary number at the correct position in 32 bits
    bin_number = bin_number << start_pos;
    if ((isolated_bits ^ bin_number) == 0)
        return true;
    return false;
}

void print_inst(size_t const size, void* ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

void call_illegal_op(blob* p_vm, uint32_t instruction) {
    printf("Illegal Operation: %X;\n", instruction);
    // Register Dump
    register_dump(p_vm, instruction);
    // Terminate
    exit(1);
}

void register_dump(blob* p_vm, uint32_t instruction) {
    printf("PC = %d;\n", p_vm->PC);
    for (size_t i = 0; i < 32; i++) {
        printf("R[%lu] = %x;\n", i, p_vm->registers[i]);
    }
}
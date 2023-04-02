#include "vm_functions.h"
#include "heap.h"
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
    // printf("rd: %d, rs1: %d, rs2: %d\n", rd, rs1, rs2);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] + p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("add: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void addi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    // https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    // print_bits(4, &imm);
    // printf("rd: %d, rs1: %d, imm: %d\n", rd, rs1, imm);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] + imm;
    p_vm->PC += 4;
    // printf("addi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sub(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] - p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("sub: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lui(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 12, 20) << 12;
    // printf("rd: %d, imm: %d\n", rd, imm);
    if (rd != 0)
        p_vm->registers[rd] = imm;
    p_vm->PC += 4;
    // printf("lui: rd: %d, imm: %d\n", p_vm->registers[rd], imm);
}

void xor(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] ^ p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("xor: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void xori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] ^ imm;
    p_vm->PC += 4;
    // printf("xori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void or(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] | p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("or: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void ori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] | imm;
    p_vm->PC += 4;
    // printf("ori: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void and(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] & p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("and: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void andi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] & imm;
    p_vm->PC += 4;
    // printf("andi: rd: %d, rs1: %d, imm: %d\n", p_vm->registers[rd], p_vm->registers[rs1], imm);
}

void sll(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] << p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("sll: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void srl(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = ((uint32_t) p_vm->registers[rs1]) >> p_vm->registers[rs2];
    p_vm->PC += 4;
    // printf("srl: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void sra(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t shifted = p_vm->registers[rs1] >> p_vm->registers[rs2];
    int32_t rot_bits = p_vm->registers[rs1] << (32 - p_vm->registers[rs2]);
    int32_t combined = shifted | rot_bits;
    if (rd != 0)
        p_vm->registers[rd] = combined;
    p_vm->PC += 4;
    // printf("sra: rd: %d, rs1: %d, rs2: %d\n", p_vm->registers[rd], p_vm->registers[rs1], p_vm->registers[rs2]);
}

void lb(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;
    // if (memory_addr <= 0x3ff) { // Instruction memory or negative address
    //     call_illegal_op(p_vm, instruction);
    // }
    // printf("lb: %x\n", memory_addr);

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lb_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0)
            scanf("%d", &p_vm->registers[rd]);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    else { // Data Memory
        if (rd != 0)
            p_vm->registers[rd] = (p_vm->data_mem[memory_addr - DATA_MEM_SIZE] << 24) >> 24;
    }
    p_vm->PC += 4;
}

void lh(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;
    // if (memory_addr <= 0x3ff) { // Instruction memory or negative address
    //     call_illegal_op(p_vm, instruction);
    // }
    // printf("lh: %x\n", memory_addr);

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lh_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0)
            scanf("%d", &p_vm->registers[rd]);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    else { // Data Memory
        int32_t first = p_vm->data_mem[memory_addr - DATA_MEM_SIZE]; // Read first 8 bits
        int32_t second = p_vm->data_mem[memory_addr - DATA_MEM_SIZE + 1] << 8; // Read second 8 bits
        int32_t combined = ((first | second) << 16) >> 16;
        if (rd != 0)
            p_vm->registers[rd] = combined; // Sign extend and store
    }
    p_vm->PC += 4;
}

void lw(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;

    // printf("lw: %x\n", memory_addr);

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lw_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0)
            scanf("%d", &p_vm->registers[rd]);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    else { // Data Memory
        int32_t first = p_vm->data_mem[memory_addr - DATA_MEM_SIZE]; // Read first 8 bits
        int32_t second = p_vm->data_mem[memory_addr - DATA_MEM_SIZE + 1] << 8; // Read second 8 bits
        int32_t third = p_vm->data_mem[memory_addr - DATA_MEM_SIZE + 2] << 16;
        int32_t fourth = p_vm->data_mem[memory_addr - DATA_MEM_SIZE + 3] << 24;
        if (rd != 0)
            p_vm->registers[rd] = (first | second | third | fourth); // Store in R[rd]
    }
    p_vm->PC += 4;
}

void lbu(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;

    // printf("lbu: m[%d]: %d, rs1: %d, rs1_val: %d, rd: %d, rd_val: %d, imm: %d\n", memory_addr - DATA_MEM_SIZE,p_vm->data_mem[memory_addr - DATA_MEM_SIZE], rs1, p_vm->registers[rs1], rd, p_vm->registers[rd], imm);

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lbu_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0)
            scanf("%u", &p_vm->registers[rd]);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    else {
        p_vm->registers[rd] = (uint8_t) p_vm->data_mem[memory_addr - DATA_MEM_SIZE];
    }
    p_vm->PC += 4;
}

void lhu(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;

    if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        int32_t first = p_vm->data_mem[memory_addr]; // Read first 8 bits
        int32_t second = p_vm->data_mem[memory_addr+1] << 8; // Read second 8 bits
        int32_t combined = (first | second);
        if (rd != 0)
            p_vm->registers[rd] = (uint16_t) combined; // Store value in R[rd]
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lhu_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    switch (memory_addr) {
        case 0x812:
            // fread(&p_vm->registers[rd], sizeof(char), 1, stdin);
            if (rd != 0)
                scanf("%lc", &p_vm->registers[rd]);
            break;
        case 0x816:
            // int32_t input;
            // fread(&input, sizeof(int32_t), 1, stdin);
            // if (rd != 0)
            //     p_vm->registers[rd] = input;
            if (rd != 0)
                scanf("%u", &p_vm->registers[rd]);
            break;
    }
}

void sb(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = ((get_number(instruction, 7, 5) | (get_number(instruction, 25, 7) << 5)));
    imm = (imm << 20) >> 20; // Sign extend
    uint32_t memory_addr = p_vm->registers[rs1] + imm;

    // printf("sb addr: %x\n", memory_addr);

    if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        memcpy(&p_vm->data_mem[memory_addr], &p_vm->registers[rs2], 1);
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        sb_h(p_vm, &p_vm->registers[rs2], memory_addr);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    switch (memory_addr) {
        case 0x800:
            printf("%lc", p_vm->registers[rs2]);
            break;
        case 0x804:
            printf("%d", p_vm->registers[rs2]);
            break;
        case 0x808:
            printf("%x", (uint32_t) p_vm->registers[rs2]);
            break;
        case 0x80c:
            printf("CPU Halt Requested\n");
            list_free(&p_vm->heap_memory.head);
            exit(0);
            break;
        case 0x820:
            printf("%x", p_vm->PC);
            break;
        case 0x824:
            register_dump(p_vm, instruction);
            break;
        case 0x828:
            printf("%x", p_vm->data_mem[(uint32_t) p_vm->registers[rs2]]);
            break;
        case 0x830:
            // malloc
            p_vm->registers[28] = my_malloc(p_vm, p_vm->registers[rs2]);
            break;
        case 0x834:
            // free
            my_free(p_vm, p_vm->registers[rs2]);
            break;
    }
    p_vm->PC += 4;
    // printf("sb: rs1: %d, rs2: %d, imm: %d, memory_addr: %d\n", p_vm->registers[rs1], p_vm->registers[rs2], imm, memory_addr);
}

void sh(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = ((get_number(instruction, 7, 5) | (get_number(instruction, 25, 7) << 5)));
    imm = (imm << 20) >> 20; // Sign extend
    uint32_t memory_addr = p_vm->registers[rs1] + imm;

    // printf("sh addr: %x\n", memory_addr);

    if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        memcpy(&p_vm->data_mem[memory_addr], &p_vm->registers[rs2], 2);
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        sh_h(p_vm, &p_vm->registers[rs2], memory_addr);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    switch (memory_addr) {
        case 0x800:
            printf("%lc", p_vm->registers[rs2]);
            break;
        case 0x804:
            printf("%d", p_vm->registers[rs2]);
            break;
        case 0x808:
            printf("%x", (uint32_t) p_vm->registers[rs2]);
            break;
        case 0x80c:
            printf("CPU Halt Requested\n");
            list_free(&p_vm->heap_memory.head);
            exit(0);
            break;
        case 0x820:
            printf("%x", p_vm->PC);
            break;
        case 0x824:
            register_dump(p_vm, instruction);
            break;
        case 0x828:
            printf("%x", p_vm->data_mem[(uint32_t) p_vm->registers[rs2]]);
            break;
        case 0x830:
            // malloc
            p_vm->registers[28] = my_malloc(p_vm, p_vm->registers[rs2]);
            break;
        case 0x834:
            // free
            my_free(p_vm, p_vm->registers[rs2]);
            break;
    }
    p_vm->PC += 4;
}

void sw(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = ((get_number(instruction, 7, 5) | (get_number(instruction, 25, 7) << 5)));
    imm = (imm << 20) >> 20; // Sign extend
    uint32_t memory_addr = p_vm->registers[rs1] + imm;

    // printf("sw addr: %d, rs1: %d, rs1_val: %d, rs2: %d, rs2_val: %d, imm: %d\n", memory_addr, rs1, p_vm->registers[rs1], rs2, p_vm->registers[rs2], imm);

    if (memory_addr >= 0x400 && memory_addr <= 0x7ff) { // Data Memory
        memory_addr -= 0x400;
        memcpy(&p_vm->data_mem[memory_addr], &p_vm->registers[rs2], 4);
    }
    else if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        sw_h(p_vm, &p_vm->registers[rs2], memory_addr);
    }
    else if (memory_addr >= 0x850) {
        call_illegal_op(p_vm, instruction);
    }
    switch (memory_addr) {
        case 0x800:
            printf("%lc", p_vm->registers[rs2]);
            break;
        case 0x804:
            printf("%d", p_vm->registers[rs2]);
            break;
        case 0x808:
            printf("%x", (uint32_t) p_vm->registers[rs2]);
            break;
        case 0x80c:
            printf("CPU Halt Requested\n");
            list_free(&p_vm->heap_memory.head);
            exit(0);
            break;
        case 0x820:
            printf("%x", p_vm->PC);
            break;
        case 0x824:
            register_dump(p_vm, instruction);
            break;
        case 0x828:
            printf("%x", p_vm->data_mem[(uint32_t) p_vm->registers[rs2]]);
            break;
        case 0x830:
            // malloc
            p_vm->registers[28] = my_malloc(p_vm, p_vm->registers[rs2]);
            break;
        case 0x834:
            // free
            my_free(p_vm, p_vm->registers[rs2]);
            break;
    }
    p_vm->PC += 4;
}

void slt(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = (p_vm->registers[rs1] < p_vm->registers[rs2]) ? 1 : 0;
    p_vm->PC += 4;
}

void slti(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = (p_vm->registers[rs1] < imm) ? 1 : 0;
    p_vm->PC += 4;
}

void sltu(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = ((uint32_t) p_vm->registers[rs1] < (uint32_t) p_vm->registers[rs2]) ? 1 : 0;
    p_vm->PC += 4;
}

void sltiu(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = get_number(instruction, 20, 12);
    if (rd != 0)
        p_vm->registers[rd] = ((uint32_t) p_vm->registers[rs1] < imm) ? 1 : 0;
    p_vm->PC += 4;
}

void beq(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    imm = (imm << 20) >> 20; // Sign extend
    // printf("beq: ");
   // print_bits(4, &imm);
    // printf("rs1: %d, rs1_val: %d, rs2: %d, rs2_val: %d, imm: %d\n", rs1, p_vm->registers[rs1], rs2, p_vm->registers[rs2], imm);
    if (p_vm->registers[rs1] == p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
    
    // printf("PC: %x\n", p_vm->PC);
}

void bne(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    // imm = (imm << 20) >> 20; // Sign extend
    // printf("bneq: ");
   //  print_bits(4, &imm);
    // printf("rs1: %d, rs2: %d, imm: %d\n", rs1, rs2, imm);
    if (p_vm->registers[rs1] != p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void blt(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    imm = (imm << 20) >> 20; // Sign extend
    if (p_vm->registers[rs1] < p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void bltu(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    imm = imm; // Sign extend
    if ((uint32_t) p_vm->registers[rs1] < (uint32_t) p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void bge(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    imm = (imm << 20) >> 20; // Sign extend
    if (p_vm->registers[rs1] >= p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void bgeu(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));
    imm = (imm << 20) >> 20; // Sign extend
    if ((uint32_t) p_vm->registers[rs1] < p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void jal(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 21, 10) << 1;
    imm = (imm | (get_number(instruction, 20, 1) << 11));
    imm = (imm | (get_number(instruction, 12, 8) << 12));
    imm = (imm | (get_number(instruction, 31, 1) << 20));
    // printf("%d\n", imm);
    // print_bits(4, &imm);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC += imm;
    // printf("jal: rd: %d, imm: %d, PC: %d\n", p_vm->registers[rd], imm, p_vm->PC);
}

void jalr(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC = p_vm->registers[rs1] + imm;
    // printf("jalr: rd: %d, rs1: %d, imm: %d\n", rd, rs1, imm);
}
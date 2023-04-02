#include "vm_functions.h"
#include "heap.h"
#include <string.h>

void add(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] + p_vm->registers[rs2];
    p_vm->PC += 4;
}

void addi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] + imm;
    p_vm->PC += 4;
}

void sub(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] - p_vm->registers[rs2];
    p_vm->PC += 4;
}

void lui(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    int32_t imm = get_number(instruction, 12, 20) << 12;
    if (rd != 0)
        p_vm->registers[rd] = imm;
    p_vm->PC += 4;
}

void xor(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] ^ p_vm->registers[rs2];
    p_vm->PC += 4;
}

void xori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] ^ imm;
    p_vm->PC += 4;
}

void or(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] | p_vm->registers[rs2];
    p_vm->PC += 4;
}

void ori(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] | imm;
    p_vm->PC += 4;
}

void and(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] & p_vm->registers[rs2];
    p_vm->PC += 4;
}

void andi(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] & imm;
    p_vm->PC += 4;
}

void sll(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = p_vm->registers[rs1] << p_vm->registers[rs2];
    p_vm->PC += 4;
}

void srl(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    if (rd != 0)
        p_vm->registers[rd] = ((uint32_t) p_vm->registers[rs1]) >> p_vm->registers[rs2];
    p_vm->PC += 4;
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
}

void lb(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    int32_t memory_addr = p_vm->registers[rs1] + imm;

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lb_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0) {
            uint8_t temp;
            scanf("%d", &temp);
            p_vm->registers[rd] = temp;
        }
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

    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lh_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0) {
            uint16_t temp;
            scanf("%d", &temp);
            p_vm->registers[rd] = temp;
        }
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


    if (memory_addr >= 0xb700 && memory_addr <= 0xd700) { // Heap banks
        // Assign value to heap memory
        lw_h(p_vm, rd, memory_addr);
    }
    else if (memory_addr == 0x812) {
        if (rd != 0)
            scanf("%lc", &p_vm->registers[rd]);
    }
    else if (memory_addr == 0x816) {
        if (rd != 0) {
            uint32_t temp;
            scanf("%d", &temp);
            p_vm->registers[rd] = temp;
        }
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
        p_vm->registers[rd] = (uint8_t) (p_vm->data_mem[memory_addr - DATA_MEM_SIZE] & 0xff);
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
            p_vm->registers[rd] = (uint16_t) (combined & 0xffff); // Store value in R[rd]
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
            if (rd != 0)
                scanf("%lc", &p_vm->registers[rd]);
            break;
        case 0x816:
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
            printf("%c", p_vm->registers[rs2]);
            break;
        case 0x804:
            printf("%d", p_vm->registers[rs2]);
            break;
        case 0x808:
            uint32_t temp = 0 | p_vm->registers[rs2];
            printf("%x", temp);
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

void sh(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = ((get_number(instruction, 7, 5) | (get_number(instruction, 25, 7) << 5)));
    imm = (imm << 20) >> 20; // Sign extend
    uint32_t memory_addr = p_vm->registers[rs1] + imm;


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
            uint32_t temp = 0 | p_vm->registers[rs2];
            printf("%x", temp);
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
            uint32_t temp = 0 | p_vm->registers[rs2];
            printf("%x", temp);
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

    if (p_vm->registers[rs1] == p_vm->registers[rs2])
        p_vm->PC += imm;
    else
        p_vm->PC += 4;
}

void bne(blob* p_vm, uint32_t instruction) {
    uint32_t rs1 = get_number(instruction, 15, 5);
    uint32_t rs2 = get_number(instruction, 20, 5);
    int32_t imm = get_number(instruction, 8, 4) << 1;
    imm = (imm | (get_number(instruction, 25, 6) << 5));
    imm = (imm | (get_number(instruction, 7, 1) << 11));
    imm = (imm | (get_number(instruction, 31, 1) << 12));

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

    if (rd != 0)
        p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC += imm;
}

void jalr(blob* p_vm, uint32_t instruction) {
    uint32_t rd = get_number(instruction, 7, 5);
    uint32_t rs1 = get_number(instruction, 15, 5);
    int32_t imm = (get_number(instruction, 20, 12) << 20) >> 20; // Sign extended
    if (rd != 0)
        p_vm->registers[rd] = p_vm->PC + 4;
    p_vm->PC = p_vm->registers[rs1] + imm;
}
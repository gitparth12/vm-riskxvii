#include "heap.h"
#include "vm_riskxvii.h"
#include "linked_list.h"
#include <math.h>

uint32_t my_malloc(blob* p_vm, uint32_t malloc_size) {

    if (malloc_size > 0x2000)
        return 0;

    if (p_vm->heap_memory.head == NULL) {
        p_vm->heap_memory.head = (Node*) malloc(1 * sizeof(Node));
        Node* temp = p_vm->heap_memory.head;
        temp->p_data = (int8_t*) calloc(malloc_size, sizeof(uint8_t));
        temp->num_banks = get_num_banks(malloc_size);
        temp->next = NULL;
        temp->size = malloc_size;
        temp->start_address = 0xb700;
        // printf("start: %x, size: %d, num_banks: %d\n", temp->start_address, temp->size, temp->num_banks);
        return temp->start_address;
    }
    else {
        // loop through linked list and find empty space
        Node* current = p_vm->heap_memory.head;
        while (1) {
            if (current->next == NULL && (current->start_address + (current->num_banks * 64) + (get_num_banks(malloc_size) * 64)) <= 0xd700) {
                current->next = (Node*) malloc(1 * sizeof(Node));
                Node* new = current->next;
                new->p_data = (int8_t*) calloc(malloc_size, sizeof(uint8_t));
                new->num_banks = get_num_banks(malloc_size);
                new->next = NULL;
                new->size = malloc_size;
                new->start_address = current->start_address + (current->num_banks * 64);
                // printf("IF CONDITION: current_start: %x, start: %x, size: %d, num_banks: %d\n", current->start_address, new->start_address, new->size, new->num_banks);
                return new->start_address;
            }
            else if (current->next == NULL && (current->start_address + (current->num_banks * 64) + (get_num_banks(malloc_size) * 64)) > 0xd700) {
                return 0; // If there's no space to malloc at the end of the list
            }
            else {
                uint32_t end_address = current->start_address + (current->num_banks * 64);
                uint32_t next_address = current->next->start_address;
                if ((next_address - end_address) >= malloc_size && (next_address - end_address) >= 64) {
                    // Insert a node in the list here
                    Node* new = (Node*) malloc(1 * sizeof(Node));
                    new->p_data = (int8_t*) calloc(malloc_size, sizeof(uint8_t));
                    new->num_banks = get_num_banks(malloc_size);
                    new->next = current->next;
                    new->size = malloc_size;
                    new->start_address = current->start_address + (current->num_banks * 64);
                    current->next = new;
                    // printf("ELSE CONDITION: current_start: %x, start: %x, size: %d, num_banks: %d\n", current->start_address, new->start_address, new->size, new->num_banks);
                    return new->start_address;
                }
            }
            current = current->next;
        }
    }
}


void my_free(blob* p_vm, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    Node* previous = p_vm->heap_memory.head;
    while (current != NULL) {
        if (current->start_address == address) {
            if (current == p_vm->heap_memory.head) {
                p_vm->heap_memory.head = current->next;
                free(p_vm->heap_memory.head->p_data);
                free(p_vm->heap_memory.head);
                return;
            }
            else {
                previous->next = current->next;
                free(current->p_data);
                free(current);
                return;
            }
        }
        previous = current;
        current = current->next;
    }
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}


// Store and Load operations using heap
void sb_h(blob* p_vm, uint32_t* value, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && address <= (current->start_address + current->size)) {
            address -= current->start_address;
            memcpy(&current->p_data[address], value, 1);
            return;
        }
        current = current->next;
    }
    // printf("sb Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void sh_h(blob* p_vm, uint32_t* value, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+1) <= (current->start_address + current->size)) {
            address -= current->start_address;
            memcpy(&current->p_data[address], value, 2);
            return;
        }
        current = current->next;
    }
    // printf("sh Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void sw_h(blob* p_vm, uint32_t* value, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        // printf("sw Address: %x, current_addr: %x, current_size: %d\n", address, current->start_address, current->size);
        if ((address >= current->start_address) && ((address+3) <= (current->start_address + current->size))) {
            address -= current->start_address;
            memcpy(&current->p_data[address], value, 4);
            return;
        }
        current = current->next;
    }
    // printf("sw Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void lb_h(blob* p_vm, uint32_t reg_index, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+3) <= (current->start_address + current->size)) {
            address -= current->start_address;
            p_vm->registers[reg_index] = current->p_data[address];
            return;
        }
        current = current->next;
    }
    // printf("lb Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void lh_h(blob* p_vm, uint32_t reg_index, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+3) <= (current->start_address + current->size)) {
            address -= current->start_address;
            int32_t first = current->p_data[address];
            int32_t second = current->p_data[address+1] << 8;
            int32_t combined = ((first | second) << 16) >> 16;
            p_vm->registers[reg_index] = combined;
            return;
        }
        current = current->next;
    }
    // printf("lh Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void lw_h(blob* p_vm, uint32_t reg_index, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+3) <= (current->start_address + current->size)) {
            address -= current->start_address;
            int32_t first = current->p_data[address];
            int32_t second = current->p_data[address+1] << 8;
            int32_t third = current->p_data[address+2] << 16;
            int32_t fourth = current->p_data[address+3] << 24;
            int32_t combined = (first | second | third | fourth);
            p_vm->registers[reg_index] = combined;
            return;
        }
        current = current->next;
    }
    // printf("lw Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void lbu_h(blob* p_vm, uint32_t reg_index, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+3) <= (current->start_address + current->size)) {
            address -= current->start_address;
            p_vm->registers[reg_index] = (uint8_t) current->p_data[address];
            return;
        }
        current = current->next;
    }
    // printf("lbu Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}

void lhu_h(blob* p_vm, uint32_t reg_index, uint32_t address) {
    Node* current = p_vm->heap_memory.head;
    while (current != NULL) {
        if (address >= current->start_address && (address+3) <= (current->start_address + current->size)) {
            address -= current->start_address;
            int32_t first = current->p_data[address];
            int32_t second = current->p_data[address+1] << 8;
            int32_t combined = (first | second);
            p_vm->registers[reg_index] = (uint16_t) combined;
            return;
        }
        current = current->next;
    }
    // printf("lhu Address: %x\n", address);
    call_illegal_op(p_vm, p_vm->inst_mem[p_vm->PC / 4]);
}


uint32_t get_num_banks(uint32_t malloc_size) {
    if (malloc_size % 64 == 0)
        return (uint32_t) malloc_size / 64;
    return (uint32_t) (malloc_size / 64) + 1;
}
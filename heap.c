#include "heap.h"
#include "vm_riskxvii.h"
#include "linked_list.h"
#include <math.h>

uint8_t get_num_banks(uint32_t malloc_size) {
    if (malloc_size % 64 == 0)
        return (uint8_t) malloc_size / 64;
    return (uint8_t) (malloc_size / 64) + 1;
}

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




void my_free(uint32_t address);
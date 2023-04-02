#ifndef LINKED_LIST
#define LINKED_LIST

#include "vm_riskxvii.h"
#include "vm_functions.h"
#include "helper_functions.h"
#include "heap.h"

// nodes are memory banks
// Node* list_init(void) {
//     // Create a new head node and store the value in it, then return it.
//     // Node* head = (Node*) calloc(1, sizeof(Node));
//     // head->value;
//     Node head = {
//         .p_data = (int8_t*) calloc(64, sizeof(int8_t)),
//         .is_allocated;
//         .bank_position;
//         .bank_size;
//         .malloc_size;
//     }

extern Node* list_init();
extern void list_add(Node** head, uint8_t index);
extern void list_delete(Node** head, Node* bank);
extern Node* list_next(Node* bank);
extern void list_free(Node** head);

//     for (int i = 0; i < 128; i++) {
//     }

//     // return head;
// }

#endif

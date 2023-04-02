#ifndef LINKED_LIST
#define LINKED_LIST

#include "vm_riskxvii.h"
#include "vm_functions.h"
#include "helper_functions.h"
#include "heap.h"

extern Node* list_init();
extern void list_add(Node** head, uint8_t index);
extern void list_delete(Node** head, Node* bank);
extern Node* list_next(Node* bank);
extern void list_free(Node** head);

#endif

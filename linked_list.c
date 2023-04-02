#include "linked_list.h"

Node* list_init() {
    // Create a new head Node and store the value in it, then return it.
    Node* head = calloc(0, sizeof(Node));
    return head;
}


void list_add(Node** head, uint8_t index) {
    // Add a new value to the end of the list.

    // Iterate until we find the end of the list.
    Node* bank = *head;
    while (bank->next != NULL) {
        bank = bank->next;
    }

    // Create the new Node.
    bank->next = calloc(0, sizeof(Node));
    //bank->next->index = index;

    return;
}


void list_delete(Node** head, Node* bank) {
    // Delete the specified Node from the list.

    // We have to be careful when the Node to delete is actually the head Node.
    if (bank == *head) {
        *head = bank->next;
        free(bank);
        return;
    }

    // Otherwise, we need to cut this Node out, and stitch the other Nodes around it back together.
    // We start by searching for the Node before the one we are deleting.
    Node* before = *head;
    while (before->next != bank) {
        before = before->next;
    }

    // We then stitch the Node before and the Node after together.
    before->next = bank->next;

    // Then we delete the Node.
    free(bank);

    return;
}


Node* list_next(Node* bank) {
    return bank->next;
}


void list_free(Node** head) {
    // Delete the entire list.

    // We iterate through the list, deleting the last Node we visited as we go.
    Node* temp = *head;
    while (temp != NULL) {
        Node* last_Node = temp;
        temp = temp->next;

        // Delete the Node we just visited.
        free(last_Node->p_data);
        free(last_Node);
    }

    // Remove the reference to the head Node from the function caller.
    *head = NULL;
    return;
}


// int main(int argc, char** argv) {

//     // // Create a new list.
//     Node* list = list_init();

//     Node* temp = list;
//     for (int i = 0; i < HEAP_SIZE; i++) {
//         printf("index: %d\n", temp->index);
//         temp = temp->next;
//     }

//     // Delete the list.
//     list_free(&list);
//     return 0;
// }
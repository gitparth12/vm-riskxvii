#include "linked_list.h"

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
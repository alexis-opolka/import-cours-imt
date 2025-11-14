#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "../utils.c"


typedef struct File {
    DoubleLinkedList *elements;
} File;

File* File_new() {
    File *new_file = malloc(sizeof(File));
    new_file->elements = double_llist_new();

    return new_file;
}

void File_free(File* file) {
    double_llist_free(file->elements);

    free(file);
}

void File_push(File* file, char elem) {

    // We insert it at the start of the linked list
    double_llist_add_elem_start(file->elements, elem);
}

void File_pop(File* file) {
    DoubleNode *to_remove = file->elements->end->previous;


    // If the next element is the start element, quit
    if (to_remove == file->elements->start) {
        printf("Nothing to pop!\n");

        return;
    };

    // If we fall in here, we should have at least one node
    // We retrieve the last node that we're going to remove
    // (i.e. the previous node of the end sentinel)
    //
    // We're updating the nodes
    // We're updating the end sentinel
    file->elements->end->previous = to_remove->previous;

    // We're updating the previous node of the one we're going to pop
    to_remove->previous->next = file->elements->end;

    free(to_remove);
}

void File_print(File* file) {
    // First get the first node
    DoubleNode *current_node = file->elements->start->next;

    // We're checking that the next node is not the end sentinel
    // If it's the case, exit
    if (current_node == file->elements->end) {
        printf("The file is empty!\n");

        return;
    }

    while (current_node != file->elements->end) {
        printf("%c \n", current_node->elem);

        current_node = current_node->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    File *file = File_new();
    
    File_push(file, 'a');
    File_push(file, 'b');
    File_push(file, 'c');

    printf("Contenu de la File:\n");
    File_print(file);

    printf("\nDéFiler un élément...\n");
    File_pop(file);
    printf("Contenu de la File après défilement:\n");
    File_print(file);

    File_pop(file);
    File_pop(file);
    printf("Contenu de la File après défilement entier:\n");
    File_print(file);



    printf("\nMémoire utilisée par la File: %d octets\n", double_llist_used_memory(file->elements));
    File_free(file);

    return 0;
}
#ifndef UTILS_H
#include "utils.h"
#endif

#ifndef FILEPILE_H
#include "filepile.h"
#endif

//===========================================================================================================//
//                                                  FILE                                                     //
//===========================================================================================================//

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

//===========================================================================================================//
//                                                  PILE                                                     //
//===========================================================================================================//

Pile* cpile_new() {
    Pile* pile = malloc(sizeof(Pile));
    pile->elements = vector_new();

    return pile;
}

void cpile_free(Pile* pile) {
    vector_free(pile->elements);

    free(pile);
}

void cpile_push(Pile* pile, char elem) {
    vector_add_elem(pile->elements, elem);
}

void cpile_pop(Pile* pile) {
    if (pile->elements->taille > 0) {
        pile->elements->taille--;
    }
}

void cpile_print(Pile *pile) {
    for (int i = pile->elements->taille - 1; i >= 0; i--) {
        printf("%c ", pile->elements->valeurs[i]);
    }

    printf("\n");
}

//===========================================================================================================//
//                                            TreeNode PILE                                                  //
//===========================================================================================================//

TreeNodePile* treenode_pile_new() {
    TreeNodePile* pile = malloc(sizeof(TreeNodePile));
    pile->elements = treenode_vector_new();

    return pile;
}

void treenode_pile_free(TreeNodePile* pile) {
    treenode_vector_free(pile->elements);

    free(pile);
}

void treenode_pile_push(TreeNodePile* pile, TreeNode* node) {
    treenode_vector_add_elem(pile->elements, node);
}

void treenode_pile_pop(TreeNodePile* pile) {
    if (pile->elements->taille > 0) {
        pile->elements->taille--;
    }
}

void treenode_pile_print(TreeNodePile *pile) {
    for (int i = pile->elements->taille - 1; i >= 0; i--) {
        printf("%c ", pile->elements->valeurs[i]);
    }

    printf("\n");
}


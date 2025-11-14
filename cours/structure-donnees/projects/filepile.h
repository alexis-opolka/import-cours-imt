#ifndef UTILS_H
#include "utils.h"
#endif

#ifndef FILEPILE_H
#define FILEPILE_H
#endif

typedef struct File {
    DoubleLinkedList *elements;
} File;
typedef struct Pile {
    Vector* elements;
} Pile;
typedef struct TreeNodePile {
    TreeNodeVector* elements;
} TreeNodePile;

//===========================================================================================================//
//                                                  PILE                                                     //
//===========================================================================================================//

Pile* cpile_new();
void cpile_free(Pile* pile);
void cpile_push(Pile* pile, char elem);
void cpile_pop(Pile* pile);
void cpile_print(Pile *pile);

//===========================================================================================================//
//                                            TREENODE PILE                                                  //
//===========================================================================================================//

TreeNodePile* treenode_pile_new();
void treenode_pile_free(TreeNodePile* pile);
void treenode_pile_push(TreeNodePile* pile, TreeNode node);
void treenode_pile_pop(TreeNodePile* pile);
void treenode_pile_print(TreeNodePile *pile);


// Two define instructions to have a "constructor-like" behaviour
// for our Pile structures depending on the given type and with
// a forwarding of the constructors parameters.
#define _SELECT_PILE_CONSTRUCTOR(T) _Generic((T)0, \
        Pile*: cpile_new, \
        TreeNodePile*: treenode_pile_new \
    )
#define Pile(T, ...) (_SELECT_PILE_CONSTRUCTOR(T))(__VA_ARGS__)

// Below are the different handlers depending on the type
#define pile_free(pile, value) _Generic((value), \
    char: cpile_free, \
    TreeNode*: treenode_pile_free \
    )(pile, value)

#define pile_push(pile, value) _Generic((value), \
    char: cpile_push, \
    TreeNode*: treenode_pile_push \
    )(pile, value)

#define pile_pop(pile, value) _Generic((value), \
    char: cpile_pop, \
    TreeNode*: treenode_pile_pop, \
    )(pile, value)

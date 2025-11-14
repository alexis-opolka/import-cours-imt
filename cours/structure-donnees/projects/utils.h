#ifndef STDIO_H
#define STDIO_H
#include "stdio.h"
#endif

#ifndef STDBLIB_H
#define STDBLIB_H
#include "stdlib.h"
#endif

#ifndef STRING_H
#define STRING_H
#include "string.h"
#endif

#ifndef UTILS_H
#define UTILS_H
#endif


typedef struct Node {
  struct Node* next;
  char elem;
} Node;

typedef struct TreeNode{
    char value;
    struct TreeNode* noeud_gauche;
    struct TreeNode* noeud_droit;
} TreeNode;

typedef struct Vector {
  int taille;
  int reserve;
  char* valeurs;
} Vector;

typedef struct TreeNodeVector {
  int taille;
  int reserve;
  TreeNode* valeurs;
} TreeNodeVector;

typedef struct LinkedList {
  Node* start;
  Node* end;
} LinkedList;

typedef struct DoubleNode {
  struct DoubleNode* next;
  struct DoubleNode* previous;
  char elem;
} DoubleNode;
typedef struct DoubleLinkedList {
  DoubleNode* start;
  DoubleNode* end;
} DoubleLinkedList;

//===========================================================================================================//
//                                                Real Utils                                                 //
//===========================================================================================================//

void printTitle(char* title);
char* read_file(char* path, int* length);
void print_time(char* format, double time);

//===========================================================================================================//
//                                                  Vectors                                                  //
//===========================================================================================================//

Vector* vector_new();
Vector* vector_from_buffer(char* buffer, int size);
void vector_add_elem(Vector* v, char elem);
int vector_rechercher(Vector* v, int starting_at, char elem);
void vector_free(Vector* v);
int vector_used_memory(Vector* v);

//===========================================================================================================//
//                                             TreeNode Vectors                                              //
//===========================================================================================================//

TreeNodeVector* treenode_vector_new();
void treenode_vector_add_elem(TreeNodeVector* v, TreeNode elem);
int treenode_vector_rechercher(TreeNodeVector* v, int starting_at, TreeNode elem);
void treenode_vector_free(TreeNodeVector* v);
int treenode_vector_used_memory(TreeNodeVector* v);

//===========================================================================================================//
//                                             LINKED LISTS                                                  //
//===========================================================================================================//

LinkedList* llist_new();
void llist_add_elem_start(LinkedList* ll, char elem);
LinkedList* llist_from_buffer(char* buffer, int size);
int llist_used_memory(LinkedList* ll);
Node* llist_rechercher(LinkedList* ll, Node* starting_at, char elem);

void llist_free(LinkedList* ll);

//===========================================================================================================//
//                                            DOUBLE LINKED LISTS                                            //
//===========================================================================================================//

DoubleLinkedList* double_llist_new();
void double_llist_add_elem_start(DoubleLinkedList* ll, char elem);
DoubleLinkedList* double_llist_from_buffer(char* buffer, int size);
int double_llist_used_memory(DoubleLinkedList* ll);
DoubleNode* double_llist_rechercher(DoubleLinkedList* ll, DoubleNode* starting_at, char elem);
void double_llist_free(DoubleLinkedList* ll);

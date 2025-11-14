#ifndef UTILS_H
#include "utils.h"
#endif

//===========================================================================================================//
//                                                Real Utils                                                 //
//===========================================================================================================//

void printTitle(char* title){
  printf("\n========== %s ==========\n\n", title);
}

char* read_file(char* path, int* length){
  char * buffer;
  FILE * f = fopen (path, "rb");
  if (f)
  {
    fseek (f, 0, SEEK_END);
    *length = ftell (f);
    buffer = malloc (*length + 1);
    fseek (f, 0, SEEK_SET);
    if (buffer)
    {
      fread (buffer, 1, *length, f);
    }
    buffer[*length] = 0;
    fclose (f);
  } else {
    printf("file not oppened : %s\n", path);
  }
  return buffer;
}

void print_time(char* format, double time) {
  if (time < 0.001) {
    printf(format, time * 1000.0 * 1000.0, "us");
  } else if (time < 1.0) {
    printf(format, time * 1000.0, "ms");
  } else {
    printf(format, time, "s");
  }
}

//===========================================================================================================//
//                                                  Vectors                                                  //
//===========================================================================================================//

Vector* vector_new() {
  Vector* v = malloc(sizeof(Vector));
  v->taille = 0;
  v->valeurs = malloc(3);
  v->reserve = 3;
  return v;
}


Vector* vector_from_buffer(char* buffer, int size) {
  Vector* v = malloc(sizeof(Vector));
  v->taille = size;
  v->valeurs = buffer;
  v->reserve = size;
  return v;
}

void vector_add_elem(Vector* v, char elem) {
  v->taille++;
  if (v->taille > v->reserve) {
    v->reserve *= 2;
    char* new_tab = malloc(v->reserve);
    memcpy(new_tab, v->valeurs, v->taille);
    free(v->valeurs);
    v->valeurs = new_tab;
  }
  v->valeurs[v->taille - 1] = elem;
}

int vector_rechercher(Vector* v, int starting_at, char elem) {
  for (int i = starting_at; i < v->taille; i++) {
    if (elem == v->valeurs[i]) {
      return i;
    }
  }
  return -1;
}

void vector_free(Vector* v) {
  free(v->valeurs);
  free(v);
}

int vector_used_memory(Vector* v) {
  return sizeof(v) + sizeof(char) * v->reserve;
}

//===========================================================================================================//
//                                             TreeNode Vectors                                              //
//===========================================================================================================//

TreeNodeVector* treenode_vector_new() {
  TreeNodeVector* v = malloc(sizeof(TreeNodeVector));
  v->taille = 0;
  v->valeurs = malloc(3);
  v->reserve = 3;
  return v;
}

void treenode_vector_add_elem(TreeNodeVector* v, TreeNode* elem) {
  v->taille++;
  if (v->taille > v->reserve) {
    v->reserve *= 2;
    TreeNode* new_tab = malloc(v->reserve);
    memcpy(new_tab, v->valeurs, v->taille);
    free(v->valeurs);
    v->valeurs = new_tab;
  }
  v->valeurs[v->taille - 1] = *elem;
}

int treenode_vector_rechercher(TreeNodeVector* v, int starting_at, TreeNode* elem) {
  for (int i = starting_at; i < v->taille; i++) {
    if (elem->value == v->valeurs[i].value) {
      return i;
    }
  }
  return -1;
}

void treenode_vector_free(TreeNodeVector* v) {
  free(v->valeurs);
  free(v);
}

int treenode_vector_used_memory(TreeNodeVector* v) {
  return sizeof(v) + sizeof(char) * v->reserve;
}

//===========================================================================================================//
//                                             LINKED LISTS                                                  //
//===========================================================================================================//

LinkedList* llist_new(){
  LinkedList* ll = malloc(sizeof(LinkedList));

  // Allocate the start and end sentinels
  ll->start = malloc(sizeof(Node));
  ll->end = malloc(sizeof(Node));

  // Initialise them
  ll->start->elem = 0;
  ll->end->elem = 0;

  // Point them to each other since they're the only ones at this stage
  ll->start->next = ll->end;
  ll->end->next = ll->start;

  return ll;
}

void llist_add_elem_start(LinkedList* ll, char elem) {
  // Allocate
  Node* new_node = malloc(sizeof(Node));

  // Init
  new_node->elem = elem;

  // Link the nodes to each other
  new_node->next = ll->start->next;
  ll->start->next = new_node;
}

LinkedList* llist_from_buffer(char* buffer, int size){
  // We create a plain linked list, free of elements which contains only our sentinels
  LinkedList* ll = llist_new();

  // We add the elements one by one
  for (int i = size; i > 0; i--) {
    // printf("Creating a new node for %c\n", buffer[i]);

    llist_add_elem_start(ll, buffer[i]);
  }

  return ll;
}

int llist_used_memory(LinkedList* ll){
  int total_size;
  char toFind = *"\x0";

  ll->end->elem = toFind;

  Node* current_node = ll->start->next;
  int i = 0;

  while (current_node->elem != toFind) {
    i++;

    current_node = current_node->next;
  }
  total_size = i*sizeof(Node);

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;

  return total_size;
}

Node* llist_rechercher(LinkedList* ll, Node* starting_at, char elem){
  // We're setting up the elem to find at the end
  ll->end->elem = elem;

  Node* curr_node = starting_at;
  while(curr_node->elem != elem) {
    curr_node = curr_node->next;
  }

  if (&curr_node == &(ll->end)) {
    printf("L'élément recherché n'est pas dans la liste");
  }

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;

  return curr_node;
}

void llist_free(LinkedList* ll){
  char toFind = *"\x0";

  ll->end->elem = toFind;

  Node* current_node = ll->start->next;

  while (current_node->elem != toFind) {

    Node* temp_node = current_node->next;

    free(current_node);
    current_node = temp_node;
  }

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;
}

//===========================================================================================================//
//                                            DOUBLE LINKED LISTS                                            //
//===========================================================================================================//

DoubleLinkedList* double_llist_new(){
  DoubleLinkedList* ll = malloc(sizeof(DoubleLinkedList));

  // Allocate the start and end sentinels
  ll->start = malloc(sizeof(DoubleNode));
  ll->end = malloc(sizeof(DoubleNode));

  // Initialise them
  ll->start->elem = 0;
  ll->end->elem = 0;

  // Point them to each other since they're the only ones at this stage
  /// First off, the start sentinel
  ll->start->next = ll->end;
  ll->start->previous = ll->end;


  /// Then the end sentinel
  ll->end->next = ll->start;
  ll->end->previous = ll->start;

  return ll;
}

void double_llist_add_elem_start(DoubleLinkedList* ll, char elem){
  // Allocate
  DoubleNode* new_node = malloc(sizeof(DoubleNode));

  // Init
  new_node->elem = elem;

  // Link the nodes to each other
  // We're setting up the next and previous of the new_node
  new_node->next = ll->start->next;
  new_node->previous = ll->start;

  // We're updating our next node that the new node is now its previous node
  new_node->next->previous = new_node;

  // We're updating the start node to have the new node as its next node
  ll->start->next = new_node;
}

DoubleLinkedList* double_llist_from_buffer(char* buffer, int size){
  // We create a plain linked list, free of elements which contains only our sentinels
  DoubleLinkedList* ll = double_llist_new();

  // We add the elements one by one
  for (int i = size; i > 0; i--) {
    // printf("Creating a new node for %c\n", buffer[i]);

    double_llist_add_elem_start(ll, buffer[i]);
  }

  return ll;
}

int double_llist_used_memory(DoubleLinkedList* ll){
  int total_size;
  char toFind = *"\x0";

  ll->end->elem = toFind;

  DoubleNode* current_node = ll->start->next;
  int i = 0;

  while (current_node->elem != toFind) {
    i++;

    current_node = current_node->next;
  }
  total_size = i*sizeof(DoubleNode);

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;

  return total_size;
}

DoubleNode* double_llist_rechercher(DoubleLinkedList* ll, DoubleNode* starting_at, char elem){
  // We're setting up the elem to find at the end
  ll->end->elem = elem;

  DoubleNode* curr_node = starting_at;
  while(curr_node->elem != elem) {
    curr_node = curr_node->next;
  }

  if (&curr_node == &(ll->end)) {
    printf("L'élément recherché n'est pas dans la liste");
  }

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;

  return curr_node;
}

void double_llist_free(DoubleLinkedList* ll){
  char toFind = *"\x0";

  ll->end->elem = toFind;

  DoubleNode* current_node = ll->start->next;

  while (current_node->elem != toFind) {
    DoubleNode* temp_node = current_node->next;

    free(current_node);
    current_node = temp_node;
  }

  // We're setting up the elem of the end sentinel back to its original value
  ll->end->elem = 0;
}

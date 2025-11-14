#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "../utils.c"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       TYPES DEFINITION                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Vector {
  int taille;
  int reserve;
  char* valeurs;
} Vector;

typedef struct Node {
  struct Node* next;
  char elem;
} Node;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       VECTOR FUNCTIONS                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      LINKED LISTS FUNCTIONS                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void llist_add_elem_start(LinkedList* ll, char elem){
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      DOUBLE LINKED LISTS FUNCTIONS                                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       SCRIPT FUNCTIONS                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int testBaseVector(){
  double cpu_time_used;
  clock_t start, end;
 
  start = clock();
  int size;
  char* buffer = read_file("dict.txt", &size);
  Vector* v = vector_from_buffer(buffer, size);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  print_time("Tableau chargé en %.3lf %s\n", cpu_time_used);
  printf("Memoire utilisée pour %d elements: %.3fMo\n", v->taille, ((float)vector_used_memory(v)) / 1000000.0);

  int total = 0;

  start = clock();
  for (char c = 'a'; c < 'z'; c++) {
    for (int pos = 0;(pos = vector_rechercher(v, pos + 1, c)) != -1; total++);
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("26 parcours de tableau et %d appels à la fonction rechercher ", total);
  print_time("en %.3lf %s\n", cpu_time_used);

  vector_free(v);
}

int testVectorPlus(){
  double cpu_time_used;
  clock_t start, end;
 
  start = clock();
  int size;
  char* buffer = read_file("dict.txt", &size);
  Vector* v = vector_from_buffer(buffer, size+50);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  print_time("Tableau chargé en %.3lf %s\n", cpu_time_used);
  printf("Memoire utilisée pour %d elements: %.3fMo\n", v->taille, ((float)vector_used_memory(v)) / 1000000.0);

  int total = 0;

  start = clock();
  for (char c = 'a'; c < 'z'; c++) {
    for (int pos = 0;(pos = vector_rechercher(v, pos + 1, c)) != -1; total++);
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("26 parcours de tableau et %d appels à la fonction rechercher ", total);
  print_time("en %.3lf %s\n", cpu_time_used);

  vector_free(v);
}



void testListeChainee(){
  double cpu_time_used;
  clock_t start, end;
 
  start = clock();
  int size;
  char* buffer = read_file("dict.txt", &size);
  LinkedList* ll = llist_from_buffer(buffer, size);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  print_time("Tableau chargé en %.3lf %s\n", cpu_time_used);
  printf("Memoire utilisée pour %d elements: %.3fMo\n", size, ((float)llist_used_memory(ll)) / 1000000.0);

  //
  // Block to test out the linked list
  // Uncomment only if you want to print out the entire file
  //
  //=========================================================
  //
  // Node* curr_node = ll->start->next;
  // for (int i = 0; i < size; i++){
  //   printf("%c", curr_node->elem);
  //   curr_node = curr_node->next;
  // }
  // printf("\n");
  //

  int total = 0;

  start = clock();
  for (char c = 'a'; c < 'z'; c++) {
    for (Node* pos = ll->start;(pos = llist_rechercher(ll, pos->next, c))->elem != 0; total++);
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("26 parcours de tableau et %d appels à la fonction rechercher ", total);
  print_time("en %.3lf %s\n", cpu_time_used);

  llist_free(ll);
}

void doubleTestListeChainee(){
  double cpu_time_used;
  clock_t start, end;
 
  start = clock();
  int size;
  char* buffer = read_file("dict.txt", &size);
  DoubleLinkedList* ll = double_llist_from_buffer(buffer, size);
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  
  print_time("Tableau chargé en %.3lf %s\n", cpu_time_used);
  printf("Memoire utilisée pour %d elements: %.3fMo\n", size, ((float)double_llist_used_memory(ll)) / 1000000.0);

  //
  // Block to test out the linked list
  // Uncomment only if you want to print out the entire file
  //
  //=========================================================
  //
  // Node* curr_node = ll->start->next;
  // for (int i = 0; i < size; i++){
  //   printf("%c", curr_node->elem);
  //   curr_node = curr_node->next;
  // }
  // printf("\n");
  //

  int total = 0;

  start = clock();
  for (char c = 'a'; c < 'z'; c++) {
    for (DoubleNode* pos = ll->start;(pos = double_llist_rechercher(ll, pos->next, c))->elem != 0; total++);
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("26 parcours de tableau et %d appels à la fonction rechercher ", total);
  print_time("en %.3lf %s\n", cpu_time_used);

  double_llist_free(ll);
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          MAIN FUNCTION                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main() {
  // de https://github.com/chrplr/openlexicon/blob/master/datasets-info/Liste-de-mots-francais-Gutenberg/liste.de.mots.francais.frgut.txt
  // RAW: https://raw.githubusercontent.com/chrplr/openlexicon/refs/heads/master/datasets-info/Liste-de-mots-francais-Gutenberg/liste.de.mots.francais.frgut.txt

  printTitle("Vecteur de base");
  testBaseVector();

  printTitle("Vecteur avec 50 charactères de plus");
  testVectorPlus();

  printTitle("Liste chainée");
  testListeChainee();

  printTitle("Liste doublement chainée");
  doubleTestListeChainee();
}


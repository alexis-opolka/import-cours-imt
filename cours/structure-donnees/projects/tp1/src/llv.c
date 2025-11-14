#define MAX_SIZE 100

// Un noeud contient:
//    un vecteur dont la taille sera entre MAX_SIZE/2 et MAX_SIZE
//    un pointeur vers le noeud suivant
typedef struct LLVNode {
  Vector* elem;
  struct LLVNode* next;
} LLVNode;

typedef struct LinkedListVector {
  LLVNode* start;
  LLVNode* end;
} LinkedListVector;

// Enregistre la position d'un charactère dans la liste
typedef struct LLVPos {
  // le noeud dans lequel le charactère se situe
  LLVNode* node;
  // la position du charactère dans le vecteur associé au noeud
  int position;
} LLVPos;

// affiche le contenu de la liste
void llv_print_all(LinkedListVector* l);
// sépare un noeud de taille 100 en deux noeuds de taille 50
// Maintient la cohérence des pointeurs (next)
void llv_split_node(LLVNode* node);
// renvoie la mémoire totale utilisée par la liste
int llv_used_memory(LinkedListVector* llv);
// renvoie la position du charactère recherché en partant de la position donnée
LLVPos llv_rechercher(LinkedListVector* llv, LLVPos starting_at, char elem);
// Ajoute un charactère à la fin du noeud donné
// renvoie 1 si le noeud a du être splitté car il contenait plus de 100 charactères
int llv_add_elem_after(LLVNode* node, char elem);
// ajoute un élément à la position donnée
void llv_add_elem_at(LLVPos node, char elem);
// ajoute un mot à la position donnée
void llv_add_word_after(LLVPos starting_at, char* word);
// compte le nombre total de charactères dans la liste
int llv_count(LinkedListVector* l);

LinkedListVector* llv_new() {
  LinkedListVector* llv = malloc(sizeof(LinkedListVector));
  llv->start = malloc(sizeof(LLVNode));
  llv->end = malloc(sizeof(LLVNode));

  llv->start->next = llv->end;
  llv->start->elem = vector_new(MAX_SIZE / 2);

  llv->end->next = llv->end;
  llv->end->elem = vector_new(MAX_SIZE / 2);

  return l;
}

LinkedListVector* llv_from_buffer(char* buffer, int size) {
  LinkedListVector* llv = llv_new();
  LLVNode* n = llv->start;
  for (int i = 0; i < size; i++) {
    int splitted = llv_add_elem_after(n, buffer[i]);
    if (splitted) {
      n = n->next;
    }
  }
  return llv;
}

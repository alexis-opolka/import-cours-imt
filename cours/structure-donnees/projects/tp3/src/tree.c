#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
    char value;
    struct Node* noeud_gauche;
    struct Node* noeud_droit;
} Node;

Node* create_node(Node* noeud_gauche, char value, Node* noeud_droit){
    Node* n = (Node*)malloc(sizeof(Node));
    n->noeud_gauche = noeud_gauche;
    n->noeud_droit = noeud_droit;
    n->value = value;
    return n;
}

// ******** FONCTION A IMPLEMENTER 

// affiche les valeurs des noeuds en utilisant un parcours en profondeur
void affiche_profondeur(Node* n);

// affiche les valeurs des noeuds en utilisant un parcours en largeur
void affiche_largeur(Node* n);

// calcule le resultat de l'expression enregistrée dans l'arbre
int calcule_resultat(Node* n);

int main(){
    Node* cinq = create_node(NULL, '5', NULL);
    Node* six = create_node(NULL, '6', NULL);
    Node* sept = create_node(NULL, '7', NULL);
    Node* a = create_node(create_node(sept, '-', cinq), '+', six);
    Node* b = create_node( cinq, '*',a);
    Node* c = create_node( b, '*',a);
    affiche_largeur(c);
    // affiche_profondeur(c);
    // printf("%d\n", calcule_resultat(c));
    free(cinq);
    free(six);
    free(sept);
    free(a);
    free(b);
    free(c);
}

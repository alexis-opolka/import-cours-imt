#ifndef STDIO_H
#define STDIO_H
#include "stdio.h"
#endif

#ifndef STDBLIB_H
#define STDBLIB_H
#include "stdlib.h"
#endif

#ifndef UTILS_H
#include "../utils.c"
#endif

#ifndef FILEPILE_H
#include "../filepile.c"
#endif

TreeNode* create_node(TreeNode* noeud_gauche, char value, TreeNode* noeud_droit){
    TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
    n->noeud_gauche = noeud_gauche;
    n->noeud_droit = noeud_droit;
    n->value = value;
    return n;
}

// ******** FONCTION A IMPLEMENTER 

// affiche les valeurs des noeuds en utilisant un parcours en profondeur
void affiche_profondeur(TreeNode* n){
    TreeNodePile* pile = Pile(TreeNodePile*);
    // TODO: Doesn't work
    // pile_push(pile, n);
}

// affiche les valeurs des noeuds en utilisant un parcours en largeur
void affiche_largeur(TreeNode* n);

// calcule le resultat de l'expression enregistrée dans l'arbre
int calcule_resultat(TreeNode* n);

int main(){


    TreeNode* cinq = create_node(NULL, '5', NULL);
    printf("Ha!\n");

    TreeNode* six = create_node(NULL, '6', NULL);
    TreeNode* sept = create_node(NULL, '7', NULL);
    TreeNode* a = create_node(create_node(sept, '-', cinq), '+', six);
    TreeNode* b = create_node( cinq, '*',a);
    TreeNode* c = create_node( b, '*',a);

    
    //affiche_largeur(c);
    affiche_profondeur(c);
    //printf("%d\n", calcule_resultat(c));
    free(cinq);
    free(six);
    free(sept);
    free(a);
    free(b);
    free(c);
}

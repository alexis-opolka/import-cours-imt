#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"
#include "../utils.c"

typedef struct Pile {
    Vector* elements;
} Pile;

Pile* pile_new() {
    Pile* pile = malloc(sizeof(Pile));
    pile->elements = vector_new();

    return pile;
}

void pile_free(Pile* pile) {
    vector_free(pile->elements);

    free(pile);
}

void pile_push(Pile* pile, char elem) {
    vector_add_elem(pile->elements, elem);
}

void pile_pop(Pile* pile) {
    if (pile->elements->taille > 0) {
        pile->elements->taille--;
    }
}

void pile_print(Pile *pile) {
    for (int i = pile->elements->taille - 1; i >= 0; i--) {
        printf("%c ", pile->elements->valeurs[i]);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    Pile *pile = pile_new();
    
    pile_push(pile, 'a');
    pile_push(pile, 'b');
    pile_push(pile, 'c');

    printf("Contenu de la pile:\n");
    pile_print(pile);

    printf("\nDépiler un élément...\n");
    pile_pop(pile);
    printf("Contenu de la pile après dépilement:\n");
    pile_print(pile);

    printf("\nMémoire utilisée par la pile: %d octets\n", vector_used_memory(pile->elements));
    pile_free(pile);

    return 0;
}
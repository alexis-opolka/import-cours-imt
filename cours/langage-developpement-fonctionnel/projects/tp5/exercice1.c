#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vecteur {
    int* tableau;
    int taille;
};
typedef struct Vecteur Vecteur;

void init(Vecteur* vector_struct, int f) {
    vector_struct->tableau = malloc(sizeof(int));
    vector_struct->tableau[0] = f;
    vector_struct->taille = 1;
}

void end(Vecteur* vector_struct, int f) {
    int* newtab = malloc(sizeof(int) * (vector_struct->taille));
    for (int i = 0; i < vector_struct->taille; i++) {
        newtab[i] = (vector_struct->tableau)[i];
    }

    printf("DEBUG Table: %d\n", vector_struct->tableau);
    printf("DEBUG Taille: %d\n", vector_struct->taille);

    newtab[vector_struct->taille] = f;
    free(vector_struct->tableau);

    vector_struct->tableau = newtab;
}

void freememory(Vecteur* vector_struct) {
    free(vector_struct->tableau);
}

int main() {
    struct Vecteur my_vector = {.taille = 0};

    char choice = 'y';
    while (choice == 'y') {
        int current_value;
        printf("Entrez une valeur int à ajouter au tableau :\n");
        scanf("%d", &current_value);

        if (my_vector.taille == 0) {
            init(&my_vector, current_value);
            printf("DEBUG: INIT: Table initiated!\n");
        } else {
            // We're incrementing the count
            my_vector.taille += 1;

            end(&my_vector, current_value);
        }


        printf("Voulez-vous ajouter une autre valeur ? (y/n) :\n");
        scanf(" %c", &choice);
    }

    printf("Le tableau à l'envers est :\n");

    for (int i = my_vector.taille; i >= 0; i--) {
        printf("%d\n", my_vector.tableau[i]);
    }

    freememory(&my_vector.tableau);
}

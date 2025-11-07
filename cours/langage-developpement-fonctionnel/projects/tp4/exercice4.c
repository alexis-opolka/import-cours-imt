#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vecteur {
    int* tableau;
    int taille;
};

float* init(int* n, float f) {
    float* tab = malloc(sizeof(float));
    tab[0] = f;
    *n = 1;
    return tab;
}

void end(int* n, float** tab, float f) {
    float* newtab = malloc(sizeof(float) * (*n+1));
    for (int i = 0; i < *n; i++) {
        newtab[i] = (*tab)[i];
    }
    newtab[*n] = f;
    free(*tab);
    *tab = newtab;
    (*n)++;
}

void freememory(float* tab) {
    free(tab);
}

int main() {
    int n;
    float first;
    printf("Entrez une valeur float à ajouter au tableau :\n");
    scanf("%f", &first);

    float* tab = init(&n, first);
    char choice = 'y';
    while (choice == 'y') {
        float value;
        printf("Entrez une valeur float à ajouter au tableau :\n");
        scanf("%f", &value);
        end(&n, &tab, value);
        printf("Voulez-vous ajouter une autre valeur ? (y/n) :\n");
        scanf(" %c", &choice);
    }
    printf("Le tableau à l'envers est :\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("%f\n", tab[i]);
    }
    freememory(tab);
}
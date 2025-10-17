#include <stdio.h>
#include <stdlib.h>

int main() {
    int nombre1;
    int nombre2;

    printf("Donnez un entier : ");
    scanf("%d", &nombre1);

    printf("Donnez un second entier : ");
    scanf("%d", &nombre2);

    // 1 - On affiche seulement l'entier le plus grand des deux
    if (nombre1 > nombre2) {
        printf("%d est plus grand que %d \n", nombre1, nombre2);
    } else if (nombre2 > nombre1) {
        printf("%d est plus petit que %d \n", nombre1, nombre2);
    } else {
        printf("%d est égal à %d \n", nombre1, nombre2);
    }

    // 2.1 - On calcule la valeur absolue des deux entiers
    int absnbr1 = abs(nombre1);
    int absnbr2 = abs(nombre2);

    // 2.2 - On affiche la valeur absolue des deux entiers
    printf("La valeur absolue de %d et %d sont : %d et %d\n", nombre1, nombre2, absnbr1, absnbr2);

    // 2.3 - On affiche seuelement la valeur absolue la plus grande
    if (absnbr1 > absnbr2) {
        printf("%d est la valeur absolue plus grande que la valeur absolue %d \n", absnbr1, absnbr2);
    } else if (absnbr2 > absnbr1) {
        printf("%d est la valeur absolue plus grande que la valeur absolue %d \n", absnbr2, absnbr1);
    } else {
        printf("La valeur absolue %d est égale à la valeur absolue %d \n", absnbr1, absnbr2);
    }
}

#include <stdio.h>

int main() {
    char nombre;

    printf("Donnez un entier: ");
    scanf(" %d", &nombre);


    printf("Vous avez choisi l'entier naturel: %d et il %s !\n", nombre, (nombre % 2) == 0 ? "est pair" : "est impair");
}

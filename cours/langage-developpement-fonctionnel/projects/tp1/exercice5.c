#include <stdio.h>

int main() {
    float rayon;

    printf("Donnez le rayon de votre cercle: ");
    scanf(" %f", &rayon);

    // 1 - On affiche la surface du cercle
    printf("La surface de votre cercle est donc de: %f\n", 3.14 * (rayon * rayon));

    // 2 - On affiche le périmètre du cercle
    printf("Le périmètre de votre cercle est donc de: %f\n", 2 * 3.14 * rayon);
}

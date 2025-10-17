#include <stdio.h>

int main() {
    char age;

    printf("Donnez votre âge: ");
    scanf(" %d", &age);

    // Première condition => Les +60 ans
    if (age > 60) {
        printf("Votre tarif est de 10€ !\n");
        return 0;
    }

    // Deuxième condition => les 20 à 59 ans
    if (age > 20 && age < 60) {
        printf("Votre tarif est de 50€ !\n");
        return 0;
    }

    // Troisième condition => les 5 à 19 ans
    if (age > 4 && age < 20) {
        printf("Votre tarif est de 15€ !\n");
        return 0;
    }

    // Quatrième condition => les moins de 5 ans
    if (age < 5) {
        printf("C'est gratuit pour vous !\n");
        return 0;
    }
}

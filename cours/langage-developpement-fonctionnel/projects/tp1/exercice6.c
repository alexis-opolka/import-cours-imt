#include <stdio.h>

int main() {
    char ini1;
    char ini2;
    char ini3;

    printf("Donnez l'initiale d'un prénom : ");
    scanf(" %c", &ini1);

    printf("Donnez l'initiale d'un second prénom : ");
    scanf(" %c", &ini2);

    printf("Donnez l'initiale d'un troisième prénom : ");
    scanf(" %c", &ini3);

    // First letter
    if (ini1 > ini2 && ini1 > ini3) { printf("%c", ini1); }
    if (ini2 > ini1 && ini2 > ini3) { printf("%c", ini2); }
    if (ini3 > ini1 && ini3 > ini2) { printf("%c", ini3); }

    // Second letter
    if (ini1 < ini2 && ini1 > ini3) { printf("%c", ini1); }
    if (ini2 < ini1 && ini2 > ini3) { printf("%c", ini2); }
    if (ini3 < ini1 && ini3 > ini2) { printf("%c", ini3); }

    // Third letter

}

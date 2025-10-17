#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t holder;
    int numbers[5] = {};

    for (int i = 0; i < 5; i++){
        char local_number;

        printf("Entrez un nombre entier %d entre 0 et 63 compris: ", i+1);
        scanf(" %d", &local_number);

        // TODO: use masks to cover which bit to set with the number and where
        //      https://stackoverflow.com/questions/4439078/how-do-you-set-only-certain-bits-of-a-byte-in-c-without-affecting-the-rest#4439221
    }

    printf("Holder: %d\n", holder);
}




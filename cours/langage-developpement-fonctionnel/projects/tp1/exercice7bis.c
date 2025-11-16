#include <stdio.h>
#include <stdint.h>

uint32_t store_number(uint32_t holder, uint8_t* number, int position) {
    // We use GCC ability to declare a binary to set up the defined result with the predetermined
    // values
    uint32_t final_result = 0b00001010000001001001111111100001;

    // We shift the holder value of 6 bits to accomodate the next value given!
    holder = holder << 6;

    // We do a bitwise OR operation to write the given number onto the 32 bit storage
    holder |= *number;

    printf("Numéro final: %u\n", holder);

    if (holder == final_result) {
        // 00001010 00000100 10011111 11100001
        // 00001010 00000100 10011111 11100001 
        printf("Nous avons bien compilé nos 5 entiers prédéfinis dans nos 32 bits à disposition!\n");
    }

    return holder;
}

int main() {
    uint32_t holder = 0;
    int numbers[5] = {};

    for (int i = 0; i < 5; i++){
        uint8_t local_number;

        printf("Entrez un nombre entier %d entre 0 et 63, bornes comprises: ", i+1);
        scanf(" %u", &local_number);

        holder = store_number(holder, &local_number, i);
    }
}




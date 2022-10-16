#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define TRUE 1
#define FALSE 0

int main(void) {
    int64_t *number = malloc(sizeof(int64_t));
    unsigned *binary_string = malloc(sizeof(unsigned) * 64);
    unsigned *hex_string = malloc(sizeof(unsigned) * 16);
    unsigned int negative_flag = FALSE;

    printf("Please enter a valid 64-Bit signed integer: ");
    scanf("%li", number);

    if (*number < 0) { // Gets Absolute Value if the number is negative
        negative_flag = TRUE;
        *number = ~*number; // Flips the bits
        (*number)++;
    }

    for (int i = 63; i >= 0; i--) { // Traverses the array in reverse
        *(binary_string + i) = *number % 2;
        *number /= 2;
    }

    if (negative_flag) {
        for (int i = 63; i >= 0; i--) {
            if (*(binary_string + i) == 1) {
                for (int j = i - 1; j >= 0; j--) {
                    *(binary_string + j) ^= 1; // Flips Bits
                }
                break;
            }
        }
    }

    printf("Binary Value:\n\t");

    unsigned digit_counter = 0; // Used to track which bit is being printed to IO
    for (unsigned *i = binary_string; i - binary_string < 64; i++) {
        // Prints the Binary value, skipping a space every 4 bits
        printf("%u", *i);
        if (digit_counter == 3) {
            printf(" ");
            digit_counter = 0;
            continue;
        }
        digit_counter++;
    }

    for (int i = 0; i < 16; i++) { // Splits the binary array into 16 groups, each representing 4 bits
        *(hex_string + i) = 0;
        for (int j = 0; j < 4; j++) {
            *(hex_string + i) <<= 1; // Shifts the bit of the previous value to the left 1
            *(hex_string + i) |= *(binary_string + ((4 * i) + j)); // Concatenates the next bit
        }
    }

    printf("\nHex Value:\n\t0x");

    for (int i = 0; i < 16; i++) { // Prints the Hex Values
        printf("%x", *(hex_string + i));
    }

    return 0;
}

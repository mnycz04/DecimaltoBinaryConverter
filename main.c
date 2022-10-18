#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define TRUE 1
#define FALSE 0

typedef uint8_t bool;

char *binary_array_to_cstring_64(uint8_t *array) {
    char *string = malloc(sizeof(char) * 80);
    uint8_t digit_counter = 0;

    *(string + 79) = '\0'; // terminates C-string

    for (int i = 0, j = 0; i < 64; i++, j++) {
        if (digit_counter == 4) {
            digit_counter = 0;
            *(string + j) = ' ';
            j++;
        }
        *(string + j) = *(array + i) + 48; // 48 is ASCII for 0;
        digit_counter++;
    }

    return string;
}

int main(void) {
    int64_t *number = malloc(sizeof(int64_t));
    uint8_t *binary_string = malloc(sizeof(uint8_t) * 64);
    uint8_t *hex_string = malloc(sizeof(uint8_t) * 16);
    bool negative_flag = FALSE;

    printf("Enter a valid, 64-bit signed decimal integer: ");
    scanf("%li", number);
    printf("\n");

    // Check for Negative Value, if it is, gets the absolute value and stores it in *number
    if (*number < 0ll) {
        negative_flag = TRUE;
        *number = ~*number; // Flips All bits in *number
        (*number)++; // Adds one to get the actual absolute value
    }

    // Binary Section

    // Traverses the empty (uninitialized) array that'll hold the binary values, in reverse
    // By repeatedly dividing the original value by 2, the remainder gives us the next binary value,
    // starting from the least significant bit (LSB) all the way until the most.
    for (uint8_t *bit = binary_string + 63; bit >= binary_string; bit--) {
        *bit = *number % 2;
        *number /= 2;
    }
    free(number);

    printf("Unsigned Binary Value:\n\t%s\n", binary_array_to_cstring_64(binary_string));

    if (negative_flag) {
        for (int i = 63; i >= 0; i--) {
            // Finds the first least significant 1 in the values binary
            if (*(binary_string + i) == 1) {
                // Iterates over all remaining bits to the left of the bit found above
                for (uint8_t *bit = binary_string + i - 1; bit >= binary_string; bit--) {
                    *bit ^= 1; // Bitwise XOR against 1 flips every bit
                }
                break; // Stops after executing once
            }
        }
    }

    printf("Signed Binary Value:\n\t%s\n", binary_array_to_cstring_64(binary_string));


    // Hex Section

    // Groups the binary values into groups of 4 that are converted into their Hex representations
    for (int i = 0; i < 16; i++) {
        *(hex_string + i) = 0; // Initializes all values to be 0b00000000
        for (int j = 0; j < 4; j++) {
            // Shifts the current value to the left once, freeing the LSB for the next bit value
            *(hex_string + i) <<= 1;

            // 'Appends' the next bit to the end of the above value
            *(hex_string + i) |= *(binary_string + (4 * i) + j);
        }
    }

    printf("Hexadecimal Value:\n\t0x");
    for (int i = 0; i < 16; i++) {
        printf("%x", *(hex_string + i));
    }

    free(binary_string);
    free(hex_string);

    return 0;
}

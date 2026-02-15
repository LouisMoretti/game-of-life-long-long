#include <stdio.h>

#define ONE '@'
#define ZERO 'a'

// static int SIZE = sizeof(unsigned long long);
#define SIZE 8

static void print_game(unsigned long long game)
{
    for (int i = 0; i < SIZE; i++)
    {
        // unsigned long long line = (game >> (i * SIZE)) & 255;
        char line = (game >> (i * SIZE));
        for (int j = SIZE - 1; j >= 0; j--)
            putchar((line >> j) & 1 ? ONE : ZERO);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    printf("Hello world!\n");
    printf("Size: %d x %d\n", SIZE, SIZE);

    // clang-format off
    unsigned long long game = 0b11000000
                            + 0b00001111 * 0x100
                            + 0b00001111 * 0x10000
                            + 0b00001111 * 0x1000000
                            + 0b00001111 * 0x100000000
                            + 0b00001111 * 0x10000000000
                            + 0b00001111 * 0x1000000000000
                            + 0b00001111 * 0x100000000000000;
    // clang-format on

    print_game(game);
}

#include <stdio.h>
#include <unistd.h>

#define ONE '@'
#define ZERO 'a'

// static int SIZE = sizeof(unsigned long long);
#define SIZE 8
#define ULL unsigned long long

#define BIT_BOARD(a, b, c, d, e, f, g, h)                                      \
    ((ULL)(a) << 56 | (ULL)(b) << 48 | (ULL)(c) << 40 | (ULL)(d) << 32         \
     | (ULL)(e) << 24 | (ULL)(f) << 16 | (ULL)(g) << 8 | (ULL)(h))

static void print_game(ULL game)
{
    for (int y = SIZE - 1; y >= 0; y--)
    {
        // unsigned long long line = (game >> (y * SIZE)) & 255;
        unsigned char line = (game >> (y * SIZE));
        for (int x = SIZE - 1; x >= 0; x--)
        {
            putchar((line >> x) & 1 ? ONE : ZERO);
            // putchar(' ');
        }
        putchar('\n');
    }
}

static unsigned int get_adjacent_count(ULL game, int x, int y)
{
    unsigned int nb = 0;

    if (x == SIZE - 1)
    {
        nb += ((game >> (y * SIZE + x - 1)) & 1);

        if (y == SIZE - 1)
        {
            nb += ((game >> ((y - 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y - 1) * SIZE + x)) & 1);
        }
        else if (y == 0)
        {
            nb += ((game >> ((y + 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x)) & 1);
        }
        else
        {
            nb += ((game >> ((y - 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y - 1) * SIZE + x)) & 1)
                + ((game >> ((y + 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x)) & 1);
        }
    }
    else if (x == 0)
    {
        nb += ((game >> (y * SIZE + x + 1)) & 1);

        if (y == SIZE - 1)
        {
            nb += ((game >> ((y - 1) * SIZE + x)) & 1)
                + ((game >> ((y - 1) * SIZE + x + 1)) & 1);
        }
        else if (y == 0)
        {
            nb += ((game >> ((y + 1) * SIZE + x)) & 1)
                + ((game >> ((y + 1) * SIZE + x + 1)) & 1);
        }
        else
        {
            nb += ((game >> ((y - 1) * SIZE + x)) & 1)
                + ((game >> ((y - 1) * SIZE + x + 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x)) & 1)
                + ((game >> ((y + 1) * SIZE + x + 1)) & 1);
        }
    }
    else
    {
        nb += ((game >> (y * SIZE + x - 1)) & 1)
            + ((game >> (y * SIZE + x + 1)) & 1);

        if (y == SIZE - 1)
        {
            nb += ((game >> ((y - 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y - 1) * SIZE + x)) & 1)
                + ((game >> ((y - 1) * SIZE + x + 1)) & 1);
        }
        else if (y == 0)
        {
            nb += ((game >> ((y + 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x)) & 1)
                + ((game >> ((y + 1) * SIZE + x + 1)) & 1);
        }
        else
        {
            nb += ((game >> ((y - 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y - 1) * SIZE + x)) & 1)
                + ((game >> ((y - 1) * SIZE + x + 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x - 1)) & 1)
                + ((game >> ((y + 1) * SIZE + x)) & 1)
                + ((game >> ((y + 1) * SIZE + x + 1)) & 1);
        }
    }

    return nb;
}

static ULL next_step(ULL game)
{
    ULL next_game = 0;
    for (int y = SIZE - 1; y >= 0; y--)
    {
        for (int x = SIZE - 1; x >= 0; x--)
        {
            unsigned int adjacent_count = get_adjacent_count(game, x, y);
            next_game += (ULL)(adjacent_count == 3
                               || (adjacent_count == 2
                                   && ((game >> (y * SIZE + x)) & 1)))
                << (y * SIZE + x);
        }
    }
    return next_game;
}

int main(int argc, char **argv)
{
    printf("Hello world!\n");

    // clang-format off
    ULL game = BIT_BOARD(
        0b01000000,
        0b00100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    );
    // clang-format on

    print_game(game);

    while (1)
    {
        ULL game_next_step = next_step(game);

        if (game_next_step == game)
            break;

        game = game_next_step;

        sleep(1);

        puts("\nNext step:");
        print_game(game);
    }
}

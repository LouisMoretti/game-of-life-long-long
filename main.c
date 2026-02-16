#include <stdio.h>
// #include <unistd.h>

#define LIVE "██"
#define DEAD "  "

// static int SIZE = sizeof(unsigned long long);
#define SIZE 8
#define ULL unsigned long long

#define BIT_BOARD(a, b, c, d, e, f, g, h)                                      \
    ((ULL)(a) << 56 | (ULL)(b) << 48 | (ULL)(c) << 40 | (ULL)(d) << 32         \
     | (ULL)(e) << 24 | (ULL)(f) << 16 | (ULL)(g) << 8 | (ULL)(h))

static void print_game(ULL game)
{
    printf("╔════════════════╗\n");

    for (int y = SIZE - 1; y >= 0; y--)
    {
        printf("║");

        unsigned char line = (game >> (y * SIZE));
        for (int x = SIZE - 1; x >= 0; x--)
            printf((line >> x) & 1 ? LIVE : DEAD);

        printf("║\n");
    }

    printf("╚════════════════╝\n");
}

static unsigned int get_neighbours_count(ULL game, int x, int y)
{
    unsigned int neighbours_count = 0;

    if (x != 0)
    {
        neighbours_count += ((game >> (y * SIZE + x - 1)) & 1);

        if (y != 0)
            neighbours_count += ((game >> ((y - 1) * SIZE + x - 1)) & 1);

        if (y != SIZE - 1)
            neighbours_count += ((game >> ((y + 1) * SIZE + x - 1)) & 1);
    }

    if (x != SIZE - 1)
    {
        neighbours_count += ((game >> (y * SIZE + x + 1)) & 1);

        if (y != 0)
            neighbours_count += ((game >> ((y - 1) * SIZE + x + 1)) & 1);

        if (y != SIZE - 1)
            neighbours_count += ((game >> ((y + 1) * SIZE + x + 1)) & 1);
    }

    if (y != 0)
        neighbours_count += ((game >> ((y - 1) * SIZE + x)) & 1);

    if (y != SIZE - 1)
        neighbours_count += ((game >> ((y + 1) * SIZE + x)) & 1);

    return neighbours_count;
}

static ULL next_generation(ULL game)
{
    ULL next_generation = 0;
    for (int y = SIZE - 1; y >= 0; y--)
    {
        for (int x = SIZE - 1; x >= 0; x--)
        {
            unsigned int neighbours_count = get_neighbours_count(game, x, y);
            next_generation += (ULL)(neighbours_count == 3
                                     || (neighbours_count == 2
                                         && ((game >> (y * SIZE + x)) & 1)))
                << (y * SIZE + x);
        }
    }
    return next_generation;
}

int main(int argc, char **argv)
{
    printf("Hello world!\n");

    // clang-format off
    ULL game = BIT_BOARD(
        // 0b01000000,
        // 0b00100000,
        // 0b11100000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b00000000
    );
    // clang-format on

    // Print initial state.
    print_game(game);

    int generation_count = 0;
    while (1)
    {
        game = next_generation(game);

        // if (game_next_generation == game)
        //     break;

        generation_count++;
        // game = game_next_generation;

        // Sleep 0.15 sec.
        // usleep(150000);

        if (generation_count % 10000000 == 0)
        {
            printf("\nGeneration %d: %llu\n", generation_count, game);
            print_game(game);
        }
    }

    printf("Game ended, all life is still.\n");
}

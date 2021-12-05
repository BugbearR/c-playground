#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Xorshift32_tag
{
    uint32_t w;
} Xorshift32_t;

void Xorshift32_init(Xorshift32_t *pThis, uint32_t seed)
{
    pThis->w = (seed == 0) ? 2463534242 : seed;
}

uint32_t Xorshift32_next(Xorshift32_t *pThis)
{
    uint32_t w = pThis->w;
    w = w ^ (w << 13);
    w = w ^ (w >> 17);
    w = w ^ (w << 5);
    pThis->w = w;
    return w;
}

int main(int argc, char *argv[])
{
    uint32_t seed;
    int i;
    Xorshift32_t prng;

    if (argc >= 2)
    {
        sscanf(argv[1], "%" SCNu32, &seed);
        Xorshift32_init(&prng, (uint32_t)seed);
    }
    else
    {
        Xorshift32_init(&prng, 0);
    }

    for (i = 0; i < 10; i++)
    {
        printf("%" PRIu32 "\n", Xorshift32_next(&prng));
    }

    return EXIT_SUCCESS;
}

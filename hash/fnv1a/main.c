#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <cplayground/fnv1a.h>

int main(int argc, char *argv[])
{
    uint32_t r = cplayground_fnv1a_hash32(argv[1], strlen(argv[1]));
    printf("%08"PRIx32"\n", r);
    return EXIT_SUCCESS;
}

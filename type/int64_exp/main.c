#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
    int64_t i64;
    uint64_t u64;

    i64 = INT64_MAX;
    printf("INT64_MAX(decimal):%" PRId64 "\n", i64);
    printf("INT64_MAX(hex):%" PRIx64 "\n", i64);

    i64 = INT64_MIN;
    printf("INT64_MIN(decimal):%" PRId64 "\n", i64);
    printf("INT64_MIN(hex):%" PRIx64 "\n", i64);

    u64 = UINT64_MAX;
    printf("UINT64_MAX(decimal):%" PRIu64 "\n", u64);
    printf("UINT64_MAX(hex):%" PRIx64 "\n", u64);

    return EXIT_SUCCESS;
}

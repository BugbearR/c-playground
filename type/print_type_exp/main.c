#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char charMin = CHAR_MIN;
    printf("CHAR_MIN: %hhd\n", charMin);
    char charMax = CHAR_MAX;
    printf("CHAR_MAX: %hhd\n", charMax);

    signed char scharMin = SCHAR_MIN;
    printf("SCHAR_MIN: %hhd\n", scharMin);
    signed char scharMax = SCHAR_MAX;
    printf("SCHAR_MAX: %hhd\n", scharMax);

    unsigned char ucharMax = UCHAR_MAX;
    printf("UCHAR_MAX: %hhu\n", ucharMax);

    short shortMin = SHRT_MIN;
    printf("SHRT_MIN: %hd\n", shortMin);
    short shortMax = SHRT_MAX;
    printf("SHRT_MAX: %hd\n", shortMax);

    unsigned short ushortMax = USHRT_MAX;
    printf("USHRT_MAX: %hu\n", ushortMax);

    int intMin = INT_MIN;
    printf("INT_MIN: %d\n", intMin);
    int intMax = INT_MAX;
    printf("INT_MAX: %d\n", intMax);

    unsigned int uintMax = UINT_MAX;
    printf("UINT_MAX: %u\n", uintMax);

    long longMin = LONG_MIN;
    printf("LONG_MIN: %ld\n", longMin);
    long longMax = LONG_MAX;
    printf("LONG_MAX: %ld\n", longMax);

    unsigned long ulongMax = ULONG_MAX;
    printf("ULONG_MAX: %lu\n", ulongMax);

    long long longLongMin = LLONG_MIN;
    printf("LLONG_MIN: %lld\n", longLongMin);
    long long longLongMax = LLONG_MAX;
    printf("LLONG_MAX: %lld\n", longLongMax);

    unsigned long long ulongLongMax = ULLONG_MAX;
    printf("ULLONG_MAX: %llu\n", ulongLongMax);

    int floatPrecision10 = (log10(2.0) * FLT_MANT_DIG) + 2;
    printf("FLT_MANT_DIG: %d\n", FLT_MANT_DIG);
    float floatMin = FLT_MIN;
    printf("FLT_MIN: %.*e\n", floatPrecision10, floatMin);
    float floatMax = FLT_MAX;
    printf("FLT_MAX: %.*e\n", floatPrecision10, floatMax);

    int doublePrecision10 = (log10(2.0) * DBL_MANT_DIG) + 2;
    printf("DBL_MANT_DIG: %d\n", DBL_MANT_DIG);
    double doubleMin = DBL_MIN;
    printf("DBL_MIN: %.*le\n", doublePrecision10, doubleMin);
    double doubleMax = DBL_MAX;
    printf("DBL_MAX: %.*le\n", doublePrecision10, doubleMax);

    int ldoublePrecision10 = (log10(2.0) * LDBL_MANT_DIG) + 2;
    printf("LDBL_MANT_DIG: %d\n", LDBL_MANT_DIG);
    long double ldoubleMin = LDBL_MIN;
    printf("LDBL_MIN: %.*Le\n", ldoublePrecision10, ldoubleMin);
    long double ldoubleMax = LDBL_MAX;
    printf("LDBL_MAX: %.*Le\n", ldoublePrecision10, ldoubleMax);

    size_t sizeMax = SIZE_MAX;
    printf("SIZE_MAX: %zu\n", sizeMax);

    ssize_t ssizeMax = SSIZE_MAX;
    printf("SSIZE_MAX: %zd\n", ssizeMax);

    int8_t int8Min = INT8_MIN;
    printf("INT8_MIN: %"PRId8"\n", int8Min);
    int8_t int8Max = INT8_MAX;
    printf("INT8_MAX: %"PRId8"\n", int8Max);

    uint8_t uint8Max = UINT8_MAX;
    printf("ULONG_MAX: %"PRIu8"\n", uint8Max);

    int16_t int16Min = INT16_MIN;
    printf("INT16_MIN: %"PRId16"\n", int16Min);
    int16_t int16Max = INT16_MAX;
    printf("INT16_MAX: %"PRId16"\n", int16Max);

    uint16_t uint16Max = UINT16_MAX;
    printf("ULONG_MAX: %"PRIu16"\n", uint16Max);

    int32_t int32Min = INT32_MIN;
    printf("INT32_MIN: %"PRId32"\n", int32Min);
    int32_t int32Max = INT32_MAX;
    printf("INT32_MAX: %"PRId32"\n", int32Max);

    uint32_t uint32Max = UINT32_MAX;
    printf("ULONG_MAX: %"PRIu32"\n", uint32Max);

    int64_t int64Min = INT64_MIN;
    printf("INT64_MIN: %"PRId64"\n", int64Min);
    int64_t int64Max = INT64_MAX;
    printf("INT64_MAX: %"PRId64"\n", int64Max);

    uint64_t uint64Max = UINT64_MAX;
    printf("ULONG_MAX: %"PRIu64"\n", uint64Max);

    intmax_t intmaxMin = INTMAX_MIN;
    printf("INTMAX_MIN: %"PRIdMAX"\n", intmaxMin);
    intmax_t intmaxMax = INTMAX_MAX;
    printf("INTMAX_MAX: %"PRIdMAX"\n", intmaxMax);

    uintmax_t uintmaxMax = UINTMAX_MAX;
    printf("ULONG_MAX: %"PRIuMAX"\n", uintmaxMax);

    return EXIT_SUCCESS;
};

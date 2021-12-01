#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <float.h>
#include <limits.h>

volatile time_t dummy;

int main(void)
{
    struct tm *pTm;
    long double ld = 1.0l + LDBL_EPSILON;
    long double rld;
    double d = 1.0 + DBL_EPSILON;
    double rd;
    float f = 1.0f + FLT_EPSILON;
    float rf;
    long llmax = LLONG_MAX;
    long rll;
    long lmax = LONG_MAX;
    long rl;
    int imax = INT_MAX;
    long ri;

    do {
        dummy = (time_t)ld;
        rld = (long double)dummy;
        if (rld == ld) {
            printf("time_t: long double.\n");
            break;
        }

        dummy = (time_t)d;
        rd = (double)dummy;
        if (rd == d) {
            printf("time_t: double.\n");
            break;
        }

        dummy = (time_t)f;
        rf = (float)dummy;
        if (rf == f) {
            printf("time_t: float.\n");
            break;
        }

        if (llmax != lmax) {
            dummy = (time_t)llmax;
            rll = (long long)dummy;
            if (rll == llmax) {
                printf("time_t: long long.\n");
                break;
            }
        }

        if (lmax != imax) {
            dummy = (time_t)lmax;
            rl = (long)dummy;
            if (rl == lmax) {
                printf("time_t: long.\n");
                break;
            }

            dummy = (time_t)lmax;
            rl = (long)dummy;
            if (rl == lmax) {
                printf("time_t: long.\n");
                break;
            }
        }

        dummy = (time_t)imax;
        ri = (int)dummy;
        if (ri == imax) {
            printf("time_t: int.\n");
            break;
        }
    } while (0);

    return EXIT_SUCCESS;
}

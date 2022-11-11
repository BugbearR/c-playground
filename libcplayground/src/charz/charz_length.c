#include <cplayground/charz.h>

size_t cplayground_charz_length(const char *p)
{
    const char *pw = p;
    while (*pw != '\0')
    {
        pw++;
    }
    return pw - p;
}

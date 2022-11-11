#include <cplayground/charz.h>

bool cplayground_charz_isBlank(const char *p)
{
    const char *pw = p;
    char c;
    while ((c = *pw) != '\0')
    {
        if (c != ' ')
        {
            return false;
        }
        pw++;
    }
    return true;
}

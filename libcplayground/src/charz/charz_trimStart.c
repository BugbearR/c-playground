#include <cplayground/charz.h>

#include <string.h>

char *cplayground_charz_trimStart(char *pStr)
{
	char *p;
	char *pStart;
	char prevC = 0;
	char c;

    if (*pStr != ' ')
    {
        return pStr;
    }

	for (p = pStr + 1; (c = *p) && c == ' '; p++)
        ;
    if (c == '\0')
    {
        *pStr = '\0';
        return pStr;
    }

    pStart = p;
    p++;
	while (*p++)
        ;
    memmove(pStr, pStart, p - pStart);
    return pStr;
}

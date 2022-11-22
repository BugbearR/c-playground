#include <cplayground/charz.h>

char *cplayground_charz_trimEnd(char *pStr)
{
	char *p;
	char *pCut = NULL;
	char prevC = 0;
	char c;

	for (p = pStr; (c = *p); p++)
    {
		if (c == ' ')
        {
			if (prevC != ' ')
            {
				pCut = p;
			}
		}
		else
        {
			pCut = NULL;
		}
		prevC = c;
	}

	if (pCut)
    {
		*pCut = '\0';
	}

    return pStr;
}

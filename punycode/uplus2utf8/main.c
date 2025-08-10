#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static int utf8_fromCodePoint(uint8_t *pBuf, size_t bufLength, uint32_t codePoint)
{
    if (codePoint <= 0x7f)
    {
        if (bufLength < 1)
        {
            return -1;
        }
        pBuf[0] = (uint8_t)codePoint;
        return 1;
    }
    else if (codePoint <= 0x07ff)
    {
        if (bufLength < 2)
        {
            return -2;
        }
        pBuf[0] = (uint8_t)((codePoint >> 6) | 0xc0);
        pBuf[1] = (uint8_t)((codePoint & 0x3f) | 0x80);
        return 2;
    }
    else if (codePoint <= 0xffff)
    {
        if (bufLength < 3)
        {
            return -3;
        }
        pBuf[0] = (uint8_t)((codePoint >> 12) | 0xe0);
        pBuf[1] = (uint8_t)(((codePoint >> 6) & 0x3f) | 0x80);
        pBuf[2] = (uint8_t)((codePoint & 0x3f) | 0x80);
        return 3;
    }
    else if (codePoint <= 0x10ffffl)
    {
        if (bufLength < 4)
        {
            return -4;
        }
        pBuf[0] = (uint8_t)((codePoint >> 18) | 0xe0);
        pBuf[1] = (uint8_t)(((codePoint >> 12) & 0x3f) | 0x80);
        pBuf[2] = (uint8_t)(((codePoint >> 6) & 0x3f) | 0x80);
        pBuf[3] = (uint8_t)((codePoint & 0x3f) | 0x80);
        return 4;
    }
    return -5;
}

int main()
{
    int r;
    unsigned long code_point;
    char uplus[3];
    int len;
    uint8_t buf[4];

    for (;;)
    {
        r = scanf("%2s%lx", uplus, &code_point);
        if (ferror(stdin))
        {
            fprintf(stderr, "file read error.\n");
            return EXIT_FAILURE;
        }
        if (r == EOF || r == 0) break;

        if (r != 2 || !(uplus[0] == 'U'|| uplus[0] == 'u') || uplus[1] != '+' || code_point > 0x10ffffl)
        {
            fprintf(stderr, "invalid format.\n");
            return EXIT_FAILURE;
        }

        memset(buf, 0, sizeof(buf));
        len = utf8_fromCodePoint(buf, sizeof(buf), code_point);
        if (len >= 0) {
            printf("%s", buf);
        }
    }
    printf("\n");
}

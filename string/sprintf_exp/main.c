#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(void)
{
    char dstBuf[6];
    char srcBuf[4];
    int i;

    sprintf(dstBuf, "XXXXX");
    sprintf(srcBuf, "A");

    // sprintf(dstBuf, "%.2s", srcBuf);
    sprintf(dstBuf, "%-2.2s", srcBuf);

    for (i = 0; i < sizeof(dstBuf); i++)
    {
        printf("%02x ", dstBuf[i]);
    }

    return EXIT_SUCCESS;
}

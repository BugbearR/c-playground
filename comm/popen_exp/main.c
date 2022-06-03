#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *pFile = NULL;
    char buf[1024 + 1];

    char *pCommand = argv[1];

    pFile = popen(pCommand, "r");
    if (!pFile)
    {
        perror("popen");
        return EXIT_FAILURE;
    }

    for (;;)
    {
        fgets(buf, sizeof(buf), pFile);
    }

    pclose(pFile);
    pFile = NULL;

EXIT_FUNC:
    if (pFile)
    {
        pclose(pFile);
    }

    return EXIT_SUCCESS;
}

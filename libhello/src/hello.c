#include "hello/hello.h"

#include <stdio.h>

int myadd(int a, int b) {
    return a + b;
}

int mysub(int a, int b) {
    return a - b;
}

int sayHello(char *pBuf, size_t bufLen, const char *pTo) {
    int count = snprintf(pBuf, bufLen, "Hello, %s!", pTo);
    return count;
}

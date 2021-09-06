#include "hello/hello.h"
#include "foo/foo.h"

#include <stdio.h>

int myadd(int a, int b) {
    return a + b;
}

int mysub(int a, int b) {
    return a - b;
}

int sayHello(char *pBuf, size_t bufLen, const char *pTo) {
    int n = foo_hello();
    int count = snprintf(pBuf, bufLen, "Hello, %s!, %d", pTo, n);
    return count;
}

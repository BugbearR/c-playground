#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchElement.h"

typedef struct MyObj {
    int *elements;
    int target;
} MyObj_t;

int compare(void *pObj, int idx) {
    MyObj_t *pMyObj = (MyObj_t *)pObj;
    int element = pMyObj->elements[idx];
    if (element > pMyObj->target) return 1;
    if (element < pMyObj->target) return -1;
    return 0;
}

int main(int argc, char *argv[]) {
    MyObj_t obj;
    int i;

    if (argc < 3) {
        printf("Usage: %s targetNum elements...\n", argv[0]);
        return EXIT_FAILURE;
    }

    obj.target = atoi(argv[1]);

    int count = argc - 2;
    obj.elements = malloc(sizeof(int) * count);
    // no sort.
    for (i = 2; i < argc; i++) {
        obj.elements[i - 2] = atoi(argv[i]);
    }

    int result = BinarySearchElement_search(&obj, count, compare);

    if (result >= 0) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found. Insertion point: %d\n", -(result + 1));
    }

    return EXIT_SUCCESS;
}

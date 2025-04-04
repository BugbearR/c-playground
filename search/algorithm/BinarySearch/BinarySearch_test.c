#include <stdio.h>
#include <stdlib.h>
#include "BinarySearch.h"

typedef struct MyObj {
    int *arr;
    int target;
} MyObj_t;

int compareInt(void *pObj, int idx) {
    MyObj_t *pMyObj = (MyObj_t *)pObj;
    if (pMyObj->arr[idx] > pMyObj->target) return 1;
    if (pMyObj->arr[idx] < pMyObj->target) return -1;
    return 0;
}

int main(int argc, char *argv[]) {
    int data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    // int data[] = { 10, 20, 30, 40, 50 };
    MyObj_t obj;
    obj.arr = data;

    if (argc < 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }
    obj.target = atoi(argv[1]);

    int count = sizeof(data) / sizeof(data[0]);
    int result = BinarySearch_search(&obj, count, compareInt);

    if (result >= 0) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found. Insertion point: %d\n", -(result + 1));
    }

    return 0;
}

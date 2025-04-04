#ifndef MERGESORTFILE_H_
#define MERGESORTFILE_H_

#include <stddef.h>

int MergeSortFile_sort(
    const char *pInputFilePath,
    const char *pOutputFilePath,
    size_t recordSize,
    int (*fnCompare)(const void *pRecord1, const void *pRecord2, void *pContext),
    void *pContext,
    const char *pTempDirPath
);

#endif // MERGESORTFILE_H_

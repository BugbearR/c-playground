#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void Memory_insertSpace(char *p, size_t elementSize, size_t capacity, size_t count, size_t index, size_t insertCount);

void Memory_removeSpace(char *p, size_t elementSize, size_t capacity, size_t count, size_t index, size_t removeCount);

#endif // MEMORY_H

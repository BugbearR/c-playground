#include "Memory.h"

void Memory_removeSpace(char *p, size_t elementSize, size_t capacity, size_t count, size_t index, size_t removeCount)
{
    if (index < count)
    {
        size_t moveCount = count - index - removeCount;
        if (moveCount > 0)
        {
            memmove(p + (index * elementSize), p + ((index + removeCount) * elementSize), moveCount * elementSize);
        }
    }
}

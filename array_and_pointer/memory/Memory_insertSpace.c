#include "Memory.h"

void Memory_insertSpace(char *p, size_t elementSize, size_t capacity, size_t count, size_t index, size_t insertCount)
{
    if (index < count)
    {
        size_t moveCount = count - index;
        size_t leftCount = capacity - count;
        if (insertCount > leftCount)
        {
            moveCount -= (insertCount - leftCount);
        }

        memmove(p + ((index + insertCount) * elementSize), p + (index * elementSize), moveCount * elementSize);
    }
}

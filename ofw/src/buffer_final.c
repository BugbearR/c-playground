#include "ofw/buffer.h"

#include <stddef.h>

void Ofw_Buffer_final(Ofw_Buffer_t *pThis)
{
    if (pThis)
    {
        if (pThis->pBuffer)
        {
            free(pThis->pBuffer);
            pThis->pBuffer = NULL;
        }
    }
}

#include "ofw/buffer.h"

int32_t Ofw_Buffer_realloc(Ofw_Buffer_t *pThis, int32_t length)
{
    uint8_t *pNewBuffer = realloc(pThis->pBuffer, length);
    if (!pNewBuffer)
    {
        return Ofw_Error_FAILED;
    }
}

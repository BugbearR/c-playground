#include "ofw/buffer.h"

void Ofw_Buffer_init(Ofw_Buffer_t *pThis, int32_t length, uint8_t *pBuffer)
{
    pThis->length = length;
    pThis->pBuffer = pBuffer;
}

#include "CborEncoder.h"

void CborEncoder_writeUint64WithMajorType(CborEncoder_t *pThis, uint8_t majorType, uint64_t value)
{
    if (value <= UINT32_MAX)
    {
        CborEncoder_writeUint32WithMajorType(pThis, majorType, (uint32_t)value);
    }
    else
    {
        pThis->outFn(majorType | CBOR_ADDITIONAL_INFO_UINT64, pThis);
        pThis->outFn((uint8_t)((value >> 56) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 48) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 40) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 32) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 24) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 16) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 8) & 0xff), pThis);
        pThis->outFn((uint8_t)(value & 0xff), pThis);
    }
}

#include "CborEncoder.h"

void CborEncoder_writeUint32WithMajorType(CborEncoder_t *pThis, uint8_t majorType, uint32_t value)
{
    if (value < 24)
    {
        pThis->outFn((uint8_t)value, pThis);
    }
    else if (value <= UINT8_MAX)
    {
        pThis->outFn(majorType | CBOR_ADDITIONAL_INFO_UINT8, pThis);
        pThis->outFn((uint8_t)(value & 0xff), pThis);
    }
    else if (value <= UINT16_MAX)
    {
        pThis->outFn(majorType | CBOR_ADDITIONAL_INFO_UINT16, pThis);
        pThis->outFn((uint8_t)((value >> 8) & 0xff), pThis);
        pThis->outFn((uint8_t)(value & 0xff), pThis);
    }
    else if (value <= UINT32_MAX)
    {
        pThis->outFn(majorType | CBOR_ADDITIONAL_INFO_UINT32, pThis);
        pThis->outFn((uint8_t)((value >> 24) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 16) & 0xff), pThis);
        pThis->outFn((uint8_t)((value >> 8) & 0xff), pThis);
        pThis->outFn((uint8_t)(value & 0xff), pThis);
    }
}

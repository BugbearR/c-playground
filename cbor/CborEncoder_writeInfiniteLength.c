#include "CborEncoder.h"

void CborEncoder_writeInfiniteLength(CborEncoder_t *pThis, uint8_t majorType)
{
    pThis->outFn(majorType | CBOR_ADDITIONAL_INFO_INFINITE, pThis);
}

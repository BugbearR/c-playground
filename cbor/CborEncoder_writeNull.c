#include "CborEncoder.h"

void CborEncoder_writeNull(CborEncoder_t *pThis, bool value)
{
    pThis->outFn(CBOR_SIMPLE_VALUE_NULL, pThis);
}

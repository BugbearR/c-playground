#include "CborEncoder.h"

void CborEncoder_writeUndefined(CborEncoder_t *pThis, bool value)
{
    pThis->outFn(CBOR_SIMPLE_VALUE_UNDEFINED, pThis);
}

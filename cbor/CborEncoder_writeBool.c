#include "CborEncoder.h"

void CborEncoder_writeBool(CborEncoder_t *pThis, bool value)
{
    pThis->outFn(value ? CBOR_SIMPLE_VALUE_TRUE : CBOR_SIMPLE_VALUE_FALSE, pThis);
}

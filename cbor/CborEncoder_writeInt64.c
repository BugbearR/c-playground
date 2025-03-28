#include "CborEncoder.h"

void CborEncoder_writeInt64(CborEncoder_t *pThis, int32_t value)
{
    if (value < 0)
    {
        CborEncoder_writeUint64WithMajorType(pThis, CBOR_MAJOR_TYPE_NEGATIVE_INTEGER, -(value + 1));
    }
    else
    {
        CborEncoder_writeUint64WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
    }
}

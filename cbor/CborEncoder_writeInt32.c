#include "CborEncoder.h"

void CborEncoder_writeInt32(CborEncoder_t *pThis, int32_t value)
{
    if (value < 0)
    {
        CborEncoder_writeUint32WithMajorType(pThis, CBOR_MAJOR_TYPE_NEGATIVE_INTEGER, -(value + 1));
    }
    else
    {
        CborEncoder_writeUint32WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
    }
}

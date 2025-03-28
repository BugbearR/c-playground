#include "CborEncoder.h"

void CborEncoder_writeUint32(CborEncoder_t *pThis, uint32_t value)
{
    CborEncoder_writeUint32WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
}

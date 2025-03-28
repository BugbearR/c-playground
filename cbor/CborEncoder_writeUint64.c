#include "CborEncoder.h"

void CborEncoder_writeUint64(CborEncoder_t *pThis, uint64_t value)
{
    CborEncoder_writeUint64WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
}

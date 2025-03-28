#include "CborEncoder.h"

void CborEncoder_writeUint8(CborEncoder_t *pThis, uint8_t value)
{
    CborEncoder_writeUint32WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
}

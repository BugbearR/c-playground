#include "CborEncoder.h"

void CborEncoder_writeUint16(CborEncoder_t *pThis, uint16_t value)
{
    CborEncoder_writeUint32WithMajorType(pThis, CBOR_MAJOR_TYPE_UNSIGNED_INTEGER, value);
}

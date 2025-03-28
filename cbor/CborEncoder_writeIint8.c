#include "CborEncoder.h"

void CborEncoder_writeInt8(CborEncoder_t *pThis, int8_t value)
{
    CborEncoder_writeInt32(pThis, value);
}

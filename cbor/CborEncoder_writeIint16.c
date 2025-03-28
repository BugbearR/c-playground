#include "CborEncoder.h"

void CborEncoder_writeInt16(CborEncoder_t *pThis, int8_t value)
{
    CborEncoder_writeInt32(pThis, value);
}

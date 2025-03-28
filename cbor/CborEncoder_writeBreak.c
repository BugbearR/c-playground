#include "CborEncoder.h"

void CborEncoder_writeBreak(CborEncoder_t *pThis)
{
    pThis->outFn(CBOR_BREAK, pThis);
}

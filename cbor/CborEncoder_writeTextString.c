#include "CborEncoder.h"

void CborEncoder_writeTextString(CborEncoder_t *pThis, const unsigned char *data, size_t length)
{
    CborEncoder_writeUint64WithMajorType(pThis, CBOR_MAJOR_TYPE_TEXT_STRING, length);

    for (size_t i = 0; i < length; i++)
    {
        pThis->outFn(data[i], pThis);
    }
}

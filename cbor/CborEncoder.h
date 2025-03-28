#ifndef CBOR_ENCODER_H_
#define CBOR_ENCODER_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef CBOR_H_
#include "Cbor.h"
#endif

typedef struct CborEncoder CborEncoder_t;

struct CborEncoder
{
    void *userData;
    int (*outFn)(uint8_t octet, CborEncoder_t *encoder);
};

void CborEncoder_init(CborEncoder_t *pThis);

void CborEncoder_setOutFn(CborEncoder_t *pThis, int (*outFn)(uint8_t octet, CborEncoder_t *encoder), void *userData);

void CborEncoder_writeUint8(CborEncoder_t *pThis, uint8_t value);

void CborEncoder_writeUint16(CborEncoder_t *pThis, uint16_t value);

void CborEncoder_writeUint32(CborEncoder_t *pThis, uint32_t value);

void CborEncoder_writeUint32WithMajorType(CborEncoder_t *pThis, uint8_t majorType, uint32_t value);

void CborEncoder_writeUint64(CborEncoder_t *pThis, uint64_t value);

void CborEncoder_writeUint64WithMajorType(CborEncoder_t *pThis, uint8_t majorType, uint64_t value);

void CborEncoder_writeInfiniteLength(CborEncoder_t *pThis, uint8_t majorType);

void CborEncoder_writeInt8(CborEncoder_t *pThis, int8_t value);

void CborEncoder_writeInt16(CborEncoder_t *pThis, int16_t value);

void CborEncoder_writeInt32(CborEncoder_t *pThis, int32_t value);

void CborEncoder_writeInt64(CborEncoder_t *pThis, int64_t value);

void CborEncoder_writeFloat(CborEncoder_t *pThis, float value);

void CborEncoder_writeDouble(CborEncoder_t *pThis, double value);

void CborEncoder_writeBool(CborEncoder_t *pThis, bool value);

void CborEncoder_writeNull(CborEncoder_t *pThis);

void CborEncoder_writeUndefined(CborEncoder_t *pThis);

void CborEncoder_writeByteString(CborEncoder_t *pThis, const unsigned char *data, size_t length);

void CborEncoder_writeTextString(CborEncoder_t *pThis, const char *data, size_t length);

void CborEncoder_writeArray(CborEncoder_t *pThis, size_t length);

void CborEncoder_writeMap(CborEncoder_t *pThis, size_t length);

void CborEncoder_writeTag(CborEncoder_t *pThis, uint64_t tag);

void CborEncoder_writeSimpleValue(CborEncoder_t *pThis, uint8_t value);

void CborEncoder_writeIndefiniteLength(CborEncoder_t *pThis, uint8_t majorType);

void CborEncoder_writeBreak(CborEncoder_t *pThis);

#endif // CBOR_ENCODER_H_

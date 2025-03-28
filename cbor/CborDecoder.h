#ifndef CBOR_DECODER_H_
#define CBOR_DECODER_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct CborDecoder CborDecoder_t;

struct CborDecoder {
    int (*readInt8)(CborDecoder_t *decoder, int8_t *value);
    int (*readInt16)(CborDecoder_t *decoder, int16_t *value);
    int (*readInt32)(CborDecoder_t *decoder, int32_t *value);
    int (*readInt64)(CborDecoder_t *decoder, int64_t *value);
    int (*readUInt8)(CborDecoder_t *decoder, uint8_t *value);
    int (*readUInt16)(CborDecoder_t *decoder, uint16_t *value);
    int (*readUInt32)(CborDecoder_t *decoder, uint32_t *value);
    int (*readUInt64)(CborDecoder_t *decoder, uint64_t *value);
    int (*readFloat)(CborDecoder_t *decoder, float *value);
    int (*readDouble)(CborDecoder_t *decoder, double *value);
    int (*readBool)(CborDecoder_t *decoder, bool *value);
    int (*readString)(CborDecoder_t *decoder, char *value, size_t size);
    int (*readBytes)(CborDecoder_t *decoder, uint8_t *value, size_t size);
    int (*readArray)(CborDecoder_t *decoder, size_t *size);
};

#endif // CBOR_DECODER_H_

#if !defined Ofw_Buffer_h_
#define Ofw_Buffer_h_ 1

#pragma once

#include <stdint.h>

typedef struct Ofw_Buffer_tag
{
    int32_t length;
    uint8_t *pBuf;
} Ofw_Buffer_t;

void Ofw_Buffer_init(Ofw_Buffer_t *pThis, int32_t length, uint8_t *pBuf);

#endif /* Ofw_Buffer_h_ */

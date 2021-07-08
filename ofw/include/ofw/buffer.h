#if !defined Ofw_Buffer_h_
#define Ofw_Buffer_h_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

#ifndef Ofw_Base_h_
#include "ofw/base.h"
#endif

#ifndef Ofw_Error_h_
#include "ofw/error.h"
#endif

typedef struct Ofw_Buffer_tag
{
    int32_t length;
    uint8_t *pBuffer;
} Ofw_Buffer_t;

void Ofw_Buffer_init(Ofw_Buffer_t *pThis, int32_t length, uint8_t *pBuffer);

void Ofw_Buffer_final(Ofw_Buffer_t *pThis);

Ofw_Result_t Ofw_Buffer_realloc(Ofw_Buffer_t *pThis, int32_t length, Ofw_Error_t *pError);

#endif /* Ofw_Buffer_h_ */

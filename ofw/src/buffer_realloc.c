#include "ofw/buffer.h"

#include <errno.h>

Ofw_Result_t Ofw_Buffer_realloc(Ofw_Buffer_t *pThis, int32_t length, Ofw_Error_t *pError)
{
    Ofw_Result_t result = Ofw_Result_FAILED;
    Ofw_Error_t error = Ofw_Error_ERROR;

    if (length < 0)
    {
        error = Ofw_Error_INVALID_PARAM | Ofw_Error_PARAM2;
        goto FUNC_EXIT;
    }

    if (pThis->length < 0)
    {
        error = Ofw_Error_INVALID_OBJECT;
        goto FUNC_EXIT;
    }

    uint8_t *pNewBuffer = realloc(pThis->pBuffer, length);
    if (!pNewBuffer)
    {
        switch (errno)
        {
        case ENOMEM:
            error = Ofw_Error_OUT_OF_MEMORY;
            break;
        default:
            error = Ofw_Error_convErrno(errno);
        }
        goto FUNC_EXIT;
    }
    pThis->pBuffer = pNewBuffer;
    pThis->length = length;

    result = Ofw_Result_SUCCEEDED;

FUNC_EXIT:
    if (Ofw_Result_isFailed(result))
    {
        if (pError)
        {
            *pError = error;
        }
    }
    return Ofw_Result_FAILED;
}

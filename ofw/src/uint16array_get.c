int8_t int8Array_get(void *pBuf, int32_t byteOffset)
{
    return *((int8_t *)pBuf + byteOffset);
}

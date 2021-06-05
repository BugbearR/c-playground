typedef struct Buffer_tag
{
    int32_t length;
    uint8_t *pBuf;
    void (*finalizer)(struct Buffer_tag *pThis);
} Buffer_t;

int Buffer_initialize(Buffer_t *pThis, int32_t length, uint8_t *PBuf, void (*finalizer)(Buffer_t *pThis))
{
    pThis->length = 0;
    pThis->pBuf = NULL;
    pThis->finalizer = finalizer;
}

typedef struct DequeItem_tag
{
    DequeItem_t *pNext;
    DequeItem_t *pPrev;
    void *pValue;
} DequeItem_t;

void Deque_initialize(DequeItem_t *pThis, DequeItem_t *pNext, DequeItem_t *pPrev)
{
    pThis->pNext = NULL;
    pThis->pPrev = NULL;
    pThis->pValue = NULL;
}

typedef struct Deque_tag
{
    int32_t length;
    DequeItem_t root;
} Deque_t;

void Deque_initialize(Deque_t *pThis)
{
    pThis->length = 0;
    DequeItem_initialize(&(pThis->root), NULL, NULL, nop);
}


typedef struct OutBuffer_tag {
    int fd;
    int32_t bufLen;
    uint8_t *pBuf;
    int32_t pos;
} OutBuffer_t;

int appendBuffer(const uint8_t *pBuf, int32_t burLen) {

}

int out(void *pThis)
{
    int result = -1;
    OutBuffer_t *pThisWk = pThis;

    ssize_t reqLen = pThisWk->bufLen - pThisWk->pos;
    ssize_t resLen;
    while (1)
    {
        ssize_t resLen = send(pThisWk->fd, pThisWk->pBuf + pThisWk->pos, reqLen, 0);
        if (resLen == -1)
        {
            subErrno = errno;
            if (subErrno == EINTR || subErrno == EAGAIN)
            {
                break;
            }
            else if (subErrno == EMSGSIZE)
            {
                reqLen >>= 1
            }
            else
            {

            }
        }
        else if (resLen >= 0)
        {
            pThisWk->pos += resLen;
            result = 0;
            break;
        }
    }

    return result;
}
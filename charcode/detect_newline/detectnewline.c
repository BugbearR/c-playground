#include "detectnewline.h"

#include <stdlib.h>

static int state_init(ofw_DetectNewLine_t *pThis, int c)
{
    switch (c)
    {
    case '\r':
        pThis->state = STATE_CR;
        pThis->crCount++;
        return 1;

    case '\n':
        pThis->lfCount++;
        return 1;

    case -1:
        return 0;

    default:
        return 1;
    }
}

static int state_cr(ofw_DetectNewLine_t *pThis, int c)
{
    switch (c)
    {
    case '\r':
        pThis->crCount++;
        return 1;

    case '\n':
        pThis->crLfCount++;
        pThis->state = STATE_INIT;
        return 1;

    case -1:
        pThis->crCount++;
        pThis->state = STATE_INIT;
        return 0;

    default:
        pThis->crCount++;
        pThis->state = STATE_INIT;
        return 1;
    }
}

void ofw_DetectNewLine_init(ofw_DetectNewLine_t *pThis)
{
    ofw_DetectNewLine_clear(pThis);
}

void ofw_DetectNewLine_clear(ofw_DetectNewLine_t *pThis)
{
    *pThis = (ofw_DetectNewLine_t) {
        .state = STATE_INIT
    };
}

int ofw_DetectNewLine_transition(ofw_DetectNewLine_t *pThis, int c, ofw_Error_t *pOutError)
{
    if (c != -1)
    {
        pThis->totalCount++;
    }

    switch (pThis->state)
    {
    case STATE_INIT:
        return state_init(pThis, c);

    case STATE_CR:
        return state_cr(pThis, c);

    default:
        return -1;
    }
}

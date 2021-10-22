#include "detectNewline.h"

int state_init(Ofw_detectNewline_t *pThis, int c)
{
    switch (c)
    {
    case '\r':
        pThis->crCount++;
        return 1;

    case '\n':
        pThis->crLfCount++;
        pThis->state = INIT;
        return 1;

    case -1:
        pThis->crCount++;
        pThis->state = INIT;
        return 0;
    }
}

int state_cr(Ofw_detectNewline_t *pThis, int c)
{
    switch (c)
    {
    case '\r':
        pThis->crCount++;
        return 1;

    case '\n':
        pThis->crLfCount++;
        pThis->state = INIT;
        return 1;

    case -1:
        pThis->crCount++;
        pThis->state = INIT;
        return 0;
    }
}

int Ofw_detectNewline_transition(Ofw_detectNewline_t *pThis, int c)
{
    if (c != -1)
    {
        pThis->totalCount++;
    }

    switch (pThis->state)
    {
    case INIT:
        state_init(pThis, c);
    case CR:
        state_cr(pThis, c);
    }
}

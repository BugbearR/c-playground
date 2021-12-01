#ifndef ofw_DetectNewLine_H_
#define ofw_DetectNewLine_H_

enum ofw_DetectNewLine_state
{
    STATE_INIT,
    STATE_CR,
};

typedef struct ofw_DetectNewLine_tag
{
    enum ofw_DetectNewLine_state state;
    int totalCount;
    int crCount;
    int crLfCount;
    int lfCount;
} ofw_DetectNewLine_t;

void ofw_DetectNewLine_init(ofw_DetectNewLine_t *pThis);

void ofw_DetectNewLine_clear(ofw_DetectNewLine_t *pThis);

int ofw_DetectNewLine_transition(ofw_DetectNewLine_t *pThis, int c, ofw_Error_t *pOutError);

#endif /* ofw_DetectNewLine_H_ */

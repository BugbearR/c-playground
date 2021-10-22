#ifndef Ofw_detectNewline_H_
#define Ofw_detectNewline_H_

enum Ofw_detectNewline_state
{
    INIT,
    CR,
};

typedef struct Ofw_detectNewline_tag
{
    enum Ofw_detectNewline_state state;
    int totalCount;
    int crCount;
    int crLfCount;
    int lfCount;
} Ofw_detectNewline_t;

int Ofw_detectNewline_transition(Ofw_detectNewline_t *pThis, int c);

#endif /* Ofw_detectNewline_H_ */

#include <stdio.h>
#include <assert.h>

#define ASSERT_OK (type, what)                                  \
    if (!type##_OK (what))                                      \
    {                                                           \
        type##_Dump (what);                                     \
        printf (#type "Failed in file: '%s'" "\n"               \
                       "line: %d" "\n", __FILE__, __LINE__);    \
        if (ERROR) perror;                                      \
        abort();                                                \
    }                                                           \


void stack_constructor (stack_t*This);

void stack_constructor (stack_t*This)
{
    assert (This);

    This->count = 0;
}

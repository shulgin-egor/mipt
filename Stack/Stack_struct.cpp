#include <stdio.h>
#include <assert.h>

#define TYPE int
#define __FUNC__ __func__
//#define __FILE__ __file__
//#define __LINE__ __line__

/*#define ASSERT_OK (type, what)                                  \
    if (!type##_OK (what))                                      \
    {                                                           \
        type##_Dump (what);                                     \
        printf (#type "Failed in file: '%s'" "\n"               \
                       "line: %d" "\n", __FILE__, __LINE__);    \
        if (ERROR) perror;                                      \
        abort();                                                \
    }  */                                                         \

/*enum Commands
 {
    cmdEnd = 0,
    cmdPush = 1,
    cmdPop = 2,
    //cmdEnd = 3
 };*/

const int MAX_STACK_SIZE = 100;
const int DEFAULT_VALUE = 0;
const int POISON_VALUE = -1;
bool MY_ERROR = false;

typedef struct
{
    TYPE data[MAX_STACK_SIZE];
    TYPE* next;
    int nElements;
} stack_t;

void stack_constructor (stack_t* This);
void stack_destructor (stack_t* This);
bool stack_ok (const stack_t* This, const char function_name[]);
void stack_dump (const stack_t* This);

void stack_constructor (stack_t* This)
{
    assert (This);

    This->nElements = DEFAULT_VALUE;
    for (int i = 0; i < MAX_STACK_SIZE; i++) This->data[i] = DEFAULT_VALUE;
    This->next = &(This->data[0]);

   // ASSERT_OK (stack_t*This);
}

void stack_destructor (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;

    This->next = NULL;
    for (int i = 0; i < This->nElements; i++) This->data[i] = POISON_VALUE;
    This->nElements = POISON_VALUE;
}

bool stack_ok (const stack_t* This, const char function_name[])
{
    assert (This);
    if (This->next == NULL)
    {
        printf ("\n" "ERROR in (%s) : Stack is spoiled. "
                                    "This->next = NULL" "\n", function_name);
        MY_ERROR = true;
        return 0;
    }
    if (This->nElements < 0)
    {
        printf ("\n" "ERROR in (%s) : Stack is spoiled. "
                                    "This->nElements = %d < 0" "\n", function_name, This->nElements);
        MY_ERROR = true;
        return 0;
    }
    else if (This->nElements < 0)
         {
            printf ("\n" "ERROR in (%s) : Stack is spoiled. "
                                        "This->nElements = %d > %d (MAX_STACK_SIZE)" "\n",
                                         function_name, This->nElements, MAX_STACK_SIZE);
            MY_ERROR = true;
            return 0;
        }

    return 1;
}

void stack_dump (const stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;

    printf ("\n---------------STACK_DUMP---------------\n");
    printf (" Size = %d" "\n", This->nElements);
    printf (" Next = %d" "\n", (*This->next));
    printf ("Stack data:" "\n");
    for (int i = 0; i < This->nElements; i++)
        printf (" [%d]  %d" "\n", i, This->data[i]);
    for (int i = This->nElements; i < MAX_STACK_SIZE; i++)
        printf (" [%d] * %d" "\n", i, This->data[i]);
    printf ("---------------STACK_DUMP---------------\n\n");
}

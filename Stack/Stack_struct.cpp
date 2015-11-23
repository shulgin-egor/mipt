#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>

#define STACK_TYPE double
#define __FUNC__ __func__
//#define __FILE__ __file__
//#define __LINE__ __line__
/*
#define ASSERT_OK (STACK_TYPE, what)                                  \
    if (!STACK_TYPE##_OK (what))                                      \
    {                                                                 \
        type##_dump (what);                                           \
        printf (#STACK_TYPE "Failed in file: '%s'" "\n"               \
                       "line: %d" "\n", __FILE__, __LINE__);          \
        if (ERROR) perror;                                            \
        abort();                                                      \
    }                                                                 \
*/

/*enum Commands
 {
    cmdEnd = 0,
    cmdPush = 1,
    cmdPop = 2,
    //cmdEnd = 3
 };*/

const int MAX_STACK_SIZE = 10;
const int DEFAULT_VALUE = 0;
const int POISON_VALUE = -1;
bool MY_ERROR = false;

typedef struct
{
    STACK_TYPE data[MAX_STACK_SIZE];
    STACK_TYPE* next;
    int nElements;
} stack_t;

void stack_constructor (stack_t* This);
void stack_destructor (stack_t* This);
bool stack_ok (const stack_t* This, const char* function_name);
void stack_dump (const stack_t* This);

void stack_end (stack_t* This);
void stack_out (stack_t* This);

void stack_push (stack_t* This, const STACK_TYPE value);
STACK_TYPE stack_pop (stack_t* This);

STACK_TYPE stack_add (stack_t* This);
STACK_TYPE stack_sub (stack_t* This);
STACK_TYPE stack_mul (stack_t* This);
STACK_TYPE stack_div (stack_t* This);


void stack_constructor (stack_t* This)
{
    assert (This);

    This->nElements = 0;
    for (int i = 0; i < MAX_STACK_SIZE; i++) This->data[i] = DEFAULT_VALUE;
    This->next = &(This->data[0]);

    //ASSERT_OK (This);
}

void stack_destructor (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;

    This->next = NULL;
    for (int i = 0; i < This->nElements; i++) This->data[i] = POISON_VALUE;
    This->nElements = POISON_VALUE;
}

bool stack_ok (const stack_t* This, const char* function_name)
{
    assert (This);
    bool flag = false;
    if (This->next == NULL)
    {
        printf ("\n" "ERROR in (%s) : Stack is spoiled: "
                                    "This->next = NULL" "\n", function_name);
        flag = true;
    }
    if (This->nElements < 0)
    {
        printf ("\n" "ERROR in (%s) : Stack is spoiled. "
                                    "This->nElements = %d < 0" "\n", function_name, This->nElements);
        flag = true;
    }
    else if (This->nElements > MAX_STACK_SIZE)
         {
            printf ("\n" "ERROR in (%s) : Stack is spoiled. "
                                        "This->nElements = %d > %d (MAX_STACK_SIZE)" "\n",
                                         function_name, This->nElements, MAX_STACK_SIZE);
            flag = true;
        }

    if (flag == true)
    {
        MY_ERROR = true;
        //stack_dump (This);
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
    printf (" Next = %lg" "\n", (*This->next));
    printf ("Stack data:" "\n");
    for (int i = 0; i < This->nElements; i++)
        printf (" [%d]  %lg" "\n", i, This->data[i]);
    for (int i = This->nElements; i < MAX_STACK_SIZE; i++)
        printf (" [%d] * %lg" "\n", i, This->data[i]);
    printf ("---------------STACK_DUMP---------------\n\n");
}


void stack_end (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;
    stack_destructor (This);
    printf ("\n" "End of the program" "\n");
}

void stack_out (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;
    printf ("\n" "STACK_OUT" "\n");
    stack_dump (This);
}

void stack_push (stack_t* This, const STACK_TYPE value)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;

    if (This->nElements == MAX_STACK_SIZE)
    {
        printf ("\n" "ERROR in (%s): STACK OVERFLOW" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return;
    }

    This->data[This->nElements] = value;
    This->next = &(This->data[This->nElements]);
    This->nElements++;

    if (!stack_ok (This, __FUNC__)) return;
}

STACK_TYPE stack_pop (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;

    if (This->nElements == 0)
    {
        printf ("\n" "ERROR in (%s): Nothing to pop" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }

    This->nElements--;

    //This->next = (This->nElements) ? (&This->data[This->nElements]) : (&This->data[This->nElements - 1]);
    if (This->nElements == 0)
        This->next = (&This->data[This->nElements]);
    else
        This->next = (&This->data[This->nElements - 1]);

    if (!stack_ok (This, __FUNC__)) return MY_ERROR;
    else return (*This->next);
}

STACK_TYPE stack_add (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;

    if (This->nElements < 2)
    {
        printf ("\n" "ERROR in (%s): Not enough elements to ADD" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }

    stack_pop (This);
    //This->nElements--;
    int nElem = This->nElements;
    This->data[nElem - 1] = This->data[nElem - 1] + This->data[nElem];
    //This->next = (&This->data[This->nElem - 1]);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;
    else return (*This->next);
}

STACK_TYPE stack_sub (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;

    if (This->nElements < 2)
    {
        printf ("\n" "ERROR in (%s): Not enough elements to SUB" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }

    stack_pop (This);
    int nElem = This->nElements;
    This->data[nElem - 1] = This->data[nElem - 1] - This->data[nElem];

    if (!stack_ok (This, __FUNC__)) return MY_ERROR;
    else return (*This->next);
}

STACK_TYPE stack_mul (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;

    if (This->nElements < 2)
    {
        printf ("\n" "ERROR in (%s): Not enough elements to MUL" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }

    stack_pop (This);
    int nElem = This->nElements;
    This->data[nElem - 1] = This->data[nElem - 1] * This->data[nElem];

    if (!stack_ok (This, __FUNC__)) return MY_ERROR;
    else return (*This->next);
}

STACK_TYPE stack_div (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return MY_ERROR;

    if (This->nElements < 2)
    {
        printf ("\n" "ERROR in (%s): Not enough elements to DIV" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }
    if ( fabs(This->data[This->nElements - 1]) < DBL_EPSILON)
    {
        printf ("\n" "ERROR in (%s): DIVISION BY ZERO: divisor = %lg" "\n", __FUNC__, This->data[This->nElements]);
        MY_ERROR = true;
        stack_dump (This);
        return MY_ERROR;
    }

    stack_pop (This);
    int nElem = This->nElements;
    This->data[nElem - 1] = (STACK_TYPE)(This->data[nElem - 1] / This->data[nElem]);

    if (!stack_ok (This, __FUNC__)) return MY_ERROR;
    else return (*This->next);
}

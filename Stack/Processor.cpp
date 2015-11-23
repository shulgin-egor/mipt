//#include "Stack_struct.cpp"
#include "Stack_struct.cpp"


typedef struct
{
    stack_t stack;
    STACK_TYPE ax, bx, cx, dx, ex;
} cpu_t;

void cpu_constructor (cpu_t* This);
void cpu_destructor (cpu_t* This);
bool cpu_ok (const cpu_t* This, const char function_name[]);
void cpu_dump (const cpu_t* This);

void cpu_push (cpu_t* This, const char register_name/*, const STACK_TYPE value*/);
STACK_TYPE cpu_pop (cpu_t* This, const char register_name);

/*int main()
{
    cpu_t This;
    cpu_constructor (&This);
    return 0;
} */


void cpu_constructor (cpu_t* This)
{
    assert (This);
    stack_constructor (&(This->stack));
    This->ax = This->bx = This->cx = This->dx = This->ex = DEFAULT_VALUE;
}

void cpu_destructor (cpu_t* This)
{
    assert (This);
    if (!cpu_ok (This, __FUNC__)) return;

    stack_destructor (&(This->stack));
    //This->stack = NULL;
    This->ax = This->bx = This->cx = This->dx = This->ex = POISON_VALUE;
}

bool cpu_ok (const cpu_t* This, const char* function_name)
{
    assert (This);
    bool flag = false;
    /*////if (This->stack == NULL)
    {
        printf ("\n" "ERROR in (%s) : CPU is spoiled: "
                                    "This->stack = NULL" "\n", function_name);
        MY_ERROR = true;
        //cpu_dump (This);
        flag = true;
    }  ////*/
    if (!stack_ok (&(This->stack), function_name)) flag = true;

    return (!flag);
}

void cpu_dump (const cpu_t* This)
{
    assert (This);
    if (!cpu_ok (This, __FUNC__)) return;

    printf ("\n" "Registers: ax = %lg, bx = %lg, cx = %lg, dx = %lg, ex = %lg",
            This->ax, This->bx, This->cx, This->dx, This->ex);
    stack_dump (&(This->stack));
}

void cpu_push (cpu_t* This, const char register_name/*, const STACK_TYPE value*/)
{
    assert (This);
    if (!cpu_ok (This, __FUNC__)) return;

    switch (register_name)
    {
        case ('a'):
            stack_push (&(This->stack), This->ax);
            //This->ax = value;
            break;
        case ('b'):
            stack_push (&(This->stack), This->bx);
            //This->bx = value;
            break;
        case ('c'):
            stack_push (&(This->stack), This->cx);
            //This->cx = value;
            break;
        case ('d'):
            stack_push (&(This->stack), This->dx);
            //This->dx = value;
            break;
        default:
            printf ("\n" "ERROR in (%s): There is no such register: '%c'" "\n", __FUNC__, register_name);
            MY_ERROR = true;
    }
}

STACK_TYPE cpu_pop (cpu_t* This, const char register_name)
{
    assert (This);
    if (!cpu_ok (This, __FUNC__)) return MY_ERROR;

    switch (register_name)
    {
        case ('a'):
            This->ax = stack_pop(&(This->stack));
            return This->ax;
            break;
        case ('b'):
            This->bx = stack_pop(&(This->stack));
            return This->bx;
            break;
        case ('c'):
            This->cx = stack_pop(&(This->stack));
            return This->cx;
            break;
        case ('d'):
            This->dx = stack_pop(&(This->stack));
            return This->dx;
            break;
        default:
            printf ("\n" "ERROR in (%s): There is no such register: '%c'" "\n", __FUNC__, register_name);
            MY_ERROR = true;
            return MY_ERROR;
    }
}

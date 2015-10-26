#include "Stack_struct.cpp"
#include "Commands.cpp"

void stack_end ();
void stack_push (stack_t* This, const int numb);
void stack_pop (stack_t* This);
void stack_add ();

int main ()
{
    printf ("# Program by Shulgin E." "\n\n");

    stack_t This;
    stack_constructor (&This);

    stack_push (&This, 1);
    //stack_dump (&This);
    //stack_push (&This, 1);
    //stack_pop (&This);
    stack_dump (&This);

    stack_destructor (&This);
    //stack_dump (&This);

    return 0;
}

void stack_push (stack_t* This, const TYPE numb)
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

    This->nElements++;
    This->data[This->nElements] = numb;
    This->next = &(This->data[This->nElements]);
}

void stack_pop (stack_t* This)
{
    assert (This);
    if (!stack_ok (This, __FUNC__)) return;

     if (This->nElements == 0)
     {
        printf ("\n" "ERROR in (%s): Nothing to pop" "\n", __FUNC__);
        MY_ERROR = true;
        stack_dump (This);
        return;
     }

     //This->next--;
     This->nElements--;
     (*This->next) = DEFAULT_VALUE;
     //This->next = ;
}

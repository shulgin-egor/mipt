#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <errno.h>

/***************************************************************************************************/

#define ASSERT_OK(type, what)                                         \
    if (!type##_ok (what))                                            \
    {                                                                 \
        printf ("Failed in file: '%s'" "\n"                           \
                "line: %d" "\n", __FILE__, __LINE__);                 \
        type##_dump (what);                                           \
        abort();                                                      \
    }

#define __FUNC__ __func__
#define LIST_TYPE char

/***************************************************************************************************/

//const char* DEFAULT_VALUE = "*";
//const char* POISON_VALUE = "poison";

bool MY_ERROR = false;

/***************************************************************************************************/

typedef struct list_t
{
    LIST_TYPE* data;
    list_t* next;
    list_t* prev;
} list_t;

typedef struct head_t
{
    list_t* head_elem;
    int nElements;
} head_t;

/***************************************************************************************************/

list_t* elem_constructor(LIST_TYPE* data);
void elem_destructor (list_t* This);

head_t* head_constructor();
void head_destructor (head_t* This);

bool list_ok (const head_t* This);
void list_dump (const head_t* This);

void list_insert (head_t* This, list_t* prev_elem, list_t* new_elem);
void list_delete (head_t* This, list_t* elem);

/***************************************************************************************************/

/*int main()
{
    head_t* head = head_constructor();

    list_t* elem = elem_constructor ("Egor");
    list_t* elem1 = elem_constructor ("Egor1");
    //printf("<%s>", elem->data);

    list_insert (head, head->head_elem, elem);
    list_insert (head, elem, elem1);

    list_dump (head);

    list_delete (head, elem);
    list_dump (head);

    head_destructor (head);
    return 1;
}*/

/***************************************************************************************************/

head_t* head_constructor()
{

    head_t* This = (head_t*) calloc (1, sizeof(head_t));

    This->head_elem = elem_constructor ("Head elem");

    This->head_elem->next = This->head_elem->prev = This->head_elem;

    This->nElements = 0;


    return This;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void head_destructor (head_t* This)
{
    //assert (This);
    ASSERT_OK(list, This);

    list_t* temp = This->head_elem->next;
    for (int i = 1; i <= This->nElements; i++)
    {
        This->head_elem->next = temp->next;
        elem_destructor (temp);
        temp = This->head_elem->next;
    }

    This->nElements = -1;
    elem_destructor (This->head_elem);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
list_t* elem_constructor (LIST_TYPE* data)
{
    if (data == NULL)
    {
        printf ("ERROR in (%s): data = NULL" "\n", __FUNC__);
        return NULL;
    }

    list_t* This = (list_t*) calloc (1, sizeof(list_t));

    This->data = (LIST_TYPE*) calloc (strlen (data), sizeof (This->data));

    This->data = data;

    This->next = NULL;
    This->prev = NULL;

    return This;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void elem_destructor (list_t* This)
{
    assert (This);

    free (This->data);
    This->data = NULL;

    This->next = NULL;
    This->prev = NULL;

    free (This);
    This = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool list_ok (const head_t* This)
{
    return (This && This->nElements >= 0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void list_dump (const head_t* This)
{
    if (This == NULL)
    {
        printf ("\n" "ERROR in (%s): This = NULL" "\n", __FUNC__);
        MY_ERROR = true;
        return;
    }

    if (This->nElements < 0)
    {
        printf ("\n" "ERROR in (%s): This->Elements = %d < 0" "\n", __FUNC__, This->nElements);
        MY_ERROR = true;
        return;
    }

    printf ("\n" "---------------------- LIST DUMP START ----------------------" "\n\n");

    printf (" Number of elements = %d" "\n\n", This->nElements);
    printf (" List_head->next = %p" "\n", This->head_elem->next);
    printf (" List_head->prev = %p" "\n\n", This->head_elem->prev);

    list_t* temp = This->head_elem;

    for (int i = 0; i <= This->nElements; i++)
    {
        printf(" [%d] data = <%s>" "\n", i, temp->data);

        printf("      elem adr = %p" "\n", temp);
        printf("      NEXT adr = %p" "\n", temp->next);
        printf("      PREV adr = %p" "\n\n", temp->prev);

        temp = temp->next;
    }
    printf ("---------------------- LIST DUMP END ----------------------" "\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void list_insert (head_t* This, list_t* prev_elem, list_t* new_elem)
{
    ASSERT_OK(list, This);

    new_elem->next = prev_elem->next;
    new_elem->prev = prev_elem;

    prev_elem->next->prev = new_elem;
    prev_elem->next = new_elem;

    This->nElements++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void list_delete (head_t* This, list_t* elem)
{
    ASSERT_OK(list, This);

    list_t* temp = elem;

    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;

    elem_destructor (temp);

    This->nElements--;
}

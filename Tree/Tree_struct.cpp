//#ifndef printf
//#include <stdio.h>
//#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dotter_.h"

#define ASSERT_OK(type, what)                                         \
    if (!type##_ok (what))                                            \
    {                                                                 \
        printf ("ASSERT_OK: Failed in file: '%s'" "\n"                \
                "line: %d" "\n", __FILE__, __LINE__);                 \
        type##_Dump (what);                                           \
        abort();                                                      \
    }

#define PTR_ERROR NULL
#define INT_ERROR -1
#define BOOL_ERROR 0
#define OK 1
#define __FUNC__ __func__

#define L This->children[0]
#define R This->children[1]
#define ParentL This->parent->children[0]
#define ParentR This->parent->children[1]
//#define operator oper
//#define P This->parent


enum Node_types
{
    NUM = 0,
    VAR = 1,
    OP = 2,
}

/*enum Node_operators
{
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
    EQUAL = 4,
}*/

/*
typedef struct list_t
{
    char* data;
    list_t* next;
    list_t* prev;
} list_t;
*/

typedef struct node_t
{
    int type;
    char* data;
    node_t* parent;
    node_t* children[2];
} node_t;
//typedef node_t;


node_t* Node_Constructor (const int type, const char* data, node_t* left, node_t* right);
bool Node_Destructor (node_t* This);
bool Node_Dump (const node_t* This);
bool Node_ok (const node_t* This);


node_t* Node_Constructor (const int type, char* data, node_t* left, node_t* right)
{
    if (type < 0 || type > 2)
    {
        printf ("ERROR in (%s): Can not construct Node with type = %d != {0,1,2}", __FUNC__, type);
        return PTR_ERROR;
    }
    if (data == NULL)
    {
        printf ("ERROR in (%s): Can not construct Node with data = NULL ", __FUNC__);
        return PTR_ERROR;
    }

    node_t* This = (node_t*) calloc (sizeof(node_t*));
    L = left;
    R = right;
    This->data = data;
    This->type = type;

    return This;
}

bool Node_Destructor (node_t* This)
{
    assert(This);
    ASSERT_OK(Node, This);
    //if (! Node_ok (This)) return BOOL_ERROR;

    This->parent = NULL;
    This->type = -1;
    This->data = NULL;

    if (L != NULL) Node_Destructor (L);
    if (R != NULL) Node_Destructor (R);

    return OK;
}

bool Node_ok (const node_t* This)
{
    assert(This);

    if (This->parent != NULL)
        if (ParentL != This && ParentR != This || ParentL == ParentR)
            return BOOL_ERROR;

    if (This->type < 0 || This->type > 2 || This->data == NULL) return BOOL_ERROR;

    if (L != NULL) Node_ok (L);
    if (R != NULL) Node_ok (R);

    return OK;
}

bool Node_Dump (const node_t* This)
{
    assert(This);

    if (This->data == NULL)
    {
        printf ("ERROR in (%s): Tree is spoiled" "\n"
                "               Node->data = NULL", __FUNC__);
        return BOOL_ERROR;
    }

    dtBegin ("Tree_Dump.dot");
    dtNodeStyle ().shape ("box")              //По умолчанию форма - коробка.
                  .style ("rounded, filled");
    char Title [30] = "";
    int i = 0;

    switch (This->type)
    {
        case(NUM):
            dtNodeStyle ().fontcolor ("darkgreen") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .color     ("darkgreen") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#98FF66");  //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
            sprintf (Title, "#%d\n%s", i, This->data);
            break;
        case(VAR):
            break;
        case(OP):
            dtNodeStyle ().fontcolor ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .color     ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#FFCCC9"); //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
            break;
        default:
            printf ("ERROR in (%s): Tree is spoiled" "\n"
                    "               Node->type = %d != {0,1,2}", __FUNC__, This->type);
            return BOOL_ERROR;
    }

    return OK;
}

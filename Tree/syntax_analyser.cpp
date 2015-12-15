#include <stdio.h>
#include <assert.h>

#define __FUNC__ __func__

typedef long long int type;


type GetN();
type GetE();
type GetT();
type GetP();
type GetG (char* str);

char* s;

int main()
{
    char* p = "1*19+(5+2*(3+2))*2";
    //if (p[7] == '\0') printf ("Last symbol = \0");
    printf ("\n %d \n", GetG(p));
    return 1;
}

type GetN()
{
    printf("in GetN *s = %c\n", *s);
    type val = 0;

    while ('0' <= *s && *s <= '9')
    {
        //printf("in while\n");
        val = val * 10 + *s - '0';
        s++;
        //printf("%d", val);
    }
    return val;
}

type GetE()
{
    printf("in GetE *s = %c\n", *s);
    type val = GetT();

    while (*s == '-' || *s == '+')
    {
        int op = *s++;
        //val = *s - '0';
        //s++;
        type val2 = GetT();
        if (op == '+') val += val2;
        if (op == '-') val -= val2;
    }
    return val;
}

type GetT()
{
    printf("in GetT *s = %c\n", *s);

    type val = GetP();

    while (*s == '*' || *s == '/')
    {
        int op = *s++;
        //val = *s - '0';
        //s++;
        type val2 = GetP();
        if (op == '*') val *= val2;
        if (op == '/') val /= val2;
    }
    return val;
}

type GetP()
{
    printf("in GetP *s = %c\n", *s);

    if (*s == '(')
    {
        s++;
        type val = GetE();
        if (*s != ')') printf ("Syntax error in (%s): s = '%c'", __FUNC__, *s);
        //assert (*s = ')');
        s++;
        return val;
    }
    else
        return GetN();
}

type GetG (char* str)
{
    s = str;
    type val = GetE();
    //assert (*s == '\0');
    if  (*s != '\0') printf("syntax error. last symbol = '%c'", *s);
    printf ("\n %d \n", val);
    return val;
}

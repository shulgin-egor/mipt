#include <stdio.h>

//#define SUCCESSFUL_INPUT 1
//#define UNSUCCESSFUL_INPUT -1

//int Input3Int (int *numb_1, int *numb_2, int *numb_3);
int ReadIntInput (const char name[]);
int GCD (int a, int b);
int LCM (int a, int b);

int main()
{
    int numb_1, numb_2, numb_3;
    printf ("# Problem A3 by E.Shulgin \n");

    numb_1 = ReadIntInput ("number 1");
    numb_2 = ReadIntInput ("number 2");
    numb_3 = ReadIntInput ("number 3");

    printf("The least common multiple %d", LCM (numb_1, LCM (numb_2, numb_3)));

    return 0;
    /*
    while (1)
    {
        int Input3Int_check = 0;
        Input3Int_check = Input3Int (&numb_1, &numb_2, &numb_3);
        if (Input3Int_check == SUCCESSFUL_INPUT) break;
    }
    printf ("%d %d %d \n", numb_1, numb_2, numb_3);
    */
}

int ReadIntInput (const char name[])
{
    printf ("Input %s > ", name);
    double val = 0;
    scanf ("%lg", &val);
    return val;
}

// The Greatest Common Divisor
int GCD (int a, int b)
{
   if (b == 0) return a;
   return GCD (b, a % b);
}

// The Least Common Multiple
int LCM (int a, int b)
{
    return (a*b / GCD(a,b));
}



/*int Input3Int (int *numb_1, int *numb_2, int *numb_3)
{
    printf ("# Enter 3 numbers for NOK \n");
    printf ("# Format: numb_1 numb_2 numb_3 \n");
    int scanf_check = 0;
    int numb1 = 0, numb2 = 0, numb3 = 0;
    scanf_check = scanf ("%d %d %d", &numb1, &numb_2, &numb_3);
    *numb_1 = numb1; *numb_2 = numb2; *numb_3 = numb3;
    printf("\n");

    if (scanf_check == 3) return SUCCESSFUL_INPUT;
    else return UNSUCCESSFUL_INPUT;
}
*/

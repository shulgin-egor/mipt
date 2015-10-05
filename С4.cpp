#include <stdio.h>
#define INVALID_INPUT -1

unsigned long long int AmountOfExpansions (int n, int current_numb);
unsigned int ReadIntInput (const char name[]);

int main()
{
    printf ("# Problem D6 by E.Shulgin \n\n");

    unsigned int n = 0;
    n = ReadIntInput ("");
    if (n == INVALID_INPUT) return 0;
    else printf ("%d \n", AmountOfExpansions (n,n));

    return 0;
}

// The amount of number expansions into sums
unsigned long long int AmountOfExpansions (int n, int current_numb)
{
    if (n == 0) return 1;
    else
        if (n < 0 || current_numb < 1) return 0;
        else return AmountOfExpansions (n - current_numb, current_numb) + AmountOfExpansions (n, current_numb-1);

}

unsigned int ReadIntInput (const char name[])
    {
        printf ("Input number \nFor calculating the quantity of it expansions into sums %s> ",name);
        int val = 0;
        int scanf_check = 0;
        while (1)
        {
            scanf_check = scanf ("%d", &val);
            if (scanf_check == 1) break;
            else
            {
                printf ("Invalid input, pls restart the program \n");
                return INVALID_INPUT;
            }
        }
        return val;
    }

#include <stdio.h>
#include <math.h>

long long int SumOfDivisors (long long int n, long long int d);
long long int ReadIntInput (const char name[]);

int main()
{
    printf ("# Problem B5 by E.Shulgin \n");

    long long int n = 0;
    n = ReadIntInput("");
    printf ("Sum of divisors: %d", SumOfDivisors (n, 1) );

    return 0;
}


long long int SumOfDivisors (long long int n, long long int d = 1)
{
    if (d <= n)
    {
        if (n % d == 0)
            return d + SumOfDivisors (n, d + 1);
        else
            return SumOfDivisors (n, d + 1);
    }
    else return 0;
}

long long int ReadIntInput (const char name[])
    {
        printf ("Input number %s> ",name);
        long long int val = 0;
        scanf ("%d", &val);
        return val;
    }

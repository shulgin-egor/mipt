#include <stdio.h>
#include <math.h>

const double DBL_EPSILON = 0.000001;
const int INFINITE_ROOTS = -1;

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2);
double Input(const char name[]);
int Output(int nRoots, double x1, double x2);

int main()
    {
        printf("#--- SolveSquare v.1 by E.Shulgin \n");

        printf("# Enter a,b,c for ax^2+bx+c=0>\n");
        double a = 1, b = 2, c = 1;
        a = Input("a"); b = Input("b"); c = Input("c");
        double x1 = 0, x2 = 0;
        int nRoots = 0;

        nRoots=SolveSquare(a, b, c, &x1, &x2);
        printf("nRoots = %d \n", nRoots);
        Output( nRoots, x1, x2);
        return 0;
    }

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2)
    {
        if (fabs(a) > DBL_EPSILON)
        {
            double d = 0;
            d = b*b - 4*a*c;
            if (d < 0)
            {
                return 0;
            }
            else
            {
                if (fabs(d) < DBL_EPSILON)
                {
                    *x1 = -b / (2*a);
                    return 1;
                }
                else
                {
                    *x1 = (-b + sqrt(d)) / (2*a);
                    *x2 = (-b - sqrt(d)) / (2*a);
                    return 2;
                }
            }
        }
        else
        {
            if (fabs(b) > DBL_EPSILON)
            {
                *x1 = - c / b;
                return 1;
            }
            else
            {
                if (fabs(c) > DBL_EPSILON)
                {
                    return 0;
                }
                else
                {
                    return INFINITE_ROOTS;
                }
            }
        }
    }

double Input(const char name[])
    {
        printf("Input %s>",name);
        double val = 0;
        scanf("%lg", &val);
        return val;
    }

int Output(int nRoots, double x1, double x2)
    {
        if (nRoots == INFINITE_ROOTS)
        {
            printf("Any real number");
        }
        else
        {
            if (nRoots == 0)
            {
                printf("No roots");
            }
            else
            {
                if (nRoots == 1)
                {
                    printf("x = %lg\n", x1);
                }
                else
                {
                    printf("x1 = %lg\n", x1);
                    printf("x2 = %lg\n", x2);
                }
            }
        }
    }

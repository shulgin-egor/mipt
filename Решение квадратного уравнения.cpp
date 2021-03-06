#include <stdio.h>
#include <math.h>

const INFINITE_ROOTS = -1;

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2);
double Input(const char name[]);

int main()
    {
        prinf("#--- SolveSquare v.1 by E.Shulgin \n");

        prinf("# Enter a,b,c for ax^2+bx+c=0:");
        double a = 0, b = 0, c = 0;
        double a = Input("a"), b = Input("b"), c = Input("c");
        double x1 = 0, x2 = 0;

        //int nRoots=SolveSquare(a, b, c, &x1, &x2);
        return 0;
    }

int SolveSquare (double a, double b, double c,
                 double* x1, double* x2)
    {
        if (fabs(a) > DBL_EPSILON)
        {
            //double d = 0;
            double d = b*b - 4*a*c;
            if (d < 0)
            {
                return 0;
            }
            else
            {
                if (d = 0)
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
                        return INFINITE_ROOTS;
                }
                else
                {
                    return 0;
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

#include <stdio.h>
#include <math.h>
#include <float.h>

#define INVALID_INPUT -1

const int INFINITE_ROOTS = -1;

int Solve_QuadraticEquation (double coef_a, double coef_b, double coef_c,
                             double* root_1, double* root_2);
double ReadDoubleInput (const char name[]);
void Output (int nRoots, double root_1, double root_2);

int main()
    {
        printf ("#--- SolveSquare v.2 by E.Shulgin \n");

        printf ("# Enter coefficients a, b, c for ax^2+bx+c=0>\n");
        double coef_a = 0, coef_b = 0, coef_c = 0;
        coef_a = ReadDoubleInput("a"); coef_b = ReadDoubleInput("b"); coef_c = ReadDoubleInput("c");
        if (coef_a != INVALID_INPUT && coef_b != INVALID_INPUT && coef_c != INVALID_INPUT){
            printf ("\n");
            double root_1 = 0, root_2 = 0;
            int nRoots = 0;

            nRoots = Solve_QuadraticEquation (coef_a, coef_b, coef_c, &root_1, &root_2);
            //printf("nRoots = %d \n", nRoots);
            Output (nRoots, root_1, root_2);
            return 0;
        }
        else return 0;
    }


int Solve_QuadraticEquation (double coef_a, double coef_b, double coef_c,
                             double* root_1, double* root_2)
    {
        if (fabs(coef_a) > DBL_EPSILON)
        {
            double d = 0;
            d = coef_b*coef_b - 4*coef_a*coef_c;
            if (d < 0) return 0;
            else if (fabs(d) < DBL_EPSILON)
                {
                    *root_1 = -coef_b / (2*coef_a);
                    return 1;
                }
                else
                {
                    *root_1 = (-coef_b + sqrt(d)) / (2*coef_a);
                    *root_2 = (-coef_b - sqrt(d)) / (2*coef_a);
                    return 2;
                }
        }
        else if (fabs(coef_b) > DBL_EPSILON)
            {
                *root_1 = - coef_c / coef_b;
                return 1;
            }
            else if (fabs(coef_c) > DBL_EPSILON) return 0;
                else return INFINITE_ROOTS;
    }

double ReadDoubleInput (const char name[])
    {
        printf ("Input %s > ",name);
        double val = 0;
        int scanf_check = 0;
        while (1)
        {
            scanf_check = scanf ("%lg", &val);
            if (scanf_check == 1) break;
            else
            {
                printf ("Invalid input, pls restart the program \n");
                return INVALID_INPUT;
            }
        }
        return val;
    }

void Output (int nRoots, double root_1, double root_2)
    {
        if (nRoots == INFINITE_ROOTS)
            printf("Any real number");
        else if (nRoots == 0)
            printf("No roots");
        else if (nRoots == 1)
            printf("x = %lg\n", root_1);
        else
        {
            printf("x1 = %lg\n", root_1);
            printf("x2 = %lg\n", root_2);
        }
    }


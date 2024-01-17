#include<stdio.h>

int factorialUsingRecursion(int n);
int (*fUR)(int);
int fpAsArg(int (*fp)(int));

void main()
{
    fUR = &factorialUsingRecursion;
    printf("\n%d", fpAsArg(fUR));

}

int factorialUsingRecursion(int n)
{
    if (n == 0)
        return 1;

    // recursion call
    return n * factorialUsingRecursion(n - 1);
}

int fpAsArg(int (*fp)(int))
{
    return (*fp)(6);
}


/// I'm lost. Understanding nothing. Need to sleep.
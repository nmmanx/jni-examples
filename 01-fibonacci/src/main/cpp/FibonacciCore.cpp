#include "FibonacciCore.h"

int fibo_recursion(int n)
{
    if (n <= 1) {
        return n;
    }

    return fibo_recursion(n-1) + fibo_recursion(n-2);
}

int fibo_dynamic(int n)
{
    int i;
    int f[n + 2];
 
    f[0] = 0;
    f[1] = 1;
 
    for(i = 2; i <= n; i++) {
       f[i] = f[i - 1] + f[i - 2];
    }
    
    return f[n];
}
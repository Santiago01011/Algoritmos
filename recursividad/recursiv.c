//factorial
#include <stdio.h>
#include <stdlib.h>

int factorial(int n);
int fibonacci(int n);
void espejar(int n);

int main(){
    int n = 7;
    printf("Factorial de %d es %d\n", n, factorial(n));
    n = 4;
    for(int i = 0; i < n; i++)
        printf("%d ", fibonacci(i));
    puts("");
    espejar(1234);
    puts("");//💀

    return 0;
}

int factorial(int n){
    if(n<=1)
        return 1;
    return n*factorial(n-1);   
}

int fibonacci(int n){
    if(n<=1)
        return n;
    return fibonacci(n - 1) + fibonacci(n-2);
}

void reves(int n){
    if (n == 0)
        return;
    printf("%d", n % 10);
    reves(n / 10);
}

void derecho(int n){
    if (n == 0)
        return;
    derecho(n / 10);
    printf("%d", n % 10);
}

void espejar(int n){
    derecho(n);
    reves(n);
}
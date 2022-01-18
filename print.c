#include <stdio.h>
#include <stdlib.h>

void print(int n);

int main(void) {
    int num = 5;

    print(num);
    printf("\n");
}

void print(int n) {
    if (n < 0)
        return;
    
    print(n-1);
    printf("%d ", n);
}
#include <stdio.h>

void tailRecursion(int n, int acc) {
    if(n==0) {
        printf("Result: %d\n", acc);
    }

    tailRecursion(n-1, acc + n);
}

void headRecursion(int n) {
    if(n==0) {
        return;
    }

    headRecursion(n -1);
    printf("Count: %d\n", n);
}

int main() {
    int n = 5;

    tailRecursion(n, 0);
    headRecursion(n);

    return 0;
}

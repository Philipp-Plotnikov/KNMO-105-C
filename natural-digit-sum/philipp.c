#include <stdio.h>

int foo(int n)
{
    int result = 0;
    while (n != 0) {
        result += n % 10;
        n /= 10;
    }
    return result;
}

int main()
{
    int n = 12;
    printf("%d", foo(n));
    return 0;
}
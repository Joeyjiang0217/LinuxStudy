#include <stdio.h>

struct A
{
    int a;
    double b;
    int c;
};


int main()
{
    printf("%d\n", sizeof(struct A));

    return 0;
}


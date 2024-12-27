#include "mymath.h"
#include "mylog.h"
#include "myprint.h"

int main()
{
    extern int myerrno;
    int x = 10;
    int y = 2;
    printf("%d\n", add(x, y));
    printf("%d\n", sub(x, y));
    printf("%d\n", mul(x, y));
    printf("%d\n", div(x, y));
    int n = div(10, 0);
    printf("errno: %d, 10 / 0 = %d\n", myerrno, div(10, 0));

    Print();
    Log("hello log function");  
    return 0;
}

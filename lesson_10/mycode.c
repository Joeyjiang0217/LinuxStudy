#include<stdio.h>

int addToTop(int top)
{
    int res = 0;
    int i = 1;
    for(; i <= top; i++)
    {
        res += i;
    }
    return res;
}



int main()
{
    printf("debug begin\n");
    
    int top = 100;
    int sum = addToTop(top);

    printf("sum: %d\n", sum);


    printf("debug end\n");
    return 0;
}

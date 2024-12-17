#include <stdio.h>
#include <unistd.h>

int main()
{
    fopen("log.txt", "w");
    while(1)
    {
        printf("I am a process.\n");
        sleep(1);
    }
    return 0;
}

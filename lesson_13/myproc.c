#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    while(1)
    {
        printf("I am a process. pid: %d\n", getpid());
        sleep(1);
    }


    //pid_t id = fork();
    //if(id == 0)
    //{
        ////child
        //int cnt = 8;
        //while(cnt)
        //{
            //printf("I am a child, pid: %d, ppid: %d\n", getpid(), getppid());
            //sleep(1);
            //cnt--;
        //}
        //exit(0);
    //}
    //else
    //{
        ////child
        //int cnt = 5;
        //while(cnt)
        //{
            //printf("I am a parent, pid: %d, ppid: %d\n", getpid(), getppid());
            //sleep(1);
            //cnt--;
        //}
     //}   


    //int a = 0;
    //printf("Enter# ");
    //scanf("%d", &a);
    //printf("echo: %d\n", a);


    //while (1)
    //{
        //sleep(1);
        //printf("hello bit\n");
    //}
    return 0;
}

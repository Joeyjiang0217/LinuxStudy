#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int a = 0;
    printf("&a: %p\n", &a);
    pid_t id = fork(); 
    if (id == 0)
    {
        //child process
        a = 12;
        printf("I am a child process. My id is %d, parent: %d, &a: %p\n", getpid(), getppid(), &a);
    }
    else if(id > 0)
    {
        //parent process
        a = 12;
        printf("I am a parent process. My id is %d, &a: %p\n", getpid(), &a);
    }
    else
    {
        //error
    }

    sleep(1);
    //printf("before: only one line\n");
    //fork();
    //printf("after: only one line\n");
    //fork();
    //printf("after after: only one line\n");
    //sleep(1);
    
    //int pid = getpid();
    //while(1)
    //{
        //printf("I am a process. My id is %d. parent: %d\n", pid, getppid());
        //sleep(1);
    //}
    return 0;
}

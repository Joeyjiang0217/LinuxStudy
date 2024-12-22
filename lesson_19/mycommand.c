#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

const char* exe = "otherExe";

int main()
{
    extern char **environ;
    putenv("PRIVATE_ENV=666666");
    pid_t id = fork();
    if(id == 0)
    {
        //char* const myargv[] = {"ls", "-a", "-l", NULL};
        printf("Before: I am a process, pid: %d, ppid: %d\n", getpid(), getppid());
        //sleep(5);    
        //execl("/home/joey/Linux_108/lesson_19/otherExe", "otherExe",  NULL);

        char* const myargv[] = {"otherExe", "-a", "-b", "-c", NULL};
        //execv("otherExe", myargv);
        char* const myenv[] = {"HELLO=123", "WORLD=456", "XIXI=789", NULL};
        execle("./otherExe", "otherExe", "-a", "-w", "-v", NULL, myenv);
        
        //execl("/usr/bin/bash", "bash", "test.sh", NULL);
        //execl("/usr/bin/python", "python", "test.py", NULL);
        //execlp("ls", "ls", "-a",  NULL);
        //execv("/usr/bin/ls", myargv);
        //execvp("ls", myargv);
        //execle("/usr/bin/ls", "ls", "-a", "-l", NULL, en
        //execl("/home/joey/Linux_108/lesson_19/a.out", "./a.out", NULL);
       
        printf("After: I am a process, pid: %d, ppid: %d\n", getpid(), getppid());
        exit(100);
    }
    int status = 123456;
    pid_t ret = waitpid(id, &status, 0);
    if(ret > 0)
    {
        printf("wait success\n, father pid: %d, ret id: %d, return status: %d\n", getpid(), ret, WEXITSTATUS(status));
    }
    //sleep(5);
    return 0;
}

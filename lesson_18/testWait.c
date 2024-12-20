#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 10

//void RunChild()
//{
    //int cnt = 5;
    //while(cnt)
    //{
        //printf("I am a child process, pid: %d, ppid: %d, cnt : %d\n", getpid(), getppid(), cnt);
        //sleep(1);
        //cnt--;
    //}
//}


#define TASK_NUM 10

typedef void(*task_t)();
task_t tasks[TASK_NUM];

void task1()
{
    printf("This is a task that performs printing logs. pid: %d\n", getpid());
}

void task2()
{
    printf("This is a task that performs checking the health of the network. pid: %d\n", getpid());
}

void task3()
{
    printf("This is a task that performs drawing a graphical interface. pid: %d\n", getpid()); 
}

void InitTask()
{
    for(int i = 0; i < TASK_NUM; i++)
    {
        tasks[i] = NULL;
    }
}

int AddTask(task_t t)
{
    int pos = 0;
    for (; pos < TASK_NUM; pos++)
    {
        if(!tasks[pos])
        {
            break;
        }
    }
    if(pos == TASK_NUM)
    {
        return -1;
    }
    tasks[pos] = t;
    return 0;

}

void ExecuteTask()
{
    for(int i = 0; i < TASK_NUM; i++)
    {
        if(!tasks[i])
        {
            continue;
        }
        tasks[i]();
    }
}


int main()
{
    // wait pid





    //for (int i = 0; i < N; i++)
    //{
        //pid_t id = fork();
        //if(id == 0)
        //{
            //RunChild();
            //exit(i);
        //}
        //printf("create child process: %d success\n", id);
    //}
    //sleep(3);
//
    //for(int i = 0; i < N; i++)
    //{
        //int status = 0;
        //pid_t id = waitpid(-1, &status, 0);
        //if (id > 0 )
        //{
            //printf("wait pid: %d successi, exit sig: %d, exit status: %d\n", id, WIFEXITED(status), WEXITSTATUS(status));
        //}
//
    //}
    //sleep(5);




    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        return 1;
    }
    else if(id == 0)
    {
        //child
        int cnt = 5;
        while(cnt)
        {
            printf("I am a child, pid: %d, ppid: %d, cnt: %d\n", getpid(), getppid(), cnt);
            cnt--;
            sleep(1);
            //int* a = NULL;
            //*a = 1;
        }
        exit(11);
    }
    else
    {
        //parent
        //int cnt = 5;
        //while(cnt)
        //{
            //printf("I am a parent, pid: %d, ppid: %d, cnt: %d\n", getpid(), getppid(), cnt);
            //cnt--;
            //sleep(1);
        //}
        //pid_t ret = wait(NULL);
        int status = 0;
        InitTask();
        AddTask(task1);
        AddTask(task2);
        AddTask(task3);
        while(1)
        {
            pid_t ret = waitpid(id, &status, WNOHANG);
            //cnt = 5;
            //while(cnt)
            //{
                //printf("The parent process is waiting. %d\n", cnt);
                //sleep(1);
                //cnt--;
            //}
            
            if(ret == id)
            {
                //printf("wait success, ret: %d, status: %d, exit sig: %d, exit code: %d\n", ret, status, status&0x7f, (status>>8)&0xff);
                printf("wait success, ret: %d, status: %d, exit sig: %d, exit code: %d\n", ret, status, WIFEXITED(status), WEXITSTATUS(status));
                break;
            }
            else if(ret == -1)
            {
                printf("wait failed.\n");
                break;
            }
            else if(ret == 0)
            {
                ExecuteTask();  
                //printf("wait not ready.\n");
            }
            usleep(500000);
        }
        

        sleep(2);
    }


    return 0;
}

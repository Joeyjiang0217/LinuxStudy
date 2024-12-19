#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//int g_val = 100;
//
//int main()
//{
    //pid_t id = fork();
    //if (id == 0)
    //{
        ////child process
        //int cnt = 5;
//
        //while(1)
        //{
            //printf("I am a child process, pid : %d, ppid : %d, g_val : %d, &g_val : %p\n", getpid(), getppid(), g_val, &g_val);
            //sleep(1);
            //if (cnt)
            //{
                //cnt--;
            //}
            //else
            //{
                //g_val = 200;
                //printf("child process changes g_val : 100 -> 200\n");
                //cnt--;
            //}
//
        //}    
        //
        //
//
    //}
    //else
    //{
        ////parent process
        //while(1)
        //{
            ////g_val = 123456789;
            //printf("I am a parent process, pid : %d, ppid : %d, g_val : %d, &g_val : %p\n", getpid(), getppid(), g_val, &g_val);
            //sleep(1);
        //}    
//
//
//
    //}
    //return 0;
//}


int g_val_1;
int g_val_2 = 100;

int main(int argc, char* argv[], char* env[])
{
    printf("code addr: %p\n", &main);
    
    const char* str = "hello bit";
    printf("read only string addr: %p\n", str);

    printf("init global value addr: %p\n", &g_val_2);

    printf("uninit global value addr: %p\n", &g_val_1);

    char* mem = (char*)malloc(100);
    char* mem_2 = (char*)malloc(100);
    printf("heap addr mem: %p\n", mem);
    printf("heap addr mem_2: %p\n", mem_2);

    int a = 0;
    printf("stack addr a: %p\n", &a);
    printf("stack addr mem_2: %p\n", &mem_2);
    printf("stack addr mem: %p\n", &mem);
    printf("stack addr str: %p\n", &str);

    
    static int sta_b = 0;
    printf("static addr sta_b: %p\n", &sta_b);
    
    printf("&argc: %p\n", &argc);
    printf("&argv: %p\n", &argv);
    int i = 0;
    for(i = 0; argv[i]; i++)
    {
        printf("argv[%d]: %p\n", i, argv[i]);
    }
    
    printf("&env: %p\n", &env);
    for(i = 0; env[i]; i++)
    {
        printf("env[%d]: %p\n", i, env[i]);
    }


    //printf("xxx = %s\n", getenv("xxx"));
    return 0;
}


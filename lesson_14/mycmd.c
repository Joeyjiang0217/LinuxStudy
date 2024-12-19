#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[], char* env[])
{
    extern char** environ;
    int i = 0;
    for(; environ[i]; i++)
    {
        printf("environ[%d] -> %s\n", i, environ[i]);
    }

    //sleep(30);
    //printf("change begin\n");
    //if(argc == 2)
    //{
        //chdir(argv[1]);
    //}
    //printf("change end\n");
    //sleep(30);

    //printf("MYVAL: %s\n", getenv("MYVAL")); 

    //int i = 0;
    //for(; argv[i]; i++)
    //{
        //printf("argv[%d] -> %s\n", i, argv[i]);
    //}
//
    //int i = 0;
    //for(; env[i]; i++)
    //{
        //printf("env[%d] -> %s\n", i, env[i]);
    //}

    //if(argc != 2)
    //{
        //printf("Usage: %s -[a|b|c|d]\n", argv[0]);
        //return 0;
    //}
   //
    //if (strcmp(argv[1], "--help") == 0)
    //{
        //printf("Usage: %s -[a|b|c|d]\n", argv[0]);
    //}
    //else if (strcmp(argv[1], "-a") == 0)
    //{
        //printf("Function 1\n");
    //}
    //else if (strcmp(argv[1], "-b") == 0)
    //{
        //printf("Function 2\n");
    //}
    //else if (strcmp(argv[1], "-c") == 0)
    //{
        //printf("Function 3\n");
    //}
    //else if (strcmp(argv[1], "-d") == 0)
    //{
        //printf("Function 4\n");
    //}
    //else
    //{
        //printf("Usage: %s -[a|b|c|d]\n", argv[0]);
        //return 0;
    //}



    //char who[32];
    //strcpy(who, getenv("USER"));
    //
    //if(strcmp(who, "root") == 0)
    //{
        //printf("A super user\n");
    //}
    //else
    //{
        //printf("A common user\n");
    //}

    //printf("%s\n", who);

    //printf("user: %s\n", getenv("USER"));

    //printf("PATH: %s\n", getenv("PATH"));   

    //int i = 0;
    //for(; i<10; i++)
    //{
        //printf("hello %d\n", i);
    //}

    return 0;
}

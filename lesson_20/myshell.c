#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEFT "["
#define RIGHT "]"
#define LABLE "#"
#define DELIM " \t"
#define LINE_SIZE 1024
#define ARGC_SIZE 32
#define EXIT_CODE 44

#define FORMAT LEFT"%s@%s %s"RIGHT""LABLE" "

int lastcode = 0;
int quit = 0;
extern char **environ;
char commandline[LINE_SIZE];
char* argv[ARGC_SIZE];
char pwd[LINE_SIZE];
char myenv[LINE_SIZE];

const char *getusername()
{
    return getenv("USER");
}

const char* gethostname()
{
    return getenv("HOSTNAME");
}

void getpwd()
{
    getcwd(pwd, sizeof(pwd));
}

void interact(char* cline, int size)
{
    getpwd();
    printf(FORMAT, getusername(), gethostname(), pwd);
    char *s = fgets(cline, size, stdin);
    assert(s != NULL);
    //void(s);
    //printf("%d\n", strlen(cline));
    cline[strlen(cline)-1] = 0;
}    

int splitstring(char* cline,  char* _argv[])
{
    int i = 0;
    //printf("%d\n", strlen(cline));
    //printf("%d\n", strlen((char*)cline + 1));
    _argv[i] = strtok(cline, DELIM);
    while(_argv[i] != NULL)
    {
        i++;
        _argv[i] = strtok(NULL, DELIM);
    }
    //while(_argv[i++] = strtok(NULL, DELIM));
    //printf("%p\n", _argv[i]);
    //while(_argv[i] != NULL);
    //{
        //printf("%d\n", i);
        //i++;
        //_argv[i] = strtok(NULL, DELIM);
    //}
    
    return i;
}

void NormalExcute(char* _argv[])
{
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        return;
    }
    else if(id == 0)
    {
        //execvpe(_argv[0], _argv, environ);
        execvp(_argv[0], _argv);
        exit(EXIT_CODE);
    }
    else
    {
        int status = 0;
        pid_t rid = waitpid(id, &status, 0);
        if(rid == id)
        {
            lastcode = WEXITSTATUS(status); 
        }
    }   
}

int buildCommand(char* _argv[], int _argc)
{
    if (_argc == 2 && strcmp(_argv[0], "cd") == 0)
    {
        chdir(_argv[1]);
        getpwd();
        sprintf(getenv("PWD"), "%s", pwd);
        return 1;
    }
    else if(_argc == 2 && strcmp(_argv[0], "export") == 0)
    {
        strcpy(myenv, _argv[1]);
        putenv(myenv);
        return 1;
    }
    else if(_argc == 2 && strcmp(_argv[0], "echo") == 0)
    {
        if(strcmp(_argv[1], "$?") == 0)
        {
            printf("%d\n", lastcode);
            lastcode = 0;
        }
        else if(*_argv[1] == '$')
        {
            char* val = getenv(_argv[1] + 1);
            if(val != NULL)
            {
                printf("%s\n", val);
            }
        }
        else
        {
            printf("%s\n", _argv[1]);
        }
        return 1;
    }

    if(strcmp(_argv[0], "ls") == 0)
    {
        _argv[_argc++] = "--color";
        _argv[_argc] = NULL;
    }
    return 0;
}


int main()
{ 
    while(!quit)
    {
        // 2. Getting command line arguments
        interact(commandline, sizeof(commandline)); 
        //printf("echo: %s\n", commandline);
        printf(commandline);        
        // 3. Parsing command line arguments
        int argc = splitstring(commandline, argv);
//        printf(commandline);
        //printf("%d\n", argc);
        if(argc == 0)
        {
            continue;
        }
        //debug
        //for(int i = 0; argv[i]; i++)
        //{
            //printf("[%d]: %s\n", i, argv[i]);
        //}

        // 4. Checking command
        int n = buildCommand(argv, argc);

        // 5. Excuting normal command
        if(!n)
        {
            NormalExcute(argv);
        }
    }


    return 0;
}

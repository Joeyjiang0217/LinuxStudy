#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define filename "log.txt"

int main()
{
    fprintf(stdout, "hello normal message\n");
    fprintf(stdout, "hello normal message\n");
    fprintf(stdout, "hello normal message\n");
    fprintf(stdout, "hello normal message\n");
    fprintf(stdout, "hello normal message\n");


    fprintf(stderr, "hello error message\n");
    fprintf(stderr, "hello error message\n");
    fprintf(stderr, "hello error message\n");
    fprintf(stderr, "hello error message\n");
    fprintf(stderr, "hello error message\n");

    
    //close(1);
    //int n = printf("stdin->fd: %d\n", stdin->_fileno);
    //printf("stdout->fd: %d\n", stdout->_fileno);
//
    //
    //fprintf(stderr, "printf ret: %d\n", n);



    //char buffer[1024];
//
    //ssize_t s = read(0, buffer, sizeof(buffer));
    //if(s<0)
    //{
        //return 1;
    //}
    //buffer[s] = '\0';
    //printf("echo : %s\n", buffer);


    //umask(0);
    ////int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    //int fd1 = open("log1.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    //int fd2 = open("log2.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    //int fd3 = open("log3.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    //int fd4 = open("log4.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    //printf("fd1: %d\n", fd1);
    //printf("fd2: %d\n", fd2);
    //printf("fd3: %d\n", fd3);
    //printf("fd4: %d\n", fd4);
    //if (fd1 < 0)
    //{
        //printf("open file error\n");
        //return 1;
    //}
    //
    ////const char* message = "hello file system call\n";
    //const char* message = "xxxxx\n";
    ////write(fd, message, strlen(message));
    //write(1, message, strlen(message));
    //write(2, "hello error", 3);
//
    //close(fd1);
    //close(fd2);
    //close(fd3);
    //close(fd4);
    return 0;
}



//#define ONE (1<<0)
//#define TWO (1<<1)
//#define THREE (1<<2)
//#define FOUR (1<<3)
//
//void show(int flags)
//{
    //if(flags & ONE)
    //{
        //printf("hello function1\n");
    //}
    //if(flags & TWO)
    //{
        //printf("hello function2\n");
    //}
    //if(flags & THREE)
    //{
        //printf("hello function3\n");
    //}
    //if(flags & FOUR)
    //{
        //printf("hello function4\n");
    //}
//}
//
//int main()
//{
    ////show(1);
    ////printf("\n");
    ////show(3);
    ////printf("\n");
    ////show(7);
    ////printf("\n");
    ////show(15);
    ////printf("\n");
    ////show(9);
    ////printf("\n");
    ////show(5);
    ////printf("\n");
    //show(ONE);
    //printf("\n");
    //show(ONE | THREE);
    //printf("\n");
    //show(ONE | TWO | THREE);
    //printf("\n");
    //return 0; 
//}




//int main()
//{
    //printf("Pid: %d\n", getpid());
////    chdir("../");
    //FILE* fp = fopen("log.txt", "a");
    //if(fp == NULL)
    //{
        //perror("fopen");
        //return 1;
    //}
    //
    //const char* message = "abcd";
    //// strlen(message) + 1? 
    ////fwrite(message, strlen(message), 1, stdout);
    //fprintf(stderr, "%s: %d\n", message, 1324);
    //fclose(fp);
    ////sleep(1000);
    //return 0;
//}

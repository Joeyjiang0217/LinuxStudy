#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define filename "log.txt"

int main()
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    //int fd = open(filename, O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }
    dup2(fd, 1);
    //fprintf(stderr, "%d\n", fd);
    close(fd);
    printf("fd: %d\n", fd);
    printf("hello printf\n");
    fprintf(stdout, "hello fprintf\n"); 

    //close(fd);
    //char inbuffer[1024];
    //ssize_t s = read(0, inbuffer, sizeof(inbuffer) - 1);
    //if (s > 0)
    //{
        //inbuffer[s] = '\0';
        //printf("echo# %s", inbuffer);
    //}
    

    //dup2(fd, 1);
    //close(fd);
    //const char* message = "hello file\n";
    //int cnt = 5;
    //while(cnt)
    //{
        //write(fd, message, strlen(message));
        //cnt--;
    //}

    close(fd);
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>


#define N 2
#define NUM 1024

using namespace std;

// child
void Writer(int wfd)
{
    string s = "Hello, I am a child.";
    pid_t self = getpid();
    int number = 0;

    char buffer[NUM];
    while(true)
    {
        sleep(1);
        // build the sending string
        buffer[0] = 0; // this array is being treated as a string
        snprintf(buffer, sizeof(buffer), "%s-%d-%d", s.c_str(), self, number++);
        //cout << buffer << endl;

        // send/write to the parent process
        write(wfd, buffer, strlen(buffer));
        // char c = 'c';
        // write(wfd, &c, 1);
        // number++;
        // cout << number << endl;

        // if(number >= 5)
        // {
        //     break;
        // }
        //sleep(1);
    }
}

// parent
void Reader(int rfd)
{
    char buffer[NUM];
    int cnt = 5;
    while(cnt)
    {

        buffer[0];
        ssize_t n = read(rfd, buffer, sizeof(buffer));
        if(n > 0)
        {
            buffer[n] = 0;
            cout << "The parent process gets a message[" << getpid() << "]# " << buffer << endl;
            cout << "------------------------------------------------\n";
            
        }
        else if(n == 0)
        {
            printf("parent read file done!\n");
            break;
        }
        else
        {
            break;
        }

        cnt--;
        if(cnt == 0)
        {
            break;
        }

        // cout << "n: " << n << endl;
    }


}

int main()
{
    int pipefd[N] = {0};
    int n = pipe(pipefd);
    if(n < 0)
    {
        return 1;
    }

    // cout << "pipefd[0]: " << pipefd[0] << ", pipefd[1]: " << pipefd[1] << endl;
    
    // child -> w, parent -> read
    pid_t id = fork();
    if(id < 0)
    {
        return 2;
    }
    if(id == 0)
    {
        // child
        close(pipefd[0]);
        // IPC code
        Writer(pipefd[1]);
        close(pipefd[1]);
        exit(0);
    }

    // parent
    close(pipefd[1]);
    // IPC code
    Reader(pipefd[0]); // read for 5s
    close(pipefd[0]);
    cout << "parent process close read fd: " << pipefd[0] << endl;

    sleep(5);
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if(rid < 0)
    {
        return 3;
    }

    cout << "wait child success: " << rid << "exit code: " << ((status>>8)&0xFF) << " exit signal: " << (status&0x7f) << endl;

    sleep(5);

    cout << "parent quit" << endl;

    return 0;
}

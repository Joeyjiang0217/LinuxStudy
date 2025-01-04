#include <iostream>
#include <signal.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void handler(int signo)
{
    sleep(5);
    pid_t rid;
    while( (rid = waitpid(-1, nullptr, WNOHANG)) > 0)
    {
        cout << "I am a process: " << getpid() << ". catch a signo: " << signo <<\
        "Child process quit: " << rid << endl;
    }
    
}

int main()
{
    signal(17, SIG_IGN);
    srand(time(nullptr));
    //signal(17, handler);
    
    for (int i = 0; i < 10; i++)
    {
        pid_t id = fork();
        if (id == 0)
        {
            while (true)
            {
                cout << "I am a child process: " << getpid() << ", ppid: " << getppid() << endl;
                sleep(5);
                break;
            }
            cout << "Child quit!" << endl;
            exit(0);
        }
        sleep(1);
    }

    // parent process
    while(true)
    {
        cout << "I am a parent process: " << getpid() << endl;
        sleep(1);
    }
    return 0;
}



// int flag = 0;

// void handler(int signo)
// {
//     cout << "catch a signal: " << signo << endl;
//     flag = 1;
// }

// int main()
// {
//     signal(2, handler);
//     while(!flag)
//     {
//         ;
//     }
//     cout << "process quit normal" << endl;
//     return 0;
// }


// void PrintPending()
// {
//     sigset_t set;
//     sigpending(&set);

//     for(int signo = 31; signo >= 1; signo--)
//     {
//         if(sigismember(&set, signo))
//         {
//             cout << "1";
//         }
//         else
//         {
//             cout << "0";
//         }
//     }
//     cout << endl;
// }

// void handler(int signo)
// {
//     cout << "catch a signal, signal number: " << signo << endl;
//     while(true)
//     {
//         PrintPending();
//         sleep(1);
//     }

// }

// int main()
// {
//     struct sigaction act, oact;
//     memset(&act, 0, sizeof(act));
//     memset(&oact, 0, sizeof(oact));
//     sigemptyset(&act.sa_mask);
//     sigaddset(&act.sa_mask, 1);
//     sigaddset(&act.sa_mask, 3);
//     sigaddset(&act.sa_mask, 4);

//     act.sa_handler = handler;
//     sigaction(2, &act, &oact);

//     while(true)
//     {
//         cout << "I am a process. pid" << getpid() << endl;
//         sleep(1);
//     }
//     return 0;
// }

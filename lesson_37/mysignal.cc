#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void PrintPending(sigset_t& pending)
{
    for(int signo = 31; signo >= 1; signo--)
    {
        if(sigismember(&pending, signo))
        {
            cout << "1";
        }
        else
        {
            cout << "0";
        }
    }
    cout << "0";
    cout << endl << endl;
}

void handler(int signo)
{
    cout << "catch a signo: " << signo << endl;
}

int main()
{
    sigset_t bset, oset, pending;
    sigemptyset(&bset);
    sigemptyset(&oset);
    for(int i = 1; i <= 31; i++)
    {
        sigaddset(&bset, i);
    }
    sigprocmask(SIG_SETMASK, &bset, &oset);
    int cnt = 1;
    while(true)
    {
        cout << "proc is running. pid: " << getpid() << endl;
        if(cnt <= 31)
        {
            if(cnt != 9 && cnt != 19)
            {
                kill(getpid(), cnt);
            }
            cnt++;
        }
        // kill(getpid(), 18);

        int n = sigpending(&pending);
        if(n < 0)
        {
            continue;
        }
        PrintPending(pending);
        sleep(1);
    }


    // // 0. customized capture of signal 2
    // signal(2, handler);

    // // 1. block signal 2
    // sigset_t bset, oset;
    // sigemptyset(&bset);
    // sigemptyset(&oset);
    // sigaddset(&bset, 2);

    // // 1.2 call system call
    // sigprocmask(SIG_SETMASK, &bset, &oset);

    // // 2. repeat printing the sigset of pending signals 0000 0000 0000 0000 0000 0000 0000 0000
    // sigset_t pending;
    // int cnt = 0;
    // while(true)
    // {
    //     // 2.1 get
    //     int n = sigpending(&pending);
    //     if(n < 0)
    //     {
    //         continue;
    //     }

    //     // 2.2 print
    //     PrintPending(pending);
    //     sleep(1);
    //     cnt++;

    //     // 2.3 unblock
    //     if(cnt == 10)
    //     {
    //         cout << "unblock signo 2" << endl;
    //         sigprocmask(SIG_SETMASK, &oset, nullptr);
    //     }

    // }
    
    // // 3. send signal 2 0000 0000 0000 0000 0000 0000 0000 0100


    return 0;
}
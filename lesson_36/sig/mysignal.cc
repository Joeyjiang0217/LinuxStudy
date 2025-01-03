#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    signal(2, SIG_DFL);

    while(1)
    {
        cout << "hello signal" << endl;
        sleep(1);
    }

    // int a = 10;
    // int b = 0;

    // a /= b;

    // cout << "a = " << a << endl;
    // pid_t id = fork();
    // if(id == 0)
    // {
    //     // child
    //     int cnt = 500;
    //     while(cnt)
    //     {
    //         cout << "I am a child process. Pid: " << getpid() \
    //         << ", cnt: " << cnt << endl;
    //         sleep(1);
    //         cnt--;
    //     }
    //     exit(0);
    // }
    
    // // parent
    // int status = 0;
    // pid_t rid = waitpid(id, &status, 0);
    // if(rid == id)
    // {
    //     cout << "Child quit info, rid: " << rid << " exit code: " \
    //     << ((status>>8)&0xFF) << ", exit signal: " << (status&0x7F) \
    //     << " core dump: " << ((status>>7)&1) << endl;
    // }
    return 0;
}


// void work()
// {
//     cout << "print log..." << endl;
// }

// void handler(int signo)
// {
//     cout << "...get a sig, number: " << signo << endl;
//     // exit(1);
//     // work();
//     int n = alarm(3);
//     cout << "remaining time: " << n << endl;
// }

// int main()
// {
//     signal(SIGALRM, handler);
//     int n = alarm(50);
//     int cnt = 0;
//     while(1)
//     {
//         cout << "proc is running... pid: " << getpid() << endl;
//         // if(cnt % 5 == 0)
//         // {
//         //     kill(getpid(), SIGALRM);
//         // }
//         // cnt++;
//         sleep(1);
//     }


//     //signal(SIGFPE, handler);
//     // cout << "div before" << endl;
//     // signal(SIGSEGV, handler);
//     // cout << "pointer error before" << endl;
//     // sleep(1);

//     // char buffer[1024];
//     // int n = 1024;
//     // n = read(4, buffer, n);
//     // printf("n = %d\n", n);
//     // perror("read");
//     // int* p = nullptr;
//     // *p = 100;


//     // cout << "pointer error after" << endl;
//     // int a = 10;
//     // a /= 0; // exception
//     //cout << "div after" << endl;
//     sleep(1);
//     return 0;
// }
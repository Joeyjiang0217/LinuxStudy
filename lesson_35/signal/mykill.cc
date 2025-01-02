#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;

void myhandler(int signo)
{
    cout << "process gets a signal: " << signo << endl;
    // exit(1);
}

void Usage(string proc)
{
    cout << "Usage:\n\t" << proc << " signum pid\n\n";
}

int main(int argc, char* argv[])
{
    signal(SIGABRT, myhandler);
    int cnt = 0;
    while(true)
    {
        cout << "I am a process, pid: " << getpid() << endl;
        sleep(1);
        cnt++;
        if(cnt % 2 == 0)
        {
            // kill(getpid(), 2);
            //raise(2);
            // abort();
        }
    }

    // if(argc != 3)
    // {
    //     Usage(argv[0]);
    //     exit(1);
    // }

    // int signum = stoi(argv[1]);
    // pid_t pid = stoi(argv[2]);
    // int n = kill(pid, signum);
    // if(n == -1)
    // {
    //     perror("kill");
    //     exit(2);
    // }
    return 0;
}





// int main()
// {
//     signal(SIGINT, myhandler);
//     signal(3, myhandler);
//     signal(19, myhandler);

//     for(int i = 1; i <= 31; i++)
//     {
//         signal(i, myhandler);
//     }

//     while(true)
//     {
//         cout << "I am a crazy process. pid: " << getpid() << endl;
//         sleep(1);
//     }


    
//     return 0;
// }
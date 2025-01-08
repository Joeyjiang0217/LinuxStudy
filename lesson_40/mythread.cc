#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

std::string toHex(pthread_t tid)
{
    char hex[64];
    snprintf(hex, sizeof(hex), "%p", (void*)tid);
    return hex;
}

void* threadRoutine(void* args)
{
    int i = 0;
    while(true)
    {
        cout << "thread id: " << toHex(pthread_self()) << ", i = " << i << endl;
        i++;
        sleep(1);
    }
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, nullptr, threadRoutine, (void*)"thread 1");
    pthread_create(&tid2, nullptr, threadRoutine, (void*)"thread 2");

    cout << "main thread1 create thread done, new thread id: " << toHex(tid1) << endl;
    cout << "main thread2 create thread done, new thread id: " << toHex(tid2) << endl;
    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    return 0;
}


// void threadRun()
// {
//     int count = 3;
//     while(count)
//     {
//         cout << "I am a new thread for C++" << endl;
//         count--;
//         sleep(1);
//     }
// } 

// int main()
// {
//     thread t1(threadRun);
    
//     t1.join();

//     return 0;
// }



// class Requeset
// {
// public:
//     Requeset(int start, int end, const string &threadname)
//         : start_(start),
//           end_(end),
//           threadname_(threadname)
//     {
//     }

// public:
//     int start_;
//     int end_;
//     string threadname_;
// };

// class Response
// {
// public:
//     Response(int result, int exitcode)
//         : result_(result),
//           exitcode_(exitcode)
//     {
//     }

// public:
//     int result_;
//     int exitcode_;
// };

// void* sumCount(void* args)
// {
//     Requeset* rq = static_cast<Requeset*>(args);
//     Response* rsp = new Response(0, 0);
//     for(int i = rq->start_; i <= rq->end_; i++)
//     {
//         cout << rq->threadname_ << " is running to calculate. i: " << i << endl; 
//         rsp->result_ += i;
//         usleep(100000);
//     }
//     delete rq;
//     return rsp;
// }

// int main()
// {
//     pthread_t tid;
//     Requeset* rq = new Requeset(1, 100, "thread 1");
//     pthread_create(&tid, nullptr, sumCount, rq);

//     void* ret;
//     pthread_join(tid, &ret);
//     Response* rsp = static_cast<Response*>(ret);
//     cout << "rsp->result: " << rsp->result_ << ", exitcode: " << rsp->exitcode_ << endl;
//     delete rsp;

//     return 0;
// }


// int g_val = 100;

// void show(const string& name)
// {
//     cout << name << "say# " << "hello thread" << endl;
// }

// void* threadRoutine(void* args)
// {
//     const char* name = (const char*)args;
//     int cnt = 5;
//     while(true)
//     {
//         printf("%s, pid: %d, g_val: %d, &g_val: %p\n", name, getpid(), \
//         g_val, &g_val);
//         // cout << "new thread, pid: " << getpid() << endl;
//         // show("[new thread]");
//         sleep(1);
//         // g_val++;
//         //int a = 10;
//         //a /= 0;
//         cnt--;
//         if(cnt == 0)
//         {
//             break;
//         }
//     }
//     pthread_exit((void*)11);
//     //exit(11);
//     //return (void*)1;
// }

// int main()
// {
//     // cout << "point size: " << sizeof(void*) << endl;
//     // cout << "void size: " << sizeof(void) << endl;

//     pthread_t tid;
//     pthread_create(&tid, nullptr, threadRoutine, (void*)"Thread 1");

//     sleep(1);

//     pthread_cancel(tid);

//     // sleep(1);
//     // return 0;
//     // while(true)
//     // {
//     //     printf("main thread, pid: %d, g_val: %d, &g_val: %p, create new thread tid: %p\n", getpid(), \
//     //     g_val, &g_val, (void*)tid);
//     //     // cout << "main thread, pid: " << getpid() << ", g_val: " << g_val << \
//     //     // ", &g_val: " << &g_val << endl;
//     //     // show("[main thread]");
//     //     sleep(1);
//     //     g_val++;
//     // }
//     //sleep(7);

//     void* retval;
//     pthread_join(tid, &retval);

//     cout << "main thread quit..., ret: " << (long)retval << endl;
//     return 0;
// }
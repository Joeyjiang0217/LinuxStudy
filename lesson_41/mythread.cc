#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <pthread.h>

using namespace std;

#define NUM 4

int tickets = 1000; // Simulating a single ticket grab with multiple threads

class threadData
{
public:
    threadData(int number)
    {
        threadname = "thread-" + to_string(number);
    }
public:
    string threadname;
};

void* getTicket(void* args)
{
    threadData* td = static_cast<threadData*>(args);
    const char* name = td->threadname.c_str();

    while (true)
    {
        if (tickets > 0)
        {
            usleep(1000);
            printf("who=%s, get a ticket: %d\n", name, tickets);
            tickets--;
        }
        else
        {
            break;
        }
    }

    printf("%s ... quit\n", name);

    return nullptr;
}

int main()
{
    vector<pthread_t> tids;
    vector<threadData*> thread_datas;
    for (int i = 1; i <= NUM; i++)
    {

        pthread_t tid;
        threadData* td = new threadData(i);
        thread_datas.push_back(td);
        pthread_create(&tid, nullptr, getTicket, thread_datas[i - 1]);
        tids.push_back(tid);
    }

    for (auto thread : tids)
    {
        pthread_join(thread, nullptr);
    }
    for (auto td : thread_datas)
    {
        delete td;
    }

    return 0;
}















// // int* p = NULL;

// __thread unsigned int number = 0;
// __thread int pid = 0;

// struct threadData
// {
//     string threadname;
// };

// // __thread threadData td;

// string toHex(pthread_t tid)
// {
//     char buffer[128];
//     snprintf(buffer, sizeof(buffer), "0x%lx", tid);
//     return buffer;
// }

// void InitThreadData(threadData* td, int number)
// {
//     td->threadname = "thread-" + to_string(number);

// }

// void* threadRoutine(void* args)
// {
//     pthread_detach(pthread_self());
//     // int test_i = 0;
//     threadData* td = static_cast<threadData*>(args);
//     string tid = toHex(pthread_self());
//     pid = getpid();

//     // if(td->threadname == "thread-2")
//     // {
//     //     p = &test_i;
//     // }
//     int i = 0;
//     while (i < 3)
//     {
//         cout << "tid: " << tid << ", pid: " << pid << endl;
//         // cout << "pid: " << getpid() << ", tid: " << \
//         //  toHex(number) << ", threadname: " << td->threadname << 
//         //  ", g_val: " << g_val << ", &g_val: " << &g_val << endl;
//         sleep(1); 
//         i++;

//     }
//     delete td;
//     return nullptr;
// }

// int main()
// {
//     vector<pthread_t> tids;
//     for(int i = 0; i < NUM; i++)
//     {
//         threadData* td = new threadData;
//         InitThreadData(td, i);
//         pthread_t tid;
//         pthread_create(&tid, nullptr, threadRoutine, td);

//         tids.push_back(tid);
//         // sleep(1);
//     }

//     sleep(1);
//     // cout << "main thread gets a thread loacl value, val: " << *p <<", &val " << p << endl;

//     // for (auto i : tids)
//     // {
//     //     pthread_detach(i);
//     // }

//     for(int i = 0; i < tids.size(); i++)
//     {
//         int n = pthread_join(tids[i], nullptr);
//         printf("n = %d, who = 0x%lx, why: %s\n", n, tids[i], strerror(n));
//     }

//     return 0;
// }
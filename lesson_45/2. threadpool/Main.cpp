#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "ThreadPool.hpp"
#include "Task.hpp"


int main()
{
    ThreadPool<Task>* tp = new ThreadPool<Task>(5);
    tp->Start();

    srand(time(nullptr) ^ getpid());
    while (true)
    {
        // 1. create tasks
        int x = rand() % 10 +1;
        usleep(10);
        int y = rand() % 5;
        char op = opers[rand() % opers.size()];

        Task t(x, y, op);
        tp->Push(t);
        // 2. hand tasks to the ThreadPool

        std::cout << "Main thread made a task: " << t.GetTask() << std::endl;
        sleep(1);
    }
    return 0;
}
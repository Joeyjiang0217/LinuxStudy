#include <iostream>
#include <unistd.h>
#include <vector>
#include "Thread.hpp"

void Print()
{
    while(true)
    {
        printf("haha, 我是一个封装的线程...\n");
        sleep(1);
    }
}

int main()
{
    std::vector<Thread> threads;

    for (int i = 0; i < 10; i++)
    {
        threads.push_back(Thread(Print));
    }

    for (auto& t : threads)
    {
        t.Run();
    }

    for (auto& t : threads)
    {
        t.Join();
    }
    // Thread t(Print);
    // t.Run();

    // std::cout << "是否启动成功：" << t.IsRunning() << std::endl;
    // std::cout << "启动成功时间戳：" << t.StartTimestamp() << std::endl;
    // std::cout << "线程的名字：" << t.Name() << std::endl;

    // t.Join();
    return 0;
}
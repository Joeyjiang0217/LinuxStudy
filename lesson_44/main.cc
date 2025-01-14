#include "BlockQueue.hpp"
#include "Task.hpp"
#include <ctime>

void* Consumer(void* args)
{
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);

    while (true)
    {
        Task t = bq->pop();
        // t.run();
        // std::cout << "A data was consumed: " << d << std::endl; 
        t();
        std::cout << "A task was completed: " << t.GetTask() << ". The result of the task is " << \
        t.GetResult() << ". Thread id: " << pthread_self() << std::endl;
        // sleep(1);
    }

    return nullptr;
}

void* Productor(void* args)
{
    int len = opers.size();

    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);

    int x = 10;
    int y = 20;
    while (true)
    {
        // simulatating producer producting data
        int data1 = rand() % 10 + 1;
        usleep(10);
        int data2 = rand() % 10 + 1;
        char op = opers[rand() % len];
        Task t(data1, data2, op);



        bq->push(t);
        std::cout << "A task was created: " << t.GetTask() << \
        ". Thread id: " << pthread_self() << std::endl; 
        sleep(1);
    }

    return nullptr;
}

int main()
{
    srand(time(nullptr));

    BlockQueue<Task>* bq = new BlockQueue<Task>();
    pthread_t c[3], p[5];

    for (int i = 0; i < 3; i++)
    {
        pthread_create(c + i, nullptr, Consumer, bq);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(p + i, nullptr, Productor, bq);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(c[i], nullptr);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(p[i], nullptr);
    }
    delete bq;

    return 0;
}
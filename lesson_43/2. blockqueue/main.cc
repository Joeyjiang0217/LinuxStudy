#include "BlockQueue.hpp"
#include "Task.hpp"

void* Consumer(void* args)
{
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);

    while (true)
    {
        Task t = bq->pop();
        t.run();
        std::cout << "A data was completed: " << std::endl; 
        // sleep(1);
    }

    return nullptr;
}

void* Productor(void* args)
{
    BlockQueue<Task>* bq = static_cast<BlockQueue<Task>*>(args);

    int x = 10;
    int y = 20;
    while (true)
    {

        Task t(x, y);
        bq->push(t);
        std::cout << "A task was created: " << std::endl; 
        // sleep(1);
    }

    return nullptr;
}

int main()
{
    BlockQueue<Task>* bq = new BlockQueue<Task>();
    pthread_t c, p;

    pthread_create(&c, nullptr, Consumer, bq);
    pthread_create(&p, nullptr, Productor, bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);
    delete bq;

    return 0;
}
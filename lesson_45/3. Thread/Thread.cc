#include <iostream>
#include <thread>
#include <unistd.h>

void run()
{
    while (true)
    {
        printf("hello world\n");
        sleep(1);
    }

}

int main()
{
    std::thread t(run);

    t.join();

    return 0;
} 
#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <pthread.h>


class Thread
{
public:
    Thread()
    {

    }

    void  Run();
    void Join();

    std::string Name();
    uint64_t StartTimestamp();
    bool IsRunning();

    ~Thread()
    {

    }
private:
    pthread_t tid;
    std::string name;
    uint64_t start_timestamp;
    bool isrunning;
};
#include <iostream>
#include <memory>
#include "EpollServer.hpp"

int main()
{
    std::cout << "Hello, Epoll Server!" << std::endl;
    std::unique_ptr<EpollServer> svr(new EpollServer());
    svr->Init();
    svr->Start();
    return 0;
}
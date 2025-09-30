#include "SelectServer.hpp"
#include <memory>

int main()
{
    // cout << "fd_set size: " << sizeof(fd_set) * 8 << endl;
    std::unique_ptr<SelectServer> svr(new SelectServer());
    svr->Init();
    svr->Start();
    return 0;
}